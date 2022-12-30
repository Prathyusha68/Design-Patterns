#include <iostream>
#include <list>

using namespace std;

/* Interface Component */
class Employee
{
public:
    void addEmployee(Employee){};
    virtual void showEmployeeDetails(){};
    void removeEmployee(Employee){};
};

/* Leaf */
class Developer : public Employee
{

    string empName;
    int salary = 0;
    int empId = 0;

public:
    Developer(int empId, int salary, string empName) : empId{empId}, salary{salary}, empName{empName}
    {
    }
    void showEmployeeDetails()
    {
        cout << "empName: " << empName << " empId: " << empId << " salary: " << salary << endl;
    }
};

/* Leaf */
class Manager : public Employee
{
    string empName;
    int salary;
    int empId;

public:
    Manager(int empId, int salary, string empName) : empId{empId}, salary{salary}, empName{empName}
    {
    }

    void showEmployeeDetails()
    {
        cout << "empName : " << empName << " empId: " << empId << " salary: " << salary << endl;
    }
};

/* Composite */
class CompanyDirectory : Employee
{
    list<Employee *> empList;

public:
    ~CompanyDirectory()
    {
        for (auto emp : empList)
        {
            delete emp;
        }     
    }
    
    void addEmployee(Employee *emp)
    {
        empList.push_back(emp);
    }

    void showEmployeeDetails()
    {
        for (Employee *emp : empList)
        {
            emp->showEmployeeDetails();
        }
    }

    void removeEmployee(Employee *emp)
    {
        empList.remove(emp);
    }
};

/* Client */
int main()
{
    /* We can use Factory design pattern here to get obj based on type instead of creating abog here */
    Developer *dev1 = new Developer(1, 50000, "Bob");
    Developer *dev2 = new Developer(2, 100000, "Alice");
    CompanyDirectory *cmpnyDir = new CompanyDirectory();
    cmpnyDir->addEmployee(dev1);
    cmpnyDir->addEmployee(dev2);
    cmpnyDir->showEmployeeDetails();
    cout << endl;

    Manager *man1 = new Manager(3, 300000, "Roy");
    Manager *man2 = new Manager(4, 200000, "Harry");
    CompanyDirectory *cmpnyDir1 = new CompanyDirectory();
    cmpnyDir1->addEmployee(man1);
    cmpnyDir1->addEmployee(man2);
    cmpnyDir1->showEmployeeDetails();
    cout << endl;

    cmpnyDir1->removeEmployee(man1);
    cmpnyDir1->showEmployeeDetails();
}