#include <iostream>
#include <time.h>
#include <vector>

#include "../include/PythonFinance.hpp"
#include "../include/Nasdaq.hpp"

int main() {
    yahoo_finance::getSymbolChart("MSFT", 1564617600, 1596672000);
    auto j = yahoo_finance::getSymbolSummary("MSFT");
    std::cout << j["context"]["dispatcher"]["stores"]["QuoteSummaryStore"] .dump(4) << std::endl;

    std::vector<yahoo_finance::nasdaq::RealTimeTrade> trades = yahoo_finance::nasdaq::getRealTimeTrades("MSFT", "15:00");

    for (int i = 0; i < trades.size(); ++i) {
        std::cout << trades[i].price << std::endl;
    }
    return 0;
}
