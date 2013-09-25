#include "bottlingplant.h"
extern PRNG prng;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ){
    total = 0;
    mShipFlv = maxShippedPerFlavour;
    theprt = &prt;
    theprt->print(Printer::BottlingPlant,'S');
    atruck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);
    for (int i = 0; i < 4; i++){ // produce some cola and ship to vending machines
        produce[i] = prng(mShipFlv);
        total += produce[i];
    }
    theprt->print(Printer::BottlingPlant,'G',total);
    atruck->action();
    total = 0;
    NS = &nameServer;
    maxStock = maxStockPerFlavour;
    numVend = numVendingMachines;
    timeBtwShip = timeBetweenShipments;
    mShipFlv = maxShippedPerFlavour;
}

// put the produced cola to the truck
void BottlingPlant::getShipment(unsigned int cargo[]){
    for(int i = 0; i < 4; i++){
        cargo[i] = produce[i];
        produce[i] = 0;
    }
    total = 0;
    theprt->print(Printer::BottlingPlant,'P');
}

void BottlingPlant::action(){
    if(prng(4) == 0){ // 1/5 chance to strike
        theprt->print(Printer::BottlingPlant, 'X');
        return;
    }
    else if(prng(timeBtwShip-1) == 0){ // if the truck come back and the do next shipment
        for (int i = 0; i < 4; i++){
            produce[i] += prng(mShipFlv);
            total += produce[i];
        }
        theprt->print(Printer::BottlingPlant,'G',total);
        atruck->action();
    }
    else {
        return;
    }
}

BottlingPlant::~BottlingPlant(){
    theprt->print(Printer::BottlingPlant,'F');
    theprt->print(Printer::Truck, 'F');
    delete atruck;
}
