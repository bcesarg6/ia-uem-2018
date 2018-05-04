//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_INVESTOR_H
#define TRAB1_BOLSA_INVESTOR_H

#include <string>
#include "WorkDay.h"

class WorkDay;

enum Type{
    AI, USER
};

enum ActionType{
    BUY, SELL
};

class BaseInvestor {
public:
    BaseInvestor(double start_wallet, std::string name, Type type) : start_wallet(start_wallet), actual_wallet(start_wallet),
                                                                name(name), type(type) {};
    /**
     * Do buy/sell operations based on data of the work day
     * @param actual Actual work day
     */
    void doOperations(WorkDay* actual);
    void printDayReport(WorkDay* workday);

protected:
    double start_wallet, actual_wallet;
    std::string name;
    std::map<Company, double> shares;
    std::map<std::pair<WorkDay*,Company>, std::pair<ActionType, double>> actions;
    std::map<std::pair<WorkDay*,Company>, double> gains;
    Type type;
    WorkDay *last_work = nullptr, *actual_work = nullptr;

    virtual void operations() = 0;
    void buy(Company company, double amount);
    void sell(Company company, double amount);
    void registerAction(Company company, ActionType action, double amount);
    void doActions(bool print_report);
};


#endif //TRAB1_BOLSA_INVESTOR_H
