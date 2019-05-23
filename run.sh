./main 1000 1e-3 crunk_nickelson > crunk_nickelson.txt
echo crunk-nikelson - done
./main 1000 1e-3 explicit > explicit.txt
echo explicit - done
./main 1000 1e-3 implicit > implicit.txt
echo implicit - done 

gnuplot script_explicit.gp
gnuplot script_implicit.gp
gnuplot script_crunk_nickelson.gp

