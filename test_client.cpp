#include "Manager.h"
#include "Developer.h"
#include "TeamLead.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <stdexcept>

using namespace std;

// Разделение списка подчинённых и проектов.
vector<string> splitList(const string& value) {
    vector<string> result;

    if (value == "-" || value.empty())
        return result;

    string item;
    stringstream stream(value);

    while (getline(stream, item, ',')) {
        if (!item.empty())
            result.push_back(item);
    }

    return result;
}

// Загрузка сотрудников из файла.
vector<unique_ptr<Employee>> loadEmployees(
    const string& filename) {

    ifstream file(filename);

    if (!file)
        throw runtime_error(
            "Не удалось открыть файл " + filename
        );

    vector<unique_ptr<Employee>> employees;
    string line;

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#')
            continue;

        stringstream ss(line);

        string type, idText, name;
        string salaryText, yearsText;
        string peopleText, projectsText;

        if (!getline(ss, type, '|') ||
            !getline(ss, idText, '|') ||
            !getline(ss, name, '|') ||
            !getline(ss, salaryText, '|') ||
            !getline(ss, yearsText, '|') ||
            !getline(ss, peopleText, '|') ||
            !getline(ss, projectsText, '|')) {

            throw runtime_error(
                "Некорректная строка: " + line
            );
        }

        int id = stoi(idText);
        double salary = stod(salaryText);
        int years = stoi(yearsText);

        vector<string> people = splitList(peopleText);
        vector<string> projects = splitList(projectsText);

        if (type == "Manager") {
            employees.push_back(
                make_unique<Manager>(
                    id, name, salary, years, people
                )
            );
        }
        else if (type == "Developer") {
            employees.push_back(
                make_unique<Developer>(
                    id, name, salary, years, projects
                )
            );
        }
        else if (type == "TeamLead") {
            employees.push_back(
                make_unique<TeamLead>(
                    id, name, salary, years,
                    people, projects
                )
            );
        }
        else {
            throw runtime_error(
                "Неизвестный тип: " + type
            );
        }
    }

    if (employees.size() != 10)
        throw runtime_error(
            "В файле должно быть 10 сотрудников"
        );

    return employees;
}

// Демонстрация полиморфизма.
void printEmployees(
    const vector<unique_ptr<Employee>>& employees) {

    cout << "\n=== Сотрудники компании ===\n";

    for (const auto& employee : employees) {
        cout << *employee << "\n";

        cout << "Роль: "
             << employee->getRole() << "\n";

        cout << "Зарплата через Employee*: "
             << employee->calculateSalary() << "\n\n";
    }
}

// Проверка копирования и присваивания.
void testCopyAndAssignment() {

    cout << "\n=== Копирование и присваивание ===\n";

    Manager original(
        100, "Исходный менеджер",
        70000, 4, {"Алексей"}
    );

    Manager copied(original);

    copied.addSubordinate("Марина");

    cout << "Оригинал: "
         << original.getSubordinateCount() << "\n";

    cout << "Копия: "
         << copied.getSubordinateCount() << "\n";

    Manager assigned(
        101, "Временный",
        50000, 1, {}
    );

    assigned = original;

    assigned.addSubordinate("Новый сотрудник");

    cout << "Оригинал после присваивания: "
         << original.getSubordinateCount() << "\n";

    cout << "Присвоенный объект: "
         << assigned.getSubordinateCount() << "\n";

    // Проверка Developer.
    Developer dev(
        102, "Разработчик",
        80000, 3, {"Сайт"}
    );

    Developer devCopy(dev);
    devCopy.addProject("Приложение");

    cout << "Проектов у оригинала: "
         << dev


getProjectCount() << "\n";

    cout << "Проектов у копии: "
         << devCopy.getProjectCount() << "\n";

    // Проверка TeamLead.
    TeamLead lead(
        103, "Тимлид",
        100000, 5,
        {"Аня"}, {"Сервис"}
    );

    TeamLead leadCopy(lead);

    leadCopy.addSubordinate("Борис");
    leadCopy.addProject("Платформа");

    cout << "У оригинального тимлида: "
         << lead.getSubordinateCount()
         << " подчинённый, "
         << lead.getProjectCount()
         << " проект\n";

    cout << "У копии тимлида: "
         << leadCopy.getSubordinateCount()
         << " подчинённых, "
         << leadCopy.getProjectCount()
         << " проекта\n";

    // Проверка самоприсваивания.
    assigned = assigned;

    cout << "Самоприсваивание проверено.\n";
}

// Проверка исключений.
void testExceptions() {

    cout << "\n=== Проверка исключений ===\n";

    try {
        Manager invalid(
            200, "Ошибка",
            -1000, 2, {}
        );
    }
    catch (const invalid_argument& e) {
        cout << "Исключение обработано: "
             << e.what() << "\n";
    }
}

int main() {

    try {
        // Загружаем 10 сотрудников.
        vector<unique_ptr<Employee>> employees =
            loadEmployees("employees.txt");

        printEmployees(employees);

        // Статические члены.
        cout << "\n=== Статические члены ===\n";

        cout << "Количество сотрудников: "
             << Employee::getEmployeeCount()
             << "\n";

        cout << "Средняя зарплата: "
             << Employee::getAverageSalary()
             << "\n";

        testCopyAndAssignment();

        testExceptions();

        cout << "\nКоличество сотрудников после тестов: "
             << Employee::getEmployeeCount()
             << "\n";
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}.