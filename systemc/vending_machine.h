#pragma once
#ifndef VENDING_MACHINE_H
#define VENDING_MACHINE_H

#include <systemc.h>

enum DrinkType {
    WATER,
    SODA,
    COFFEE
};

enum State {
    INIT,
    WAIT_FOR_SELECTION,
    RECEIVE_COIN,
    DISPENSE_DRINK,
    DISPENSE_CHANGE,
    RETURN_MONEY
};

SC_MODULE(VendingMachine) {
    // Ports
    sc_in<bool> clock;
    sc_in<bool> reset;
    sc_in<int> coinInserted;
    sc_in<bool>  sensor;
    sc_in<DrinkType> selectedDrink;
    sc_out<bool> dispenseDrink;
    sc_out<bool> dispenseChange;
    sc_in<bool>  water;
    sc_in<bool>  return_money;
    int money;


    // Internal variables
    State currentState;

    // Constructor
    SC_CTOR(VendingMachine) {
        SC_THREAD(controlProcess);
        sensitive << clock.pos();
        sensitive << reset.neg();
        currentState = INIT;
        money = 0;
    }

    // Method to simulate the control process
    void controlProcess();
};

#endif // VENDING_MACHINE_H

