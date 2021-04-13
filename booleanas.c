
#include "booleanas.h"

/**     Funcao IsGameOver(): Retorn TRUE se jogador recebeu game over
    */

BOOL IsGameOver( Jogo jogo )
{
        if( !jogo.jogador.vidas && !jogo.jogador.VIVO )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsEndGame(): Retorn TRUE se jogador recebeu zerou o jogo
    */

BOOL IsEndGame( Jogo jogo )
{
        if( jogo.Level > MAXLEVEL )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################



/**     Funcao IsVoltarMenu(): Retorn TRUE se jogador quer volar para o menu principal
    */

BOOL IsVoltarMenu( Jogo jogo )
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

BOOL IsLevelEnd( Jogo jogo )
{
        if( jogo.dadosLevel.TERMINADO )
        {
                return SIM;
        }
        else
                return NAO;
}
//##############################################################################


/**     Funcao TestaLimVizua():
    */
BOOL TestaLimVizual( Jogo jogo )
{
        return SIM;
}

//##############################################################################
