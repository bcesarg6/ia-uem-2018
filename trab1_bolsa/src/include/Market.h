//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_MARKET_H
#define TRAB1_BOLSA_MARKET_H

#include <vector>

#include "WorkPaper.h"
#include "WorkDay.h"

class Market {
public:
    /**
     * Creates a new market object
     * @param start_day Number of the first day of the market
     * @param n_days Number of market duration days
     * @param work_days Vector of work day objects, used for simulating market
     */
    Market(int start_day, int n_days, std::vector<WorkDay*>& work_days);

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
     * @return True if market has next day, else false
     */
    bool hasNextDay();

    /**
     * Starts this market simulation
     */
    void startMarket();

private:
    int actual_day, n_days;
    std::vector<WorkDay*>& work_days;

    /**
     * Goes to next day of simulation
     */
    void nextDay();
};


#endif //TRAB1_BOLSA_MARKET_H
