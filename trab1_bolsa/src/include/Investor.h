//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_INVESTOR_H
#define TRAB1_BOLSA_INVESTOR_H

#include <string>
#include "WorkDay.h"

class WorkDay;

enum Type{
    AI, USER
};

class Investor {
public:
    /**
     * Do buy/sell operations based on data of the work day
     * @param last Previous work day
     * @param actual Actual work day
     */
    virtual void doOperations(WorkDay* last, WorkDay* actual) = 0;
    Investor(float start_wallet, std::string name, Type type) : start_wallet(start_wallet),
                                                                             name(name), type(type) {};
private:
    float start_wallet, actual_wallet;
    std::string name;
    Type type;
};


#endif //TRAB1_BOLSA_INVESTOR_H
