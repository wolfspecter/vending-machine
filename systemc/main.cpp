#include <systemc.h>

#include "vending_machine.h"
#include "supply.h"
#include "testbench.h"

int sc_main(int argc, char* argv[]) {
    // Signals
    sc_clock clock("clock", 1, SC_NS);
    sc_signal<bool> reset;
    sc_signal<int> coinInserted;
    sc_signal<DrinkType> selectedDrink;
    sc_signal<bool> dispenseDrink;
    sc_signal<bool> dispenseChange;
    sc_signal<bool> waterAvailable;
    sc_signal<bool> w;
    sc_signal<bool> sensor;
    sc_signal<bool> return_money;

    // Instantiate the Supply module
    Supply supply("supply");
    supply.clock(clock);
    supply.reset(reset);
   // supply.waterAvailable(waterAvailable);

    // Instantiate the VendingMachine module
    VendingMachine vendingMachine("vendingMachine");
    vendingMachine.clock(clock);
    vendingMachine.reset(reset);
    vendingMachine.coinInserted(coinInserted);
    vendingMachine.selectedDrink(selectedDrink);
    vendingMachine.dispenseDrink(dispenseDrink);
    vendingMachine.dispenseChange(dispenseChange);
    vendingMachine.water(w);
    vendingMachine.return_money(return_money);
    vendingMachine.sensor(sensor);

    // Connect the supply module to the vending machine
    supply.waterAvailable(waterAvailable);
    supply.water(w);

    // Instantiate the Testbench
    Testbench testbench("testbench");
    testbench.clock(clock);
    testbench.reset(reset);
    testbench.coinInserted(coinInserted);
    testbench.selectedDrink(selectedDrink);
    testbench.dispenseDrink(dispenseDrink);
    testbench.dispenseChange(dispenseChange);
    testbench.waterAvailable(waterAvailable);
    testbench.return_money(return_money);
    testbench.sensor(sensor);

    // Trace signals for simulation
    sc_trace_file* traceFile;
    traceFile = sc_create_vcd_trace_file("VendingMachine");
    sc_trace(traceFile, clock, "clock");
    sc_trace(traceFile, reset, "reset");
    sc_trace(traceFile, coinInserted, "coinInserted");
    sc_trace(traceFile, selectedDrink, "selectedDrink");
    sc_trace(traceFile, dispenseDrink, "dispenseDrink");
    sc_trace(traceFile, dispenseChange, "dispenseChange");
    sc_trace(traceFile, waterAvailable, "waterAvailable");
    sc_trace(traceFile, w, "w");
    sc_trace(traceFile, return_money, "return_money");
    sc_trace(traceFile, sensor, "sensor");

    // Initialize simulation
    reset.write(true);
    sc_start(1, SC_NS);
    reset.write(false);

    // Run the simulation
    sc_start();

    // Close trace file
    sc_close_vcd_trace_file(traceFile);

    return 0;
}
