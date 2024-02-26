#pragma once

#include "Factory.h"
#include "Command.h"

template<class ExactCommand>
class FactoryInitializer{
public:
    FactoryInitializer(const std::string& Id) {
        bool x =  Factory<Command, std::string, Command *(*)()>::getInstance()
                ->regist3r(Id, createExactCommand);
    }
private:
    static Command *createExactCommand() {
        return new ExactCommand();
    }
};
