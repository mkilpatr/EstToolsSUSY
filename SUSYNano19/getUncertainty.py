#! /usr/bin/env python

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
from ROOT import TGraphAsymmErrors
import numpy as np
rt.gROOT.SetBatch(True)

from ROOT import TCanvas, TFile, TProfile, TNtuple, TH1F, TH2F, THStack, TLegend, TFile, TColor

isRun2 = True

uncdir = '/eos/uscms/store/user/lpcsusyhad/Stop_production/LimitInputs/31Jul2020_Run2_dev_v7/' if isRun2 else '/eos/uscms/store/user/lpcsusyhad/Stop_production/LimitInputs/12May2020_2016Unblind_dev_v6/'
uncdir_local = '/uscms/home/mkilpatr/nobackup/CMSSW_10_2_9/src/Limits/Datacards/setup/SUSYNano19/'

uncfiles=[]
if isRun2:
    uncfiles.append(uncdir + 'LostLepton/values_unc_sb_ll.conf')
    uncfiles.append(uncdir + 'LostLepton/values_unc_cb_ll.conf')
    uncfiles.append(uncdir + 'Zinvisible/zinv_syst_Run2.conf')
    uncfiles.append(uncdir + 'TTZRare/TTZ_syst.conf')
    uncfiles.append(uncdir + 'TTZRare/Rare_syst.conf')
    uncfiles.append(uncdir + 'QCD/JSW_Baseline_systematics_QCDResidMET.conf')
    uncfiles.append(uncdir + 'QCD/JSW_QCDCR_systematics_QCDResidMET.conf')
else:
    uncfiles.append(uncdir + 'LostLepton/values_unc_sb_ll_2016.conf')
    uncfiles.append(uncdir + 'LostLepton/values_unc_cb_ll_2016.conf')
    uncfiles.append(uncdir + 'Zinvisible/zinv_syst_2016.conf')
    uncfiles.append(uncdir + 'TTZRare/TTZ_syst.conf')
    uncfiles.append(uncdir + 'TTZRare/Rare_syst.conf')
    uncfiles.append(uncdir + 'QCD/JSW_Baseline_systematics_QCDResidMET.conf')
    uncfiles.append(uncdir + 'QCD/JSW_QCDCR_systematics_QCDResidMET.conf')

all_bin_unc_file = uncdir_local + 'values_unc_all.conf'

all_samples=('ttbarplusw', 'znunu', 'TTZ', 'Rare', 'qcd')
unc_samples=('ttbarplusw', 'znunu', 'TTZ', 'Rare', 'qcd', 'phocr_gjets', 'phocr_back', 'Rare')
graph_names=('httbar', 'hznunu', 'httz', 'hRare', 'hqcd')
table_header='Search bin & \ptmiss [{\GeVns}]  &  Lost lepton  &  \\zparennunujets  & Rare & QCD multijet &  Total SM  &  \\ND{}  \\\\ \n'

uncMap = {
    "b_light"       : "Light b-tag",
    "b_heavy"       : "Heavy b-tag",
    "ivfunc"        : "Soft b-tag",
    #"LHEScale"     : "LHE Scale",
    "ISR_Weight_background" : "ISR",
    "JES"       : "JES",
    "metres"        : "\met res.",
    "Prefire_Weight"    : "Prefire",
    "PDF_Weight"    : "PDF",
    "PU_Weight"     : "Pileup",
    "eff_e"     : "$e$ veto",
    "err_mu"        : "$\mu$ veto",
    "eff_tau"       : "$\\tau$ veto",
    "eff_toptag"    : "\Nt",
    "eff_restoptag" : "\Nres",
    "eff_wtag"      : "\Nw",
    "eff_fatjet_veto"   : "AK8 Veto",
    "lumi"      : "Lumi",
}

pred_total_name = 'hpred'
json_bkgPred = uncdir + '/combine_bkgPred.json'

processMap = {'ttbarplusw':'lepcr', 'znunu':'phocr', 'qcd':'qcdcr'}
systUnc_rel_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'TTZ':{}, 'Rare':{}}

debug = False
test_samp = ['znunu']
test_bin  = ['bin_hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500_MET_pt250to350']
test_type = ['PDF_Weight']

# ordered bin list
binlist=('bin_lm_nb0_nivf0_highptisr_nj2to5_MET_pt450to550', 
    'bin_lm_nb0_nivf0_highptisr_nj2to5_MET_pt550to650', 
    'bin_lm_nb0_nivf0_highptisr_nj2to5_MET_pt650to750', 
    'bin_lm_nb0_nivf0_highptisr_nj2to5_MET_pt750toinf', 
    'bin_lm_nb0_nivf0_highptisr_nj6_MET_pt450to550', 
    'bin_lm_nb0_nivf0_highptisr_nj6_MET_pt550to650', 
    'bin_lm_nb0_nivf0_highptisr_nj6_MET_pt650to750', 
    'bin_lm_nb0_nivf0_highptisr_nj6_MET_pt750toinf', 
    'bin_lm_nb0_nivf1_highptisr_nj2to5_MET_pt450to550', 
    'bin_lm_nb0_nivf1_highptisr_nj2to5_MET_pt550to650', 
    'bin_lm_nb0_nivf1_highptisr_nj2to5_MET_pt650to750', 
    'bin_lm_nb0_nivf1_highptisr_nj2to5_MET_pt750toinf', 
    'bin_lm_nb0_nivf1_highptisr_nj6_MET_pt450to550', 
    'bin_lm_nb0_nivf1_highptisr_nj6_MET_pt550to650', 
    'bin_lm_nb0_nivf1_highptisr_nj6_MET_pt650to750', 
    'bin_lm_nb0_nivf1_highptisr_nj6_MET_pt750toinf', 
    'bin_lm_nb1_nivf0_lowmtb_lowptisr_lowptb_MET_pt300to400', 
    'bin_lm_nb1_nivf0_lowmtb_lowptisr_lowptb_MET_pt400to500', 
    'bin_lm_nb1_nivf0_lowmtb_lowptisr_lowptb_MET_pt500to600', 
    'bin_lm_nb1_nivf0_lowmtb_lowptisr_lowptb_MET_pt600toinf', 
    'bin_lm_nb1_nivf0_lowmtb_lowptisr_medptb_MET_pt300to400', 
    'bin_lm_nb1_nivf0_lowmtb_lowptisr_medptb_MET_pt400to500', 
    'bin_lm_nb1_nivf0_lowmtb_lowptisr_medptb_MET_pt500to600', 
    'bin_lm_nb1_nivf0_lowmtb_lowptisr_medptb_MET_pt600toinf', 
    'bin_lm_nb1_nivf0_lowmtb_highptisr_lowptb_MET_pt450to550', 
    'bin_lm_nb1_nivf0_lowmtb_highptisr_lowptb_MET_pt550to650', 
    'bin_lm_nb1_nivf0_lowmtb_highptisr_lowptb_MET_pt650to750', 
    'bin_lm_nb1_nivf0_lowmtb_highptisr_lowptb_MET_pt750toinf', 
    'bin_lm_nb1_nivf0_lowmtb_highptisr_medptb_MET_pt450to550', 
    'bin_lm_nb1_nivf0_lowmtb_highptisr_medptb_MET_pt550to650', 
    'bin_lm_nb1_nivf0_lowmtb_highptisr_medptb_MET_pt650to750', 
    'bin_lm_nb1_nivf0_lowmtb_highptisr_medptb_MET_pt750toinf', 
    'bin_lm_nb1_nivf1_lowmtb_medptisr_lowptb_MET_pt300to400', 
    'bin_lm_nb1_nivf1_lowmtb_medptisr_lowptb_MET_pt400to500', 
    'bin_lm_nb1_nivf1_lowmtb_medptisr_lowptb_MET_pt500toinf', 
    'bin_lm_nb2_lowmtb_lowptisr_lowptb12_MET_pt300to400', 
    'bin_lm_nb2_lowmtb_lowptisr_lowptb12_MET_pt400to500', 
    'bin_lm_nb2_lowmtb_lowptisr_lowptb12_MET_pt500toinf', 
    'bin_lm_nb2_lowmtb_lowptisr_medptb12_MET_pt300to400', 
    'bin_lm_nb2_lowmtb_lowptisr_medptb12_MET_pt400to500', 
    'bin_lm_nb2_lowmtb_lowptisr_medptb12_MET_pt500toinf', 
    'bin_lm_nb2_lowmtb_lowptisr_highptb12_nj7_MET_pt300to400', 
    'bin_lm_nb2_lowmtb_lowptisr_highptb12_nj7_MET_pt400to500', 
    'bin_lm_nb2_lowmtb_lowptisr_highptb12_nj7_MET_pt500toinf', 
    'bin_lm_nb2_lowmtb_highptisr_lowptb12_MET_pt450to550', 
    'bin_lm_nb2_lowmtb_highptisr_lowptb12_MET_pt550to650', 
    'bin_lm_nb2_lowmtb_highptisr_lowptb12_MET_pt650toinf', 
    'bin_lm_nb2_lowmtb_highptisr_medptb12_MET_pt450to550', 
    'bin_lm_nb2_lowmtb_highptisr_medptb12_MET_pt550to650', 
    'bin_lm_nb2_lowmtb_highptisr_medptb12_MET_pt650toinf', 
    'bin_lm_nb2_lowmtb_highptisr_highptb12_nj7_MET_pt450to550', 
    'bin_lm_nb2_lowmtb_highptisr_highptb12_nj7_MET_pt550to650', 
    'bin_lm_nb2_lowmtb_highptisr_highptb12_nj7_MET_pt650toinf', 
    'bin_hm_nb1_lowmtb_nj7_nrtgeq1_MET_pt250to300', 
    'bin_hm_nb1_lowmtb_nj7_nrtgeq1_MET_pt300to400', 
    'bin_hm_nb1_lowmtb_nj7_nrtgeq1_MET_pt400to500', 
    'bin_hm_nb1_lowmtb_nj7_nrtgeq1_MET_pt500toinf', 
    'bin_hm_nb2_lowmtb_nj7_nrtgeq1_MET_pt250to300', 
    'bin_hm_nb2_lowmtb_nj7_nrtgeq1_MET_pt300to400', 
    'bin_hm_nb2_lowmtb_nj7_nrtgeq1_MET_pt400to500', 
    'bin_hm_nb2_lowmtb_nj7_nrtgeq1_MET_pt500toinf', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000_MET_pt250to350', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000_MET_pt350to450', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000_MET_pt450to550', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nw0_htgt1000_MET_pt550toinf', 
    'bin_hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000_MET_pt250to350', 
    'bin_hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000_MET_pt350to450', 
    'bin_hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000_MET_pt450to550', 
    'bin_hm_nb2_highmtb_nt0_nrt0_nw0_htgt1000_MET_pt550toinf', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000_MET_pt250to550', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000_MET_pt550to650', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_htlt1000_MET_pt650toinf', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1500_MET_pt250to550', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1500_MET_pt550to650', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_ht1000to1500_MET_pt650toinf', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500_MET_pt250to550', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500_MET_pt550to650', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nw0_htgt1500_MET_pt650toinf', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1300_MET_pt250to350', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1300_MET_pt350to450', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nwgeq1_htlt1300_MET_pt450toinf', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1300_MET_pt250to350', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1300_MET_pt350to450', 
    'bin_hm_nb1_highmtb_nt0_nrt0_nwgeq1_htgt1300_MET_pt450toinf', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000_MET_pt250to350', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000_MET_pt350to450', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000_MET_pt450to550', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000_MET_pt550to650', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htlt1000_MET_pt650toinf', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500_MET_pt250to350', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500_MET_pt350to450', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500_MET_pt450to550', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500_MET_pt550to650', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_ht1000to1500_MET_pt650toinf', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500_MET_pt250to350', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500_MET_pt350to450', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500_MET_pt450to550', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500_MET_pt550to650', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nw0_htgt1500_MET_pt650toinf', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_MET_pt250to550', 
    'bin_hm_nb1_highmtb_ntgeq1_nrt0_nwgeq1_MET_pt550toinf', 
    'bin_hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_MET_pt250to550', 
    'bin_hm_nb1_highmtb_ntgeq1_nrtgeq1_nw0_MET_pt550toinf', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_MET_pt250to550', 
    'bin_hm_nb1_highmtb_nt0_nrtgeq1_nwgeq1_MET_pt550toinf', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000_MET_pt250to550', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000_MET_pt550to650', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_htlt1000_MET_pt650toinf', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500_MET_pt250to550', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500_MET_pt550to650', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_ht1000to1500_MET_pt650toinf', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500_MET_pt250to550', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500_MET_pt550to650', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw0_htgt1500_MET_pt650toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1300_MET_pt250to350', 
    'bin_hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1300_MET_pt350to450', 
    'bin_hm_nbeq2_highmtb_nt0_nrt0_nw1_htlt1300_MET_pt450toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300_MET_pt250to350', 
    'bin_hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300_MET_pt350to450', 
    'bin_hm_nbeq2_highmtb_nt0_nrt0_nw1_htgt1300_MET_pt450toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000_MET_pt250to350', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000_MET_pt350to450', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000_MET_pt450to550', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000_MET_pt550to650', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htlt1000_MET_pt650toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500_MET_pt250to350', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500_MET_pt350to450', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500_MET_pt450to550', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500_MET_pt550to650', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_ht1000to1500_MET_pt650toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500_MET_pt250to350', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500_MET_pt350to450', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500_MET_pt450to550', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500_MET_pt550to650', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw0_htgt1500_MET_pt650toinf', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw1_MET_pt250to550', 
    'bin_hm_nbeq2_highmtb_nt1_nrt0_nw1_MET_pt550toinf', 
    'bin_hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300_MET_pt250to350', 
    'bin_hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300_MET_pt350to450', 
    'bin_hm_nbeq2_highmtb_nt1_nrt1_nw0_htlt1300_MET_pt450toinf', 
    'bin_hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300_MET_pt250to350', 
    'bin_hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300_MET_pt350to450', 
    'bin_hm_nbeq2_highmtb_nt1_nrt1_nw0_htgt1300_MET_pt450toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw1_MET_pt250to550', 
    'bin_hm_nbeq2_highmtb_nt0_nrt1_nw1_MET_pt550toinf', 
    'bin_hm_nbeq2_highmtb_nt2_nrt0_nw0_MET_pt250to450', 
    'bin_hm_nbeq2_highmtb_nt2_nrt0_nw0_MET_pt450toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt0_nw2_MET_pt250toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300_MET_pt250to450', 
    'bin_hm_nbeq2_highmtb_nt0_nrt2_nw0_htlt1300_MET_pt450toinf', 
    'bin_hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300_MET_pt250to450', 
    'bin_hm_nbeq2_highmtb_nt0_nrt2_nw0_htgt1300_MET_pt450toinf', 
    'bin_hm_nbeq2_highmtb_nrtntnwgeq3_MET_pt250toinf', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000_MET_pt350to550', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_htlt1000_MET_pt550toinf', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500_MET_pt350to550', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_ht1000to1500_MET_pt550toinf', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500_MET_pt350to550', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw0_htgt1500_MET_pt550toinf', 
    'bin_hm_nb3_highmtb_nt0_nrt0_nw1_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt0_nrt0_nw1_MET_pt350to550', 
    'bin_hm_nb3_highmtb_nt0_nrt0_nw1_MET_pt550toinf', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000_MET_pt350to550', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_htlt1000_MET_pt550toinf', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500_MET_pt350to550', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_ht1000to1500_MET_pt550toinf', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500_MET_pt350to550', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw0_htgt1500_MET_pt550toinf', 
    'bin_hm_nb3_highmtb_nt1_nrt0_nw1_MET_pt250toinf', 
    'bin_hm_nb3_highmtb_nt1_nrt1_nw0_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt1_nrt1_nw0_MET_pt350toinf', 
    'bin_hm_nb3_highmtb_nt0_nrt1_nw1_MET_pt250toinf', 
    'bin_hm_nb3_highmtb_nt2_nrt0_nw0_MET_pt250toinf', 
    'bin_hm_nb3_highmtb_nt0_nrt0_nw2_MET_pt250toinf', 
    'bin_hm_nb3_highmtb_nt0_nrt2_nw0_MET_pt250to350', 
    'bin_hm_nb3_highmtb_nt0_nrt2_nw0_MET_pt350toinf', 
    'bin_hm_nb3_highmtb_nrtntnwgeq3_MET_pt250toinf')

labelMap = {
    'lowptisr': r'$300 < \ptISR < 500\GeV$',
    'ntgeq1': r'$\Nt \geq 1$',
    'nt2': r'$\Nt = 2$',
    'nivf0': r'$\Nsv = 0$',
    'nivf1': r'$\Nsv \geq 1$',
    'nw2': r'$\Nw = 2$',
    'nj2to5': r'$2 \leq \Nj \leq 5$',
    'nb2': r'$\Nb \geq 2$',
    'nbeq2': r'$\Nb = 2$',
    'nb3': r'$\Nb \geq 3$',
    'nb1': r'$\Nb = 1$',
    'nbgeq1': r'$\Nb \geq 1$',
    'nb0': r'$\Nb = 0$',
    'nrt2': r'$\Nres = 2$',
    'medptisr': r'$\ptISR > 300\GeV$',
    'highptisr': r'$\ptISR > 500\GeV$',
    'nj7': r'$\Nj \geq 7$',
    'highptb': r'$\ptb > 70\GeV$',
    'hm': r'High \dm',
    'nw0': r'$\Nw = 0$',
    'nwgeq1': r'$\Nw \geq 1$',
    'nw1': r'$\Nw = 1$',
    'nrt0': r'$\Nres = 0$',
    'nrt1': r'$\Nres = 1$',
    'lowptb': r'$\ptb < 40\GeV$',
    'medptb': r'$40 < \ptb < 70\GeV$',
    'nt0': r'$\Nt = 0$',
    'lm': r'Low \dm',
    'lowptb12': r'$\ptbonetwo < 80\GeV$',
    'highptb12': r'$\ptbonetwo > 140\GeV$',
    'lowmtb': r'$\mTb < 175\GeV$',
    'highmtb': r'$\mTb > 175\GeV$',
    'nt1': r'$\Nt = 1$',
    'medptb12': r'$80 < \ptbonetwo < 140\GeV$',
    'nrtgeq1': r'$\Nres \geq 1$',
    'nj6': r'$\Nj \geq 6$',
    'nrtntnwgeq2': r'$(\Nt+\Nres+\Nw) \geq 2$',
    'nrtntnwgeq3': r'$(\Nt+\Nres+\Nw) \geq 3$',
    'htlt1000': r'$\HT < 1000\GeV$',
    'htgt1000': r'$\HT > 1000\GeV$',
    'ht1000to1500': r'$1000 < \HT < 1500\GeV$',
    'htgt1500': r'$\HT > 1500\GeV$',
    'htlt1300': r'$\HT < 1300\GeV$',
    'htgt1300': r'$\HT > 1300\GeV$',
    'lmNoDPhi': r'low $\Delta m$',
    'hmNoDPhi': r'high $\Delta m$',
    'MET': r'',
    }

# ------ process json file ------
def json_load_byteified(file_handle):
#     https://stackoverflow.com/questions/956867/how-to-get-string-objects-instead-of-unicode-ones-from-json-in-python/13105359#13105359
    import json
    return _byteify(
        json.load(file_handle, object_hook=_byteify),
        ignore_dicts=True
    )
def _byteify(data, ignore_dicts = False):
    # if this is a unicode string, return its string representation
    if isinstance(data, unicode):
        return data.encode('utf-8')
    # if this is a list of values, return list of byteified values
    if isinstance(data, list):
        return [ _byteify(item, ignore_dicts=True) for item in data ]
    # if this is a dictionary, return dictionary of byteified keys and values
    # but only if we haven't already byteified it
    if isinstance(data, dict) and not ignore_dicts:
        return {
            _byteify(key, ignore_dicts=True): _byteify(value, ignore_dicts=True)
            for key, value in data.iteritems()
        }
    # if it's anything else, return it in its original form
    return data

with open(json_bkgPred) as jf:
    j_bkg = json_load_byteified(jf)
    binMaps = j_bkg['binMaps']
    yields_dc  = j_bkg['yieldsMap']
    binlist = j_bkg['binlist']
    binnum  = j_bkg['binNum']
    crbinlist = {
        'lepcr': yields_dc['lepcr_data'].keys(),
        'phocr': yields_dc['phocr_data'].keys(),
        'qcdcr': yields_dc['qcdcr_data'].keys(),
    }

def addAsymm(e, asymm):
    #print e, asymm
    e_low = math.sqrt(e[0]*e[0] + asymm[0]*asymm[0])
    e_up  = math.sqrt(e[1]*e[1] + asymm[1]*asymm[1])
    return (e_low, e_up)

def sumUncLogNorm(unc_list, p, bin = "", sample = "", type_ = {}):
# syst_histo[systematic][bintype][region][direction]
    log_syst_up_sum = 0.
    log_syst_down_sum = 0.
    log_syst_up_total = 0.
    log_syst_down_total = 0.
    if p == 0: 
        systUnc_rel_pieces[sample][bin] = [1.0, 1.0]
        return [0,0]
    for err, type in zip(unc_list, type_):
        p_up    = err[1]
        p_down  = err[0]
        if p_up == 0 or p_down == 0: continue
        log_syst_up     = p_up / p
        log_syst_down   = p_down / p
        if sample in test_samp and bin in test_bin and debug:
            print "%20s Up: %8.6f Down: %8.6f" % (type, log_syst_up, log_syst_down)
        # If both systematics go the same direction, need to symmetrize
        # Because all the nuisance parameters are log-normal, symmetrize by dividing by the geometric mean
        if ((log_syst_up > 1) and (log_syst_down > 1)) or ((log_syst_up < 1) and (log_syst_down < 1)):
            geometric_mean = np.sqrt(log_syst_up * log_syst_down)
            log_syst_up   /= geometric_mean
            log_syst_down /= geometric_mean
            if sample in test_samp and bin in test_bin and debug and ((log_syst_up > 1 and log_syst_down < 1) or (log_syst_down > 1 and log_syst_up < 1)):
                print "%20s Up: %8.6f Down: %8.6f geometric_mean: %8.6f" % (type, log_syst_up, log_syst_down, geometric_mean)
        #if sample in ['TTZ', 'Rare'] and log_syst_up > 2.:
        #    log_syst_up = 2.0
        # Because all the nuisance parameters are log-normal, sum the log of the ratios in quadrature
        # Sum (the square of the log of) all the ratios that are greater than 1
        # Sum (the square of the log of) all the ratios that are less than 1
        # Then at the end, take the exponential of the square root of each sum to get the total systematic ratio
        if log_syst_up > 1 or log_syst_down < 1:
            log_syst_up_sum     += np.log(log_syst_up)**2
            log_syst_down_sum   += np.log(log_syst_down)**2
        else:
            log_syst_up_sum     += np.log(log_syst_down)**2
            log_syst_down_sum   += np.log(log_syst_up)**2
        log_syst_up_total   = np.exp( np.sqrt(log_syst_up_sum))
        log_syst_down_total = np.exp(-np.sqrt(log_syst_down_sum)) # Minus sign is needed because this is the *down* ratio
    if sample in test_samp and bin in test_bin and debug:
        print bin
        print sample
        print "pred={0}, log_syst_up_total={1}, log_syst_down_total={2}".format(p, log_syst_up_total, log_syst_down_total)
    if bin != "" and sample != "": 
        systUnc_rel_pieces[sample][bin] = [log_syst_down_total, log_syst_up_total]
    return [p - log_syst_down_total*p, log_syst_up_total*p - p]

def sumUnc(unc_list):
    '''Add uncertainties in quadrature.'''
    return math.sqrt(sum(err*err for err in unc_list))

# relUnc[type][bin][sample] : percentage syst. uncertainty of each 'type' per 'bin' per 'sample'
# absUnc[bin][type] : absolute uncertainty per 'bin' of each 'type'
# yields[bin][sample] : predicted bkg yields per bin per sample 
# statUnc[bin] : stat. (MC + data CR) unc. per bin [asymmetric errors]
# systUnc[bin] : syst. unc. per bin
# fullUnc[bin] : full unc. per bin

relUnc={}
absUnc={}
absUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'TTZ':{}, 'Rare':{}}
yields={}
yields_total={}
yields_cr={}
yields_data={}
statUnc={} #asymm
statUnc_pieces={} #asymm 
systUnc={}
systUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'TTZ':{}, 'Rare':{}}
fullUnc={} #asymm
fullUnc_pieces={'ttbarplusw':{}, 'znunu':{}, 'qcd':{}, 'TTZ':{}, 'Rare':{}} #asymm
allVals = {}

def readRelUnc(config_path):
    '''Read in percentage syst. uncertainty from the config files.'''
    for unc_fn in uncfiles:
        print(os.path.join(config_path, unc_fn))
        with open(os.path.join(config_path, unc_fn), 'r') as f:
            for line in f.readlines():
                if line[0]=='#' or line[0]=='%': continue
                try:
                    bin, type_, sample, value = line.split()
                except ValueError:
                    continue
                #if bin not in binlist or sample not in all_samples:
                #    # ignore CR syst., e.g., "bin_onelepcr_250_5_1_0_0"
                #    continue
                if "_Up" in type_:
                    up = float(value)
                    continue
                type = type_.replace("_Down", "")
                if type not in relUnc:
                    relUnc[type] = {}
                if bin not in relUnc[type]:
                    relUnc[type][bin] = {}
                if sample in unc_samples:
                    if "_Down" in type_:
                        down = float(value)
                        relUnc[type][bin][sample] = (down, up)
                    else:
                        sign = 1 if float(value) > 1 else -1
                        up = float(value)
                        down = np.exp(-1 * np.log(up))
                        relUnc[type][bin][sample] = (down, up)

    # for all bin uncs
    if all_bin_unc_file != '':
        with open(os.path.join(config_path, all_bin_unc_file), 'r') as f:
            for line in f.readlines():
                try:
                    bin, type, sample, value = line.split()
                except ValueError:
                    continue
                for samp in unc_samples:
                    if samp not in sample:
                        continue
                    print 'adding unc %s for %s'%(type, samp)                    
                    if type not in relUnc:
                        relUnc[type] = {}
                    # bin=='all' in config file
                    for samp in ['lepcr', 'qcdcr', 'phocr']:
                        for bin in crbinlist[samp]:
                            if bin not in relUnc[type]:
                                relUnc[type][bin] = {sample : (float(value)-1, float(value)-1)}
                    for bin in binlist:
                        if bin not in relUnc[type]:
                            relUnc[type][bin] = {sample : (float(value)-1, float(value)-1)}

    # if a type of unc. is not define for some samples/bins, then fill zero
    for type in relUnc:
        for samp in ['lepcr', 'qcdcr', 'phocr']:
            for bin in crbinlist[samp]:
                if bin not in relUnc[type]:
                    # for bin-specific unc. (e.g., qcd-tf) : set other bins to 0
                    relUnc[type][bin] = {sample: (1.0,1.0) for sample in unc_samples}
                else:
                    for sample in unc_samples:
                        # for sample specific unc.: set other samples to 0
                        if sample not in relUnc[type][bin]:
                            relUnc[type][bin][sample] = (1.0, 1.0)
        for bin in yields_dc['ttbarplusw']:
            if bin not in relUnc[type]:
                # for bin-specific unc. (e.g., qcd-tf) : set other bins to 0
                relUnc[type][bin] = {sample: (1.0,1.0) for sample in unc_samples}
            else:
                for sample in unc_samples:
                    # for sample specific unc.: set other samples to 0
                    if sample not in relUnc[type][bin]:
                        relUnc[type][bin][sample] = (1.0, 1.0)
        for bin in binlist:
            if bin not in relUnc[type]:
                # for bin-specific unc. (e.g., qcd-tf) : set other bins to 0
                relUnc[type][bin] = {sample: (1.0,1.0) for sample in unc_samples}
            else:
                for sample in unc_samples:
                    # for sample specific unc.: set other samples to 0
                    if sample not in relUnc[type][bin]:
                        relUnc[type][bin][sample] = (1.0, 1.0)


def readYields(pred_file):
    ''' Read in predicted bkg yields and the stat. unc. 
    
    pred_file -- input root file 
    '''
    f = rt.TFile(pred_file)
    for hname, sample in zip(graph_names, all_samples):
        h = f.Get(hname)
        for ibin in xrange(0, h.GetNbinsX()):
            bin = binlist[ibin]
            if bin not in yields:
                yields[bin] = {}
                yields_total[bin] = 0.
                statUnc_pieces[bin] = {}
            y = h.GetBinContent(ibin+1)
            e_up = h.GetBinError(ibin+1)
            e_low = h.GetBinError(ibin+1)
            yields[bin][sample] = y
            yields_total[bin]  += y
            if sample == 'rare': statUnc_pieces[bin][sample] = (min(e_up,y), min(e_up,y))  # don't want MC stat unc > 100%
            else :               statUnc_pieces[bin][sample] = (e_low, e_up)
    h = f.Get('hdata')
    for ibin in xrange(0, h.GetNbinsX()):
        bin = binlist[ibin]
        yields_data[bin] = (h.GetBinContent(ibin+1), h.GetBinError(ibin+1))
        #yields_data[bin] = (1, 1)
    # get total pred (w/ asymmetric errors)
    h = f.Get(pred_total_name)
    for ibin in xrange(0, h.GetNbinsX()):
        bin = binlist[ibin]
        e_up = h.GetBinError(ibin+1)
        e_low = h.GetBinError(ibin+1)
        statUnc[bin] = (e_low, e_up)
    f.Close()

def bkgTFPrediction(cr_description, bin, type, sample):
    '''Calculate the prediction using the updown variation in each bin'''
    crproc = 'lepcr' if 'ttbar' in sample else ('qcdcr' if 'qcd' in sample else 'phocr')
    total_up = 0.
    total_dn = 0.
    crdata = 0
    crunit_up = 0.
    srunit_up = 0.
    crother_up = 0.
    crunit_dn = 0.
    srunit_dn = 0.
    crother_dn = 0.
    for entry in cr_description.replace(' ','').split('+'):
        if '*' in entry: sr, cr = entry.split('*')
        else:
            sr = bin
            cr = entry
        if '<' in cr: sr, cr = cr, sr
        sr = sr.strip('<>')
        cr = cr.strip('()')

        #Get total sr unit yeild up and down
        srunit_up += yields_dc[sample][sr][0] * relUnc[type][bin][sample][1]
        srunit_dn += yields_dc[sample][sr][0] * relUnc[type][bin][sample][0]

        #Data doesn't have a fluction
        crdata += yields_dc[crproc + '_data'][cr][0]

        if 'ttbar' in sample: 
            crunit_up += yields_dc[crproc+'_'+sample][cr][0] * relUnc[type][cr][sample][1]
            crunit_dn += yields_dc[crproc+'_'+sample][cr][0] * relUnc[type][cr][sample][0]
        if 'qcd' in sample: 
            crunit_up += yields_dc[crproc+'_'+sample][cr][0] * relUnc[type][cr][sample][1]
            crother_up+=yields_dc[crproc+'_ttbarplusw'][cr][0] * relUnc[type][cr]['ttbarplusw'][1]
            crother_up+=yields_dc[crproc+'_znunu'][cr][0] * relUnc[type][cr]['znunu'][1]
            crother_up+=yields_dc[crproc+'_Rare'][cr][0] * relUnc[type][cr]['Rare'][1]
            crunit_dn += yields_dc[crproc+'_'+sample][cr][0] * relUnc[type][cr][sample][0]
            crother_dn+=yields_dc[crproc+'_ttbarplusw'][cr][0] * relUnc[type][cr]['ttbarplusw'][0]
            crother_dn+=yields_dc[crproc+'_znunu'][cr][0] * relUnc[type][cr]['znunu'][0]
            crother_dn+=yields_dc[crproc+'_Rare'][cr][0] * relUnc[type][cr]['Rare'][0]
        if 'znunu' in sample:
            crunit_up += yields_dc[crproc+'_gjets'][cr][0] * relUnc[type][cr][crproc+'_gjets'][1] if yields_dc[crproc+'_gjets'][cr][0] * relUnc[type][cr][crproc+'_gjets'][1] > 0 else 0.000001
            crother_up+=yields_dc[crproc+'_back'][cr][0] * relUnc[type][cr][crproc+'_back'][1]
            crunit_dn += yields_dc[crproc+'_gjets'][cr][0] * relUnc[type][cr][crproc+'_gjets'][0] if yields_dc[crproc+'_gjets'][cr][0] * relUnc[type][cr][crproc+'_gjets'][0] > 0 else 0.000001
            crother_dn+=yields_dc[crproc+'_back'][cr][0] * relUnc[type][cr][crproc+'_back'][0]

        if sample in test_samp and bin in test_bin and type in test_type and debug:
            print "srunit_up: {0}, crdata: {1}, crunit_up: {2}, crother_up: {3}".format(srunit_up, crdata, crunit_up, crother_up)

    if 'znunu' in sample: 
        total_up = (crdata/(crunit_up + crother_up))*srunit_up
        total_dn = (crdata/(crunit_dn + crother_dn))*srunit_dn
    elif 'qcd' in sample: 
        total_up = np.clip(crdata - crother_up, 1, None)*srunit_up/crunit_up
        total_dn = np.clip(crdata - crother_dn, 1, None)*srunit_dn/crunit_dn
    else:                 
        total_up = crdata*srunit_up/crunit_up
        total_dn = crdata*srunit_dn/crunit_dn

    if crdata == 0: 
        if 'znunu' in sample:
            total_up = yields[bin][sample]
        if 'ttbarplusw' in sample:
            total_up = yields[bin][sample]

    if total_dn < 0:
        total_dn = 0.001
   
    if total_up < total_dn:
        total_up, total_dn = total_dn, total_up

    if sample in ['qcd'] and statUnc_pieces[bin][sample][1] > yields[bin][sample]:
        total_dn, total_up = yields[bin][sample], yields[bin][sample]

    if sample in test_samp and bin in test_bin and type in test_type and debug:
        print("type, {0}. sample: {1}, bin: {2}, Pred Up: {3}, Pred Down: {4}, Pred Nominal: {5}".format(type, sample, bin, total_up, total_dn, yields[bin][sample]))    

    return (total_dn, total_up)

def calcAbsUnc():
    ''' Calculate syst. uncertainty.
    For uncertainties of the same type, add linearly for each bin.
    For uncertainties of different types, add in quadrature for each bin.
    '''
    mergedbins = [bin for bin in binlist if '*' in binMaps['lepcr'][bin]]
    global absUnc
    absUnc = {bin:{} for bin in binlist}
    yields_cr = {bin:{} for bin in binlist}
    for sample in all_samples: absUnc_pieces[sample] = {bin:{} for bin in binlist}
    for bin in binlist:
        absUnc[bin] = {type: [0, 0] for type in relUnc.keys()}
        for sample in all_samples: absUnc_pieces[sample][bin] = {type:[0, 0] for type in relUnc.keys()}
        for type in relUnc:
            for sample in all_samples:
                tempUnc_down = 0.
                tempUnc_up = 0.
                tempUnc_CR_down = 0.
                tempUnc_CR_up = 0.
                if sample not in ['TTZ', 'Rare']:
                    tempUnc_down, tempUnc_up = bkgTFPrediction(binMaps[processMap[sample]][bin], bin, type, sample)
                else:
                    tempUnc_down += relUnc[type][bin][sample][0] * yields[bin][sample]
                    tempUnc_up   += relUnc[type][bin][sample][1] * yields[bin][sample]

                # Add the same type of unc. linearly
                absUnc[bin][type][0]                += tempUnc_down
                absUnc_pieces[sample][bin][type][0] += tempUnc_down
                absUnc[bin][type][1]                += tempUnc_up
                absUnc_pieces[sample][bin][type][1] += tempUnc_up

                if sample in test_samp and bin in test_bin and debug:
                    up = float(absUnc_pieces[sample][bin][type][1]/yields[bin][sample])
                    down = float(absUnc_pieces[sample][bin][type][0]/yields[bin][sample])
                    print "%3s %30s %20s Up: %8.6f Down: %8.6f" % (sample, bin, type, up, down)

    for bin in absUnc:
        # Add different types of unc. in quadrature
        #systUnc[bin] = sumUnc(absUnc[bin].values())
        systUnc[bin] = sumUncLogNorm(absUnc[bin].values(), yields_total[bin], bin, "", absUnc[bin].keys())
        fullUnc[bin] = addAsymm(systUnc[bin], statUnc[bin])
        for sample in all_samples:
            systUnc_pieces[sample][bin] = sumUncLogNorm(absUnc_pieces[sample][bin].values(), yields[bin][sample], bin, sample, absUnc_pieces[sample][bin].keys())
            fullUnc_pieces[sample][bin] = addAsymm(systUnc_pieces[sample][bin], statUnc_pieces[bin][sample])

def writeFullUnc(pred_file):
    ''' Update the input root file, add a hist with total prediction and full uncertainty. '''
    f = rt.TFile(pred_file, 'UPDATE')
    h = TGraphAsymmErrors(f.Get(pred_total_name).Clone('bkgtotal_unc_sr'))
    h_syst = TGraphAsymmErrors(f.Get(pred_total_name).Clone('bkgtotal_syst_unc_sr'))
    h_pieces = {}
    h_syst_pieces = {}
    for hname, sample in zip(graph_names, all_samples):
        h_pieces[sample] = TGraphAsymmErrors(f.Get(hname).Clone(sample+'_unc_sr'))
        h_syst_pieces[sample + "_up"] = TH1F(sample+'_syst_up', sample+'_syst_up', 183, 0, 183)
        h_syst_pieces[sample + "_dn"] = TH1F(sample+'_syst_dn', sample+'_syst_dn', 183, 0, 183)
    print "%30s %10s %16s" % ('bin', 'total pred', 'total unc.')
    for ibin in xrange(0, h.GetN()):
        bin = binlist[ibin]
        val = h.GetY()[ibin]
        e_low, e_up = fullUnc[bin]
        h.SetPointEYlow(ibin, e_low)
        h.SetPointEYhigh(ibin, e_up)
        print "%30s %10.4f +%8.4f -%8.4f" % (bin, val, e_up, e_low)
        allVals[bin] = {'bkg':(val,e_low,e_up)}
        # Test for only syst histograms
        val = h_syst.GetY()[ibin]
        e_low, e_up = systUnc[bin]
        h_syst.SetPointEYlow(ibin, e_low)
        h_syst.SetPointEYhigh(ibin, e_up)
        for sample in all_samples:
            val = yields[bin][sample]
            e_low, e_up = fullUnc_pieces[sample][bin]
            #print "%11s %30s %10.4f +%8.4f -%8.4f" % (sample, bin, val, e_up, e_low)
            h_pieces[sample].SetPointEYlow(ibin, e_low)
            h_pieces[sample].SetPointEYhigh(ibin, e_up)
            allVals[bin][sample] = (val,e_low,e_up)  
            # Test for only syst histograms
            e_low, e_up = systUnc_rel_pieces[sample][bin]
            #if sample in test_samp and bin in test_bin and type in test_type and debug:
            #if 'TTZ' in sample and e_up > 8:
            #    print("%11s %30s %10.4f +%8.4f -%8.4f" % (sample, bin, val, e_up, e_low))
            h_syst_pieces[sample + "_up"].SetBinContent(ibin + 1, e_up)
            h_syst_pieces[sample + "_dn"].SetBinContent(ibin + 1, e_low)
            h_syst_pieces[sample + "_up"].SetBinError(ibin + 1, 0)
            h_syst_pieces[sample + "_dn"].SetBinError(ibin + 1, 0)
    h.Write('bkgtotal_unc_sr', rt.TObject.kOverwrite)
    h.Write('bkgtotal_syst_unc_sr', rt.TObject.kOverwrite)
    for sample in all_samples : 
        h_pieces[sample].Write(sample+'_unc_sr', rt.TObject.kOverwrite)
        h_syst_pieces[sample + "_up"].Write(sample+'_syst_up', rt.TObject.kOverwrite)
        h_syst_pieces[sample + "_dn"].Write(sample+'_syst_dn', rt.TObject.kOverwrite)
    f.Close()

def makeYieldTable(output='pred_sr.tex'):
    ''' Make a Latex-formatted table with each bkg plus unc, total bkg plus unc, and observed data for every bin. '''
    print '\nprinting yield table...\n'
    s = makeTable()
    print s
    with open(output, 'w') as f:
        print >> f, s
   
def makeUncertaintyTable(output='pred_unc.tex'):
    ''' Make a Latex-formatted table with each bkg plus unc, total bkg plus unc, and observed data for every bin. '''
    print '\nprinting yield table...\n'
    s  = beginUncTable()
    header='Search region & \\met [\GeV]  '
    for type in uncMap.keys():
        header += ' & ' + str(uncMap[type])
    unc_header = header + '  \\\\ \n'
    s += unc_header
    s += '\\hline\n'
    s += makeUncTable(unc_header)
    s += endUncTable(135,182)
    print s
    with open(output, 'w') as f:
        print >> f, s
   
def beginTable(table_index, ibini, ibinf):
    '''Add a break between the bins to fit on each page'''
    s  = '\\begin{table*}[!h]\n'
    label='tab:pred-%d'%table_index
    desc='Prediction for bins %d--%d'%(ibini, ibinf)
    s += '\\centering\n'
    s += '\\internallinenumbers\n'
    s += '\\topcaption[' + desc + ']{Observed number of events and SM background predictions in search bins %d--%d.}\n'%(ibini, ibinf)
    s += '\\label{' + label + '}\n'
    s += '\\cmsTable{\n'
    s += '\\renewcommand*{\\arraystretch}{1.25}\n'
    s += '\\begin{scotch}{cccccccr}\n'
    #s += '\\hline\n'
    return s

def beginUncTable():
    col = ''
    '''Add a break between the bins to fit on each page'''
    s  = '\\begin{table}[!p]\n'
    s += '\\begin{center}\n'
    s += '\\resizebox*{1.0\\textwidth}{!}{\n'
    for type in uncMap.keys():
        col += '|c'
    s += '\\begin{tabular}{|c||c|' + col + '|}'
    s += '\\hline\n'
    return s

def endTable():
    '''Add a break between the bins to fit on each page'''
    s  = '\n'
    #s += '\\hline\n'
    s += '\\end{scotch}\n'
    s += '} % End \cmsTable\n'
    s += '\\end{table*}\n'
    return s

def endUncTable(ibini, ibinf):
    '''Add a break between the bins to fit on each page'''
    label='tab:uncert-lm'
    desc='Low \\dm uncertainties bins 0--52'
    if ibini == 53:
        label='tab:uncert-hm-1'
        desc='High \\dm uncertainties bins 53--93'
    elif ibini == 94:
        label='tab:uncert-hm-2'
        desc='High \\dm uncertainties bins 94--134'
    elif ibini == 135:
        label='tab:uncert-hm-3'
        desc='High \\dm uncertainties bins 135--183'
    s  = '\\hline\n'
    s += '\\end{tabular}}\n'
    s += '\\caption[' + desc + ']{The SM uncertainties for Run 2 with \datalumi for each search region in the analysis for bins ' + str(ibini) + '--' + str(ibinf) + '.}\n'
    s += '\\label{' + label + '}'
    s += '\\end{center}\n'
    s += '\\end{table}\n'
    return s


def makeTable():
    ''' Put together the table chunk for the given nj,nb,mtb,nt mega-bin. '''
    sections=[]
    s=''
    ibin=0
    ibini=0
    table_splits = [0, 28, 53, 81, 108, 137, 162, 183]
    table_split_index = 0
    for bin in binlist: 
        if ibin == table_splits[table_split_index]:
            s += beginTable(table_split_index, table_splits[table_split_index], table_splits[table_split_index+1]-1)
            s += table_header
            s += '\\hline\n'

        sec, met= bin.lstrip('bin_').rsplit('_', 1)
        if sec not in sections:
            if ibin == table_splits[table_split_index]:
                s += '\n'
            else:
                s += '[\\cmsTabSkip]\n\n'
            sections.append(sec)
            s += chunkHeader(sec)
        else:
            s += '\n'
        xlow, xhigh = met.lstrip('met_pt').split('to')
        metlabel = r'$>%s$'%xlow if xhigh=='inf' else '$-$'.join([xlow, xhigh])
        s += '%d & '%ibin
        ibin = ibin+1
        s += metlabel
        for bkg in list(all_samples)+['bkg']:
            if bkg == 'Rare': continue
            n, e_low, e_up = allVals[bin][bkg]
            if bkg == 'TTZ':
                n1, e1_low, e1_up = allVals[bin]["Rare"]
                n += n1
                e_low = sumUnc([e_low, e1_low])
                e_up  = sumUnc([e_up, e1_up])
            s += formatPrediction(n,e_low,e_up)
        #print("bin: {0}, allVals: {1}".format(bin, allVals[bin]))
        n, e = yields_data[bin]
        s += ' & ' + str(int(n))
        s += ' \\\\'
        if ibin in table_splits:
            s += endTable()
            s += '\n'*8
            table_split_index += 1
    return s

def makeUncTable(unc_header):
    ''' Put together the table chunk for the given nj,nb,mtb,nt mega-bin. '''
    sections=[]
    s=''
    ibin=0
    ibini=0
    for bin in binlist: 
        sec, met= bin.lstrip('bin_').rsplit('_', 1)
        if sec not in sections:
            sections.append(sec)
            s += chunkUncHeader(sec)
        xlow, xhigh = met.lstrip('met_pt').split('to')
        metlabel = r'$>%s$'%xlow if xhigh=='inf' else '$-$'.join([xlow, xhigh])
        s += '%d & '%ibin
        ibin = ibin+1
        s += metlabel
        for type in uncMap.keys():
            e_low, e_up = absUnc[bin][type]
            n = yields_total[bin]
            s += formatUncertainty(n,e_low,e_up)
        s += ' \\\\ \n'
        if ibin == 53 or ibin == 94 or ibin == 135:
            s += endUncTable(ibini, ibin-1)
            s += beginUncTable()
            s += unc_header
            ibini=ibin
    return s

# formats the prediction nEvents +/- error
def formatPrediction(n,e_low,e_up):
    assert e_low >= 0 and e_up >= 0 and n >= 0

    if e_up > 0: log10_e_up = np.log10(e_up)
    else:        log10_e_up = -2

    if e_low > 0: log10_e_low = np.log10(e_low)
    else:         log10_e_low = -2

    place = int(np.ceil(max(log10_e_up, log10_e_low, 0) - 2))

    n_round = round(n, -place)
    e_low_round = round(e_low, -place)
    e_up_round = round(e_up, -place)

    unc_ave = (e_up_round + e_low_round)/2.
    if unc_ave > 0:
        unc_frac_diff = abs(e_up_round - e_low_round) / unc_ave
        if unc_frac_diff < 0.05:
            e_up_round = round(unc_ave, -place)
            e_low_round = round(unc_ave, -place)

    n_format_str = '%%.%df'%(max(0, -place))
    e_format_str = '%%+.%df'%(max(0, -place))

    n_str = n_format_str%n_round
    e_low_str = e_format_str%(-e_low_round)
    e_up_str = e_format_str%e_up_round

    if n_round == 0:
        if e_up_round == 0:
            return ' & $< 0.01$ '
        else:
            return ' & $< %s$'%e_up_str[1:]
    else:
        if e_low_round == e_up_round:
            return ' & $%s \\pm %s$ '%(n_str, e_up_str[1:])
        else:
            return ' & $%s\,^{%s}_{%s}$ '%(n_str, e_up_str, e_low_str)

# formats the prediction nEvents +/- error
def formatUncertainty(n,e_low,e_up):
    unc = (((e_up/n) - 1) + (1 - (e_low/n)))/2.*100
    out = ''
    if unc>=10:
        unc  = str(int(round(unc,0)))
    elif unc>=1:
        unc  = str(round(unc,1))
    else:
        unc  = str(round(unc,2))
    if unc=='0.0':
        return ' & $<$0.01 \% '
    out = ' & $ %s' %(unc)
    out += ' \% $ '
    return out


# puts together the bin header for bins of nJets, mtb, nTop (no selection on nB)
def chunkHeader(sec):
    ''' Put together the mega-bin chunk header. '''
    cats = sec.split('_')
    labs = [labelMap[c] for c in cats if labelMap[c] != '']
    ncolumn = len(all_samples)+3
    s  = ''
    #s += '\\hline\n'
    s += '\\multicolumn{'+str(ncolumn)+'}{c}{'
    s += ', '.join(labs)
    s += '} \\\\[\\cmsTabSkip] \n'
    #s += '\\hline\n' 
    return s

def chunkUncHeader(sec):
    ''' Put together the mega-bin chunk header. '''
    cats = sec.split('_')
    labs = [labelMap[c] for c in cats]
    ncolumn = len(uncMap.keys())+2
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
    if args.printTable : 
        makeYieldTable()
        makeUncertaintyTable()

if __name__=='__main__':
    main()
