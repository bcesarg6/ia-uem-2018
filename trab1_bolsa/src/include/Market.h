//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_MARKET_H
#define TRAB1_BOLSA_MARKET_H

#include <vector>

#include "WorkDay.h"
#include "Investor.h"
#include "Company.h"

class Market {
public:
    /**
     * Creates a new market object
     * @param start_day Number of the first day of the market
     * @param n_days Number of market duration days
     * @param work_days Vector of work day objects, used for simulating market
     */
    Market(int start_day, int n_days, std::vector<WorkDay*>* work_days, std::vector<Investor*>* investors);

    /**
     * @return Actual day number
     */
    int getActualDay() const;

    /**
     * @return Actual work day object
     */
    WorkDay* getActualWork();

    /**
     * @return Next work day object
     */
    WorkDay* getNextWork();

    /**
     * @return If doesn't have previous work, null, else the work day object
     */
    WorkDay* getLastWork();

    /**
     * @return True if market has next day, else false
     */
    bool hasNextDay();

    static std::string getCompanyName(Company company);

    /**
     * Starts this market simulation
     */
    void startMarket();

private:
    int actual_day, n_days;
    std::vector<WorkDay*>* work_days;
    std::vector<Investor*>* investors;

    /**
     * Goes to next day of simulation
     */
    void nextDay();
};


#endif //TRAB1_BOLSA_MARKET_H
