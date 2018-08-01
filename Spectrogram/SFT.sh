#!/bin/sh

fNameIn=$1
tmp=${fNameIn%.*}
fNameOut="SFTresult${tmp}"

#echo $fNameIn
#echo $fNameOut

./SFT $fNameIn
gnuplot -e "fileName='$fNameOut'" draw.plt
