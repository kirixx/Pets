#pragma once
#include <string>
#include <iostream>

//always use const
class CRuleN3
{
    //TextBlock
public:
    CRuleN3(const std::string text) : mText(text)
    {}

    //operator for constant objects
    const char& operator[] (std::size_t position) const
    {
        std::cout << "const operator \n";
        /*
            some code 
        */
        return mText[position];
    }

    //operator for non-constant objects
    char& operator[](std::size_t position)
    {
        std::cout << "non const operator \n";
        //avoiding code duplication by calling const function from non const function
        return const_cast<char&>(static_cast<const CRuleN3&>(*this)[position]);
    }
private:
    std::string mText;
};

void mayersRule3()
{
    std::cout << "Rule N3 use the const modifier wherever it possible\n";

    CRuleN3 nonConstUsing("Non Const");

    std::cout << nonConstUsing[0] << '\n';

    const CRuleN3 constUsing("Const");

    std::cout << constUsing[1] << '\n';
}