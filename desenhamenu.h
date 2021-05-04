#ifndef __DESENHAMENU_H_
#define __DESENHAMENU_H_

        #include "estruturascomplexas.h"
        #include "logicamenu.h"

        void NomeWolfenEntrada( JOGO *jogo , int selecao  );
        void DesenhaMenuPrincipal(JOGO *jogo, int selecao);
        void DesenhaMenuDificuldade( JOGO *jogo , int selecao );
        void DesenharObrigado( void );
        int CentraTextoXEX( Font fonte , char *texto , float fontsize , float space);
        int CentraTextoX( char *texto , int fontsize );
        void DesenharConfirmarSair( int selecao , JOGO *jogo );
        void DesenhaSobre( JOGO jogo);



#endif // __DESENHAMENU_H_
