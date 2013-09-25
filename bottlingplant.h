#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "PRNG.h"
#include "printer.h"
#include "nameserver.h"
#include "truck.h"

class Truck;

class BottlingPlant {
    int total;
    Printer *theprt;
    unsigned int produce[4];
    unsigned int timeBtwShip;
    unsigned int mShipFlv;
    Truck* atruck;
    unsigned int numVend;
    NameServer* NS;
    unsigned int maxStock;
    public:
    ~BottlingPlant();
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
    unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
    unsigned int timeBetweenShipments );
    void getShipment( unsigned int cargo[] );
    void action();
};

#endif
