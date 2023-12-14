#include "testbench.h"

void Testbench::testProcess() {
    reset.write(true);
    reset.write(false);
    // Test 1: Normal operation
    SC_REPORT_INFO("Testbench", "Test 1: Normal operation");
    coinInserted.write(30000);
    sensor.write(true);
    wait(2, SC_NS);
    sensor.write(false);
    selectedDrink.write(WATER);
    return_money.write(false);
    wait(15, SC_NS);

  // Test 2: Out of water
    SC_REPORT_INFO("Testbench", "Test 2: Out of water");
    coinInserted.write(10000);
    sensor.write(true);
    wait(2, SC_NS);
    sensor.write(false);
    selectedDrink.write(WATER);
    return_money.write(false);
    wait(10, SC_NS);

    // Test 3: Reset and coin inserted
    SC_REPORT_INFO("Testbench", "Test 3: Reset and coin inserted");
    reset.write(true);
    reset.write(false);
    coinInserted.write(20000);
    sensor.write(true);
    wait(2, SC_NS);
    sensor.write(false);
    selectedDrink.write(WATER);
    return_money.write(true);
    wait(10, SC_NS);

    // Add more test scenarios as needed
    sc_stop(); // Stop simulation after the tests
}
