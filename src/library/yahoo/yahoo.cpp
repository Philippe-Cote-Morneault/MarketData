#include "yahoo.hpp"
namespace market_data {
    namespace yahoo {
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

        inline size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
            ((std::string *) userp)->append((char *) contents, size * nmemb);
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

        inline nlohmann::json getSymbolSummary(const std::string &symbol) {
            CURL *curl = curl_easy_init();
            std::string url = "https://finance.yahoo.com/quote/" + symbol;

            std::string readBuffer;
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }

            size_t firstPos = readBuffer.find("root.App.main = ");
            size_t secondPos = readBuffer.find("(this)", firstPos);

            nlohmann::json j = nlohmann::json::parse(readBuffer.substr(firstPos + 16, secondPos - 3 - firstPos - 16));

            return j;
        }
    }
}