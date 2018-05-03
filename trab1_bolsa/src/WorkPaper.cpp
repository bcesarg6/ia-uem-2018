//
// Created by cristofer on 03/05/18.
//

#include <utility>
#include <iostream>
#include "include/WorkPaper.h"

WorkPaper::WorkPaper(std::string company_code, float openp, float maxp, float minp, float medp, float lastp)
        : company_code(std::move(company_code)), openp(openp), maxp(maxp), minp(minp), avgp(medp), lastp(lastp) {}

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
    std::cout << "\tPaper from " << getCompanycode() << std::endl;
    std::cout << "\tPrices: " << std::endl;
    std::cout << "\t\tOpening: " << getOpenp() << std::endl;
    std::cout << "\t\tMaximum: " << getMaxp() << std::endl;
    std::cout << "\t\tMinimum: " << getMinp() << std::endl;
    std::cout << "\t\tAverage: " << getAvgp() << std::endl;
    std::cout << "\t\tLast: " << getLastp() << std::endl;
}
