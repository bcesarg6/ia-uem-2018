//
// Created by cristofer on 07/05/18.
//

#include <iostream>
#include "include/BaseInvestor.h"
#include "include/Market.h"

void BaseInvestor::doOperations(WorkDay* actual){
    last_work = actual_work;
    actual_work = actual;

    operations();
    doActions(true);
}

void BaseInvestor::buy(Company company, double amount) {
    if(amount > (actual_wallet+0.0001)){
        std::cout << "Compra maior que a carteira atual" << std::endl;
        return;
    }

    actual_wallet -= amount;

    shares[company] += amount;
}

void BaseInvestor::sell(Company company, double amount) {
    if(amount > (shares[company]+0.0001)){
        std::cout << "Venda (" << amount << ") maior do que a quantidade existente (" << shares[company] << ")" << std::endl;
        return;
    }

    actual_wallet += amount;

    shares[company] -= amount;
}

void BaseInvestor::registerAction(Company company, ActionType action, double amount){
    if(action == ActionType::BUY){
        if(buy_actions.find(std::pair<WorkDay*, Company>(actual_work, company)) != buy_actions.end()){
            std::cout << "Já existe uma ação registrada para a compania " << Market::getCompanyName(company) << " para este dia" << std::endl;
        }
        else{
            buy_actions.insert(std::make_pair(std::pair<WorkDay*, Company>(actual_work, company), amount));
        }
    }
    else{
        if(sell_actions.find(std::pair<WorkDay*, Company>(actual_work, company)) != sell_actions.end()){
            std::cout << "Já existe uma ação registrada para a compania " << Market::getCompanyName(company) << " para este dia" << std::endl;
        }
        else{
            sell_actions.insert(std::make_pair(std::pair<WorkDay*, Company>(actual_work, company), amount));
        }
    }
}

void BaseInvestor::doActions(bool print_report) {
    Company company;

    for(std::string& name : companies){
        company = Market::getCompanyCode(name);
        auto it = sell_actions.find(std::pair<WorkDay*, Company>(actual_work, company));

        if(it != sell_actions.end()){
            sell(company, it->second);
        }
    }

    for(std::string& name : companies){
        company = Market::getCompanyCode(name);
        auto it = buy_actions.find(std::pair<WorkDay*, Company>(actual_work, company));

        if(it != buy_actions.end()){
            buy(company, it->second);
        }
    }

    double gain;
    for(std::string& name : companies){
        company = Market::getCompanyCode(name);

        if(last_work == nullptr){
            gains[std::pair<WorkDay*, Company>(actual_work, company)] = 0;
        }
        else{
            gain = actual_work->getWorkPapers().at(company)->getLastp() - last_work->getWorkPapers().at(company)->getLastp();
            gain = gain/last_work->getWorkPapers().at(company)->getLastp() * shares[company];
            shares[company] += gain;

            gains[std::pair<WorkDay*, Company>(actual_work, company)] = gain;
        }
    }

    if(print_report)
        printDayReport(actual_work);
}

void BaseInvestor::printDayReport(WorkDay* workday){
    Company company;
    double used_wallet = 0, day_gain = 0;
    static int sub = 0;
    static int desc = 0;

    std::cout << std::endl << "Relatório do dia " << workday->getDay() << "/" << workday->getMonth() << "/" << workday->getYear() << std::endl;
    if(workday->previous != nullptr) {
        std::cout << "Dia anterior: " << workday->previous->getDay() << "/" << workday->previous->getMonth() << "/" << workday->previous->getYear() << std::endl;
    }

    for(std::string& name : companies){
        company = Market::getCompanyCode(name);
        auto buy_action = buy_actions.find(std::pair<WorkDay*, Company>(workday, company));
        auto sell_action = sell_actions.find(std::pair<WorkDay*, Company>(workday, company));

        if(buy_action != buy_actions.end()){
            std::cout << "Foi realizada uma compra na empresa " << name << " de " << buy_action->second<< std::endl;
        }
        if(sell_action != sell_actions.end()){
            std::cout << "Foi realizada uma venda na empresa " << name << " de " << sell_action->second << std::endl;
        }
        std::cout << "Ganho para " << name << " " << gains[std::pair<WorkDay*, Company>(workday, company)] << ", carteira atual " << shares[company] << std::endl;
        day_gain+=gains[std::pair<WorkDay*, Company>(workday, company)];
        used_wallet+=shares[company];
    }

    if(day_gain < 0){
        desc++;
    }
    else{
        sub++;
    }

    std::cout << "Total usado: " << used_wallet << ", ganho do dia: " << day_gain << std::endl;
    std::cout << "Carteira restante: " << actual_wallet << std::endl;
    std::cout << "Dias de subida: " << sub << ", dias de descida: " << desc << std::endl;
    std::cout << "Ganho total: " << (used_wallet-1) << std::endl;
}

void BaseInvestor::getMMS(WorkDay *workDay, std::map<Company, double>& mms, int mm_days) {
    WorkDay* actual = workDay;
    int past_days = 0;

    for(int i = 0; i < mm_days; i++){
        if(actual == nullptr) break;

        for(std::string& comp : companies){
            Company company = Market::getCompanyCode(comp);
            mms[company] += actual->getWorkPapers().at(company)->getLastp();
        }
        actual = actual->previous;
        past_days++;
    }

    for(std::string& comp : companies){
        Company company = Market::getCompanyCode(comp);
        mms[company] = mms[company]/past_days;
    }
}
