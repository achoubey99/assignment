#include "Socket.h"

int main()
{

   // declaring and defining the server port and IP address
   uint16_t serverPort=3002;
   string serverIpAddr = "127.0.0.1", clientIpAddr = "127.0.0.1", type_of_connection="TCP";
   // declaring buffers for sending and receiving data
   char rcvDataBuf[maxDataSize], sendDataBuf[maxDataSize]; 
   int flags = 0;
   cout<<"------------------ Client ----------------------"<<endl;
   cout<<"IP address of the Server you want to connect with: "<<serverIpAddr<<endl;
   //cin>>serverIpAddr;
   cout<<"Port number of the Server you want to connect with: "<<serverPort<<endl;
   //cin>>serverPort;

   // setup the client and connect to the server
   int clientSocketFd = client_setup(serverIpAddr, serverPort, type_of_connection);
   connect_to_server(serverPort, serverIpAddr, clientSocketFd);

   // beginning threads to asynchronously send and receive data from the server
   thread worker_r(recv_data, clientSocketFd, flags); // this thread is responsible to constantly checking if server 
                                    // has sent some data or not and then print data in the console.

   thread worker_s(send_data, clientSocketFd, flags); // this thread is responsible for taking input from the terminal
                                    // at any point of time and sending it to the server

   // stop the threads
   worker_r.join();
   worker_s.join();

   return 0;

}   