#ifndef __DEFINICOES_H_
#define __DEFINICOES_H_

        #include <math.h>
        #include <stdio.h>
        #include <time.h>
        #include <stdlib.h>

        ///MENU's
        #define ITENS_MAIN_MENU 7
        #define ITENS_NOVO_JOGO 5

        ///BOOL
        #define SIM 1
        #define NAO 0

        ///LEVEL's
        #define MAXLEVEL 3

        ///FPS
        #define FPS 50
        #define DIV_FPS_PER 2

        ///TELA
        #define REF_TELA_LARG 1366
        #define REF_TELA_ALT 768

        ///JOGADOR
        #define LARG_PADRAO 130
        #define ALT_PADRAO 115
        #define RAZAO_SOLID_JOGADOR 10


        ///EXIT
        #define EXITKEY KEY_BACKSLASH
        //#define EXITKEY KEY_ESCAPE

        ///MOVIMENTO DO JOGADOR
        #define PASSO 2
        #define PASSO_CORRENDO 2.4
        #define TOL_MOV_LATERAL 20      //Angulo de tolerancia para se considerar o movimento do jogador perpendicular aa mira ( lateral )

        ///MAPA
        #define PIXEL_LARGURA_MAPA 304
        #define PIXEL_ALTURA_MAPA 171
        #define ESCALA 4.5

        ///SALAS
        #define QTDSALAS 16
        #define QTD_ZONAS_MAX 10
        #define QTD_SALAS_SPAWN 9
        #define MAX_SPAWN_SALAS 10

        ///SPAWNS
        #define LARG_MUNDO_SPAWN 50
        #define ALT_MUNDO_SPAWN 30
        #define DELAY_SPAWN 100

        ///INIMIGOS
        #define QTD_MAX_T1_SALA 50
        #define PASSOT1 .7*PASSO
        #define CONSTANTE_ANITFLICK 5

        ///ARMAS
//        #define QTD_ARMAS 5
        #define QTD_ARMAS 1
        #define QTD_STATUS_MAX 7
        #define DESVIO_MIRA 5
        #define QTD_BALAS_RENDER 20

        ///PERSONAGEM PRINCIPAL - JOGADOR
        #define ESC_PER 1
        #define ESC_PES 2.1/3
        #define QTD_STATUS_PES 5
        #define DELTA_PES 50

        ///BAUS
        #define QTD_DROP_MAX_BAUS 3             //Quantidade maxima de itens que os baus podem chegar a dropar( fornecer )
        #define MAX_BAUS_SALA 8
        #define BAU_LARGURA 31
        #define BAU_COMPRIMENTO 21

        ///PORTAS
        #define TOL_ENTRAR_PORTAS 10
        #define SALTO_PORTA 105


#endif // __DEFINICOES_H_
