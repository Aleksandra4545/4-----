#include "TeamLead.h"
#include <sstream>

TeamLead::TeamLead(
    int id, const std::string& name,
    double salary, int years,
    const std::vector<std::string>& people,
    const std::vector<std::string>& projectList)

    : SalariedEmployee(id, name, salary, years),
      Manager(id, name, salary, years, people),
      Developer(id, name, salary, years, projectList) {}

TeamLead::TeamLead(const TeamLead& other)
    : SalariedEmployee(other),
      Manager(other),
      Developer(other) {}

TeamLead& TeamLead::operator=(const TeamLead& other) {
    if (this != &other) {
        SalariedEmployee::operator=(other);
        Manager::operator=(other);
        Developer::operator=(other);
    }

    return *this;
}

double TeamLead::calculateSalary() const {
    return baseSalary
        + experienceBonus()
        + managerBonus()
        + projectBonus();
}

std::string TeamLead::getInfo() const {
    std::ostringstream out;

    out << "TeamLead | ID: " << id
        << " | Имя: " << name
        << " | Стаж: " << experienceYears
        << " | Подчинённых: " << subordinates.size()
        << " | Проектов: " << projects.size()
        << " | Зарплата: " << calculateSalary();

    return out.str();
}

std::string TeamLead::getRole() const {
    return "Тимлид";
}