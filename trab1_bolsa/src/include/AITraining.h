//
// Created by cristofer on 09/05/18.
//

#ifndef TRAB1_BOLSA_AITRAINING_H
#define TRAB1_BOLSA_AITRAINING_H


#include "Market.h"

/**
 * Class representing the AI train. It uses the market information to generate
 * knowledge about the initial shares of each company. Uses *insert AI method
 * here*.
 */
class AITraining {
public:
    /**
     * Basic constructor, recieves the market used for the training
     * @param market The market filled with data
     */
    explicit AITraining(Market &market, double alpha, double beta, double delta, double gamma) : market(market) ,
                                                                                                 alpha(alpha),
                                                                                                 delta(delta),
                                                                                                 beta(beta),
                                                                                                 gamma(gamma){}

    /**
     * Trains the AI with a genetic algorithm and populates the initial shares.
     * *insert method explanation*
     * @param initial_shares The map to be populated
     */
    void trainAI(std::map<Company, double> &initial_shares, std::map<Company,double>& confiability);

private:
    double alpha; //parametro heuristico
    double beta;
    double delta;
    double gamma;
    Market& market;

    void simulateMarket(std::map<Company,double>& confiability);
};


#endif //TRAB1_BOLSA_AITRAINING_H
