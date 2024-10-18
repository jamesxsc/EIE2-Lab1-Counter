rm -rf obj_dir
rm -f counterchallenge.vcd

verilator -Wall --cc --trace counterchallenge.sv --exe counterchallenge_tb.cpp

make -j -C obj_dir/ -f Vcounterchallenge.mk Vcounterchallenge

obj_dir/Vcounterchallenge