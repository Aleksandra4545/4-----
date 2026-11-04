#ifndef TEAMLEAD_H
#define TEAMLEAD_H

#include "Manager.h"
#include "Developer.h"

class TeamLead : public Manager, public Developer {
public:
    TeamLead(int id, const std::string& name,
             double baseSalary, int years,
             const std::vector<std::string>& subordinates,
             const std::vector<std::string>& projects);

    TeamLead(const TeamLead& other);

    TeamLead& operator=(const TeamLead& other);

    ~TeamLead() override = default;

    double calculateSalary() const override;
    std::string getInfo() const override;
    std::string getRole() const override;
};

#endif