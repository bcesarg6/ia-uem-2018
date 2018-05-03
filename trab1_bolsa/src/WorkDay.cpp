//
// Created by cristofer on 03/05/18.
//

#include <iostream>
#include "include/WorkDay.h"

WorkDay::WorkDay(int day, int month, int year, std::vector<WorkPaper *>& work_papers) : day(day), month(month),
                                                                                            year(year),
                                                                                            work_papers(work_papers) {}

int WorkDay::getDay() const {
    return day;
}


int WorkDay::getMonth() const {
    return month;
}


int WorkDay::getYear() const {
    return year;
}

const std::vector<WorkPaper *> &WorkDay::getWorkPapers() const {
    return work_papers;
}

void WorkDay::printDayHeader(){
    std::cout << "\t/-------------------------------/" << std::endl;
    std::cout << "\t/   Dia de trabalho: " << getDay() << "/" << getMonth() << "/" << getYear() << "   /" << std::endl;
    std::cout << "\t/         Papeis do dia         /" << std::endl;
    std::cout << "\t/-------------------------------/" << std::endl << std::endl;
}

void WorkDay::printDay() {
    printDayHeader();

    for(WorkPaper* paper : getWorkPapers()){
        paper->printPaper();
    }
}

