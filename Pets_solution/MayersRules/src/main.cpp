#include "MayersRules/RuleN3.h"
#include "CompleteModernC++/Printer.h"

enum class eTests
{
    COMPLETE_MODERN_Cpp = 1,
    MAYERS_RULES = 2
};

eTests chooseTheTest()
{
    uint16_t test = 0;
    std::cout << "1.Complete Modern C++ tests\n" <<
                 "2.Mayers rules\n";
    std::cin >> test;
    std::cout << '\n';
    return static_cast<eTests>(test);
}

void weakPtrUseCase()
{
    Printer obj;
    std::shared_ptr<int> weakTest = std::make_shared<int>(11);
    std::shared_ptr<int> sharedTest = std::make_shared<int>(11);
    obj.setWeakValue(weakTest);
    obj.setSharedValue(sharedTest);

    std::cout << "free the resources of shared and weak pointers\n";
    weakTest = nullptr;
    sharedTest = nullptr;
  
    obj.printSharedP();
    obj.printWeakP();
}

void mayersRule3()
{
    std::cout << "Rule N3 use the const modifier wherever it possible\n";
    
    CRuleN3 nonConstUsing("Non Const");

    std::cout << nonConstUsing[0] << '\n';

    const CRuleN3 constUsing("Const");

    std::cout << constUsing[1] << '\n';
}

int main()
{
    while (true)
    {
        switch (chooseTheTest())
        {
        case eTests::COMPLETE_MODERN_Cpp:
            weakPtrUseCase();
            break;
        case eTests::MAYERS_RULES:
            mayersRule3();
            break;
        default:
            std::cout << "choose another one\n";
            break;
        }
    }

    return 0;
}