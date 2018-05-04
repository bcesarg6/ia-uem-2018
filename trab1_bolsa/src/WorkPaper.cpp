//
// Created by cristofer on 03/05/18.
//

#include <utility>
#include <iostream>
#include "include/WorkPaper.h"

WorkPaper::WorkPaper(std::string company_code, float openp, float maxp, float minp, float avgp, float lastp)
        : company_code(std::move(company_code)), openp(openp), maxp(maxp), minp(minp), avgp(avgp), lastp(lastp) {}

const std::string &WorkPaper::getCompanycode() const {
    return company_code;
}


float WorkPaper::getOpenp() const {
    return openp;
}

float WorkPaper::getMaxp() const {
    return maxp;
}


float WorkPaper::getMinp() const {
    return minp;
}


float WorkPaper::getAvgp() const {
    return avgp;
}

float WorkPaper::getLastp() const {
    return lastp;
}

void WorkPaper::printPaper() {
    std::cout << "\t   " << getCompanycode() << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << "/ Abertura: " << getOpenp() << std::endl;
    std::cout << "/   Maximo: " << getMaxp() << std::endl;
    std::cout << "/   Minimo: " << getMinp() << std::endl;
    std::cout << "/    Media: " << getAvgp() << std::endl;
    std::cout << "/   Ultimo: " << getLastp() << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << std::endl;
}
