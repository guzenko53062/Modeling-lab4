set datafile separator "\t"
set terminal png size 1200,800 font "Arial,12"
set grid

set output "histogram.png"

set size ratio 1
plot [][0:] 'out.dat' using 1:2:3 with boxes fs solid 0.75
pause -1
