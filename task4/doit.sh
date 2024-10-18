rm -rf obj_dir/
rm -rf counter.vcd

verilator -Wall --cc --trace top.sv counter.sv bin2bcd.sv --exe top_tb.cpp

make obj_dir -j -C obj_dir/ -f Vtop.mk Vtop

obj_dir/Vtop