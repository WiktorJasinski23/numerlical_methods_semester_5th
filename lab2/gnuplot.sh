#!/usr/bin/env bash
set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set output "1.eps" # nazwa pliku wynikowego
set title "Iteracja Pickarda" # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "y(t)" # etykieta osi OY
set grid # wlaczenie widoczno�ci siatki pomocniczej
#set xrange [-0.2:5.2]
#set yrange [-0.2:1.2]
plot 'pickard.dat' using 1:2 with lines title "u(t)",\
'pickard.dat' using 1:3 with lines title "v(t)",\
#'euler3.dat' using 1:2 with points title "dt=1" ,\
#'anal.dat' using 1:2 with lines title "analitycznie"
#, 'name.dat' using 1:3 with lines title "b_i, M_S=M_C=30"
#replot "dane2.dat" using 1:3 with points

set output "2.eps" # nazwa pliku wynikowego
set title "Iteracja Newtona" # tytul wykresu
#et xrange [-0.2:5.2]
#set yrange [-0.5:0]
plot 'newton.dat' using 1:2 with lines title "u(t)",\
'newton.dat' using 1:3 with lines title "v(t)",\
#'euler3.dat' using 1:3 with lines title "dt=1"
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"

set output "3.eps" # nazwa pliku wynikowego
set title "Iteracja RK2" # tytul wykresu
#et xrange [-0.2:5.2]
#set yrange [-0.5:0]
plot 'rk2.dat' using 1:2 with lines title "u(t)",\
'rk2.dat' using 1:3 with lines title "v(t)",\


