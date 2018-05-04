//
// Created by cristofer on 04/05/18.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include "include/Utils.h"

void readFile(std::string file_name, Market* market){
    std::string line;
    std::ifstream file(file_name);
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
            std::string company_code(in);

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.copy(in, 13, 56);
            std::cout << in;

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.copy(in, 13, 69);

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.copy(in, 13, 81);

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.copy(in, 13, 94);

            free(in);
            in = (char*)malloc(sizeof(char) * 13);
            line.copy(in, 13, 107);

            std::cin >> line;
        }
    }
    else{
        std::cout << "Erro ao abrir arquivo " << file_name << std::endl;
    }
}