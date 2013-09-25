#include "watcardoffice.h"
extern PRNG prng;

WATCardOffice::WATCardOffice(Printer &prt){
    theprinter = &prt;
    theprinter->print(Printer::WATCardOffice,'S');
}

WATCard* WATCardOffice::create(unsigned int id, unsigned int amount){ // create a new watcard
    WATCard* new_card = new WATCard;
    new_card->id = id;
    new_card->balance = amount;
    theprinter->print(Printer::WATCardOffice,'C',id,amount);
    return new_card;
}

// transfer some money to the watcard
void WATCardOffice::transfer(unsigned int id, unsigned int amount, WATCard &card){
    theprinter->print(Printer::Student, id, 't', amount);
    theprinter->print(Printer::WATCardOffice,'t',id,amount);
    if(prng(3) == 0){ // 1/4 chance to transfer half of the money
        card.balance += (amount / 2);
        theprinter->print(Printer::Student, id, 'T', card.balance);
        theprinter->print(Printer::WATCardOffice,'T',id,amount / 2);
    }
    else{
        card.balance += amount;
        theprinter->print(Printer::Student, id, 'T', card.balance);
        theprinter->print(Printer::WATCardOffice,'T',id,amount);
    }
}

WATCardOffice::~WATCardOffice(){
    theprinter->print(Printer::WATCardOffice,'F');
}
