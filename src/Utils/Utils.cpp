#include "Utils.h"

#include <algorithm>

#include <iostream>


std::string convert_number_to_string(int number) {
    std::string result;

    while (number > 0) {
        result += number % 10 + '0';
        number /= 10;
    }

    std::reverse(result.begin(), result.end());

    return result;
}

int convert_string_to_number(std::string string_number) {
    int result = 0;
    for (auto it : string_number) {
        if (it == '-') continue;
        result = result * 10 + it - '0';
    }
    if (string_number[0] == '-')
        result *= (-1);
    return result;
}

bool cmp_by_title(const Movie& a, const Movie& b) {
    return a.get_title() < b.get_title();
}

bool cmp_by_actor(const Movie& a, const Movie& b) {
    return a.get_actor() < b.get_actor();
}

bool cmp_by_year_and_gen(const Movie& a, const Movie& b) {
    if (a.get_year() != b.get_year())
        return a.get_year() < b.get_year();
    return a.get_gen() < b.get_gen();
}


std::string get_first_field(std::string& input, const char& delim) {
    size_t delim_pos = input.find(delim);
    std::string field = input.substr(0, delim_pos);
    input = input.substr(delim_pos + 1);
    return field;
}