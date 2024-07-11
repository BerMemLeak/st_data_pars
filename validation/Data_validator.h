#include <utility>

//
// Created by user on 05.07.2024.
//

#pragma once

class validation_data {
    universal_parser& first;
    universal_parser& second;
    std::string path;
    std::string outputFilename;



public:
    explicit validation_data(universal_parser& first, universal_parser& second, std::string  path,  std::string outputFilename): first(first), second(second), path(std::move(path)) , outputFilename(std::move(outputFilename)){
        compareFiles();
    }
private:
    void compareFiles(){
        std::ofstream outputFile(outputFilename);
        if (!outputFile.is_open()) {
            std::cerr << "Не получилось открыть файл: " << outputFilename << std::endl;
            return;
        }

        std::string goodValidation = "\n\nПравильные данные: \n"; //строка с правильными челиками
        std::string noPers= "\n\nВ файле приемки записей про таких людей нет:\n"; // нет микрочела
        std::string badValidation = "\n\nОшибка в заполненых данных:\n"; // ошибки в заполнении

        int a = 0;
        //сравниваю каждую строчку с каждой
        try {
            for(const auto &vec1 : first.get_data()){
                bool contest_quid = false;
                bool cafedra_quid = false;
                bool found = false;
                for(const auto &vec2 : second.get_data()){
                    //перевести в нижний регистр?

                    //проверка, есть ли чеговек такой

                    if  ((vec1.at("Фамилия") == vec2.at("Фамилия абитуриента")) and (vec1.at("Имя") == vec2.at("Имя абитуриента")) and (vec1.at("Отчество") == vec2.at("Отчество абитуриента")) and (vec1.at("ДатаРождения") == vec2.at("Дата рождения абитуриента"))){
                        if(vec1.at("QUID_конкурса") == vec2.at("GUID конкурса")){contest_quid = true;}
                        if(vec1.at("QUID_кафедры") == vec2.at("GUID кафедры")){cafedra_quid = true;}
//                        std::cout<< vec1.at("GUID конкурса")<< std::endl;
                        found = true;
                    }
                    if(found and cafedra_quid and contest_quid){
                        //тут все хорошо сделать запись и выйти во внешний цикл
                        goodValidation +="\n"+vec1.at("Фамилия")+" "+ vec1.at("Имя") + " " + vec1.at("Отчество") + " - сходятся все данные";
                        break;
                    }
                }
                if(!found){
                    //сделать запись, что микрочелика нету
                    noPers += "\n"+vec1.at("Фамилия")+" "+ vec1.at("Имя") + " " + vec1.at("Отчество");
                }
                if(found and !contest_quid and !cafedra_quid){
                    //неправильный quid кокурса и куид кафедры
                    badValidation += "\n" + vec1.at("Фамилия")+" "+ vec1.at("Имя") + " " + vec1.at("Отчество") + " - неправильный quid кокурса и quid кафедры ";
                }
                if(found and contest_quid and !cafedra_quid){
                    //неправильный  куид кафедры
                    badValidation += "\n" + vec1.at("Фамилия")+" "+ vec1.at("Имя") + " " + vec1.at("Отчество") + " - неправильный quid кафедры ";
                }
                if(found and !contest_quid and cafedra_quid){
                    //неправильный  куид конкурса
                    badValidation += "\n" + vec1.at("Фамилия")+" "+ vec1.at("Имя") + " " + vec1.at("Отчество") + " - неправильный quid конкурса ";
                }
            }
            outputFile << goodValidation;
            outputFile << noPers ;
            outputFile << badValidation;
            outputFile.close();
        }catch (const char* error_message)
        {
            std::cout << error_message << std::endl;
        }


//        ликвидность quid по имени фамилии и дате
//        проверить по всем возможным полям тхт файла
        // создаю файл с 3 секциями:
        // 1 ошибки и их описание
        // 2 ненайденные микрочелы
        // 3 все правильно
    }

};







