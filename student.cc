#include "student.h"
#include <iostream>
extern PRNG prng;

// int_to_flv is used to change an int between 0 and 3 to the flavour.
VendingMachine::Flavours int_to_flv(int i){
    switch (i){
        case 0:
            return VendingMachine::cherry;
        case 1:
            return VendingMachine::soda;
        case 2:
            return VendingMachine::root;
        case 3:
            return VendingMachine::lime;
        }
}

Student::Student(Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases){
    howmany = prng(1,maxPurchases); // determine how many bottles need to buy
    favourate = prng(3); // choose a flavour
    p = &prt;
    ns = &nameServer;
    WO = &cardOffice;
    myid = id;
    idnow = id;
    p->print(Printer::Student,myid,'S',favourate,howmany);
    mycard = WO->create(myid, 5);
    posn = ns->getMachine(myid);
    p->print(Printer::NameServer,'N', id, posn->getId());
    p->print(Printer::Student, myid, 'V', posn->getId());
};

// the student's action
bool Student::action(){
    if (howmany == 0){
        p->print(Printer::Student,myid,'F');
        return false; // return false if no more cola need to buy
    }
    else {
        VendingMachine::Status result = posn->buy(int_to_flv(favourate), mycard);
        if (mycard == NULL){
                  p->print(Printer::Student, myid, 'D');
                  mycard = WO->create(myid, 5);
        }
        if (result == VendingMachine::STOCK){ // if vending machine do not have enough cola
            idnow += 1;
            posn = ns->getMachine(idnow);
            p->print(Printer::NameServer,'N', myid, posn->getId());
            p->print(Printer::Student, myid, 'V', posn->getId());
        }
        else if(result == VendingMachine::FUNDS){ // do not have enough money
            while(mycard->balance < posn->cost()){
                WO->transfer(myid, 3, *mycard);
            }
        }
        else{ // buy a cola
            howmany -= 1;
            p->print(Printer::Student,myid,'B',mycard->balance);
        }
    }
    return true;
}

Student::~Student(){
    delete mycard;
}
