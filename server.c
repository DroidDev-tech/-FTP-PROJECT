/*
  This code is a modification by Ibrahim Stephen Jatau ,of the basic Concurrent Echo Server for linux platform.
  Provided by Dr Devrim Seral It's used to teach how basic server  running.
For compile code : # gcc prog.name.c -o execfile
  -----------------------Copyright Devrim Seral---------------------------------
*/



#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SIZE 1024
#define DEF_BUFLEN 512
#define PORT 3233
#define NAME 20

void filedirectory(){
    char dirlist[200] ="";
    printf(path);
    DIR *d;
    struct direct *dir;
    d = opendir(path);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strcmp(dir->d_name, ".")
                != 0 && strcmp(dir->d_name, "..") != 0)
                strcat(strcat(drls,"\n"),
                       dir->d_name);
        }
        closedir(d);
    }
    strcat(drls, "\n.\n");
    strcpy(dirList, drls);
}

int auth_handler(){
    char *user[20]="user";
    char *pass[20]="user000";

}
char *user;
char *pass;
char userId[20];
char userPass[20];
char comm[5];
char path[100];
char dirList[200];
char serverFile[1000];


void est_file(int sf) {
    int length,
    int cpath;
    int n;
    int  rbuflen = DEF_BUFLEN;
    char rbuf[DEF_BUFLEN];
    char bmsg[DEF_BUFLEN];
    char sMessage[100] = "Welcome to  FTP  Server";
    char authMsg[4] = "400";
    n=strlen(sMessage)+1;
    send( sf, sMessage, n, 0 );

    //receiving path from client
    cpath = recv(sf, rbuf, rbuflen, 0);
    strcpy(path,recvbuf);
    printf(path);

    do {



        cpath = recv(sf, rbuf, rbuflen, 0);
        strcpy(comm, rbuf);

        if (cpath > 0) {
            if(strncmp(comm, "USER", 4)== 0){
                cpath = recv(fd, rbuf, rbuflen, 0);
                strcpy(userId, rbuf);
                cpath = recv(fd, rbuf, rbuflen, 0);
                strcpy(userPass, rbuf);
                printf("Username: %s\n", userId);
                printf("password: %s\n", userPass);
                if(strcmp(userId, "test") == 0){
                    if(strcmp(userPass, "test01") == 0){
                        strcpy(authMsg, "200");
                        n=strlen(authMsg)+1;
                        send( sf, &authMsg, n, 0 );
                    }
                    else{
                        strcpy(authMsg, "400");
                        n=strlen(authMsg)+1;
                        send( sf, &authMsg, n, 0 );
                    }
                    printf(authMsg);
                }
                else
                    printf("Error");
            }
            else if(strncmp(comm, "LIST", 4)== 0){
                directory();
                n=strlen(dirList)+1;
                send( sf, dirList, n, 0 );
                printf(dirList);
            }
            else if(strncmp(comm, "DEL", 3)== 0){
                cpath = recv(sf, rbuf, rbuflen, 0);
                sleep(1);
                char tempPath[30];
                strcpy(tempPath,path);
                char *filepath = strcat(tempPath, rbuf);

                int status = remove(fullpath);
                if(status){
                    strcpy(authMsg, "400");
                    n=strlen(authMsg)+1;
                    send( sf, &authMsg, n, 0 );
                }
                else{
                    strcpy(authMsg, "200");
                    n=strlen(authMsg)+1;
                    send( fd, &authMsg, n, 0 );
                }
            }
            else if(strncmp(command, "GET", 3)== 0){
                cpath = recv(sf, rbuf, rbuflen, 0);
                sleep(1);
                char tempPath[100];
                strcpy(tempPath,path);
                char *sfilepath = strcat(tempPath, rbuf);
                FILE *filepoint;
                char buffer[SIZE];
                char c;

                // assignment result conditon
                if (filepoint =fopen(sfilepath,"q")){
                    while(fgets(buffer, 255, f)
                    != NULL){
                        strcat(serverFile, buffer);
                    }
                    strcat(serverFile, "\n.\n");
                    n=strlen(serverFile)+1;
                    send( sf, serverFile, n, 0 );

                }
                else{
                    char fileMsg[4] ="400";
                    n=strlen(fileMsg)+1;
                    send( sf, fileMsg, n, 0 );
                }
            }

            printf("[+] Command Input: %s\n", comm);



        }
        else if (cpath == 0)
            printf("[+]Socket Connection closing...\n");
        else  {
            printf("[-]Error occurred receiving file:\n");
            close(sf);
            break;
        }
    } while (cpath > 0);
}



int main()
{
    int serversock;
    int clientsock;
    struct sockaddr_in server_addr;
    struct sockaddr_in remote_addr;
    char *ipAddress = "127.0.0.1";
    int length;
    int sf;
    int cpath;
    int optval;
    pid_t pid;

    serversock = socket(AF_INET, SOCK_STREAM, 0);
    if(serversock < 0) {
        perror("[-] Socket creation Error");
        exit(1);
    }
    printf("[+]Server socket has been created successfully.\n");


    /* Set address structure to zero */
    memset( &server_addr,0, sizeof(server_addr));
    memset( &remote_addr,0, sizeof(remote_addr));

/* Set server address  */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(ipAddress);


// set SO_REUSEADDR on a socket to true (1):
    optval = 1;
    setsockopt(serversock, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof optval);

    sf = bind(serversock, (struct sockaddr*)
            &server_addr, sizeof(server_addr));
    if(sf < 0) {
        perror("[-]Error in socket Binding");
        exit(1);
    }
    printf("[+]Binding established successfully.\n");

    if(listen(serversock, SOMAXCONN) < 0){
        printf("[+]Socket Listening....\n");
    }else{
        perror("[-]Error occurred listening");
        exit(1);
    }

    printf(" [+] System ready on port %d\n",PORT);
    printf("Wait for connection\n");

    while(1) {
        addr_size = sizeof remote_addr;
        if ((sf = accept(serversock,
                         (struct sockaddr *)&remote_addr,
          &addr_size)) == -1) {
            perror(" [-] Error Accepting Connection");
            continue;
        }

        printf("FTP Server: accepted connection from %s\n", \
            inet_ntoa(remote_addr.sin_addr));

        //start new child process //
        if ((pid=fork()) == 0) {
            close(serversock);
            est_file(sf);
            printf(" [+] Client task completion\n");
            close(sf));
            exit(0);
        }

    }
    printf("[+]Closing Server....\n");
    close(serversock);
}


