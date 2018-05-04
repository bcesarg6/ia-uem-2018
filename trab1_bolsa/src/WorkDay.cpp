//
// Created by cristofer on 03/05/18.
//

#include <iostream>
#include "include/WorkDay.h"

WorkDay::WorkDay(int day, int month, int year) : day(day), month(month), year(year){}

int WorkDay::getDay() const {
    return day;
}


int WorkDay::getMonth() const {
    return month;
}


int WorkDay::getYear() const {
    return year;
}

const std::map<Company, WorkPaper *> &WorkDay::getWorkPapers() const {
    return work_papers;
}

void WorkDay::addWorkPaper(WorkPaper *workpaper, Company company) {
    work_papers.insert(std::pair<Company, WorkPaper*>(company, workpaper));
}

void WorkDay::printDayHeader(){
    std::cout << "\t/-------------------------------/" << std::endl;
    std::cout << "\t/   Dia de trabalho: " << getDay() << "/" << getMonth() << "/" << getYear() << "   /" << std::endl;
    std::cout << "\t/         Papeis do dia         /" << std::endl;
    std::cout << "\t/-------------------------------/" << std::endl << std::endl;
}

void WorkDay::printDay() {
    printDayHeader();

    for(std::pair<Company, WorkPaper*> paper : getWorkPapers()){
        paper.second->printPaper();
    }
}

