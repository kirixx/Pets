#include "MayersRules/RuleN3.h"
#include "CompleteModernC++/Printer.h"
#include "CompleteModernC++/Deleter.h"
#include "CompleteModernC++/StringPractice.h"

int main()
{
    std::cout << "***WEAK PTR USE CASE***\n";
    weakPtrUseCase();
    std::cout << "\n***DELETERS FOR SMART POINTERS***\n";
    Deleter::uniquePtrDeleterTest();
    Deleter::sharedPtrDeleterTest();

    std::cout << "***ALWAYS USE CONST WHEREVER IT POSSIBLE***\n";
    mayersRule3();

    std::cout << "***STRING CONVERSION AND CASE SENSITIVE FIND***\n";
    std::string up = StringPractice::ConvertToCase(std::string("boom"), StringPractice::Case::TO_UPPER);
    std::string low = StringPractice::ConvertToCase(std::string("BAM"), StringPractice::Case::TO_LOWER);
    
    std::string src("RUN boom");
    std::string patt("BOOM");

    size_t pos = StringPractice::Find(src, patt);

    return 0;
}