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

if not os.path.exists(args.saveDir):
    os.makedirs(args.saveDir)

def write_json(data):
    fout.write((json.dumps(data, sort_keys=False)+'\n').encode('utf-8'))

def writeTot_json(data):
    ftot.write((json.dumps(data, sort_keys=False)+'\n').encode('utf-8'))

def open_json(jsonfilename):
    tweets = []
    with gzip.open(jsonfilename,'r') as fin:        
        for line in fin:        
            if line == "\n": continue
            write_json(json.loads(line))
            if any(x in jsonfilename for x in ['dyll', 'diboson', 'wjets']):
                writeTot_json(json.loads(line))

print(Dist)

for type in ['genHiggs', 'genTaus']:
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
        fout = gzip.open(args.saveDir + "/" + type + "_" + d + ".json.gz", 'w')

        print(eosDir + d + "/" + onlyFiles[0])
        for idx, sd in enumerate(onlyFiles):
            open_json(eosDir + d + "/" + sd)

