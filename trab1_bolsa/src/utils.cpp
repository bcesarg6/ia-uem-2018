//
// Created by cristofer on 04/05/18.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include "include/utils.h"

void readFile(std::string file_name, Market& market){
    std::string line;
    std::ifstream file(file_name);
    Company company_code;
    WorkDay* workday;
    WorkDay* previous = nullptr;
    char* in;

    int year, month, day;
    float openp, maxp, minp, avgp, lastp;

    if(file){
        while(std::getline(file, line)){
            in = (char*)malloc(sizeof(char) * 13);

            line.copy(in, 4, 2); //reads year
            in[4] = '\0';
            year = atoi(in);

            free(in);
            in = (char*)malloc(sizeof(char) * 13);

            line.copy(in, 2, 6); //reads year
            in[2] = '\0';
            month = atoi(in);

            free(in);
            in = (char*)malloc(sizeof(char) * 13);

            line.copy(in, 2, 8); //reads year
            in[2] = '\0';
            day = atoi(in);

            free(in);
            in = (char*)malloc(sizeof(char) * 13);

            line.copy(in, 12, 12);
            in = strtok(in, " ");
            std::string company_name(in);
            company_code = Market::getCompanyCode(company_name);

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.insert(67, ".");
            line.copy(in, 14, 56);
            openp = static_cast<float>(atof(in));

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.insert(81, ".");
            line.copy(in, 14, 70);
            maxp = static_cast<float>(atof(in));

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.insert(95, ".");
            line.copy(in, 14, 84);
            minp = static_cast<float>(atof(in));

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.insert(109, ".");
            line.copy(in, 14, 98);
            avgp = static_cast<float>(atof(in));

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.insert(123, ".");
            line.copy(in, 14, 112);
            lastp = static_cast<float>(atof(in));

            workday = market.getWorkDayByDate(day, month, year);
            if(!workday){
                workday = new WorkDay(day, month, year);
                workday->previous = previous;
                previous = workday;
                market.addWorkDay(workday);
            }

            workday->addWorkPaper(new WorkPaper(company_name, openp, maxp, minp, avgp, lastp), company_code);

        }
    }
    else{
        std::cout << "Erro ao abrir arquivo " << file_name << std::endl;
    }
}