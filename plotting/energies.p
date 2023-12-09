if (!exists("filename1")) filename1='results_expl_euler.txt'
if (!exists("filename2")) filename2='results_impl_euler.txt'
if (!exists("filename3")) filename3='results_trapezoidal.txt'

set terminal qt size 1600,600
set xzeroaxis
set xlabel "time [s]"
set ylabel "energy [J]"
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

set multiplot layout 1,3 rowsfirst

set title "Explicit Euler";
plot    filename1 u 2:5 with points ls 1 title "Kinetic energy", \
        filename1 u 2:6 with points ls 2 title "Potential energy", \
        filename1 u 2:7 with points ls 3 title "Total energy"

set title "Implicit Euler";
plot    filename2 u 2:5 with points ls 1 title "Kinetic energy", \
        filename2 u 2:6 with points ls 2 title "Potential energy", \
        filename2 u 2:7 with points ls 3 title "Total energy"

set title "Trapezoidal";
plot    filename3 u 2:5 with points ls 1 title "Kinetic energy", \
        filename3 u 2:6 with points ls 2 title "Potential energy", \
        filename3 u 2:7 with points ls 3 title "Total energy"

unset multiplot

pause -1 