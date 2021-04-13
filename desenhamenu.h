#ifndef __DESENHAMENU_H_
#define __DESENHAMENU_H_

        #include "structsgraficos.h"
        #include "logicamenu.h"

        void NomeWolfenEntrada( Jogo *jogo , int selecao  );
        void DesenhaMenuPrincipal(Jogo *jogo, int selecao);
        void DesenhaMenuDificuldade( Jogo *jogo , int selecao );
        void DesenharObrigado( void );
        int CentraTextoXEX( Font fonte , char *texto , float fontsize , float space);
        int CentraTextoX( char *texto , int fontsize );
        void DesenharConfirmarSair( int selecao , Jogo *jogo );
        void DesenhaSobre( Jogo jogo);



#endif // __DESENHAMENU_H_
