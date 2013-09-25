#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "watcard.h"
#include "printer.h"
#include "PRNG.h"

class WATCardOffice{
    Printer* theprinter;
    public:
    ~WATCardOffice();
    WATCardOffice(Printer &prt);
    WATCard *create(unsigned int id, unsigned int amount);
    void transfer(unsigned int id, unsigned int amount, WATCard &card);
};

#endif
