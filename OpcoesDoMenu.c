
#include "OpcoesDoMenu.h"
#include "booleanas.h"


void NovoJOGO( JOGO *jogo )
{
        int selecaoMenu = 0;
        static int sair_menuP = 0;

        do
        {
                DesenhaMenuDificuldade( jogo , selecaoMenu );   // Desenha Menu secundário para escolher dificuldade
                AtualizaMenu( &selecaoMenu , ITENS_NOVO_JOGO );   //Atualiza Menu secundário Novo jogo

                if( selecaoMenu != ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER )  ){
                        sair_menuP = 1;
                        CriarNovoJogador( jogo );   //  Definir nome do jogador

                        while(  !IsGameOver( jogo )  &&  !IsKeyPressed( KEY_HOME )  && !IsEndGame( jogo ) )
                        {
                                AtualizaLevel( jogo );
                                DesenhaLevel( jogo );
                        }
                }
        }
        while( !(selecaoMenu == ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER ) )  &&  !sair_menuP);
}


void Continuar( JOGO *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Continuar " , 300 , 300 , 50 , GREEN );
                EndDrawing();
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
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Ajuda " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Sobre( JOGO *jogo)
{
        do{
                DesenhaSobre( *jogo );

        }while( IsKeyPressed( KEY_ENTER ) );
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

#include <string.h>
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

        }while( !IsKeyPressed( KEY_ENTER ) );

        TextCopy( jogo->jogador.nome , nome );
}
