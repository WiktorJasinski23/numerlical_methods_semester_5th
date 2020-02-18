#!/usr/bin/env bash
set terminal post enhanced colour solid font 20  # wybor formatu, w jakim chcemy utworzyc wynikowy rysunek
set output "1.eps" # nazwa pliku wynikowego
set title "z1 metoda eulera - rozwi¹zanie " # tytul wykresu
set xlabel "t" # etykieta osi OX
set ylabel "y(t)" # etykieta osi OY
set grid # wlaczenie widocznoœci siatki pomocniczej
set xrange [-0.2:5.2]
set yrange [-0.2:1.2]
plot 'euler1.dat' using 1:2 with lines title "dt=0.01",\
'euler2.dat' using 1:2 with lines title "dt=0.1",\
'euler3.dat' using 1:2 with points title "dt=1" ,\
'anal.dat' using 1:2 with lines title "analitycznie"
#, 'name.dat' using 1:3 with lines title "b_i, M_S=M_C=30"
#replot "dane2.dat" using 1:3 with points

set output "2.eps" # nazwa pliku wynikowego
set title "z1 metoda eulera - b³¹d globalny " # tytul wykresu
set xrange [-0.2:5.2]
set yrange [-0.5:0]
plot 'euler1.dat' using 1:3 with lines title "dt=0.01",\
'euler2.dat' using 1:3 with lines title "dt=0.1",\
'euler3.dat' using 1:3 with lines title "dt=1"
# plot - polecenie rysowania pliku o podanej nazwie "out.dat"
# w p == with points
# t "dt = 0.1" == title "dt = 0.1"

set output "3.eps" # nazwa pliku wynikowego
set title "z2 metoda RK2- rozwi¹zanie " # tytul wykresu
set xrange [-0.2:5.2]
set yrange [-0.2:1.2]

plot 'trap1.dat' using 1:2 with lines title "dt=0.01",\
'trap2.dat' using 1:2 with lines title "dt=0.1",\
'trap3.dat' using 1:2 with points title "dt=1" ,\
'anal2.dat' using 1:2 with lines title "analitycznie"

set output "4.eps" # nazwa pliku wynikowego
set title "z2 metoda RK2- b³¹d globalny " # tytul wykresu
set xrange [-0.2:5.2]
set yrange [-0.2:0.2]

plot 'trap1.dat' using 1:3 with lines title "dt=0.01",\
'trap2.dat' using 1:3 with lines title "dt=0.1",\
'trap3.dat' using 1:3 with lines title "dt=1" ,\

set output "5.eps" # nazwa pliku wynikowego
set title "z3 metoda RK4- rozwi¹zanie " # tytul wykresu
set xrange [-0.2:5.2]
set yrange [-0.2:1.2]

plot 'trap4.dat' using 1:2 with lines title "dt=0.01",\
'trap5.dat' using 1:2 with lines title "dt=0.1",\
'trap6.dat' using 1:2 with points title "dt=1" ,\
'anal2.dat' using 1:2 with lines title "analitycznie"

set output "6.eps" # nazwa pliku wynikowego
set title "z3 metoda RK4- b³¹d globalny " # tytul wykresu
set xrange [-0.2:5.2]
set yrange [-0.0:0.01]

plot 'trap4.dat' using 1:3 with lines title "dt=0.01",\
'trap5.dat' using 1:3 with lines title "dt=0.1",\
'trap6.dat' using 1:3 with lines title "dt=1"

set output "7.eps" # nazwa pliku wynikowego
set title "z4 metoda RK4, Q(t) " # tytul wykresu
set xrange [-0.1:0.5]
set yrange [-0.003:0.004]
plot 'omega0.5.dat' using 1:2 with lines title "0.5{/Symbol w}_0",\
'omega0.8.dat' using 1:2 with lines title "0.8{/Symbol w}_0",\
'omega1.0.dat' using 1:2 with lines title "1{/Symbol w}_0" ,\
'omega1.2.dat' using 1:2 with lines title "1.2{/Symbol w}_0"

set output "8.eps" # nazwa pliku wynikowego
set title "z4 metoda RK4, I(t) " # tytul wykresu
set xrange [-0.1:0.5]
set yrange [-0.1:0.1]
plot 'omega0.5.dat' using 1:3 with lines title "0.5{/Symbol w}_0",\
'omega0.8.dat' using 1:3 with lines title "0.8{/Symbol w}_0",\
'omega1.0.dat' using 1:3 with lines title "1{/Symbol w}_0" ,\
'omega1.2.dat' using 1:3 with lines title "1.2{/Symbol w}_0"