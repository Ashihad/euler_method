if (!exists("filename")) filename='results.txt'

set title "Energies"
set xzeroaxis
set xlabel "time [s]"
set ylabel "Energy [J]"
set yrange [-3:3]

set style line 1 \
    pointtype 7 \
    pointsize 0.2 \
    linecolor rgb 'red'

set style line 2 \
    pointtype 7 \
    pointsize 0.2 \
    linecolor rgb 'blue'

set style line 3 \
    pointtype 7 \
    pointsize 0.2 \
    linecolor rgb 'green'

plot    filename u 2:5 with points ls 1 title "Kinetic energy", \
        filename u 2:6 with points ls 2 title "Potential energy", \
        filename u 2:7 with points ls 3 title "Total energy"
pause -1 