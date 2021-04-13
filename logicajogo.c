
#include "logicajogo.h"

/**     Funcao AtualizaLevel(): Atualiza os dados do level atual
    */
void AtualizaLevel( Jogo *jogo)
{
//        AtualizaObjetos( &jogo );
//        AtualizaFundo( &jogo );
        AtualizaPosicao( jogo );
        AtualizaMira( jogo );
        AtualizaMapa( jogo );
//        AtualizaTiroERecarga( &jogo );
//        AtualizaArma( &jogo );
//        AtualizaInimigosT1( &jogo );

}
//##############################################################################


/**     Funcao AtualizaPosicao():
    */

#ifndef PASSO
#define PASSO 3.5 // Só pra lembrar. Alterar em definições
#endif

void AtualizaPosicao( Jogo *jogo)
{
//        float ESC = 1; // Razão entre o deslocamento na tela e no mapa


        //Alterando posição global no mapa
        if( IsKeyDown( KEY_W ) )
                jogo->jogador.YMapa -= PASSO;
//        {
//                jogo->jogador.py -= PASSO;//                jogo->jogador.YMapa -= PASSO / ESC ;
//        }

        if( IsKeyDown( KEY_S ) )
                jogo->jogador.YMapa += PASSO;
//        {
//                jogo->jogador.py += PASSO;//                jogo->jogador.YMapa += PASSO / ESC;
//        }

        if( IsKeyDown( KEY_D ) )
                jogo->jogador.XMapa += PASSO;
//        {
//                jogo->jogador.px += PASSO;//                jogo->jogador.XMapa += PASSO / ESC ;
//        }

        if( IsKeyDown( KEY_A ) )
                jogo->jogador.XMapa -= PASSO;
//        {
//                jogo->jogador.px -= PASSO;//                jogo->jogador.XMapa -= PASSO / ESC ;
//        }

        //Alterando posição na tela
        if( 1 )
        {
                jogo->jogador.px = jogo->tela.width / 2;
                jogo->jogador.py = jogo->tela.height / 2;
        }

}
//##############################################################################


/**     Funcao AtualizaMira():
    */


void AtualizaMira( Jogo *jogo)
{
        jogo->jogador.Rotac = ( 180 / PI ) * atan2( ( GetMouseY() - jogo->jogador.py ) ,  ( GetMouseX() - jogo->jogador.px ) );
}
//##############################################################################



/**     Funcao AtualizaMapa():
    */


void AtualizaMapa( Jogo *jogo)
{
        float novox = jogo->jogador.XMapa - jogo->tela.width / 2;  // Desloca coordenadas do desenho do fundo centrando o personagem
        float novoy = jogo->jogador.YMapa - jogo->tela.height / 2;

//        if( novox > jogo->salas[ jogo->atualSala ].limEsq  &&  novox < jogo->salas[ jogo->atualSala ].limDir )  // Confere se não ultrapassará os limites de vizualização esquero e direito
                jogo->tela.x = novox;

//        if( novoy > jogo->salas[ jogo->atualSala ].limSup  &&  novoy < jogo->salas[ jogo->atualSala ].limInf )
                jogo->tela.y = novoy;
}
//##############################################################################
