#include "Manager.h"
#include <sstream>

Manager::Manager(
    int id, const std::string& name,
    double salary, int years,
    const std::vector<std::string>& people)
    : SalariedEmployee(id, name, salary, years),
      subordinates(people) {}

Manager::Manager(const Manager& other)
    : SalariedEmployee(other),
      subordinates(other.subordinates) {}

Manager& Manager::operator=(const Manager& other) {
    if (this != &other) {
        SalariedEmployee::operator=(other);
        subordinates = other.subordinates;
    }

    return *this;
}

double Manager::managerBonus() const {
    return 1500.0 * subordinates.size();
}

double Manager::calculateSalary() const {
    return baseSalary + experienceBonus() + managerBonus();
}

std::string Manager::getInfo() const {
    std::ostringstream out;

    out << "Manager | ID: " << id
        << " | Имя: " << name
        << " | Стаж: " << experienceYears
        << " | Подчинённых: " << subordinates.size()
        << " | Зарплата: " << calculateSalary();

    return out.str();
}

std::string Manager::getRole() const {
    return "Менеджер";
}

void Manager::addSubordinate(const std::string& subordinate) {
    subordinates.push_back(subordinate);
}

std::size_t Manager::getSubordinateCount() const {
    return subordinates.size();
}