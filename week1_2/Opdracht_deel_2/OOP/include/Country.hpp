#pragma once
#include <string>

class Country
{
    public:
        Country(std::string name) : name(name) {}

        const std::string& get_name()
        {
            return name;
        }

        void print();
    protected:
        std::string name;
};