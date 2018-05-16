//
// Created by cristofer on 09/05/18.
//

#include <iostream>
#include "include/AITraining.h"

void AITraining::trainAI(std::map<Company, double> &initial_shares, std::map<Company,double>& confiability) {
    for(std::string& company : companies){
        confiability[Market::getCompanyCode(company)] = 1.0;
    }

    simulateMarket(confiability);

    double sum = 0;
    for(auto it: confiability){
        if(it.second > 0)
            sum += it.second;
    }


    //std::cout << "Initial shares:" << std::endl;
    for(auto it: confiability) {
        if(it.second > 0)
            initial_shares[it.first] = it.second / sum;
        else
            initial_shares[it.first] = 0;

        //  std::cout << Market::getCompanyName(it.first) << " : " << initial_shares[it.first] << std::endl;
    }

    //std::cout << "Soma final dos shares " << cris << std::endl;



}


void AITraining::simulateMarket(std::map<Company,double>& confiability){
    int mm_days = 30;
    double gain;
    std::map<Company , double> mms_anterior;
    std::map<Company , double> mms_atual;
    std::map<Company, int> streak_up;
    std::map<Company, bool> streak_up_check;
    std::map<Company, int> streak_down;
    std::map<Company, bool> streak_down_check;
    Company c;

    for (WorkDay* day : market.getWorkDays()){
        mms_atual.clear();
        mms_anterior.clear();

        if(day->getYear() == 2016) continue;

        //day->printDayHeader();

        if(day->previous == nullptr)
            continue;

        BaseInvestor::getMMS(day->previous, mms_anterior, mm_days);
        BaseInvestor::getMMS(day, mms_atual, mm_days);

        for(std::string& company : companies){
            c = Market::getCompanyCode(company);
            gain = (mms_atual[c] - mms_anterior[c])/mms_anterior[c];
            //std::cout << "ganho: " << gain << std::endl;

            if(mms_atual[c] > mms_anterior[c]){
                streak_up_check[c] = true;
                streak_down_check[c] = false;
                streak_down[c] = 0;

                /* Confiabilidade sobe */
                confiability[c] += alpha;

                /* Mecanismo de streak_up de confiabilidade */
                if(streak_up_check[c]){
                    streak_up[c]++;
                    confiability[c] += confiability[c] * gamma * (streak_up[c] - 1);
                }

            } else{
                streak_up_check[c] = false;
                streak_down_check[c] = true;
                streak_up[c] = 0;

                /* Confiabilidade desce */
                confiability[c] -= beta;

                /* Mecanismo de streak_up de confiabilidade */
                if(streak_down_check[c]){
                    streak_down[c]++;
                    confiability[c] -= confiability[c] * delta * (streak_down[c] - 1);
                }
            }
        }

        /*std::cout << "Printando as confiabilidades" << std::endl;
        for(auto confiabilities : confiability){
            std::cout<< Market::getCompanyName(confiabilities.first) << " : " << confiabilities.second << std::endl;
        }*/

    }


}