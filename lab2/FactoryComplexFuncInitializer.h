#pragma once

#include "Factory.h"
#include "Command.h"

template<class ExactCommand>
class FactoryComplexFuncInitializer{
public:
    FactoryComplexFuncInitializer(const std::string& Id) {
        bool x =  Factory<Command, std::string, Command *(*)()>::getInstance()
                ->complexFuncRegist3r(Id, createExactCommand);
    }
private:
    static Command *createExactCommand() {
        return new ExactCommand();
    }
};
