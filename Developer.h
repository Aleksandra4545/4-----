#ifndef DEVELOPER_H
#define DEVELOPER_H

#include "SalariedEmployee.h"
#include <vector>

class Developer : virtual public SalariedEmployee {
protected:
    std::vector<std::string> projects;

    double projectBonus() const;

public:
    Developer(int id, const std::string& name,
              double baseSalary, int years,
              const std::vector<std::string>& projects);

    Developer(const Developer& other);

    Developer& operator=(const Developer& other);

    ~Developer() override = default;

    double calculateSalary() const override;
    std::string getInfo() const override;
    std::string getRole() const override;

    void addProject(const std::string& project);

    std::size_t getProjectCount() const;
};

#endif