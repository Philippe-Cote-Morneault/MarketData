#include <iostream>
#include "../include/PythonFinance.hpp"

int main() {
    std::cout << python_finance::getSymbolChart("MSFT", 1564617600, 1596672000) << std::endl;
    return 0;
}
