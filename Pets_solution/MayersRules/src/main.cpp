#include "MayersRules/RuleN3.h"
#include "CompleteModernC++/Printer.h"
#include "CompleteModernC++/Deleter.h"
#include "CompleteModernC++/StringPractice.h"
#include <vector>

namespace TemplateTest
{
    //the example when class and typename is not interchangeably
    template <typename T>
    struct wrapper
    {
        using value_type = T;
        value_type value;
    };

    template <typename T>
    struct foo
    {
        T wrapped_value;
        //you need to return a wrapped value, class is not allowed here.
        typename T::value_type get_wrapped_value() { return wrapped_value.value; }
    };

    //template of template. since c++17 class could be changed on typename.
    template < template < typename, typename > /*here*/class Container, typename Type >
    class Example
    {
        Container< Type, std::allocator < Type > > baz;
    };

}



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


    TemplateTest::foo<TemplateTest::wrapper<int>> f{ {42} };
    std::cout << f.get_wrapped_value() << '\n';

    TemplateTest::Example<std::vector, int> a;

    return 0;
}