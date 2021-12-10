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
mkdir -p diboson/ww
mv *WW* diboson/ww/.
mkdir -p diboson/wz
mv *WZ* diboson/wz/.
mkdir -p diboson/zz
mv *ZZ* diboson/zz/.
mkdir -p wjets
mv *WJetsToLNu* wjets/.
mkdir -p dyll
mv *DYJetsToLL* dyll/.
cd -

haddnano ggHHto2b2tau_tree.root `xrdfsls -u ${files}/ggHHto2b2tau | grep '\.root'`
xrdcp ggHHto2b2tau_tree.root root://cmseos.fnal.gov/${files}/.
rm -f ggHHto2b2tau_tree.root
haddnano ggHto2tau_tree.root `xrdfsls -u ${files}/ggHto2tau | grep '\.root'`
xrdcp ggHto2tau_tree.root root://cmseos.fnal.gov/${files}/.
rm -f ggHto2tau_tree.root
haddnano vbfHto2tau_tree.root `xrdfsls -u ${files}/vbfHto2tau | grep '\.root'`
xrdcp vbfHto2tau_tree.root root://cmseos.fnal.gov/${files}/.
rm -f vbfHto2tau_tree.root

haddnano ww_tree.root `xrdfsls -u ${files}/diboson/ww | grep '\.root'`
haddnano wz_tree.root `xrdfsls -u ${files}/diboson/wz | grep '\.root'`
haddnano zz_tree.root `xrdfsls -u ${files}/diboson/zz | grep '\.root'`
haddnano wjets_tree.root `xrdfsls -u ${files}/wjets | grep '\.root'`
haddnano dyll_tree.root `xrdfsls -u ${files}/dyll | grep '\.root'`
haddnano qcd_tree.root `xrdfsls -u ${files}/qcd | grep '\.root'`

haddnano diboson_tree.root ww_tree.root wz_tree.root zz_tree.root

xrdcp ww_tree.root root://cmseos.fnal.gov/${files}/.
xrdcp wz_tree.root root://cmseos.fnal.gov/${files}/.
xrdcp zz_tree.root root://cmseos.fnal.gov/${files}/.
xrdcp diboson_tree.root root://cmseos.fnal.gov/${files}/.
xrdcp wjets_tree.root root://cmseos.fnal.gov/${files}/.
xrdcp dyll_tree.root root://cmseos.fnal.gov/${files}/.
xrdcp qcd_tree.root root://cmseos.fnal.gov/${files}/.
rm -f diboson_tree.root ww_tree.root wz_tree.root zz_tree.root wjets_tree.root dyll_tree.root qcd_tree.root
