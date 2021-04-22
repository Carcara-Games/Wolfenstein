
#include "logicajogo.h"
#include "definicoes.h"
#include <math.h> // uso para atan2

/**     Funcao AtualizaLevel(): Atualiza os dados do level atual
    */
void AtualizaLevel( Jogo *jogo)
{
//        AtualizaObjetos( &jogo );
//        AtualizaFundo( &jogo );
        AtualizaPosicao( jogo );
        AtualizaMapa( jogo );
        AtualizaOrigin( jogo );
        EntraEmPortas( jogo );
        AtualizaMira( jogo );
        AtualizaFrameJogador( jogo );
//        AtualizaTiroERecarga( &jogo );
//        AtualizaArma( &jogo );
//        AtualizaInimigosT1( &jogo );

}
//##############################################################################


/**     Funcao AtualizaPosicao():
    */

void AtualizaPosicao( Jogo *jogo)
{
//        float ESC = 1; // Razao entre o deslocamento na tela e no mapa

        jogo->jogador.atualStatus = 0;
        //Alterando posicao global no mapa
        if( IsKeyDown( KEY_W ) )
                if( ChecaMov( *jogo , 0 , -PASSO ) )
                        jogo->jogador.PosMundo.y -= PASSO  ,  jogo->jogador.atualStatus = 1;

        if( IsKeyDown( KEY_S ) )
                if( ChecaMov( *jogo , 0 , PASSO ) )
                        jogo->jogador.PosMundo.y += PASSO , jogo->jogador.atualStatus = 1;

        if( IsKeyDown( KEY_D ) )
                if( ChecaMov( *jogo , PASSO , 0 ) )
                        jogo->jogador.PosMundo.x += PASSO , jogo->jogador.atualStatus = 1;

        if( IsKeyDown( KEY_A ) )
                if( ChecaMov( *jogo , -PASSO , 0 ) )
                        jogo->jogador.PosMundo.x -= PASSO , jogo->jogador.atualStatus = 1;

//        //Alterando posicao na tela
//        if( 1 )
//        {
//                jogo->jogador.PosTela.x = ( jogo->tela.width - jogo->jogador.PosTela.width) / 2;
//                jogo->jogador.PosTela.y = ( jogo->tela.height  -  jogo->jogador.PosTela.height ) / 2;
//        }
        //Alterando posicao na tela
        if( 1 )
        {
                jogo->jogador.PosTela.x = jogo->tela.width / 2;
                jogo->jogador.PosTela.y = jogo->tela.height / 2;
        }
}
//##############################################################################


/**     Funcao AtualizaMira():
    */

void AtualizaMira( Jogo *jogo)
{
        jogo->jogador.Rotac = ( 180 / PI ) * atan2( ( GetMouseY() - jogo->jogador.PosTela.y ) ,  ( GetMouseX() - jogo->jogador.PosTela.x ) );
}
//##############################################################################



/**     Funcao AtualizaMapa():
    */

void AtualizaMapa( Jogo *jogo)
{
        float novox = jogo->jogador.PosMundo.x - jogo->MapaDesenho.width / 2;  // Desloca coordenadas do desenho do fundo centrando o personagem
        float novoy = jogo->jogador.PosMundo.y - jogo->MapaDesenho.height / 2;

//        if( novox > jogo->salas[ jogo->atualSala ].limEsq  &&  novox < jogo->salas[ jogo->atualSala ].limDir )  // Confere se n�o ultrapassar� os limites de vizualiza��o esquero e direito
                jogo->MapaDesenho.x = novox;

//        if( novoy > jogo->salas[ jogo->atualSala ].limSup  &&  novoy < jogo->salas[ jogo->atualSala ].limInf )
                jogo->MapaDesenho.y = novoy;


}
//##############################################################################

/**     Funcao ChecaMov():
    */

BOOL ChecaMov( Jogo jogo , int varx , int vary )
{
        int i;

        for( i = 0 ; i < jogo.salas[ jogo.atualSala ].qtdZonas ; i++ )
                if( jogo.jogador.PosMundo.x + varx <= jogo.salas[ jogo.atualSala ].zonas[ i ].dir  &&  jogo.jogador.PosMundo.x + varx >= jogo.salas[ jogo.atualSala ].zonas[ i ].esq   )
                        if( jogo.jogador.PosMundo.y + vary <= jogo.salas[ jogo.atualSala ].zonas[ i ].inf  &&  jogo.jogador.PosMundo.y + vary >= jogo.salas[ jogo.atualSala ].zonas[ i ].sup )
                                return 1;

        return 0;
}
//##############################################################################



/**     Funcao EntraEmPortas():
    */

void EntraEmPortas( Jogo *jogo )
{
        int porta = ChecaPortas( *jogo );

        if( porta != -1 )
        {
                jogo->jogador.PosMundo.x = jogo->salas[ jogo->atualSala ].portas[ porta ].destino.x;
                jogo->jogador.PosMundo.y = jogo->salas[ jogo->atualSala ].portas[ porta ].destino.y;
                jogo->atualSala = jogo->salas[ jogo->atualSala ].portas[ porta ].alteraPSala;
                jogo->PASSAGEM = 1;
        }
        else
                jogo->PASSAGEM = 0;
}
//##############################################################################

/**     Funcao ChecaPortas():
    */

BOOL ChecaPortas( Jogo jogo )
{
        int i;
        int tol = 3 ;

        for( i = 0 ; i < jogo.salas[ jogo.atualSala ].qtdPortas ; i++ )
                if( jogo.salas[ jogo.atualSala ].portas[ i ].DESTRANCADA )
                        if( jogo.jogador.PosMundo.y <= jogo.salas[ jogo.atualSala ].portas[ i ].entrada.y + tol  &&  jogo.jogador.PosMundo.y >= jogo.salas[ jogo.atualSala ].portas[ i ].entrada.y - tol   )
                                if( jogo.jogador.PosMundo.x <= jogo.salas[ jogo.atualSala ].portas[ i ].entrada.x + tol  &&  jogo.jogador.PosMundo.x >= jogo.salas[ jogo.atualSala ].portas[ i ].entrada.x - tol   )
                                                return i;

        return -1;
}
//##############################################################################


///Função pausa

void pausa( int tempo)
{
        int i;

        for( i = tempo * FPS ; i ; i-- )
        {
                BeginDrawing();
                EndDrawing();
        }
}



///
void AtualizaOrigin( Jogo *jogo )
{
//        jogo->jogador.Origin.x = jogo->jogador.PosTela.x + jogo->jogador.PosTela.width / 2;
//        jogo->jogador.Origin.y = jogo->jogador.PosTela.y + jogo->jogador.PosTela.height / 2;
        jogo->jogador.Origin.x = jogo->jogador.PosTela.width / 2;
        jogo->jogador.Origin.y = jogo->jogador.PosTela.height / 2;
//        jogo->jogador.Origin.x = 0;
//        jogo->jogador.Origin.y = 0;


}



void AtualizaFrameJogador( Jogo *jogo )
{
        static int aux = 0;
        static int frame = 0;
        static int antStatus = 0;

        if( jogo->jogador.atualStatus != antStatus )
        {
                aux = 0;
                frame = 0;
        }


        aux++;

        if( aux == DIV_FPS_PER)
        {
                aux = 0;
                frame++;
                if( frame == jogo->armasDef.QTD_FRAMES[ jogo->jogador.atualArma ][ jogo->jogador.atualStatus ] - 1 )
                        frame = 0;
        }

        jogo->jogador.atualFrame = frame;
        antStatus = jogo->jogador.atualStatus;
}








