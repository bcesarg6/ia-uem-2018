//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_BASICINVESTOR_H
#define TRAB1_BOLSA_BASICINVESTOR_H


#include "BaseInvestor.h"

class UserInvestor : public BaseInvestor{
public:
    UserInvestor(double start_wallet, const std::string &name, Type type);

    void operations() override;
private:

};


#endif //TRAB1_BOLSA_BASICINVESTOR_H
