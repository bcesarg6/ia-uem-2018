//
// Created by cristofer on 16/05/18.
//

#ifndef TRAB1_BOLSA_ORACLEINVESTOR_H
#define TRAB1_BOLSA_ORACLEINVESTOR_H


#include "BaseInvestor.h"

class OracleInvestor : public BaseInvestor {
public:
    OracleInvestor(double start_wallet, const std::string &name, InvestorType type);

protected:
    void operations() override;

private:
    Company last;
};


#endif //TRAB1_BOLSA_ORACLEINVESTOR_H
