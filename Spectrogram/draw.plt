set terminal x11

DATANAME = fileName.".txt"
OUTPUTNAME = fileName.".pdf"

set grid

do for[mode = 0:1]{

    if(mode==0){
        set terminal x11
    }
    else{
        set terminal pdf
        set output OUTPUTNAME
    }

    set title DATANAME
    set nokey
    set xlabel "time[ms]"
    set ylabel "Frequecy[Hz]"
    set cblabel "Power[dB]"
    plot DATANAME using 1:2:3 lc palette
}
set terminal x11
