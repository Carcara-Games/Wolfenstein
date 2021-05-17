
#include "OpcoesDoMenu.h"
#include "booleanas.h"



void NovoJOGO( JOGO *jogo ){
        int selecaoMenu = 0;
        int sair_menuP = 0;

        do
        {
                DesenhaMenuDificuldade( jogo , selecaoMenu );   // Desenha Menu secundário para escolher dificuldade
                AtualizaMenu( &selecaoMenu , ITENS_NOVO_JOGO );   //Atualiza Menu secundário Novo jogo

                if( selecaoMenu != ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER )  ){
                        sair_menuP = 1;
                        CriarNovoJogador( jogo );   //  Definir nome do jogador

                        while(  !IsGameOver( jogo )  &&  !IsKeyPressed( KEY_HOME )  && !IsEndGame( jogo )   &&  !jogo->VOLTARMENU ){
                                AtualizaLevel( jogo );
                                DesenhaLevel( jogo );

                        }
                }
        }
        while( !(selecaoMenu == ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER ) )  &&  !sair_menuP);
}

#include <string.h>
void Continuar( JOGO *jogo){
        char cam[100] = "Saves/";

        char msg[ 100 ] = "Nome do save game:";
        char nome[ 100 ] = { 0 };
        char add[ 2 ] = { '\0' , '\0' };
        do{
                BeginDrawing();
                        ClearBackground( MAROON );
                        DrawText( msg , CentraTextoX( msg , 35 ) , jogo->tela.height / 2 - 50 , 35 , RAYWHITE );
                        DrawRectangle( jogo->tela.width / 2 - 255 , jogo->tela.height / 2 , 510 , 50 , BLACK );
                        DrawRectangle( jogo->tela.width / 2 - 250 , jogo->tela.height / 2 + 5, 500 , 40 , DARKGRAY );


                        DrawText( nome , CentraTextoX( nome , 35 ) , jogo->tela.height / 2 + 5 , 35 , RAYWHITE );

                EndDrawing();

                add[ 0 ] = GetCharPressed();
                strcat( nome , add );

                if( IsKeyPressed( KEY_BACKSPACE )  &&  strlen( nome ) )
                        nome[ strlen( nome ) - 1 ] = '\0';

        }while( !IsKeyPressed( KEY_ENTER )  ||  nome[0] == '\0' );


        strcat( cam , nome );
        FILE* save = fopen( cam , "r" );

        fread( jogo , sizeof(JOGO) , 1 ,  save );


        while(  !IsGameOver( jogo )  &&  !IsKeyPressed( KEY_HOME )  && !IsEndGame( jogo )   &&  !jogo->VOLTARMENU ){
                AtualizaLevel( jogo );
                DesenhaLevel( jogo );

        }
}


void ModoHorda( JOGO *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Modo Horda " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Configurar( JOGO *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Configurar " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Ajuda( JOGO *jogo)
{
        do{

                BeginDrawing();
                        ClearBackground( BLACK );
                        DrawTexture( jogo->Res.Ajuda_Menu , jogo->tela.width / 2 - 500 , jogo->tela.height / 2 - 267 , WHITE );
                EndDrawing();
        }while( !IsKeyPressed( KEY_ENTER ) );

}


void Sobre( JOGO *jogo)
{

        DesenhaSobre( *jogo );

}


void Sair( JOGO *jogo)
{
//        int selecaoMenu = 0;
//        do
//        {
//                AtualizaConfirmarSair( &selecaoMenu );   //Janela de confirmação de saída
//                DesenharConfirmarSair( selecaoMenu , jogo);
//                 jogo->FECHAR = selecaoMenu ? SIM : NAO;
//        }while( !IsKeyPressed( KEY_ENTER ) );
        jogo->FECHAR = SIM;
}

void CriarNovoJogador( JOGO* jogo ){
        char msg[ 100 ] = "Seu nome soldado:";
        char nome[ 100 ] = { 0 };
        char add[ 2 ] = { '\0' , '\0' };
        do{
                BeginDrawing();
                        ClearBackground( MAROON );
                        DrawText( msg , CentraTextoX( msg , 35 ) , jogo->tela.height / 2 - 50 , 35 , RAYWHITE );
                        DrawRectangle( jogo->tela.width / 2 - 255 , jogo->tela.height / 2 , 510 , 50 , BLACK );
                        DrawRectangle( jogo->tela.width / 2 - 250 , jogo->tela.height / 2 + 5, 500 , 40 , DARKGRAY );


                        DrawText( nome , CentraTextoX( nome , 35 ) , jogo->tela.height / 2 + 5 , 35 , RAYWHITE );

                EndDrawing();

                add[ 0 ] = GetCharPressed();
                strcat( nome , add );

                if( IsKeyPressed( KEY_BACKSPACE )  &&  strlen( nome ) )
                        nome[ strlen( nome ) - 1 ] = '\0';

        }while( !IsKeyPressed( KEY_ENTER )  ||  nome[0] == '\0' );

        /// Alocar Nome do Jogador
        jogo->jogador.nome = (char*)malloc( ( strlen( nome ) + 1 ) * sizeof( char ) );

        strcpy( jogo->jogador.nome , nome );
}


void som_enter( void ){
        Sound som = LoadSound("Som/enter.wav") ;
        PlaySound( som );
}
