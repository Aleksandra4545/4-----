#ifndef MANAGER_H
#define MANAGER_H

#include "SalariedEmployee.h"
#include <vector>

class Manager : virtual public SalariedEmployee {
protected:
    std::vector<std::string> subordinates;

    double managerBonus() const;

public:
    Manager(int id, const std::string& name,
            double baseSalary, int years,
            const std::vector<std::string>& subordinates);

    Manager(const Manager& other);

    Manager& operator=(const Manager& other);

    ~Manager() override = default;

    double calculateSalary() const override;
    std::string getInfo() const override;
    std::string getRole() const override;

    void addSubordinate(const std::string& subordinate);

    std::size_t getSubordinateCount() const;
};

#endif