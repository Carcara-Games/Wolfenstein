/**     WOLFENSTEIN
    *     Autores: Manoel Narciso Filho e Matheus De Moraes Costa
    *     Última Modificação: 09/04/2021 16:36
    *
    */

#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ITENS_MAIN_MENU 7
#define ITENS_NOVO_JOGO 5
#define SIM 1
#define NAO 0
#define MAXLEVEL 3

typedef struct
{
        Texture2D MenuFundo;    // Imagem do plano de fundo principal
        Texture2D Logo;    // Imagem de fundo (Logo)
        Font fonteWolfen;  // Fonte Estilizada Wolfenstein
        Font fonteWolfen2;  // Fonte Estilizada Wolfenstein
        Texture2D TelaDeFundo;  //Tela de fundo somente cores
        Texture2D FundoConfirmarSair;  //Janela de fundo da confirmação de saída

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
        float px;
        float py;
        int Rotac;  //0 -> Horizontal frente para baixo , 1-> Vertical frente direita , 2 -> Hor. frente para cima, 4 -> Vert. frente para esquerda
        unsigned ABERTO : 1;
}Bau;

typedef struct
{
        int AlturaTotal;
        int LarguraTotal;
        int qtdBaus;  // Quantidade de baus
        int qtdPortas;  // Quantidade de portas iterativas par o jogador
        int qtdSpawnsT1;  //Quantidade de portas ou outro marco de onde brotam inimigos tipos 1
        int qtdSpawnsT2;  //Quantidade de portas ou outro marco de onde brotam inimigos tipos 2
        int qtdInimT1;  // Quantidade de inimigos tipo 1
        int qtdInimT2;  // Quantidade de inimigos tipo 2
        Bau *baus;
        unsigned TERMINADO; //O level foi terminado

}DadosLevel;

typedef int BOOL;

typedef struct
{
        char *nome;
        float px;
        float py;
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
}Jogo;

#define QTD_MAX_INI_T1 15
typedef struct  //Tipo um tem 1 ponto de saúde
{
        float px;
        float py;
        float Rotac;
        int dropXP;  // Quantidade de Xp que o jogador ganha ao eliminar o inimigo
        unsigned VIVO : 1;

}InimT1;

#define QTD_MAX_INI_T2 5
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


///Protótipos
void IniciarJanela( void );
Jogo IniciaJogo( void );

void MovimentoMenu( int *selecao , int qtd_opcoes );
int CentraTextoX( char *texto , int fontsize );
int CentraTextoXEX( Font fonte , char *texto , float fontsize , float space);

void AtualizaMenu( int* selecao , int qtd_opcoes );
void AtualizaConfirmarSair( int *selecao );
void NomeWolfenEntrada( Jogo *jogo , int selecao  );
void DesenhaMenuPrincipal(Jogo *jogo, int selecao);
void DesenhaMenuDificuldade( Jogo *jogo , int selecao );
void DesenharConfirmarSair( int selecao , Jogo *jogo );
void DesenharObrigado( void );

void DesenhaSobre( Jogo jogo);

char *ItensMenuPrincipal(int escolha);
char *ItensMenuDificuldade( int escolha );

BOOL IsGameOver( Jogo jogo );
BOOL IsEndGame( Jogo jogo );
BOOL IsVoltarMenu( Jogo jogo );
BOOL IsLevelEnd( Jogo jogo );

void CarregarLevel( Jogo *jogo);
void AtualizaLevel( Jogo *jogo);
void DesenhaLevel( Jogo jogo);

///MAIN
int main()
{
        IniciarJanela();  //Configura as opções da janela

        Jogo jogo = IniciaJogo();  // Carrega recursos do jogo

        int selecaoMenu = 0;

        while( !((IsKeyPressed( KEY_ENTER ) && selecaoMenu == ITENS_MAIN_MENU - 1 ) || WindowShouldClose() || jogo.FECHAR ) )
        {
                DesenhaMenuPrincipal(&jogo, selecaoMenu);   // Desenha menu principal
                AtualizaMenu( &selecaoMenu , 7 );   // Retorna opção que jogador apertou enter. 7 é o número de opções do menu principal

                if (IsKeyPressed(KEY_ENTER))
                {
                        jogo.NivelMenu = 1;
                        switch( selecaoMenu )   // Escolhe ação dependendo opção escolhida no menu principal
                        {

                                case 0:   //Novo Jogo ---------------------------------------------------------------------------------------------------------------------------------------------------
                                        do
                                        {
                                                DesenhaMenuDificuldade( &jogo , selecaoMenu );   // Desenha Menu secundário para escolher dificuldade
                                                AtualizaMenu( &selecaoMenu , ITENS_NOVO_JOGO );   //Atualiza Menu secundário Novo jogo

                                                if( selecaoMenu != ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER )  )
                                                {
                //                                      CriarNovoJogador();   //  Definir nome do jogador
                                                        while( !IsGameOver( jogo ) && !IsEndGame( jogo ) ) //Continua avançando de level a menos que usuário receba game over, zere o jogo ou volte para o menu
                                                        {
                                                                CarregarLevel( &jogo ); //Carrega as fases em sequência. Se Jogador recebe game over, zera ou pede para voltar para o menu ativa as respectivas flags
                                                                while( !IsLevelEnd( jogo )  &&  !IsVoltarMenu( jogo ) )
                                                                {
                                                                        AtualizaLevel( &jogo );
                                                                        DesenhaLevel( jogo );
                                                                }
                                                                jogo.Level++;
                                                        }

                                                }

                                        }
                                        while( !(selecaoMenu == ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER ) ) );

                                        break;

                                case 1:    //Continuar ------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                ListaJogadoresSalvos();  //Menu secundário que apresenta jogadores salvos ( cada jogador criado só pode manter um savegame para não virar uma zona)
                                        break;


                                case 2:    //Modo Horda ---------------------------------------------------------------------------------------------------------------------------------------------------
        //                                IniciarModoHorda();   //Inicia modo horda. Dificuldade única
                                        break;

                                case 3:    //Configurar ------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                AbreConfiguracoes();   //Menu secundário de configurações
                                        //Só um teste
                                        while( !IsKeyPressed( KEY_A ) )
                                        {

                                                BeginDrawing();
                                                        ClearBackground( WHITE );
                                                        DrawRectangle( 100 , 400 , 70 , 30 , RED);
                                                        DrawTriangle( (Vector2 ){ 100 , 100} , (Vector2 ){ 500 , 100} , (Vector2 ){ 400 , 400} , GREEN);
                                                EndDrawing();
                                        }
                                        break;

                                case 4:    //Ajuda ------------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                ApresentaAjuda();   // Ajudas e dicas gerais sobre o jogo e sobre os comandos

                                        break;

                                case 5:    //Sobre ------------------------------------------------------------------------------------------------------------------------------------------------------------
                                        do{
                                                DesenhaSobre( jogo );   //Apresenta autores e etc
                                        }while( !IsKeyPressed(KEY_ENTER) );

                                        break;

                                case 6:    //Sair ---------------------------------------------------------------------------------------------------------------------------------------------------
                                        selecaoMenu = 0;
                                        do
                                        {
                                                AtualizaConfirmarSair( &selecaoMenu );   //Janela de confirmação de saída
                                                DesenharConfirmarSair( selecaoMenu , &jogo);
                                                 jogo.FECHAR = selecaoMenu ? SIM : NAO;
                                        }while( !IsKeyPressed( KEY_ENTER ) );
                                        break;
                        }
                }

        }

        DesenharObrigado();
        CloseWindow();
        return 0;
}

/**      Funcao AtualizaMenuPrincipal() : Atualiza a seleção do menu principal
    *                   ->Entradas: Endereço da variável seleção e quantidade de opções do menu
    */
void AtualizaMenu(  int* selecao , int qtd_opcoes )
{

        if( IsKeyPressed( KEY_DOWN)  &&  *selecao < qtd_opcoes - 1  )
        {
                (*selecao)++;
                return;
        }

        if( IsKeyPressed( KEY_UP)  &&  *selecao > 0 )
        {
                (*selecao)--;
                return;
        }

}
//##############################################################################


#define COR_MENU_COMUM WHITE          // Cor do texto do menu nao selecionado
#define COR_MENU_SELECAO GOLD          // Cor do texto do menu selecionado

/** Funcao DesenhaMenuPrincipal() : Desenha o menu quando programa esta na parte inicial
    *
    */

void DesenhaMenuPrincipal(Jogo* jogo, int selecao) {
        int i;
        const int FONT_SIZE = 30;   // Tamanho da fonte do menu
        const int ALTURA_ITEM_0 = GetScreenWidth() / 4;   //Posicao Y do primeiro item menu
        const int VARIACAO_ALTURA = FONT_SIZE * 1.5;    // Variacao de altura entre cada item dado pelo tamanho da letra
        const int QTD_OPCOES = 7;     // Quantidade de opcoes no menu

        BeginDrawing();
        {
                // Fundo
                ClearBackground(WHITE);
                DrawTexture( jogo->Res.MenuFundo , ( GetScreenWidth() - jogo->Res.MenuFundo.width ) / 2 , ( GetScreenHeight() - jogo->Res.MenuFundo.height ) / 2 , WHITE);  //Plano de Fundo Customizado
                NomeWolfenEntrada( jogo , selecao );  //Nome Wolfenstein com efeito de entrada
                DrawTextureEx( jogo->Res.Logo , (Vector2 ){ 5 , 5 } , 0 ,  .2 , WHITE );  //Mini logo no canto superior esquerdo

                // Desenha todos os itens em cor comum
                for( i = 0 ; i < QTD_OPCOES ; i++)
                        DrawText( TextFormat( ItensMenuPrincipal( i ) )  , CentraTextoX( ItensMenuPrincipal( i ) , FONT_SIZE ) , ALTURA_ITEM_0 + i * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_COMUM  );

                // Desenha o item em foco em cor de selecao
                DrawText( TextFormat( ItensMenuPrincipal( selecao ) ) , CentraTextoX( ItensMenuPrincipal( selecao ) , FONT_SIZE ) , ALTURA_ITEM_0 + selecao * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_SELECAO  );
        }
        EndDrawing();
}
//##############################################################################



/**     Funcao ItensMenuPrincipal() :
     */
char *ItensMenuPrincipal(int escolha)
{
        static char opcao[ 7 ][ 30 ] =             {
                                                                                "Novo Jogo" ,  // 0       //Items do menu
                                                                                "Continuar" ,   // 1
                                                                                "Modo Horda" ,  // 2
                                                                                "Configurar" , // 3
                                                                                "Ajuda" ,    // 4
                                                                                "Sobre" ,   // 5
                                                                                "Sair"    // 6
                                                                        };

        return opcao[ escolha ];
}
//##############################################################################

/**     Funcao NomeWolfenEntrada() : Escreve Wolfenstein com efeito legal
    */

#define HWOLF 150    //Posicao Y na tela do nome Wolfenstein
#define FONT_SIZE_WOLF 130    // Tamanho na tela do nome Wolfenstein
#define MULT 5
#define ESP_WOLF 7

void NomeWolfenEntrada( Jogo *jogo , int selecao  )
{
        static int i = 0 , j = 10 * MULT;
        int k , f , L1 , L2;
        const char Nome[ 12 ] = "WOLFENSTEIN";
        char Escreva[ 12 ] = "           ";

        if( jogo->NivelMenu != 0  &&  selecao != ITENS_MAIN_MENU - 1  &&  selecao != ITENS_MAIN_MENU - 2 )  // Em SAIR e em SOBRE não renicia o efeito do nome
        {
                jogo->NivelMenu = 0;
                i = 0;
                j = 10 * MULT;
        }
        //Sobrescreve com nome certo de 0 até i e do final até j
        if( i <= j )
        {
                for( k = 0 , f = 11 * MULT ; k <= i &&  f >= j ; k++ , f-- )
                {
                        L1 = k / MULT;
                        L2 = ceil( f / MULT);

                        Escreva[ L1 ] = Nome[ L1 ];
                        Escreva[ L2 ] = Nome[ L2 ];
                }
                i++;
                j--;
        }
        else
                TextCopy( Escreva , Nome );

        DrawTextEx( jogo->Res.fonteWolfen ,  Escreva , (Vector2){ CentraTextoXEX( jogo->Res.fonteWolfen , Escreva , FONT_SIZE_WOLF , ESP_WOLF  )  ,  HWOLF / ( 27 - i ) }  , FONT_SIZE_WOLF , ESP_WOLF , WHITE );

}

//##############################################################################



/**     Funcao DesenhaWolfenstein() : Desenha o nome do jogo com a fonte certa
    *                   ->Entrada: Jogo
    */

void DesenhaWolfenstein( Jogo *jogo )
{

}

//##############################################################################



/**     Funcao IniciarJanela() : Inicia janela do jogo
    */

#define FPS 30
#define EXITKEY KEY_BACKSLASH
//#define EXITKEY KEY_ESCAPE

void IniciarJanela( void )
{
        int TelaLargura = GetMonitorWidth(0);
        int TelaAltura = GetMonitorHeight (0);

        InitWindow( TelaLargura , TelaAltura , "WOLFENSTEIN" );
        SetTargetFPS( FPS );
        ToggleFullscreen();
        SetExitKey( EXITKEY );
        DisableCursor();
}



///
Jogo IniciaJogo( void )
{
        Jogo jogo;

        jogo.Res.Logo =  LoadTexture("Logo/Logo.png");   // Imagem de fundo (Logo)
        jogo.Res.MenuFundo =  LoadTexture("Menu_Imagens/MenuPrincipal.png");   // Imagem do plano de fundo
        jogo.Res.TelaDeFundo =  LoadTexture("Menu_Imagens/FundoLimpo.png");
        jogo.Res.fonteWolfen =    LoadFontEx("Fontes/ReturnToCastle-MZnx.ttf"  ,96 , 0 , 0);
        jogo.Res.fonteWolfen2 =    LoadFontEx("Fontes/wolfenstein.ttf"  ,96 , 0 , 0);
        jogo.Res.FundoConfirmarSair =    LoadTexture("Menu_Imagens/FundoConfirmarSair.png");

        jogo.FECHAR = 0;

        return jogo;
}

/**     Funcao CentraTextoX() : Centraliza o texto em relacao à largura da tela
    *           -> Entradas: Endereço do texto e Tamanho da fonte.
    */

int CentraTextoX( char *texto , int fontsize )
{
        return ( GetScreenWidth() - MeasureText( texto , fontsize ) ) / 2 ;
}
//##############################################################################



/**     Funcao CentraTextoXEX() : Centraliza o texto em relação à largura da tela extendida
    *           -> Entradas: Tipo de fonte , Endereço do texto ,Tamanho da fonte e Espaçamento.
    */

int CentraTextoXEX( Font fonte , char *texto , float fontsize , float space)
{
        return ( GetScreenWidth() - MeasureTextEx( fonte , texto , fontsize , space ).x ) / 2 ;
}
//##############################################################################



/**     Funcao DesenhaMenuDificuldade() : Desenha o menu de escolha de dificuldade
    */
#define RECRUTA 0
#define SOLDADO 1
#define VETERANO 2
#define CHUCK_NORRIS 3
#define VOLTAR 4

void DesenhaMenuDificuldade( Jogo *jogo , int selecao )
{
        int i ;

        const int QTD_OPCOES = 5;     // Quantidade de opcoes no menu
        const int FONT_SIZE = 30;   // Tamanho da fonte
        const int FONT_SIZE_M1 = 50;   // Tamanho da fonte
        const int FONT_SIZE_M2 = 20;   // Tamanho da fonte

        const int VARIACAO_ALTURA = FONT_SIZE * 1.5;    // Variacao de altura entre cada item dado pelo tamanho da letra
        const int ALTURA_ITEM_0 = GetScreenWidth() / 4;   //Posicao Y do primeiro item menu
        const int ALTURA_ITEM_VOLTAR = ALTURA_ITEM_0 + QTD_OPCOES * VARIACAO_ALTURA + 30 ;   //Posicao Y do primeiro item menu



        {
                BeginDrawing();

                        //Desenhar Plano de Fundo
                        ClearBackground( BLUE );
                        DrawTexture( jogo->Res.TelaDeFundo , 1 , 1 , WHITE );

                        DrawText( ItensMenuDificuldade( 5 ) , CentraTextoX( ItensMenuDificuldade( 5 ) , FONT_SIZE_M1 ) , ALTURA_ITEM_0 - 70 , FONT_SIZE_M1 , WHITE);
                        DrawText( ItensMenuDificuldade( 6 ) , CentraTextoX( ItensMenuDificuldade( 6 ) , FONT_SIZE_M2 ) , GetScreenHeight() - 30 , FONT_SIZE_M2 , WHITE);

                        //Itens Não Selecionados
                        for( i = 0 ; i < QTD_OPCOES - 1 ; i++)
                                DrawText( TextFormat( ItensMenuDificuldade( i ) )  , CentraTextoX( ItensMenuDificuldade( i ) , FONT_SIZE ) , ALTURA_ITEM_0 + i * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_COMUM  );

                        DrawText( ItensMenuDificuldade( VOLTAR ) , CentraTextoX( ItensMenuDificuldade( VOLTAR) , FONT_SIZE) , ALTURA_ITEM_VOLTAR , FONT_SIZE , COR_MENU_COMUM);

                        //Item Selecionado
                        if( selecao != VOLTAR)
                                DrawText( ItensMenuDificuldade( selecao ) , CentraTextoX( ItensMenuDificuldade( selecao) , FONT_SIZE) , ALTURA_ITEM_0 + selecao * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_SELECAO);
                        else
                                DrawText( ItensMenuDificuldade( selecao ) , CentraTextoX( ItensMenuDificuldade( selecao) , FONT_SIZE) , ALTURA_ITEM_VOLTAR , FONT_SIZE , COR_MENU_SELECAO);

                EndDrawing();
        }

}
//##############################################################################



/**     Funcao ItensMenuDificuldade() : Retorna os itens do menu de escolha de dificuldade
    */

char *ItensMenuDificuldade( int escolha )
{
        static char itens[ 7 ][ 70 ] = { "Recruta",
                                                   "Soldado",
                                                   "Coronel",
                                                   "Chuck Norris",
                                                   "Voltar",
                                                   "Escolha a sua patente:",
                                                   "ALERTA: COM GRANDES PODERES VEM GRANDES RESPONSABILIDADES..."
                                                 };

        return itens[ escolha ];
}
//##############################################################################



/**     Funcao AtualizaConfirmarSair();() : Retorna os itens do menu de escolha de dificuldade
    */
void AtualizaConfirmarSair( int *selecao )
{

        if( ( IsKeyPressed( KEY_DOWN) || IsKeyPressed( KEY_RIGHT) ) &&  !*selecao  )
        {
                (*selecao)++;
                return;
        }

        if( ( IsKeyPressed( KEY_UP) || IsKeyPressed( KEY_LEFT) ) &&  *selecao )
        {
                (*selecao)--;
                return;
        }

}
//##############################################################################



/**     Funcao DesenharConfirmarSair() : Retorna os itens do menu de escolha de dificuldade
    */
void DesenharConfirmarSair( int selecao , Jogo *jogo )
{
        Rectangle Janela ;
        Janela.width = 550;
        Janela.height = 100;
        Janela.x = ( GetScreenWidth() - Janela.width ) / 2;
        Janela.y = ( GetScreenHeight() - Janela.height ) / 2;
        const int fonte = 30 ;

        Color cor0;
        Color cor1;

        BeginDrawing();
                DrawTexture( jogo->Res.TelaDeFundo , 1 , 1 , WHITE );
                NomeWolfenEntrada( jogo , ITENS_MAIN_MENU - 1 );
//                DrawTexturePro(  jogo->Res.FundoConfirmarSair , Janela , Janela , (Vector2 ){ Janela.x , Janela.y } ,  0 , WHITE );
                DrawTextureEx(  jogo->Res.FundoConfirmarSair , (Vector2 ){ Janela.x , Janela.y } , 0 , 1 , WHITE );

                cor0 = selecao ? WHITE : GOLD;
                cor1 = selecao ? GOLD : WHITE;

                DrawText("Tem certeza ?" , Janela.x + Janela.width / 3 - 40 ,  Janela.y + Janela.height / 2, fonte , WHITE );
                DrawText("  ~ " , Janela.x + Janela.width / 3 - 50 ,  Janela.y + Janela.height / 2 + 65, fonte , cor0 );
                DrawText("NAO" , Janela.x + Janela.width / 3 - 50 ,  Janela.y + Janela.height / 2 + 85, fonte , cor0 );
                DrawText("SIM" , Janela.x + 2 * Janela.width / 3 - 50 ,  Janela.y + Janela.height / 2 + 85 , fonte , cor1 );

        EndDrawing();
}
//##############################################################################


/**     Funcao DesenharObrigado(): Desenha obrigado na tela
    */
void DesenharObrigado( void )
{
        char obrigado[] = "Obrigado por jogar!";
        int fontsize = 50;
        int i;

        for( i = FPS * 2 ; i ; i-- )
        {
                BeginDrawing();
                        ClearBackground( BLACK );
                        DrawText( obrigado , CentraTextoX( obrigado , fontsize ) , GetScreenHeight() / 2 , fontsize , RAYWHITE);
                EndDrawing();
        }


}
//##############################################################################



/**     Funcao IsGameOver(): Retorn TRUE se jogador recebeu game over
    */

BOOL IsGameOver( Jogo jogo )
{
        if( !jogo.jogador.vidas && !jogo.jogador.VIVO )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsEndGame(): Retorn TRUE se jogador recebeu zerou o jogo
    */

BOOL IsEndGame( Jogo jogo )
{
        if( jogo.Level > MAXLEVEL )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsVoltarMenu(): Retorn TRUE se jogador quer volar para o menu principal
    */

BOOL IsVoltarMenu( Jogo jogo )
{
        if( jogo.VOLTARMENU )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsLevelEnd(): Retorn TRUE se jogador terminou level
    */

BOOL IsLevelEnd( Jogo jogo )
{
        if( jogo.dadosLevel.TERMINADO )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao CarregarLevel(): Carrega os levels
    */
void CarregarLevel( Jogo *jogo)
{
        int i;

        switch( jogo->Level )
        {
                case 1:
                        // Definindo Informações do level
                        jogo->dadosLevel.AlturaTotal = 1000 ;//alet md
                        jogo->dadosLevel.LarguraTotal = 800 ;//alet md
                        jogo->dadosLevel.TERMINADO = 0 ;
                        jogo->dadosLevel.qtdBaus = 1 ;//alet md
                        jogo->dadosLevel.qtdInimT1 = 1 ;//alet md
                        jogo->dadosLevel.qtdInimT2 = 0 ;//alet md
                        jogo->dadosLevel.qtdPortas = 1 ;//alet md
                        jogo->dadosLevel.qtdSpawnsT1 = 2 ;//alet md

                        // Definindo Baús
                        jogo->dadosLevel.baus = (Bau *)malloc( jogo->dadosLevel.qtdBaus * sizeof( Bau) );  // Alocando dinamicamente array dos baus

                        //Itens
                        for( i = 0 ; i < jogo->dadosLevel.qtdBaus ; i++ )
                        {
                                jogo->dadosLevel.baus[ i ].ABERTO = 0 ;
                                jogo->dadosLevel.baus[ i ].KitMedicoP = 1;
                                jogo->dadosLevel.baus[ i ].KitMedicoG = 0;
                                jogo->dadosLevel.baus[ i ].MunEspingarda = 0;
                                jogo->dadosLevel.baus[ i ].MunGranada = 1;
                                jogo->dadosLevel.baus[ i ].MunPistola = GetRandomValue( 10 , 20) ;
                                jogo->dadosLevel.baus[ i ].MunRifle = 0;
                                jogo->dadosLevel.baus[ i ].vidaUp = 0 ;
                                jogo->dadosLevel.baus[ i ].XP = GetRandomValue( 10 , 100);
                        }

                        //Posicionamento
                        jogo->dadosLevel.baus->Rotac = 1 ;//alet md
                        jogo->dadosLevel.baus->px = 15 ;  //alet md
                        jogo->dadosLevel.baus->py = 15;  //alet md


        }

}
//##############################################################################


/**     Funcao AtualizaLevel(): Atualiza os dados do level atual
    */
void AtualizaLevel( Jogo *jogo)
{


}
//##############################################################################



/**     Funcao DesenhaLevel(): Desenha o level atual
    */
void DesenhaLevel( Jogo jogo)
{


}
//##############################################################################



/**     Funcao DesenhaSobre(): Desenha a janela de informações sobre a autoria do jogo
    */

void DesenhaSobre( Jogo jogo)
{
        const int fonte = 25 ;
        const int escala = 1.3;
        Rectangle Janela ;
        Janela.width = escala * jogo.Res.FundoConfirmarSair.width;
        Janela.height = escala * jogo.Res.FundoConfirmarSair.height;
        Janela.x = ( GetScreenWidth() - Janela.width ) / 2;
        Janela.y = 2 * ( GetScreenHeight() - Janela.height ) / 3;
        int ESPY = 18 , ESPX = 25;


        BeginDrawing();

                DrawTexture( jogo.Res.TelaDeFundo , 1 , 1 , WHITE );
                NomeWolfenEntrada( &jogo , ITENS_MAIN_MENU - 1 );
                DrawTextureEx(  jogo.Res.FundoConfirmarSair , (Vector2 ){ Janela.x , Janela.y } , 0 , escala , WHITE );

                DrawTextEx( jogo.Res.fonteWolfen ,    "WOLFENSTEIN 1.0" , (Vector2 ){ Janela.x + ESPX , Janela.y + ESPY } , fonte , 3 , WHITE );
                DrawText(TextFormat("Escrito por : ") , Janela.x + 2 * ESPX ,  Janela.y + 4 * ESPY , fonte , WHITE );
                DrawText("-Manoel Narciso Filho" , Janela.x + 3 * ESPX ,  Janela.y + 6 * ESPY , fonte , WHITE );
                DrawText("-Matheus De Moraes Costa" , Janela.x + 3 * ESPX ,  Janela.y + 8 * ESPY , fonte , WHITE );
                DrawText("SAIR" , Janela.x + ( Janela.width - MeasureText( "SAIR" , fonte ) ) / 2 , Janela.y + Janela.height - 30 , fonte , GOLD );

        EndDrawing();


}
//##############################################################################
