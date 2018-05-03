//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_BASICINVESTOR_H
#define TRAB1_BOLSA_BASICINVESTOR_H


#include "Investor.h"

class BasicInvestor : public Investor{
public:
    BasicInvestor(float start_wallet, const std::string &name, Type type);

private:
    void doOperations(WorkDay *last, WorkDay *actual) override;

};


#endif //TRAB1_BOLSA_BASICINVESTOR_H
