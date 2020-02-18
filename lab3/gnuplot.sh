#!/usr/bin/env bash
#t, dt, xn, vn)
set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set output "1.eps" # nazwa pliku wynikowego
set title "metoda RK2" # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "x(t)" # etykieta osi OY
set grid # wlaczenie widoczno�ci siatki pomocniczej
#set xrange [-0.2:5.2]
#set yrange [-0.2:1.2]
plot 'RK2.dat' using 1:3 with lines title "TOL = 10^{-2}",\
'RK22.dat' using 1:3 with lines title "TOL = 10^{-5}",\
#'euler3.dat' using 1:2 with points title "dt=1" ,\
#'anal.dat' using 1:2 with lines title "analitycznie"
#, 'name.dat' using 1:3 with lines title "b_i, M_S=M_C=30"
#replot "dane2.dat" using 1:3 with points

set output "2.eps" # nazwa pliku wynikowego
set title "metoda RK2" # tytul wykresu
#et xrange [-0.2:5.2]
#set yrange [-0.5:0]
set xlabel "t" # etykieta osi OX
set ylabel "v(t)" # etykieta osi OY
plot 'RK2.dat' using 1:4 with lines title "TOL = 10^{-2}",\
'RK22.dat' using 1:4 with lines title "TOL = 10^{-5}",\
#'euler3.dat' using 1:3 with lines title "dt=1"
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"

set output "3.eps" # nazwa pliku wynikowego
set title "metoda RK2" # tytul wykresu
#et xrange [-0.2:5.2]
#set yrange [-0.5:0]
set xlabel "t" # etykieta osi OX
set ylabel "dt(t)" # etykieta osi OY
plot 'RK2.dat' using 1:2 with lines title "TOL = 10^{-2}",\
'RK22.dat' using 1:2 with lines title "TOL = 10^{-5}",\

set output "4.eps" # nazwa pliku wynikowego
set title "metoda RK2" # tytul wykresu
#et xrange [-0.2:5.2]
#set yrange [-0.5:0]
set xlabel "v" # etykieta osi OX
set ylabel "x" # etykieta osi OY
plot 'RK2.dat' using 3:4 with lines title "TOL = 10^{-2}",\
'RK22.dat' using 3:4 with lines title "TOL = 10^{-5}",\

set output "5.eps" # nazwa pliku wynikowego
set title "metoda trapezow" # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "x(t)" # etykieta osi OY
set grid # wlaczenie widoczno�ci siatki pomocniczej
#set xrange [-0.2:5.2]
#set yrange [-0.2:1.2]
plot 'trapezy.dat' using 1:3 with lines title "TOL = 10^{-2}",\
'trapezy2.dat' using 1:3 with lines title "TOL = 10^{-5}",\
#'euler3.dat' using 1:2 with points title "dt=1" ,\
#'anal.dat' using 1:2 with lines title "analitycznie"
#, 'name.dat' using 1:3 with lines title "b_i, M_S=M_C=30"
#replot "dane2.dat" using 1:3 with points

set output "6.eps" # nazwa pliku wynikowego
set title "metoda trapezow" # tytul wykresu
#et xrange [-0.2:5.2]
#set yrange [-0.5:0]
set xlabel "t" # etykieta osi OX
set ylabel "v(t)" # etykieta osi OY
plot 'trapezy.dat' using 1:4 with lines title "TOL = 10^{-2}",\
'trapezy2.dat' using 1:4 with lines title "TOL = 10^{-5}",\
#'euler3.dat' using 1:3 with lines title "dt=1"
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"

set output "7.eps" # nazwa pliku wynikowego
set title "metoda trapezow" # tytul wykresu
#et xrange [-0.2:5.2]
#set yrange [-0.5:0]
set xlabel "t" # etykieta osi OX
set ylabel "dt(t)" # etykieta osi OY
plot 'trapezy.dat' using 1:2 with lines title "TOL = 10^{-2}",\
'trapezy2.dat' using 1:2 with lines title "TOL = 10^{-5}",\

set output "8.eps" # nazwa pliku wynikowego
set title "metoda trapezow" # tytul wykresu
#et xrange [-0.2:5.2]
#set yrange [-0.5:0]
set xlabel "v" # etykieta osi OX
set ylabel "x" # etykieta osi OY
plot 'trapezy.dat' using 3:4 with lines title "TOL = 10^{-2}",\
'trapezy2.dat' using 3:4 with lines title "TOL = 10^{-5}",\




