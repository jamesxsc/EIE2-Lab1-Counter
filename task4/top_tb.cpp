#include "Vtop.h" // generated source
#include "verilated.h"
#include "verilated_vcd_c.h" // to generate trace

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    // init 
    Verilated::commandArgs(argc, argv);

    Vtop* top = new Vtop;

    Verilated::traceEverOn(true); // init trace dump
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    // initialize inputs to DUT
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation
    for (i = 0; i < 300; i++) {
        // dump variables to trace
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2 * i * clk);
            top->clk = !top->clk;
            top->eval();
        }

        top->rst = (i < 2 || i == 15); // times to reset at
        top->en = (i > 4);
        if (Verilated::gotFinish()) exit(0);
    }

    tfp->close();
    exit(0);
}