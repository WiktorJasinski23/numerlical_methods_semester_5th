#!/usr/bin/gnuplot 

set term png enhanced size 600,300 

set size ratio -1


set output "u-1000.png"
set xlabel "x"
set ylabel "y"
set title "1a"
set cbr [-2:16]
set pm3d map
set palette defined (-2 "blue", 16 "red")

splot "zad1u.dat" i 0 u 1:2:3

reset

set output "v-1000.png"
set xlabel "x"
set ylabel "y"
set title "1a"
set cbr [-6:1]
set pm3d map
set palette defined (-6 "blue",1 "red")

splot "zad1v.dat" i 0 u 1:2:3


set o "psi-1000.png"
set contour
#set cntrparam levels 40 # lub ponizsze:
set cbr [-56:-50]
set cntrparam levels increment -56 ,0.2,-50
unset surface
set view map
unset key
splot "zad1psi.dat" u 1:2:3:3 w l lt -1 palette  t '' 

set o "dzeta-1000.png"
set contour
#set cntrparam levels 40 # lub ponizsze:
set cbr [-200:350]
set cntrparam levels increment -200 ,10,350
unset surface
set view map
unset key
splot "zad1dzeta.dat" u 1:2:3:3 w l lt -1 palette  t '' 





##############################################################
reset

set output "u-4000.png"
set xlabel "x"
set ylabel "y"
set title "1a"
set cbr [-10:70]
set pm3d map
set palette defined (-10 "blue", 70 "red")

splot "zad2u.dat" i 0 u 1:2:3

reset

set output "v-4000.png"
set xlabel "x"
set ylabel "y"
set title "1a"
set cbr [-14:4]
set pm3d map
set palette defined (-14 "blue",4 "red")

splot "zad2v.dat" i 0 u 1:2:3

set o "psi-4000.png"
set contour
#set cntrparam levels 40 # lub ponizsze:
set cbr [-218:-202]
set cntrparam levels increment -218 ,0.4,-202
unset surface
set view map
unset key
splot "zad2psi.dat" u 1:2:3:3 w l lt -1 palette  t '' 

set o "dzeta-4000.png"
set contour
#set cntrparam levels 40 # lub ponizsze:
set cbr [-700:1200]
set cntrparam levels increment -700 ,10,1200
unset surface
set view map
unset key
splot "zad1dzeta.dat" u 1:2:3:3 w l lt -1 palette  t '' 


##############################################################

set o "psi4000.png"
set contour
#set cntrparam levels 40 # lub ponizsze:
set cbr [202:218]
set cntrparam levels increment 202 ,0.4,218
unset surface
set view map
unset key
splot "zad3psi.dat" u 1:2:3:3 w l lt -1 palette  t '' 


