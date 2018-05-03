//
// Created by cristofer on 03/05/18.
//

#include <iostream>
#include "include/BasicInvestor.h"

void BasicInvestor::doOperations(WorkDay *last, WorkDay *actual) {
    std::cout << "Fazendo operação" << std::endl;

}

BasicInvestor::BasicInvestor(float start_wallet, const std::string &name, Type type) : Investor(start_wallet,
                                                                                                          name, type) {}
