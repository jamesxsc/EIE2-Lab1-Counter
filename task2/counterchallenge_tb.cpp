#include "Vcounterchallenge.h"     // Generated source
#include "verilated.h"     // Verilator core header
#include "verilated_vcd_c.h" // For trace generation
#include "vbuddy.cpp"      // Vbuddy library

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    // Initialize Verilated and Vcounter
    Verilated::commandArgs(argc, argv);
    Vcounterchallenge* top = new Vcounterchallenge;

    Verilated::traceEverOn(true);  // Enable tracing
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counterchallenge.vcd");

    // Initialize Vbuddy
    if (vbdOpen() != 1) return -1;
    vbdHeader("Lab 1: Counter");

    // Initialize inputs to DUT
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // Run the simulation for 300 clock cycles
    for (i = 0; i < 300; i++) {
        // Toggle clock
        for (clk = 0; clk < 2; clk++) {
            tfp->dump(2 * i + clk);  // Dump to trace file
            top->clk = !top->clk;
            top->eval();
        }

        // Send count value to Vbuddy plot (0 to 255)
        vbdPlot(int(top->count), 0, 255);
        vbdCycle(i + 1);

        // Control the reset signal at specific times
        top->rst = (i < 2 || i == 15);

        // Use vbdFlag() to set 'en' as the direction control: 1 for up, 0 for down
        top->en = vbdFlag();  // If vbdFlag() returns 1, count up; if 0, count down

        // End the simulation if Verilator finish signal is received
        if (Verilated::gotFinish()) exit(0);
    }

    // Cleanup
    vbdClose();   // Close Vbuddy
    tfp->close(); // Close trace file
    exit(0);
}