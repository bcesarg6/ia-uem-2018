#include <iostream>
#include "include/Market.h"

void runTests();

void printInitHeader(){
    std::cout << "\t/--------------------------------------/" << std::endl;
    std::cout << "\t/ Simulaçao da bolsa de valores 2016   /" << std::endl;
    std::cout << "\t/                                      /" << std::endl;
    std::cout << "\t/    Bruno Cesar & Cristofer Oswald    /" << std::endl;
    std::cout << "\t/   Trabalho de IA. UEM, maringa, PR   /" << std::endl;
    std::cout << "\t/--------------------------------------/" << std::endl;
    std::cout << std::endl;

}

int main() {
    printInitHeader();

    std::cout << "Iniciando testes..." << std::endl << std::endl;
    runTests();

    std::cout << "Testes concluidos!" << std::endl;

    return 0;
}

void runTests(){
    Market* market;

    std::vector<WorkDay*> work_days;
    std::vector<WorkPaper*> work_papers;

    work_papers.push_back(new WorkPaper("UPG3", 10, 12, 8, 11, 11.5));
    work_papers.push_back(new WorkPaper("WR2", 20, 25, 15, 22, 23.2));
    work_papers.push_back(new WorkPaper("TF2", 12, 16, 11, 14, 15.6));
    work_papers.push_back(new WorkPaper("GGEE", 31, 32, 27, 28, 29.1));

    work_days.push_back(new WorkDay(1, 1, 2014, work_papers));

    work_papers.clear();

    work_papers.push_back(new WorkPaper("UPG3", 11.5, 13, 11, 12, 12.1));
    work_papers.push_back(new WorkPaper("WR2", 23.2, 27, 20, 23, 26.4));
    work_papers.push_back(new WorkPaper("TF2", 15.6, 18, 13, 16, 15.8));
    work_papers.push_back(new WorkPaper("GGEE", 29.1, 30, 25, 26, 27.2));

    work_days.push_back(new WorkDay(1, 2, 2014, work_papers));

    market = new Market(0, 2, work_days);

    market->startMarket();
}