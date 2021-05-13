#ifndef __STRUCTSGRAFICOS_H_
#define __STRUCTSGRAFICOS_H_

#include "raylib.h"
#include "definicoes.h"

typedef int BOOL;


typedef struct
{
        ///Sprites do corpo do personagem com armas
        int QTD_STATUS[QTD_ARMAS]; // QTD de status para cada arma
                                   //[1�] codigo da arma :    pistola 0 , smg 1 , faca de contato 2 , faca de arremesso 3

        int QTD_FRAMES[QTD_ARMAS][QTD_STATUS_MAX]; // QTD de iamgens disponiveis para status de cada arma
        //[1] codigo da arma :    pistola 0 , smg 1 , faca de contato 2 , faca de arremesso 3
        //[2] codigo do status :  repouso 0 , movimento 1 , atirando 2 , coronhada 3 , recarregando 4
        int atualFrame; //Frame atual do personagem

        ///Sprite dos pes do personagem
        int QTD_FRAMES_PES[QTD_STATUS_PES]; // Quantidade de frames para pes de cada status
        //[1] codigo do status :  repouso 0 , andando 1 , correndo 2 , lateralEsquerda 3 , lateralDireita 4
        int atualFramePes; //Frame atual dos pes

        ///
        Rectangle Src;    //Retangulo de extracao da textura com as dimensoes da mesma do personagem
        Rectangle SrcPes;
        Rectangle SrcT1;
        Vector2 Origin;   // O deslocamento entre a quina superior esquerda da textura PersonagemPrincipal e o centro de rotacao
        Vector2 OriginPes;
        Vector2 OriginT1;

        ///T1
        int QTD_FRAMES_T1[ QTD_STATUS_T1 ];
        int atualFrame_T1[ MAX_INI_TELA ];       //Para cada T1 na tela

        ///T0

} SpriteDef;

typedef struct
{
        ///Menus
        Texture2D MenuFundo;          // Imagem do plano de fundo principal
        Texture2D TelaDeFundo;        //Tela de fundo somente cores
        Texture2D FundoConfirmarSair; //Janela de fundo da confirmacao de saida
        Texture2D Logo;               // Imagem de fundo (Logo)
        Texture2D Bala;
        Texture2D Faca;
        Texture2D ItemMapa;     // Item dropada do level 1 para o 2
        Font fonteWolfen;             // Fonte Estilizada Wolfenstein
        Font fonteWolfen2;            // Fonte Estilizada Wolfenstein 2


        ///Mapa
        Texture2D Mapa; // Imagem do mapa

        ///Imagens do Personagem
        Texture2D Per[QTD_ARMAS][QTD_STATUS_MAX][100]; // Personagem [1�][2�][3�]
        //[1] codigo da arma atual:    pistola 0 , smg 1 , faca de contato 2 , faca de arremesso 3
        //[2] codigo do status atual:  repouso 0 , movimento 1 , atirando 2 , coronhada 3 , recarregando 4
        //[3] codigo do frame atual

        ///Imagens dos pes/pernas do personagem
        Texture2D Pes[QTD_STATUS_PES][100]; // Pernas e pes do Personagem [1�][2�]
        //[1] codigo do status atual:  repouso 0 , andando 1 , correndo 2 , lateralEsquerda 3 , lateralDireita 4
        //[2] codigo do frame atual

        ///T1
        Texture2D T1[ QTD_STATUS_T1][100]; // Pernas e pes do Personagem [1�][2�]
        //[1] codigo do status atual:  repouso 0 , andando 1 , correndo 2 , lateralEsquerda 3 , lateralDireita 4
        //[2] codigo do frame atual

        ///T2


        ///T0
        Texture2D T0;
        ///Objetos do JOGO
        Texture2D Portas;  // Imagem das portas
        Texture2D BauAberto;
        Texture2D BauFechado;

        Texture2D KitMed;
        Texture2D KitEnergia;
        Texture2D Municao;



} Recursos;

typedef struct{
        int codItem;        // Codigo do item
        Vector2 posMundo;       // Posicao no mapa
        BOOL recolhido;         // Se ja foi recolhido ou nao
} ITEM;

typedef struct
{
        Vector2 pos; // Posicao de desenho
        float rotac; // Angulo de rotacao

        int alteraPSala; // Sala de destino

        unsigned DESTRANCADA : 1; // Se esta destrancada == 1 , se nao == 0
} Porta;

///
typedef struct
{
        int tipo; // T0 , T1 , T2
        Vector2 posMundo;       // Posicao do centro do inimigo no mundo
        Rectangle recMundo;       // Area que inimigo ocupa no mundo
        Rectangle posTela;      // Posicao na tela
        float Rotac;

        int saude;      // Pontos de Saude
        BOOL atacando;
        int latenciaAtaque;

        int codItem; // Codigo do item que ira dropar
        int xpDrop;     // Qtd de pontos que ira liberar

        Color cor;
        BOOL dano;

        unsigned VIVO : 1;
} Inim;

typedef struct{
        float dist_manter[ 3 ];
        float vel[ 3 ];
        int saude[ 3 ];
        int xpDrop[ 3 ];     // Qtd de pontos que ira liberar
        int largMundo[ 3 ];
        int altMundo[ 3 ];


}infoTipoIni;

typedef struct
{
        Rectangle posMundo; // Posicao
        Rectangle posTela;
        float rotac; // Angulo de rotacao

        int tipo;       //Tipo de inimigo que spawna
        int inimigoTipo; // Tipo de inimigo que ele spawna
        unsigned ATIVO : 1; // Se esta ativo == 1 , se nao == 0
} Spawn;

typedef struct
{
        unsigned TERMINADO : 1; //O level foi terminado

} DadosLevel;

typedef struct
{
        Rectangle posMapa;            // Posicao no mapa geral
        Rectangle posTela;            // Posicao na tela se necessario
        Rectangle src;
        Vector2 origin;
        float Rotac;            // Angulo de rotacao

        int QtdItens;                    // A quantidade de itens que o bau fornecera. Por isso e a quantidade de elementos do array CodItens
        int CodItens[QTD_DROP_MAX_BAUS]; // Codigo definidos randomicamente na criacao do bau que estabelecerao os itens fornecidos

        Texture2D imagem;       // Texto do nome do arquivo imagem
        unsigned ABERTO : 1;
}Bau;

typedef struct
{
        Rectangle LimCam; // Limites de deslocamento da camera aerea na sala

        Rectangle zonas[QTD_ZONAS_MAX]; //Zonas da sala, por onde o jogador se locomove
        int qtdZonas;
        int qtdBaus; // Quantidade de baus
        Bau baus[MAX_BAUS_SALA];

        int qtdPortas; // Quantidade de portas iterativas para o jogador
        Porta portas[10];

        int qtdSpawns; //Quantidade de portas ou outro marco de onde brotam inimigos tipos 1
        Spawn spawns[10];

        int qtd_inimigos_liberados; // Quantidade de inimigos liberados
        int qtd_inimigos_liberar; // Quantidade de inimigos abatidos para se liberar porta_a_ser_liberada
        int qtd_abatidos;       // Inimigos ja abatidos
        int porta_a_ser_liberada;     // O numero da porta que sera destrancada depois de qtd_abatidos atingir qtd_inimigos_liberar

        int max_ativos; //Maximo de inimigos ativos na sala. A ser definido pela dificuldade do jogo
        Inim inimigos[ QTD_MAX_T1_SALA ];   // O array com os inimigos da sala
} Sala;
typedef struct
{
        int latencia;   // A latencia entre tiros


}ARMA;
typedef struct
{
        char *nome;

        Vector2 PosMundo;     //Posicionamento do jogador no mundo
        Rectangle PosTela;    //Posicionamento do jogador na tela
        Rectangle PosTelaPes; //Posicionamento do pes dp jogador na tela
        float Rotac;          //Rotacao

        Vector2 posMouse; // Posicao do mouse

        BOOL armasDisp[QTD_ARMAS]; //Se o jogador ja tem determinada arma
        int municao[QTD_ARMAS];    //A quantidade de municao de cada tipo de arma

        int pontos; //Pontuacao do jogador
        int saude;  //Pontos de saude.
        int vidas;  //Vidas gerais. Cada vez que saude zera perde uma vida.
        int energia;

        int atualArma;
        int atualStatus;
        int atualMovTipo;
        int atualLevel;

        int latencia;

        BOOL DANO;
        Color cor;

        int dificuldade;
        int probabilidadeDrop;          // Em percentagem
        /**   lembra de excluir    */ int testeFlagTiro; //excluir depois no final
} Jogador;

typedef struct
{
        Vector2 direcao; // x=cosseno  y= seno   do angulo
        Vector2 pos;
        Vector2 posTela;     // origem = jogador + distancia pra arma
        bool ativo;
        float Rotac; // mesma que jogador
        float speed;
        float nx;
        float ny;

} Tiro;



typedef struct
{

        Vector2 direcao; // x=cosseno  y= seno   do angulo
        Vector2 pos;
        Vector2 posTela; // origem = jogador + distancia pra arma
        Vector2 posInicial;
        Rectangle hitbox;
        bool ativo;
        float Rotac; // mesma que jogador
        float speed;
        float nx;
        float ny;
        float distancia;

        int flag_colisao;

        bool disponivel : 1;

} Faca;



typedef struct
{
        int NivelMenu; //Nivel atual do menu( 0->Principal , 1- Algum dos secundarios , 2->Menu interno do jogo , 3 - Jogando)
        unsigned FECHAR : 1;
        unsigned VOLTARMENU : 1;

        Rectangle tela;    //Resolucao da Tela do usuario
        int regulagemTela; //Se foi preciso deixar um espaco em cima 1 , nas laterais 2. Caso contrario 0

        Vector2 MapaTamanho;
        Rectangle MapaDesenho;
        Sala salas[QTDSALAS];

        unsigned PASSAGEM : 1; //Indica se esta atravessando alguma porta
        Jogador jogador;
        int atualSala;

        Tiro tirosJog[QTD_BALAS_RENDER];
        int qtd_tirosJog;
        Faca faca;


        //                DadosLevel dadosLevel;

        Recursos Res; //Recursos do jogo
        SpriteDef spriteDef;

        Vector2 escalaGeral;

        infoTipoIni infoIniT;

        int qtd_items_liberados;
        ITEM items[ MAX_ITENS_MUNDO ];   // Items do jogo

} JOGO;




//        typedef struct
//        {
//                float px;
//                float py;
//                float Rotac;
//                unsigned VIVO : 1;
//
//        }InimT2;
//
//        typedef struct
//        {
//                float px;
//                float py;
//        }Municao;

//         typedef struct
//        {
//                float px;
//                float py;
//        }Faca;
//

#endif // __STRUCTSGRAFICOS_H_

/*
                int KitMedicoP;  //Cura metade da saude
                int KitMedicoG;  //Cura saude completamente
                int vidaUp;  //Aumenta em 1 a quantidade de vidas
                int XP;
                int MunPistola;
                int MunEspingarda;


                                int saude;  // T2 comeca com 2 de pontos de saude
                int dropXP;  // Quantidade de Xp que o jogador ganha ao eliminar o inimigo
                int dropMun;  // Quantidade de municao que o jogador ganha ao eliminar o inimigo
                int dropMunTipo;  // Tipo de municao que o jogador ganha ao eliminar o inimigo

                                int qtdSpawnsT2;  //Quantidade de portas ou outro marco de onde brotam inimigos tipos 2
                int qtdInimT1;  // Quantidade de inimigos tipo 1 que precisarao ser abatidos para que algum inimigo drope uma uma chave
                int qtdInimT2;  // Quantidade de inimigos tipo 2 que precisarao ser abatidos para que algum inimigo drope uma uma chave



*/
/*
typedef struct //Um retangulo definido pelos limites
{
        float esq;
        float dir;
        float inf;
        float sup;
} RecLim;
*/
