#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "PRNG.h"
#include "vendingmachine.h"
#include "printer.h"

class VendingMachine;

class NameServer {
    unsigned int now;
    VendingMachine **thelist;
    Printer* theprt;
    unsigned int nVM;
    unsigned int nS;
    unsigned int lengthnow;
    public:
    ~NameServer();
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif
