//
// Created by user on 04.07.2024.
//
#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <stdexcept>
#include <regex>
#include <string>

class universal_parser {
private:
    std::vector<std::map<std::string, std::string>> data;
    std::string filename;
public:
    explicit universal_parser(const std::string& filename):filename(std::move(filename))  {
        parse_file();
    }
    void parse_file() {

        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл");
        }
        std::string line;
        static const std::regex rdelim{";"}; // задаем разделитель
        int line_index = 0;
        int data_field_count = 0;
        std::vector<std::string> cols_name;

        // обработка строки столбцов
        const std::sregex_token_iterator end; // итератор конца последовательности

        if (std::getline(file, line)) {
            const std::sregex_token_iterator end; // итератор конца последовательности
            for (std::sregex_token_iterator it(line.begin(), line.end(), rdelim, -1); it != end; it++) {
                std::string token = *it; // Извлекаем текущий токен как строку
                // Удаление кавычек из токена
                token.erase(std::remove(token.begin(), token.end(), '"'), token.end());
                cols_name.push_back(token) ; // Записываем очищенный токен в person_data
            }
        } else {
            throw std::runtime_error("Файл пустой или не содержит заголовков столбцов");
        }
        while (std::getline(file, line)) {
            int data_index = 0;
            std::map<std::string, std::string> person_data;
            const std::sregex_token_iterator end1; // итератор конца последовательности
            for (std::sregex_token_iterator it(line.begin(), line.end(), rdelim, -1); it != end1; it++) {
                std::string token = *it; // Извлекаем текущий токен как строку
                // Удаление кавычек из токена
                token.erase(std::remove(token.begin(), token.end(), '"'), token.end());
                person_data[cols_name[data_index]] = token; // Записываем очищенный токен в person_data
                data_index++;
            }
            if (line_index < this->data.size()) {
                this->data.push_back(person_data);
            } else {
                this->data.push_back({person_data});
            }
            line_index++;
        }
        file.close(); // закрываем файл после чтения
    }
    std::vector<std::map<std::string, std::string>> get_data(){
        return this->data;
    }
};


