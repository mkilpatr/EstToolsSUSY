#!/bin/bash
cmsenv
#haddnano tW_tree.root `xrdfsls -u /store/user/mkilpatr/13TeV/nanoaod_all_skim_v2/tW | grep '\.root'`
files=$1
cd /eos/uscms/$files
mkdir ggHto2tau
mv *GluGluHToTauTau* ggHto2tau/.
mkdir ggHHto2b2tau
mv *GluGluToHHTo2B2Tau* ggHHto2b2tau/.
mkdir vbfHto2tau
mv *VBFHToTauTau* vbfHto2tau/.
mkdir -p diboson
mv *WW* diboson/.
mv *WZ* diboson/.
mv *ZZ* diboson/.
mkdir -p wjets
mv *WJetsToLNu* wjets/.
mkdir -p dyll
mv *DYJetsToLL* dyll/.
mkdir -p qcd
mv *QCD_HT* qcd/.
cd -

