#include <iostream>
#include "include/Market.h"
#include "include/UserInvestor.h"
#include "include/utils.h"
#include "include/NoInvestor.h"
#include "include/MASInvestor.h"
#include "include/AITraining.h"

void runTests(bool create_data);

void printInitHeader(){
    std::cout << "\t/--------------------------------------/" << std::endl;
    std::cout << "\t/ Simulaçao da bolsa de valores 2016   /" << std::endl;
    std::cout << "\t/                                      /" << std::endl;
    std::cout << "\t/    Bruno Cesar & Cristofer Oswald    /" << std::endl;
    std::cout << "\t/   Trabalho de IA. UEM, Maringá, PR   /" << std::endl;
    std::cout << "\t/--------------------------------------/" << std::endl;
    std::cout << std::endl;

}

int main() {
    printInitHeader();

    std::cout << "Iniciando testes..." << std::endl << std::endl;
    runTests(false);
    std::cout << "Testes concluídos!" << std::endl;

    return 0;
}

void runTests(bool create_data){
    std::map<Company, double> initial_shares;
    Market market(2, 1, 2014); //Mudar para data de 2016
    AITraining ai(market);

    if(!create_data){
        readFile("dados2014.txt", market);
        readFile("dados2015.txt", market);
        //readFile("dados2016.txt", market);
    }
    else{
        WorkDay* workday;

        workday = new WorkDay(1, 1, 2014);
        workday->addWorkPaper(new WorkPaper("UPG3", 10, 12, 8, 11, 11.5), Company::CIEL3);
        workday->addWorkPaper(new WorkPaper("WR2", 20, 25, 15, 22, 23.2), Company::GRND3);
        workday->addWorkPaper(new WorkPaper("TF2", 12, 16, 11, 14, 15.6), Company::JSLG3);
        workday->addWorkPaper(new WorkPaper("GGEE", 31, 32, 27, 28, 29.1), Company::LEVE3);

        market.addWorkDay(workday);

        workday = new WorkDay(2, 1, 2014);
        workday->addWorkPaper(new WorkPaper("UPG3", 11.5, 13, 11, 12, 12.1), Company::CIEL3);
        workday->addWorkPaper(new WorkPaper("WR2", 23.2, 27, 20, 23, 26.4), Company::GRND3);
        workday->addWorkPaper(new WorkPaper("TF2", 15.6, 18, 13, 16, 15.8), Company::JSLG3);
        workday->addWorkPaper(new WorkPaper("GGEE", 29.1, 30, 25, 26, 27.2), Company::LEVE3);

        market.addWorkDay(workday);
    }
    ai.trainAI(initial_shares);

    market.addInvestor(new NoInvestor(1., "No", InvestorType::AI));
    market.addInvestor(new MASInvestor(1., "Auto", InvestorType::AI, initial_shares));
    market.startMarket();
}