#!/bin/bash

runmacro=$1
outputdir=$2
scramdir=$3
outdir=${4}
scram=${5}

workdir=`pwd`
cmssw=${scramdir##*/}
export USER = $(whoami)

echo $(whoami)
echo `hostname`
echo "${_CONDOR_SCRATCH_DIR}"
echo "scramdir: $scramdir"
echo "workdir: $workdir"
echo "args: $*"
echo $cmssw
echo $scram
ls -l

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=$scram
eval `scramv1 project CMSSW $cmssw`
cd ${cmssw}/src/
eval `scramv1 runtime -sh`
scramv1 b ProjectRename
echo "CMSSW: "$CMSSW_BASE
cd ../../
CMSSW=${CMSSW_BASE##*/}

xrdcp root://cmseos.fnal.gov//store/user/$(whoami)/${CMSSW}.tgz .
tar -xf ${CMSSW}.tgz
rm ${CMSSW}.tgz
echo $pwd
ls

cd ${_CONDOR_SCRATCH_DIR}
pwd
cd CMSSW_9_4_10/src/AnalysisMethods/EstTools/SUSYNano19/systematics/
echo $outdir

root -l -b -q $runmacro+
xrdcp -np values*.conf root://cmseos.fnal.gov//store/user/$(whoami)/13TeV/${outdir}/.
ls -a

status=`echo $?`
echo "Status = $status"

exit $status
