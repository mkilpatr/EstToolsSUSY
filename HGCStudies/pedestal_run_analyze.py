#1/user/bin/env python
import ROOT
ROOT.PyConfig.IgnoreCommandLineOptions = True
import math
import numpy as np
import os

def loadHisto(filename,hname):
    tf = ROOT.TFile.Open(filename)
    hist = []
    for h1 in hname:
    	hist_ = tf.Get(h1)
    	#hist_.SetDirectory(0)
    	hist.append(hist_)
    tf.Close()
    return hist

def pedestal_run_analyze(inputDir):
    inputDir = inputDir
    histNames = {"chip", "channel", "channeltype", 
                 "adc_median", "adc_iqr", "adc_mean", "adc_stdd", 
                 "tot_median", "tot_iqr", "tot_mean", "tot_stdd", "tot_efficiency", "tot_efficiency_error", 
                 "toa_median", "toa_iqr", "toa_mean", "toa_stdd", "toa_efficiency", "toa_efficiency_error"}

    files = os.listdir(inputDir)
    for f in files:
        if "root" not in f: continue

        hists = {}
        for n in histNames:
            hists[n] = loadHisto(inputDir + "/" + f, n)

        print(hists)
