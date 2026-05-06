/*
Numele temei pt review: Pariuri sportive
Nume coleg review: Bugeac Alexandru
*/
#include <fstream>
#include <cstring>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "staff.h"
#include "department.h"
#include "patient.h"
#include "staff.cpp"
#include "patient.cpp"
#include "department.cpp"
#include "exceptions.h"
#include "exceptions.cpp"

int main()
{
    try
    {
        std::vector<Department> departments;
        std::vector<std::shared_ptr<Staff>> staff;
        {

            std::ifstream fin("doctors.txt");
            if(!fin.is_open()) throw FileOpenException("doctors.txt");

            std::string name, role;
            int patientsPerDay, salary;
            while (fin >> name >> role >> patientsPerDay >> salary)
            {
                std::shared_ptr<Doctor> d = std::make_shared<Doctor>(name, salary, role, patientsPerDay);

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
            if(!fin.is_open()) throw FileOpenException("nurses.txt");
            std::string name, role;
            int salary;
            while(fin >> name >> role >> salary)
            {
                std::shared_ptr<Nurse> d = std::make_shared<Nurse>(name, salary, role);

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
            if(!fin.is_open()) throw FileOpenException("admins.txt");
            std::string name;
            int salary;
            while(fin >> name >> salary)
            {
                std::shared_ptr<Admin> d = std::make_shared<Admin>(name, salary);
                staff.push_back(d);
            }
        }

        std::vector<std::shared_ptr<Patient>> patients;
        {
            std::ifstream fin("patients.txt");
            if(!fin.is_open()) throw FileOpenException("patients.txt");
            std::string name;
            int age;
            while(fin >> name >> age)
            {
                std::shared_ptr<Patient> p = std::make_shared<Patient>(name, age);

                std::string problems;
                std::getline(fin, problems); //luam restul liniei si o punem intr-un singur stringg
                
                std::string word;

                for (size_t i = 0; i < problems.size(); i++) //impartim linia in cuvinte
                {
                    if (problems[i] == ' ')
                    {
                        if (!word.empty())
                        {
                            p->addProblem(word);
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
                    p->addProblem(word);
                }

                patients.push_back(p);
            }
        }

        for(int hour=1; hour<=8; hour++) // 8 ore de munca
        {
            std::cout<<'\n'<<"----------- HOUR " << hour << " -----------\n";
            int size = staff.size();
            for(int i=size-1; i>=0; i--)
            {
                staff[i]->doWork(patients, departments);
            }
            if(patients.size() == 0)
            {
                std::cout << "\nALL PATIENTS HAVE BEEN TREATED\n";

                int unusedHours = 8 - hour;

                if(unusedHours > 0)
                {
                    int totalSalary = 0;

                    for(int i = 0; i < staff.size(); i++)
                        totalSalary += staff[i]->getSalary();

                    int wastedMoney = (totalSalary * unusedHours) / 20;

                    std::cout << "Recommendation: The hospital finished " << unusedHours << " hour(s) early and wasted approximately " << wastedMoney << " ron in salaries. Consider reducing staff or accepting more patients.\n";
                }

                break;
            }
        }
        if(patients.size() > 0)
        {
            int untreatedPatients = patients.size();

            int estimatedLoss = untreatedPatients * 1000;

            std::cout << "\nRecommendation: " << untreatedPatients << " patient(s) were not treated before the hospital closed. The hospital likely needs more doctors, nurses, or administrators in overloaded departments. Alternatively, there may be departments that don't exist.";
        }

        std::cout << "\n\nFINAL STAFF RESULTS:";
        std::cout << "\nADMINS:\n";
        for(int i = 0; i < staff.size(); i++)
            if(std::dynamic_pointer_cast<Admin>(staff[i]))
                std::cout << *staff[i] << "\n";

        std::cout << "\nDEPARTMENTS:\n";
        for(int i = 0; i < departments.size(); i++)
            std::cout << departments[i] << "\n";

        return 0;
    }
    catch(const HospitalException& e)
    {
        std::cout << "Hospital error: " << e.what() << "\n";
    }
    catch(const std::exception& e)
    {
        std::cout << "Standard error: " << e.what() << "\n";
    }
}
