//
// Created by cristofer on 09/05/18.
//

#include <iostream>
#include "include/AITraining.h"

void AITraining::trainAI(std::map<Company, double> &initial_shares) {
    std::map<Company,double> confiability;

    for(std::string& company : companies){
        confiability[Market::getCompanyCode(company)] = 1.0;
    }

    simulateMarket(confiability);

    double sum = 0;
    double cris = 0;
    for(auto it: confiability){
        sum += it.second;
    }


    //std::cout << "Initial shares:" << std::endl;
    for(auto it: confiability) {
        initial_shares[it.first] = it.second / sum;
        cris += it.second / sum;
      //  std::cout << Market::getCompanyName(it.first) << " : " << initial_shares[it.first] << std::endl;
    }

    //std::cout << "Soma final dos shares " << cris << std::endl;



}


void AITraining::simulateMarket(std::map<Company,double>& confiability){
    int mm_days = 5;
    std::map<Company , double> mms_anterior;
    std::map<Company , double> mms_atual;
    std::map<Company, int> streak;
    std::map<Company, bool> streak_check;
    Company c;

    for (WorkDay* day : market.getWorkDays()){
        if(day->getYear() == 2016) break;

        //day->printDayHeader();

        if(day->previous != nullptr){
            BaseInvestor::getMMS(day->previous, mms_anterior, mm_days);
        }

        BaseInvestor::getMMS(day, mms_atual, mm_days);

        for(std::string& company : companies){
            c = Market::getCompanyCode(company);

            if(mms_atual[c] > mms_anterior[c]){
                streak_check[c] = true;

                /* Confiabilidade sobe */
                confiability[c] += alpha;

                /* Mecanismo de streak de confiabilidade */
                if(streak_check[c]){
                    streak[c]++;
                    confiability[c] += confiability[c] * gamma * (streak[c] - 1);
                }

            } else{
                /* Confiabilidade desce */
                confiability[c] -= beta;
                streak_check[c] = false;
                streak[c] = 0;
            }
        }

        /*std::cout << "Printando as confiabilidades" << std::endl;
        for(auto confiabilities : confInvestor.confiabiality){
            std::cout<< Market::getCompanyName(confiabilities.first) << " : " << confiabilities.second << std::endl;
        }*/

    }


}