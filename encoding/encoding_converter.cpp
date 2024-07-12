#include "encoding_converter.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <uchardet/uchardet.h> // Подключение библиотеки uchardet

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

#include <filesystem> // Для работы с файловой системой (доступно в C++17 и выше)

void convert_file_encoding(const std::string& input_file, const std::string& source_encoding, const std::string& target_encoding) {
    std::ifstream input_stream(input_file);
    if (!input_stream.is_open()) {
        std::cerr << "Error: Unable to open input file: " << input_file << std::endl;
        return;
    }

    // Чтение содержимого файла в строку
    std::stringstream buffer;
    buffer << input_stream.rdbuf();
    std::string content = buffer.str();
    input_stream.close(); // Закрываем входной поток


    //тут нужна функция iconv !!!!!!!!


    // Открываем новый файл для записи в новой кодировке а ее нету(((
    std::ofstream output_stream(input_file);
    if (!output_stream.is_open()) {
        std::cerr << "Error: Unable to create output file: " << input_file << std::endl;
        return;
    }

    // Запись содержимого обратно в файл с новой кодировкой
    output_stream << content;
    output_stream << "123";
    output_stream.close(); // Закрываем выходной поток

}