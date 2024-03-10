/* Vinicius Machado da Rocha Viana 2111343 3WA */
/* João Ricardo Malta de Oliveira 2112714 3WA */

#include "cria_func.h"
#include <stdio.h>
#include <stdlib.h>

void cria_func(void *f, DescParam params[], int n, unsigned char codigo[]) {
  codigo[0] = 0x55; // pushq %rbp

  // movq %rsp, %rbp
  codigo[1] = 0x48;
  codigo[2] = 0x89;
  codigo[3] = 0xe5;

  // subq $32, %rsp
  codigo[4] = 0x48;
  codigo[5] = 0x83;
  codigo[6] = 0xec;
  codigo[7] = 0x20;

  // movq %rbx,-8(%rbp)
  codigo[8] = 0x48;
  codigo[9] = 0x89;
  codigo[10] = 0x5d;
  codigo[11] = 0xf8;

  // movq %r12,-16(%rbp)
  codigo[12] = 0x4c;
  codigo[13] = 0x89;
  codigo[14] = 0x65;
  codigo[15] = 0xf0;

  // movq %r13,-24(%rbp)
  codigo[16] = 0x4c;
  codigo[17] = 0x89;
  codigo[18] = 0x6d;
  codigo[19] = 0xe8;

  // movq %r14,-32(%rbp)
  codigo[20] = 0x4c;
  codigo[21] = 0x89;
  codigo[22] = 0x75;
  codigo[23] = 0xe0;

  int pos_atual = 24; // inteiro para saber em qual parte do vetor estamos
                      // escrevendo no código. Inicializei em 24 pois as 24
                      // primeiras posições serão sempre iguais

  // Tratando de parâmetros

  // Salvando os parâmetros recebidos em registradores
  for (int i = 0; i < n; i++) {
    if (params[i].orig_val == PARAM) {

      for (int j = 0; j < n; j++) {
        if (j == 0){ // movq %rdi, %rbx
          codigo[pos_atual] = 0x48;
        pos_atual++;
        codigo[pos_atual] = 0x89;
        pos_atual++;
        codigo[pos_atual] = 0xfb;
        pos_atual++;
        }

        if (j == 1){ // movq %rsi, %r12
          codigo[pos_atual] = 0x49;
        pos_atual++;
        codigo[pos_atual] = 0x89;
        pos_atual++;
        codigo[pos_atual] = 0xf4;
        pos_atual++;
        }

        if (j == 2){ // movq %rdx, %r13
          codigo[pos_atual] = 0x49;
        pos_atual++;
        codigo[pos_atual] = 0x89;
        pos_atual++;
        codigo[pos_atual] = 0xd5;
        pos_atual++;
      }
      }
    }
  }

  int npar = 0;//Quantos parâmetros já foram transferidos

  // Criando a função
  for (int i = 0; i < n; i++) {
    // // Se for PARAM, passar o valor do parâmetro recebido para a função
    // original
    if (params[i].orig_val == PARAM) {
      if (params[i].tipo_val == INT_PAR) {
        // caso onde era para estar em esi
        if (i == 1 && npar == 0) { // movl %ebx, %esi
          codigo[pos_atual] = 0x89; 
          pos_atual++;
          codigo[pos_atual] = 0xde;
          pos_atual++;

        }
        // caso onde era para estar em edx
        else if (i == 2 && npar == 0) { // movl %ebx, %edx
          codigo[pos_atual] = 0x89;
          pos_atual++;
          codigo[pos_atual] = 0xda;
          pos_atual++;
        }
        // caso onde era para estar em edx
        else if (i == 2 && npar == 1) { // movl %r12d, %edx
          codigo[pos_atual] = 0x44; 
          pos_atual++;
          codigo[pos_atual] = 0x89;
          pos_atual++;
          codigo[pos_atual] = 0xe2;
          pos_atual++;
        }
        npar++;
      } else if (params[i].tipo_val == PTR_PAR) {
        // caso onde era para estar em rsi
        if (i == 1 && npar == 0) { // movq %rbx, %rsi
          codigo[pos_atual] = 0x48; 
          pos_atual++;
          codigo[pos_atual] = 0x89;
          pos_atual++;
          codigo[pos_atual] = 0xde;
          pos_atual++;
        }
        // caso onde era para estar em rdx
        else if (i == 2 && npar == 0) { // movq %rbx, %rdx
          codigo[pos_atual] = 0x48; 
          pos_atual++;
          codigo[pos_atual] = 0x89;
          pos_atual++;
          codigo[pos_atual] = 0xda;
          pos_atual++;
        }
        // caso onde era para estar em rdx
        else if (i == 2 && npar == 1) { // movq %r12, %rdx
          codigo[pos_atual] = 0x4c; 
          pos_atual++;
          codigo[pos_atual] = 0x89;
          pos_atual++;
          codigo[pos_atual] = 0xe2;
          pos_atual++;
        }
        npar++;
      } else {
        printf("Erro! Tipo de parâmetro não é válido!");
        exit(1);
      }
    } 
    else if (params[i].orig_val == FIX) {
      if (params[i].tipo_val == INT_PAR) {
        if (i == 0) {
          codigo[pos_atual] = 0xbf; // movl em edi
          pos_atual++;
          for (int j = 0; j < 4; ++j) { // passando os 4 bytes do valor inteiro
                                        // para o registrador de parâmetro
            codigo[pos_atual] = (params[i].valor.v_int >> (j * 8)) &
                                0xFF; // mascara utilizada para pegar apenas os
                                      // 8 bits significativos que queremos
            pos_atual++;
          }
          // pos_atual++;
        } else if (i == 1) {
          codigo[pos_atual] = 0xbe; // movl em esi
          pos_atual++;
          for (int j = 0; j < 4; ++j) {
            codigo[pos_atual] = (params[i].valor.v_int >> (j * 8)) & 0xFF;
            pos_atual++;
          }

        } else if (i == 2) {
          codigo[pos_atual] = 0xba; // movl em edx
          pos_atual++;
          for (int j = 0; j < 4; ++j) {
            codigo[pos_atual] = (params[i].valor.v_int >> (j * 8)) & 0xFF;
            pos_atual++;
          }

        } else {
          printf("Erro! Número de parâmetro não está entre 1 e 3");
          exit(1);
        }
      } 
      else if (params[i].tipo_val == PTR_PAR) {
        long int aux = (long int)params[i].valor.v_ptr;
        // Dando movq para os parâmetros
        codigo[pos_atual] = 0x48;
        pos_atual++;
        // Passando para o registrador certo
        if (i == 0) {
          codigo[pos_atual] = 0xbf; //%rdi
          pos_atual++;
        } else if (i == 1) {
          codigo[pos_atual] = 0xbe; //%rsi
          pos_atual++;
        } else if (i == 2) {
          codigo[pos_atual] = 0xba; //%rdx
          pos_atual++;
        } else {
          printf("Erro! Número de parâmetro não está entre 1 e 3");
          exit(1);
        }

        for (int k = 0; k < 8; k++) {
          codigo[pos_atual] = (aux >> (k * 8)) & 0xFF;
          pos_atual++;
        }

      } 
      else {
        printf("Erro! Tipo de parâmetro não é válido!");
      }
    } 
    else if (params[i].orig_val == IND) {

      long int aux =
          (long)params[i]
              .valor.v_ptr; // transformando em Long para ter 8 bytes, assim
                            // mesmo se for um número inteiro, eu posso utilizar
                            // o mesmo código que para ponteiro
      // Dando movq para %rax
      codigo[pos_atual] = 0x48;
      pos_atual++;
      codigo[pos_atual] = 0xb8;
      pos_atual++;

      // Passando o conteúdo para o registrador o endereço
      for (int k = 0; k < 8; k++) {
        codigo[pos_atual] = (aux >> (k * 8)) & 0xFF;
        pos_atual++;
      }

      // Passando o conteúdo do endereço para o registrador
      if (params[i].tipo_val == INT_PAR) {

        codigo[pos_atual] = 0x8b;
        pos_atual++;
        if (i == 0) { // passando para %rdi
          codigo[pos_atual] = 0x38;
          pos_atual++;
        } else if (i == 1) { // passando para %rsi
          codigo[pos_atual] = 0x30;
          pos_atual++;
        } else if (i == 2) { // passando para %rdx
          codigo[pos_atual] = 0x10;
          pos_atual++;
        } else {
          printf("Erro! Número de parâmetro não está entre 1 e 3");
          exit(1);
        }

      } else if (params[i].tipo_val == PTR_PAR) {

        codigo[pos_atual] = 0x48;
        pos_atual++;
        codigo[pos_atual] = 0x8b;
        pos_atual++;
        if (i == 0) { // passando para %rdi
          codigo[pos_atual] = 0x38;
          pos_atual++;
        } else if (i == 1) { // passando para %rsi
          codigo[pos_atual] = 0x30;
          pos_atual++;
        } else if (i == 2) { // passando para %rdx
          codigo[pos_atual] = 0x10;
          pos_atual++;
        } else {
          printf("Erro! Número de parâmetro não está entre 1 e 3");
          exit(1);
        }
      } else {
        printf("Erro! Tipo de parâmetro não é válido");
        exit(1);
      }
    } 
    else {
      printf("Erro! Origem de valor desconhecida. Encerrando o código\n");
      exit(1);
    }
  }
  // Movendo o parâmetro da função para um registrador
  long int k = (long int)f;
  // Movq para %rax
  codigo[pos_atual] = 0x48;
  pos_atual++;
  codigo[pos_atual] = 0xb8;
  pos_atual++;
  // Passando os bytes da função para o registrador
  for (int j = 0; j < 8; j++) {
    codigo[pos_atual] = (k >> j * 8) & 0xff;
    pos_atual++;
  }
  codigo[pos_atual] = 0xff; // callq *%rax
  pos_atual++;
  codigo[pos_atual] = 0xd0;
  pos_atual++;

  // movq -8(%rbp),%rbx
  codigo[pos_atual] = 0x48;
  pos_atual++;
  codigo[pos_atual] = 0x8b;
  pos_atual++;
  codigo[pos_atual] = 0x5d;
  pos_atual++;
  codigo[pos_atual] = 0xf8;
  pos_atual++;

  // movq -16(%rbp),%r12
  codigo[pos_atual] = 0x4c;
  pos_atual++;
  codigo[pos_atual] = 0x8b;
  pos_atual++;
  codigo[pos_atual] = 0x65;
  pos_atual++;
  codigo[pos_atual] = 0xf0;
  pos_atual++;

  // movq -24(%rbp),%r13
  codigo[pos_atual] = 0x4c;
  pos_atual++;
  codigo[pos_atual] = 0x8b;
  pos_atual++;
  codigo[pos_atual] = 0x6d;
  pos_atual++;
  codigo[pos_atual] = 0xe8;
  pos_atual++;

  // movq -32(%rbp),%r14
  codigo[pos_atual] = 0x4c;
  pos_atual++;
  codigo[pos_atual] = 0x8b;
  pos_atual++;
  codigo[pos_atual] = 0x75;
  pos_atual++;
  codigo[pos_atual] = 0xe0;
  pos_atual++;

  // Encerrando o código
  codigo[pos_atual] = 0xc9; // leave
  pos_atual++;
  codigo[pos_atual] = 0xc3; // ret
}