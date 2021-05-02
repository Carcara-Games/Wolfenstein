#ifndef __LOGICAJOGO_H_
#define __LOGICAJOGO_H_

        #include "structsgraficos.h"

        void AtualizaLevel( Jogo *jogo);
        void AtualizaPosicao( Jogo *jogo);
        void AtualizaMira( Jogo *jogo);
        void AtualizaMapa( Jogo *jogo);
        BOOL ChecaMov(Jogo jogo, Vector2 posAtual , int varx, int vary);
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
        int CalcularSpawnPerto( Jogo *jogo );
        float distancia( Vector2 pos0 , Vector2 posF );
        Vector2 SomaVectores( Vector2 vet1 , Vector2 vet2 );
        float modVector( Vector2 vet );
        float argVector( Vector2 vet );
        void AtualizaFramePes( Jogo *jogo );
        void AtualizaObjetos( Jogo *jogo );
        void AtualizaBaus( Jogo *jogo );

        void AtualizaInimigosT1(Jogo *jogo);
       Vector2 T1Perseguicao( Jogo *jogo , Vector2 posAtual , Vector2 alvo , int tipo );
        int sinalNumero( float nmr );
        int nmrRand( int mini , int maxi );
        Vector2 AtualizaPosTela( Jogo *jogo , Vector2 posMundo );
        int tipoAlinhamentoCheck( Vector2 posAtual , Vector2 alvo );

        void GeraInimigos( Jogo *jogo );

        void AtualizaFrameT1(Jogo *jogo);
        void AtualizaAtaqueT1(Jogo *jogo);
        void AtualizaDanoJogador( Jogo *jogo );
        void AtualizaRotacT1(Jogo *jogo);

        BOOL mesmaZona( Jogo *jogo , Vector2 pos1 , Vector2 pos2 );




#endif // __LOGICAJOGO_H_
