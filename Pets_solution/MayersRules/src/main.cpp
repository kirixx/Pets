#include "MayersRules/RuleN3.h"
#include "CompleteModernC++/Printer.h"
#include "CompleteModernC++/Deleter.h"

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

int main()
{
    while (true)
    {
        switch (chooseTheTest())
        {
        case eTests::COMPLETE_MODERN_Cpp:
            std::cout << "***WEAK PTR USE CASE***\n";
            weakPtrUseCase();
            std::cout << "\n***DELETERS FOR SMART POINTERS***\n";
            Deleter::uniquePtrDeleterTest();
            Deleter::sharedPtrDeleterTest();
            break;
        case eTests::MAYERS_RULES:
            std::cout << "***ALWAYS USE CONST WHEREVER IT POSSIBLE***\n";
            mayersRule3();
            break;
        default:
            std::cout << "choose another one\n";
            break;
        }
    }

    return 0;
}