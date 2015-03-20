#include <iostream>
#include <string>
#include "globalFunctions.h"

extern "C" {
#include <netdb.h>
#include <arpa/inet.h>
}

using std::string;
using std::cout;
using std::endl;


const int BACKLOGSIZE = 20;
const int BUFFERSIZE = 128;

int main(int argc, char *argv[]){
  // Create the server socket
  addrinfo* info = populateAddrInfo();
  int serverFd = getSocket(*info);

  // Allow us to reuse the socket if we restart the application
  int yes = 1;
  setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  // Set listening port (bind descriptor to actual pipe)
  bind(serverFd, info->ai_addr, info->ai_addrlen);
  freeaddrinfo(info);

  // Start listening for connection attempts
  listen(serverFd, BACKLOGSIZE);

  // Block until someone connects
  sockaddr_storage clientAddr;
  socklen_t connAddr = sizeof(sockaddr_storage);
  int acceptedClientFd = accept(serverFd, reinterpret_cast<sockaddr*>(&clientAddr), &connAddr);

  // Wait for them to send us a message
  char buf[BUFFERSIZE];
  recv(acceptedClientFd, reinterpret_cast<void*>(&buf), BUFFERSIZE, 0);
  cout << "Server got message! " << buf << endl;

  // Send a response
  string reply("Hello client!");
  send(acceptedClientFd, reply.data(), reply.size(), MSG_NOSIGNAL);

  // Clean up
  close(acceptedClientFd);
  close(serverFd);

  return 0;
}
