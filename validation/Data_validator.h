#include <utility>

//
// Created by user on 05.07.2024.
//

#pragma once

class validation_data {
    universal_parser& first;
    universal_parser& second;
    std::string path;


public:
    explicit validation_data(universal_parser& first, universal_parser& second, std::string  path): first(first), second(second), path(std::move(path)){
        compareFiles();
    }
//private:
    void compareFiles(){
        //сравниваю каждую строчку с каждой
        for(const auto &vec1 : first.get_data()){
            bool flag = false;
            for(const auto &vec2 : second.get_data())
            if(vec1.at("Фамилия") == vec2.at("Фамилия абитуриента")){
                flag = true ;
                std::cout<< "asdas";
            }
        }


//        ликвидность quid по имени фамилии и дате
//        проверить по всем возможным полям тхт файла
        // создаю файл с 3 секциями:
        // 1 ошибки и их описание
        // 2 ненайденные микрочелы
        // 3 все правильно
    }

};


