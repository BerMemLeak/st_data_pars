#include <iostream>
#include <string>
#include "./parser/Universal_parser.h"
#include "./validation/Data_validator.h"
#include "./encoding/encoding_converter.h"
//#include <QApplication>
//#include "./ui/mainwindow.h"




void print(universal_parser first);
void convert(std::string first_file_csv,std::string second_file_txt );

int main(int argc, char *argv[]) {

    try {
        std::string file1 = "../data/1.txt";
        std::string source_encoding1 = detect_encoding(file1);
        std::cout << "Определенная кодировка: " << source_encoding1 << std::endl;
        std::string target_encoding1 = "utf-8";
        convert_file_encoding(file1, source_encoding1, target_encoding1);
        std::cout << "Файл " << file1 << " успешно конвертирован в " << target_encoding1 << std::endl;

        std::string file2 = "../data/2.csv";
        std::string source_encoding2 = detect_encoding(file2);
        std::cout << "Определенная кодировка: " << source_encoding2 << std::endl;
        std::string target_encoding2 = "utf-8";
        convert_file_encoding(file2, source_encoding2, target_encoding2);
        std::cout << "Файл " << file2 << " успешно конвертирован в " << target_encoding2 << std::endl;

        universal_parser first(file1);
        universal_parser second(file2);


//        QApplication app(argc, argv);
//        MainWindow w;
//        w.show();
//        return app.exec();

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