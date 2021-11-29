#!/bin/bash

eosloc=$1
savedir=$2

declare -a regionArray=("tot" "ehad" "emu" "hadhad" "muhad")

for region in ${regionArray[@]}; do
	#. ./hadd_samples_json.sh /store/user/mkilpatr/13TeV/${eosloc}_${region}
	python3 mergeLundJSON.py -d ${eosloc}_${region} -s ${savedir}/${region}
done
