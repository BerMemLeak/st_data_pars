#include "encoding_converter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <uchardet/uchardet.h> // Подключение библиотеки uchardet
#include <boost/locale.hpp>
#include <string>


std::string convertCRLFtoLF(const std::string& input) {
    std::string result;
    result.reserve(input.size());

    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '\r') {
            // Если после \r идет \n, добавляем только \n
            if (i + 1 < input.size() && input[i + 1] == '\n') {
                result += '\n';
                ++i; // Пропускаем \n
            } else {
                result += '\n'; // Просто добавляем \n
            }
        } else {
            result += input[i];
        }
    }

    return result;
}


// Функция для определения кодировки файла
std::string detect_encoding(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + file_path);
    }

    std::vector<char> raw_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    uchardet_t ud = uchardet_new();
    if (!ud) {
        throw std::runtime_error("Не удалось инициализировать uchardet");
    }

    uchardet_handle_data(ud, raw_data.data(), raw_data.size());
    uchardet_data_end(ud);

    const char* detected_charset = uchardet_get_charset(ud);
    std::string detected_encoding = detected_charset ? detected_charset : "unknown";

    uchardet_delete(ud);

    return detected_encoding;
}

// Функция для преобразования строки из одной кодировки в другую
std::string convert_encoding(const std::string& input, const std::string& from_encoding, const std::string& to_encoding) {
    using namespace boost::locale;
    generator gen;
    std::locale loc = gen("en_US.UTF-8");
    std::locale::global(loc);
//    std::cout << conv::between(input, to_encoding, from_encoding)<< std::endl;
    return conv::between(input, to_encoding, from_encoding);
}

// Функция для преобразования кодировки файла
void convert_file_encoding(const std::string& input_file, const std::string& source_encoding, const std::string& target_encoding) {
    std::ifstream input_stream(input_file, std::ios::binary);
    if (!input_stream.is_open()) {
        std::cerr << "Error: Unable to open input file: " << input_file << std::endl;
        return;
    }

    // Чтение содержимого файла в строку
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    std::string content = buffer.str();
    input_stream.close(); // Закрываем входной поток

    content = convertCRLFtoLF(content);

    // Преобразование содержимого из исходной кодировки в целевую
    std::string converted_content = convert_encoding(content, source_encoding, target_encoding);

    // Создаем имя для нового файла
    const std::string& output_file =   input_file ;

    // Открываем новый файл для записи в новой кодировке
    std::ofstream output_stream(output_file, std::ios::binary);
    if (!output_stream.is_open()) {
        std::cerr << "Error: Unable to create output file: " << output_file << std::endl;
        return;
    }

    // Запись преобразованного содержимого в новый файл
    output_stream << converted_content;
    output_stream.close(); // Закрываем выходной поток

    std::cout << "Файл успешно преобразован и сохранен по пути : " << output_file << std::endl;
}

