#! /usr/bin/python

'''
Calculate the full (stat.+syst.) uncertainty of the background prediction.
Predicted yields and stat. uncertainties (MC stat. and CR data stat.) are taken from the output of background prediction macro.
[see: AnalysisMethods/macros/0LepSearchRegions/getZeroLeptonPrediction.C] 
Syst. uncertainties are calculate based on the config files for datacard production.
[see: Limits/Datacards/setup/values_0l_unc_*.conf] 
'''

import os
import math
import json
import argparse
import ROOT as rt
rt.gROOT.SetBatch(True)

uncfiles=[
'values_0l_unc_jesunc.conf',
'values_0l_unc_lepcorr.conf',
'values_0l_unc_toppt.conf',
'values_0l_unc_wtopfrac.conf',
 ]

ttzuncfile = 'values_0l_unc_all.conf'

all_samples=('ttbarplusw', 'znunu', 'rare', 'qcd')
hist_names=('ttbarplusw_pred', 'znunu_pred', 'rare_pred', 'qcd_pred')
table_header='Search region & \\met [GeV]  &  Lost lepton  &  \\znunu  & \\Rare &  QCD  &  total SM  &  $N_{\\rm data}$  \\\\ \n'

# ordered bin list
binlist=('bin_250_nb1_mtb0_nj5',
 'bin_300_nb1_mtb0_nj5',
 'bin_400_nb1_mtb0_nj5',
 'bin_500_nb1_mtb0_nj5',
 'bin_250_nb1_mtb0_nj7',
 'bin_300_nb1_mtb0_nj7',
 'bin_400_nb1_mtb0_nj7',
 'bin_500_nb1_mtb0_nj7',
 'bin_250_nb2_mtb0_nj5',
 'bin_300_nb2_mtb0_nj5',
 'bin_400_nb2_mtb0_nj5',
 'bin_500_nb2_mtb0_nj5',
 'bin_250_nb2_mtb0_nj7',
 'bin_300_nb2_mtb0_nj7',
 'bin_400_nb2_mtb0_nj7',
 'bin_500_nb2_mtb0_nj7',
 'bin_250_nb1_mtb175_nj5_nt0_nw0',
 'bin_350_nb1_mtb175_nj5_nt0_nw0',
 'bin_450_nb1_mtb175_nj5_nt0_nw0',
 'bin_550_nb1_mtb175_nj5_nt0_nw0',
 'bin_250_nb1_mtb175_nj7_nt0_nw0',
 'bin_350_nb1_mtb175_nj7_nt0_nw0',
 'bin_450_nb1_mtb175_nj7_nt0_nw0',
 'bin_550_nb1_mtb175_nj7_nt0_nw0',
 'bin_250_nb1_mtb175_nj5t_nt0_nw1t',
 'bin_350_nb1_mtb175_nj5t_nt0_nw1t',
 'bin_450_nb1_mtb175_nj5t_nt0_nw1t',
 'bin_550_nb1_mtb175_nj5t_nt0_nw1t',
 'bin_650_nb1_mtb175_nj5t_nt0_nw1t',
 'bin_250_nb1_mtb175_nj5t_nt1t_nw0',
 'bin_350_nb1_mtb175_nj5t_nt1t_nw0',
 'bin_450_nb1_mtb175_nj5t_nt1t_nw0',
 'bin_550_nb1_mtb175_nj5t_nt1t_nw0',
 'bin_650_nb1_mtb175_nj5t_nt1t_nw0',
 'bin_250_nb1_mtb175_nj5t_nt1t_nw1t',
 'bin_300_nb1_mtb175_nj5t_nt1t_nw1t',
 'bin_400_nb1_mtb175_nj5t_nt1t_nw1t',
 'bin_500_nb1_mtb175_nj5t_nt1t_nw1t',
 'bin_250_nb2_mtb175_nj5_nt0_nw0',
 'bin_350_nb2_mtb175_nj5_nt0_nw0',
 'bin_450_nb2_mtb175_nj5_nt0_nw0',
 'bin_550_nb2_mtb175_nj5_nt0_nw0',
 'bin_250_nb2_mtb175_nj7_nt0_nw0',
 'bin_350_nb2_mtb175_nj7_nt0_nw0',
 'bin_450_nb2_mtb175_nj7_nt0_nw0',
 'bin_550_nb2_mtb175_nj7_nt0_nw0',
 'bin_250_nb2_mtb175_nj5t_nt0_nw1t',
 'bin_350_nb2_mtb175_nj5t_nt0_nw1t',
 'bin_450_nb2_mtb175_nj5t_nt0_nw1t',
 'bin_550_nb2_mtb175_nj5t_nt0_nw1t',
 'bin_650_nb2_mtb175_nj5t_nt0_nw1t',
 'bin_250_nb2_mtb175_nj5t_nt1t_nw0',
 'bin_350_nb2_mtb175_nj5t_nt1t_nw0',
 'bin_450_nb2_mtb175_nj5t_nt1t_nw0',
 'bin_550_nb2_mtb175_nj5t_nt1t_nw0',
 'bin_650_nb2_mtb175_nj5t_nt1t_nw0',
 'bin_250_nb2_mtb175_nj5t_nt1t_nw1t',
 'bin_300_nb2_mtb175_nj5t_nt1t_nw1t',
 'bin_400_nb2_mtb175_nj5t_nt1t_nw1t',
 'bin_500_nb2_mtb175_nj5t_nt1t_nw1t')


binMap={
### nb1, low mtb ###
'nb1_mtb0_nj5': {
   'cut': 'mtcsv12met<175 && nbjets==1 && njets>=5 && njets<7',
   'var': 'met',
   'bin': [250, 300, 400, 500, 1000]
    },
'nb1_mtb0_nj7': {
   'cut': 'mtcsv12met<175 && nbjets==1 && njets>=7',
   'var': 'met',
   'bin': [250, 300, 400, 500, 1000]
    },
### nb2, low mtb ###
'nb2_mtb0_nj5': {
   'cut': 'mtcsv12met<175 && nbjets>=2 && njets>=5 && njets<7',
   'var': 'met',
   'bin': [250, 300, 400, 500, 1000]
    },
'nb2_mtb0_nj7': {
   'cut': 'mtcsv12met<175 && nbjets>=2 && njets>=7',
   'var': 'met',
   'bin': [250, 300, 400, 500, 1000]
    },
### nb1, high mtb ###
'nb1_mtb175_nj5_nt0_nw0': {
   'cut': 'mtcsv12met>=175 && nbjets==1 && njets>=5 && njets<7 && nsdtopjmewp1loose==0 && nsdwjmewp1loose==0',
   'var': 'met',
   'bin': [250, 350, 450, 550, 1000]
    },
'nb1_mtb175_nj7_nt0_nw0': {
   'cut': 'mtcsv12met>=175 && nbjets==1 && njets>=7 && nsdtopjmewp1loose==0 && nsdwjmewp1loose==0',
   'var': 'met',
   'bin': [250, 350, 450, 550, 1000]
    },
'nb1_mtb175_nj5t_nt0_nw1t': {
   'cut': 'mtcsv12met>=175 && nbjets==1 && njets>=5 && nsdtopjmewp1loose==0 && nsdwjmewp1loose>=1',
   'var': 'met',
   'bin': [250, 350, 450, 550, 650, 1000]
    },
'nb1_mtb175_nj5t_nt1t_nw0': {
   'cut': 'mtcsv12met>=175 && nbjets==1 && njets>=5 && nsdtopjmewp1loose>=1 && nsdwjmewp1loose==0',
   'var': 'met',
   'bin': [250, 350, 450, 550, 650, 1000]
    },
'nb1_mtb175_nj5t_nt1t_nw1t': {
   'cut': 'mtcsv12met>=175 && nbjets==1 && njets>=5 && nsdtopjmewp1loose>=1 && nsdwjmewp1loose>=1',
   'var': 'met',
   'bin': [250, 300, 400, 500, 1000]
    },
### nb2, high mtb ###
'nb2_mtb175_nj5_nt0_nw0': {
   'cut': 'mtcsv12met>=175 && nbjets>=2 && njets>=5 && njets<7 && nsdtopjmewp1loose==0 && nsdwjmewp1loose==0',
   'var': 'met',
   'bin': [250, 350, 450, 550, 1000]
    },
'nb2_mtb175_nj7_nt0_nw0': {
   'cut': 'mtcsv12met>=175 && nbjets>=2 && njets>=7 && nsdtopjmewp1loose==0 && nsdwjmewp1loose==0',
   'var': 'met',
   'bin': [250, 350, 450, 550, 1000]
    },
'nb2_mtb175_nj5t_nt0_nw1t': {
   'cut': 'mtcsv12met>=175 && nbjets>=2 && njets>=5 && nsdtopjmewp1loose==0 && nsdwjmewp1loose>=1',
   'var': 'met',
   'bin': [250, 350, 450, 550, 650, 1000]
    },
'nb2_mtb175_nj5t_nt1t_nw0': {
   'cut': 'mtcsv12met>=175 && nbjets>=2 && njets>=5 && nsdtopjmewp1loose>=1 && nsdwjmewp1loose==0',
   'var': 'met',
   'bin': [250, 350, 450, 550, 650, 1000]
    },
'nb2_mtb175_nj5t_nt1t_nw1t': {
   'cut': 'mtcsv12met>=175 && nbjets>=2 && njets>=5 && nsdtopjmewp1loose>=1 && nsdwjmewp1loose>=1',
   'var': 'met',
   'bin': [250, 300, 400, 500, 1000]
    },
}

labelMap = {
    'nb1': r'$\nb=1$',
    'nb2': r'$\nb\geq2$',
    'mtb0': r'$\mtb<175$~\GeV',
    'mtb175': r'$\mtb>175$~\GeV',
    'nj5': r'$5\leq\nj<7$',
    'nj7': r'$nj\geq7$',
    'nj5t': r'$\nj\geq5$',
    'nt0': r'$\nt=0$',
    'nw0': r'$\nw=0$',
    'nt1t':r'$\nt\geq1$',
    'nw1t':r'$\nw\geq1$',
    }



def sumUnc(unc_list):
    '''Add uncertainties in quadrature.'''
    return math.sqrt(sum(err*err for err in unc_list))


# relUnc[type][bin][sample] : percentage syst. uncertainty of each 'type' per 'bin' per 'sample'
# absUnc[bin][type] : absolute uncertainty per 'bin' of each 'type'
# yields[bin][sample] : predicted bkg yields per bin per sample 
# statUnc[bin] : stat. (MC + data CR) unc. per bin
# systUnc[bin] : syst. unc. per bin
# fullUnc[bin] : full unc. per bin

relUnc={}
absUnc={}
absUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'rare':{}}
yields={}
yields_data={}
statUnc={}
statUnc_pieces={}
systUnc={}
systUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'rare':{}}
fullUnc={}
fullUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'rare':{}}
allVals = {}

def readRelUnc(config_path):
    '''Read in percentage syst. uncertainty from the config files.'''
    for unc_fn in uncfiles:
        with open(os.path.join(config_path, unc_fn), 'r') as f:
            for line in f.readlines():
                try:
                    bin, type, sample, value = line.split()
                except ValueError:
                    continue
                if bin not in binlist or sample not in all_samples:
                    # ignore CR syst., e.g., "bin_onelepcr_250_5_1_0_0"
                    continue
                if type not in relUnc:
                    relUnc[type] = {}
                if bin not in relUnc[type]:
                    relUnc[type][bin] = {}
                if sample in all_samples:
                    relUnc[type][bin][sample] = float(value)-1
    
    # only for rare: need special treatment for lumi and rareNorm unc.
    if ttzuncfile != '':
        with open(os.path.join(config_path, ttzuncfile), 'r') as f:
            for line in f.readlines():
                try:
                    bin, type, sample, value = line.split()
                except ValueError:
                    continue
                for samp in all_samples:
                    if samp not in sample:
                        continue
                    print 'adding unc %s for %s'%(type, samp)                    
                    if type not in relUnc:
                        relUnc[type] = {}
                    # bin=='all' in config file
                    for bin in binlist:
                        if bin not in relUnc[type]:
                            relUnc[type][bin] = {sample : float(value)-1}

    # if a type of unc. is not define for some samples/bins, then fill zero
    for type in relUnc:
        for bin in binlist:
            if bin not in relUnc[type]:
                # for bin-specific unc. (e.g., qcd-tf) : set other bins to 0
                relUnc[type][bin] = {sample:0 for sample in all_samples}
            else:
                for sample in all_samples:
                    # for sample specific unc.: set other samples to 0
                    if sample not in relUnc[type][bin]:
                        relUnc[type][bin][sample] = 0


def readYields(pred_file):
    ''' Read in predicted bkg yields and the stat. unc. 
    
    pred_file -- input root file 
    '''
    f = rt.TFile(pred_file)
    for hname, sample in zip(hist_names, all_samples):
        h = f.Get(hname)
        for ibin in xrange(0, h.GetNbinsX()):
            bin = binlist[ibin]
            if bin not in yields:
                yields[bin] = {}
                statUnc_pieces[bin] = {}
            y = h.GetBinContent(ibin+1)
            e = h.GetBinError(ibin+1)
            yields[bin][sample] = y
            if sample == 'rare': statUnc_pieces[bin][sample] = min(e,y) # don't want MC stat unc > 100%
            else :              statUnc_pieces[bin][sample] = e
    h = f.Get('data')
    for ibin in xrange(0, h.GetNbinsX()):
        bin = binlist[ibin]
        yields_data[bin] = (h.GetBinContent(ibin+1), h.GetBinError(ibin+1))
    f.Close()
    for bin in binlist:
        statUnc[bin] = sumUnc(statUnc_pieces[bin].values())


def calcAbsUnc():
    ''' Calculate syst. uncertainty.
    For uncertainties of the same type, add linearly for each bin.
    For uncertainties of different types, add in quadrature for each bin.
    '''
    absUnc = {bin:{} for bin in binlist}
    for sample in all_samples: absUnc_pieces[sample] = {bin:{} for bin in binlist}
    for bin in binlist:
        absUnc[bin] = {type:0 for type in relUnc.keys()}
        for sample in all_samples: absUnc_pieces[sample][bin] = {type:0 for type in relUnc.keys()}
        for type in relUnc:
            for sample in all_samples:
                # Add the same type of unc. linearly
                tempUnc = relUnc[type][bin][sample] * yields[bin][sample]
                absUnc[bin][type]                += tempUnc
                absUnc_pieces[sample][bin][type] += tempUnc

    for bin in absUnc:
        # Add different types of unc. in quadrature
        systUnc[bin] = sumUnc(absUnc[bin].values())
        fullUnc[bin] = sumUnc([statUnc[bin], systUnc[bin]])
        for sample in all_samples:
            systUnc_pieces[sample][bin] = sumUnc(absUnc_pieces[sample][bin].values())
            fullUnc_pieces[sample][bin] = sumUnc([statUnc_pieces[bin][sample], systUnc_pieces[sample][bin]])


def writeFullUnc(pred_file):
    ''' Update the input root file, add a hist with total prediction and full uncertainty. '''
    f = rt.TFile(pred_file, 'UPDATE')
    h = rt.TH1F('bkgtotal_unc_sr', '', len(binlist), 0, len(binlist))
    h_pieces = {}
    for sample in all_samples : h_pieces[sample] = rt.TH1F(sample+'_unc_sr', '', len(binlist), 0, len(binlist))
    print "%30s %10s %8s" % ('bin', 'total pred', 'total unc.')
    for ibin in xrange(0, h.GetNbinsX()):
        bin = binlist[ibin]
        val = sum(yields[bin].values())
        err = fullUnc[bin]
        h.SetBinContent(ibin+1, val)
        h.SetBinError(ibin+1, err)
        print "%30s %10.2f %8.2f" % (bin, val, err)
        allVals[bin] = {'bkg':(val,err)}
        for sample in all_samples:
            val = yields[bin][sample]
            err = fullUnc_pieces[sample][bin]
            h_pieces[sample].SetBinContent(ibin+1, val)
            h_pieces[sample].SetBinError(ibin+1, err)
            allVals[bin][sample] = (val,err)  
    h.Write('bkgtotal_unc_sr', rt.TObject.kOverwrite)
    for sample in all_samples : h_pieces[sample].Write(sample+'_unc_sr', rt.TObject.kOverwrite)
    f.Close()

def makeYieldTable(output='pred.tex'):
    ''' Make a Latex-formatted table with each bkg plus unc, total bkg plus unc, and observed data for every bin. '''
    print '\nprinting yield table...\n'
    s  = '\\hline\n'
    s += table_header
    s += '\\hline\n'
    s += makeTable()
    s += '\\hline\n'
    print s
    with open(output, 'w') as f:
        print >> f, s
    
def makeTable():
    ''' Put together the table chunk for the given nj,nb,mtb,nt mega-bin. '''
    sections=[]
    s=''
    ibin=0
    for bin in binlist: 
        _, met, sec = bin.split('_', 2)
        if sec not in sections:
            sections.append(sec)
            s += chunkHeader(sec)
        metbins = binMap[sec]['bin']
        print metbins
        idx = metbins.index(int(met))
        metlabel = r'$>%s$'%met if idx==len(metbins)-2 else '$-$'.join([met, str(metbins[idx+1])])
        s += '%d & '%ibin
        ibin = ibin+1
        s += metlabel
        for bkg in list(all_samples)+['bkg']:
            n, e = allVals[bin][bkg]
            s += formatPrediction(n,e)
        n, e = yields_data[bin]
        s += ' & ' + str(int(n))
        s += ' \\\\ \n'
    return s

# formats the prediction nEvents +/- error
def formatPrediction(n,e):
  if n>=10:
    n = str(int(round(n,0)))
    e = str(int(round(e,0)))
  elif n>=1:
    n = str(round(n,1))
    e = str(round(e,1))
  else:
    n = str(round(n,2))
    e = str(round(e,2))
  if n=='0.0':
    if e=='0.0':
      return ' & $<$0.01'
    return ' & $<$' + e
  return ' & ' + n + ' $\\pm$ ' + e

# puts together the bin header for bins of nJets, mtb, nTop (no selection on nB)
def chunkHeader(sec):
    ''' Put together the mega-bin chunk header. '''
    cats = sec.split('_')
    labs = [labelMap[c] for c in cats]
    ncolumn = len(all_samples)+4
    s  = '\\hline\n'
    s += '\\multicolumn{'+str(ncolumn)+'}{c}{'
    s += ', '.join(labs)
    s += '} \\\\ \n'
    s += '\\hline\n' 
    return s


def main():
    parser = argparse.ArgumentParser('Calculate the full (stat.+syst.) uncertainty of the background prediction.')
    parser.add_argument('predfile',
        default='srpred.root',
        help='Input prediction file. Default: %(default)s'
    )
    parser.add_argument('-c', '--configdir',
        dest='configdir',
        default='syst',
        help='Uncertainties configs directory. Default: %(default)s'
    )
    parser.add_argument('-t', '--printTable',
        dest='printTable',
        action='store_true',
        help='print the full bkg prediction table: %(default)s'
    )
    args = parser.parse_args()
    
    readRelUnc(args.configdir)
    readYields(args.predfile)
    calcAbsUnc()
    writeFullUnc(args.predfile)
    if args.printTable : makeYieldTable()


if __name__=='__main__':
    main()
