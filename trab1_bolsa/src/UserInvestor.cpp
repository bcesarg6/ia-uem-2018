//
// Created by cristofer on 03/05/18.
//

#include <iostream>
#include "include/UserInvestor.h"
#include "include/Market.h"

void UserInvestor::operations() {
    std::string in;
    double amount;

    std::cout << "Fazendo operações para o dia " << actual_work->getDay() << "/" << actual_work->getMonth() << "/" << actual_work->getYear() << std::endl << std::endl;
    if(last_work == nullptr){
        for(std::string& name : companies){
            registerAction(Market::getCompanyCode(name), ActionType::BUY, start_wallet/companies.size());
        }
    }
    else {
        for (std::string &name : companies) {
            std::cout << "Você deseja comprar ou vender de " << name << "? (C/V/N) (Atual: " << shares[Market::getCompanyCode(name)] << ")" << std::endl;
            std::cin >> in;
            if(in == "C"){
                std::cout << "Digite a quantidade para comprar da empresa " << name << std::endl;
                std::cin >> amount;
                registerAction(Market::getCompanyCode(name), ActionType::BUY, amount);
            }
            else if(in == "V"){
                std::cout << "Digite a quantidade para vender da empresa " << name << std::endl;
                std::cin >> amount;
                registerAction(Market::getCompanyCode(name), ActionType::SELL, amount);
            }
            else{
                std::cout << "Não serão realizadas operações para esta empresa" << std::endl;
            }
        }
    }
}

UserInvestor::UserInvestor(double start_wallet, const std::string &name, Type type) : BaseInvestor(start_wallet,
                                                                                                          name, type) {}
