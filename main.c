/**     WOLFENSTEIN
    *     Autores: Manoel Narciso Filho e Matheus De Moraes Costa
    *     Última Modificação: 09/04/2021 16:36
    *
    */

#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

#define SAIR 6

typedef struct
{
        Texture2D MenuFundo;    // Imagem do plano de fundo
        Texture2D Logo;    // Imagem de fundo (Logo)
        Font fonteWolfen;
        Texture2D TelaDeFundo;

}Recursos;

typedef struct
{
        Recursos Res;


}Jogo;

///Protótipos
void IniciarJanela( void );
void MovimentoMenu( int *selecao , int qtd_opcoes );
int CentraTextoX( char *texto , int fontsize );
int CentraTextoXEX( Font fonte , char *texto , float fontsize , float space);

int MenuPrincipal( Jogo *jogo );
int MenuDificuldade( Jogo *jogo );

void NomeEntrada( Jogo *jogo );
char *ItensMenuPrincipal(int escolha);
char *ItensMenuDificuldade( int escolha );
Jogo IniciaJogo( void );
void LimparBuffer( void );



///Main
int main()
{
        int selecaoMenu = 0;

        IniciarJanela();

        Jogo jogo = IniciaJogo();


        while( selecaoMenu != SAIR  &&  !WindowShouldClose() )
        {
                selecaoMenu = MenuPrincipal( &jogo );   // Retorna opção que jogador apertou enter

                printf("\n\nInicio Switch Retorno :: %d" , selecaoMenu );
                switch( selecaoMenu )   // Escolhe ação dependendo opção escolhida no menu principal
                {

                        case 0:   //Novo Jogo ---------------------------------------------------------------------------------------------------------------------------------------------------
                                selecaoMenu = MenuDificuldade( &jogo );   //Menu secundário para escolher dificuldade
//                                CriarNovoJogador();   //Menu secundário para definir nome

//                                whille( !IsGameOver() && !IsEndGame() && !IsVoltarMenu() ) //Continua avançando de level a menos que usuário receba game over, zere o jogo ou volte para o menu
//                                {
//                                        static int Level = 0;  // Level Inicia em 0 para ser somado 1
//
//                                        Level++;
//                                        CarregarFase(Level); //Carrega as fases em sequência. Se Jogador recebe game over, zera ou pede para voltar para o menu ativa as respectivas flags
//                                }
                                break;

                        case 1:    //Continuar ---------------------------------------------------------------------------------------------------------------------------------------------------
//                                ListaJogadoresSalvos();  //Menu secundário que apresenta jogadores salvos ( cada jogador criado só pode manter um savegame para não virar uma zona)
                                break;


                        case 2:    //Modo Horda ---------------------------------------------------------------------------------------------------------------------------------------------------
//                                IniciarModoHorda();   //Inicia modo horda. Dificuldade única
                                break;

                        case 3:    //Configurar ---------------------------------------------------------------------------------------------------------------------------------------------------
//                                AbreConfiguracoes();   //Menu secundário de configurações
                                break;

                        case 4:    //Ajuda ---------------------------------------------------------------------------------------------------------------------------------------------------
//                                ApresentaAjuda();   // Ajudas e dicas gerais sobre o jogo e sobre os comandos

                                break;

                        case 5:    //Sobre ---------------------------------------------------------------------------------------------------------------------------------------------------
                                //Só um teste
                                while( !WindowShouldClose() )
                                {

                                        BeginDrawing();
                                                ClearBackground( WHITE );
                                                DrawRectangle( 100 , 400 , 70 , 30 , RED);
                                                DrawTriangle( (Vector2 ){ 100 , 100} , (Vector2 ){ 500 , 100} , (Vector2 ){ 400 , 400} , GREEN);
                                        EndDrawing();
                                }

//                                ApresentaSobre();   //Apresenta autores e etc
                                break;

                        case 6:    //Sair ---------------------------------------------------------------------------------------------------------------------------------------------------
//                                ConfirmarSair();   //Janela de confirmação de saída
                                break;
                }
                printf("\n\nFinal Switch");
        }

        CloseWindow();
        return 0;
}



/// Funcao Menu() : Desenha o menu quando programa esta na parte inicial

#define COR_MENU_COMUM WHITE          // Cor do texto do menu nao selecionado
#define COR_MENU_SELECAO GOLD          // Cor do texto do menu selecionado

int MenuPrincipal( Jogo *jogo )
{
        int i;
        int selecao = 0;   // Informa qual item do menu esta em foco

        const int FONT_SIZE = 30;   // Tamanho da fonte do menu
        const int ALTURA_ITEM_0 = GetScreenWidth() / 4;   //Posicao Y do primeiro item menu
        const int VARIACAO_ALTURA = FONT_SIZE * 1.5;    // Variacao de altura entre cada item dado pelo tamanho da letra
        const int QTD_OPCOES = 7;     // Quantidade de opcoes no menu

        //LOOP MENU
        printf("\n>>%d<<" , IsKeyPressed( KEY_ENTER ));
        LimparBuffer();
        while( !IsKeyPressed( KEY_ENTER )  )
        {
                // Captura movimento entre itens do menu
                MovimentoMenu( &selecao , QTD_OPCOES );

                BeginDrawing();
                {
                        // Fundo
                        ClearBackground(WHITE);
                        DrawTexture( jogo->Res.MenuFundo , ( GetScreenWidth() - jogo->Res.MenuFundo.width ) / 2 , ( GetScreenHeight() - jogo->Res.MenuFundo.height ) / 2 , WHITE);  //Plano de Fundo Customizado
                        NomeEntrada( jogo );  //Nome Wolfenstein com efeito de entrada
                        DrawTextureEx( jogo->Res.Logo , (Vector2 ){ 5 , 5 } , 0 ,  .2 , WHITE );  //Mini logo no canto superior esquerdo

                        // Desenha todos os itens em cor comum
                        for( i = 0 ; i < QTD_OPCOES ; i++)
                                DrawText( TextFormat( ItensMenuPrincipal( i ) )  , CentraTextoX( ItensMenuPrincipal( i ) , FONT_SIZE ) , ALTURA_ITEM_0 + i * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_COMUM  );

                        // Desenha o item em foco em cor de selecao
                        DrawText( TextFormat( ItensMenuPrincipal( selecao ) ) , CentraTextoX( ItensMenuPrincipal( selecao ) , FONT_SIZE ) , ALTURA_ITEM_0 + selecao * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_SELECAO  );
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

/**     Funcao NomeEntrada() : Escreve Wolfenstein com efeito legal
    */

#define HWOLF 150    //Posicao Y na tela do nome Wolfenstein
#define FONT_SIZE_WOLF 130    // Tamanho na tela do nome Wolfenstein
#define MULT 5
#define ESP_WOLF 7

void NomeEntrada( Jogo *jogo )
{
        static int i = 0 , j = 10 * MULT;
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

        DrawTextEx( jogo->Res.fonteWolfen ,  Escreva , (Vector2){ CentraTextoXEX( jogo->Res.fonteWolfen , Escreva , FONT_SIZE_WOLF , ESP_WOLF  )  ,  HWOLF / ( 27 - i ) }  , FONT_SIZE_WOLF , ESP_WOLF , WHITE );

}

//##############################################################################

/**     Funcao MovimentoMenu() : Captura pressionamento de teclas alterando item em foco do menu
    *           -> Entradas: Endereço do variavel de selecao
    */

void MovimentoMenu( int *selecao , int qtd_opcoes )
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

#define FPS 30
//#define EXITKEY KEY_BACKSLASH
#define EXITKEY KEY_ESCAPE

void IniciarJanela( void )
{
        int TelaLargura = GetMonitorWidth(0);
        int TelaAltura = GetMonitorHeight (0);

        InitWindow( TelaLargura , TelaAltura , "WOLFENSTEIN" );
        SetTargetFPS( FPS );
        //ToggleFullscreen();
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



/**     Funcao MenuDificuldade() : Apresenta o menu de escolha de dificuldade
    */
#define RECRUTA 0
#define SOLDADO 1
#define VETERANO 2
#define CHUCK_NORRIS 3
#define VOLTAR 4

int MenuDificuldade( Jogo *jogo )
{
        int selecao = 0;
        register int i ;

        const int QTD_OPCOES = 5;     // Quantidade de opcoes no menu
        const int FONT_SIZE = 30;   // Tamanho da fonte

        const int VARIACAO_ALTURA = FONT_SIZE * 1.5;    // Variacao de altura entre cada item dado pelo tamanho da letra
        const int ALTURA_ITEM_0 = GetScreenWidth() / 4;   //Posicao Y do primeiro item menu
        const int ALTURA_ITEM_VOLTAR = ALTURA_ITEM_0 + QTD_OPCOES * VARIACAO_ALTURA + 30 ;   //Posicao Y do primeiro item menu



        while( !IsKeyPressed( KEY_ENTER ) )
        {
                BeginDrawing();

                        //Desenhar Plano de Fundo
                        ClearBackground( WHITE );
                        DrawTexture( jogo->Res.TelaDeFundo , 1 , 1 , WHITE );

                        MovimentoMenu( &selecao , QTD_OPCOES );

                        //Itens Não Selecionados
                        for( i = 0 ; i < QTD_OPCOES - 1 ; i++)
                                DrawText( TextFormat( ItensMenuDificuldade( i ) )  , CentraTextoX( ItensMenuDificuldade( i ) , FONT_SIZE ) , ALTURA_ITEM_0 + i * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_COMUM  );


                        //Item Selecionado
                        if( selecao != VOLTAR)
                                DrawText( ItensMenuDificuldade( selecao ) , CentraTextoX( ItensMenuDificuldade( selecao) , FONT_SIZE) , ALTURA_ITEM_0 + selecao * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_SELECAO);
                        else
                                DrawText( ItensMenuDificuldade( selecao ) , CentraTextoX( ItensMenuDificuldade( selecao) , FONT_SIZE) , ALTURA_ITEM_VOLTAR , FONT_SIZE , COR_MENU_SELECAO);

                EndDrawing();
        }

        return selecao ;
}
//##############################################################################



/**     Funcao ItensMenuDificuldade() : Retorna os itens do menu de escolha de dificuldade
    */

char *ItensMenuDificuldade( int escolha )
{
        static char itens[ 5 ][ 30 ] = { "Recruta",
                                                   "Soldado",
                                                   "Veterano",
                                                   "Chuck Norris"
                                                   "Voltar"
                                                 };

        return itens[ escolha ];
}

void LimparBuffer( void )
{
        int i;

        for( i = 40 ; i ; i--)
                GetKeyPressed();

}

