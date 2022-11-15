import ROOT

def GetLastBin(h, xmax=None):
    nb = h.GetNbinsX()
    if xmax!=None:
        lastbin=1
        while h.GetXaxis().GetBinUpEdge(lastbin) <= xmax and lastbin<nb+1:
            lastbin += 1
        lastbin -= 1
    else:
        lastbin = nb
    return lastbin

def GetFirstBin(h, xmin=None):
    nb = h.GetNbinsX()
    if xmin!=None:
        firstbin=1
        while h.GetXaxis().GetBinUpEdge(firstbin) <= xmin and firstbin<nb+1:
            firstbin += 1
        if firstbin == nb+1:
            raise Exception("ERROR [pyRootPlotMaker]: xmin is out of histogram range!")
    else:
        firstbin=1
    return firstbin

def GetBinWidth(h):
    width = h.GetBinWidth(1)
    for i in range(2,h.GetNbinsX()+1):
        if h.GetBinWidth(i) != width:
            return None
    return width

def PutOverflowInLastBin(h, xmax=None):

    nb = h.GetNbinsX()
    lastbin = GetLastBin(h,xmax)

    bc_new = h.Integral(lastbin,nb+1)
    be_new = ROOT.TMath.Sqrt(sum([h.GetBinError(i)**2 for i in range(lastbin,nb+2)]))
    
    h.SetBinContent(lastbin,bc_new)
    h.SetBinError(lastbin,be_new)

    for i in range(lastbin+1,nb+2):
        h.SetBinContent(i,0)
        h.SetBinError(i,0)

def PutUnderflowInFirstBin(h, xmin=None):

    firstbin = GetFirstBin(h,xmin)

    bc_new = h.Integral(0,firstbin)
    be_new = ROOT.TMath.Sqrt(sum([h.GetBinError(i)**2 for i in range(0,firstbin+1)]))
    
    h.SetBinContent(firstbin,bc_new)
    h.SetBinError(firstbin,be_new)

    for i in range(0,firstbin):
        h.SetBinContent(i,0)
        h.SetBinError(i,0)

def GetUnderOverHist(f, hname, rename=None, color=None, linewidth=3, under=True, over=True, norm=False):
    hbase = f.Get(hname)
    if hbase == None:
        raise Exception("ERROR [pyRootPlotMaker]: {0} not found in {1}".format(hname,f.GetTitle()))
    h = hbase.Clone(hbase.GetName() + "_UnderOver")
    if rename != None:
        h.SetTitle(rename)
    if color != None:
        h.SetLineColor(color)
    h.SetLineWidth(linewidth)
    if (under):
        PutUnderflowInFirstBin(h)
    if (over):
        PutOverflowInLastBin(h)
    if (norm):
        h.Scale(1.0 / h.Integral())
    return h

def SetYBounds(stack, isLog, h_bkg_vec, data_max, xRangeUser):
    xmin = None if xRangeUser==None else xRangeUser[0]
    xmax = None if xRangeUser==None else xRangeUser[1]
    firstbin = GetFirstBin(h_bkg_vec[0], xmin)
    lastbin = GetLastBin(h_bkg_vec[0], xmax)
    tmax = 0
    tmin = float("inf")
    for i in range(firstbin,lastbin+1):
        c = sum([h.GetBinContent(i) for h in h_bkg_vec])
        e = ROOT.TMath.Sqrt(sum([h.GetBinError(i)**2 for h in h_bkg_vec]))
        if c+e > tmax:
            tmax = c+e
        if c < tmin:
            tmin = c

    tmax = max(tmax,data_max)
    if isLog:
        if tmin>0:
            tmin = max(0.1, 0.5*tmin)
        else:
            tmin = 0.1
        stack.SetMinimum(tmin)
        stack.SetMaximum(tmax**(1.0/0.69))
    else:
        stack.SetMaximum(tmax*1.33)

def ConvertToPoissonGraph(h_data, graph, drawZeros=True, drawXerr=True, drawYerr=True):

    alpha = 1-0.6827

    for i in range(1,h_data.GetNbinsX()+1):
        x = h_data.GetBinCenter(i)
        xerr = h_data.GetBinWidth(i)/2 if drawXerr else 0.0
        y = h_data.GetBinContent(i) if drawYerr else 0.0

        if y < 0:
            continue
        
        if y==0 and not drawZeros:
            continue

        ym = 0 if y==0 else ROOT.Math.gamma_quantile(alpha/2, y, 1)
        yp = ROOT.Math.gamma_quantile_c(alpha/2, y+1, 1)
        
        yerrplus = yp-y
        yerrminus = y-ym

        thisPoint = graph.GetN()
        graph.SetPoint(thisPoint, x, y)
        graph.SetPointError(thisPoint, xerr, xerr, yerrminus, yerrplus)

def GetPoissonRatioGraph(h_mc, h_data, g_ratio, drawZeros=True, drawXerr=True, drawYerr=True, useMCErr=True):

    alpha = 1-0.6827

    for i in range(1,h_mc.GetNbinsX()+1):
        x = h_mc.GetBinCenter(i)
        mcy = h_mc.GetBinContent(i)
        datay = h_data.GetBinContent(i)

        if mcy==0 or (datay==0 and not drawZeros):
            continue

        mcerr = h_mc.GetBinError(i)
        if not useMCErr:
            mcerr = 0
        dataerrup = ROOT.Math.gamma_quantile_c(alpha/2, datay+1, 1) - datay
        dataerrdown = 0 if datay==0 else (datay-ROOT.Math.gamma_quantile(alpha/2, datay, 1))

        r = datay/mcy
        rerrup = ROOT.TMath.Sqrt((dataerrup/mcy)**2 + (mcerr*datay/mcy**2)**2) if drawYerr else 0.0
        rerrdown = ROOT.TMath.Sqrt((dataerrdown/mcy)**2 + (mcerr*datay/mcy**2)**2) if drawYerr else 0.0

        xerr = h_mc.GetBinWidth(i)/2 if drawXerr else 0.0

        thisPoint = g_ratio.GetN()
        g_ratio.SetPoint(thisPoint, x, r)
        g_ratio.SetPointError(thisPoint, xerr, xerr, rerrdown, rerrup)

def GetPullGraph(h_mc, h_data, g_ratio, drawZeros=True, drawXerr=True, drawYerr=True, useMCErr=True):

    alpha = 1-0.6827

    for i in range(1,h_mc.GetNbinsX()+1):
        x = h_mc.GetBinCenter(i)
        mcy = h_mc.GetBinContent(i)
        datay = h_data.GetBinContent(i)

        if mcy==0 or (datay==0 and not drawZeros):
            continue

        mcerr = h_mc.GetBinError(i)
        if not useMCErr:
            mcerr = 0
        dataerrup = ROOT.Math.gamma_quantile_c(alpha/2, datay+1, 1) - datay
        dataerrdown = 0 if datay==0 else (datay-ROOT.Math.gamma_quantile(alpha/2, datay, 1))

        dataerr = dataerrdown
        if datay<mcy:
            dataerr = dataerrup
        r = (datay-mcy)/dataerr

        xerr = h_mc.GetBinWidth(i)/2 if drawXerr else 0.0

        thisPoint = g_ratio.GetN()
        g_ratio.SetPoint(thisPoint, x, r)
        g_ratio.SetPointError(thisPoint, xerr, xerr, 0.0, 0.0)

def GetEfficRatioGraph(hnum, hden, g_ratio):
    level = 0.6827
    for i in range(1, hnum.GetNbinsX()+1):
        x = hnum.GetBinCenter(i)
        xerr = hnum.GetBinWidth(i) / 2.0
        num = hnum.GetBinContent(i)
        den = hden.GetBinContent(i)
        if den > 0:
            val = float(num)/den
            errup = ROOT.TEfficiency.ClopperPearson(den, num, level, 1) - val
            errdn = val - ROOT.TEfficiency.ClopperPearson(den, num, level, 0)
            thisPoint = g_ratio.GetN()
            g_ratio.SetPoint(thisPoint, x, val)
            g_ratio.SetPointError(thisPoint, xerr, xerr, errdn, errup)

def GetCumulative(h,lowToHighBinsCumulative=True):
    hout = h.Clone()
    sumOfBins = 0
    sumOfBinsError = 0
    if lowToHighBinsCumulative:
        for i in range(1, h.GetNbinsX()+1):
            sumOfBins = sumOfBins + h.GetBinContent(i)
            sumOfBinsError = (sumOfBinsError*sumOfBinsError + h.GetBinError(i)*h.GetBinError(i))**0.5
            hout.SetBinContent(i,sumOfBins)
            hout.SetBinError(i,sumOfBinsError)
    else:
        for i in range(h.GetNbinsX(),0,-1):
            sumOfBins = sumOfBins + h.GetBinContent(i)
            sumOfBinsError = (sumOfBinsError*sumOfBinsError + h.GetBinError(i)*h.GetBinError(i))**0.5
            hout.SetBinContent(i,sumOfBins)
            hout.SetBinError(i,sumOfBinsError)
    return hout

def DrawCmsText(canvas, text="CMS Preliminary", textFont=62, textSize=0.035, insideAxes=False):
    ttext = ROOT.TLatex()
    ttext.SetNDC(1)
    ttext.SetTextFont(textFont)
    ttext.SetTextAlign(11)
    ttext.SetTextSize(textSize)

    canvas.cd()
    if insideAxes:
        ttext.DrawLatex(canvas.GetLeftMargin()+0.04, 1.0-canvas.GetTopMargin()-0.01-textSize, text)
    else:
        ttext.DrawLatex(canvas.GetLeftMargin()+0.01, 1.0-canvas.GetTopMargin()+0.01, text)

def DrawLumiText(canvas, lumi=1.0, lumiUnit="fb", energy=13, textFont=42, textSize=0.035, bonusText=None):
    ttext = ROOT.TLatex()
    ttext.SetNDC(1)
    ttext.SetTextFont(textFont)
    ttext.SetTextAlign(31)
    ttext.SetTextSize(textSize)

    canvas.cd()
    if energy is not None:
        text = "{0} {1}^{{#minus1}} ({2} TeV{3})".format(lumi,lumiUnit,energy, ", "+bonusText if bonusText is not None else "")
    else:
        text = "{0} {1}^{{#minus1}}{2}".format(lumi,lumiUnit, " ("+bonusText+")" if bonusText is not None else "")
    ttext.DrawLatex(1.0-canvas.GetRightMargin()-0.01, 1.0-canvas.GetTopMargin()+0.01, text)

# Function to add labels to plots in the official CMS style circa Moriond 2019.
# Most parameters should be left as they are unless you have very good reason to change them.
# cmsText is shown in bold at upper left. Defaults to "CMS".
# extraText is shown in italics. Defaults to nothing. Often want "Preliminary" here.
# Depending on the size of your plot, you made need to tweak relPosX so these two don't overlap. TODO: Make this tweak automatically.
# lumi is a string expecting something like "101 fb^{1}" as its input.
def CMS_Style(pad, iPosX = 0, cmsText = "CMS", extraText = None, lumi = "", cmsTextFont = 61, extraTextFont = 52, cmsTextSize = 0.35, cmsTextOffset = 0.1, lumiTextSize = 0.35, lumiTextOffset = 0.2, relPosX = 0.1):

    writeExtraText = extraText != None

    relPosY    = 0.035
    relExtraDY = 1.2

    extraOverCmsTextSize  = 0.76

    drawLogo      = False

    outOfFrame    = False
    if(iPosX/10==0 ): outOfFrame = True

    alignY_=3
    alignX_=2
    if( iPosX/10==0 ): alignX_=1
    if( iPosX==0    ): alignY_=1
    if( iPosX/10==1 ): alignX_=1
    if( iPosX/10==2 ): alignX_=2
    if( iPosX/10==3 ): alignX_=3
    align_ = 10*alignX_ + alignY_

    H = pad.GetWh()
    W = pad.GetWw()
    l = pad.GetLeftMargin()
    t = pad.GetTopMargin()
    r = pad.GetRightMargin()
    b = pad.GetBottomMargin()
    e = 0.025

    pad.cd()

    lumiText = lumi + " (13 TeV)" if len(lumi) > 0 else "(13 TeV)"

    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextAngle(0)
    latex.SetTextColor(ROOT.kBlack)    
    
    extraTextSize = extraOverCmsTextSize*cmsTextSize
    
    latex.SetTextFont(42)
    latex.SetTextAlign(31) 
    latex.SetTextSize(lumiTextSize*t)    

    latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText)

    if( outOfFrame ):
        latex.SetTextFont(cmsTextFont)
        latex.SetTextAlign(11) 
        latex.SetTextSize(cmsTextSize*t)    
        latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText)
  
    pad.cd()

    posX_ = 0
    if( iPosX%10<=1 ):
        posX_ =   l + relPosX*(1-l-r)
    elif( iPosX%10==2 ):
        posX_ =  l + 0.5*(1-l-r)
    elif( iPosX%10==3 ):
        posX_ =  1-r - relPosX*(1-l-r)

    posY_ = 1-t - relPosY*(1-t-b)

    if( not outOfFrame ):
        if( drawLogo ):
            posX_ =   l + 0.045*(1-l-r)*W/H
            posY_ = 1-t - 0.045*(1-t-b)
            xl_0 = posX_
            yl_0 = posY_ - 0.15
            xl_1 = posX_ + 0.15*H/W
            yl_1 = posY_
            CMS_logo = ROOT.TASImage("CMS-BW-label.png")
            pad_logo =  ROOT.TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 )
            pad_logo.Draw()
            pad_logo.cd()
            CMS_logo.Draw("X")
            pad_logo.Modified()
            pad.cd()          
        else:
            latex.SetTextFont(cmsTextFont)
            latex.SetTextSize(cmsTextSize*t)
            latex.SetTextAlign(align_)
            latex.DrawLatex(posX_, posY_, cmsText)
            if( writeExtraText ) :
                latex.SetTextFont(extraTextFont)
                latex.SetTextAlign(align_)
                latex.SetTextSize(extraTextSize*t)
                latex.DrawLatex(posX_, posY_- relExtraDY*cmsTextSize*t, extraText)
    elif( writeExtraText ):
        if( iPosX==0):
            posX_ =   l +  relPosX*(1-l-r)
            posY_ =   1-t+lumiTextOffset*t

        latex.SetTextFont(extraTextFont)
        latex.SetTextSize(extraTextSize*t)
        latex.SetTextAlign(align_)
        latex.DrawLatex(posX_, posY_, extraText)      

    pad.Update()

