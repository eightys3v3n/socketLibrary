#include <cstdio>
#include <cassert>
#include "socket.hpp"


int main()
{
  std::string buff = "";
  int result;

  Socket s("127.0.0.1", 25555);
  printf("Initialized socket. Please start a server on %s:%d and press enter.",
    s.host.c_str(), s.port);
  getchar();

  printf("Attempting to connect...\n");
  result = s.connect();
  if (result)
  {
    printf("Failed to connect %d.\n", result);
    return 1;
  }
  printf("Connected.\n");

  s.send("hello world\n");
  printf("Sent 'hello world\\n'.");
  getchar();

  printf("Please send 7 or more bytes.\n");
  printf("Waiting to receive 4 bytes...\n");
  buff = s.receive(4);
  assert(buff.length() == 4);
  printf("Received '%s'.\n", buff.c_str());

  printf("Reading 2 more bytes...\n");
  buff += s.read(2);
  assert(buff.length() == 6);
  printf("Received '%s'.\n", buff.substr(4).c_str());

  printf("Reading the rest of received bytes...\n");
  buff += s.read();
  assert(buff.length() > 6);
  printf("Received '%s'.\n", buff.substr(6).c_str());

  s.close();
  printf("Closed socket.\n");

  return 0;
}