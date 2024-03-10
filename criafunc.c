/* Vinicius Machado da Rocha Viana 2111343 3WA */
/* João Ricardo Malta de Oliveira 2112714 3WA */

#include <stdio.h>
#include <stdlib.h>
#include "cria_func.h"


void cria_func (void* f, DescParam params[], int n, unsigned char codigo[]){
  codigo[0] = 0x55;//pushq %rbp

  //movq %rsp, %rbp
  codigo[1] = 0x48;
  codigo[2] = 0x89;
  codigo[3] = 0xe5;

  //subq $32, %rsp
  codigo[4] = 0x48;
  codigo[5] = 0x83;
  codigo[6] = 0xec;
  codigo[7] = 0x20;

  //movq %rbx,-8(%rbp)
  codigo[8] = 0x48;
  codigo[9] = 0x89;
  codigo[10] = 0x5d;
  codigo[11] = 0xf8;

  //movq %r12,-16(%rbp)
  codigo[12] = 0x4c;
  codigo[13] = 0x89;
  codigo[14] = 0x65;
  codigo[15] = 0xf0;

  //movq %r13,-24(%rbp)
  codigo[16] = 0x4c;
  codigo[17] = 0x89;
  codigo[18] = 0x6d;
  codigo[19] = 0xe8;

  //movq %r14,-32(%rbp)
  codigo[20] = 0x4c;
  codigo[21] = 0x89;
  codigo[22] = 0x75;
  codigo[23] = 0xe0;


  int pos_atual = 24;//inteiro para saber em qual parte do vetor estamos escrevendo no código. Inicializei em 24 pois as 24 primeiras posições serão sempre iguais

  for (int i = 0; i < n; i++) {
    if (params[i].orig_val == PARAM) {
        if (i == 0) {
            // ...
        } else if (i == 1) {
            // ...
        } else if (i == 2) {
            // ...
        } else {
            printf("Erro! Número de parâmetro não está entre 1 e 3");
            exit(1);
        }
    } else if (params[i].orig_val == FIX) {
        if (i == 0) {
            codigo[pos_atual] = 0xbf; //movl em edi
            for (int j = 0; j < 4; ++j) {//passando os 4 bytes do valor inteiro para o registrador de parâmetro
                codigo[pos_atual] = (params[i].valor.v_int >> (j * 8)) & 0xFF;//mascara utilizada para pegar apenas os 8 bits significativos que queremos
                pos_atual++;
            }
            pos_atual++;
        } else if (i == 1) {
            codigo[pos_atual] = 0xbe; //movl em esi
            for (int j = 0; j < 4; ++j) {
                codigo[pos_atual] = (params[i].valor.v_int >> (j * 8)) & 0xFF;
                pos_atual++;
            }
            pos_atual++;
        } else if (i == 2) {
            codigo[pos_atual] = 0xba; //movl em edx
            for (int j = 0; j < 4; ++j) {
                codigo[pos_atual] = (params[i].valor.v_int >> (j * 8)) & 0xFF;
                pos_atual++;
            }
            pos_atual++;
        } else {
            printf("Erro! Número de parâmetro não está entre 1 e 3");
            exit(1);
        }
    } else if (params[i].orig_val == IND) {
        if (i == 0) {
            // ...
        } else if (i == 1) {
            // ...
        } else if (i == 2) {
            // ...
        } else {
            printf("Erro! Número de parâmetro não está entre 1 e 3");
            exit(1);
        }
    } else {
        printf("Erro! Origem de valor desconhecida. Encerrando o código\n");
        exit(1);
    }
}

  // Chamando a função
  codigo[pos_atual] = 0xe8; //call
  int deslocamento = (unsigned char*)&f - &(codigo[pos_atual+4]);//endereço de onde eu quero ir - endereço da próxima instrução. pulei 4 bytes pois é o espaço para chamar uma função que retorna inteiro
  codigo[pos_atual] = deslocamento;
  pos_atual++;
  codigo[pos_atual] = deslocamento >> 8;
  pos_atual++;
  codigo[pos_atual] = deslocamento >> 16;
  pos_atual++;
  codigo[pos_atual] = deslocamento >> 24;
  pos_atual++;

  //movq -8(%rbp),%rbx
  codigo[pos_atual] = 0x48;
  pos_atual++;
  codigo[pos_atual] = 0x8b;
  pos_atual++;
  codigo[pos_atual] = 0x5d;
  pos_atual++;
  codigo[pos_atual] = 0xf8;
  pos_atual++;

  //movq -16(%rbp),%r12
  codigo[pos_atual] = 0x4c;
  pos_atual++;
  codigo[pos_atual] = 0x8b;
  pos_atual++;
  codigo[pos_atual] = 0x65;
  pos_atual++;
  codigo[pos_atual] = 0xf0;
  pos_atual++;

  //movq -24(%rbp),%r13
  codigo[pos_atual] = 0x4c;
  pos_atual++;
  codigo[pos_atual] = 0x8b;
  pos_atual++;
  codigo[pos_atual] = 0x6d;
  pos_atual++;
  codigo[pos_atual] = 0xe8;
  pos_atual++;

  //movq -32(%rbp),%r14
  codigo[pos_atual] = 0x4c;
  pos_atual++;
  codigo[pos_atual] = 0x8b;
  pos_atual++;
  codigo[pos_atual] = 0x75;
  pos_atual++;
  codigo[pos_atual] = 0xe0;
  pos_atual++;

  // Encerrando o código
  codigo[pos_atual] = 0xc9;//leave
  pos_atual++;
  codigo[pos_atual] = 0xc3;//ret
}