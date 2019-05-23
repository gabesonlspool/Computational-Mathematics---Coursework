set terminal gif \
	animate \
	optimize \
	delay 1 \
	size 1920, 1080

set style line 1 \
    linecolor rgb '#0060ad' \
    linetype 1 linewidth 2

set style line 2 \
    linecolor rgb '#dd181f' \
    linetype 1 linewidth 2

set xrange [0: 1]
set yrange [260: 280]
set xlabel "X, m" font "Helvetica, 18"
set ylabel "T, K" font "Helvetica, 18"
set bmargin 4
set rmargin 4
set grid xtics lt 0 lw 1 lc rgb "#bbbbbb"
set grid ytics lt 0 lw 1 lc rgb "#bbbbbb" 
set output "stefan_problem_implicit.gif"
do for [i = 0:2000:2] {
	plot "output_implicit.dat" index i using 2:3 with lines linestyle 2 title "solid" ,\
	     ""           	   index i + 1 using 2:3 with lines linestyle 1 title "fluid" 

}

exit
