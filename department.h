#pragma once
#include <vector>
#include "staff.h"
#include <iostream>

class Department
{
    std::vector<int> blah;
    std::vector<Staff*> assignedStaff;
    std::string name="";

    public:
        //monte de getteurs et setteurs
        int getEmployeeCount() const;
        const std::vector<Staff*>& getStaff() const;
        void setName(const std::string newName);
        const std::string& getName() const;

        //constructori
        Department(const std::string& name);
        

        Department(const Department& other);

        //dstructor
        ~Department();

        //adaugam un angajat in departament
        void addEmployee(Staff& e);

        friend std::ostream& operator<<(std::ostream& os, const Department& d);
        Department& operator=(const Department& other);
};