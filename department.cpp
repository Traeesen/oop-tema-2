#include <vector>
#include "staff.h"
#include "department.h"
#include <iostream>


//monte de getteurs et setteurs
int Department::getEmployeeCount() const { return assignedStaff.size(); }
const std::vector<Staff*>& Department::getStaff() const { return assignedStaff; }
void Department::setName(const std::string newName)
{
    name = newName;
}
const std::string& Department::getName() const
{
    return name;
}

//constructori
Department::Department(const std::string& name)
{
    setName(name);
}

Department::Department(const Department& other)
{
    setName(other.getName());

    assignedStaff = other.getStaff();
}

//dstructor
Department::~Department()
{
}

//adaugam un angajat in departament
void Department::addEmployee(Staff& e)
{

    assignedStaff.push_back(&e);
}

Department& Department::operator=(const Department& other)
{
    if (this == &other) return *this;

    setName(other.getName());

    assignedStaff = other.getStaff();

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Department& d)
{
    os << d.getName();
    os << "---EMPLOYEES:\n";
    for (int i = 0; i < d.getEmployeeCount(); i++) os << "    |" << *(d.getStaff()[i]) << "\n";
    return os;
}