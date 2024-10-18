#include "Vcounter.h" // generated source
#include "verilated.h"
#include "verilated_vcd_c.h" // to generate trace
#include "vbuddy.cpp" 

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    // init 
    Verilated::commandArgs(argc, argv);

    Vcounter* top = new Vcounter;

    Verilated::traceEverOn(true); // init trace dump
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    //init vbuddy
    if (vbdOpen()!=1 return(-1));
    vbdHeader(" Lab 1: Counter");

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

    // Send count Value to Vbuddy
    vbdHex(4, (int(top->count) >> 16) & 0xF);
    vbdHex(3, (int(top->count) >> 8) & 0xF);
    vbdHex(2, (int(top->count) >> 4) & 0xF);
    vbdHex(1, int(top->count) & 0xF);
    vbdCycle(i+1);
    // end of Vbuddy Output section

        top->rst = (i < 2 || i == 15); // times to reset at
        top->en = (i > 4);
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}