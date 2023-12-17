#include "supply.h"

void Supply::supplyProcess() {
    while (true) {
            // Simulate water supply (this could be modeled based on real-time)
            waterAvailable.write(true);
            SC_REPORT_INFO("Supply", "Water is available");
            water = true;
            wait(15, SC_NS);  // Assume water is available for 10 seconds
            waterAvailable.write(false);
            SC_REPORT_INFO("Supply", "Out of water");
            water = false;
            wait(15, SC_NS);  // Assume out of water for the next 20 seconds
            SC_REPORT_INFO("Supply", "Water is available");
            water = true;
            wait(15, SC_NS);  // Assume water is available for 10 seconds
            waterAvailable.write(true);
            wait();
    }
}
