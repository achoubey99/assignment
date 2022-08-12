#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/select.h>
#include <errno.h>
#include <fstream>
#include <sys/wait.h>
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <algorithm>

#define PORTNO 8888 
#define bSIZE 1024
#define TRUE 1
#define FALSE 0

using namespace std;

class User
{
    protected:
    string u_fname;
    string u_lname;
    int u_age;
    string u_gender;
    string u_email;
    long int u_phno;

    public:
    void setFname(string f){u_fname = f;}
    void setLname(string l){u_lname = l;}
    void setAge(int a){ u_age = a;}
    void setGender(string g){u_gender = g;}
    void setEmail(string e){ u_email = e;}
    void setPhno(long int p){u_phno = p;}

    string getFame(){return u_fname;}
    string getLname(){return u_lname;}
    int getAge(){return u_age;}
    string getGender(){return u_gender;}
    string getEmail(){return u_email;}
    long int getPhno(){return u_phno;} 
};

class Login: public User 
{
    private:
    string l_uname;
    string l_passwd;

    public:
    void registration(string,string ,int  ,	string ,string ,long int ,string,string );
    
    void signIn(string,string );

};



void WelComeMsg();
//int Menu();
int subMenu();
void Action_SM(int);
void Action_M(int);