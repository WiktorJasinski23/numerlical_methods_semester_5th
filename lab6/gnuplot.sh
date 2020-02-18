#!/usr/bin/gnuplot
set term png

set size ratio -1

set output "map1a.png"
set xlabel "x"
set ylabel "y"
set title "1a"
set pm3d map
set palette defined (-10 "blue", 0 "white", 10 "red")

splot "map1a.dat" i 0 u 2:1:3

reset

set output "map1b.png"
set xlabel "x"
set ylabel "y"
set title "1b"
set pm3d map
set palette defined (-10 "blue", 0 "white", 10 "red")


splot "map1b.dat" i 0 u 2:1:3

reset

set output "map1c.png"
set xlabel "x"
set ylabel "y"
set title "1c"
set pm3d map
set palette defined (-10 "blue", 0 "white", 10 "red")
set size ratio -1

splot "map1c.dat" i 0 u 2:1:3

reset

set output "map2a.png"
set xlabel "x"
set ylabel "y"
set title "2a"
set pm3d map
set palette defined (-1 "blue", 0 "white", 1 "red")


splot [0:10][0:10][-0.8:0.8] "map2a.dat" i 0 u 2:1:3


reset

set output "map2b.png"
set xlabel "x"
set ylabel "y"
set title "2b"
set pm3d map
set palette defined (-1 "blue", 0 "white", 1 "red")



splot [0:10][0:10][-0.8:0.8] "map2b.dat" i 0 u 2:1:3


reset

set output "map2c.png"
set xlabel "x"
set ylabel "y"
set title "2c"
set pm3d map
set palette defined (-1 "blue", 0 "white", 1 "red")

splot [0:10][0:10][-0.8:0.8] "map2c.dat" i 0 u 2:1:3
