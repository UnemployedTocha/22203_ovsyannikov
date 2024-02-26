#pragma once
#include <map>
#include <assert.h>
#include "Command.h"

template<class Product, class Id, class Creator>
class Factory {
public:
    static Factory* getInstance() {
        static Factory f;
        return &f;
    }

    Product* createProductByName(const Id& name) {
        auto creator  = creators_.at(name);
        return creator();
    }

    bool regist3r(const Id& name, Creator creator) {
        assert(creator);

        if(isRegist3red(name)) {
            return false;
        }
        creators_[name] = creator;
        return true;
    }

    bool isRegist3red(const Id& name) {
        return creators_.find(name) != creators_.end();
    }

    bool isComplexFuncRegist3red(const Id& name) {
        return complexCreators_.find(name) != complexCreators_.end();
    }

    bool complexFuncRegist3r(const Id& name, Creator creator) {
        assert(creator);

        if(isComplexFuncRegist3red(name)) {
            return false;
        }
        creators_[name] = creator;
        complexCreators_[name] = creator;
        return true;
    }
private:
    Factory() = default;

    std::map<Id, Creator> creators_;
    std::map<Id, Creator> complexCreators_;
};