//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_BASICINVESTOR_H
#define TRAB1_BOLSA_BASICINVESTOR_H


#include "BaseInvestor.h"

/**
 * User based investor. Makes a initial uniform buy than anks to user what to buy/sell.
 */
class UserInvestor : public BaseInvestor{
public:
    UserInvestor(double start_wallet, const std::string &name, InvestorType type);

    void operations() override;
private:

};


#endif //TRAB1_BOLSA_BASICINVESTOR_H
