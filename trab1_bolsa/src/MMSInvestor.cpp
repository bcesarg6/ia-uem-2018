//
// Created by cristofer on 09/05/18.
//

#include <iostream>
#include "include/MMSInvestor.h"
#include "include/Market.h"
#include "include/ConfMMSInvestor.h"

MMSInvestor::MMSInvestor(double start_wallet, const std::string &name, InvestorType type,
                         std::map<Company, double> &initial_shares, int mm_days) : BaseInvestor(start_wallet, name, type),
                                                                                   initial_shares(initial_shares),
                                                                                    mm_days(mm_days){}

void MMSInvestor::operations() {
    if(last_work == nullptr){
        for(std::string& company : companies){
            Company comp = Market::getCompanyCode(company);
            if(initial_shares.at(comp) > 0.0001)
                registerAction(comp, ActionType::BUY, initial_shares.at(comp));
        }
    }
    else{
        double virtual_wallet = 0, wallet_share = 0, conf_sum = 0;
        std::set<std::pair<double, Company>, Cmp> mms_gain;
        std::map<Company, double> mms;
        std::map<Company, double> last_mms;
        BaseInvestor::getMMS(last_work, mms, mm_days);
        if(last_work->previous != nullptr)
            BaseInvestor::getMMS(last_work->previous, last_mms, mm_days);

        for(auto a_mms : mms){
            double gain;

            if(last_mms[a_mms.first])
                gain = (a_mms.second - last_mms[a_mms.first])/last_mms[a_mms.first];
            else
                gain = 0;

            std::cout << "ganho de " << Market::getCompanyName(a_mms.first) << ": " << gain << std::endl;
            mms_gain.insert(std::pair<double, Company>(gain, a_mms.first));


        }

        if((--mms_gain.end())->first <= 0){
            return;
        }

        for(auto it : mms_gain){
            if(it.first < 0){
                std::cout << "Vendendo ação de " << Market::getCompanyName(it.second) << " que está em queda: " << shares[it.second] << std::endl;

                registerAction(it.second, ActionType::SELL, shares[it.second]);
                virtual_wallet += shares[it.second];
            }
            else if(it.first >= 0){
                break;
            }
        }

        registerAction((--mms_gain.end())->second, ActionType::BUY, virtual_wallet);
    }
}
