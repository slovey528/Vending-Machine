#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "PRNG.h"
#include "printer.h"
#include "nameserver.h"
#include "bottlingplant.h"
class BottlingPlant;

class Truck {
    protected:
    Printer* theprinter;
    NameServer* NS;
    BottlingPlant* BP;
    unsigned int cargo[4];
    unsigned int VM, SPF;
    public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
    unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    void action();
};

#endif
