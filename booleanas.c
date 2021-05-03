
#include "booleanas.h"

/**     Funcao IsGameOver(): Retorn TRUE se jogador recebeu game over
    */

BOOL IsGameOver( JOGO jogo )
{
        if( !jogo.jogador.vidas )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsEndGame(): Retorn TRUE se jogador recebeu zerou o jogo
    */

//BOOL IsEndGame( JOGO jogo )
//{
//        if( jogo.atualLevel > MAXLEVEL )
//        {
//                return SIM;
//        }
//        else
//                return NAO;
//}
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
