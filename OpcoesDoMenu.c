
#include "OpcoesDoMenu.h"
#include "booleanas.h"
#include "inicializar.h"


int dificuldade;
extern Music musMenu;
void NovoJOGO( JOGO *jogo ){
        int selecaoMenu = 0;
        int sair_menuP = 0;

        inicializarJogador( jogo );
        inicializarInimigosSalas( jogo );
        CriaPortas( jogo );
        CriaSpawns( jogo );             // Cria Spawns
        CriaBaus( jogo );               //Cria BAUS
        CarregarBaus( jogo );               //Cria BAUS

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

                                ShowCursor();   // Reexibir cursor

                                while(  !IsGameOver( jogo )  &&  !IsKeyPressed( KEY_HOME )  && !IsEndGame( jogo )   &&  !jogo->VOLTARMENU ){
                                        AtualizaLevel( jogo );
                                        DesenhaLevel( jogo );

                                }

                                HideCursor();
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
                        if( jogo->jogador.venceu ) UpdateMusicStream( jogo->Res.musica_final );
                        else UpdateMusicStream( musMenu );

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
        FILE* save = fopen( cam , "rb" );
//        FILE* save = fopen( "Saves/MNarF" , "r" );

        if( save == NULL ){
                som_erro();
                return;
        }

        fread( jogo , sizeof(JOGO) , 1 ,  save );

        fclose( save );


        while(  !IsGameOver( jogo )  &&  !IsKeyPressed( KEY_HOME )  && !IsEndGame( jogo )   &&  !jogo->VOLTARMENU ){
                AtualizaLevel( jogo );
                DesenhaLevel( jogo );

        }
}


#include <ctype.h>
BOOL mHorda = NAO;
void ModoHorda( JOGO *jogo)
{
        char cam[100] = "Niveis/";
        char msg[ 100 ] = "Nome do nivel a ser carregado:";
        char nome[ 100 ] = { 0 };
        char add[ 2 ] = { '\0' , '\0' };




        do{
                BeginDrawing();
                        if( jogo->jogador.venceu ) UpdateMusicStream( jogo->Res.musica_final );
                        else UpdateMusicStream( musMenu );
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
                cam[ 7 + z ] = nome[ z ];

//        strcat( cam , nome );
        FILE* nivel = fopen( cam , "r" );
//        FILE* nivel = fopen( "Niveis/nivel0.txt" , "r" );
//        FILE* save = fopen( "Saves/MNarF" , "r" );

        if( nivel == NULL ){
                som_erro();
                return;
        }

        jogo->Res.Mapa = LoadTexture("Mapa/MapaModoHorda.png");

        ///GERAL
        jogo->jogador.saude = SAUDE_TOTAL_JOGADOR;
        jogo->jogador.vidas = VIDAS_INICIAIS_JOGADOR;
        jogo->jogador.pontos = 0;
        jogo->jogador.energia = ENERGIA_TOTAL;
        jogo->jogador.cor = WHITE;
        jogo->jogador.latencia = 0;
        jogo->jogador.DANO = 0;
        jogo->jogador.atualArma = 0;
        jogo->jogador.atualLevel = 0;
        jogo->faca.disponivel = 1;
        jogo->faca.ativo = false;
        jogo->faca.flag_colisao = 0;
        jogo->jogador.venceu = 0;

        /// Municao
        jogo->jogador.municao[ 0 ] = 25;
         jogo->qtd_tirosJog = 0;
        /// Configuracoes
        mHorda = 1;
        jogo->jogador.PosMundo.x = 1261;
        jogo->jogador.PosMundo.y =1112;
        jogo->atualSala = 10;

        jogo->salas[ 10 ].qtdPortas = 1;
        jogo->salas[ 10 ].qtdSpawns = 0;
        jogo->salas[ 10 ].qtdBaus = 0;
        jogo->salas[ 10 ].qtd_inimigos_liberar = 49;
        jogo->salas[ 10 ].qtd_inimigos_liberados = 0;

        jogo->salas[ 10 ].portas[ 0 ].DESTRANCADA = 0;
        jogo->salas[ 10 ].portas[ 0 ].rotac = 0;


        int i , j;
        i = j = 0;
        while( !feof( nivel ) ){
                switch( toupper( fgetc( nivel ) ) ){
                        case '\n':
                                i++;
                                j = 0;
                                break;
                        case 'J':
                                jogo->jogador.PosMundo = (Vector2){ 982 + j * 7 , 989 + i * 8 };
                                break;
                        case 'P':
                                jogo->salas[ 10 ].portas[ 0 ].pos = (Vector2){ 982 + j * 7 , 989 + i * 8 };
                                break;
                        case 'B':
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].imagem = jogo->Res.BauFechado;
//                                jogo->salas[ 10 ].baus.[ jogo->salas[ 10 ].qtdBaus ].origin ;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].posMapa.x = 982 + j * 7 ;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].posMapa.x = 989 + i * 8 ;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].posMapa.width = BAU_LARGURA;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].posMapa.height  = BAU_COMPRIMENTO;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].posTela.width = BAU_LARGURA * jogo->escalaGeral.x;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].posTela.height  = BAU_COMPRIMENTO * jogo->escalaGeral.y;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].src = (Rectangle){ 0 , 0 , jogo->Res.BauFechado.width , jogo->Res.BauFechado.height };
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].Rotac = 0;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].ABERTO = 0;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].QtdItens = 1;
                                jogo->salas[ 10 ].baus[ jogo->salas[ 10 ].qtdBaus ].CodItens[ 0 ] = nmrRand( 1 , 3 );
                                jogo->salas[ 10 ].qtdBaus += 1;
                                break;
                        case 'E':
                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].posMundo.x = 982 + j * 7 ;
                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].posMundo.y = 989 + i * 8 ;
                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].tipo = 0;
                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].inimigoTipo = 0;

                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].ATIVO = 1;

                                jogo->salas[ 10 ].qtdSpawns++;
                                break;
                        case 'M':
                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].posMundo.x = 982 + j * 7 ;
                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].posMundo.y = 989 + i * 8 ;
                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].tipo = 1;
                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].inimigoTipo = 1;

                                jogo->salas[ 10 ].spawns[ jogo->salas[ 10 ].qtdSpawns ].ATIVO = 1;

                                jogo->salas[ 10 ].qtdSpawns++;
                                break;
                }
                j++;
        }

        fclose( nivel );

        ShowCursor();   // Reexibir cursor

        while(  !IsGameOver( jogo )  &&  !IsKeyPressed( KEY_HOME )  && !IsEndGame( jogo )   &&  !jogo->VOLTARMENU ){
                AtualizaLevel( jogo );
                DesenhaLevel( jogo );
        }

        HideCursor();

}

typedef struct{
        char nome[ 10 ][ 100 ];
        int pnts[ 10 ];
}PONTUAC;

void HighScores( JOGO *jogo)
{
        /// HIGHSCORES
        PONTUAC pontuac;
        FILE* arq;
        arq = fopen( "HighScores/high_scores" , "rb+");

        fread( &pontuac , sizeof( PONTUAC ) , 1 , arq );

        fclose( arq );


        for( int z = FPS / 6 ; z ; z-- ){
                BeginDrawing();
                        if( jogo->jogador.venceu ) UpdateMusicStream( jogo->Res.musica_final );
                        else UpdateMusicStream( musMenu );

                        ClearBackground( BLACK );
                EndDrawing();
        }

        do{
                if( jogo->jogador.venceu ) UpdateMusicStream( jogo->Res.musica_final );
                else UpdateMusicStream( musMenu );
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
                        if( jogo->jogador.venceu ) UpdateMusicStream( jogo->Res.musica_final );
                        else UpdateMusicStream( musMenu );

                        ClearBackground( BLACK );
                EndDrawing();
        }

        do{
                BeginDrawing();
                        if( jogo->jogador.venceu ) UpdateMusicStream( jogo->Res.musica_final );
                        else UpdateMusicStream( musMenu );

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

        for( int tempo = 3 ; tempo ; tempo-- ){
                BeginDrawing();
                        ClearBackground( MAROON );
                EndDrawing();
        }

        do{
                BeginDrawing();
                        UpdateMusicStream( musMenu );
//                        ClearBackground( MAROON );
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
void som_erro( void ){
        Sound som = LoadSound("Som/acesso_negado.wav") ;
        PlaySound( som );
}
