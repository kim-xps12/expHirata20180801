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
    set xlabel "Frequency[Hz]"
    set ylabel "Level[dB]"
    plot DATANAME using 1:2 with lines linetype 1
}
set terminal x11
