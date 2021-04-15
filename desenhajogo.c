
#include "desenhajogo.h"

/**     Funcao DesenhaMapa():
    */
void DesenhaMapa( Jogo jogo)
{
        const float ESC = 4.5;
        Rectangle  screen;
        Rectangle  mapa;
        Vector2 pos;

        mapa.width = jogo.tela.width / ESC;
        mapa.height = jogo.tela.height / ESC;
        mapa.x = jogo.tela.x;
        mapa.y = jogo.tela.y;

        screen.width = jogo.tela.width;
        screen.height = jogo.tela.height;
        screen.x = 0;
        screen.y = 0;

        pos.x = 0;
        pos.y = 0;

       DrawTexturePro( jogo.Res.Mapa , mapa , screen , pos , 0 , WHITE );

}
//##############################################################################


/**     Funcao DesenhaJogador():
    */
void DesenhaJogador( Jogo jogo)
{
        Rectangle ret;
        Vector2 vet;

        ret.height = 30;
        ret.width = 60;
        ret.x = jogo.jogador.px - ret.width / 2;
        ret.y = jogo.jogador.py - ret.height / 2;

        // vetor para origem centralizada de rotacao mouse
        vet.x = ret.width/2;
        vet.y = ret.height/2;


        DrawRectanglePro( ret  , vet , jogo.jogador.Rotac  , BLUE );
//        DrawRectanglePro( ret  , vet , 0 , BLUE );
//        DrawRectangle( ret.x , ret.y , ret.width , ret.height , GREEN);

}
//##############################################################################



/**     Funcao DesenhaPortas():
    */

void DesenhaPortas( Jogo jogo)
{
//        int i;

//        for( i = 0 ; i < jogo.dadosLevel.salas[ i ].qtdPortas ; i++ )
//                DrawTextureEx( jogo.Res.Portas , jogo.dadosLevel.salas[ i ].portas.pos , jogo.dadosLevel.salas[ i ].portas.rotac , 1 , WHITE );
}
//##############################################################################


/**     Funcao DesenhaLevel(): Desenha o level atual
    */
void DesenhaLevel( Jogo jogo)
{
        BeginDrawing();
                DesenhaMapa( jogo );
                //DesenhaPortas( jogo );
                DesenhaJogador( jogo );

        EndDrawing();
}
//##############################################################################
