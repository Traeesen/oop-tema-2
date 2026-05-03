/*
Numele temei pt review: Pariuri sportive
Nume coleg review: Bugeac Alexandru
*/
#include <iostream>
#include <cstring>
#include <vector>
#include "staff.h"
#include "staff.cpp"
#include "department.h"
#include "department.cpp"
#include "patient.cpp"

int main()
{
    std::cout << "Do you wish to autogenerate data? (Y/N) ";
    char answer[2];
    std::cin.getline(answer,2);
    answer[1]=0;
    if(strcmp(answer, "Y")==0 || strcmp(answer, "y")==0)
    {
        Department d("HR", 10000);

        Employee e1("Alice", 3000, 5);
        Employee e2("Bob", 2500, 3);
        Employee e3("Charlie", 4000, 8);
        Employee e4("MerekiDor", 1, 189);
        Employee e5("I_Like_Money", 800000, 0);

        Project p1("HR", 20000, 100);
        Project p2("Getting rid of MerekiDor", 1800, 60);

        d.addEmployee(e1);
        d.addEmployee(e2);
        d.addEmployee(e3);
        d.addEmployee(e4);
        d.addEmployee(e5);

        d.addProject(p1);
        d.addProject(p2);

        d.assignEmployeeToProject(e1, p1);
        d.assignEmployeeToProject(e2, p1);
        d.assignEmployeeToProject(e3, p2);

        std::cout << d << "\n";
        
        d.optimiseAssignments();

        std::cout<<"\n--- ASSIGNMENTS HAVE BEEN OPTIMISED ---\n\n";
        std::cout<<d;
    }
    else
    {
        int numDepartments;
        std::cout << "Enter number of departments: ";
        std::cin >> numDepartments;
        std::cin.ignore();

        Department** departments = new Department*[numDepartments];

        for (int d = 0; d < numDepartments; d++)
        {
            char depName[100];
            std::cout << "\nDepartment " << d + 1 << " name: ";
            std::cin.getline(depName, 100);

            int budget;
            std::cout << "Enter monthly budget: ";
            std::cin >> budget;
            std::cin.ignore();

            departments[d] = new Department(depName, budget);

            int numEmployees;
            std::cout << "Enter number of employees: ";
            std::cin >> numEmployees;
            std::cin.ignore();

            for (int i = 0; i < numEmployees; i++)
            {
                char name[100];
                int salary, experience;
                std::cout << "Employee " << i + 1 << " name: ";
                std::cin.getline(name, 100);
                std::cout << "Salary: ";
                std::cin >> salary;
                std::cout << "Years of experience: ";
                std::cin >> experience;
                std::cin.ignore();

                Employee* e = new Employee(name, salary, experience);
                departments[d]->addEmployee(*e);
            }

            int numProjects;
            std::cout << "Enter number of projects: ";
            std::cin >> numProjects;
            std::cin.ignore();

            for (int i = 0; i < numProjects; i++)
            {
                char name[100];
                int reward, work;
                std::cout << "Project " << i + 1 << " name: ";
                std::cin.getline(name, 100);
                std::cout << "Reward: ";
                std::cin >> reward;
                std::cout << "Work required: ";
                std::cin >> work;
                std::cin.ignore();

                Project* p = new Project(name, reward, work);
                departments[d]->addProject(*p);
            }

            departments[d]->optimiseAssignments();
        }

        for (int d = 0; d < numDepartments; d++)
        {
            std::cout<<'\n'<<*(departments[d]);
            delete departments[d];
        }
        delete[] departments;
    }

    return 0;
}