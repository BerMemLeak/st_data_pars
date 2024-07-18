//
// Created by user on 05.07.2024.
//

#include "Data_validator.h"

validation_data::validation_data(universal_parser& first, universal_parser& second, std::string outputFilename)
        : first(first), second(second),  outputFilename(std::move(outputFilename)) {
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
        for (const auto& vec1 : second.get_data()) {
            bool contest_quid = false;
            bool cafedra_quid = false;
            bool found = false;
            for (const auto& vec2 : first.get_data()) {
                // проверка, есть ли человек такой
                if ((vec1.at("Фамилия абитуриента") == vec2.at("Фамилия")) &&
                    (vec1.at("Имя абитуриента") == vec2.at("Имя")) &&
                    (vec1.at("Отчество абитуриента") == vec2.at("Отчество")) &&
                    (vec1.at("Дата рождения абитуриента") == vec2.at("ДатаРождения"))) {
                    if (vec1.at("GUID конкурса") == vec2.at("QUID_конкурса")) { contest_quid = true; }
                    if (vec1.at("GUID кафедры") == vec2.at("QUID_кафедры")) { cafedra_quid = true; }
                    found = true;
                }
                if (found && cafedra_quid && contest_quid) {
                    // тут все хорошо, сделать запись и выйти во внешний цикл
                    goodValidation += "\n" + vec1.at("Фамилия абитуриента") + " " + vec1.at("Имя абитуриента") + " " + vec1.at("Отчество абитуриента") + " - сходятся все данные";
                    break;
                }
            }
            if (!found) {
                // сделать запись, что микрочелика нету
                noPersInPriem += "\n" + vec1.at("Фамилия абитуриента") + " " + vec1.at("Имя абитуриента") + " " + vec1.at("Отчество абитуриента");
            }
            if (found && !contest_quid && !cafedra_quid) {
                // неправильный quid конкурса и quid кафедры
                badValidation += "\n" + vec1.at("Фамилия абитуриента") + " " + vec1.at("Имя абитуриента") + " " + vec1.at("Отчество абитуриента") + " - неправильный quid конкурса и quid кафедры";
            }
            if (found && contest_quid && !cafedra_quid) {
                // неправильный quid кафедры
                badValidation += "\n" + vec1.at("Фамилия абитуриента") + " " + vec1.at("Имя абитуриента") + " " + vec1.at("Отчество абитуриента") + " - неправильный quid кафедры";
            }
            if (found && !contest_quid && cafedra_quid) {
                // неправильный quid конкурса
                badValidation += "\n" + vec1.at("Фамилия абитуриента") + " " + vec1.at("Имя абитуриента") + " " + vec1.at("Отчество абитуриента") + " - неправильный quid конкурса";
            }
        }
        outputFile << noPersInPriem;
        outputFile << badValidation;
        outputFile << goodValidation;
        outputFile.close();
        std::cout <<"Все успешно!";
    } catch (const char* error_message) {
        std::cout<<"ошибка в валидации" << error_message << std::endl;
    }
}

