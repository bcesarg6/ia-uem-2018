#include <iostream>
#include "include/Market.h"
#include "include/UserInvestor.h"
#include "include/utils.h"
#include "include/NoInvestor.h"
#include "include/ConfMMSInvestor.h"
#include "include/AITraining.h"
#include "include/MMSInvestor.h"
#include "include/OracleInvestor.h"

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
    int mode;
    std::map<Company, double> initial_shares;
    std::map<Company,double> confiability;
    Market market(4, 1, 2016); //Mudar para data de 2016
    AITraining ai(market, 0.1, 0.05, 0.0002, 0.0002);

    if(!create_data){
        WorkDay* prev;
        prev = readFile("dados2014.txt", market, nullptr);
        prev = readFile("dados2015.txt", market, prev);
        readFile("dados2016.txt", market, prev);
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
    ai.trainAI(initial_shares, confiability);

    std::cout << "Digite 1 para MMS com confiabilidade, 2 para MMS simples, 3 para automático, 4 para oráculo e 5 para entrada do usuário..." << std::endl;
    std::cin >> mode;

    switch (mode){
        case 1:
            market.addInvestor(new ConfMMSInvestor(1., "MMS investor", InvestorType::AI, initial_shares, confiability, 15));
            break;
        case 2:
            market.addInvestor(new MMSInvestor(1., "MMS investor", InvestorType::AI, initial_shares, 180));
            break;
        case 3:
            market.addInvestor(new NoInvestor(1., "Auto", InvestorType::AI));
            break;
        case 4:
            market.addInvestor(new OracleInvestor(1., "Auto", InvestorType::AI));
            break;
        case 5:
            market.addInvestor(new UserInvestor(1., "Auto", InvestorType::USER));
            break;
        default:
            std::cout << "Entrada inválida, iniciando com MMS simples" <<std::endl;
            market.addInvestor(new MMSInvestor(1., "MMS investor", InvestorType::AI, initial_shares, 180));
    }
    //market.addInvestor(new ConfMMSInvestor(1., "MMS investor", InvestorType::AI, initial_shares, confiability, 15));
    market.startMarket();
}