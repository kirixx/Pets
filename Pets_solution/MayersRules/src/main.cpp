#include "MayersRules/RuleN3.h"

int main()
{
    CRuleN3 nonConstUsing("Some Text");

    std::cout << nonConstUsing[0] << '\n';
    
    const CRuleN3 constUsing("Some Text");

    std::cout << constUsing[1] <<'\n';

    system("pause");

    return 0;
}