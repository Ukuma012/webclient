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
    perror("Error");
    exit(1);
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_address.sin_port = htons(8000);

  if (connect(socketfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    fprintf(stderr, "connect failed\n");
    perror("Error");
    exit(1);
  }

  char *msg = "Hello from client";
  int msg_len = sizeof(msg);
  if(send(socketfd, msg, msg_len, 0) < 0) {
    fprintf(stderr, "send failed\n");
    exit(1);
  }

  printf("%s\n", "msg send success");

  exit(0);
}
