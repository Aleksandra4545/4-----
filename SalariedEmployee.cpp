#include "SalariedEmployee.h"

SalariedEmployee::SalariedEmployee(
    int id, const std::string& name,
    double salary, int years)
    : Employee(id, name),
      baseSalary(salary),
      experienceYears(years) {

    if (salary < 0 || years < 0) {
        throw std::invalid_argument(
            "Ставка и стаж не могут быть отрицательными"
        );
    }
}

SalariedEmployee::SalariedEmployee(
    const SalariedEmployee& other)
    : Employee(other),
      baseSalary(other.baseSalary),
      experienceYears(other.experienceYears) {}

SalariedEmployee& SalariedEmployee::operator=(
    const SalariedEmployee& other) {

    if (this != &other) {
        Employee::operator=(other);
        baseSalary = other.baseSalary;
        experienceYears = other.experienceYears;
    }

    return *this;
}

double SalariedEmployee::getBaseSalary() const {
    return baseSalary;
}

int SalariedEmployee::getExperienceYears() const {
    return experienceYears;
}

double SalariedEmployee::experienceBonus() const {
    return baseSalary * 0.02 * experienceYears;
}