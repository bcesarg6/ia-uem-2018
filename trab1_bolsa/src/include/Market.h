//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_MARKET_H
#define TRAB1_BOLSA_MARKET_H

#include <vector>

#include "WorkDay.h"
#include "BaseInvestor.h"
#include "Company.h"

static std::vector<std::string> companies = {"UGPA3", "WEGE3", "LREN3", "GRND3", "SBSP3", "JSLG3", "CIEL3", "NATU3", "VIVT4", "LEVE3"};

/**
 * Represents the market object. Handles the day to day update, storing all work days and running the investments
 */
class Market {
public:

    Market(int day, int month, int year) : start_day(day), start_month(month), start_year(year) {}

    /**
     * Adds a work day to the market
     * @param workday The work day object
     */
    void addWorkDay(WorkDay* workday);

    /**
     * Adds a new investor to the market
     * @param investor The investor object
     */
    void addInvestor(BaseInvestor* investor);

    /**
      * @return The number of work days
    */
    int getNumberOfWorkDays();

    /**
      * @return Actual day number
    */
    int getPastDays() const;

    /**
     *
     * @return
     */
    std::vector<WorkDay*>& getWorkDays();

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

    /**
     * Returns the work day of a given date
     * @param day
     * @param month
     * @param year
     * @return If exists, the work day object, else nullptr
     */
    WorkDay* getWorkDayByDate(int day, int month, int year);

    /**
     * Gets a company name by its code
     * @param company The company code
     * @return String containing the name
     */
    static std::string getCompanyName(Company company);

    /**
     * Gets a company code by its name
     * @param name The string containing the name
     * @return The company code
     */
    static Company getCompanyCode(std::string name);

    /**
     * Starts this market simulation
     */
    void startMarket();

private:
    int past_days = 0, start_day, start_month, start_year;
    std::vector<WorkDay*> work_days;
    std::map<std::string, WorkDay*> work_day_map;
    std::vector<BaseInvestor*> investors;

    /**
     * Goes to next day of simulation
     */
    void nextDay();
};


#endif //TRAB1_BOLSA_MARKET_H
