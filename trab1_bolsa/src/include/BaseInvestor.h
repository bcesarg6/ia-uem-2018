//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_INVESTOR_H
#define TRAB1_BOLSA_INVESTOR_H

#include <string>
#include <utility>
#include "WorkDay.h"
#include <map>
#include "Company.h"

class WorkDay;

/**
 * Enum representing the type of the investor.
 */
enum InvestorType{
    AI, USER
};

/**
 * Type of the possible operations
 */
enum ActionType{
    BUY, SELL
};


/**
 * Base abstract class for all investors. Stores all information needed by a investor and implements
 * the basic functions needed by a investor. The main function is operations() wich needs to be implemented
 * by other classes, should use the registerAction() function to make actions.
 */
class BaseInvestor {
public:
    static int mm_days;

    /**
     * @param start_wallet Initial wallet, my be used to parcel the initial shares
     * @param name Name of the investor
     * @param type Type of the investor (AI, USER)
     */
    BaseInvestor(double start_wallet, std::string name, InvestorType type) : start_wallet(start_wallet), actual_wallet(start_wallet),
                                                                name(std::move(name)), type(type) {};

    /**
     * Construtor vazio
     */
    BaseInvestor() = default;

    /**
     * Updates the actual/last work, calls the operations() function and then call doActions() funcion
     * @param actual Actual work day
     */
    void doOperations(WorkDay* actual);

    static void getMMS(WorkDay* workDay, std::map<Company, double>& mms);

    /**
     * Prints to screen the dayly report with gains and actual wallet
     * @param workday
     */
    void printDayReport(WorkDay* workday);

protected:
    double start_wallet{}, actual_wallet{};
    std::string name;
    std::map<Company, double> shares;
    std::map<std::pair<WorkDay*,Company>, double> buy_actions;
    std::map<std::pair<WorkDay*,Company>, double> sell_actions;
    std::map<std::pair<WorkDay*,Company>, double> gains;
    InvestorType type;
    WorkDay *last_work = nullptr, *actual_work = nullptr;

    /**
     * Abstract function, should be implemented to register actions.
     */
    virtual void operations() = 0;

    /**
     * Register a action to be done at the end of the day
     * @param company Target company o the action
     * @param action Buy or sell type
     * @param amount Amount
     */
    void registerAction(Company company, ActionType action, double amount);

private:
    /**
     * Performs a buy operation, updating the wallet and shares
     * @param company The company to be bought
     * @param amount The amount to be bought
     */
    void buy(Company company, double amount);

    /**
     * Performs a sell operation, updating the wallet and shares
     * @param company The company to be bought
     * @param amount The amount to be bought
     */
    void sell(Company company, double amount);

    /**
     * Called at the end of doOperations(). Perform all registered actions.
     * @param print_report If needs to print the dayly report at the end of all operations
     */
    void doActions(bool print_report);
};


#endif //TRAB1_BOLSA_INVESTOR_H
