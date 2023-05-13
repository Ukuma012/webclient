#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// struct in_addr
// {
//         ip_addr_t s_addr;
// };

//  struct sockaddr_in {
//      unsigned char  sin_len;
//      unsigned char  sin_family;
//      unsigned short sin_port;
//      struct in_addr sin_addr;
//      unsigned char  sin_zero[8];
// };

int main(int argc, char *argv[])
{
  int socketfd;
  if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    fprintf(stderr, "socket failed\n");
    exit(1);
  }

  struct sockaddr_in serveraddress;
  serveraddress.sin_family = AF_INET;
  serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
  serveraddress.sin_port = htons(8000);

  printf("%d\n", socketfd);
  exit(0);
}
