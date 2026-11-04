#!/bin/bash
set -e

CXX=g++
FLAGS="-std=c++17 -Wall -Wextra -pedantic"

# Исходные файлы библиотеки
SOURCES="Employee.cpp SalariedEmployee.cpp Manager.cpp Developer.cpp TeamLead.cpp"

# 1. Статическая библиотека
$CXX $FLAGS -c Employee.cpp SalariedEmployee.cpp Manager.cpp Developer.cpp TeamLead.cpp

ar rcs liblab3.a Employee.o SalariedEmployee.o Manager.o Developer.o TeamLead.o

# 2. Динамическая библиотека
$CXX $FLAGS -fPIC -c Employee.cpp SalariedEmployee.cpp Manager.cpp Developer.cpp TeamLead.cpp

$CXX -shared -o liblab3.so Employee.o SalariedEmployee.o Manager.o Developer.o TeamLead.o

# 3. Тест со статической библиотекой
$CXX $FLAGS test_client.cpp ./liblab3.a -o test_static

# 4. Тест с динамической библиотекой
$CXX $FLAGS test_client.cpp -L. -llab3 -Wl,-rpath,'$ORIGIN' -o test_dynamic

echo "Сборка завершена!"