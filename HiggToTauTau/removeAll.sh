#!/bin/bash

eosloc=$1
declare -a regionArray=("tot" "ehad" "emu" "hadhad" "muhad")

for region in ${regionArray[@]}; do
	echo eosrm -r /store/user/mkilpatr/13TeV/${eosloc}_${region}
	eosrm -r /store/user/mkilpatr/13TeV/${eosloc}_${region}
done
