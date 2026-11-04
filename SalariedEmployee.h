#ifndef SALARIEDEMPLOYEE_H
#define SALARIEDEMPLOYEE_H

#include "Employee.h"
#include <stdexcept>

class SalariedEmployee : public Employee {
protected:
    double baseSalary;
    int experienceYears;

public:
    SalariedEmployee(int id, const std::string& name,
                     double baseSalary, int experienceYears);

    SalariedEmployee(const SalariedEmployee& other);

    SalariedEmployee& operator=(const SalariedEmployee& other);

    ~SalariedEmployee() override = default;

    double getBaseSalary() const;
    int getExperienceYears() const;

    virtual double experienceBonus() const;
};

#endif