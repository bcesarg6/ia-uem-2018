//
// Created by cristofer on 09/05/18.
//

#ifndef TRAB1_BOLSA_MAEINVESTOR_H
#define TRAB1_BOLSA_MAEINVESTOR_H


#include "BaseInvestor.h"

/**
 * Investor used by the AI. Recieves the initial shares (trained by the AI) and makes
 * buy/sell operations based on the moving averages exponential
 */
class MMEInvestor : public BaseInvestor {
public:
    /**
     * @param initial_shares Map with the initial shares of each company
     */
    MMEInvestor(double start_wallet, const std::string &name, InvestorType type, std::map<Company, double>& initial_shares);

protected:
    void operations() override;

private:
    std::map<Company, double> initial_shares;
};


#endif //TRAB1_BOLSA_MAEINVESTOR_H
