#include "myH.h"

void WelComeMsg()
{
	system("clear");
	cout<<"\n\t\tWelcome to the Client-Server Application"<<endl;
}


	

int subMenu(){
	system("clear");
	cout<<"\n\t\tPress"<<endl;
	cout<<"\n\t\t1. Process Data"<<endl;
	cout<<"\n\t\t2. Search"<<endl;
	cout<<"\n\t\t3. GoBack to Main Menu"<<endl;
	cout<<"\n\t\tChoice: ";
	int ch=0;
	cin>>ch;
	return ch;
}

void Action_SM(int ch)
{
	cout<<"Choice: "<<ch<<endl;
	switch(ch)
	{
		case 1:
			cout<<"Sub Menu case 1"<<endl;
			break;
		case 2:
			cout<<"Sub Menu case 2"<<endl;
			break;
		case 3:
			//Action_M(Menu());
			break;
		default:
			cout<<"Enter Correct Choice"<<endl;

	}

}

void Action_M(int ch)
{
	switch(ch)
	{
		case 1:
			cout<<"Registration Process"<<endl;
			break;
		case 2:
			cout<<"Login Process"<<endl;
			Action_SM(subMenu());
			break;
		case 3:
			system("clear");
			cout<<"\n\n\n\t\t\t==========Exit=========\n\n\n"<<endl;
			exit(0);
			break;
		default:
			cout<<"Enter Correct Choice"<<endl;

	}

}



// int main()
// {
	
// 	WelComeMsg();
// 	Action_M(Menu());

// 	return 0;

// }