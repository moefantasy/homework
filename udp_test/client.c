#include "unp.h"
#include "../np.h"


void dg_cli(FILE* fp, int sockfd, const SA *pservaddr, socklen_t servlen);

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc !=2 )
        err_quit("usage udpcli <IPaddress>");

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    printf("%s", argv[1]);
    np_inet_pton4(argv[1], &servaddr.sin_addr);
    

    sockfd = np_socket4(SOCK_DGRAM, 0);

    dg_cli(stdin, sockfd, (SA*)&servaddr, sizeof(servaddr));

    exit(0);
}

void dg_cli(FILE* fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE +1];

    while(np_fgets(sendline, MAXLINE, fp) != NULL)
    {
        np_sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);

        n = np_recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        recvline[n] = 0;

        np_fputs(recvline, stdout);
    }
    
}

