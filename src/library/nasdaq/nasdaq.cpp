#include "nasdaq.hpp"

namespace market_data {
    namespace nasdaq {
        namespace {
            inline std::string formatUrl(const std::string &symbol, const std::string &time, int limit) {
                return "https://api.nasdaq.com/api/quote/" +
                       symbol +
                       "/realtime-trades?&limit=" +
                       std::to_string(limit) +
                       "&fromTime=" +
                       time;
            }
        }

        size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
        {
            ((std::string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        }

        void to_json(nlohmann::json& j, const RealTimeTrade& p) {
            j = nlohmann::json{{"nlsTime", p.time}, {"nlsPrice", p.price}, {"nlsShareVolume", p.shareVolume}};
        }

        void from_json(const nlohmann::json& j, RealTimeTrade& p) {
            j.at("nlsTime").get_to(p.time);
            j.at("nlsPrice").get_to(p.price);
            j.at("nlsShareVolume").get_to(p.shareVolume);
        }

        std::vector<RealTimeTrade> getRealTimeTrades(const std::string &symbol, std::string time, int limit) {
            CURL *curl = curl_easy_init();
            struct curl_slist *list = NULL;
            list = curl_slist_append(list, "accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9");
            list = curl_slist_append(list, "accept-encoding: gzip, deflate, br");
            list = curl_slist_append(list, "accept-language: en-US,en;q=0.9,fr;q=0.8");
            std::string url = formatUrl(symbol, time, limit);
            std::string readBuffer;

            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
                curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
                curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }

            auto j = nlohmann::json::parse(readBuffer);

            std::vector<RealTimeTrade> trades = j["data"]["rows"];

            return trades;
        }
    }
}

