//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_WORKPAPER_H
#define TRAB1_BOLSA_WORKPAPER_H

#include <string>

class WorkPaper {
public:
    /**
     * Creates a new work paper objetc, represnting a company negotiation paper
     * @param company_code Company code
     * @param openp Opening price
     * @param maxp Maximum price
     * @param minp Minimum price
     * @param avgp Medium price
     * @param lastp Last price
     */
    WorkPaper(std::string company_code, float openp, float maxp, float minp, float avgp, float lastp);

    /**
     * @return The company code
     */
    const std::string &getCompanycode() const;

    /**
     * @return The openning price
     */
    float getOpenp() const;

    /**
     * @return The maximum price
     */
    float getMaxp() const;

    /**
     * @return The minimum price
     */
    float getMinp() const;

    /**
     * @return The medium price
     */
    float getAvgp() const;

    /**
     * @return The last price
     */
    float getLastp() const;

    /**
     * Prints the paper information
     */
    void printPaper();

private:
    std::string company_code;
    float openp, maxp, minp, avgp, lastp;

};


#endif //TRAB1_BOLSA_WORKPAPER_H
