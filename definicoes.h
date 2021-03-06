#ifndef __DEFINICOES_H_
#define __DEFINICOES_H_

        #include <math.h>
        #include <stdio.h>
        #include <time.h>
        #include <stdlib.h>

        ///MENU's
        #define ITENS_MAIN_MENU 7
        #define ITENS_NOVO_JOGO 5
        #define TEMPO_CARREGAR_LOGO 50

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
        #define DELAY_DANO 10

        #define SAUDE_TOTAL_JOGADOR 15
        #define VIDAS_INICIAIS_JOGADOR 3


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

        ///Inimigos
        #define MULTI_PASSO_SEGURO 3
        #define MAX_INI_TELA 50

        ///INIMIGOS T1
        #define QTD_MAX_T1_SALA 50
        #define PASSO_T1 0.65*PASSO
        #define CONSTANTE_ANITFLICK 5


        #define SRC_LQ_T1_0 600      // Tamanho do lado em pixels do quadrado de extracao da imagem original
        #define SRC_X_T1_0 0      // X
        #define SRC_Y_T1_0 0      // Y


        #define MAPA_LQ_T1 550      // Tamanho do lado em pixels do quadrado de destino no mapa

        #define QTD_STATUS_T1 2

        #define DIV_FPS_T1 2

        #define DIST_MANTER 30
        #define DIST_INICIAR_ATAQUE_T1 80
        #define DIST_EFETIVAR_ATAQUE_T1 55
        #define LATENCIA_T1 FPS*2

        ///Inimigos T0
        #define PASSO_T0  1*PASSO


        #define SRC_LQ_T0 600      // Tamanho do lado em pixels do quadrado de extracao da imagem original


        #define MAPA_LQ_T0 100      // Tamanho do lado em pixels do quadrado de destino no mapa

        #define QTD_STATUS_T0 2

        #define DIV_FPS_T1 2

        #define DIST_MANTER 30
        #define DIST_INICIAR_ATAQUE_T0 80
        #define DIST_EFETIVAR_ATAQUE_T0 13
        #define LATENCIA_T0 FPS*2

        ///ARMAS
//        #define QTD_ARMAS 5
        #define QTD_ARMAS 1
        #define QTD_STATUS_MAX 7
        #define DESVIO_MIRA 5
        #define QTD_BALAS_RENDER 100

        ///PERSONAGEM PRINCIPAL - JOGADOR
        #define ESC_PER 1
        #define ESC_PES 2.1/3
        #define QTD_STATUS_PES 5
        #define DELTA_PES 50

        ///BAUS
        #define DIST_ABRIR_BAUS 15
        #define QTD_DROP_MAX_BAUS 3             //Quantidade maxima de itens que os baus podem chegar a dropar( fornecer )
        #define MAX_BAUS_SALA 8
        #define BAU_LARGURA 31
        #define BAU_COMPRIMENTO 21
        #define DIST_DROP 7
        #define DELTA_DIST_DROP 4

        ///PORTAS
        #define TOL_ENTRAR_PORTAS 10
        #define SALTO_PORTA 105
        #define LARG_PORTAS 105
        #define ALT_PORTAS 90

        ///RASTREAMENTO DE ALVO
        #define PASSO_RASTREAMENTO 2

        ///ITEMS
        #define MAX_ITENS_MUNDO 300
        #define TIPOS_ITEMS 3
        #define DIST_COLETAR_ITEMS 5
        #define QTD_MUNICAO_DROP  18

        ///ENERGIA
        #define ENERGIA_TOTAL 200

        ///PAUSE
        #define DELAY_PAUSE 20000

        /// HUD
        #define HUD_LARG 496
        #define HUD_ALT 158
        #define X_0_ATRIB 164
        #define Y_0_ATRIB_SAUDE 45
        #define Y_0_ATRIB_ENERGIA 80
        #define LARG_RET_ATRIB 331
        #define ALT_RET_ATRIB 33
        #define X_CORAC 173
        #define Y_CORAC 47
        #define LARG_CORAC 35
        #define ALT_CORAC 27

        #define X_ENERG 176
        #define Y_ENERG 82
        #define LARG_ENERG 30
        #define ALT_ENERG 30

        #define XP_X  430
        #define XP_Y 23
        #define XP_FONT_S 20

        #define LEVEL_X  463
        #define LEVEL_Y 2
        #define LEVEL_FONT_S 20

        #define MUN_X  250
        #define MUN_Y 119
        #define MUN_FONT_S 25

        #define X_FACA 347
        #define Y_FACA 121
        #define LARG_FACA 65
        #define ALT_FACA 22

        #define X_REC_FACA 345
        #define Y_REC_FACA 116
        #define LARG_REC_FACA 69
        #define ALT_REC_FACA 31

        #define NOME_X  170
        #define NOME_Y 6
        #define NOME_FONT_S 30

        #define VIDAS_X  11
        #define VIDAS_Y 129
        #define VIDAS_FONT_S 25

        /// REFENS
        #define QTD_REFENS 15

        /// MODO HORDA
        #define SALA_HORDA 10
        #define INIMIGOS_META 49
        #define TEMPO_CALMARIA 3 * FPS

#endif // __DEFINICOES_H_
