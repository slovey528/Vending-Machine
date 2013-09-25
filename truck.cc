#include "truck.h"

// min is used to compare two unsigned int and get the maximum/minimum
int min(unsigned int a, unsigned int b){
    if (a <= b)
        return a;
    else
        return b;
}

// numhave is used to get the total number of cola.
int numhave(unsigned int cargo[]){
    int i = 0;
    for (int j = 0; j < 4; j++){
        i += cargo[j];
    }
    return i;
}

Truck::Truck(Printer &prt, NameServer &nameServer, BottlingPlant &plant, unsigned int numVendingMachines, unsigned int maxStockPerFlavour){
    theprinter = &prt;
    NS = &nameServer;
    BP = &plant;
    VM = numVendingMachines;
    SPF = maxStockPerFlavour;
    theprinter->print(Printer::Truck,'S');
}


void Truck::action(){
    BP->getShipment(cargo);
    int totalnow = numhave(cargo);
    int need = 0;
    theprinter->print(Printer::Truck,'P',totalnow);
    VendingMachine** V_list = NS->getMachineList();
    for (int j = 0; j < VM ; j++){ // ship all the vending machines
        theprinter->print(Printer::Vending,V_list[j]->getId(),'r');
        theprinter->print(Printer::Truck,'d',V_list[j]->getId(),totalnow);
        unsigned int *V_stock = V_list[j]->inventory();
        for(int i = 0; i < 4; i += 1){ // ship all the 4 flavours
            unsigned int numtransfer = min((SPF - V_stock[i]), cargo[i]);
            V_stock[i] += numtransfer;
            cargo[i] -= numtransfer;
            totalnow -= numtransfer;
            need += SPF - V_stock[i];
        }
        if (need != 0)
            theprinter->print(Printer::Truck,'U',V_list[j]->getId(),need);
        need = 0;
        theprinter->print(Printer::Truck, 'D', V_list[j]->getId(), totalnow);
        theprinter->print(Printer::Vending,V_list[j]->getId(),'R');
        V_list[j]->restocked();
    }
}
