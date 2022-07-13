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

int main(int argc , char *argv[])
{	
	vector<Employee*>v;

	
	Employee *e=new Employee("abc" , 1001 , 10000);
	v.push_back(e);

	Employee *e=new Employee("def" , 1002 , 10020);
	v.push_back(e);

	Employee *e=new Employee("xyz" , 1003 ,10110);
	v.push_back(e);
	
	fstream x;
	

	int pid;
	pid=fork();
	if (pid== 0)
	{
		cout<<"child starts"<<endl;
		x.open(argv[1], ios::out);
		vector<Employee*>::iterator itr;
		if(!x)
		{
			cout<<"\n unable to open the file"<<wndl;
			exit(0);
		}

		for(itr=v.begin();itr!=v.end();itr++)
                 {
                         x<<*itr<<endl;
                 }
		x.close();
		cout<<"child terminates"<<endl;
	}
	else
	{
		wait(0);
		cout<<"parent starts"<<endl;
		x.open(argv[1], ios::in);
		
		if(!x)
		{
			cout<<"\n unable to open the file"<<endl;
			exit(0);
		}
		x.read(argv[1]);
		cout<<"file content"<<endl;
		x.close();
		cout<<"parent terminates"<<endl;
	}

return 0;
}
