
#include "booleanas.h"

/**     Funcao IsGameOver(): Retorn TRUE se jogador recebeu game over
    */

BOOL IsGameOver( JOGO* jogo )
{
        if( !jogo->jogador.vidas )
        {
                PlaySound( LoadSound("Som/game_over_som.mp3") );
                for( int i = 5 ; i ; i--){
                        BeginDrawing();
                                DrawTexturePro( LoadTexture("Menu_Imagens/game_over.png") , (Rectangle){ 0 , 0 , 1366 , 768 } ,  jogo->tela , (Vector2){ 0 , 0 } , 0 , WHITE );
                        EndDrawing();
                }
                for( int i = 4 * FPS ; i ; i--){
                        BeginDrawing();
                        EndDrawing();
                }

                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsEndGame(): Retorn TRUE se jogador recebeu zerou o jogo
    */

BOOL IsEndGame( JOGO* jogo )
{
        if( jogo->jogador.venceu )
                return SIM;
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsVoltarMenu(): Retorn TRUE se jogador quer volar para o menu principal
    */

BOOL IsVoltarMenu( JOGO jogo )
{
        if( jogo.VOLTARMENU )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsLevelEnd(): Retorn TRUE se jogador terminou level
    */

//BOOL IsLevelEnd( JOGO jogo )
//{
//        if( jogo.dadosLevel.TERMINADO )
//        {
//                return SIM;
//        }
//        else
//                return NAO;
//}
//##############################################################################


/**     Funcao TestaLimVizua():
    */
BOOL TestaLimVizual( JOGO jogo )
{
        return SIM;
}

//##############################################################################
