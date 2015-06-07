//
//  serverEngine.c
//  Trabalho de SO
//
//  Created by Rafael Lopes Francisco on 30/05/15.
//  Copyright (c) 2015 Rafael Lopes Francisco. All rights reserved.
//

#include "serverEngine.h"

void startServer(){
    cliente *head = malloc(sizeof(cliente));
    head->next = NULL;
    pid_t pid_server = getpid();
    bool starting = true;
    
    int client_to_server;
    char *myfifo = "/tmp/client_to_server_fifo";
    
    int server_to_client;
    char *myfifo2 = "/tmp/server_to_client_fifo";
    
    unlink(myfifo);
    unlink(myfifo2);
    
    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);
    mkfifo(myfifo2, 0666);
    printf("FIFO's criados\n");
    
    //Threading - inutilizado por agora
    fork();
    pid_t child_ppid = getppid(); //get the child's parent pid
    
    if (child_ppid == pid_server) //if the current process is a child of the main process
    {
        
        exit(1); //making sure to avoid fork bomb
    }
    
    server_to_client = open(myfifo2, O_WRONLY);
    write(server_to_client, "Server ligado", sizeof("Server ligado"));
    printf("FIFO de saida criado\n");
    close(server_to_client);

    /* open, read, and display the message from the FIFO */
    client_to_server = open(myfifo, O_RDONLY);
    printf("FIFO's criados\n");
    
    do{
        pid_t pid_temp;
        dungeon *temp;
        
        read(client_to_server, &pid_temp, sizeof(pid_t));
        read(client_to_server, temp, sizeof(dungeon));
       
        addCliente(*head, pid_temp, temp);
    }while(starting);
}

void addCliente(cliente lista, int pid, dungeon *m){
    int server_to_client;
    char *myfifo2 = "/tmp/server_to_client_fifo";
    
    printf("A adiconar cliente com PID %d\n", pid);
    
    if (lista.next == NULL) {
        server_to_client = open(myfifo2, O_WRONLY);
        write(server_to_client, "1", sizeof("1"));
        close(server_to_client);
    }
    
    lista.next = malloc(sizeof(cliente));
    
    printf("Cliente adicionado !\n");
}