#include "vending_machine.h"

void VendingMachine::controlProcess() {
    while (true) {
        if (reset.read()) {
            currentState = INIT;
            money = 0;
        }
        else {
            switch (currentState) {
            case INIT:
                SC_REPORT_INFO("VendingMachine", "Machine is in INIT state");
                dispenseDrink.write(false);
                dispenseChange.write(false);
                if (sensor.read()) money = coinInserted;
                cout << "YOUR_MONEY : " << money << endl;
                if (money >0) {
                    currentState = WAIT_FOR_SELECTION;
                }
                break;

            case WAIT_FOR_SELECTION:
                if (selectedDrink.read() == WATER  && water == 1) {
                    SC_REPORT_INFO("VendingMachine", "Choose water ,You need 10k VND ");
                    if (money >= 10000) {
                        currentState = RECEIVE_COIN;
                        
                        money = money - 10000;
                        cout << "money = " << money << endl;
                    }
                    else SC_REPORT_INFO("VendingMachine", "Money is not correct");
                }
                else if ( selectedDrink.read() == SODA && water == 1) {
                    SC_REPORT_INFO("VendingMachine", "Choose soda ,You need 20k VND ");
                    if (coinInserted == 20000) currentState = RECEIVE_COIN;
                    else SC_REPORT_INFO("VendingMachine", "Money is not correct");
                }
                 else if (selectedDrink.read() == COFFEE && water == 1 ) {
                    SC_REPORT_INFO("VendingMachine", "Choose coffe ,You need 30k VND ");
                    if (coinInserted == 30000) currentState = RECEIVE_COIN;
                    else SC_REPORT_INFO("VendingMachine", "Money is not correct");
                }
                 else {
                     currentState = DISPENSE_CHANGE;
                     SC_REPORT_INFO("VendingMachine", "Out of water , see you next time");
                 }
                break;

            case RECEIVE_COIN:
                if (coinInserted.read()) {
                    currentState = DISPENSE_DRINK;
                    SC_REPORT_INFO("VendingMachine", "Received coin, dispensing drink");
                }
                break;

            case DISPENSE_DRINK:
                dispenseDrink.write(true);
                currentState = DISPENSE_CHANGE;
                SC_REPORT_INFO("VendingMachine", "Dispensing drink");
                break;

            case DISPENSE_CHANGE:
                if (money > 0 && return_money.read()) {
                    currentState = RETURN_MONEY;
                }
                else {
                    dispenseChange.write(true);
                    currentState = INIT;
                    SC_REPORT_INFO("VendingMachine", "Dispensing change, back to INIT state");
                }
                break;
            case RETURN_MONEY: {
                SC_REPORT_INFO("VendingMachine", "RETURN_MONEY");
                money = 0;
                currentState = INIT;
            }
            }
        }
        wait();  // Wait for one clock cycle to simulate control process
    }
}
