#ifndef __STRUCTSGRAFICOS_H_
#define __STRUCTSGRAFICOS_H_

        #include "raylib.h"
        #include "definicoes.h"

        typedef int BOOL;
         typedef struct
         {
                float esq;
                float dir;
                float inf;
                float sup;
         }RecLim;


        typedef struct
        {
                 int QTD_STATUS[QTD_ARMAS] ;  // QTD de status para cada arma
                //[1°] codigo da arma :    pistola 0 , smg 1 , faca de contato 2 , faca de arremesso 3

                 int QTD_FRAMES[QTD_ARMAS][QTD_STATUS_MAX] ;  // QTD de iamgens disponiveis para status de cada arma
                //[1°] codigo da arma :    pistola 0 , smg 1 , faca de contato 2 , faca de arremesso 3
                //[2°] codigo do status :  repouso 0 , movimento 1 , atirando 2 , coronhada 3 , recarregando 4

        }ArmasDef;

        typedef struct
        {
                Texture2D MenuFundo;    // Imagem do plano de fundo principal
                Texture2D Logo;    // Imagem de fundo (Logo)
                Font fonteWolfen;  // Fonte Estilizada Wolfenstein
                Font fonteWolfen2;  // Fonte Estilizada Wolfenstein 2
                Texture2D TelaDeFundo;  //Tela de fundo somente cores
                Texture2D FundoConfirmarSair;  //Janela de fundo da confirmacao de saida
                Texture2D FundoLevel1;
                Texture2D Mapa;  // Imagem do mapa
                Texture2D Portas;  // Imagem das portas

                Texture2D Per[ QTD_ARMAS ][ QTD_STATUS_MAX ][100];  // Personagem [1°][2°][3°]
                //[1°] codigo da arma atual:    pistola 0 , smg 1 , faca de contato 2 , faca de arremesso 3
                //[2°] codigo do status atual:  repouso 0 , movimento 1 , atirando 2 , coronhada 3 , recarregando 4
                //[3°] codigo do frame atual

                Texture2D Pes[5][100];  // Pernas e pes do Personagem [1°][2°]
                //[1°] codigo do status atual:  repouso 0 , movimento 1 , correndo 2 , lateralEsquerda 3 , lateralDireita 4
                //[3°] codigo do frame atual

        }Recursos;


        typedef struct
        {
                int KitMedicoP;  //Cura metade da saude
                int KitMedicoG;  //Cura saude completamente
                int vidaUp;  //Aumenta em 1 a quantidade de vidas
                int XP;
                int MunPistola;
                int MunEspingarda;

                Vector2 pos;
                float Rotac;
                unsigned ABERTO : 1;
        }Bau;

        typedef struct
        {
                Vector2 pos;
                float rotac;
                unsigned DESTRANCADA : 1;
                Vector2 entrada;
                Vector2 destino;
                int alteraPSala;
        }Porta;

        typedef struct
        {
                unsigned TERMINADO; //O level foi terminado

        }DadosLevel;

        typedef struct
        {
                RecLim LimCam;  // Limites de deslocamento da camera aerea
                RecLim zonas[20];    //Zonas da sala, por onde o jogador se locomove
                int qtdZonas;

                int qtdBaus;  // Quantidade de baus
                Bau baus[ 3 ];

                int qtdPortas;  // Quantidade de portas iterativas para o jogador
                Porta portas[ 10 ];

                int qtdSpawnsT1;  //Quantidade de portas ou outro marco de onde brotam inimigos tipos 1
                int qtdSpawnsT2;  //Quantidade de portas ou outro marco de onde brotam inimigos tipos 2
                int qtdInimT1;  // Quantidade de inimigos tipo 1 que precisarao ser abatidos para que algum inimigo drope uma uma chave
                int qtdInimT2;  // Quantidade de inimigos tipo 2 que precisarao ser abatidos para que algum inimigo drope uma uma chave
        }Sala;

        typedef struct
        {
                char *nome;
                Rectangle PosTela;              //Posicionamento do jogador na tela
                Vector2 Origin;                 //Centro de rotacao na tela do personagem ?????porque nao funciona como o esperado?
                float Rotac;
                float mousex;
                float mousey;

                Rectangle Src;          //Retangulo de extracao da textura com as dimensoes da mesma

                Vector2 PosMundo;          //Posicionamento do jogador no mundo
                unsigned FACA : 1;
                unsigned PISTOLA : 1;
                unsigned SMG : 1;
                int PistolaMun;
                int RifleMun;
                int pontos;  //Pontuacao do jogador
                int vidas;  //Vidas gerais. Cada vez que saude zera perde uma vida.
                int saude;  //Pontos de saude. Quantidade a definir.
                int missaoCumprida;
                unsigned VIVO : 1;

                int atualArma;
                int atualStatus;
                int atualFrame;
        }Jogador;

        typedef struct
        {
                int NivelMenu;  //Nivel atual do menu( 0->Principal , 1- Algum dos secundarios , 2->Menu interno do jogo , 3 - Jogando)
                unsigned FECHAR : 1;
                unsigned VOLTARMENU : 1;
                Jogador jogador;

                DadosLevel dadosLevel;
                int Level;

                int atualSala;
                Sala salas[ QTDSALAS ];
                Rectangle tela;

                Vector2 MapaTamanho;
                Rectangle MapaDesenho;

                Recursos Res;  //Recursos do jogo

                unsigned PASSAGEM : 1;        //Indica se esta atravessando alguma porta
                ArmasDef armasDef;
        }Jogo;

        typedef struct  //Tipo um tem 1 ponto de saude
        {
                float px;
                float py;
                float Rotac;
                int dropXP;  // Quantidade de Xp que o jogador ganha ao eliminar o inimigo
                unsigned VIVO : 1;
        }InimT1;

        typedef struct
        {
                float px;
                float py;
                float Rotac;
                int saude;  // T2 comeca com 2 de pontos de saude
                int dropXP;  // Quantidade de Xp que o jogador ganha ao eliminar o inimigo
                int dropMun;  // Quantidade de municao que o jogador ganha ao eliminar o inimigo
                int dropMunTipo;  // Tipo de municao que o jogador ganha ao eliminar o inimigo
                unsigned VIVO : 1;

        }InimT2;

        typedef struct
        {
                float px;
                float py;
        }Municao;

         typedef struct
        {
                float px;
                float py;
        }Faca;



#endif // __STRUCTSGRAFICOS_H_
