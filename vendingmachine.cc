#include "vendingmachine.h"
#include <iostream>
extern PRNG prng;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer,unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ){
    idnum = id;
    thecost = sodaCost;
    maxStock = maxStockPerFlavour;
    theprinter = &prt;
    NS = &nameServer;
    for (int i = 0; i < 4; i++){
        invent[i] = 0;
    }
}

VendingMachine::~VendingMachine(){
    theprinter->print(Printer::Vending,idnum,'F');
}

unsigned int* VendingMachine::inventory(){
    unsigned int* output = invent;
    return output;
}

VendingMachine::Status VendingMachine::buy(Flavours flavour, WATCard *&card){}

void VendingMachine::restocked(){
}

unsigned int VendingMachine::cost(){

}

unsigned int VendingMachine::getId(){

}

VendingMachineCardEater::VendingMachineCardEater(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour): VendingMachine(prt, nameServer, id, sodaCost, maxStockPerFlavour){
    thecost = sodaCost;
    theprinter->print(Printer::Vending,id,'S',thecost);
    NS->VMregister(this); // regist in nameserver
    theprinter->print(Printer::NameServer,'R',id);
}

// purchase a bottle of cola in a cardeater machine.
VendingMachine::Status VendingMachineCardEater::buy(Flavours flavour, WATCard *&card){
    Status output;
    if(invent[flavour] == 0){
        output = STOCK;
    }
    else if(card->balance < thecost){
        output = FUNDS;
    }
    else{
        card->balance -= thecost;
        invent[flavour] -= 1;
        theprinter->print(Printer::Vending,idnum ,'B',flavour,invent[flavour]);
        output = BUY;
    }
        if(prng(9) == 0){ // 1/10 chance to destroy a card
            delete card;
            card = NULL;
    }
    return output;
}

unsigned int VendingMachineCardEater::cost(){
    return thecost;
}

unsigned int VendingMachineCardEater::getId(){
    return idnum;
}

VendingMachineOverCharger::VendingMachineOverCharger(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour):VendingMachine(prt, nameServer, id, sodaCost, maxStockPerFlavour){
    thecost = 2 * sodaCost; // charge more money
    theprinter->print(Printer::Vending,id,'S',thecost);
    NS->VMregister(this); // regist in nameserver
    theprinter->print(Printer::NameServer,'R',idnum);
}

VendingMachine::Status VendingMachineOverCharger::buy(Flavours flavour, WATCard *&card){
    if (invent[flavour] == 0){
        return STOCK;
    }
    else if (card->balance < thecost){
        return FUNDS;
    }
    else {
        card->balance -= thecost;
        invent[flavour] -= 1;
        theprinter->print(Printer::Vending,idnum,'B',flavour,invent[flavour]);
        return BUY;
    }
}

unsigned int VendingMachineOverCharger::cost(){
    return thecost;
}

unsigned int VendingMachineOverCharger::getId(){
    return idnum;
}
