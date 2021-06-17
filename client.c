/*
  This code is a modification by Ibrahim Stephen Jatau ,of the basic  TCP Server for linux platform.
  Provided by Dr Devrim Seral It's used to teach how basic server  running.
For compile code : # gcc prog.name.c -o execfile
  -----------------------Copyright Devrim Seral---------------------------------
*/


#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <pthread.h>


#define PORT 3233
#define DEF_BUFLEN 1024
#define STDIN 0
#define SADDR "127.0.0.1"
#define TV_SEC 10

#define PANIC(msg)  { \
        perror(msg); exit(-1); }

void PANIC(char* msg);

char param1[20];
char param2[20];
char comm[5];
char input[200];

void test_fds(fd_set testfds, int filesock) {
    int bRead;
    char buffer[BUF_LEN];


    if (FD_ISSET(filesock, &testfds)) {
        ioctl(filesock,FIONREAD,&bytesRead);
        if (bRead == 0) {
            printf("[+] Socket byte read successfully.\n");
            exit(0);
        }
        bRead = read(filesock, buffer, bRead);
        buffer[bRead] = '\0';
        printf("%s", buffer);
    }
        if (FD_ISSET(STDIN, &testfds)) {
            ioctl(STDIN,FIONREAD,&nread);
            if (bRead == 0) {
                printf("[+] Keyboard input ok.\n");
                exit(0);
            }
}

int main(int argc, char **argv)
{
    int filesock,
    int bytes_received,
    int authFlag=1,
    int sf;
    int n;
    char send_data[DEF_BUFLEN];
    char recv_data[DEF_BUFLEN];
    struct sockaddr_in server_addr;
    fd_set readfd,testfd;
    struct timeval tv;
    int maxfd;
    int stdeof;
    int q;
    int ret;
    char *saddr = NULL;
    char *fport = NULL;
    char *filept = NULL;


    while ((q = getopt (argc, argv, "f:/:")) != -1)
        switch (q)
        {
            case '/':
                fpath = optarg;
                break;
            case 'f':
                filedd = optarg;
                break;
            case '?':
                fprintf(stderr,"[-]Invalid input: -%d\n",
                        optopt);
                return 1;
            default:
                exit ();
        }


    /* Setting up server socket  */
    filesock = socket(AF_INET, SOCK_STREAM, 0);
    if(filesock < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");


    /* Set Socket  to null values */
    bzero(&(server_addr.sin_zero),sizeof server_addr);
    server_addr.sin_family = AF_INET;

    /* Setting PORT number */
    if ( fport != NULL )
        server_addr.sin_port = htons(atoi(fport));
    else
        server_addr.sin_port = htons(PORT);

    /* Setting ipADDRESS */
    if ( saddr != NULL )
        inet_pton(AF_INET, saddr, &(server_addr.sin_addr));
    else
        inet_pton(AF_INET, SADDR , &(server_addr.sin_addr));

    /* Setting up server connection */
    sf= connect(filesock, (struct sockaddr *)
            &server_addr, sizeof(server_addr));
    if(sf == -1) {
        perror("[-] socket connection error");
        exit(1);
    }
    printf("[+]Successfully Connected to Server.");

}

 while (1) {

   bytes_received=recv(filesock,recv_data,DEF_BUFLEN,0);
   if (recv > 0)
   printf("s: %s\n ",recv_data);
   printf(filept);
   n=strlen(path)+1;
   send(filesock, path, n, 0);

   //assignment result as condition with (())
    while((authFlag =-1)){
    printf("\n[+] Input User Login Details: ");
    fgets(input,DEF_BUFLEN,stdin);
     sscanf(input,"%s %s %s", comm, param1, param2);

        if(strncmp(comm, "USER",3)== 0){
            printf("\n[+] Logging into FTP server ... ");

            n=strlen(comm)+1;
            send( filesock, comm, n, 0 );
            sleep(1);
            n=strlen(param1)+1;
            send( filesock, param1, n, 0 );
            sleep(1);
            n=strlen(param2)+1;
            send( filesock, param2, n, 0 );

            bytes_recieved=recv(filesock,recv_data,DEF_BUFLEN,0);
            printf(recv_data);

            if (strcmp(recv_data, "200")==0){
                authFlag=1;
                printf("\n[+] s: %s User %s logged in\n ",recv_data,param1);

                while(1){

                    printf("Input here : ");
                    fgets(input,BUF_LEN,stdin);
                    // format string not a string literal made argument
                    printf("%s", input);
                    sscanf(input,"%s %s %s", comm, param1, param2);
                    n=strlen(command)+1;
                    send( filesock, comm, n, 0 );

                    if(strncmp(comm, "LIST", 4)== 0){
                        printf("\n [+]Querying FTP Server File List \n");

                        bytes_recieved=recv(filesock,recv_data,DEF_BUFLEN,0);
                        if (recv > 0)
                            printf("s: %s\n ",recv_data);

                    }

                    //  GET file from server
                    else if(strncmp(comm, "GET", 3)== 0){
                        printf("[+] Retrieving the file from server ...\n");
                        n=strlen(param1)+1;
                        send( filesock, param1, n, 0 );

                        bytes_recieved=recv(filesock,recv_data,DEF_BUFLEN,0);
                        if(strcmp(recv_data, "400")==0){
                            printf("\ns: %s FILE %s not available.\n ",recv_data, param1);

                        }
                        printf(recv_data);
                    }
                    else if(strncmp(comm, "DEL", 3)== 0){
                        n=strlen(param1)+1;
                        send(filesock, param1, n, 0 );
                        bytes_recieved=recv(filesock,recv_data,DEF_BUFLEN,0);
                        if (strcmp(recv_data, "200")==0){
                            printf("\n[-] s: %s File %s deleted.\n ",recv_data,param1);
                        }
                        else{
                            printf("\n[-] s: %s File %s is not on the server.\n ",recv_data,param1);
                        }
                    }
                    else{
                        printf("[-] Incorrect command");
                    }
                }
            }
            else if (strcmp(recv_data, "400")==0){
                printf("\n[-] s: %s User not found. Please try another user.\n ",recv_data);
                authFlag =-1;
            }
            else{
                authFlag = -1;
            }
        }


    }

 }
}