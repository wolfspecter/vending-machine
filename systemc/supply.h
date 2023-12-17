#ifndef SUPPLY_H
#define SUPPLY_H

#include <systemc.h>

SC_MODULE(Supply) {
    // Ports
    sc_in<bool> clock;
    sc_in<bool> reset;
    sc_out<bool> waterAvailable;
    sc_out<bool> water;

    // Constructor
    SC_CTOR(Supply) {
        SC_THREAD(supplyProcess);
        sensitive << clock.pos();
        sensitive << reset.neg();
    }

    // Process to simulate the water supply
    void supplyProcess();
};

#endif // SUPPLY_H
