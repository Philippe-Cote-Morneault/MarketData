#ifndef MARKET_DATA_YAHOO_YAHOO_HPP_
#define MARKET_DATA_YAHOO_YAHOO_HPP_

#include <string>
#include <curl/curl.h>

#include <nlohmann/json.hpp>
#include <market_data/api.hpp>
#include <market_data/yahoo/yahoo.inl>

namespace market_data {
    namespace yahoo {
        namespace {
            std::string formatUrl(const std::string &symbol, long start, long end);
        }

        size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
            ((std::string *) userp)->append((char *) contents, size * nmemb);
            return size * nmemb;
        }

        std::string getSymbolChart(const std::string &symbol, long start, long end);

        nlohmann::json getSymbolSummary(const std::string &symbol);
    }
}

#if defined(LIBRARY_HEADER_ONLY)
#include <market_data/yahoo/yahoo.cpp>
#endif

#endif