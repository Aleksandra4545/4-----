#include "Employee.h"
#include <ostream>

int Employee::employeeCount = 0;
std::vector<Employee*> Employee::registry;

Employee::Employee(int employeeId, const std::string& employeeName)
    : id(employeeId), name(employeeName) {
    ++employeeCount;
    registry.push_back(this);
}

Employee::Employee(const Employee& other)
    : id(other.id), name(other.name) {
    ++employeeCount;
    registry.push_back(this);
}

Employee& Employee::operator=(const Employee& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
    }
    return *this;
}

Employee::~Employee() {
    for (auto it = registry.begin(); it != registry.end(); ++it) {
        if (*it == this) {
            registry.erase(it);
            break;
        }
    }
    --employeeCount;
}

void Employee::copyBaseFrom(const Employee& other) {
    id = other.id;
    name = other.name;
}

int Employee::getId() const {
    return id;
}

const std::string& Employee::getName() const {
    return name;
}

std::string Employee::getRole() const {
    return "Сотрудник";
}

int Employee::getEmployeeCount() {
    return employeeCount;
}

double Employee::getAverageSalary() {
    if (registry.empty()) return 0.0;

    double total = 0.0;

    for (const Employee* employee : registry) {
        total += employee->calculateSalary();
    }

    return total / static_cast<double>(registry.size());
}

std::ostream& operator<<(std::ostream& out,
                         const Employee& employee) {
    return out << employee.getInfo();
}