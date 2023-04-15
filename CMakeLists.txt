cmake_minimum_required(VERSION 3.24)
project(find_Simplified C)

set(CMAKE_C_STANDARD 99)



add_executable(myfind main.c findFunctionality.c findFunctionality.h inputProcessing.c inputProcessing.h expressionFunctions.c expressionFunctions.h linkedLists.c linkedLists.h helperFunctions.c helperFunctions.h)
