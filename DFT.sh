#!/bin/sh

fNameIn=$1
tmp=${fNameIn%.*}
fNameOut="DFTresult${tmp}"

#echo $fNameIn
#echo $fNameOut

./DFT $fNameIn
gnuplot -e "fileName='$fNameOut'" draw.plt
