
#include "OpcoesDoMenu.h"
#include "booleanas.h"
#include "inicializar.h"


int dificuldade;

void NovoJOGO( JOGO *jogo ){
        if( jogo->jogador.venceu ) return;
        int selecaoMenu = 0;
        int sair_menuP = 0;


        do
        {
                DesenhaMenuDificuldade( jogo , selecaoMenu );   // Desenha Menu secundário para escolher dificuldade
                AtualizaMenu( &selecaoMenu , ITENS_NOVO_JOGO );   //Atualiza Menu secundário Novo jogo

                if( selecaoMenu != ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER )  ){
                        sair_menuP = 1;
                        dificuldade = selecaoMenu;
                        jogo->salas[0].qtd_inimigos_liberar *= ( 1+ dificuldade / 2 );
                        jogo->salas[2].qtd_inimigos_liberar *= ( 1+ dificuldade / 2 );
                        jogo->salas[4].qtd_inimigos_liberar *= ( 1+ dificuldade / 2 );
                        jogo->salas[5].qtd_inimigos_liberar *= ( 1+ dificuldade / 2 );
                        jogo->salas[6].qtd_inimigos_liberar *= 1;
                        jogo->salas[8].qtd_inimigos_liberar *= 1;
                        jogo->salas[10].qtd_inimigos_liberar *= 1;
                        jogo->salas[12].qtd_inimigos_liberar *= ( 1+ dificuldade / 2 ); //N precisa
                        jogo->salas[13].qtd_inimigos_liberar *= ( 1+ dificuldade / 2 ); //N precisa



                        CriarNovoJogador( jogo );   //  Definir nome do jogador

                        while(  !IsGameOver( jogo )  &&  !IsKeyPressed( KEY_HOME )  && !IsEndGame( jogo )   &&  !jogo->VOLTARMENU ){
                                AtualizaLevel( jogo );
                                DesenhaLevel( jogo );

                        }
                }
        }
        while( !(selecaoMenu == ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER ) )  &&  !sair_menuP );
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

                if( !IsKeyDown( KEY_ENTER ) ){
                        add[ 0 ] = GetCharPressed();
                        strcat( nome , add );
                }

                if( IsKeyPressed( KEY_BACKSPACE )  &&  strlen( nome ) )
                        nome[ strlen( nome ) - 1 ] = '\0';

        }while( !IsKeyPressed( KEY_ENTER )  ||  nome[0] == '\0' );

        for( int z = 0 ; z <= strlen( nome ) ; z++ )
                cam[ 6 + z ] = nome[ z ];

//        strcat( cam , nome );
        FILE* save = fopen( cam , "r" );
//        FILE* save = fopen( "Saves/MNarF" , "r" );

        fread( jogo , sizeof(JOGO) , 1 ,  save );

        fclose( save );


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

typedef struct{
        char nome[ 10 ][ 100 ];
        int pnts[ 10 ];
}PONTUAC;

void Configurar( JOGO *jogo)
{
        /// HIGHSCORES
        PONTUAC pontuac;
        FILE* arq;
        arq = fopen( "HighScores/high_scores" , "rb+");

        fread( &pontuac , sizeof( PONTUAC ) , 1 , arq );

        fclose( arq );


        for( int z = FPS / 6 ; z ; z-- ){
                BeginDrawing();
                        ClearBackground( BLACK );
                EndDrawing();
        }

        do{
                UpdateMusicStream( jogo->Res.musica_final );
                BeginDrawing();
                        DrawTextEx( jogo->Res.fonteWolfen2 , "HIGHSCORES" , (Vector2){ CentraTextoXEX( jogo->Res.fonteWolfen2 , "HIGHSCORES" , 70 , 3 ) , 90 } , 70 , 3 , RED );

                        for( int y = 0 ; y < 10 ; y++ ){
                                DrawText( TextFormat("%4d  -  %s" , pontuac.pnts[ y ] , pontuac.nome[ y ] ) , 300 , 200 + 50 * y , 40 , WHITE );
                        }

                        for ( int k =  3000 * FPS  ; k ; k-- );

                EndDrawing();
        }while( !IsKeyPressed( KEY_ENTER ) );
}


void Ajuda( JOGO *jogo)
{

        for( int z = FPS / 6 ; z ; z-- ){
                BeginDrawing();
                        ClearBackground( BLACK );
                EndDrawing();
        }

        do{
                BeginDrawing();
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
