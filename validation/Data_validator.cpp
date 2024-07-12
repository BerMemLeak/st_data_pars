//
// Created by user on 05.07.2024.
//

#include "Data_validator.h"

validation_data::validation_data(universal_parser& first, universal_parser& second, std::string path, std::string outputFilename)
        : first(first), second(second), path(std::move(path)), outputFilename(std::move(outputFilename)) {
    compareFiles();
}

void validation_data::compareFiles() {
    std::ofstream outputFile(outputFilename);
    if (!outputFile.is_open()) {
        std::cerr << "Не получилось открыть файл: " << outputFilename << std::endl;
        return;
    }

    std::string goodValidation = "\n\nПравильные данные: \n"; // строка с правильными челиками
    std::string noPersInPriem = "\n\nВ файле приемки записей про таких людей нет:\n"; // нет микрочела
    std::string badValidation = "\n\nОшибка в заполненных данных:\n"; // ошибки в заполнении

    // сравниваю каждую строчку с каждой
    try {
        for (const auto& vec1 : first.get_data()) {
            bool contest_quid = false;
            bool cafedra_quid = false;
            bool found = false;
            for (const auto& vec2 : second.get_data()) {
                // проверка, есть ли человек такой
                if ((vec1.at("Фамилия") == vec2.at("Фамилия абитуриента")) &&
                    (vec1.at("Имя") == vec2.at("Имя абитуриента")) &&
                    (vec1.at("Отчество") == vec2.at("Отчество абитуриента")) &&
                    (vec1.at("ДатаРождения") == vec2.at("Дата рождения абитуриента"))) {
                    if (vec1.at("QUID_конкурса") == vec2.at("GUID конкурса")) { contest_quid = true; }
                    if (vec1.at("QUID_кафедры") == vec2.at("GUID кафедры")) { cafedra_quid = true; }
                    found = true;
                }
                if (found && cafedra_quid && contest_quid) {
                    // тут все хорошо, сделать запись и выйти во внешний цикл
                    goodValidation += "\n" + vec1.at("Фамилия") + " " + vec1.at("Имя") + " " + vec1.at("Отчество") + " - сходятся все данные";
                    break;
                }
            }
            if (!found) {
                // сделать запись, что микрочелика нету
                noPersInPriem += "\n" + vec1.at("Фамилия") + " " + vec1.at("Имя") + " " + vec1.at("Отчество");
            }
            if (found && !contest_quid && !cafedra_quid) {
                // неправильный quid конкурса и quid кафедры
                badValidation += "\n" + vec1.at("Фамилия") + " " + vec1.at("Имя") + " " + vec1.at("Отчество") + " - неправильный quid конкурса и quid кафедры";
            }
            if (found && contest_quid && !cafedra_quid) {
                // неправильный quid кафедры
                badValidation += "\n" + vec1.at("Фамилия") + " " + vec1.at("Имя") + " " + vec1.at("Отчество") + " - неправильный quid кафедры";
            }
            if (found && !contest_quid && cafedra_quid) {
                // неправильный quid конкурса
                badValidation += "\n" + vec1.at("Фамилия") + " " + vec1.at("Имя") + " " + vec1.at("Отчество") + " - неправильный quid конкурса";
            }
        }
        outputFile << noPersInPriem;
        outputFile << badValidation;
        outputFile << goodValidation;
        outputFile.close();
    } catch (const char* error_message) {
        std::cout << error_message << std::endl;
    }
}

