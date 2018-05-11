//
// Created by cristofer on 08/05/18.
//

#ifndef TRAB1_BOLSA_RANDOMINVESTOR_H
#define TRAB1_BOLSA_RANDOMINVESTOR_H


#include "BaseInvestor.h"

/**
 * Investor that does nothing, just makes a initial uniform buy.
 */
class NoInvestor : public BaseInvestor {
public:
    NoInvestor(double start_wallet, const std::string &name, InvestorType type);
    void operations() override ;

};


#endif //TRAB1_BOLSA_RANDOMINVESTOR_H
