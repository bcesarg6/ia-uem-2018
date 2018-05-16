//
// Created by cristofer on 09/05/18.
//

#include <iostream>
#include "include/ConfMMSInvestor.h"
#include "include/Market.h"

ConfMMSInvestor::ConfMMSInvestor(double start_wallet, const std::string &name, InvestorType type, std::map<Company,
        double>& initial_shares, std::map<Company,double>& confiability, int mm_days) : BaseInvestor(start_wallet, name, type),
                                                                                        initial_shares(initial_shares),
                                                                                        mm_days(mm_days), confiability(confiability){}

void ConfMMSInvestor::operations() {
    if(last_work == nullptr){
        for(std::string& company : companies){
            Company comp = Market::getCompanyCode(company);
            if(initial_shares.at(comp) > 0.0001) {
                registerAction(comp, ActionType::BUY, initial_shares.at(comp));
            }
        }
    }
    else{
        int positives = 0;
        double virtual_wallet = 0, wallet_share = 0, conf_sum = 0;
        std::set<std::pair<double, Company>, Cmp> mms_gain;
        std::map<Company, double> mms;
        std::map<Company, double> last_mms;
        std::map<Company, double> share_map;
        std::map<Company, double> conf_share;
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
        std::cout << std::endl;

        if((--mms_gain.end())->first <= 0){
            return;
        }

        for(auto it : mms_gain){
            if(it.first < 0){
                double sell = calculateSell(it.second, it.first);
                if(sell > shares[it.second]){
                    sell = shares[it.second];
                }
                std::cout << "Vendendo ação de " << Market::getCompanyName(it.second) << " que está em queda: " << sell << std::endl;

                registerAction(it.second, ActionType::SELL, sell);
                virtual_wallet += sell;
            }
            else if(it.first > 0){
                positives++;
                wallet_share += it.first;
            }
            //std::cout << "ganho de " << Market::getCompanyName(it.second) << ": " << it.first<< std::endl;
        }

        auto it = mms_gain.end();
        for(int i = 0; i < positives; i++) {
            it--;
            share_map[it->second] = it->first/wallet_share;
        }

        it = mms_gain.end();
        for(int i = 0; i < positives; i++) {
            it--;
            conf_sum += initial_shares[it->second];
        }

        it = mms_gain.end();
        for(int i = 0; i < positives; i++) {
            it--;
            conf_share[it->second] = initial_shares[it->second]/conf_sum;
        }

        it = mms_gain.end();
        std::cout << "wallet " << virtual_wallet <<std::endl;

        double buyw = 0;
        for(int i = 0; i < positives; i++){
            it--;
            double buy = calculateBuy(it->second, virtual_wallet, share_map[it->second], conf_share[it->second]);
            buyw+= buy;
            std::cout << "Comprando ação de " << Market::getCompanyName(it->second) << ", obteve crescimento : " << buy << std::endl;
            registerAction(it->second, ActionType::BUY, buy);
        }

        //std::cin >> mm_days;
    }
}

double ConfMMSInvestor::calculateBuy(Company company, double wallet, double gain, double conf_share) {
    //return wallet * (gain/4 + conf_share/2);
    return wallet * conf_share;
}

double ConfMMSInvestor::calculateSell(Company company, double gain) {
    //return (shares[company]/50) + (((1-initial_shares[company]))*gain*-1);
    return shares[company]/((initial_shares[company]*100) + (gain*-1*100));
}
