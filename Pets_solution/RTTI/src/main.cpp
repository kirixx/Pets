#include <iostream>
#include "Vehicles/Car.h"

int main()
{
    std::cout << RTTI::IsDerived<CCar>::from<CVehicle>() << std::endl;
    
    system("pause");

    return 0;
}