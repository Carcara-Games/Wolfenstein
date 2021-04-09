/**     WOLFENSTEIN
    *     Autores: Manoel Narciso Filho e Matheus De Moraes Costa
    *     Última Modificação: 08/04/2021 16:36
    *
    */

#include "raylib.h"
#include <math.h>


void IniciarJanela( void );
void MovimentoMenu( int *selecao );
int CentraTextoX( char *texto , int fontsize );
int CentraTextoXEX( Font fonte , char *texto , float fontsize , float space);
int Menu( void );
void EntradaNome( void );
void NomeEntrada( void );
char *ItensMenuPrincipal(int escolha);

#define SAIR 6

int main()
{
        IniciarJanela();

        int selecaoMenu = 0;

        while( selecaoMenu != SAIR  ||  WindowShouldClose() )
        {
                selecaoMenu = Menu();   // Retorna opção que jogador apertou enter

                switch( selecaoMenu )   // Age em cima da opção do menu principal
                {
                        //Novo Jogo
                        case 0:
//                                Dificuldade();   //Menu secundário para escolher dificuldade
//                                CriarNovoJogador();   //Menu secundário para definir nome

//                                whille( !IsGameOver() && !IsEndGame() && !IsVoltarMenu() ) //Continua avançando de level a menos que usuário receba game over, zere o jogo ou volte para o menu
//                                {
//                                        static int Level = 0;  // Level Inicia em 0 para ser somado 1
//
//                                        Level++;
//                                        CarregarFase(Level); //Carrega as fases em sequência. Se Jogador recebe game over, zera ou pede para voltar para o menu ativa as respectivas flags
//                                }
//
                                break;

                        //Continuar
                        case 1:
//                                ListaJogadoresSalvos();  //Menu secundário que apresenta jogadores salvos ( cada jogador criado só pode manter um savegame para não virar uma zona)
                                break;

                        //Modo Horda
                        case 2:
//                                IniciarModoHorda();   //Inicia modo horda. Dificuldade única
                                break;

                        //Configurar
                        case 3:
//                                AbreConfiguracoes();   //Menu secundário de configurações
                                break;

                        //Ajuda
                        case 4:
//                                ApresentaAjuda();   // Ajudas e dicas gerais sobre o jogo e sobre os comandos
                                break;

                        //Sobre
                        case 5:
//                                ApresentaSobre();   //Apresenta autores e etc
                                break;

                        //Sair
                        case 6:
//                                ConfirmarSair();   //Janela de confirmação de saída

                                break;

                }
        }

        CloseWindow();
        return 0;
}



/// Funcao Menu() : Desenha o menu quando programa esta na parte inicial

#define COR_MENU_FUNDO LIGHTGRAY          // Cor de fundo do menu
#define COR_MENU_COMUM WHITE          // Cor do texto do menu nao selecionado
#define COR_MENU_SELECAO GOLD          // Cor do texto do menu selecionado
#define QTD_OPCOES 7            //QTD de opcoes

int Menu( void )
{
        int i;
        int selecao = 0;   // Informa qual item do menu esta em foco
        const int FONTSIZE = 30;   // Altura da fonte do menu
        const int ALTMENU0 = GetScreenWidth() / 4;   //Posicao Y do primeiro item menu
        const int ALTMENUVAR = FONTSIZE * 1.5;    // Variacao de altura entre cada item dado pelo tamanho da letra
        Texture2D MenuFundo = LoadTexture("Menu_Imagens/Menu10.png");    // Imagem do fundo
        Texture2D Logo = LoadTexture("Logo/Logo.png");    // Imagem do fundo
        //LOOP MENU
        while( !IsKeyPressed( KEY_ENTER ) )
        {
                BeginDrawing();
                {

                        // Fundo
                        ClearBackground(WHITE);
                        DrawTexture( MenuFundo , ( GetScreenWidth() - MenuFundo.width ) / 2 , ( GetScreenHeight() - MenuFundo.height ) / 2 , WHITE);
                        NomeEntrada();
                        DrawTextureEx( Logo ,(Vector2 ){ 5 , 5 } , 0 ,  .2 , WHITE );

                        // Desenha todos os itens em cor comum
                        for( i = 0 ; i < QTD_OPCOES ; i++)
                                DrawText( TextFormat( ItensMenuPrincipal( i ) )  , CentraTextoX( ItensMenuPrincipal( i ) , FONTSIZE ) , ALTMENU0 + i * ALTMENUVAR , FONTSIZE , COR_MENU_COMUM  );

                        // Captura movimento entre itens do menu
                        MovimentoMenu( &selecao );

                        // Desenha o item em foco em cor de selecao
                        DrawText( TextFormat( ItensMenuPrincipal( selecao ) ) , CentraTextoX( ItensMenuPrincipal( selecao ) , FONTSIZE ) , ALTMENU0 + selecao * ALTMENUVAR , FONTSIZE , COR_MENU_SELECAO  );
                }
                EndDrawing();
        }


        return selecao;
}
//##############################################################################

/**     Funcao ItensMenuPrincipal() :
    */
char *ItensMenuPrincipal(int escolha)
{
        static char opcao[ QTD_OPCOES ][ 30 ] =             {
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

/**     Funcao NomeEntrada() : Escreve Wolfenstein com efeito legal
    */

#define HWOLF 150    //Posicao Y na tela do nome Wolfenstein
#define FONT_SIZE_WOLF 130    // Tamanho na tela do nome Wolfenstein
#define MULT 5
#define ESP_WOLF 7

void NomeEntrada( void )
{
        static int i = 0 , j = 10 * MULT;
        Font fonteWolfen = LoadFontEx("Fontes/ReturnToCastle-MZnx.ttf"  ,96 , 0 , 0);
        int k , f , L1 , L2;
        const char Nome[ 12 ] = "WOLFENSTEIN";
        char Escreva[ 12 ] = "           ";

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

        DrawTextEx(fonteWolfen ,  Escreva , (Vector2){ CentraTextoXEX( fonteWolfen , Escreva , FONT_SIZE_WOLF , ESP_WOLF  )  ,  HWOLF / ( 27 - i ) }  , FONT_SIZE_WOLF , ESP_WOLF , WHITE );

}

//##############################################################################

/**     Funcao MovimentoMenu() : Captura pressionamento de teclas alterando item em foco do menu
    *           -> Entradas: Endereço do variavel de selecao
    */

void MovimentoMenu( int *selecao )
{
        if( IsKeyPressed( KEY_DOWN)  &&  *selecao < QTD_OPCOES - 1 )
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

#define FPS 30
#define EXITKEY KEY_BACKSLASH
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




