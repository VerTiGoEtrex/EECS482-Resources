#ifndef GLOBALFUNCTIONS_H_
#define GLOBALFUNCTIONS_H_

#include <cstring>
#include <stdexcept>

extern "C" {
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
}

addrinfo* populateAddrInfo();
int getSocket(addrinfo& info);
#endif
