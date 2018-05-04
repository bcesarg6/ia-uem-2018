//
// Created by cristofer on 08/05/18.
//

#ifndef TRAB1_BOLSA_RANDOMINVESTOR_H
#define TRAB1_BOLSA_RANDOMINVESTOR_H


#include "BaseInvestor.h"

class NoInvestor : public BaseInvestor {
public:
    NoInvestor(double start_wallet, const std::string &name, Type type);
    void operations() override ;

};


#endif //TRAB1_BOLSA_RANDOMINVESTOR_H
