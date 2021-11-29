import os
import json
import argparse
import re

from pedestal_run_analyze import pedestal_run_analyze

parser = argparse.ArgumentParser(
        description='Produce or print limits based on existing datacards')
parser.add_argument("-d", "--dir", dest="baseDir", default='TestDir',
                         help="")
parser.add_argument("-n", "--name", dest="moduleName", default='module',
                         help="")
args = parser.parse_args()

eosDir = "./" + args.baseDir + "/"
Dist = os.listdir(eosDir)

if not os.path.exists(os.path.join(args.baseDir, "ModuleGrade")):
    os.makedirs(os.path.join(args.baseDir, "ModuleGrade"))

for d in Dist:
    subDist = os.listdir(eosDir + "/" + d)
    for sd in subDist:
        #if "pedestal_scan" in d: pedestal_scan_analyze()
        if "pedestal_run" in d: pedestal_run_analyze(eosDir + "/" + d + "/" + sd)
        #if "injection_scan" in d: injection_scan_analyze()
        #if "phase_scan" in d: phase_scan_analyze()
        #if "sampling_scan" in d: sampling_scan_analyze()
        #if "vrefinv_scan" in d: vrefinv_scan_analyze()
        #if "IVCurve" in d: ivcurve_analyze()
