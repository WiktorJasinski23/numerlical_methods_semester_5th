#!/usr/bin/gnuplot
set term png


set output "integral.png"
set xlabel "it"
set ylabel "S(it)"
set title "Całka funkcjonalna S(it)"

plot "integral1.dat" u 1:2 with lines title "k=16",\
 "integral2.dat" u 1:2 with lines title "k=8",\
 "integral3.dat" u 1:2 with lines title "k=4",\
 "integral4.dat" u 1:2 with lines title "k=2",\
 "integral5.dat" u 1:2 with lines title "k=1"

set size ratio -1

set output "map16.png"
set xlabel "x"
set ylabel "y"
set title "k=16"
set pm3d map
set palette defined (-1 "blue", 0 "green", 1 "red")


splot [0:25.6][0:25.6] "map1.dat" u 1:2:3

set output "map8.png"
set xlabel "x"
set ylabel "y"
set title "k=8"
set pm3d map
set palette defined (-1 "blue", 0 "green", 1 "red")


splot [0:25.6][0:25.6] "map2.dat" u 1:2:3

set output "map4.png"
set xlabel "x"
set ylabel "y"
set title "k=4"
set pm3d map
set palette defined (-1 "blue", 0 "green", 1 "red")


splot [0:25.6][0:25.6] "map3.dat" u 1:2:3

set output "mapa2.png"
set xlabel "x"
set ylabel "y"
set title "k=2"
set pm3d map
set palette defined (-1 "blue", 0 "green", 1 "red")


splot  "map4.dat" u 1:2:3

set output "mapa1.png"
set xlabel "x"
set ylabel "y"
set title "k=1"
set pm3d map
set palette defined (-1 "blue", 0 "green", 1 "red")


splot [0:25.6][0:25.6] "map4.dat" u 1:2:3
