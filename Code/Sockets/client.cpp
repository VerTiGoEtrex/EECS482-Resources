#include <iostream>
#include <string>
#include <algorithm>
#include "globalFunctions.h"

extern "C" {
#include <netdb.h>
#include <arpa/inet.h>
}

using std::string;
using std::cout;
using std::cin;
using std::endl;


const int BACKLOGSIZE = 20;
const int BUFFERSIZE = 128;

int main(int argc, char *argv[]){
  // Create the client socket
  addrinfo* info = populateAddrInfo();
  int clientFd = getSocket(*info);

  // Attempt a connection
  connect(clientFd, info->ai_addr, info->ai_addrlen);
  freeaddrinfo(info);

  // Send some data to the server
  cout << "Please input a message to send to the server!" << endl;
  string msg;
  cin >> msg;
  send(clientFd, msg.data(), msg.size(), MSG_NOSIGNAL);

  // Get a response
  char buf[BUFFERSIZE];
  std::fill_n(buf, BUFFERSIZE, '\0');
  recv(clientFd, reinterpret_cast<void*>(&buf), BUFFERSIZE, 0);

  cout << "Client got response: " << buf << endl;

  // Clean up
  close(clientFd);

  return 0;
}
