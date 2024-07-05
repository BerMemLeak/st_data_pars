#include <iostream>
#include <string>
#include "./parser/Universal_parser.h"

void convert(std::string first_file_csv,std::string second_file_txt ){
    /*
     * Функция конвертирования файлов, перезаписывает файлы в читаемый формат
     * из кодировки cp1251 --> utf-16 для файла приемки  ##### тут csv файл
     * из cp1251 --> utf-16 для файла из базы access   ##### тут txt файл
     *
     * @param first_file_csv файл приемной комиссии.
     * @param second_file_txt файл из бд.
     * .
     */

}

int main() {
//    try {
//        database_txt_parser database_csv("ini.txt");
//        selection_committee_parser selection_committee("ini.txt");
//        std::cout << "Значение: " << "asd" << std::endl;
//    } catch (const std::exception& e) {
//        std::cerr << "Ошибка: " << e.what() << std::endl;
//    }
    universal_parser database_csv("../data/выгрузка.txt");



    for (const auto& vec1 : database_csv.get_data()) {
        for (const auto& map : vec1) {
            for (const auto& pair : map) {
                std::cout << "{" << pair.first << ": " << pair.second << "} ";
            }
            std::cout << std::endl;
        }
    }
    int c = 0;
    for(auto i: database_csv.get_data())
    {
        c++;
    }
    std::cout << c <<std::endl;
//    database_txt_parser asd("../data/договоры на платное.csv");
    return 0;
}
