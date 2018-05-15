//
// Created by cristofer on 08/05/18.
//

#include <iostream>
#include "include/NoInvestor.h"
#include "include/Market.h"

void NoInvestor::operations() {

    //std::cout << "Fazendo operações para o dia " << actual_work->getDay() << "/" << actual_work->getMonth() << "/" << actual_work->getYear() << std::endl << std::endl;
    if(last_work == nullptr){
        for(std::string& name : companies){
            registerAction(Market::getCompanyCode(name), ActionType::BUY, start_wallet/companies.size());
        }
    }

}


NoInvestor::NoInvestor(double start_wallet, const std::string &name, InvestorType type) : BaseInvestor(start_wallet,
                                                                                                       name, type) {}