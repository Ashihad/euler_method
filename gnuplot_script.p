#set size 500,500
set title "Phase portrait (X(t), V(t))"
set xlabel "X [m]"
set ylabel "V [m/s]"
plot "results.txt" u 2:3
pause -1 