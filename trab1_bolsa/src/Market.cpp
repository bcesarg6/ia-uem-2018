//
// Created by cristofer on 03/05/18.
//

#include <iostream>
#include "include/Market.h"

Market::Market(int start_day, int n_days, std::vector<WorkDay*>* work_days, std::vector<Investor*>* investors) :
                                                                                     actual_day(start_day),
                                                                                     work_days(work_days),
                                                                                     n_days(n_days),
                                                                                     investors(investors){
    if(n_days != work_days->size()){
        std::cout << "Number of work days different!" << std::endl;
        exit(0);
    }
}

int Market::getActualDay() const {
    return actual_day;
}

WorkDay* Market::getActualWork(){
    return (*work_days)[actual_day];
}

WorkDay* Market::getNextWork(){
    return (*work_days)[actual_day+1];
}

WorkDay* Market::getLastWork(){
    if((actual_day - 1) < 0){
        return nullptr;
    }

    return (*work_days)[actual_day-1];
}

bool Market::hasNextDay() {
    return ((actual_day + 1) <= n_days);
}

void Market::nextDay(){
    actual_day = actual_day + 1;
}

void Market::startMarket() {
    for(int i = 0; i < n_days; i++){
        for(Investor* investor : *investors){
            investor->doOperations(getLastWork(), getActualWork());
        }

        getActualWork()->printDay();
        nextDay();
    }
}

std::string Market::getCompanyName(Company company) {
    std::string companies[10] = {"UGPA3", "WEGE3", "LREN3", "GRND3", "SBSP3", "JSLG3", "CIEL3", "NATU3", "VIVT4", "LEVE3"};
    return companies[company];
}
