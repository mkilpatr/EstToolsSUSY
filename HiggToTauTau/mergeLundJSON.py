import os
import io
import gzip
import json
import argparse
import re

parser = argparse.ArgumentParser(
        description='Produce or print limits based on existing datacards')
parser.add_argument("-d", "--dir", dest="baseDir", default='nanoAOD_diHiggs',
                         help="Base directory where files are located on EOS")
parser.add_argument("-s", "--save", dest="saveDir", default='diHiggsJSON',
                         help="Directory where new merged files should be locally saved")
args = parser.parse_args()

eosDir = "/eos/uscms/store/user/mkilpatr/13TeV/" + args.baseDir + "/"
Dist = os.listdir(eosDir)


samples = {
'GluGluToHHTo2B2Tau_node_SM_TuneCP5_PSWeights_13TeV': [0.04457, 399983, 17],
'GluGluToHHTo2B2Tau_node_2_TuneCP5_PSWeights_13TeV': [0.01008, 315961, 39],
'GluGluToHHTo2B2Tau_node_3_TuneCP5_PSWeights_13TeV': [0.5599, 384985, 15],
'GluGluToHHTo2B2Tau_node_4_TuneCP5_PSWeights_13TeV': [12.17, 399988, 12],
'GluGluToHHTo2B2Tau_node_5_TuneCP5_PSWeights_13TeV': [0.03537, 399983, 17],
'GluGluToHHTo2B2Tau_node_6_TuneCP5_PSWeights_13TeV': [0.8265, 387985, 15],
'GluGluToHHTo2B2Tau_node_7_TuneCP5_PSWeights_13TeV': [15.95, 344981, 19],
'GluGluToHHTo2B2Tau_node_8_TuneCP5_PSWeights_13TeV': [1375.0, 399983, 17],
'GluGluToHHTo2B2Tau_node_9_TuneCP5_PSWeights_13TeV': [0.0328, 394964, 36],
'GluGluToHHTo2B2Tau_node_10_TuneCP5_PSWeights_13TeV': [268.6, 399977, 23],
'GluGluToHHTo2B2Tau_node_11_TuneCP5_PSWeights_13TeV': [0.7869, 399978, 22],
'GluGluToHHTo2B2Tau_node_12_TuneCP5_PSWeights_13TeV': [1348.0, 399980, 20],
'GluGluHToTauTauUncorrelatedDecay_Filtered_M125_TuneCP5_13TeV': [5.261, 20117451, 41567],
'VBFHToTauTauUncorrelatedDecay_Filtered_M125_TuneCP5_13TeV': [1.043, 24049754, 15429],
'WWTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8': [45.68, 3812178, 870958],
'WWTo2L2Nu_DoubleScattering_13TeV-pythia8': [0.1703, 871500, 0],
'WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8': [47.73, 3801607, 7193],
'WZTo1L1Nu2Q_13TeV_amcatnloFXFX_madspin_pythia8': [10.73, 15075066, 3826403],
'WZTo2L2Q_13TeV_amcatnloFXFX_madspin_pythia8': [5.606, 22621041, 5572607],
'WZTo3LNu_TuneCP5_13TeV-amcatnloFXFX-pythia8': [5.052, 17893491, 4104096],
'WZTo1L3Nu_13TeV_amcatnloFXFX_madspin_pythia8': [3.054, 1305208, 384856],
'ZZTo2L2Q_13TeV_TuneCP5_amcatnloFXFX_madspin_pythia8': [3.703, 23176603, 5114699],
'ZZTo4L_TuneCP5_13TeV-amcatnloFXFX-pythia8': [0.003879, 22450654, 3920571],
'WJetsToLNu_HT-70To100_TuneCP5_13TeV': [1292.0, 28072273, 11971],
'WJetsToLNu_HT-100To200_TuneCP5_13TeV': [1395.0, 29504734, 16424],
'WJetsToLNu_HT-200To400_TuneCP5_13TeV': [407.9, 25446044, 22889],
'WJetsToLNu_HT-400To600_TuneCP5_13TeV': [57.48, 5924335, 8366],
'WJetsToLNu_HT-600To800_TuneCP5_13TeV': [12.87, 19735538, 35756],
'WJetsToLNu_HT-800To1200_TuneCP5_13TeV': [5.366, 8382457, 20230],
'WJetsToLNu_HT-1200To2500_TuneCP5_13TeV': [1.074, 7602766, 31183],
'WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV': [0.008001, 3232796, 41184],
'DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV': [146.5, 10015512, 4172],
'DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV': [160.7, 11524320, 6190],
'DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV': [48.63, 11216164, 9723],
'DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV': [6.993, 9629913, 13271],
'DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV': [1.761, 8759728, 16577],
'DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV': [0.8021, 3130052, 8077],
'DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV': [0.1937, 534089, 2327],
'DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV': [0.003514, 421382, 5669],
'QCD_HT50to100_TuneCP5_13TeV-madgraphMLM-pythia8': [185300000.0, 38753958, 272],
'QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8': [23590000.0, 93962673, 9705],
'QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8': [1551000.0, 54270554, 18888],
'QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8': [323400.0, 54459006, 30365],
'QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8': [30140.0, 54933452, 48225],
'QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8': [6344.0, 48098739, 59999],
'QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8': [1092.0, 15099835, 28588],
'QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8': [99.76, 10921419, 33668],
'QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8': [20.35, 5445111, 30566]
}

nEvents = 20000
MaxEvents = {
  'train': nEvents,
  'test': 2*nEvents,
  'valid': 4.5*nEvents
}
totalEvents = 0
totalXsec = 0.
for key, listOfValues in samples.items():
    if any(x in key for x in ['DYJetsToLL', 'WW', 'WZ', 'ZZ', 'WJets', 'QCD']):
        totalXsec += listOfValues[0]
        totalEvents += listOfValues[1]
        totalEvents -= listOfValues[2]

if not os.path.exists(args.saveDir):
    os.makedirs(args.saveDir)
    os.makedirs(args.saveDir+"/train/")
    os.makedirs(args.saveDir+"/test/")
    os.makedirs(args.saveDir+"/valid/")

def write_json(fout, data):
    fout.write((json.dumps(data, sort_keys=False)+'\n').encode('utf-8'))

def writeTot_json(data):
    ftot.write((json.dumps(data, sort_keys=False)+'\n').encode('utf-8'))

def gz_size(fname):
    with gzip.open(fname, 'rb') as f:
        return f.seek(0, whence=2)

def fileName(fname):
    p = re.search(r'_[0-9]+\.json\.gz', fname)
    g = fname[0:fname.find('_')]
    n = fname.replace(p.group(), '').replace(g + "_", '')
    return n

def open_json(ftrain, ftest, fvalid, jsonfilename, fname, maxEvents):
    if gz_size(jsonfilename):
        eventList = samples[fileName(fname)]
        eventFrac, xsecFrac = float((eventList[1] - eventList[2])/totalEvents), float(eventList[0]/totalXsec)
        with gzip.open(jsonfilename,'r') as fin:        
            for line in fin:        
                if line == "\n": continue
                if maxEvents < MaxEvents["train"]: write_json(ftrain, json.loads(line))
                elif maxEvents >= MaxEvents["train"] and maxEvents < MaxEvents["test"]: write_json(ftest, json.loads(line))
                elif maxEvents >= MaxEvents["test"] and maxEvents < MaxEvents["valid"]: write_json(fvalid, json.loads(line))
                else: break

                if any(x in jsonfilename for x in ['dyll', 'diboson', 'wjets', 'qcd']):
                    if maxEvents/totalEvents < eventFrac and maxEvents/totalEvents < xsecFrac:
                        writeTot_json(json.loads(line))
                maxEvents+=1
    return maxEvents, fileName(fname)

for type in ['genHiggs']:
    ftot = gzip.open(args.saveDir + "/" + type + "_bkg.json.gz", 'w')
    for d in Dist:
        if "json" in d: continue
        subDist = os.listdir(eosDir + d)
        onlyFiles = []
        for sd in subDist:
            if os.path.isdir(eosDir + d + "/" + sd): continue
            if "json" in sd:
                if type in sd:
                    onlyFiles.append(sd)
                elif type not in sd and 'gen' not in type:
                    onlyFiles.append(sd)
    
        ftrain = gzip.open(args.saveDir + "/train/" + type + "_" + d + ".json.gz", 'w')
        ftest = gzip.open(args.saveDir + "/test/" + type + "_" + d + ".json.gz", 'w')
        fvalid = gzip.open(args.saveDir + "/valid/" + type + "_" + d + ".json.gz", 'w')
        if(len(onlyFiles) > 0): print(eosDir + d + "/" + onlyFiles[0])
        maxEvents = 0
        name = ''
        for idx, sd in enumerate(onlyFiles):
            buff = fileName(sd)
            if name != buff:
                maxEvents = 0
            maxEvents, name = open_json(ftrain, ftest, fvalid, eosDir + d + "/" + sd, sd, maxEvents)
