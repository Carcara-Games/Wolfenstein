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
        void AtualizaOriginPes( Jogo *jogo );

        void AtualizaSrcPer( Jogo *jogo );
        void AtualizaSrcPes( Jogo *jogo );


        void AtualizaFrameJogador( Jogo *jogo );
        void AtualizaAtirar( Jogo *jogo );

        void IncrementaPosicao( Vector2 *pos , int addX , int addY );
        float Deslocamento( Vector2 posInicial ,  Vector2 posFinal );
        Vector2 SomaVectores( Vector2 vet1 , Vector2 vet2 );
        float modVector( Vector2 vet );
        float argVector( Vector2 vet );
        void AtualizaFramePes( Jogo *jogo );




#endif // __LOGICAJOGO_H_
