//
// Created by cristofer on 09/05/18.
//

#include <iostream>
#include "include/AITraining.h"

void AITraining::trainAI(std::map<Company, double> &initial_shares) {
    //Criar treinamento
}


void AITraining::simulateMarket(){
    std::map<Company , double> mms_anterior;
    std::map<Company , double> mms_atual;
    Company c;

    std::map<Company, int> streak;
    std::map<Company, bool> streak_check;

    for (WorkDay* day : market.getWorkDays()){
        if(day->getYear() == 2016) break;

        day->printDayHeader();

        if(day->previous != nullptr){
            //mms_anterior = funcaolouca(day->previous );
        }

        //mms_atual = funcaolouca(day);

        for(std::string& company : companies){
            c = Market::getCompanyCode(company);

            if(mms_atual[c] > mms_anterior[c]){
                streak_check[c] = true;

                /* Confiabilidade sobe */
                confInvestor.confiabiality[c] += alpha;

                /* Mecanismo de streak de confiabilidade */
                if(streak_check[c]){
                    streak[c]++;
                    confInvestor.confiabiality[c] += confInvestor.confiabiality[c] * gamma * (streak[c] - 1);
                }

            } else{
                /* Confiabilidade desce */
                confInvestor.confiabiality[c] -= beta;
                streak_check[c] = false;
                streak[c] = 0;
            }
        }

        std::cout << "Printando as confiabilidades" << std::endl;
        for(auto confiabilities : confInvestor.confiabiality){
            std::cout<< Market::getCompanyName(confiabilities.first) << " : " << confiabilities.second << std::endl;
        }

    }


}