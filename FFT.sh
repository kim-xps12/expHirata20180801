#!/bin/sh

fNameIn=$1
tmp=${fNameIn%.*}
fNameOut="FFTresult${tmp}"

#echo $fNameIn
#echo $fNameOut

./FFT $fNameIn
gnuplot -e "fileName='$fNameOut'" draw.plt
