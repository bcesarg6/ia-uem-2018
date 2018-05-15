//
// Created by cristofer on 09/05/18.
//

#include "include/ConfInvestor.h"
#include "include/Market.h"

ConfInvestor::ConfInvestor(double start_wallet, const std::string &name, InvestorType type, std::map<Company,
        double>& initial_shares) : BaseInvestor(start_wallet, name, type), initial_shares(initial_shares) {}


void ConfInvestor::operations() {
    if(last_work == nullptr){
        for(std::string& company : companies){
            Company comp = Market::getCompanyCode(company);
            if(initial_shares.at(comp) > 0.0001)
                registerAction(comp, ActionType::BUY, initial_shares.at(comp));
        }
    }
    else{
        //Calcular médias móveis, escolher qual tem maior tendência
    }
}

