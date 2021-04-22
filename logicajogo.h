#ifndef __LOGICAJOGO_H_
#define __LOGICAJOGO_H_

        #include "structsgraficos.h"

        void AtualizaLevel( Jogo *jogo);
        void AtualizaPosicao( Jogo *jogo);
        void AtualizaMira( Jogo *jogo);
        void AtualizaMapa( Jogo *jogo);
        BOOL ChecaMov( Jogo jogo , int varx , int vary );
        int ChecaPortas( Jogo jogo );
        void EntraEmPortas( Jogo *jogo );
        void pausa( int tempo);
        void AtualizaOrigin( Jogo *jogo );
        void AtualizaFrameJogador( Jogo *jogo );



#endif // __LOGICAJOGO_H_
