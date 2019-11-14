#!/bin/bash

CMSSW=${CMSSW_BASE##*/}
DIR=$(pwd)

cd $CMSSW_BASE
cd ..
eosrm /store/user/${USER}/${CMSSW}.tgz
tar --exclude-caches-all -zcf ${CMSSW}.tgz $CMSSW --exclude="$CMSSW/src/AnalysisMethods/macros/*" --exclude="$CMSSW/src/AnalysisBase/*" --exclude="$CMSSW/src/.git/*" --exclude="*.root" --exclude="*.pdf" --exclude="*.png" --exclude="*.log" --exclude="*.err" --exclude="*.out" --exclude="*.txt" --exclude="*.tex" --exclude="*.sh" --exclude="AnalysisTools/*" --exclude="PhysicsTools/*.root" --exclude="AnalysisMethods/EstTools/datacard_moriond17/*" --exclude="$CMSSW/src/AnalysisMethods/EstTools/SUSYNano19/LLB/*" --exclude="$CMSSW/src/AnalysisMethods/EstTools/SUSYNano19/QCD/*"
xrdcp -f ${CMSSW}.tgz root://cmseos.fnal.gov//store/user/${USER}/${CMSSW}.tgz
rm -f ${CMSSW}.tgz
cd $DIR
