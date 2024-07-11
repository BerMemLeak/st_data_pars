#include <iostream>
#include <string>
#include "./parser/Universal_parser.h"
#include "./validation/Data_validator.h"


void print(universal_parser first);
void convert(std::string first_file_csv,std::string second_file_txt );

int main() {
    try {
        universal_parser first("../data/выгрузка.txt");
        universal_parser second("../data/договоры на платное.csv");

        validation_data val(first,second,"../data/", "../data/output.txt");
//        val.compareFiles();
//        print(second);


    }catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;

}



void print(universal_parser first){
    for (const auto& vec1 : first.get_data()) {
            for (const auto& pair : vec1) {
                std::cout << "{" << pair.first << ": " << pair.second << "} ";
            }
            std::cout << std::endl;
    }
    int c = 0;
    for(auto i: first.get_data())
    {
        c++;
    }
    std::cout << c <<std::endl;
}


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