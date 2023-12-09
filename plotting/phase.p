if (!exists("filename1")) filename1='results_expl_euler.txt'
if (!exists("filename2")) filename2='results_impl_euler.txt'
if (!exists("filename3")) filename3='results_trapezoidal.txt'

set title "Phase portrait (X(t), V(t))"
set terminal qt size 1600,600
set xlabel "x [m]"
set ylabel "v [m/s]"

set style line 1 \
    pointtype 7 \
    pointsize 0.3 \
    linecolor rgb 'blue'

set multiplot layout 1,3 rowsfirst

set title "Explicit Euler"
plot filename1 u 3:4 with points ls 1 title "Phase portrait (X(t), V(t))", \

set title "Implicit Euler"
plot filename2 u 3:4 with points ls 1 title "Phase portrait (X(t), V(t))", \

set title "Trapezoidal"
plot filename3 u 3:4 with points ls 1 title "Phase portrait (X(t), V(t))", \

unset multiplot
pause -1 