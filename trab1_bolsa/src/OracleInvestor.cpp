//
// Created by cristofer on 16/05/18.
//

#include <set>
#include "include/OracleInvestor.h"
#include "include/Market.h"
#include "include/ConfMMSInvestor.h"

OracleInvestor::OracleInvestor(double start_wallet, const std::string &name, InvestorType type) : BaseInvestor(start_wallet, name, type){

}

void OracleInvestor::operations() {
    std::set<std::pair<double, Company>, Cmp> gains;

    for(const auto &s : companies){
        double gain;
        Company c = Market::getCompanyCode(s);

        gain = actual_work->getWorkPapers().at(c)->getLastp() - actual_work->previous->getWorkPapers().at(c)->getLastp();
        gain = gain/actual_work->previous->getWorkPapers().at(c)->getLastp();

        gains.insert(std::pair<double, Company>(gain, c));
    }

    Company c = (--gains.end())->second;
    if(actual_work->previous->getYear() != actual_work->getYear()){
        registerAction(c, ActionType::BUY, 1);
    }
    else if(last != c){
        registerAction(last, ActionType::SELL, shares[last]);
        registerAction(c, ActionType::BUY, shares[last]);
    }
    last = c;

}
