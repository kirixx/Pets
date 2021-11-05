#include "MayersRules/RuleN3.h"
#include "CompleteModernC++/Printer.h"
#include "CompleteModernC++/Deleter.h"
#include "CompleteModernC++/StringPractice.h"
#include <vector>
#include <future>

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

    template<class T> 
    T Add(T x, T y)
    {
        T sum = x + y;
        std::cout << __FUNCSIG__ << sum << '\n';
        return sum;
    }

    template <class T>
    T ArraySum(T* pArray, T size)
    {
        T retVal = 0;
        for (T i = 0; i < size; ++i)
        {
            retVal += pArray[i];
        }
        std::cout << __FUNCSIG__ << retVal << '\n';
        return retVal;
    }

    template <class T>
    T Max(T* pArray, T size)
    {
        T retVal = size > 0 ? pArray[0] : 0;
        for (T i = 0; i < size; ++i)
        {
            retVal = pArray[i] > retVal ? pArray[i] : retVal;
        }
        std::cout << __FUNCSIG__ << retVal << '\n';
        return retVal;
    }

    //variadic
    void Print() {
        std::cout << std::endl;
    }

    //Template parameter pack
    template<typename T, typename...Params>
    //Function parameter pack
    void Print(T&& a, Params&&... args) {
        //std::cout << sizeof...(args) << std::endl;
        //std::cout << sizeof...(Params) << std::endl;
        std::cout << a;
        if (sizeof...(args) != 0) {
            std::cout << ",";
        }
        //We can forward a function parameter pack
        Print(std::forward<Params>(args)...);
    }

    /*
    1. Print(1, 2.5, 3, "4") ;
    2. Print(2.5, 3, "4") ;
    3. Print(3, "4") ;
    4. Print("4") ;
    5. Print() ;
    */



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
    
    TemplateTest::Add(3, 5);
    int ar[] = { 1,2,3,4 };
    TemplateTest::ArraySum(ar, 4);
    TemplateTest::Max(ar, 4);

    TemplateTest::Print(0, 1, 2, 4.5, "BOOM");

    return 0;
}