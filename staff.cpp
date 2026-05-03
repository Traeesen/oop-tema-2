#include <iostream>
#include <vector>
#include "staff.h"

// -- STAFF --

//getter-e/setter-e
void Staff::setSalary(const int newSalary)
{
    salary=newSalary;
}
int Staff::getSalary() const
{
    return salary;
}
void Staff::setName(const std::string& newName)
{
    name = newName;
}
const std::string& Staff::getName() const
{
    return name;
}
int Staff::getId() const {return id;}

//constructori
Staff::Staff() : id(nextId++)
{
    setSalary(0);
    setName("");
}
Staff::Staff(const std::string& name, const int salary) : id(nextId++)
{
    setSalary(salary);
    setName(name);
}
Staff::Staff(const Staff& other) : id(nextId++)
{
    setSalary(other.salary);
    setName(other.name);
}

int Staff::nextId=1;

//operatori
Staff& Staff::operator=(const Staff& other)
{
    if (this == &other) return *this;
    setSalary(other.getSalary());
    setName(other.getName());
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Staff& e)
{
    os << (e.getName() != "" ? e.getName() : "none");
    os << ", Salary: " << e.getSalary();
    return os;
}

// -- DOCTOR --

//getter-e/setter-e
void Doctor::setSpecialization(const std::string& spec)
{
    specialisation = spec;
}

const std::string& Doctor::getSpecialisation() const
{
    return specialisation;
}

void Doctor::setPatientsPerDay(int nr)
{
    patientsPerDay = nr;
}

int Doctor::getPatientsPerDay() const
{
    return patientsPerDay;
}

//constructori
Doctor::Doctor() : Staff(), specialisation(""), patientsPerDay(0)
{
}

Doctor::Doctor(const std::string& name, int salary, const std::string& specialisation, int patientsPerDay) : Staff(name, salary)
{
    setSpecialization(specialisation);
    setPatientsPerDay(patientsPerDay);
}

Doctor::Doctor(const Doctor& other) : Staff(other)
{
    setSpecialization(other.specialisation);
    setPatientsPerDay(other.patientsPerDay);
}

//metoda virtuala
void Doctor::doWork()
{
    std::cout << "Doctor treating patients in " << specialisation << "\n";
}

//operatori
Doctor& Doctor::operator=(const Doctor& other)
{
    if (this == &other) return *this;
    Staff::operator=(other);
    setSpecialization(other.getSpecialisation());
    setPatientsPerDay(other.getPatientsPerDay());
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Doctor& d)
{
    os << (d.getName() != "" ? d.getName() : "none");
    os << ", Salary: " << d.getSalary();
    os << ", Specialization: " << d.getSpecialisation();
    os << ", Patients/Day: " << d.getPatientsPerDay();
    return os;
}


// -- ASISTENT --

//constructori
Nurse::Nurse() : Staff(), department(""), shiftsPerWeek(0)
{
}

Nurse::Nurse(const std::string& name, int salary, const std::string& department, int shiftsPerWeek) : Staff(name, salary)
{

}

Nurse::Nurse(const Nurse& other) : Staff(other)
{
    setDepartment(other.department);
    setShiftsPerWeek(other.shiftsPerWeek);
}

//metoda virtuala
void Nurse::doWork()
{
    std::cout << "Nurse working in " << department << "\n";
}

//operatori
Nurse& Nurse::operator=(const Nurse& other)
{
    if (this == &other) return *this;
    Staff::operator=(other);
    setDepartment(other.getDepartment());
    setShiftsPerWeek(other.getShiftsPerWeek());
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Nurse& n)
{
    os << (n.getName() != "" ? n.getName() : "none");
    os << ", Salary: " << n.getSalary();
    os << ", Department: " << n.getDepartment();
    os << ", Shifts/Week: " << n.getShiftsPerWeek();
    return os;
}


// -- ADMIN --

//getter-e/setter-e
void Admin::setRole(const std::string& r)
{
    role = r;
}

const std::string& Admin::getRole() const
{
    return role;
}

void Admin::setHoursPerWeek(int hours)
{
    hoursPerWeek = hours;
}

int Admin::getHoursPerWeek() const
{
    return hoursPerWeek;
}

//constructori
Admin::Admin() : Staff(), role(""), hoursPerWeek(0)
{
}

Admin::Admin(const std::string& name, int salary, const std::string& role, int hoursPerWeek) : Staff(name, salary)
{
    setRole(role);
    setHoursPerWeek(hoursPerWeek);
}

Admin::Admin(const Admin& other) : Staff(other)
{
    setRole(other.role);
    setHoursPerWeek(other.hoursPerWeek);
}

//metoda virtuala
void Admin::doWork()
{
    std::cout << "Admin handling " << role << " tasks\n";
}

//operatori
Admin& Admin::operator=(const Admin& other)
{
    if (this == &other) return *this;
    Staff::operator=(other);
    setRole(other.getRole());
    setHoursPerWeek(other.getHoursPerWeek());
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Admin& a)
{
    os << (a.getName() != "" ? a.getName() : "none");
    os << ", Salary: " << a.getSalary();
    os << ", Role: " << a.getRole();
    os << ", Hours/Week: " << a.getHoursPerWeek();
    return os;
}