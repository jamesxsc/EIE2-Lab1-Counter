#include "Vcounter.h" // generated source
#include "verilated.h"
#include "verilated_vcd_c.h" // to generate trace

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

    // initialize inputs to DUT
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation
    int stopFor = 0;
    for (i = 0; i < 300; i++) {
        // Stop when counter gets to 9
        if (top->count == 8 && stopFor == 0) {
            stopFor = 2;
        }

        // dump variables to trace
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2 * i * clk);
            top->clk = !top->clk;
            top->eval();
        }

        // Set en
        if (stopFor > 0) {
            top->en = false;
            stopFor--;
        } else {
            top->en = true;
        }

        top->rst = (i < 2 || i == 15); // times to reset at
        if (Verilated::gotFinish()) exit(0);
    }

    tfp->close();
    exit(0);
}