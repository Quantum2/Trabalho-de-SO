//
//  jogoPrincipal.c
//  Trabalho de SO
//
//  Created by Rafael Lopes Francisco on 12/05/15.
//  Copyright (c) 2015 Rafael Lopes Francisco. All rights reserved.
//

#include "jogoPrincipal.h"

void comecarJogo(){
    char nome[256];
    sala *salas;
    
    salas = carregarDados();
    
    printf("Nome do jogador ?\n");
    scanf("%s", nome);
    
    
}