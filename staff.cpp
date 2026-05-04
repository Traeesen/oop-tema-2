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

Staff::~Staff()
{
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
void Doctor::doWork(std::vector<Patient>& waitingInQueue, std::vector<Department>& departments)
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
Nurse::Nurse() : Staff(), role("")
{
}

Nurse::Nurse(const std::string& name, int salary, const std::string& role) : Staff(name, salary), role(role)
{
}
Nurse::Nurse(const Nurse& other) : Staff(other), role(other.role)
{
}

//metoda virtuala
void Nurse::doWork(std::vector<Patient>& waitingInQueue, std::vector<Department>& departments)
{
    std::cout << "Nurse working in " << role << "\n";
}

//operatori
Nurse& Nurse::operator=(const Nurse& other)
{
    if (this == &other) return *this;
    Staff::operator=(other);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Nurse& n)
{
    os << (n.getName() != "" ? n.getName() : "none");
    os << ", Salary: " << n.getSalary();
    return os;
}


// -- ADMIN --

//getter-e/setter-e

//constructori
Admin::Admin() : Staff()
{
}

Admin::Admin(const std::string& name, int salary) : Staff(name, salary)
{
}

Admin::Admin(const Admin& other) : Staff(other)
{
}

//metoda virtuala
void Admin::doWork(std::vector<Patient>& waitingInQueue, std::vector<Department>& departments)
{
}

//operatori
Admin& Admin::operator=(const Admin& other)
{
    if (this == &other) return *this;
    Staff::operator=(other);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Admin& a)
{
    os << (a.getName() != "" ? a.getName() : "none");
    os << ", Salary: " << a.getSalary();
    return os;
}