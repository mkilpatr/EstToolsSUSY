#!/bin/bash

runmacro=$1
outputdir=$2
scramdir=$3
outdir=${4}
scram=${5}
location=${6}
sysname=${7}
bins=${8}

workdir=`pwd`
cmssw=${scramdir##*/}

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

xrdcp root://cmseos.fnal.gov//store/user/$(whoami)/${CMSSW}_${outdir}.tgz .
tar -xf ${CMSSW}_${outdir}.tgz
rm ${CMSSW}_${outdir}.tgz
echo $pwd
ls

cd ${_CONDOR_SCRATCH_DIR}
pwd
cd ${CMSSW}/src/EstToolsSUSY/HGCStudies
echo $outdir

sed -i -e "s/Gaussian_PCBplus000_Kaptonplus000_senTokap185_midSensor/$bins/g" ModuleStudies.C

ulimit -s unlimited
cd $location
root -l -b -q $runmacro+
xrdcp -np -r $bins root://cmseos.fnal.gov//store/user/mkilpatr/13TeV/${outdir}
ls -a

status=`echo $?`
echo "Status = $status"

exit $status
