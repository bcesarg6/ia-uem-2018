//
// Created by Bruno Cesar on 09/05/18.
//

#ifndef TRAB1_BOLSA_CONFINVESTOR_H
#define TRAB1_BOLSA_CONFINVESTOR_H


#include "BaseInvestor.h"
#include "Market.h"

/**
 * Investor used by the AI. Receives the initial shares (trained by the AI) and makes
 * buy/sell operations based on the moving averages exponential
 */
class ConfInvestor : public BaseInvestor {
public:
    /**
     * Mapa de confiabilidade das companias
     */
    std::map<Company, double> confiabiality;

    /**
     * @param initial_shares Map with the initial shares of each company
     */
    ConfInvestor(double start_wallet, const std::string &name, InvestorType type, std::map<Company, double>& initial_shares);

    /**
     * COnstrutor vazio
     */
    explicit ConfInvestor(std::string name){
        BaseInvestor::name = name;

        for(std::string& company : companies){
            confiabiality[Market::getCompanyCode(company)] = 1.0;
        }
    };

protected:
    void operations() override;

private:
    std::map<Company, double> initial_shares;
};


#endif //TRAB1_BOLSA_CONFINVESTOR_H
