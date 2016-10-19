#include "unp.h"
#include "../np.h"

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen);
int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    np_bind(sockfd, (SA*)&servaddr, sizeof(servaddr));

    dg_echo(sockfd, (SA*)&servaddr, sizeof(servaddr));
    
}

void dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
    int n;
    socklen_t len;
    char msg[MAXLINE];

    for(;;){
        len = clilen;
        n = np_recvfrom(sockfd, msg, MAXLINE, 0, pcliaddr, &len);

        np_sendto(sockfd, msg, n, 0, pcliaddr, len);
    }
}
