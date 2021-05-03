#ifndef __LOGICAJOGO_H_
#define __LOGICAJOGO_H_

        #include "structsgraficos.h"

        void AtualizaLevel( JOGO *jogo);
        void AtualizaPosicao( JOGO *jogo);
        void AtualizaMira( JOGO *jogo);
        void AtualizaMapa( JOGO *jogo);
        BOOL ChecaMov(JOGO jogo, Vector2 posAtual , int varx, int vary);
        int ChecaPortas( JOGO jogo );
        void EntraEmPortas( JOGO *jogo );
        void pausa( int tempo);

        void AtualizaOrigin( JOGO *jogo );
        void AtualizaOriginPes( JOGO *jogo );

        void AtualizaSrcPer( JOGO *jogo );
        void AtualizaSrcPes( JOGO *jogo );


        void AtualizaFrameJogador( JOGO *jogo );
        void AtualizaAtirar( JOGO *jogo );

        void IncrementaPosicao( Vector2 *pos , int addX , int addY );
        float Deslocamento( Vector2 posInicial ,  Vector2 posFinal );
        int CalcularSpawnPerto( JOGO *jogo );
        float distancia( Vector2 pos0 , Vector2 posF );
        Vector2 SomaVectores( Vector2 vet1 , Vector2 vet2 );
        float modVector( Vector2 vet );
        float argVector( Vector2 vet );
        void AtualizaFramePes( JOGO *jogo );
        void AtualizaObjetos( JOGO *jogo );
        void AtualizaBaus( JOGO *jogo );

        void AtualizaInimigosT1(JOGO *jogo);
       Vector2 T1Perseguicao( JOGO *jogo , Vector2 posAtual , Vector2 alvo , int tipo );
        int sinalNumero( float nmr );
        int nmrRand( int mini , int maxi );
        Vector2 AtualizaPosTela( JOGO *jogo , Vector2 posMundo );
        int tipoAlinhamentoCheck( Vector2 posAtual , Vector2 alvo );

        void GeraInimigos( JOGO *jogo );

        void AtualizaFrameT1(JOGO *jogo);
        void AtualizaAtaqueT1(JOGO *jogo);
        void AtualizaDanoJogador( JOGO *jogo );
        void AtualizaRotacT1(JOGO *jogo);

        BOOL mesmaZona( JOGO *jogo , Vector2 pos1 , Vector2 pos2 );




#endif // __LOGICAJOGO_H_
