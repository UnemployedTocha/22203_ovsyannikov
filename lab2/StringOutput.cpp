#include "StringOutput.h"
#include <iostream>
#include "FactoryInitializer.h"

void StringOutput::Execute(std::stack<int>& numbers_, std::ifstream& inputFile){
//    Factory<Command, std::string, Command *(*)()>* pFactory =  Factory<Command, std::string, Command *(*)()>::getInstance()
    std::string s;
    

}

namespace {
    FactoryInitializer<StringOutput> Registration(".\"");
}