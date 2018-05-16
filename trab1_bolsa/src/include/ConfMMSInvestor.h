//
// Created by cristofer on 09/05/18.
//

#ifndef TRAB1_BOLSA_AUTOINVESTOR_H
#define TRAB1_BOLSA_AUTOINVESTOR_H


#include <map>
#include <set>
#include "Company.h"
#include "BaseInvestor.h"

struct Cmp
{
    bool operator ()(const std::pair<double, Company> &a, const std::pair<double, Company> &b)
    {
        return a.first < b.first;
    }
};

/**
 * Investor used by the AI. Recieves the initial shares (trained by the AI) and makes
 * buy/sell operations based on the moving averages simple
 */
class ConfMMSInvestor : public BaseInvestor {
public:
    /**
     * @param initial_shares Map with the initial shares of each company
     */
    ConfMMSInvestor(double start_wallet, const std::string &name, InvestorType type, std::map<Company,
            double>& initial_shares, std::map<Company,double>& confiability, int mm_days);

protected:
    void operations() override;

private:
    int mm_days;
    std::map<Company, double> initial_shares;
    std::map<Company,double>& confiability;
    double calculateSell(Company company, double gain);
    double calculateBuy(Company company, double wallet, double gain, double conf_share);
};


#endif //TRAB1_BOLSA_AUTOINVESTOR_H
