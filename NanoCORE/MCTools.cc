#include "MCTools.h"
#include "Math/VectorUtil.h"

vector<int> GenPart_leptDaughters(int i)
{
    vector<int> lept_daughters;
    for (unsigned int j = 0; j < nGenPart(); j++)
    {
        if (GenPart_genPartIdxMother().at(j) == i &&
            (abs(GenPart_pdgId().at(j)) >= 11 && abs(GenPart_pdgId().at(j)) <= 18))
        {
            lept_daughters.push_back(j);
        }
    }
    return lept_daughters;
}

vector<int> GenPart_daughters(int i)
{
    vector<int> daughters;
    for (unsigned int j = 0; j < nGenPart(); j++)
    {
        if (GenPart_genPartIdxMother().at(j) == i)
        {
            daughters.push_back(j);
        }
    }
    return daughters;
}

GenPart::GenPart(int idx)
{
    idx = idx;
    pdg_id = GenPart_pdgId().at(idx);
    is_last = (GenPart_statusFlags().at(idx) & (1 << 13)) == (1 << 13);
    is_fromHard = (GenPart_statusFlags().at(idx) & (1 << 8)) == (1 << 8);
    daughters = GenPart_daughters(idx);
    mother_idx = GenPart_genPartIdxMother().at(idx);
    status = GenPart_status().at(idx);
    pt = GenPart_pt().at(idx);
    eta = GenPart_eta().at(idx);
    phi = GenPart_phi().at(idx);
    mass = GenPart_mass().at(idx);
}

bool is_bad_copy(GenPart part)
{
    return (part.pdg_id == GenPart_pdgId().at(part.daughters[0]));
}

vector<GenPart> get_GenParticles()
{
    vector<GenPart> particles;
    for (unsigned int i = 0; i < nGenPart(); i++)
    {
        GenPart part(i);
        particles.push_back(part);
    }

    // Make Corrections for Bad Copies
    for (size_t i = 0; i < particles.size(); i++)
    {
        int m_id = particles.at(i).mother_idx;
        if (m_id >= 0)
        {
            if (is_bad_copy(particles.at(m_id)))
            {
                particles.at(i).mother_idx = particles.at(m_id).mother_idx;
                for (size_t j = 0; j < particles.at(m_id).daughters.size(); j++)
                {
                    particles.at(particles.at(m_id).mother_idx).daughters.push_back(
                        particles.at(m_id).daughters.at(j));
                }
            }
        }
    }
    return particles;
}

bool isFromBoson(int idx)
{
    int m_idx = GenPart_genPartIdxMother().at(idx);
    if (m_idx < 0)
    {
        return false;
    }
    else
    {
        if (abs(GenPart_pdgId().at(m_idx)) == 23 or abs(GenPart_pdgId().at(m_idx)) == 24 or abs(GenPart_pdgId().at(m_idx)) == 25)
            return true;
        else
            return isFromBoson(m_idx);
    }
}

bool isFromMassiveGaugeBoson(int idx)
{
    int m_idx = GenPart_genPartIdxMother().at(idx);
    if (m_idx < 0)
    {
        return false;
    }
    else
    {
        if (abs(GenPart_pdgId().at(m_idx)) == 23 or abs(GenPart_pdgId().at(m_idx)) == 24)
            return true;
        else
            return isFromMassiveGaugeBoson(m_idx);
    }
}

bool isEMuFromMassiveGaugeBoson(int idx)
{
    int m_idx = GenPart_genPartIdxMother().at(idx);
    int pdg_id = GenPart_pdgId().at(idx);

    if (not (abs(pdg_id) == 11 or abs(pdg_id) == 13))
        return false;

    if (m_idx < 0)
    {
        return false;
    }
    else
    {
        if (abs(GenPart_pdgId().at(m_idx)) == 23 or abs(GenPart_pdgId().at(m_idx)) == 24)
            return true;
        else
            return isEMuFromMassiveGaugeBoson(m_idx);
    }
}

bool isEMuFromTauFromMassiveGaugeBoson(int idx, int depth, bool foundTau)
{
    int m_idx = GenPart_genPartIdxMother().at(idx);
    int pdg_id = GenPart_pdgId().at(idx);
    if (depth == 0)
    {
        if (not (abs(pdg_id) == 11 or abs(pdg_id) == 13))
            return false;
    }
    else
    {
        if (not (abs(pdg_id) == 11 or abs(pdg_id) == 13 or abs(pdg_id) == 15))
            return false;
    }

    if (m_idx < 0)
    {
        return false;
    }
    else
    {
        int m_pdgid = GenPart_pdgId().at(m_idx);
        if ((abs(m_pdgid) == 23 or abs(m_pdgid) == 24) and foundTau)
        {
            return true;
        }
        else
        {
            bool motherIsTau = abs(m_pdgid) == 15 ? true : false;
            bool updateFoundTau = foundTau or motherIsTau;
            return isEMuFromTauFromMassiveGaugeBoson(m_idx, depth+1, updateFoundTau);
        }
    }
}

bool isHadronicTauFromMassiveGaugeBoson(int idx)
{
    int pdg_id = GenPart_pdgId().at(idx);
    std::vector<int> daughter_idxs = GenPart_daughters(idx);

    if (abs(pdg_id) != 15)
        return false;

    bool is_leptonic_decay = false;
    bool tau_decayed = false;
    for (auto& daughter_idx : daughter_idxs)
    {
        int daughter_pdg_id = GenPart_pdgId().at(daughter_idx);
        if (abs(daughter_pdg_id) == 11 or abs(daughter_pdg_id) == 13)
        {
            is_leptonic_decay = true;
        }
        if (abs(daughter_pdg_id) == 16)
        {
            tau_decayed = true;
        }
    }

    bool is_hadronic_tau = (tau_decayed and not is_leptonic_decay);

    if (is_hadronic_tau)
        return isFromMassiveGaugeBoson(idx);
    else
        return false;

}

int idxOfMassiveGaugeBosonAncestor(int idx)
{
    int m_idx = GenPart_genPartIdxMother().at(idx);
    if (m_idx < 0)
    {
        return -1;
    }
    else
    {
        if (abs(GenPart_pdgId().at(m_idx)) == 23 or abs(GenPart_pdgId().at(m_idx)) == 24)
            return m_idx;
        else
            return idxOfMassiveGaugeBosonAncestor(m_idx);
    }
}

void dumpGenParticleInfos(std::vector<int> filter_pdgid)
{
    dumpGenParticleInfoHeader();
    for (unsigned int idx = 0; idx < GenPart_pdgId().size(); ++idx)
    {
        int pdg_id = GenPart_pdgId().at(idx);
        if (filter_pdgid.size() != 0)
            if (std::find(filter_pdgid.begin(), filter_pdgid.end(), pdg_id) == filter_pdgid.end())
                continue;
        dumpGenParticleInfo(idx);
    }
}

void dumpGenParticleInfoHeader()
{
    // Header
    cout << "                  " << "   pt    " << "  phi  " << "      eta   " << "    mass  " << "status " << "Mother_idx  " << "Mother  " << "boson_lep  " << endl;
    cout << "-------------------------------------------------------------------------------" << endl;
}

void dumpGenParticleInfo(int idx)
{
    TDatabasePDG pdg;
    int pdg_id = GenPart_pdgId().at(idx);
    // int is_last = (GenPart_statusFlags().at(idx) & (1 << 13)) == (1 << 13);
    // int is_fromHard = (GenPart_statusFlags().at(idx) & (1 << 8)) == (1 << 8);
    std::vector<int> daughters = GenPart_daughters(idx);
    int m_index = GenPart_genPartIdxMother().at(idx);
    int status = GenPart_status().at(idx);
    float pt = GenPart_pt().at(idx);
    float eta = GenPart_eta().at(idx);
    float phi = GenPart_phi().at(idx);
    float mass = GenPart_mass().at(idx);
    bool is_from_boson = isEMuFromTauFromMassiveGaugeBoson(idx) or isEMuFromMassiveGaugeBoson(idx);
    const char* particle = (abs(pdg_id) == 4124) ? "Lambda_c*" : pdg.GetParticle(pdg_id)->GetName();
    const char* mother_particle = m_index < 0 ? "-" : (abs(GenPart_pdgId().at(m_index)) == 4124) ? "Lambda_c*" : pdg.GetParticle(GenPart_pdgId().at(m_index))->GetName();
    cout << setw(4)  << left  <<                    idx                      << " "
        << setw(10) << left  <<                    particle                 << " "
        << setw(7)  << right << setprecision(4) << pt                       << "  "
        << setw(7)  << right << setprecision(4) << phi                      << "  "
        << setw(10) << right << setprecision(4) << eta                      << "  "
        << setw(10) << right << setprecision(4) << mass                     << "  "
        << setw(4)  << right <<                    status                   << "  "
        << setw(10) << left  <<                    m_index                  << " "
        << setw(10) << left  <<                    mother_particle          << " "
        << setw(13) << left  <<                    is_from_boson            << ", daughters = ";
    for (auto& daughter : daughters)
    {
        cout << setw(10) << left << ((abs(GenPart_pdgId().at(daughter)) == 4124) ? "Lambda_c*" : pdg.GetParticle(GenPart_pdgId().at(daughter))->GetName()) << " ";
    }
    cout << endl;
}

int dumpDocLines()
{
    // Particle Database
    TDatabasePDG *pdg = new TDatabasePDG();
    vector<GenPart> genParticles = get_GenParticles();

    // Header
    cout << "                  " << "   pt    " << "  phi  " << "      eta   " << "    mass  " << "status " << "Mother_idx  " << "Mother  " << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    // Loop over Gen Particles
    for (unsigned int j = 0; j < genParticles.size(); j++) {
        int m_index = genParticles[j].mother_idx;
        // Mass
        float mass = genParticles[j].mass != 0 ? genParticles[j].mass : pdg->GetParticle(genParticles[j].pdg_id)->Mass();
        //Print information about the jth gen particle
        const char* particle = (abs(genParticles[j].pdg_id) == 4124) ? "Lambda_c*" : pdg->GetParticle(genParticles[j].pdg_id)->GetName();
        const char* mother_particle = m_index < 0 ? "-" : (abs(genParticles[m_index].pdg_id) == 4124) ? "Lambda_c*" : pdg->GetParticle(genParticles[m_index].pdg_id)->GetName();
        cout << setw(4)  << left  <<                    j                        << " "
             << setw(10) << left  <<                    particle                 << " "
             << setw(7)  << right << setprecision(4) << genParticles[j].pt       << "  "
             << setw(7)  << right << setprecision(4) << genParticles[j].phi      << "  "
             << setw(10) << right << setprecision(4) << genParticles[j].eta      << "  "
             << setw(10) << right << setprecision(4) << mass                     << "  "
             << setw(4)  << right <<                    genParticles[j].status   << "  "
             << setw(10) << left  <<                    m_index                  << " "
             << setw(10) << left  <<                    mother_particle          << " "
             << endl;
    }
    delete pdg;
    return 0;
}

bool isFromSUSY(int id, int idx) {
    vector<GenPart> genParticles = get_GenParticles();
    int mc_id = 0, mc_motherid = 0, mc_motheridx = 0, mc_grandmaid = 0;
    if (abs(id) == 11 || abs(id) == 13) {
        mc_id = genParticles[idx].pdg_id;
        mc_motherid = genParticles[genParticles[idx].mother_idx].pdg_id;
        mc_motheridx = genParticles[idx].mother_idx;
    }
    mc_grandmaid = mc_motheridx < 0 ? -1 : genParticles[mc_motheridx].mother_idx;

    // For Leptons
    if ((abs(mc_id) == 11 || abs(mc_id) == 13)) {
        if (abs(mc_motherid) == 1000024) {return true;}
        if (abs(mc_motherid) == 15 && abs(mc_grandmaid) == 1000024) {return true;}
        return false;
    }
    return false;
}

bool isFromW(int id, int idx) {
    vector<GenPart> genParticles = get_GenParticles();
    int mc_id = 0, mc_motherid = 0, mc_motheridx = 0, mc_grandmaid = 0;
    if (abs(id) == 11 || abs(id) == 13) {
        mc_id = genParticles[idx].pdg_id;
        mc_motherid = genParticles[genParticles[idx].mother_idx].pdg_id;
        mc_motheridx = genParticles[idx].mother_idx;
    }
    mc_grandmaid = mc_motheridx < 0 ? -1 : genParticles[mc_motheridx].mother_idx;

    // For Leptons
    if ((abs(mc_id) == 11 || abs(mc_id) == 13)) {
        if (abs(mc_motherid) == 24) {return true;}
        if (abs(mc_motherid) == 15 && abs(mc_grandmaid) == 24) {return true;}
        return false;
    }
    // For Photons
    if (abs(mc_id) == 22) {
        if (abs(mc_motherid) != abs(id)) {return false;}
        if (abs(mc_motherid) != 24) {return false;}
        return true;
    }
    // everything else
    return false;
}

bool isFromZ(int id, int idx) {
    vector<GenPart> genParticles = get_GenParticles();
    int mc_id = 0, mc_motherid = 0, mc_motheridx = 0, mc_grandmaid = 0;
    if (abs(id) == 11 || abs(id) == 13) {
        mc_id = genParticles[idx].pdg_id;
        mc_motherid = genParticles[genParticles[idx].mother_idx].pdg_id;
        mc_motheridx = genParticles[idx].mother_idx;
    }
    mc_grandmaid = mc_motheridx < 0 ? -1 : genParticles[mc_motheridx].mother_idx;

    // For Leptons
    if ((abs(mc_id) == 11 || abs(mc_id) == 13)) {
        if (abs(mc_motherid) == 23) {return true;}
        if (abs(mc_motherid) == 15 && abs(mc_grandmaid) == 23) {return true;}
        return false;
    }

    // For Photons
    if (abs(mc_id) == 22) {
        if (abs(mc_motherid) != abs(id)) {return false;}
        if (abs(mc_motherid) != 23) {return false;}
        return true;
    }

    // For everything else
    return false;
}

bool isFromTau(int id, int idx) {
    vector<GenPart> genParticles = get_GenParticles();
    int mc_id = 0, mc_motherid = 0, mc_motheridx = 0, mc_grandmaid = 0;
    if (abs(id) == 11 || abs(id) == 13) {
        mc_id = genParticles[idx].pdg_id;
        mc_motherid = genParticles[genParticles[idx].mother_idx].pdg_id;
        mc_motheridx = genParticles[idx].mother_idx;
    }
    mc_grandmaid = mc_motheridx < 0 ? -1 : genParticles[mc_motheridx].mother_idx;

    // For Leptons
    if ((abs(mc_id) == 11 || abs(mc_id) == 13)) {
        if (abs(mc_motherid) == 15 && abs(mc_grandmaid) == 24) {return true;}
        if (abs(mc_motherid) == 15 && abs(mc_grandmaid) == 23) {return true;}
        return false;
    }

    // everything else
    return false;
}

bool isFromB(int id, int idx) {
    vector<GenPart> genParticles = get_GenParticles();
    int mc_id = 0, mc_motherid = 0;
    if (abs(id) == 11 || abs(id) == 13) {
        mc_id = genParticles[idx].pdg_id;
        mc_motherid = genParticles[genParticles[idx].mother_idx].pdg_id;
    }
    return (abs(mc_id) == 11 || abs(mc_id) == 13) && idIsBeauty(mc_motherid);
}

bool isFromC(int id, int idx) {
    vector<GenPart> genParticles = get_GenParticles();
    int mc_id = 0, mc_motherid = 0;
    if (abs(id) == 11 || abs(id) == 13) {
        mc_id = genParticles[idx].pdg_id;
        mc_motherid = genParticles[genParticles[idx].mother_idx].pdg_id;
    }
    return (abs(mc_id) == 11 || abs(mc_id) == 13) && idIsCharm(mc_motherid);
}

bool isFromLight(int id, int idx) {
    vector<GenPart> genParticles = get_GenParticles();
    int mc_id = 0, mc_motherid = 0;
    if (abs(id) == 11 || abs(id) == 13) {
        mc_id = genParticles[idx].pdg_id;
        mc_motherid = genParticles[genParticles[idx].mother_idx].pdg_id;
    }
    if (abs(mc_id) != 11 && abs(mc_id) != 13) {return false;}
    if (abs(mc_motherid) > 200 && abs(mc_motherid) < 400) {return true;}
    if (abs(mc_motherid) > 0 && abs(mc_motherid) < 4) {return true;}
    return false;
}

bool isFromLightFake(int id, int idx) {
    vector<GenPart> genParticles = get_GenParticles();
    int mc_id = 0, mc_motherid = 0;
    if (abs(id) == 11 || abs(id) == 13) {
        mc_id = genParticles[idx].pdg_id;
        mc_motherid = genParticles[genParticles[idx].mother_idx].pdg_id;
    }
    // True if light hadron
    if (abs(mc_id) > 200 && abs(mc_id) < 400) {return true;}

    // True if non-quark whose mother is light hadron
    if (abs(mc_id) == 11) {return false;}
    if (abs(mc_id) == 13) {return false;}
    if (abs(mc_motherid) > 200 && abs(mc_motherid) < 400) {return true;}
    if (abs(mc_motherid) > 0 && abs(mc_motherid) < 4) {return true;}

    return false;
}

bool idIsCharm(int id) {
    id = abs(id);
    if (id == 4) {return true;}
    if (id == 411) {return true;}
    if (id == 421) {return true;}
    if (id == 10411) {return true;}
    if (id == 10421) {return true;}
    if (id == 413) {return true;}
    if (id == 423) {return true;}
    if (id == 10413) {return true;}
    if (id == 10423) {return true;}
    if (id == 20413) {return true;}
    if (id == 20423) {return true;}
    if (id == 415) {return true;}
    if (id == 425) {return true;}
    if (id == 431) {return true;}
    if (id == 10431) {return true;}
    if (id == 433) {return true;}
    if (id == 10433) {return true;}
    if (id == 20433) {return true;}
    if (id == 435) {return true;}
    if (id == 441) {return true;}
    if (id == 10441) {return true;}
    if (id == 100441) {return true;}
    if (id == 443) {return true;}
    if (id == 10443) {return true;}
    if (id == 20443) {return true;}
    if (id == 100443) {return true;}
    if (id == 30443) {return true;}
    if (id == 9000443) {return true;}
    if (id == 9010443) {return true;}
    if (id == 9020443) {return true;}
    if (id == 445) {return true;}
    if (id == 9000445) {return true;}
    if (id == 4122) {return true;}
    if (id == 4222) {return true;}
    if (id == 4212) {return true;}
    if (id == 4112) {return true;}
    if (id == 4224) {return true;}
    if (id == 4214) {return true;}
    if (id == 4114) {return true;}
    if (id == 4232) {return true;}
    if (id == 4132) {return true;}
    if (id == 4322) {return true;}
    if (id == 4312) {return true;}
    if (id == 4324) {return true;}
    if (id == 4314) {return true;}
    if (id == 4332) {return true;}
    if (id == 4334) {return true;}
    if (id == 4412) {return true;}
    if (id == 4422) {return true;}
    if (id == 4414) {return true;}
    if (id == 4424) {return true;}
    if (id == 4432) {return true;}
    if (id == 4434) {return true;}
    if (id == 4444) {return true;}
    return false;
}

bool idIsBeauty(int id) {
    id = abs(id);
    if (id == 5) {return true;}
    if (id == 511) {return true;}
    if (id == 521) {return true;}
    if (id == 10511) {return true;}
    if (id == 10521) {return true;}
    if (id == 513) {return true;}
    if (id == 523) {return true;}
    if (id == 10513) {return true;}
    if (id == 10523) {return true;}
    if (id == 20513) {return true;}
    if (id == 20523) {return true;}
    if (id == 515) {return true;}
    if (id == 525) {return true;}
    if (id == 531) {return true;}
    if (id == 10531) {return true;}
    if (id == 533) {return true;}
    if (id == 10533) {return true;}
    if (id == 20533) {return true;}
    if (id == 535) {return true;}
    if (id == 541) {return true;}
    if (id == 10541) {return true;}
    if (id == 543) {return true;}
    if (id == 10543) {return true;}
    if (id == 20543) {return true;}
    if (id == 545) {return true;}
    if (id == 551) {return true;}
    if (id == 10551) {return true;}
    if (id == 100551) {return true;}
    if (id == 110551) {return true;}
    if (id == 200551) {return true;}
    if (id == 210551) {return true;}
    if (id == 553) {return true;}
    if (id == 10553) {return true;}
    if (id == 20553) {return true;}
    if (id == 30553) {return true;}
    if (id == 100553) {return true;}
    if (id == 110553) {return true;}
    if (id == 120553) {return true;}
    if (id == 130553) {return true;}
    if (id == 200553) {return true;}
    if (id == 210553) {return true;}
    if (id == 220553) {return true;}
    if (id == 300553) {return true;}
    if (id == 900055) {return true;}
    if (id == 901055) {return true;}
    if (id == 555) {return true;}
    if (id == 10555) {return true;}
    if (id == 20555) {return true;}
    if (id == 100555) {return true;}
    if (id == 110555) {return true;}
    if (id == 120555) {return true;}
    if (id == 200555) {return true;}
    if (id == 557) {return true;}
    if (id == 100557) {return true;}
    if (id == 5122) {return true;}
    if (id == 5112) {return true;}
    if (id == 5212) {return true;}
    if (id == 5222) {return true;}
    if (id == 5114) {return true;}
    if (id == 5214) {return true;}
    if (id == 5224) {return true;}
    if (id == 5132) {return true;}
    if (id == 5232) {return true;}
    if (id == 5312) {return true;}
    if (id == 5322) {return true;}
    if (id == 5314) {return true;}
    if (id == 5324) {return true;}
    if (id == 5332) {return true;}
    if (id == 5334) {return true;}
    if (id == 5142) {return true;}
    if (id == 5242) {return true;}
    if (id == 5412) {return true;}
    if (id == 5422) {return true;}
    if (id == 5414) {return true;}
    if (id == 5424) {return true;}
    if (id == 5342) {return true;}
    if (id == 5432) {return true;}
    if (id == 5434) {return true;}
    if (id == 5442) {return true;}
    if (id == 5444) {return true;}
    if (id == 5512) {return true;}
    if (id == 5522) {return true;}
    if (id == 5514) {return true;}
    if (id == 5524) {return true;}
    if (id == 5532) {return true;}
    if (id == 5534) {return true;}
    if (id == 5542) {return true;}
    if (id == 5544) {return true;}
    if (id == 5554) {return true;}
    return false;
}

//________________________________________________________________

int getSourceId(int genpIdx) {

    // look for earliest mother that is: top, W, Z, or H
    // terminate search if top or H is found
    // continue if W, Z is found, to see if there's a top or H
    // can also add SUSY particles to logic, not yet done
    vector<GenPart> genParticles = get_GenParticles();
    int currentIdx = genpIdx;
    int motherIdx = genParticles[currentIdx].mother_idx;
    int motherId = genParticles[motherIdx].pdg_id;
    int sourceId = -1;
    if (useSourceId(motherId)) sourceId = motherId;
    while ((currentIdx >= 0) && (motherIdx >= 0) && !terminateSourceId(sourceId) && !terminateMotherId(motherId)) {
        currentIdx = motherIdx;
        motherIdx = genParticles[currentIdx].mother_idx;
        motherId = abs(genParticles[currentIdx].pdg_id);
        if (useSourceId(motherId)) sourceId = motherId;
    }
    return sourceId;
}

//________________________________________________________________
// list of sourceIds to terminate search on
//   can add susy particles here
bool terminateSourceId(int sourceId) {
    int id = abs(sourceId);
    if (id == 6 || id == 25) {return true;}
    return false;
}

//________________________________________________________________
// list of sourceIds to allow
//   top, Z, W, H
//   can add susy particles here
bool useSourceId(int motherId) {
    int id = abs(motherId);
    if (id == 6 || (id >= 23 && id <= 25)) {return true;}
    return false;
}

//________________________________________________________________
// list of mother PdgIds to terminate search on
//   quarks, gluons, hadrons
bool terminateMotherId(int motherId) {
    int id = abs(motherId);
    if (id <= 5 || id == 21 || (id > 100 && id < 1000000)) {return true;}
    return false;
}

//________________________________________________________________
// top pt reweighting from the TOP PAG
//  https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
//  using the 13 TeV "All Combined" weights
float topPtWeight(float pt_top, float pt_tbar) {
    if (pt_top < 0. || pt_tbar < 0.) return 1.;
    float weight_top = exp(0.0615 - 0.0005 * pt_top);
    float weight_tbar = exp(0.0615 - 0.0005 * pt_tbar);
    return sqrt(weight_top * weight_tbar);
}

//________________________________________________________________
// top pt reweighting from the TOP PAG
//  https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
//  using the 13 TeV "All Combined" weights
//  adding the recommendation to cutoff the reweighting at pt of 400
float topPtWeightCutoff(float pt_top, float pt_tbar) {
    if (pt_top < 0. || pt_tbar < 0.) return 1.;
    float pt_top_cutoff = min(pt_top, float(400.));
    float pt_tbar_cutoff = min(pt_tbar, float(400.));
    float weight_top = exp(0.0615 - 0.0005 * pt_top_cutoff);
    float weight_tbar = exp(0.0615 - 0.0005 * pt_tbar_cutoff);
    return sqrt(weight_top * weight_tbar);
}

//________________________________________________________________
// code to get number of reco jets matched to ISR jets
// inputs are jets with pt > 30, |eta| < 2.4, PF Loose ID, leptons removed
// https://github.com/manuelfs/babymaker/blob/0136340602ee28caab14e3f6b064d1db81544a0a/bmaker/plugins/bmaker_full.cc#L1268-L1295

int getNISRMatch(const vector<LorentzVector> &clean_jets) {
    int nisr(0);
    vector<GenPart> genParticles = get_GenParticles();
    for (size_t ijet(0); ijet < clean_jets.size(); ijet++) {
        if (clean_jets.at(ijet).pt() < 30.0) continue;
        if (fabs(clean_jets.at(ijet).eta()) > 2.4) continue;
        bool matched = false;
        for (size_t imc = 0; imc < nGenPart(); imc++) {
            if (matched) break;
            if (genParticles[imc].status != 23 || abs(genParticles[imc].pdg_id) > 5) continue;
            int momid = abs(genParticles[genParticles[imc].mother_idx].pdg_id);
            if (!(momid == 6 || momid == 23 || momid == 24 || momid == 25 || momid > 1e6)) continue;
            // check against daughter in case of hard initial splitting
            // - since we don't save daughters, only mothers, we do a double loop here...
            for (size_t jmc = 0; jmc < nGenPart(); jmc++) {
                if (genParticles[jmc].mother_idx != int(imc)) continue;
                if (genParticles[jmc].mass <= 0) continue;
                float dR = ROOT::Math::VectorUtil::DeltaR(clean_jets.at(ijet), GenPart_p4().at(jmc));
                if (dR < 0.3) {
                    matched = true;
                    break;
                }
            }
        }
        if (!matched) { nisr++; }
    }
    return nisr;
}

//________________________________________________________________
// returns year dependent ISR weight based on nisrMatch
float getISRWeight(int nisrMatch, int year) {
    if (year >= 2016) {
        // Moriond 2017 values for ISR weight based on nisrMatch
        if (nisrMatch == 0)
            return 1.000;
        else if (nisrMatch == 1)
            return 0.920;
        else if (nisrMatch == 2)
            return 0.821;
        else if (nisrMatch == 3)
            return 0.715;
        else if (nisrMatch == 4)
            return 0.662;
        else if (nisrMatch == 5)
            return 0.561;
        else if (nisrMatch >= 6)
            return 0.511;
    }
    return 1.;
}

//________________________________________________________________
// returns year dependent ISR weight uncertainty based on nisrMatch
float getISRUncertainty(int nisrMatch, int year) {
    if (year >= 2016) {
        // Moriond 2017 values
        if (nisrMatch == 0)
            return 0.000;
        else if (nisrMatch == 1)
            return 0.040;
        else if (nisrMatch == 2)
            return 0.090;
        else if (nisrMatch == 3)
            return 0.143;
        else if (nisrMatch == 4)
            return 0.170;
        else if (nisrMatch == 5)
            return 0.221;
        else if (nisrMatch >= 6)
            return 0.258;
    }
    return 0.;
}

//________________________________________________________________
// returns 2016 ICHEP ISR weight based on nisrMatch
// s13 of
// https://indico.cern.ch/event/557678/contributions/2247944/attachments/1311994/1963568/16-07-19_ana_manuelf_isr.pdf
float getISRWeight(int nisrMatch) {
    if (nisrMatch == 0)
        return 1.;
    else if (nisrMatch == 1)
        return 0.882;
    else if (nisrMatch == 2)
        return 0.792;
    else if (nisrMatch == 3)
        return 0.702;
    else if (nisrMatch == 4)
        return 0.648;
    else if (nisrMatch == 5)
        return 0.601;
    else if (nisrMatch >= 6)
        return 0.515;

    // shouldn't get here
    std::cout << "ERROR: get_isrWeight: bad input for nisrMatch: " << nisrMatch << std::endl;
    return 1.;
}

//________________________________________________________________
// returns 2016 ICHEP ISR weight uncertainty based on nisrMatch
// s13 of
// https://indico.cern.ch/event/557678/contributions/2247944/attachments/1311994/1963568/16-07-19_ana_manuelf_isr.pdf
float getISRUncertainty(int nisrMatch) {
    if (nisrMatch == 0)
        return 0.;
    else if (nisrMatch == 1)
        return 0.059;
    else if (nisrMatch == 2)
        return 0.104;
    else if (nisrMatch == 3)
        return 0.149;
    else if (nisrMatch == 4)
        return 0.176;
    else if (nisrMatch == 5)
        return 0.199;
    else if (nisrMatch >= 6)
        return 0.242;

    // shouldn't get here
    std::cout << "ERROR: get_isrUnc: bad input for nisrMatch: " << nisrMatch << std::endl;
    return 0.;
}

//________________________________________________________________
// returns 2017 Moriond ISR weight based on ISR pt, for ewkino models
// s6 of https://www.dropbox.com/s/rv79odbk1plltm1/17-02-22_ana_isr_ewk.pdf?dl=1 (link to be updated once in a more
// permanent place)
float getISRWeightEWkino(float isr_pt) {

    if (isr_pt < 50.)
        return 1.000;
    else if (isr_pt < 100.)
        return 1.052;
    else if (isr_pt < 150.)
        return 1.179;
    else if (isr_pt < 200.)
        return 1.150;
    else if (isr_pt < 300.)
        return 1.057;
    else if (isr_pt < 400.)
        return 1.000;
    else if (isr_pt < 600.)
        return 0.912;
    else
        return 0.783;
    // shouldn't get here
    std::cout << "ERROR: get_isrWeight_ewk: bad input for isr_pt: " << isr_pt << std::endl;
    return 1.;
}
