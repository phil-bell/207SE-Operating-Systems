#include <arpa/inet.h>

#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>


#define MAX_MSG 100
#define LINE_ARRAY_SIZE (MAX_MSG+1)

using namespace std;

int main()
{
  int listenSocket, connectSocket, i;
  unsigned short int listenPort;
  socklen_t clientAddressLength;
  struct sockaddr_in clientAddress, serverAddress;
  char line[LINE_ARRAY_SIZE];
  int num1; //first number in the RPN
  int num2; //second number in the RPN
  char sign; //the sign that the user has selected
  char output; //output to be put in the line array so it can be sent to the client
  int temp; //temp that is used to store the value that is make by the sum of the users RPN before it is converted to a char(output) to be put in line

  cout << "Enter port number to listen on (between 1500 and 65000): ";
  cin >> listenPort;

  // Create socket for listening for client connection
  // requests.
  listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocket < 0) {
    cerr << "cannot create listen socket";
    exit(1);
  }
  
  // Bind listen socket to listen port. First set various
  // fields in the serverAddress structure, then call
  // bind().

  // htonl() and htons() convert long integers and short
  // integers (respectively) from host byte order (on x86
  // this is Least Significant Byte first) to network byte
  // order (Most Significant Byte first).
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddress.sin_port = htons(listenPort);
  
  if (bind(listenSocket,
           (struct sockaddr *) &serverAddress,
           sizeof(serverAddress)) < 0) {
    cerr << "cannot bind socket";
    exit(1);
  }

  // Wait for connections from clients. This is a
  // non-blocking call; i.e., it registers this program with
  // the system as expecting connections on this socket, and
  // then this thread of execution continues on.
  listen(listenSocket, 5);
  
  while (1) {
    cout << "Waiting for TCP connection on port " << listenPort << " ...\n";

    // Accept a connection with a client that is requesting
    // one. The accept() call is a blocking call; i.e., this
    // thread of execution stops until a connection comes
    // in. connectSocket is a new socket that the system
    // provides, separate from listenSocket. We *could*
    // accept more connections on listenSocket, before
    // connectSocket is closed, but this program doesn't do
    // that.
    clientAddressLength = sizeof(clientAddress);
    connectSocket = accept(listenSocket,
                           (struct sockaddr *) &clientAddress,
                           &clientAddressLength);
    if (connectSocket < 0) {
      cerr << "cannot accept connection ";
      exit(1);
    }
    
    // Show the IP address of the client.
    // inet_ntoa() converts an IP address from binary form to the
    // standard "numbers and dots" notation.
    cout << "  connected to " << inet_ntoa(clientAddress.sin_addr);

    // Show the client's port number.
    // ntohs() converts a short int from network byte order (which is
    // Most Significant Byte first) to host byte order (which on x86,
    // for example, is Least Significant Byte first).
    cout << ":" << ntohs(clientAddress.sin_port) << "\n";

    // Read lines from socket, using recv(), storing them in the line
    // array.  If no messages are currently available, recv() blocks
    // until one arrives.
    // First set line to all zeroes, so we'll know where the end of
    // the string is.
    memset(line, 0x0, LINE_ARRAY_SIZE);
    while (recv(connectSocket, line, MAX_MSG, 0) > 0) {
      cout << "  --  " << line << "\n";

      num1 = line[0] -'0'; //converts the first value to an integer and puts it in the var num1
      num2 = line[1] -'0'; //converts the second value to an integer and puts it in the var num2
      sign = (char)line[2]; //buts the third value that will be the operator in the var sign
      cout << num1 << endl; // this line and the next 2 output what has been put in the num1, num2 and sign to the server screen to make sure it is correct
      cout << num2 << endl;
      cout << sign << endl;

      if (sign == '+') //if the user has entered "+" then it does the following
      {
        temp = num1+num2; //adds the 2 numbers the user entered and stores it in temp
      }
      else if(sign == '-') //if the user has entered "-" then it does the following
      {
        temp = num1-num2; //subtracts the 2 numbers the user entered and stores it in temp
      }
      else if(sign == '*') //if the user has entered "*" then it does the following
      {
        temp = num1*num2; //multiplies the 2 numbers the user entered and stores it in temp
      }
      else if(sign == '/') //if the user has entered "/" then it does the following
      {
        temp = num1/num2; //divides the 2 numbers the user entered and stores it in temp
      }
      else //if the user hasn't used a valid operator
      {
        cout << "User entered invalid entry\n";
      }
      output = temp + '0';//temp is converted to the char output so it can be stored in line
      line[0] = output;//sets the first value in line to the sum of the users equation. The integer has been converted to a char so it can be sent to the client
      line[1] = '\0';//this and the next line empty the array
      line[2] = '\0';
      cout << "temp: " << temp << endl; //this and the next 2 lines output the 3 variable temp. output and line to the server screen so you can see they have been converted from int to char to char* correctly.
      cout << "output: " << output << endl;
      cout << "line: " << line << endl;

      // Send converted line back to client.
      if (send(connectSocket, line, strlen(line) + 1, 0) < 0)
        cerr << "Error: cannot send modified data";

      memset(line, 0x0, LINE_ARRAY_SIZE);  // set line to all zeroes
    }
  }
}

