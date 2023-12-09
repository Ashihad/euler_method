if (!exists("filename")) filename='results.txt'

set title "Phase portrait (X(t), V(t))"
set xlabel "X [m]"
set ylabel "V [m/s]"

set style line 1 \
    pointtype 7 \
    pointsize 0.3 \
    linecolor rgb 'blue'

plot filename u 3:4 with points ls 1 title "Phase portrait (X(t), V(t))"
pause -1 