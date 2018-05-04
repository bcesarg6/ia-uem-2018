//
// Created by cristofer on 03/05/18.
//

#include <iostream>
#include "include/Market.h"

void Market::addWorkDay(WorkDay* workday){
    std::string date;

    work_days.push_back(workday);

    date += std::to_string(workday->getDay()) + std::to_string(workday->getMonth()) + std::to_string(workday->getYear());
    work_day_map[date] = workday;
}

void Market::addInvestor(BaseInvestor* investor){
    investors.push_back(investor);
}

WorkDay *Market::getWorkDayByDate(int day, int month, int year) {
    std::string date;

    date += std::to_string(day) + std::to_string(month) + std::to_string(year);

    auto it = work_day_map.find(date);
    if(it != work_day_map.end()){
        return it->second;
    }

    return nullptr;
}

int Market::getPastDays() const {
    return past_days;
}

WorkDay* Market::getActualWork(){
    if(past_days < work_days.size()){
        return work_days[past_days];
    }

    return nullptr;
}

WorkDay* Market::getNextWork(){
    if((past_days + 1) >= getNumberOfWorkDays()){
        return nullptr;
    }

    return work_days[past_days+1];
}

WorkDay* Market::getLastWork(){
    if(getPastDays() == 0){
        return nullptr;
    }

    return work_days[getPastDays()-1];
}

int Market::getNumberOfWorkDays(){
    return static_cast<int>(work_days.size());
}

bool Market::hasNextDay() {
    return past_days < getNumberOfWorkDays();
}

void Market::nextDay(){
    past_days = past_days + 1;
}

void Market::startMarket() {
    WorkDay* actual_work;

    while(hasNextDay()){
        actual_work = getActualWork();
        for(BaseInvestor* investor : investors){
            investor->doOperations(actual_work);
        }

        nextDay();
    }
}

std::string Market::getCompanyName(Company company) {
    return companies[company];
}

Company Market::getCompanyCode(std::string name) {
    if(name == "UGPA3"){
        return Company::UGPA3;
    }
    else if(name == "WEGE3"){
        return Company::WEGE3;
    }
    else if(name == "LREN3"){
        return Company::LREN3;
    }
    else if(name == "GRND3"){
        return Company::GRND3;
    }
    else if(name == "SBSP3"){
        return Company::SBSP3;
    }
    else if(name == "JSLG3"){
        return Company::JSLG3;
    }
    else if(name == "CIEL3"){
        return Company::CIEL3;
    }
    else if(name == "NATU3"){
        return Company::NATU3;
    }
    else if(name == "VIVT4"){
        return Company::VIVT4;
    }
    else if(name == "LEVE3"){
        return Company::LEVE3;
    }
    else{
        std::cout << "Company code not found!" << std::endl;
    }
}
