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

#define SAIR_PRINCIPAL 6
#define SIM 1
#define NAO 0

typedef struct
{
        Texture2D MenuFundo;    // Imagem do plano de fundo principal
        Texture2D Logo;    // Imagem de fundo (Logo)
        Font fonteWolfen;  // Fonte Estilizada Wolfenstein
        Texture2D TelaDeFundo;  //Tela de fundo somente cores
        Texture2D FundoConfirmarSair;  //Janela de fundo da confirmação de saída

}Recursos;

typedef struct
{
        Recursos Res;  //Recursos do jogo
        int NivelMenu;  //Nível atual do menu( 0->Principal , 1- Algum dos secundários , 2->Menu interno do jogo , 3 - Jogando);
        unsigned FECHAR : 1;
}Jogo;

///Protótipos
void IniciarJanela( void );
void MovimentoMenu( int *selecao , int qtd_opcoes );
int CentraTextoX( char *texto , int fontsize );
int CentraTextoXEX( Font fonte , char *texto , float fontsize , float space);

void AtualizaMenu( int* selecao , int qtd_opcoes );
void DesenhaMenuPrincipal(Jogo *jogo, int selecao);
void DesenhaMenuDificuldade( Jogo *jogo , int selecao );

void NomeWolfenEntrada( Jogo *jogo , int selecao  );
char *ItensMenuPrincipal(int escolha);
char *ItensMenuDificuldade( int escolha );
Jogo IniciaJogo( void );
void LimparBuffer( void );

void DesenharConfirmarSair( int selecao , Jogo *jogo );
void AtualizaConfirmarSair( int *selecao );
void DesenharObrigado( void );



///MAIN
int main()
{
        IniciarJanela();  //Configura as opções da janela

        Jogo jogo = IniciaJogo();  // Carrega recursos do jogo

        int selecaoMenu = 0;

        while( !((IsKeyPressed(KEY_ENTER) && selecaoMenu == SAIR_PRINCIPAL) || WindowShouldClose() || jogo.FECHAR) )
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
                                                AtualizaMenu( &selecaoMenu , 5 );   //Atualiza Menu secundário

                                                if( selecaoMenu != 4 && IsKeyPressed( KEY_ENTER )  )
                                                {
                //                                      CriarNovoJogador();   //Menu secundário para definir nome

                                                }

                                        }
                                        while( !(selecaoMenu == 4 && IsKeyPressed( KEY_ENTER ) ) );

        //                                whille( !IsGameOver() && !IsEndGame() && !IsVoltarMenu() ) //Continua avançando de level a menos que usuário receba game over, zere o jogo ou volte para o menu
        //                                {
        //                                        static int Level = 0;  // Level Inicia em 0 para ser somado 1
        //
        //                                        Level++;
        //                                        CarregarFase(Level); //Carrega as fases em sequência. Se Jogador recebe game over, zera ou pede para voltar para o menu ativa as respectivas flags
        //                                }
                                        break;

                                case 1:    //Continuar ------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                ListaJogadoresSalvos();  //Menu secundário que apresenta jogadores salvos ( cada jogador criado só pode manter um savegame para não virar uma zona)
                                        break;


                                case 2:    //Modo Horda ---------------------------------------------------------------------------------------------------------------------------------------------------
        //                                IniciarModoHorda();   //Inicia modo horda. Dificuldade única
                                        break;

                                case 3:    //Configurar ------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                AbreConfiguracoes();   //Menu secundário de configurações
                                        break;

                                case 4:    //Ajuda ------------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                ApresentaAjuda();   // Ajudas e dicas gerais sobre o jogo e sobre os comandos

                                        break;

                                case 5:    //Sobre ------------------------------------------------------------------------------------------------------------------------------------------------------------
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

        if( jogo->NivelMenu != 0  &&  selecao != SAIR_PRINCIPAL )
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
//#define EXITKEY KEY_BACKSLASH
#define EXITKEY KEY_ESCAPE

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
                        ClearBackground( WHITE );
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



/**     Funcao DesenharConfirmarSair();() : Retorna os itens do menu de escolha de dificuldade
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
                NomeWolfenEntrada( jogo , SAIR_PRINCIPAL );
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
