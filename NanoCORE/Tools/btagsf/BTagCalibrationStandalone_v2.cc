#include "BTagCalibrationStandalone_v2.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <sstream>

BTagEntry_v2::Parameters::Parameters(OperatingPoint op, std::string measurement_type, std::string sys_type, JetFlavor jf, float eta_min, float eta_max, float pt_min, float pt_max, float discr_min, float discr_max) : operatingPoint(op), measurementType(measurement_type), sysType(sys_type), jetFlavor(jf), etaMin(eta_min), etaMax(eta_max), ptMin(pt_min), ptMax(pt_max), discrMin(discr_min), discrMax(discr_max)
{
    std::transform(measurementType.begin(), measurementType.end(), measurementType.begin(), ::tolower);
    std::transform(sysType.begin(), sysType.end(), sysType.begin(), ::tolower);
}

BTagEntry_v2::BTagEntry_v2(const std::string &csvLine)
{
    // Stupid BTV has "pow(blah,2)" functions in the formula that messes up the csv format.
    TString csvLineTStr = csvLine;
    csvLineTStr.ReplaceAll("pow(x,","pow(x;");
    // make tokens
    std::stringstream buff(csvLineTStr.Data());
    std::vector<std::string> vec;
    std::string token;
    while (std::getline(buff, token, ","[0]))
    {
        token = BTagEntry_v2::trimStr(token);
        if (token.empty())
        {
            continue;
        }
        vec.push_back(token);
    }
    if (vec.size() != 11)
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "Invalid csv line; num tokens != 11: " << csvLine << std::endl;
        throw std::exception();
    }

    // clean string values
    char chars[] = " \"\n";
    for (unsigned int i = 0; i < strlen(chars); ++i)
    {
        vec[1].erase(remove(vec[1].begin(), vec[1].end(), chars[i]), vec[1].end());
        vec[2].erase(remove(vec[2].begin(), vec[2].end(), chars[i]), vec[2].end());
        vec[10].erase(remove(vec[10].begin(), vec[10].end(), chars[i]), vec[10].end());
    }

    // make formula
    formula = vec[10];
    TString formulaTStr = formula;
    formulaTStr.ReplaceAll("pow(x;", "pow(x,"); // Now revert back
    formula = formulaTStr.Data(); // reset
    TF1 f1("", formula.c_str()); // compile formula to check validity
    if (f1.IsZombie())
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "Invalid csv line; formula does not compile: " << csvLine << std::endl;
        throw std::exception();
    }

    // make parameters
    unsigned op;
    if (vec[0] == "L") op = 0;
    else if (vec[0] == "M") op = 1;
    else if (vec[0] == "T") op = 2;
    else op = 3;
    if (op > 3)
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "Invalid csv line; OperatingPoint is not 'L' or 'M' or 'T': " << csvLine << std::endl;
        throw std::exception();
    }
    unsigned jf = stoi(vec[3]);
    if (jf == 5) jf = 0;
    else if (jf == 4) jf = 1;
    else if (jf == 0) jf = 2;
    if (jf > 2)
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "Invalid csv line; JetFlavor > 2: " << csvLine << std::endl;
        throw std::exception();
    }
    params = BTagEntry_v2::Parameters(BTagEntry_v2::OperatingPoint(op), vec[1], vec[2], BTagEntry_v2::JetFlavor(jf), stof(vec[4]), stof(vec[5]), stof(vec[6]), stof(vec[7]), stof(vec[8]), stof(vec[9]));
}

BTagEntry_v2::BTagEntry_v2(const std::string &func, BTagEntry_v2::Parameters p) : formula(func), params(p)
{
    TF1 f1("", formula.c_str()); // compile formula to check validity
    if (f1.IsZombie())
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "Invalid func string; formula does not compile: " << func << std::endl;
        throw std::exception();
    }
}

BTagEntry_v2::BTagEntry_v2(const TF1 *func, BTagEntry_v2::Parameters p) : formula(std::string(func->GetExpFormula("p").Data())), params(p)
{
    if (func->IsZombie())
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "Invalid TF1 function; function is zombie: " << func->GetName() << std::endl;
        throw std::exception();
    }
}

// Creates chained step functions like this:
// "<prevous_bin> : x<bin_high_bound ? bin_value : <next_bin>"
// e.g. "x<0 ? 1 : x<1 ? 2 : x<2 ? 3 : 4"
std::string th1ToFormulaLin_v2(const TH1 *hist)
{
    int nbins = hist->GetNbinsX();
    TAxis const *axis = hist->GetXaxis();
    std::stringstream buff;
    buff << "x<" << axis->GetBinLowEdge(1) << " ? 0. : "; // default value
    for (int i = 1; i < nbins + 1; ++i)
    {
        char tmp_buff[50];
        sprintf(tmp_buff,
                "x<%g ? %g : ", // %g is the smaller one of %e or %f
                axis->GetBinUpEdge(i), hist->GetBinContent(i));
        buff << tmp_buff;
    }
    buff << 0.; // default value
    return buff.str();
}

// Creates step functions making a binary search tree:
// "x<mid_bin_bound ? (<left side tree>) : (<right side tree>)"
// e.g. "x<2 ? (x<1 ? (x<0 ? 0:0.1) : (1)) : (x<4 ? (x<3 ? 2:3) : (0))"
std::string th1ToFormulaBinTree_v2(const TH1 *hist, int start = 0, int end = -1)
{
    if (end == -1)
    { // initialize
        start = 0.;
        end = hist->GetNbinsX() + 1;
        TH1 *h2 = (TH1 *)hist->Clone();
        h2->SetBinContent(start, 0); // kill underflow
        h2->SetBinContent(end, 0);   // kill overflow
        std::string res = th1ToFormulaBinTree_v2(h2, start, end);
        delete h2;
        return res;
    }
    if (start == end)
    { // leave is reached
        char tmp_buff[20];
        sprintf(tmp_buff, "%g", hist->GetBinContent(start));
        return std::string(tmp_buff);
    }
    if (start == end - 1)
    { // no parenthesis for neighbors
        char tmp_buff[70];
        sprintf(tmp_buff, "x<%g ? %g:%g", hist->GetXaxis()->GetBinUpEdge(start), hist->GetBinContent(start), hist->GetBinContent(end));
        return std::string(tmp_buff);
    }

    // top-down recursion
    std::stringstream buff;
    int mid = (end - start) / 2 + start;
    char tmp_buff[25];
    sprintf(tmp_buff, "x<%g ? (", hist->GetXaxis()->GetBinUpEdge(mid));
    buff << tmp_buff << th1ToFormulaBinTree_v2(hist, start, mid) << ") : (" << th1ToFormulaBinTree_v2(hist, mid + 1, end) << ")";
    return buff.str();
}

BTagEntry_v2::BTagEntry_v2(const TH1 *hist, BTagEntry_v2::Parameters p) : params(p)
{
    int nbins = hist->GetNbinsX();
    TAxis const *axis = hist->GetXaxis();

    // overwrite bounds with histo values
    if (params.operatingPoint == BTagEntry_v2::OP_RESHAPING)
    {
        params.discrMin = axis->GetBinLowEdge(1);
        params.discrMax = axis->GetBinUpEdge(nbins);
    }
    else
    {
        params.ptMin = axis->GetBinLowEdge(1);
        params.ptMax = axis->GetBinUpEdge(nbins);
    }

    // balanced full binary tree height = ceil(log(2*n_leaves)/log(2))
    // breakes even around 10, but lower values are more propable in pt-spectrum
    if (nbins < 15)
    {
        formula = th1ToFormulaLin_v2(hist);
    }
    else
    {
        formula = th1ToFormulaBinTree_v2(hist);
    }

    // compile formula to check validity
    TF1 f1("", formula.c_str());
    if (f1.IsZombie())
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "Invalid histogram; formula does not compile (>150 bins?): " << hist->GetName() << std::endl;
        throw std::exception();
    }
}

std::string BTagEntry_v2::makeCSVHeader()
{
    return "OperatingPoint, "
           "measurementType, "
           "sysType, "
           "jetFlavor, "
           "etaMin, "
           "etaMax, "
           "ptMin, "
           "ptMax, "
           "discrMin, "
           "discrMax, "
           "formula \n";
}

std::string BTagEntry_v2::makeCSVLine() const
{
    std::stringstream buff;
    buff << params.operatingPoint << ", " << params.measurementType << ", " << params.sysType << ", " << params.jetFlavor << ", " << params.etaMin << ", " << params.etaMax << ", " << params.ptMin << ", " << params.ptMax << ", " << params.discrMin << ", " << params.discrMax << ", \"" << formula << "\" \n";
    return buff.str();
}

std::string BTagEntry_v2::trimStr(std::string str)
{
    size_t s = str.find_first_not_of(" \n\r\t");
    size_t e = str.find_last_not_of(" \n\r\t");

    if ((std::string::npos == s) || (std::string::npos == e))
        return "";
    else
        return str.substr(s, e - s + 1);
}

#include <fstream>
#include <sstream>

BTagCalibration_v2::BTagCalibration_v2(const std::string &taggr) : tagger_(taggr) {}

BTagCalibration_v2::BTagCalibration_v2(const std::string &taggr, const std::string &filename) : tagger_(taggr)
{
    std::ifstream ifs(filename);
    if (!ifs.good())
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "input file not available: " << filename << std::endl;
        throw std::exception();
    }
    readCSV(ifs);
    ifs.close();
}

void BTagCalibration_v2::addEntry(const BTagEntry_v2 &entry) { data_[token(entry.params)].push_back(entry); }

const std::vector<BTagEntry_v2> &BTagCalibration_v2::getEntries(const BTagEntry_v2::Parameters &par) const
{
    std::string tok = token(par);
    if (!data_.count(tok))
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "(OperatingPoint, measurementType, sysType) not available: " << tok << std::endl;
        throw std::exception();
    }
    return data_.at(tok);
}

void BTagCalibration_v2::readCSV(const std::string &s)
{
    std::stringstream buff(s);
    readCSV(buff);
}

void BTagCalibration_v2::readCSV(std::istream &s)
{
    std::string line;

    // firstline might be the header
    getline(s, line);
    if (line.find("OperatingPoint") == std::string::npos)
    {
        addEntry(BTagEntry_v2(line));
    }

    while (getline(s, line))
    {
        line = BTagEntry_v2::trimStr(line);
        if (line.empty())
        { // skip empty lines
            continue;
        }
        addEntry(BTagEntry_v2(line));
    }
}

void BTagCalibration_v2::makeCSV(std::ostream &s) const
{
    s << tagger_ << ";" << BTagEntry_v2::makeCSVHeader();
    for (std::map<std::string, std::vector<BTagEntry_v2>>::const_iterator i = data_.cbegin(); i != data_.cend(); ++i)
    {
        const std::vector<BTagEntry_v2> &vec = i->second;
        for (std::vector<BTagEntry_v2>::const_iterator j = vec.cbegin(); j != vec.cend(); ++j)
        {
            s << j->makeCSVLine();
        }
    }
}

std::string BTagCalibration_v2::makeCSV() const
{
    std::stringstream buff;
    makeCSV(buff);
    return buff.str();
}

std::string BTagCalibration_v2::token(const BTagEntry_v2::Parameters &par)
{
    std::stringstream buff;
    buff << par.operatingPoint << ", " << par.measurementType << ", " << par.sysType;
    return buff.str();
}

class BTagCalibrationReader_v2::BTagCalibrationReaderImpl_v2
{
    friend class BTagCalibrationReader_v2;

  public:
    struct TmpEntry
    {
        float etaMin;
        float etaMax;
        float ptMin;
        float ptMax;
        float discrMin;
        float discrMax;
        TF1 func;
    };

  private:
    BTagCalibrationReaderImpl_v2(BTagEntry_v2::OperatingPoint op, const std::string &sysType, const std::vector<std::string> &otherSysTypes = {});

    void load(const BTagCalibration_v2 &c, BTagEntry_v2::JetFlavor jf, std::string measurementType);

    double eval(BTagEntry_v2::JetFlavor jf, float eta, float pt, float discr) const;

    double eval_auto_bounds(const std::string &sys, BTagEntry_v2::JetFlavor jf, float eta, float pt, float discr) const;

    std::pair<float, float> min_max_pt(BTagEntry_v2::JetFlavor jf, float eta, float discr) const;

    BTagEntry_v2::OperatingPoint op_;
    std::string sysType_;
    std::vector<std::vector<TmpEntry>> tmpData_; // first index: jetFlavor
    std::vector<bool> useAbsEta_;                // first index: jetFlavor
    std::map<std::string, std::shared_ptr<BTagCalibrationReaderImpl_v2>> otherSysTypeReaders_;
};

BTagCalibrationReader_v2::BTagCalibrationReaderImpl_v2::BTagCalibrationReaderImpl_v2(BTagEntry_v2::OperatingPoint op, const std::string &sysType, const std::vector<std::string> &otherSysTypes) : op_(op), sysType_(sysType), tmpData_(3), useAbsEta_(3, true)
{
    for (const std::string &ost : otherSysTypes)
    {
        if (otherSysTypeReaders_.count(ost))
        {
            std::cerr << "ERROR in BTagCalibration_v2: "
                      << "Every otherSysType should only be given once. Duplicate: " << ost << std::endl;
            throw std::exception();
        }
        otherSysTypeReaders_[ost] = std::unique_ptr<BTagCalibrationReaderImpl_v2>(new BTagCalibrationReaderImpl_v2(op, ost));
    }
}

void BTagCalibrationReader_v2::BTagCalibrationReaderImpl_v2::load(const BTagCalibration_v2 &c, BTagEntry_v2::JetFlavor jf, std::string measurementType)
{
    if (tmpData_[jf].size())
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "Data for this jet-flavor is already loaded: " << jf << std::endl;
        throw std::exception();
    }

    BTagEntry_v2::Parameters params(op_, measurementType, sysType_);
    const std::vector<BTagEntry_v2> &entries = c.getEntries(params);

    for (const auto &be : entries)
    {
        if (be.params.jetFlavor != jf)
        {
            continue;
        }

        TmpEntry te;
        te.etaMin = be.params.etaMin;
        te.etaMax = be.params.etaMax;
        te.ptMin = be.params.ptMin;
        te.ptMax = be.params.ptMax;
        te.discrMin = be.params.discrMin;
        te.discrMax = be.params.discrMax;

        if (op_ == BTagEntry_v2::OP_RESHAPING)
        {
            te.func = TF1("", be.formula.c_str(), be.params.discrMin, be.params.discrMax);
        }
        else
        {
            te.func = TF1("", be.formula.c_str(), be.params.ptMin, be.params.ptMax);
        }

        tmpData_[be.params.jetFlavor].push_back(te);
        if (te.etaMin < 0)
        {
            useAbsEta_[be.params.jetFlavor] = false;
        }
    }

    for (auto &p : otherSysTypeReaders_)
    {
        p.second->load(c, jf, measurementType);
    }
}

double BTagCalibrationReader_v2::BTagCalibrationReaderImpl_v2::eval(BTagEntry_v2::JetFlavor jf, float eta, float pt, float discr) const
{
    bool use_discr = (op_ == BTagEntry_v2::OP_RESHAPING);
    if (useAbsEta_[jf] && eta < 0)
    {
        eta = -eta;
    }

    // search linearly through eta, pt and discr ranges and eval
    // future: find some clever data structure based on intervals
    const auto &entries = tmpData_.at(jf);

    // Added warning not in original BTV code if no entry for the requested jet flavor.
    // To match old SNT code, return dummy value 1.0 in this case.
    if (entries.size() == 0)
    {
        std::cout << "CORE/Tools/btagsf/BTagCalibrationReader_v2::eval(): WARNING: No scale factors found for jet flavor " << jf << ", returning dummy value 1.0 for consistency with legacy SNT btagsf code. Modern unmodified BTV code returns 0.0 in this case, so this may not be what you want/expect." << std::endl;
        return 1.0;
    }

    for (unsigned i = 0; i < entries.size(); ++i)
    {
        const auto &e = entries.at(i);
        if (e.etaMin <= eta && eta < e.etaMax // find eta
            && e.ptMin < pt && pt <= e.ptMax  // check pt
        )
        {
            if (use_discr)
            { // discr. reshaping?
                if (e.discrMin <= discr && discr < e.discrMax)
                { // check discr
                    return e.func.Eval(discr);
                }
            }
            else
            {
                return e.func.Eval(pt);
            }
        }
    }

    return 0.; // default value
}

double BTagCalibrationReader_v2::BTagCalibrationReaderImpl_v2::eval_auto_bounds(const std::string &sys, BTagEntry_v2::JetFlavor jf, float eta, float pt, float discr) const
{
    auto sf_bounds = min_max_pt(jf, eta, discr);
    float pt_for_eval = pt;
    bool is_out_of_bounds = false;

    if (pt < sf_bounds.first)
    {
        pt_for_eval = sf_bounds.first + .0001;
        is_out_of_bounds = true;
    }
    else if (pt > sf_bounds.second)
    {
        pt_for_eval = sf_bounds.second - .0001;
        is_out_of_bounds = true;
    }

    // get central SF (and maybe return)
    double sf = eval(jf, eta, pt_for_eval, discr);
    if (sys == sysType_)
    {
        return sf;
    }

    // get sys SF (and maybe return)
    if (!otherSysTypeReaders_.count(sys))
    {
        std::cerr << "ERROR in BTagCalibration_v2: "
                  << "sysType not available (maybe not loaded?): " << sys << std::endl;
        throw std::exception();
    }
    double sf_err = otherSysTypeReaders_.at(sys)->eval(jf, eta, pt_for_eval, discr);
    if (!is_out_of_bounds)
    {
        return sf_err;
    }

    // double uncertainty on out-of-bounds and return
    sf_err = sf + 2 * (sf_err - sf);
    return sf_err;
}

std::pair<float, float> BTagCalibrationReader_v2::BTagCalibrationReaderImpl_v2::min_max_pt(BTagEntry_v2::JetFlavor jf, float eta, float discr) const
{
    bool use_discr = (op_ == BTagEntry_v2::OP_RESHAPING);
    if (useAbsEta_[jf] && eta < 0)
    {
        eta = -eta;
    }

    const auto &entries = tmpData_.at(jf);
    float min_pt = -1., max_pt = -1.;
    for (const auto &e : entries)
    {
        if (e.etaMin <= eta && eta < e.etaMax // find eta
        )
        {
            if (min_pt < 0.)
            { // init
                min_pt = e.ptMin;
                max_pt = e.ptMax;
                continue;
            }

            if (use_discr)
            { // discr. reshaping?
                if (e.discrMin <= discr && discr < e.discrMax)
                { // check discr
                    min_pt = min_pt < e.ptMin ? min_pt : e.ptMin;
                    max_pt = max_pt > e.ptMax ? max_pt : e.ptMax;
                }
            }
            else
            {
                min_pt = min_pt < e.ptMin ? min_pt : e.ptMin;
                max_pt = max_pt > e.ptMax ? max_pt : e.ptMax;
            }
        }
    }

    return std::make_pair(min_pt, max_pt);
}

BTagCalibrationReader_v2::BTagCalibrationReader_v2(BTagEntry_v2::OperatingPoint op, const std::string &sysType, const std::vector<std::string> &otherSysTypes) : pimpl(new BTagCalibrationReaderImpl_v2(op, sysType, otherSysTypes)) {}

void BTagCalibrationReader_v2::load(const BTagCalibration_v2 &c, BTagEntry_v2::JetFlavor jf, const std::string &measurementType) { pimpl->load(c, jf, measurementType); }

double BTagCalibrationReader_v2::eval(BTagEntry_v2::JetFlavor jf, float eta, float pt, float discr) const { return pimpl->eval(jf, eta, pt, discr); }

double BTagCalibrationReader_v2::eval_auto_bounds(const std::string &sys, BTagEntry_v2::JetFlavor jf, float eta, float pt, float discr) const { return pimpl->eval_auto_bounds(sys, jf, eta, pt, discr); }

std::pair<float, float> BTagCalibrationReader_v2::min_max_pt(BTagEntry_v2::JetFlavor jf, float eta, float discr) const { return pimpl->min_max_pt(jf, eta, discr); }
