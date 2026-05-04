#pragma once
#include <iostream>
#include <vector>
#include "patient.h"

class Department;

class Staff
{
    std::string name="";
    int salary;
    static int nextId;
    const int id;

    public:
        //getter-e/setter-e
        void setSalary(const int newSalary);
        int getSalary() const;
        void setName(const std::string& newName);
        const std::string& getName() const;
        int getId() const;

        //constructori
        Staff();

        Staff(const std::string& name, const int salary);

        Staff(const Staff& other);
        //destructor
        ~Staff();

        friend void Swap(Staff& a, Staff& b);

        //operatori
        friend std::ostream& operator<<(std::ostream& os, const Staff& e);
        Staff& operator=(const Staff& other);

        //metoda virtuala
        virtual void doWork(std::vector<Patient> waitingInQueue, std::vector<Department> departments) = 0;
};

class Doctor : public Staff 
{
    int patientsPerDay;
    std::string specialisation;

    public: 
        // gettere/settere
        void setSpecialization(const std::string& spec);
        const std::string& getSpecialisation() const;

        void setPatientsPerDay(int nr);
        int getPatientsPerDay() const;


        //constuctori
        Doctor();
        Doctor(const std::string& name, int salay, const std::string& specialisation, int patientsPerDay);
        Doctor(const Doctor& other);

        //override
        void doWork(std::vector<Patient> waitingInQueue, std::vector<Department> departments) override;

        //operatori
        Doctor& operator=(const Doctor& other);
        friend std::ostream& operator<<(std::ostream& os, const Doctor& d);
};

class Nurse : public Staff
{
    const std::string role;

    public:
        // constructori
        Nurse();
        Nurse(const std::string& name, int salary, const std::string& role);
        Nurse(const Nurse& other);

        // override
        void doWork(std::vector<Patient> waitingInQueue, std::vector<Department> departments) override;

        //operatori
        Nurse& operator=(const Nurse& other);
        friend std::ostream& operator<<(std::ostream& os, const Nurse& n);
};

class Admin : public Staff
{

    public:
        // constructori
        Admin();
        Admin(const std::string& name, int salary);
        Admin(const Admin& other);

        // override
        void doWork(std::vector<Patient> waitingInQueue, std::vector<Department> departments) override;

        // operatori
        Admin& operator=(const Admin& other);
        friend std::ostream& operator<<(std::ostream& os, const Admin& a);
};