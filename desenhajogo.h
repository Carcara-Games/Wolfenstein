#ifndef __DESENHAJOGO_H_
#define __DESENHAJOGO_H_

        #include "estruturascomplexas.h"

        void DesenhaLevel( JOGO *jogo);
        void DesenhaMapa( JOGO *jogo);
        void DesenhaPes( JOGO *jogo);
        void DesenhaJogador( JOGO *jogo);
        void DesenhaPortas( JOGO *jogo);
        void DesenhaDebug( JOGO *jogo );
        void PassagemPorta( void );
        void DesenhaTiro(JOGO *jogo);

        void DesenhaObjetos( JOGO *jogo );
        void DesenhaItems( JOGO *jogo );
        void DesenhaBaus( JOGO *jogo );
        void DesenhaInimigos( JOGO *jogo);
        void DesenhaSpawns( JOGO *jogo);


#endif // __DESENHAJOGO_H_
