#include "Developer.h"
#include <sstream>

Developer::Developer(
    int id, const std::string& name,
    double salary, int years,
    const std::vector<std::string>& projectList)
    : SalariedEmployee(id, name, salary, years),
      projects(projectList) {}

Developer::Developer(const Developer& other)
    : SalariedEmployee(other),
      projects(other.projects) {}

Developer& Developer::operator=(const Developer& other) {
    if (this != &other) {
        SalariedEmployee::operator=(other);
        projects = other.projects;
    }

    return *this;
}

double Developer::projectBonus() const {
    return 3000.0 * projects.size();
}

double Developer::calculateSalary() const {
    return baseSalary + experienceBonus() + projectBonus();
}

std::string Developer::getInfo() const {
    std::ostringstream out;

    out << "Developer | ID: " << id
        << " | Имя: " << name
        << " | Стаж: " << experienceYears
        << " | Проектов: " << projects.size()
        << " | Зарплата: " << calculateSalary();

    return out.str();
}

std::string Developer::getRole() const {
    return "Разработчик";
}

void Developer::addProject(const std::string& project) {
    projects.push_back(project);
}

std::size_t Developer::getProjectCount() const {
    return projects.size();
}