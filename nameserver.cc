#include "nameserver.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ){
    lengthnow = 0;
    theprt = &prt;
    nVM = numVendingMachines;
    nS = numStudents;
    thelist = new VendingMachine* [nVM];
    theprt->print(Printer::NameServer,'S');
}

void NameServer::VMregister( VendingMachine *vendingmachine ){
    thelist[lengthnow] = vendingmachine; // add a vending machine at the end of array
    lengthnow += 1;
}

// return the vending machine according to the input id.
VendingMachine *NameServer::getMachine( unsigned int id ){
    return thelist[id % nVM];
}

VendingMachine **NameServer::getMachineList(){
    VendingMachine** output = thelist;
    return output;
}

NameServer::~NameServer(){
    theprt->print(Printer::NameServer, 'F');
    delete[] thelist;
}
