#pragma once
#include <memory>
#include <iostream>

namespace Deleter
{
    struct sDeleterObj
    {
        void operator()(int* p)
        {
            free(p);
            std::cout << "pointer freed by object deleter\n";
        }
    };

    void functionDeleter(int* p)
    {
        free(p);
        std::cout << "pointer freed by function deleter\n";
    }

    void uniquePtrDeleterTest()
    {
        std::cout << "initialize unique ptr through malloc\n";
        //default deleter will call "delete"
        std::unique_ptr<int, sDeleterObj> testWithObject ( (int*)malloc(4), sDeleterObj());
        *testWithObject = 100;
        std::cout << *testWithObject << '\n';
        //for unique ptr in case of using function deleter we need to specify
        //the type of deleter as second parameter in template
        std::unique_ptr<int, void(*) (int*)> testWithFunction((int*)malloc(4), functionDeleter);
        *testWithFunction = 100;
        std::cout << *testWithFunction << '\n';
    }

    void sharedPtrDeleterTest()
    {
        std::cout << "initialize shared ptr through malloc\n";
        //default deleter will call "delete"
        std::shared_ptr<int> testWithObject((int*)malloc(4), sDeleterObj());
        *testWithObject = 100;
        std::cout << *testWithObject << '\n';
        //for shared ptr in case of using function deleter we no need to specify
        //the type of deleter as second parameter in template
        std::shared_ptr<int> testWithFunction((int*)malloc(4), functionDeleter);
        *testWithFunction = 100;
        std::cout << *testWithFunction << '\n';
    }
}
