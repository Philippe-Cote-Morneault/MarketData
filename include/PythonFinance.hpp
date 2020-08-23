#include <string>
#include <curl/curl.h>

namespace python_finance {
    namespace {
        inline std::string formatUrl(const std::string &symbol, long start, long end) {
            return "https://query1.finance.yahoo.com/v8/finance/chart/" +
                   symbol +
                   "?period1=" +
                    std::to_string(start) +
                   "&period2=" +
                    std::to_string(end) +
                   "&interval=1d&events=history";
        }
    }

    inline size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        auto potato = (char*)contents;
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    inline std::string getSymbolChart(const std::string &symbol, long start, long end) {
        CURL *curl = curl_easy_init();
        std::string url = formatUrl(symbol, start, end);
        std::string readBuffer;
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        return readBuffer;
    }
}