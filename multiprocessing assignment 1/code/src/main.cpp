#include <multiprcs.h>

void func()
{
	cout<<"function called from parent process"<<endl;
}

int main(int argc, char* argv[])
{
	string l1,l2;
	
	
	fstream f;
		


	int pid;
	pid=fork();

	if (pid==0)
	{	
		cout<<"this is the child process with PID: "<<getpid()<<endl;


		f.open(argv[1] ,ios::out);
		if(!f)
		{	
			cout<<"unable to open the file"<<endl;
			exit(0);
		}
		else
		{
			cout<<"enter the content to be entered"<<endl;
		        cout<<"Enter the data:"<<endl;
                        cin>>l1;
                        cin>>l2;
			f<<l1;
			f<<l2;

			f.close();
		}
		cout<<"child prcocess ends"<<endl;
	}
	else
	{	
		wait(0);
		cout<<"this is the parent process with PID"<<getpid()<<endl;
		f.open(argv[1] , ios::in);
		if(!f)
		{
		cout<<"unable to open the file"<<endl;
		}
		
		cout<<"contents of the file are"<<endl;
		      char buf[200];
			f.read(buf,200);
			cout<<buf<<endl;
		
		f.close();

		func();
		cout<<"parent process ends"<<endl;
	} 	
return 0;
}














	
					



	
		
