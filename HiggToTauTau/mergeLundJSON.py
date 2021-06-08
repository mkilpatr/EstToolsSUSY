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
parser.add_argument("-n", "--nEvents", dest="nEvents", default=500000,
                         help="Directory where new merged files should be locally saved")
args = parser.parse_args()

eosDir = "/eos/uscms/store/user/mkilpatr/13TeV/" + args.baseDir + "/"
Dist = os.listdir(eosDir)

if not os.path.exists(os.path.join(args.baseDir, args.saveDir)):
    os.makedirs(os.path.join(args.baseDir, args.saveDir))

def write_json(data):
    fout.write((json.dumps(data, sort_keys=False)+'\n').encode('utf-8'))

def open_json(jsonfilename, nEvents):
    tweets = []
    with gzip.open(jsonfilename,'r') as fin:        
        for line in fin:        
            tweets.append(json.loads(line))
            nEvents+=1
            if nEvents > args.nEvents: break

    return tweets, nEvents

print(Dist)



for d in Dist:
    nEvents = 0
    if "json" in d: continue
    subDist = os.listdir(eosDir + d)
    for type in ['genHiggs', 'otherMatch']:
        onlyFiles = []
        for sd in subDist:
            if os.path.isdir(eosDir + d + "/" + sd): continue
            if "json" in sd:
                if type in sd:
                    onlyFiles.append(sd)
                elif type not in sd and 'gen' not in type:
                    onlyFiles.append(sd)
        fout = gzip.open(os.path.join(args.baseDir, args.saveDir) + "/" + type + "_" + d + ".json.gz", 'w')

        print(eosDir + d + "/" + onlyFiles[0])
        newData = []
        for idx, sd in enumerate(onlyFiles):
            json_insert, nEvents = open_json(eosDir + d + "/" + sd, nEvents)
            if idx == 0: newData = json_insert
            else:        newData.append(json_insert)
            if nEvents > args.nEvents: break

        write_json(newData)

