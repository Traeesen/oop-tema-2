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
void Doctor::doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments)
{
    for (int i = 0; i < departments.size(); i++)
    {
        if (departments[i].getName() == specialisation)
        {
            int patientsThisHour = patientsPerDay / 8;

            if (patientsThisHour < 1) patientsThisHour = 1;

            // nurse doubles efficiency
            if (departments[i].useAvailableNurse())
            {
                patientsThisHour *= 2;
            }
            else
            {
                patientsThisHour /= 2;
                if (patientsThisHour < 1) patientsThisHour = 1;
            }

            for (int j = 0; j < patientsThisHour && departments[i].getPatients().size() > 0; j++)
            {
                std::shared_ptr<Patient> patient = departments[i].getPatients()[0];

                departments[i].removeFirstPatient();

                if (patient->getProblems().size() > 0)
                {
                    std::cout << getName() << " Treated " << patient->getName() << " for " << patient->getProblems()[0] << "\n";
                    patient->removeFirstProblem();
                }

                // patient still needs treatment
                if (patient->getProblems().size() > 0)
                {
                    waitingInQueue.push_back(patient);
                }
            }

            break;
        }
    }
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
void Nurse::doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments)
{
    for (int i = 0; i < departments.size(); i++)
    {
        if (departments[i].getName() == role)
        {
            departments[i].addAvailableNurse();
            std::cout << getName()<< " is assisting department "<< role<< "\n";
            break;
        }
    }
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
void Admin::doWork(std::vector<std::shared_ptr<Patient>>& waitingInQueue, std::vector<Department>& departments)
{
    int patientsToRedirect = 1;

    for (int i = 0; i < patientsToRedirect && waitingInQueue.size() > 0; i++)
    {
        std::shared_ptr<Patient> patient = waitingInQueue[0];
        waitingInQueue.erase(waitingInQueue.begin());

        if (patient->getProblems().size() == 0)
            continue;

        std::string neededDepartment = patient->getProblems()[0];

        bool found = false;

        for (int j = 0; j < departments.size(); j++)
        {
            if (departments[j].getName() == neededDepartment)
            {
                departments[j].addPatient(patient);
                found = true;

                std::cout << getName()<< " redirected "<< patient->getName()<< " to "<< neededDepartment<< "\n";

                break;
            }
        }

        if (!found)
        {
            std::cout << getName()<< " could not redirect "<< patient->getName()<< " because department "<< neededDepartment<< " does not exist. Patient cannot be treated.\n";
        }
    }
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