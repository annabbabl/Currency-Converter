#ifndef CONVERTER_H
#define CONVERTER_H
#include <vector>
#include <unordered_map>
#include <string>
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <QString>
#include "date.h"

class Converter
{
public:
    Converter();

    const std::vector<QString>& get_currencies() const;

    float convert(const std::string& from, const std::string& to, float value);
    std::vector<std::pair<Date,float>> get_history(const std::string& base,const std::string& into, const Date &from, const Date &to);
    std::vector<std::pair<Date,float>> get_history(const std::string& base,const std::string& into, const std::vector<Date>& dates);// with specific dates
private:
    static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);
    float parse_response(const std::string& response);

    std::string m_api_key;
    std::string m_url;
    std::string m_historical_url; // to send requests about history

    std::vector<QString> m_currencies{"USD","GBP", "EUR", "CAD", "AUD", "JPY","CNY"};


};

#endif // CONVERTER_H
