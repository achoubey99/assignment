#include "Socket.h"

//char rcvDataBuf[maxDataSize];

int main()
{

   // declaring and defining the server port
   uint16_t serverPort=3002; // any port number>1024 should work
   string serverIpAddr = "127.0.0.1", sendDataStr; // dummy server ip address(here it is the loop back address)
   int N; // stores max number of clients 
   vector<string> client_names; // stores the username of different clients
   vector<int> list_of_clientfd;
   int max_socket_seen, bytes_recv;
   char rcvDataBuf[maxDataSize];

   // take input from the terminal to set the server port and server ip address
   cout<<"------------------ Server ----------------------"<<endl;
   cout<<"IP address of the Server: ";
   //cin>>serverIpAddr;
   cout<<"Port number of the Server: ";
   //cin>>serverPort;
   cout<<"Max number of clients that can group chat: ";
   cin>>N;

   // setup the server process
   int serverSocketFd = server_setup(serverIpAddr,serverPort);
   max_socket_seen = serverSocketFd;

   // declaring fd_set to keep track of open sockets and readable sockets
   fd_set current_sockets, ready_read_sockets;

   //initialize
   FD_ZERO(&current_sockets);
   FD_SET(serverSocketFd, &current_sockets); // add server socket to current socket

   // keep looping untill either server or client closes connection
   while(1)
   {

      // select is destructive so we need to use the copy of current_sockets
      ready_read_sockets = current_sockets;

      // use select() API to check which socket is currently readable
      if(select(FD_SETSIZE, &ready_read_sockets,NULL,NULL,NULL)< 0)
      {
         cout<<"Error"<<endl; 
         exit(1);
      }

      // iterate through the available sockets to check for their status
      for (int i = 0; i <= max_socket_seen; ++i)
      {

         if(FD_ISSET(i, &ready_read_sockets)) // check if the ith socket is ready for reading
         {
            if(i==serverSocketFd && list_of_clientfd.size()==N) // chatroom full
            {
               cout<<"New connection request rejected as group chat is currently full"<<endl;
               int newClientFd = accept_connection(serverSocketFd);
               send(newClientFd, "#FULL", 6, 0);// signal that chatroom is full
               close(newClientFd);
               continue;
            }
            if(i==serverSocketFd)// new connection and space available
            {
               int newClientFd = accept_connection(serverSocketFd);
               // ask the client for username
               //char buff[200] = "\n\t\tPress\n\t\t1. Registration\n\t\t2. Login\n\t\t3. Exit\n\t\tChoice: ";
               char buff[100]="1";
               send(newClientFd, buff, sizeof(buff), 0);
               //send(newClientFd, "Enter the name of user: ", 25, 0);
               // reset the rcv buffer before storing new data

               memset(&rcvDataBuf, 0, maxDataSize); 
               // receive username from client
               recv(newClientFd, &rcvDataBuf, maxDataSize, 0); 
               if(is_number(rcvDataBuf)){
                  //cout<<"Number"<<endl;
                  switch(atoi(rcvDataBuf))
                  {
                     case 1:
                           cout<<"Registration"<<endl;
                           
                           strcpy(buff, "Registration Done!");
                           send(newClientFd, buff, strlen(buff), 0); 
                           break;
                     case 2:
                           cout<<"Login"<<endl;
                           
                           // for indicate start of conversation at the client
                           strcpy(buff, "Login Success");
                           send(newClientFd, buff, strlen(buff), 0); 
                           break;
                     case 3:
                           strcpy(buff, "Disconnected From Server");
                           send(newClientFd, buff, strlen(buff), 0); 
                           close(newClientFd);
                           break;
                     default:
                           cout<<"Not correct choice"<<endl;
                  }
               }
               else
                  cout<<"Not Number"<<endl;

               
               // for indicate start of conversation at the client
               //send(newClientFd, "---------------------------------------", 41, 0); 
               // after the above step, the rcvDataBuf contains the new clients name
               // add the name to the vector
               client_names.push_back(convertToString(rcvDataBuf,sizeof(rcvDataBuf)/sizeof(char))); 
               cout<<rcvDataBuf<<" connected"<<endl;
               // prepare msg to be broadcasted for all other clients to let them know a new client has joined
               sendDataStr = "############## ";
               sendDataStr.append(rcvDataBuf); sendDataStr = sendDataStr+" connected ##############";
               // reset the rcv buffer
               memset(&rcvDataBuf, 0, maxDataSize); 
               // convert string to char array
               strcpy(rcvDataBuf, sendDataStr.c_str());
               // broadcast
               broadcast_msg_to_all_clients("", serverSocketFd, list_of_clientfd,client_names);
               // add the newClient to the list of active clients
               list_of_clientfd.push_back(newClientFd);
               FD_SET(newClientFd, &current_sockets); // add the new client to the watch list
               if(newClientFd>max_socket_seen) max_socket_seen = newClientFd;
            }
            else
            {
               //TASK 1: handle connection for client socket i i.e. read from whoever wants to speak
               memset(&rcvDataBuf, 0, maxDataSize); // reset the rcv buffer
               bytes_recv = handle_connection(i);

               if(bytes_recv==-1) continue;

               // check if the client i wants to leave the group chat
               if(!strcmp(rcvDataBuf, "bye"))
               {
                  close(i);
                  // remove the socket i from watch list
                  FD_CLR(i,&current_sockets);
                  int index_of_socket_i = getIndex(list_of_clientfd,i);
                  string leaving_client = client_names[getIndex(list_of_clientfd,i)];
                  // display msg on server showing that a client has left
                  cout<<leaving_client<<" left the group chat"<<endl;
                  // remove the client
                  list_of_clientfd.erase(list_of_clientfd.begin()+index_of_socket_i);
                  client_names.erase(client_names.begin()+index_of_socket_i);
                  // broadcast the leaving msg on all active clients
                  memset(&rcvDataBuf, 0, maxDataSize); 
                  broadcast_msg_to_all_clients(leaving_client+" left the group chat", 
                                               serverSocketFd, list_of_clientfd,client_names);
                  continue;
               }                  

               //TASK 2: Then broadcast this msg to all the clients
               broadcast_msg_to_all_clients(client_names[getIndex(list_of_clientfd,i)], serverSocketFd, list_of_clientfd, client_names);            
            }
         }
      }

   }
   return 0;
}