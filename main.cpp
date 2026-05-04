/*
Numele temei pt review: Pariuri sportive
Nume coleg review: Bugeac Alexandru
*/
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include "staff.h"
#include "department.h"
#include "patient.h"

int main()
{
    std::vector<Department> departments;
    std::vector<Staff> staff;
    {
        std::ifstream fin("doctors.txt");
        while(fin)
        {
            std::string name, role;
            int patientsPerDay, salary;
            fin >> name >> salary >> role >> patientsPerDay;
            Doctor d(name, salary, role, patientsPerDay);

            int count = departments.size();
            bool found=false;
            for(int i=0; i<count; i++)
            {
                if(departments[i].getName() == role)
                {
                    found=true;
                    departments[i].addEmployee(d);
                    break;
                }
            }
            if(found==false)
            {
                Department dep(role);
                dep.addEmployee(d);
                departments.push_back(dep);
            }
            staff.push_back(d);
        }
    }
    {
        std::ifstream fin("nurses.txt");
        while(fin)
        {
            std::string name, role;
            int salary;
            fin >> name >> salary >> role;
            Nurse d(name, salary, role);

            int count = departments.size();
            bool found=false;
            for(int i=0; i<count; i++)
            {
                if(departments[i].getName() == role)
                {
                    found=true;
                    departments[i].addEmployee(d);
                    break;
                }
            }
            if(found==false)
            {
                // TODO THROW ERROR
            }
            staff.push_back(d);
        }
    }

    {
        std::ifstream fin("admins.txt");
        while(fin)
        {
            std::string name;
            int salary;
            fin >> name >> salary;
            Admin d(name, salary);
            staff.push_back(d);
        }
    }

    std::vector<Patient> patients;
    {
        std::ifstream fin("patients.txt");
        while(fin)
        {
            std::string name;
            int age;
            fin >> name >> age;
            Patient p(name, age);
            patients.push_back(p);

            std::string problems;
            std::getline(fin, problems); //luam restul liniei si o punem intr-un singur stringg
            
            std::string word;

            for (size_t i = 0; i < problems.size(); i++) //impartim linia in cuvinte
            {
                if (problems[i] == ' ')
                {
                    if (!word.empty())
                    {
                        p.addProblem(word);
                        word.clear();
                    }
                }
                else
                {
                    word += problems[i];
                }
            }

            // last word
            if (!word.empty())
            {
                p.addProblem(word);
            }
        }
    }

        for(int hour=1; hour<=8; hour++) // 8 ore de munca
        {
            int size = staff.size();
            for(int i=size-1; i>=0; i++)
            {
                staff[i].doWork(patients, departments);
            }
        }
    
}