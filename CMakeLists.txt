cmake_minimum_required(VERSION 3.0)
project(reconciliation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(Qt5_DIR "/Users/ilya/Qt/5.15.2/clang_64/lib/cmake/Qt5")

set(UCHARDET_ROOT "/usr/local/Cellar/uchardet/0.0.8")
set(BOOST_ROOT "/usr/local/Cellar/boost/1.85.0")

# Find Boost.Locale
find_package(Boost 1.70 REQUIRED COMPONENTS locale)

find_library(UCHARDET_LIBRARY NAMES uchardet PATHS ${UCHARDET_ROOT}/lib)
find_path(UCHARDET_INCLUDE_DIR uchardet/uchardet.h PATHS ${UCHARDET_ROOT}/include)



## Получите пути для включения и линковки Python из python3-config
#execute_process(COMMAND python3-config --includes OUTPUT_VARIABLE PYTHON_INCLUDES OUTPUT_STRIP_TRAILING_WHITESPACE)
#execute_process(COMMAND python3-config --ldflags OUTPUT_VARIABLE PYTHON_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
#execute_process(COMMAND python3-config --libs OUTPUT_VARIABLE PYTHON_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)
#
## Установите пути для включения и линковки Python
#include_directories(${PYTHON_INCLUDES})
#link_directories(${PYTHON_LDFLAGS})

# Найдите Python
#find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

if(NOT UCHARDET_INCLUDE_DIR)
    message(FATAL_ERROR "Не удалось найти заголовочный файл uchardet.h")
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(reconciliation main.cpp
        parser/Universal_parser.h
        ui/mainwindow.h
        parser/Universal_parser.cpp
        validation/Data_validator.cpp
        encoding/encoding_converter.h
        encoding/encoding_converter.cpp
)

target_include_directories(reconciliation PRIVATE ${UCHARDET_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})
target_link_libraries(reconciliation ${UCHARDET_LIBRARY} Qt5::Widgets ${Boost_LIBRARIES})
target_include_directories(reconciliation PRIVATE ${Python3_INCLUDE_DIRS})
#target_link_libraries(reconciliation PRIVATE ${Python3_LIBRARIES})

