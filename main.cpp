#include "Test.h"
#include "DOM_1.h"
#include "DOM_2.h"
#include "DOM_3.h"
#include "DOM_4.h"
#include "DOM_5.h"


int main() {

    DepthOfMarket_1 DOM_1;
    DepthOfMarket_2 DOM_2;
    DepthOfMarket_3 DOM_3;
    DepthOfMarket_4 DOM_4;
    DepthOfMarket_5 DOM_5;
    DomTest Test;

    std::cout << "Начало теста класса DepthOfMarket_1" << std::endl;
    Test.test_methods(DOM_1);
    Test.time_methods(DOM_1);
    std::cout << std::endl;

    std::cout << "Начало теста класса DepthOfMarket_2" << std::endl;
    Test.test_methods(DOM_2);
    Test.time_methods(DOM_2);
    std::cout << std::endl;

    std::cout << "Начало теста класса DepthOfMarket_3" << std::endl;
    Test.test_methods(DOM_3);
    Test.time_methods(DOM_3);
    std::cout << std::endl; 

    std::cout << "Начало теста класса DepthOfMarket_4" << std::endl;
    Test.test_methods(DOM_4);
    Test.time_methods(DOM_4);
    std::cout << std::endl; 

    std::cout << "Начало теста класса DepthOfMarket_5" << std::endl;
    Test.test_methods(DOM_5);
    Test.time_methods(DOM_5);
    std::cout << std::endl; 

    return 1;
}