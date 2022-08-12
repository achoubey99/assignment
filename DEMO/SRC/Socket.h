#pragma once

#include "myH.h"

// global variables
using namespace std;
const int backLog = 3;
const int maxDataSize = 1460;

//char rcvDataBuf[maxDataSize];

// define and return a TCP socket after doing error checking and setting relevant attributes
int client_setup(string , int , string );


// given the client fd and server port and IP addr, connect the client to the server
void connect_to_server(int , string , int );


// this function received data from the server and stores it in rcvDataBuf array
void recv_data(int , int );


// this function sends data taken from the terminal to the server
void send_data(int , int );


// converts char array to string
string convertToString(char* , int );


// finding index of value K in a vector v(K is always present in v)
int getIndex(vector<int> , int );


// define and return a TCP server socket after doing error checking and setting relevant attributes
// the returned socket would be listening for new connections
int server_setup(string ,int );


// this function accepts incoming connections to the socket given as input and does some error checking
// it returns the socket fd which the server will use for communicating with the client
int accept_connection(int );



// this function receives the data coming to the socket given as input
// it returns the number of bytes received
int handle_connection(int);
void send_data_s(string , int );
void broadcast_msg_to_all_clients(string , int , vector<int> , vector<string> );

bool is_number(const std::string&);

void Login :: registration(string u_fname,	string u_lname,	int u_age ,	string u_gender,string u_email,	long int u_phno,string l_uname,	string l_passwd	)
{
	
	
	int count = 0;
	string rid,rpass;

	
	system("clear");

	cout<<"\t\t\t\t\t\t WELCOME TO THE REGISTRATION PAGE\n\n\n";

	cout<<"\t\t\tEnter your First name:";
	
	cin>>u_fname;

	cout<<"\t\t\tEnter your last name:";

	cin>>u_lname;
			    
			    
	cout<<"\t\t\tEnter your Age:";
	cin>>u_age;
    

	cout<<"\t\t\tEnter your Gender:";
    cin>>u_gender;
    
				        
				        
    cout<<"\t\t\tEnter your Mobile Number:";
    cin>>u_phno;
					      
					      
					      
	cout<<"\t\t\tEnter your Email-id:";
    cin>>u_email;
	

	cout<<"\t\t\tEnter any username:";
	cin>>l_uname;
	cout<<"\t\t\tEnter your password:";
	cin>>l_passwd;

	ifstream f("record.txt");
	while(f>>rid)
	{
		if(rid == l_uname)
		{
			count =1;
		}
	}
	f.close();
	if(count==1)
		{
			cout<<"\n\n This Username is taken, please try another\n";			
		}
	else
	{
		ofstream f1("record.txt" , ios::app);
		f1<<u_fname<<' '<<u_lname<<' '<<u_age<<' '<<u_gender<<' '<<u_phno<<' '<<u_email<<' '<<l_uname<<' '<<l_passwd<<endl;
		cout<<"\n\t\t\t registration is successful:\n";
		
	}
}


void Login :: signIn(string l_uname, string l_passwd)
{	
	
	int count;
	string id,pass;
	
	

	cout<<"\t\t\t please enter the username and password:"<<endl;
	cout<<"\t\t\t username: ";
	cin>>l_uname;
	cout<<"\t\t\t password: ";
	cin>>l_passwd;


	ifstream input("record.txt");
	while(input>>id>>pass)
	{
	if(id==l_uname &&  pass==l_passwd)
	{
		count=1;

		
	}
	}
	input.close();
	if(count==1)
	{	
		
		cout<<l_uname<<" your login is successful!\nthanks for logging in \n";
		sleep(5);

		
	}
	else{
		cout<<"\n login error \n please check your username and password"<<endl;
		
	
	}
	}





