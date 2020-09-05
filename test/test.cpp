#include <iostream>
#include <time.h>
#include <vector>

#include <curl/curl.h>

#include <library/nasdaq.hpp>
#include <library/yahoo.hpp>

int main() {
    market_data::yahoo_finance::getSymbolChart("MSFT", 1564617600, 1596672000);
    auto j = market_data::yahoo_finance::getSymbolSummary("MSFT");
    std::cout << j["context"]["dispatcher"]["stores"]["QuoteSummaryStore"] .dump(4) << std::endl;

    std::vector<market_data::nasdaq::RealTimeTrade> trades = market_data::nasdaq::getRealTimeTrades("MSFT", "15:00");

    for (int i = 0; i < trades.size(); ++i) {
        std::cout << trades[i].price << std::endl;
    }

    return 0;
}
