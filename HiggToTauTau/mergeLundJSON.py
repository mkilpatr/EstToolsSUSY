import os
import json
import argparse
import re

parser = argparse.ArgumentParser(
        description='Produce or print limits based on existing datacards')
parser.add_argument("-d", "--dir", dest="baseDir", default='nanoAOD_diHiggs',
                         help="Search region to use when running the maximum likelihood fit. [Default: Search region with 183]")
args = parser.parse_args()


# json file witll_BkgPred_v2e bkg predictions and signal yields
def write_json(data, filename=args.baseDir + '/' + Dist[0] + '.json.gz'):
    with open(filename,'w') as f:
    	json.dump(data, f, indent=2, ensure_ascii=False)

eosDir = "/eos/uscms/store/user/mkilpatr/13TeV/" + args.baseDir + "/"
Dist = os.listdir(eosDir)

os.makedirs(os.path.join(args.baseDir, "diHiggsJSON"))

with open("/eos/uscms/store/user/mkilpatr/13TeV/" + args.baseDir + "/" + Dist[0] + ".json.gz", "a+") as new:
    newData = json.load(new)

for d in Dist:
    with open(eosDir+d+".json.gz", "r") as lepcr:
        lep_insert = json.load(lepcr)

write_json(newData)

