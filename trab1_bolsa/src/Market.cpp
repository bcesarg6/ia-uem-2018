//
// Created by cristofer on 03/05/18.
//

#include <iostream>
#include "include/Market.h"

Market::Market(int start_day, int n_days, std::vector<WorkDay*>& work_days) : actual_day(start_day),
                                                                                     work_days(work_days),
                                                                                     n_days(n_days){
    if(n_days != work_days.size()){
        std::cout << "Number of work days different!" << std::endl;
        exit(0);
    }
}

int Market::getActualDay() const {
    return actual_day;
}

WorkDay* Market::getActualWork(){
    return work_days[actual_day];
}

WorkDay* Market::getNextWork(){
    return work_days[actual_day+1];
}

bool Market::hasNextDay() {
    return ((actual_day + 1) <= n_days);
}

void Market::nextDay(){
    actual_day = actual_day + 1;
}

void Market::startMarket() {
    for(int i = 0; i < n_days; i++){
        getActualWork()->printDay();
        nextDay();
    }
}