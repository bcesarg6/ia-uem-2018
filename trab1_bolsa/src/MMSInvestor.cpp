//
// Created by cristofer on 09/05/18.
//

#include <iostream>
#include "include/MMSInvestor.h"
#include "include/Market.h"

MMSInvestor::MMSInvestor(double start_wallet, const std::string &name, InvestorType type, std::map<Company,
        double>& initial_shares, int mm_days) : BaseInvestor(start_wallet, name, type), initial_shares(initial_shares),
                                                                                        mm_days(mm_days){}

void MMSInvestor::operations() {
    calculateMMS(actual_work);
    if(last_work == nullptr){
        for(std::string& company : companies){
            Company comp = Market::getCompanyCode(company);
            if(initial_shares.at(comp) > 0.0001)
                registerAction(comp, ActionType::BUY, initial_shares.at(comp));
        }
    }
    else{
        double virtual_wallet = 0;

        for(auto it = mms_gain[actual_work].end(); it != mms_gain[actual_work].begin(); it--){
            if(it->first < 0){
                std::cout << "Vendendo ação de " << Market::getCompanyName(it->second) << " que está em queda" << std::endl;
                //
                registerAction(it->second, ActionType::SELL, shares[it->second]);
                virtual_wallet += shares[it->second];
            }
        }

        if(virtual_wallet > 0){
            std::cout << "Comprando ação de " << Market::getCompanyName(mms_gain[actual_work].begin()->second) << ", maior crescimento" << std::endl;
            registerAction(mms_gain[actual_work].begin()->second, ActionType::BUY, virtual_wallet);
        }
    }
}

void MMSInvestor::calculateMMS(WorkDay *workDay) {

}
