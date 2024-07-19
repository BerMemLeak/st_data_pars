#include <iostream>
#include <string>
#include "./parser/Universal_parser.h"
#include "./validation/Data_validator.h"
#include "./encoding/encoding_converter.h"
//#include <QApplication>
//#include "./ui/mainwindow.h"




void print(universal_parser first);
bool is_txt_file(const std::string& file_path);
bool is_csv_file(const std::string& file_path);
bool is_file(const std::string& str);

int main(int argc, char *argv[]) {
    try {
        std::cout << "Введите путь к первому файлу с расширением .txt (Выгрузка в ПК)\nпуть к файлу :";
        std::string file1;
        std::getline(std::cin, file1);

        // Проверка расширения файла
        while (!is_txt_file(file1)) {
            std::cout << "\nОшибка: Файл должен иметь расширение .txt" << std::endl;
            std::cout << "Введите путь к первому файлу с расширением .txt (Выгрузка в ПК)\nпуть к файлу :";
            std::getline(std::cin, file1); // Считывание строки целиком
        }

        // Продолжение работы с файлом
        std::cout << "Файл принят: " << file1 << std::endl;
        std::string source_encoding1 = detect_encoding(file1);
        std::cout << "\nОпределенная кодировка: " << source_encoding1 << std::endl;
        std::string target_encoding1 = "utf-8";
        convert_file_encoding(file1, source_encoding1, target_encoding1);
        std::cout << "Файл " << file1 << " успешно конвертирован в " << target_encoding1 << std::endl;

        std::cout << "\n\n\nВведите путь ко второму файлу с расширением .csv (Договоры на платное обучение)\nпуть к файлу :";
        std::string file2;
        std::getline(std::cin, file2);

        // Проверка расширения файла
        while (!is_csv_file(file2)) {
            std::cout << "\nОшибка: Файл должен иметь расширение .csv" << std::endl;
            std::cout << "Введите путь ко второму файлу с расширением .csv (Договоры на платное обучение)\nпуть к файлу :";
            std::getline(std::cin, file2); // Считывание строки целиком
        }

        std::string source_encoding2 = detect_encoding(file2);
        std::cout << "\n\nОпределенная кодировка: " << source_encoding2 << std::endl;
        std::string target_encoding2 = "utf-8";
        convert_file_encoding(file2, source_encoding2, target_encoding2);
        std::cout << "Файл " << file2 << " успешно конвертирован в " << target_encoding2 << std::endl;

        universal_parser first(file1);
        universal_parser second(file2);
        std::cout <<"\nВыберите путь для выходного файла(нужно указать папку)\nпуть к папке :";
        std::string outputPath;
        std::getline(std::cin, outputPath);
        while (is_file(outputPath)){
            std::cout << "\nОшибка: Либо в пути присутствует точка, либо вы передали путь к файлу, а надо в папку .csv\n" << std::endl;
            std::cout <<"\nВыберите путь для выходного файла(нужно указать папку)\nпуть к папке :";
            std::getline(std::cin, outputPath);
        }
        outputPath += "/ouput.txt";
        validation_data val(first, second, outputPath);
        // print(first);

    } catch (const std::exception& e) {
        std::cerr << "Ошибка : " << e.what() << std::endl;
        return 1;
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

bool is_csv_file(const std::string& file_path) {
    // Проверяем, что файл имеет расширение .csv
    return file_path.size() >= 4 && file_path.substr(file_path.size() - 4) == ".csv";
}
bool is_file(const std::string& str) {
    for (char ch : str) {
        if (ch == '.') {
            return true;
        }
    }
    return false;
}
bool is_txt_file(const std::string& filename) {
    // Проверяем, что файл имеет расширение .txt
    return filename.size() > 4 && filename.substr(filename.size() - 4) == ".txt";
}