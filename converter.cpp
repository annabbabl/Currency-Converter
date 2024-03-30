#include "converter.h"

size_t Converter::write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

float Converter::parse_response(const std::string &response) {
    // since we get the value for the one currency, the api of the webapp returns us only one "value:" option
    // so we can just search for it
    int index = response.find("\"value\":");
    if(index != std::string::npos){ // if found
        index += strlen("\"value\":");
        std::string number;

        // just filling the number variable until we reach to the end of the number
        while(response[index] != '}'){
            number += response[index];
            index++;
        }

        return std::stof(number); // stof function converts string to float
    }

    return 0.0f;
}

Converter::Converter()
{
    // we get the api key from the file and then create corresponding url address
    std::ifstream userdata_input("userdata.txt");
    userdata_input >> m_api_key;
    std::cout << m_api_key << std::endl;
    m_url = "https://api.currencyapi.com/v3/latest?apikey=" + m_api_key;
    m_historical_url = "https://api.currencyapi.com/v3/historical?apikey=" + m_api_key;
    userdata_input.close();
}

const std::vector<QString> &Converter::get_currencies() const
{
    return m_currencies;
}

float Converter::convert(const std::string &from, const std::string &to, float value)
{
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        std::string request_url = m_url + "&currencies=" + to + "&base_currency="+from;
        std::cout << request_url << std::endl;
        curl_easy_setopt(curl, CURLOPT_URL, request_url.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            std::cerr << "Something went wrong when performing curl http request!" << std::endl;

        curl_easy_cleanup(curl);

        float rate = parse_response(response);

        return value*rate; // doing the converting magic

    } else std::cerr << "Unable to start curl!" << std::endl;

    return 0.0f;
}

std::vector<std::pair<Date,float>> Converter::get_history(const std::string& base,const std::string& into, const Date &from, const Date &to) {
    std::vector<std::pair<Date,float>> data;
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        std::string request_url_base = m_historical_url + "&currencies=" + into +"&base_currency="+base + "&date=";
        for(Date i= from; i <= to; ++i){
            std::string request = request_url_base + i.get_date();
            curl_easy_setopt(curl, CURLOPT_URL, request.c_str());

            res = curl_easy_perform(curl);
            if(res != CURLE_OK)
                std::cerr << "Something went wrong when performing curl http request!" << std::endl;
            
            data.push_back(std::pair<Date,float>(i,parse_response(response)));
            response.clear();
        }

        curl_easy_cleanup(curl);
        return data;

    } else std::cerr << "Unable to start curl!" << std::endl;

    return data;
}
std::vector<std::pair<Date,float>> Converter::get_history(const std::string& base,const std::string& into, const std::vector<Date>& dates) {
    std::vector<std::pair<Date,float>> data;
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        std::string request_url_base = m_historical_url + "&currencies=" + into +"&base_currency="+base + "&date=";
        for(int i =0; i <dates.size();i++){
            std::string request = request_url_base + dates[i].get_date();
            curl_easy_setopt(curl, CURLOPT_URL, request.c_str());

            res = curl_easy_perform(curl);
            if(res != CURLE_OK)
                std::cerr << "Something went wrong when performing curl http request!" << std::endl;
            
            data.push_back(std::pair<Date,float>(dates[i],parse_response(response)));
            response.clear();
        }

        curl_easy_cleanup(curl);
        return data;

    } else std::cerr << "Unable to start curl!" << std::endl;

    return data;
}
