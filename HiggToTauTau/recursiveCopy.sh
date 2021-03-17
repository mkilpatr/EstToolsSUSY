#!/bin/bash

input=$1
output=$2

while read p; do
	xrdcp root://cmseos.fnal.gov/$p $output
done < ${input}
