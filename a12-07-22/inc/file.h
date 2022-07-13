#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#define BUF_SIZE 2000

using namespace std;

class Employee
{
	private:
	string name;
	int empId;
	int salary;
	
	public:
	Employee(){}
	Employee(string n,int e, int s){ name = n; empId =e; salary =s}
 	
	
};

