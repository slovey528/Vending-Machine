#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "PRNG.h"
#include "printer.h"
#include "nameserver.h"
#include "watcard.h"

class NameServer;

class VendingMachine { // general vending machine
    public:
    enum Flavours{cherry, soda, root, lime};
    enum Status { BUY, STOCK, FUNDS }; // purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer,
    unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    virtual ~VendingMachine(); // necessary to trigger destructors in inherited classes
    virtual Status buy( Flavours flavour, WATCard *&card ); // YOU DEFINE FLAVOURS
    virtual unsigned int *inventory();
    virtual void restocked();
    virtual unsigned int cost();
    virtual unsigned int getId();
    protected:
    unsigned int invent[4];
    unsigned int idnum,thecost,maxStock;
    Printer* theprinter;
    NameServer* NS;
};

class VendingMachineCardEater : public VendingMachine { // specific vending machine
    unsigned int thecost;
    public:
    Status buy(Flavours flavour, WATCard *&card);
    VendingMachineCardEater( Printer &prt, NameServer &nameServer,
    unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    unsigned int cost();
    unsigned int getId();
    // member routines from VendingMachine
};

class VendingMachineOverCharger : public VendingMachine { // specific vending machine
    unsigned int thecost;
    public:
    Status buy(Flavours flavour, WATCard *&card);
    VendingMachineOverCharger( Printer &prt, NameServer &nameServer,
    unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    unsigned int cost();
    unsigned int getId();
    // member routines from VendingMachine
};

#endif
