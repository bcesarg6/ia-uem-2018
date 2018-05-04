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
    if(actions.find(std::pair<WorkDay*, Company>(actual_work, company)) != actions.end()){
        std::cout << "Já existe uma ação registrada para a compania " << Market::getCompanyName(company) << " para este dia" << std::endl;
    }
    else{
        actions.insert(std::make_pair(std::pair<WorkDay*, Company>(actual_work, company), std::pair<ActionType, double>(action, amount)));
    }
}

void BaseInvestor::doActions(bool print_report) {
    Company company;

    for(std::string& name : companies){
        company = Market::getCompanyCode(name);
        auto it = actions.find(std::pair<WorkDay*, Company>(actual_work, company));

        if(it != actions.end()){
            if(it->second.first == ActionType::BUY){
                buy(company, it->second.second);
            }
            else if(it->second.first == ActionType::SELL){
                sell(company, it->second.second);
            }

        }
        else{
            std::cout << "Não há ações no dia de hoje para " << name << std::endl;
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

    std::cout << "Relatório do dia " << workday->getDay() << "/" << workday->getMonth() << "/" << workday->getYear() << std::endl;

    for(std::string& name : companies){
        company = Market::getCompanyCode(name);
        auto action = actions.find(std::pair<WorkDay*, Company>(workday, company));

        if(action != actions.end()){
            if(action->second.first == ActionType::BUY){
                std::cout << "Foi realizada uma compra na empresa " << name << " de " << action->second.second << std::endl;
            }
            else{
                std::cout << "Foi realizada uma venda na empresa " << name << " de " << action->second.second << std::endl;
            }
        }
        std::cout << "Ganho para " << name << " " << gains[std::pair<WorkDay*, Company>(workday, company)] << ", carteira atual " << shares[company] << std::endl;
    }

    std::cout << "Carteira restante: " << actual_wallet << std::endl;
}
