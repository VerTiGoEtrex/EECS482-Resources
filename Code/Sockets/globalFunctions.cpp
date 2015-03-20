#include "globalFunctions.h"

using std::runtime_error;
using std::string;

addrinfo* populateAddrInfo() {
  addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET; // IPv4
  hints.ai_socktype = SOCK_STREAM; // TCP
  hints.ai_flags = AI_PASSIVE;
  const char* const host = "localhost";
  const char* const service = "25682"; // Use port 25682, 0 will let OS decide for you

  addrinfo* info;
  auto rc = getaddrinfo(host, service, &hints, &info);
  if (rc != 0)
    throw runtime_error{string{"getaddrinfo error: "} + gai_strerror(rc)};

  return info;
}

int getSocket(addrinfo& info) {
  return socket(info.ai_family, info.ai_socktype, info.ai_protocol);
}
