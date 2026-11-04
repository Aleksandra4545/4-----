#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include <iosfwd>

class Employee {
protected:
    int id;
    std::string name;

    static int employeeCount;
    static std::vector<Employee*> registry;

    void copyBaseFrom(const Employee& other);

public:
    Employee(int id, const std::string& name);
    Employee(const Employee& other);
    Employee& operator=(const Employee& other);
    virtual ~Employee();

    int getId() const;
    const std::string& getName() const;

    virtual double calculateSalary() const = 0;
    virtual std::string getInfo() const = 0;

    virtual std::string getRole() const;

    static int getEmployeeCount();
    static double getAverageSalary();

    friend std::ostream& operator<<(std::ostream& out,
                                    const Employee& employee);
};

#endif