#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include "vending_machine.h"

SC_MODULE(Testbench) {
    // Ports
    sc_in<bool> clock;
    sc_out<bool> reset;
    sc_out<int> coinInserted;
    sc_out<DrinkType> selectedDrink;
    sc_in<bool> dispenseDrink;
    sc_in<bool> dispenseChange;
    sc_in<bool> waterAvailable;
    sc_out<bool> return_money;
    sc_out<bool> sensor;

    // Constructor
    SC_CTOR(Testbench) {
        SC_THREAD(testProcess);
        sensitive << clock.pos();
    }

    // Process to simulate the testbench
    void testProcess();
};

#endif // TESTBENCH_H
