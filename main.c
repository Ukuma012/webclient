#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

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

  char *request = "GET / HTTP/1.1\r\nHost: example.com\r\nConnection: close\r\n\r\n";
  int request_len = strlen(request);
  if(send(socketfd, request, request_len, 0) < 0) {
    fprintf(stderr, "send failed\n");
    exit(1);
  }
  printf("%s\n", "msg send success");

  char recvmsg[4096];
  int recvmsg_len = sizeof(recvmsg) - 1;
  int recv_len = recv(socketfd, recvmsg, recvmsg_len, 0);
  if(recv_len < 0) {
    fprintf(stderr, "recv failed\n");
    exit(1);
  }

  recvmsg[recv_len] = '\0';
  printf("status: %s\n", recvmsg);

  exit(0);
}
