#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "PRNG.h"
#include "watcardoffice.h"
#include "watcard.h"
#include "printer.h"
#include "vendingmachine.h"
#include "nameserver.h"

class Student {
    WATCard* mycard;
    VendingMachine* posn;
    unsigned int myid;
    unsigned int idnow;
    unsigned int maxP;
    Printer* p;
    NameServer* ns;
    WATCardOffice* WO;
    unsigned int favourate;
    unsigned int howmany;
    public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
    unsigned int maxPurchases );
    ~Student();
    bool action();
};

#endif
