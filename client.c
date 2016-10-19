#include "unp.h"
#include "np.h"

void str_cli(FILE* fp, int sockfd);
void str_cli_select(FILE* fp, int sockfd);

int main(int argc, char** argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if(argc != 2)
    {
        err_quit("usage: tcpcli <IPaddress>");
    }

    sockfd = np_socket4(SOCK_STREAM, 0);
//    sockfd = Socket(AF_INET, SOCK_STREAM,0);

//    bzero(&servaddr, sizeof(servaddr));
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
//    Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    np_inet_pton4(argv[1], &servaddr.sin_addr);    

//    Connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
    np_connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
//    str_cli_select(stdin, sockfd);
    exit(0);
}

void str_cli(FILE* fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];
    while(Fgets(sendline, MAXLINE, fp)!=NULL){
        Writen(sockfd, sendline, strlen(sendline));
        if( Readline(sockfd, recvline, MAXLINE) == 0 ){
            err_quit("str_cli: server terminated prematurely");
        }
        Fputs(recvline, stdout);
    }
}

void str_cli_select(FILE* fp, int sockfd)
{
    int maxfdpl, stdineof;
    fd_set rset;
    char sendline[MAXLINE], recvline[MAXLINE];
    char buf[MAXLINE];
    int n;

    stdineof = 0;
    FD_ZERO(&rset);
    for(;;)
    {
        if(stdineof ==0)
            FD_SET(fileno(fp), &rset);

        FD_SET(sockfd, &rset);
        maxfdpl = max(fileno(fp), sockfd)+1;
        Select(maxfdpl, &rset, NULL, NULL, NULL);

       if(FD_ISSET(sockfd, &rset))
       {
           if((n=Read(sockfd, recvline, MAXLINE)==0))
           {
               if(stdineof ==0)
                   return;
               else
                err_quit("str_cli: server terminated permaturely!");
           }
           //Fputs(recvline, stdout);
           Write(fileno(stdout), buf, n);
       } 

       if(FD_ISSET(fileno(fp), &rset))
       {
          if((n = Read(fileno(fp), buf, MAXLINE))==0)
          {
            stdineof = 1;
            Shutdown(sockfd, SHUT_WR);
            FD_CLR(fileno(fp), &rset);
            continue;
          } 
          Writen(sockfd, buf, n);
       }
    }
}



















