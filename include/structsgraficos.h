#ifndef __STRUCTSGRAFICOS_H_
#define __STRUCTSGRAFICOS_H_

        #include "raylib.h"

        typedef struct
        {
                Texture2D MenuFundo;    // Imagem do plano de fundo principal
                Texture2D Logo;    // Imagem de fundo (Logo)
                Font fonteWolfen;  // Fonte Estilizada Wolfenstein
                Font fonteWolfen2;  // Fonte Estilizada Wolfenstein 2
                Texture2D TelaDeFundo;  //Tela de fundo somente cores
                Texture2D FundoConfirmarSair;  //Janela de fundo da confirmação de saída
                Texture2D FundoLevel1;
                Texture2D Mapa;  // Imagem do mapa
                Texture2D Portas;  // Imagem das portas

        }Recursos;


        typedef struct
        {
                int KitMedicoP;  //Cura metade da saúde
                int KitMedicoG;  //Cura saúde completamente
                int vidaUp;  //Aumenta em 1 a quantidade de vidas
                int XP;
                int MunPistola;
                int MunRifle;
                int MunEspingarda;
                int MunGranada;

                Vector2 pos;
                float Rotac;
                unsigned ABERTO : 1;
        }Bau;

        typedef struct
        {
                Vector2 pos;
                float rotac;
                unsigned DESTRANCADA : 1;
        }Porta;

        typedef struct
        {
                unsigned TERMINADO; //O level foi terminado

        }DadosLevel;

        typedef struct
        {
                float limEsq;  // Limites de deslocamento da câmera aérea
                float limDir;
                float limInf;
                float limSup;

                int qtdBaus;  // Quantidade de baus
                Bau baus[ 3 ];

                int qtdPortas;  // Quantidade de portas iterativas para o jogador
                Porta portas[ 10 ];

                int qtdSpawnsT1;  //Quantidade de portas ou outro marco de onde brotam inimigos tipos 1
                int qtdSpawnsT2;  //Quantidade de portas ou outro marco de onde brotam inimigos tipos 2
                int qtdInimT1;  // Quantidade de inimigos tipo 1 que precisarão ser abatidos para que algum inimigo drope uma uma chave
                int qtdInimT2;  // Quantidade de inimigos tipo 2 que precisarão ser abatidos para que algum inimigo drope uma uma chave
        }Sala;

        typedef int BOOL;

        typedef struct
        {
                char *nome;
                float px;  //Posição x na tela
                float XMapa;  // Posição x no mapa
                float py;
                float YMapa;
                float Rotac;
                float mousex;
                float mousey;
                unsigned FACA : 1;
                unsigned PISTOLA : 1;
                unsigned RIFLE : 1;
                unsigned ESPINGARDA : 1;
                unsigned GRANADA : 1;
                int PistolaMun;
                int RifleMun;
                int EspingardaMun;
                int GranadaMun;
                int pontos;  //Pontuação do jogador
                int vidas;  //Vidas gerais. Cada vez que saude zera perde uma vida.
                int saude;  //Pontos de saúde. Quantidade a definir.
                int missaoCumprida;
                unsigned VIVO : 1;
        }Jogador;

        typedef struct
        {
                Recursos Res;  //Recursos do jogo
                int NivelMenu;  //Nível atual do menu( 0->Principal , 1- Algum dos secundários , 2->Menu interno do jogo , 3 - Jogando)
                unsigned FECHAR : 1;
                unsigned VOLTARMENU : 1;
                Jogador jogador;

                DadosLevel dadosLevel;
                int Level;
                int atualSala;
                Sala salas[ 12 ];
                Rectangle tela;
        }Jogo;

        typedef struct  //Tipo um tem 1 ponto de saúde
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
                int saude;  // T2 começa com 2 de pontos de saúde
                int dropXP;  // Quantidade de Xp que o jogador ganha ao eliminar o inimigo
                int dropMun;  // Quantidade de munição que o jogador ganha ao eliminar o inimigo
                int dropMunTipo;  // Tipo de munição que o jogador ganha ao eliminar o inimigo
                unsigned VIVO : 1;

        }InimT2;

#endif // __STRUCTSGRAFICOS_H_
