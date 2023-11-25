set title "Energies"
set xzeroaxis
set xlabel "time [s]"
set ylabel "Energy [J]"
set yrange [-3:3]

set style line 1 \
    pointtype 7 \
    pointsize 0.2 \
    linecolor rgb 'green'

set style line 1 \
    pointtype 7 \
    pointsize 0.2 \
    linecolor rgb 'blue'

set style line 1 \
    pointtype 7 \
    pointsize 0.2 \
    linecolor rgb 'red'

plot "results.txt" u 2:5 with points ls 1 title "Kinetic energy", \
    "results.txt" u 2:6 with points ls 2 title "Potential energy", \
    "results.txt" u 2:7 with points ls 3 title "Total energy"
pause -1 