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
    head->quantidade_clientes = 0;
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
    
    do{
        pid_t pid_temp;
        dungeon temp;
        
        server_to_client = open(myfifo2, O_WRONLY);
        
        write(server_to_client, "Server ligado", sizeof("Server ligado"));
        close(server_to_client);
        
        client_to_server = open(myfifo, O_RDONLY);
        
        read(client_to_server, &pid_temp, sizeof(pid_t));
        close(client_to_server);
        
        client_to_server = open(myfifo, O_RDONLY);
        read(client_to_server, &temp, sizeof(dungeon));
        
        close(client_to_server);
       
        addCliente(head, pid_temp, temp);
        
        //Reset aos pipes
        unlink(myfifo);
        unlink(myfifo2);
        mkfifo(myfifo, 0666);
        mkfifo(myfifo2, 0666);
    }while(starting);
}

void addCliente(cliente *lista, int pid, dungeon mas){
    int server_to_client;
    char *myfifo2 = "/tmp/server_to_client_fifo";
    
    printf("A adiconar cliente com PID %d\n", pid);
    server_to_client = open(myfifo2, O_WRONLY);
    write(server_to_client, "Conectado ao servidor", sizeof("Conectado ao servidor"));
    close(server_to_client);
    
    server_to_client = open(myfifo2, O_WRONLY);
    if (lista->quantidade_clientes == 0) {
        write(server_to_client, "1", sizeof("1"));
        lista->quantidade_clientes++;
    }
    else{
        write(server_to_client, "0", sizeof("0"));
        lista->quantidade_clientes++;
    }
    close(server_to_client);
    
    while (lista->next != NULL) {
        lista = lista->next;
    }
    
    lista->ID = lista->quantidade_clientes;
    lista->masmorra = mas;
    lista->next = malloc(sizeof(cliente));
    lista->next = NULL;
    
    printf("Cliente adicionado !\n");
}