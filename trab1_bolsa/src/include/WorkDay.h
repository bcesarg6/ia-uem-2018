//
// Created by cristofer on 03/05/18.
//

#ifndef TRAB1_BOLSA_WORKDAY_H
#define TRAB1_BOLSA_WORKDAY_H

#include <vector>
#include <map>

#include "WorkPaper.h"
#include "Company.h"

class WorkDay {
public:
    /**
     * Creates a new work day object based on work papers
     * @param day Day of negotiation
     * @param month Month of negotiation
     * @param year Year of negotiation
     * @param work_papers Vector of the work papers negotiated this day
     */
    WorkDay(int day, int month, int year);

    /**
     * @return The day of this negotiation
     */
    int getDay() const;

    /**
     * @return The month of this negotiation
     */
    int getMonth() const;

    /**
     * @return The year of this negotiation
     */
    int getYear() const;

    /**
     * @return Vector of all work papers negotiated this day
     */
    const std::map<Company, WorkPaper*> &getWorkPapers() const;

    /**
     * Adds a work paper to the map
     * @param workpaper
     * @param company Company code
     */
    void addWorkPaper(WorkPaper* workpaper, Company company);

    /**
     * Displays the papers negotiated this day
     */
    void printDay();

    /**
     * Prints the header of a day
     */
    void printDayHeader();

private:
    int day, month, year;
    std::map<Company, WorkPaper*> work_papers;
};


#endif //TRAB1_BOLSA_WORKDAY_H
