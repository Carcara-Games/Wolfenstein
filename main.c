/***-  WOLFENSTEIN══════════════════════════════╗
        *  UFRGS
        *  INF01202 - Algorítmos e Programação
        *  Aluno: @author Manoel Narciso Reis Soares Filho
        *  Aluno: @author Matheus Moraes
        *  Data: @date 19/05/2021
        *  ════════════════════════════════════════╝
        *
        *    Trabalho Final --------------------------------------------------
        *               Versão do clássico jogo wolfenstein, escrito em
        *       linguagem C utilizando bliblioteca gráfica RayLib.
        *       Divirta-se.
        *
        *
        */

#include "raylib.h"
#include "inicializar.h"
#include "OpcoesDoMenu.h"


/// PROTÓTIPOS PRINCIPAIS  -------------------------------------------------
void logoCarcaraGames( Rectangle tela );

///MAIN  -------------------------------------------------
int main(){
        IniciarJanela();  //Configura as opcoes da janela
        InitAudioDevice();
        JOGO jogo = definirPreJogo();          // Inicializa fontes, texturas e informacoes gerais do jogo
        IniciaNovoJogo( &jogo );  // Incializa informacoes para Novo Jogo
        void (*opcao[])( JOGO* ) = { NovoJOGO , Continuar , ModoHorda , HighScores , Ajuda , Sobre , Sair };            //Ponteiro para as opcoes do MENU
        int selecaoMenu = 0;

        SetMouseCursor( 3 );    // Cursor Modo Mira
        HideCursor();           // Esconder Cursor

        logoCarcaraGames( jogo.tela );
        do{
                DesenhaMenuPrincipal( &jogo, selecaoMenu );   // Desenha menu principal
                AtualizaMenu( &selecaoMenu , 7  );   // Atualiza Selecao do menu. 7 é o número de opções do menu principal

                if ( IsKeyPressed(KEY_ENTER) ){
                        som_enter();
                        opcao[ selecaoMenu ]( &jogo ) , selecaoMenu = 0 ;
                }
        }while( !( (IsKeyPressed( KEY_ENTER ) && selecaoMenu == ITENS_MAIN_MENU - 1 ) || WindowShouldClose() || jogo.FECHAR ) );
        DesenharObrigado();

        CloseAudioDevice();
        CloseWindow();
        return 0;
}
//################################################################################################

#define LARG_LOGO 400
#define ALTU_LOGO 400
#include <time.h>
void logoCarcaraGames( Rectangle tela ){
        Texture logo = LoadTexture( "Logo/Logo2.png" );
        Sound som_logo = LoadSound( "Som/Som_Logo_Carcara_Games.mp3" );
        Font fonte = LoadFont("Fontes/fontew2.ttf");
        int visib_logo = 0;
        long int CLOCK = 1;

        PlaySound( som_logo );

        for( int tempo = FPS / 5 ; tempo ; tempo-- ){
                BeginDrawing();
                        ClearBackground( BLACK );
                EndDrawing();
        }

        for( int tempo = 7 * FPS ; tempo ; tempo-- ){
                BeginDrawing();
                        DrawTexturePro( logo , (Rectangle){ 0 , 0 , logo.width , logo.height } , (Rectangle){ ( tela.width - LARG_LOGO ) / 2 , ( tela.height - ALTU_LOGO) / 2 , LARG_LOGO , ALTU_LOGO } , (Vector2){ 0 , 0 } , 0 , CLITERAL(Color){ 255, 255, 255, visib_logo } );

                        DrawTextEx( fonte , "CARCARA GAMES" , (Vector2){ tela.width / 2 + LARG_LOGO / 2 - MeasureTextEx( fonte , "CARCARA GAMES" , 50 , 10 ).x , ( tela.height - ALTU_LOGO) / 2+ ALTU_LOGO + 60 } , 50 , 10 ,  CLITERAL(Color){ 255, 203, 0, visib_logo } );

                        if( !( CLOCK % 5 ) )  if( visib_logo < 255 ) visib_logo++;

                        CLOCK++;
                EndDrawing();
        }

}



