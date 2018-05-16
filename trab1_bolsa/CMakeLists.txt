cmake_minimum_required(VERSION 3.10)
project(trab1_bolsa)

set(CMAKE_CXX_STANDARD 11)

add_executable(trab1_bolsa src/main.cpp src/WorkDay.cpp src/include/WorkDay.h src/WorkPaper.cpp src/include/WorkPaper.h src/Market.cpp src/include/Market.h src/include/BaseInvestor.h src/include/Company.h src/UserInvestor.cpp src/include/UserInvestor.h src/include/utils.h src/utils.cpp src/BaseInvestor.cpp src/NoInvestor.cpp src/include/NoInvestor.h src/MMSInvestor.cpp src/include/MMSInvestor.h src/AITraining.cpp src/include/AITraining.h src/MMEInvestor.cpp src/include/MMEInvestor.h)