#!/usr/bin/env python
import os
import sys
import argparse

parser = argparse.ArgumentParser(description='Process config file')
parser.add_argument("-s", "--submit", dest="submit", default="submitall", help="Name of shell script to run for job submission. [Default: submitall]")
parser.add_argument("-p", "--pathtomacro", dest="path", default="..", help="Path to directory with run macro and configuration file. [Default: \"../\"]")
parser.add_argument("-m", "--runmacro", dest="macro", default="ModulesStudies.C", help="ROOT macro to run. [Default: ModulesStudies.C]")
parser.add_argument("-c", "--conf", dest="config", default="", help="a conf file for all macros [Default: ""]")
parser.add_argument("-n", "--sysname", dest="sysname", default="Tolerances", help="type of uncertainty calc")
parser.add_argument("-o", "--outdir", dest="outdir", default="${PWD}/plots", help="Output directory for plots, [Default: \"${PWD}/plots\"]")
parser.add_argument("-r", "--runscript", dest="script", default="runjobs", help="Shell script to be run by the jobs, [Default: runjobs]")
parser.add_argument("-t", "--submittype", dest="submittype", default="condor", choices=["interactive","lsf","condor"], help="Method of job submission. [Options: interactive, lsf, condor. Default: condor]")
parser.add_argument("-q", "--queue", dest="queue", default="1nh", help="LSF submission queue. [Default: 1nh]")
parser.add_argument("-a", "--tar", dest="tar", default="", help="add the tar command to the submit script")
parser.add_argument("-l", "--location", dest="location", default=".", help="move to location of files")
parser.add_argument("--output-suffix", dest="suffix", default="_tree.root", help="Suffix of output file. [Default: %(default)s. Use '.json' with dumpJSON.C.]")
parser.add_argument("--jobdir", dest="jobdir", default="jobs", help="Job dir. [Default: %(default)s]")
parser.add_argument("--path-to-rootlogon", dest="rootlogon", default="../../rootlogon.C", help="Path to the root logon file. [Default: %(default)s]")
parser.add_argument("-b", "--bins", dest="bins", default="srbins.conf", help="List of signal files. [Default: T2tt_signals.conf]")
#parser.print_help()
args = parser.parse_args()

types = []
state = 0
snum = 0
samples = []
macro = []
sysname = []
bins = []
with open((args.bins),"r") as f :
    for line in f:
        content = os.path.splitext(line)[0]
        bins.append(content)

bins = [x.strip() for x in bins]

if not args.config == "":
    with open((args.path+"/"+args.config),"r") as f :
        for line in f :
            content = os.path.splitext(line)[0]
	    macro.append(content+".C")
	    sysname.append(content)
else:
    macro.append(args.macro)
    sysname.append(args.sysname)

os.system("mkdir -p %s" % args.jobdir)

memory = 2000

print "Creating submission file: ",args.submit+".sh"
script = open(args.submit+".sh","w")
script.write("""#!/bin/bash 
outputdir={outdir}
runmacro={macro}
location={location}
sysname={sysname}
source tarCMSSW_hgc.sh $outputdir
 
eosmkdir -p /eos/uscms/store/user/mkilpatr/13TeV/$outputdir
   
echo "$runscript $runmacro $workdir $outputdir"    
""".format(outdir=args.outdir, pathtomacro=args.path, macro=args.macro, location=args.location, sysname=args.sysname))
        
for i in xrange(len(macro)):
    print(sysname[i])
    for b in xrange(len(bins)):
        scriptSep = open(os.path.join(args.jobdir,"submitSep_{}_{}.sh".format(sysname[i], bins[b])),"w")
        scriptSep.write("""#!/bin/bash
outputdir={outdir}
runmacro={macro}
location={location}
sysname={sysname}
bins={bins}
""".format(outdir=args.outdir, pathtomacro=args.path, macro=macro[i], location=args.location, sysname=sysname[i], bins=bins[b]))
        if args.submittype == "lsf" or args.submittype == "condor" :
            scriptSep.write("""
workdir=$CMSSW_BASE
scram=$SCRAM_ARCH
runscript={runscript}{stype}.sh
        
if [ ! "$CMSSW_BASE" ]; then
  echo "-------> error: define cms environment."
  exit 1
fi
        
cp {rootlogon} $workdir
cp {pathtomacro}/{location}/$runmacro $workdir
""".format(pathtomacro=args.path,location=args.location,runscript=args.script,stype=args.submittype,rootlogon=args.rootlogon))

        if args.submittype == "interactive" :
            scriptSep.write("""root -l -q -b {rootlogon} {pathtomacro}/$runmacro+\()\n""".format(
            rootlogon=args.rootlogon, pathtomacro=args.path, 
            ))
        elif args.submittype == "condor" :
            os.system("mkdir -p %s/logs" % args.outdir)
            jobscript = open(os.path.join(args.jobdir,"submit_{}_{}.sh".format(sysname[i], bins[b])),"w")
            outputname = ''
            jobscript.write("""
cat > submit.cmd << EOF
universe                = vanilla
Executable              = {runscript}{stype}.sh
Arguments               = {macro} . {workdir} {outdir} {scram} {location} {sysname} {bins}
Output                  = logs/{sysname}_{bins}.out
Error                   = logs/{sysname}_{bins}.err
Log                     = logs/{sysname}_{bins}.log
x509userproxy           = 
request_memory 		= {memory}
initialdir              = {outdir}
Should_Transfer_Files   = YES
transfer_input_files    = {workdir}/{macro},{workdir}/rootlogon.C
transfer_output_files   = {outname}
WhenToTransferOutput    = ON_EXIT
Queue
EOF

  condor_submit submit.cmd;
  rm submit.cmd""".format(
        runscript=args.script, stype=args.submittype, macro=macro[i], sysname=sysname[i], workdir="${CMSSW_BASE}", outdir=args.outdir, outname=outputname, scram="${SCRAM_ARCH}", location=args.location, memory=memory, bins=bins[b]
        ))
        jobscript.close()
        scriptSep.write("./{jobdir}/submit_{name}_{bins}.sh\n".format(jobdir=args.jobdir, name=sysname[i], bins=bins[b]))
        script.write("./{jobdir}/submitSep_{name}_{bins}.sh\n".format(jobdir=args.jobdir, name=sysname[i], bins=bins[b]))
        os.system("chmod +x %s/submit_%s_%s.sh" %(args.jobdir, sysname[i], bins[b]))
        os.system("chmod +x %s/submitSep_%s_%s.sh" %(args.jobdir, sysname[i], bins[b]))
        
       
    
script.close()
os.system("chmod +x %s.sh" % args.submit)

print "Done!"
