
#include "logicajogo.h"
#include "definicoes.h"
#include "fisica.h"
#include <math.h>

/**     Funcao AtualizaLevel(): Atualiza os dados do level atual
    */
void AtualizaLevel(JOGO *jogo)
{
        AtualizaLevelAtual( jogo );

        AtualizaMira(jogo);
        //        AtualizaArma( &jogo );
        AtualizaFaca(jogo);
        AtualizaFacaColisao(jogo);
        AtualizaTirosJogador( jogo );
        AtualizaColisaoTirosJogador( jogo );
        //        AtualizaRecarga( &jogo );

        AtualizaPosicao(jogo);
        AtualizaMapa(jogo);

        //        AtualizaSrcPer( jogo );
        AtualizaSrcPes(jogo);
        AtualizaOrigin(jogo);
        AtualizaOriginPes(jogo);

        EntraEmPortas(jogo);
        abrirBaus( jogo );
        destrancarPortas( jogo );
        AtualizaAtirar(jogo);


        AtualizaFrameJogador( jogo );
        AtualizaFramePes( jogo );
        AtualizaFrameT1( jogo );
//        AtualizaFrameT0( jogo );

        AtualizaObjetos( jogo );

        AtualizaInimigosT1( jogo );
        AtualizaRotacT1( jogo );
        AtualizaAtaqueT1( jogo );

        AtualizaDanoJogador( jogo );
        AtualizaDanoInimigo( jogo );


        if( IsKeyPressed( KEY_P ) )
                Pause( jogo , 0 );


        GeraInimigos( jogo );


}
//##############################################################################


/**     Funcao AtualizaObjetos():
    */
void AtualizaObjetos( JOGO *jogo ){
        AtualizaBausDesenho( jogo );
        AtualizaItems( jogo );


}
//##############################################################################



/** \brief Mudar estado de BAUS para aberto e dropar items
 *
 * \param *JOGO
 *
 */
void abrirBaus( JOGO *jogo ){
        int i , j;

        for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtdBaus ; i++)
//                if( Deslocamento( jogo->jogador.PosMundo , (Vector2){ jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.x , jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.y} ) < DIST_ABRIR_BAUS )
                if( CheckCollisionPointRec( (Vector2){ jogo->jogador.PosMundo.x + DIST_ABRIR_BAUS * cos( ( PI / 180 ) * jogo->jogador.Rotac ) , jogo->jogador.PosMundo.y + DIST_ABRIR_BAUS * sin( ( PI / 180 ) * jogo->jogador.Rotac ) } ,  jogo->salas[ jogo->atualSala ].baus[ i ].posMapa ) )
                        if( !jogo->salas[ jogo->atualSala ].baus[ i ].ABERTO )
                                if( IsKeyPressed( KEY_E ) ){
                                        jogo->salas[ jogo->atualSala ].baus[ i ].ABERTO = 1;

                                        for( j = 0 ; j < jogo->salas[ jogo->atualSala ].baus[ i ].QtdItens ; j++ ){
                                                jogo->items[ jogo->qtd_items_liberados ].recolhido =  NAO;
//                                                jogo->items[ jogo->qtd_items_liberados ].posMundo.x =  jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.x + jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.width / 2 + (DIST_DROP + j * DELTA_DIST_DROP ) * sin( jogo->salas[ jogo->atualSala ].baus[ i ].Rotac * ( PI / 180 ) );
//                                                jogo->items[ jogo->qtd_items_liberados ].posMundo.y =  jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.y + (DIST_DROP + j * DELTA_DIST_DROP ) * cos( jogo->salas[ jogo->atualSala ].baus[ i ].Rotac * ( PI / 180 ) );
                                                jogo->items[ jogo->qtd_items_liberados ].posMundo.x =  jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.x + jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.width / 2 ;
                                                jogo->items[ jogo->qtd_items_liberados ].posMundo.y =  jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.y + jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.height / 2 ;

                                                if( jogo->salas[ jogo->atualSala ].baus[ i ].Rotac  == 90  ||  jogo->salas[ jogo->atualSala ].baus[ i ].Rotac  == -90 ){
                                                        jogo->items[ jogo->qtd_items_liberados ].posMundo.x +=  -jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.width / 2 + jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.height / 2 ;
                                                        jogo->items[ jogo->qtd_items_liberados ].posMundo.y += -jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.height / 2 + jogo->salas[ jogo->atualSala ].baus[ i ].posMapa.width / 2 ;
                                                        if( jogo->salas[ jogo->atualSala ].baus[ i ].Rotac  == 90 ){
                                                                jogo->items[ jogo->qtd_items_liberados ].posMundo.x -= 5 * REF_TELA_LARG / jogo->tela.width  ;
                                                        }

//                                                        jogo->items[ jogo->qtd_items_liberados ].posMundo.y += - (jogo->salas[ jogo->atualSala ].baus[ i ].QtdItens - 1 - i ) * DELTA_DIST_DROP ;

                                                }


                                                if( jogo->salas[ jogo->atualSala ].baus[ i ].Rotac  == 180 )
                                                        jogo->items[ jogo->qtd_items_liberados ].posMundo.y -= 5 * REF_TELA_ALT / jogo->tela.height  ;


                                                jogo->items[ jogo->qtd_items_liberados ].codItem =  jogo->salas[ jogo->atualSala ].baus[ i ].CodItens[ j ];
                                                jogo->qtd_items_liberados++;
                                        }

                                        jogo->salas[ jogo->atualSala ].baus[ i ].ABERTO = 1;
                                        jogo->salas[ jogo->atualSala ].baus[ i ].imagem = jogo->Res.BauAberto;
                                }


}


/** \brief Mudar estado de PORTAS para destrancada
 *
 * \param *JOGO
 *
 */
void destrancarPortas( JOGO *jogo ){
        if( jogo->salas[ jogo->atualSala ].qtd_abatidos >= jogo->salas[ jogo->atualSala ].qtd_inimigos_liberar )
                jogo->salas[ jogo->atualSala ].portas[ jogo->salas[ jogo->atualSala ].porta_a_ser_liberada ].DESTRANCADA = 1;

}


/**     Funcao AtualizaBaus():
    */
void AtualizaBausDesenho( JOGO *jogo ){
        int bau;

        for( bau = 0 ; bau < jogo->salas[ jogo->atualSala ].qtdBaus ; bau++ ){
                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.x = ( jogo->salas[ jogo->atualSala ].baus[ bau ].posMapa.x -  jogo->MapaDesenho.x ) * jogo->escalaGeral.x;
                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.y = ( jogo->salas[ jogo->atualSala ].baus[ bau ].posMapa.y -  jogo->MapaDesenho.y ) * jogo->escalaGeral.y;

//                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.x = 500;
//                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.y = 400;

                // Corrigindo deslocamento causado pelo origin necessario para a rotacao do bau
                switch( (int)jogo->salas[ jogo->atualSala ].baus[ bau ].Rotac ){
                        case 90:
                                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.x += ( jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.width / 2 ) ;
                                break;
                        case -90:
//                                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.x += ( jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.width / 2 ) ;
                                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.y += ( jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.width / 2 ) ;
                                break;
                        case 180:
                                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.x += ( jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.width  );
                                jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.y += ( jogo->salas[ jogo->atualSala ].baus[ bau ].posTela.width / 2 );
                                break;
                        case 0:
                                break;

                }
        }

}
//##############################################################################



/**     Funcao AtualizaPosicao():
    */

void AtualizaPosicao(JOGO *jogo)
{
        Vector2 desloc = (Vector2){0, 0}; // Deslocamento
        Vector2 posAtual = jogo->jogador.PosMundo; // Deslocamento

        int movimentoTipo;
        int status = 0;
        int ang;                         // Desvio entre a fronte do jogador e o sentido de deslocamento
        const int tol = TOL_MOV_LATERAL; // Tolerancia angular para se considerar o movimento como lateral

        //Velocidade - Se usuario pressionar ctrl a velocidade aumenta
        float passo = PASSO;

        if( jogo->jogador.energia ){
                if ( IsKeyDown( KEY_LEFT_CONTROL ) ){
                        passo = PASSO_CORRENDO;
                        movimentoTipo = 2;
                        jogo->jogador.energia--;
                }
                else{
                        status = 1;
                        movimentoTipo = 1;
                }

        }
        else
        {
                status = 1;
                movimentoTipo = 1;
        }

        //Alterando posicao global no mapa
        if (IsKeyDown(KEY_W))
                if (ChecaMov(*jogo, posAtual , 0, -passo))
                        desloc.y -= passo;

        if (IsKeyDown(KEY_S))
                if (ChecaMov(*jogo, posAtual , 0, passo))
                        desloc.y += passo;

        if (IsKeyDown(KEY_D))
                if (ChecaMov(*jogo, posAtual , passo, 0))
                        desloc.x += passo;

        if (IsKeyDown(KEY_A))
                if (ChecaMov(*jogo, posAtual , -passo, 0))
                        desloc.x -= passo;

        ang = argVector(desloc) - jogo->jogador.Rotac;
        // Calculando tipo de movimento
        if (!modVector(desloc))
        {
                jogo->jogador.atualStatus = 0;
                jogo->jogador.atualMovTipo = 0;
                return;
        }
        else
        {
                if (ang >= -90 - tol && ang <= -90 + tol)
                        movimentoTipo = 3; // Movimento Lateral para a Esquerda
                if (ang >= 90 - tol && ang <= 90 + tol)
                        movimentoTipo = 4; // Movimento Lateral para a Direita
        }

        //Corrigindo movimento diagonal
        if (modVector(desloc) > passo)
        {
                desloc.x /= sqrt(2);
                desloc.y /= sqrt(2);
        }

        // Atribuicao
        jogo->jogador.PosMundo = SomaVectores(jogo->jogador.PosMundo, desloc);
        jogo->jogador.atualStatus = status;
        jogo->jogador.atualMovTipo = movimentoTipo;

        //        //Alterando posicao na tela
        //        if( 1 )
        //        {
        //                jogo->jogador.PosTela.x = ( jogo->tela.width - jogo->jogador.PosTela.width) / 2;
        //                jogo->jogador.PosTela.y = ( jogo->tela.height  -  jogo->jogador.PosTela.height ) / 2;
        //        }
        //Alterando posicao na tela
        if (1)
        {
                ///Personagemg
//                jogo->jogador.PosTela.x =  jogo->escalaGeral.x * ( jogo->jogador.PosMundo.x - jogo->MapaDesenho.x );
//                jogo->jogador.PosTela.y =  jogo->escalaGeral.y * ( jogo->jogador.PosMundo.y - jogo->MapaDesenho.y );
                jogo->jogador.PosTela.x = jogo->tela.width / 2;
                jogo->jogador.PosTela.y = jogo->tela.height / 2;
                ///Pes
                //                jogo->jogador.PosTelaPes.x =  ( jogo->jogador.PosTela.x - jogo->jogador.PosTelaPes.width ) / 2;
                //                jogo->jogador.PosTelaPes.y =  ( jogo->jogador.PosTela.y -  jogo->jogador.PosTelaPes.height ) / 2;
                //                jogo->jogador.PosTelaPes.x =  jogo->jogador.PosTela.x + DELTA_PES * cos( jogo->jogador.Rotac );
                //                jogo->jogador.PosTelaPes.y =  jogo->jogador.PosTela.y - DELTA_PES * sin( jogo->jogador.Rotac);
                //
                jogo->jogador.PosTelaPes.x = jogo->jogador.PosTela.x;
                jogo->jogador.PosTelaPes.y = jogo->jogador.PosTela.y;
        }
}
//##############################################################################








/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void IncrementaPosicao(Vector2 *pos, int addX, int addY)
{
        pos->x += addX;
        pos->y += addY;
}







/**     Funcao AtualizaMira():
    */

void AtualizaMira(JOGO *jogo)
{
        //O angulo formado entre a linha imaginaria do centro de rotacao do personagem e o centro de mira que fica na ponta da arma
        //        const int delta[ 3/*QTD_ARMAS*/ ] = { 00 , 25 };
        //
        //        // A distancia horizontal entre o centro de rotacao e o centro de mira
        //        const int deltaX[ 3/*QTD_ARMAS*/ ] = { jogo->Res.Per[0][0][0].width/ DESVIO_MIRA , jogo->Res.Per[1][0][0].width / DESVIO_MIRA , 0};
        //
        //         // A distancia horizontal entre o centro de rotacao e o centro de mira
        //        const int deltaY[ 3/*QTD_ARMAS*/ ] = { jogo->Res.Per[0][0][0].height / DESVIO_MIRA ,  jogo->Res.Per[1][0][0].height / DESVIO_MIRA,0 };
        //        const int arm = jogo->jogador.atualArma;
        //        const int angulo =  jogo->jogador.Rotac;
        //
        //        Vector2 CENTRO_DE_MIRA; // CENTRO_DE_MIRA do PERSONAGEM no mapa que varia com a rotacao inclusive
        //        int difY; // Diferenca em distancia de tela do ponto CENTRO_DE_MIRA do PERSONAGEM no mapa e o ponteiro do mouse
        //        int difX;

        //        CENTRO_DE_MIRA.x =
        //        CENTRO_DE_MIRA.y =
        //
        //        difX =
        //        difY =
        //        const int tanangulo = ( 180 / PI ) * tan( jogo->jogador.Rotac );

        jogo->jogador.Rotac = (180 / PI) * atan2((GetMouseY() - jogo->jogador.PosTela.y), (GetMouseX() - jogo->jogador.PosTela.x));
        //        jogo->jogador.Rotac = ( 180 / PI ) * atan2( ( GetMouseY() - jogo->jogador.PosTela.y - deltaY[ arm ] ) ,  ( GetMouseX() - jogo->jogador.PosTela.x - deltaX[ arm ] ) ) - delta[ arm ];
        //        jogo->jogador.Rotac = ( 180 / PI ) * atan2( ( GetMouseY() - jogo->jogador.PosTela.y + deltaY[ arm ] ) ,  ( GetMouseX() - jogo->jogador.PosTela.x + deltaX[ arm ] ) );
        //        jogo->jogador.Rotac = ( 180 / PI ) * atan2( ( GetMouseY() - jogo->jogador.PosTela.y + deltaY[ arm ] * tanangulo ) ,  ( GetMouseX() - jogo->jogador.PosTela.x + deltaX[ arm ] * tanangulo ) ) - delta[ arm ] ;
}
//##############################################################################

/**     Funcao AtualizaMapa():
    */

void AtualizaMapa(JOGO *jogo)
{
        float novox = jogo->jogador.PosMundo.x - jogo->MapaDesenho.width / 2; // Desloca coordenadas do desenho do fundo centrando o personagem
        float novoy = jogo->jogador.PosMundo.y - jogo->MapaDesenho.height / 2;

        //        if( novox > jogo->salas[ jogo->atualSala ].limEsq  &&  novox < jogo->salas[ jogo->atualSala ].limDir )  // Confere se n�o ultrapassar� os limites de vizualiza��o esquero e direito
        jogo->MapaDesenho.x = novox;

        //        if( novoy > jogo->salas[ jogo->atualSala ].limSup  &&  novoy < jogo->salas[ jogo->atualSala ].limInf )
        jogo->MapaDesenho.y = novoy;
}
//##############################################################################

/**     Funcao ChecaMov():
    */

BOOL ChecaMov(JOGO jogo, Vector2 posAtual , int varx, int vary)
{
        int i;
        Vector2 destino = SomaVectores( posAtual , (Vector2){ varx , vary } );

        for (i = 0; i < jogo.salas[jogo.atualSala].qtdZonas; i++)
                if (CheckCollisionPointRec(destino, jogo.salas[jogo.atualSala].zonas[i]))
                        return 1;

        return 0;
}
//##############################################################################

/**     Funcao EntraEmPortas():
    */

void EntraEmPortas(JOGO *jogo)
{
        int porta = ChecaPortas(*jogo);

        if (porta != -1)
        {
                int addX = -SALTO_PORTA * sin((PI / 180) * jogo->salas[jogo->atualSala].portas[porta].rotac);
                int addY = -SALTO_PORTA * cos((PI / 180) * jogo->salas[jogo->atualSala].portas[porta].rotac);

                jogo->jogador.PosMundo.x = jogo->salas[jogo->atualSala].portas[porta].pos.x + addX;
                jogo->jogador.PosMundo.y = jogo->salas[jogo->atualSala].portas[porta].pos.y + addY;
                jogo->atualSala = jogo->salas[jogo->atualSala].portas[porta].alteraPSala;
                jogo->PASSAGEM = 1;
        }
        else
                jogo->PASSAGEM = 0;
}
//##############################################################################

/**     Funcao ChecaPortas():
    */

BOOL ChecaPortas(JOGO jogo)
{
        int i;

        for (i = 0; i < jogo.salas[jogo.atualSala].qtdPortas; i++)
                if (jogo.salas[jogo.atualSala].portas[i].DESTRANCADA)
                        if (jogo.jogador.PosMundo.y <= jogo.salas[jogo.atualSala].portas[i].pos.y + TOL_ENTRAR_PORTAS && jogo.jogador.PosMundo.y >= jogo.salas[jogo.atualSala].portas[i].pos.y - TOL_ENTRAR_PORTAS)
                                if (jogo.jogador.PosMundo.x <= jogo.salas[jogo.atualSala].portas[i].pos.x + TOL_ENTRAR_PORTAS && jogo.jogador.PosMundo.x >= jogo.salas[jogo.atualSala].portas[i].pos.x - TOL_ENTRAR_PORTAS)
                                        return i;

        return -1;
}
//##############################################################################

///Função pausa

void pausa(float tempo)
{
        int i;

        for ( i = floor( tempo * FPS ); i; i--)
        {
                BeginDrawing();
                EndDrawing();
        }
}

///
void AtualizaOrigin(JOGO *jogo)
{
        if (jogo->jogador.atualArma == 0)
        {
                jogo->spriteDef.Origin.x = jogo->jogador.PosTela.width / 2;
                jogo->spriteDef.Origin.y = jogo->jogador.PosTela.height / 2;
        }

        if (jogo->jogador.atualArma == 1)
        {
                jogo->spriteDef.Origin.x = 2 * jogo->jogador.PosTela.width / 3;
                jogo->spriteDef.Origin.y = 2 * jogo->jogador.PosTela.height / 3;
        }
}

///
void AtualizaOriginPes(JOGO *jogo)
{
        /*if( jogo->jogador.atualMovTipo == 0 )*/ {
                jogo->spriteDef.OriginPes.x = jogo->jogador.PosTelaPes.width / 2;
                jogo->spriteDef.OriginPes.y = jogo->jogador.PosTelaPes.height / 2;
        }
}




///
void AtualizaFrameJogador(JOGO *jogo)
{
        static int aux = 0;
        static int frame = 0;
        static int antStatus = 0;
        static int flagTiro = 0;

        //Teste Para Debug
        jogo->jogador.testeFlagTiro = flagTiro;

        //melhorar depois
        //Caso atire e preciso terminar o ciclo dos frames
        if (jogo->jogador.atualStatus == 2 || flagTiro)
        {
                if (!flagTiro)
                {
                        flagTiro = 1;
                        frame = 0;
                        aux = 0;
                }
                else
                        aux++;

                jogo->jogador.atualStatus = 2;

                if (aux == DIV_FPS_PER)
                {
                        aux = 0;
                        frame++;
                }

                jogo->spriteDef.atualFrame = frame;

                if (frame == 2)
                {
                        frame = 0;
                        flagTiro = 0;
                }
                antStatus = jogo->jogador.atualStatus;
                return;
        }

        if (jogo->jogador.atualStatus != antStatus)
        {
                aux = 0;
                frame = 0;
        }

        aux++;

        if (aux == DIV_FPS_PER)
        {
                aux = 0;
                frame++;
                jogo->spriteDef.atualFrame = frame;
                if (frame == jogo->spriteDef.QTD_FRAMES[jogo->jogador.atualArma][jogo->jogador.atualStatus] - 1)
                        frame = 0;
        }

        antStatus = jogo->jogador.atualStatus;
}

///
void AtualizaFramePes(JOGO *jogo)
{
        static int aux = 0;
        static int frame = 0;
        static int antTipoMovimento = 0;

        //Reniciar ciclo se alterar tipo de movimento
        if (jogo->jogador.atualMovTipo != antTipoMovimento)
        {
                aux = 0;
                frame = 0;
        }

        aux++;

        if (aux == DIV_FPS_PER)
        {
                aux = 0;
                frame++;

                if (frame == jogo->spriteDef.QTD_FRAMES_PES[jogo->jogador.atualMovTipo])
                        frame = 0;
        }

        //Atribuicao
        jogo->spriteDef.atualFramePes = frame;

        antTipoMovimento = jogo->jogador.atualMovTipo;
}

///
void AtualizaAtirar(JOGO *jogo)
{
        //Pistola
        if (jogo->jogador.atualArma == 0)
        {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        if( jogo->jogador.municao[ 0 ] ){
                                jogo->jogador.atualStatus = 2;
                                jogo->jogador.municao[ 0 ]--;
                        }
                }

        }


        //Smg
        if (jogo->jogador.atualArma == 1)
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
                        jogo->jogador.atualStatus = 2;
}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void AtualizaFrameT1(JOGO *jogo)
{
        static int aux[ QTD_MAX_T1_SALA ] = { 0 };
        static int frame[ QTD_MAX_T1_SALA ] = { 0 };
        static int antStatus = 0;
        static int flagTiro[ QTD_MAX_T1_SALA ] =  { 0 };

        int ini;
        int aSal = jogo->atualSala;

        for( ini = 0 ; ini < jogo->salas[ aSal ].qtd_inimigos_liberados ; ini++)
                if( jogo->salas[ aSal ].inimigos[ ini ].VIVO ){
                        //Caso atire e preciso terminar o ciclo dos frame[ ini ]s
                        if ( jogo->salas[ aSal ].inimigos[ ini ].atacando  || flagTiro[ ini ])
                        {
                                if (!flagTiro[ ini ])
                                {
                                        flagTiro[ ini ] = 1;
                                        frame[ ini ] = 0;
                                        aux[ ini ] = 0;
                                }
                                else
                                        aux[ ini ]++;

                                jogo->salas[ aSal ].inimigos[ ini ].atacando = 1;

                                if (aux[ ini ] == DIV_FPS_T1 )
                                {
                                        aux[ ini ] = 0;
                                        frame[ ini ]++;
                                }

                                jogo->spriteDef.atualFrame_T1[ ini ] = frame[ ini ];

                                if ( frame[ ini ] >= jogo->spriteDef.QTD_FRAMES_T1[ 1 ] - 1 )
                                {
                                        frame[ ini ] = 0;
                                        flagTiro[ ini ] = 0;
                                }
                                antStatus = jogo->salas[ aSal ].inimigos[ ini ].atacando;
                                return;
                        }

                        if ( jogo->salas[ aSal ].inimigos[ ini ].atacando != antStatus)
                        {
                                aux[ ini ] = 0;
                                frame[ ini ] = 0;
                        }

                        aux[ ini ]++;

                        if ( aux[ ini ] == DIV_FPS_T1 )
                        {
                                aux[ ini ] = 0;
                                frame[ ini ]++;
                                jogo->spriteDef.atualFrame_T1[ ini ] = frame[ ini ];
                                if (frame[ ini ] == jogo->spriteDef.QTD_FRAMES_T1[ jogo->salas[ aSal ].inimigos[ ini ].atacando ] - 1)
                                        frame[ ini ] = 0;
                        }

                        antStatus = jogo->salas[ aSal ].inimigos[ ini ].atacando;
                }
}

//void AtualizaFrameT0(JOGO *jogo)
//{
//        static int aux[ QTD_MAX_T1_SALA ] = { 0 };
//        static int frame[ QTD_MAX_T1_SALA ] = { 0 };
//        static int antStatus = 0;
//        static int flagTiro[ QTD_MAX_T1_SALA ] =  { 0 };
//
//        int ini;
//        int aSal = jogo->atualSala;
//
//        for( ini = 0 ; ini < jogo->salas[ aSal ].qtd_inimigos_liberados ; ini++)
//                if( jogo->salas[ aSal ].inimigos[ ini ].VIVO ){
//                        //Caso atire e preciso terminar o ciclo dos frame[ ini ]s
//                        if ( jogo->salas[ aSal ].inimigos[ ini ].atacando  || flagTiro[ ini ])
//                        {
//                                if (!flagTiro[ ini ])
//                                {
//                                        flagTiro[ ini ] = 1;
//                                        frame[ ini ] = 0;
//                                        aux[ ini ] = 0;
//                                }
//                                else
//                                        aux[ ini ]++;
//
//                                jogo->salas[ aSal ].inimigos[ ini ].atacando = 1;
//
//                                if (aux[ ini ] == DIV_FPS_T1 )
//                                {
//                                        aux[ ini ] = 0;
//                                        frame[ ini ]++;
//                                }
//
//                                jogo->spriteDef.atualFrame_T1[ ini ] = frame[ ini ];
//
//                                if (frame[ ini ] == jogo->spriteDef.QTD_FRAMES_T1[ 1 ] - 1)
//                                {
//                                        frame[ ini ] = 0;
//                                        flagTiro[ ini ] = 0;
//                                }
//                                antStatus = jogo->salas[ aSal ].inimigos[ ini ].atacando;
//                                return;
//                        }
//
//                        if ( jogo->salas[ aSal ].inimigos[ ini ].atacando != antStatus)
//                        {
//                                aux[ ini ] = 0;
//                                frame[ ini ] = 0;
//                        }
//
//                        aux[ ini ]++;
//
//                        if ( aux[ ini ] == DIV_FPS_T1 )
//                        {
//                                aux[ ini ] = 0;
//                                frame[ ini ]++;
//                                jogo->spriteDef.atualFrame_T1[ ini ] = frame[ ini ];
//                                if (frame[ ini ] == jogo->spriteDef.QTD_FRAMES_T1[ jogo->salas[ aSal ].inimigos[ ini ].atacando ] - 1)
//                                        frame[ ini ] = 0;
//                        }
//
//                        antStatus = jogo->salas[ aSal ].inimigos[ ini ].atacando;
//                }
//}



void AtualizaSrcPes(JOGO *jogo){
        jogo->spriteDef.SrcPes.width = jogo->Res.Pes[jogo->jogador.atualMovTipo][0].width;
        jogo->spriteDef.SrcPes.height = jogo->Res.Pes[jogo->jogador.atualMovTipo][0].height;
}

void AtualizaSrcPer(JOGO *jogo)
{
        jogo->jogador.PosTela.width = jogo->Res.Per[jogo->jogador.atualArma][jogo->jogador.atualStatus][0].width;
        jogo->jogador.PosTela.height = jogo->Res.Per[jogo->jogador.atualArma][jogo->jogador.atualStatus][0].height;
}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void AtualizaAtaqueT1(JOGO *jogo)
{
        Vector2 posAtual;
        Vector2 alvo = jogo->jogador.PosMundo;
        int i;
        static int flagAtaque[ 50 ];

        int aSal = jogo->atualSala;

        for( i = 0 ; i < jogo->salas[ aSal ].qtd_inimigos_liberados ; i++ )
                if( jogo->salas[ aSal ].inimigos[ i ].VIVO ){
                        posAtual = jogo->salas[ aSal ].inimigos[ i ].posMundo;

                        if( Deslocamento( posAtual , alvo ) < DIST_INICIAR_ATAQUE_T1  &&  !jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque ){
                                jogo->salas[ aSal ].inimigos[ i ].atacando = 1;
                                jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque = LATENCIA_T1;
                        }

                        if(  !jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque ){
                                jogo->salas[ aSal ].inimigos[ i ].atacando = 0;
                        }

                        ///T1
                        if( jogo->salas[ aSal ].inimigos[ i ].tipo == 1 ){
                                if( !flagAtaque[ i ] && jogo->salas[ aSal ].inimigos[ i ].atacando  &&  jogo->spriteDef.atualFrame_T1[ i ] >= 29  &&  jogo->spriteDef.atualFrame_T1[ i ] <= 35  &&  Deslocamento( posAtual , alvo ) <= DIST_EFETIVAR_ATAQUE_T1 ){
                                        jogo->jogador.DANO = 1;
                                        flagAtaque[ i ] = DELAY_DANO;
                                }
                        }

                        ///T0
                        if( jogo->salas[ aSal ].inimigos[ i ].tipo == 0 ){
                                if( !flagAtaque[ i ]  &&  Deslocamento( posAtual , alvo ) <= DIST_EFETIVAR_ATAQUE_T0 ){
                                        jogo->jogador.DANO = 1;
                                        flagAtaque[ i ] = 4 * DELAY_DANO;
                                }
                        }

                        if( jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque )
                                jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque--;

                        if( flagAtaque[ i ] ) flagAtaque[ i ]--;
                }
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void AtualizaRotacT1(JOGO *jogo)
{
        Vector2 posAtual;
        Vector2 alvo = jogo->jogador.PosMundo;
        int i;

        int aSal = jogo->atualSala;

        for( i = 0 ; i < jogo->salas[ aSal ].qtd_inimigos_liberados ; i++ )
                if( jogo->salas[ aSal ].inimigos[ i ].VIVO ){
                        posAtual.x = jogo->salas[ aSal ].inimigos[ i ].posMundo.x;
                        posAtual.y = jogo->salas[ aSal ].inimigos[ i ].posMundo.y;

                        jogo->salas[ aSal ].inimigos[ i ].Rotac = -90 + argVector( (Vector2){ alvo.y - posAtual.y , alvo.x - posAtual.x } );
                        jogo->salas[ aSal ].inimigos[ i ].Rotac = - 90 +(180 / PI) * atan2((alvo.y - posAtual.y), (alvo.x  - posAtual.x));
                }
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void AtualizaInimigosT1(JOGO *jogo)
{
        Vector2 posAtual;
        int i;
        Vector2 alvo = jogo->jogador.PosMundo;

//        static int sentidoAleatorioAnt[ MAX_INI_TELA ] = { 0 };
        static int sentidoAleatorio[ MAX_INI_TELA ] = { 0 };
        static int batera[ MAX_INI_TELA ] = { 0 };
        Vector2 passo;


        int aSal = jogo->atualSala;

        for( i = 0 ; i < jogo->salas[ aSal ].qtd_inimigos_liberados ; i++ )
                if( jogo->salas[ aSal ].inimigos[ i ].VIVO ){
                        posAtual.x = jogo->salas[ aSal ].inimigos[ i ].posMundo.x;
                        posAtual.y = jogo->salas[ aSal ].inimigos[ i ].posMundo.y;

                         if( mesmaZona( jogo , posAtual , alvo ) ){
                                /// Direta (ALVO AVISTADO)
                                posAtual = T1Perseguicao( jogo , posAtual , alvo , jogo->salas[ aSal ].inimigos[ i ].tipo );
                         }else{
                                ///Rodando aleatoriamente
                                 passo.x = cos( (PI / 180) * sentidoAleatorio[ i ] ) * jogo->infoIniT.vel[ jogo->salas[ aSal ].inimigos[ i ].tipo ];
                                 passo.y = sin( (PI / 180) * sentidoAleatorio[ i ] ) * jogo->infoIniT.vel[ jogo->salas[ aSal ].inimigos[ i ].tipo ];
//
                                 if( !ChecaMov( *jogo ,  posAtual , MULTI_PASSO_SEGURO * passo.x , MULTI_PASSO_SEGURO * passo.y ) )
                                        batera[ i ] = 1;
//
                                 if( !batera[ i ] ){
                                        posAtual = SomaVectores( posAtual , passo );
                                 }
                                 else{
//                                        sentidoAleatorioAnt[ i ] = sentidoAleatorio[ i ];
//                                        while( sentidoAleatorioAnt[ i ] == sentidoAleatorio[ i ] ){
                                        switch( nmrRand(1 , 4) ){
                                                case 1:
                                                        sentidoAleatorio[ i ] = 0;
                                                        break;
                                                case 2:
                                                        sentidoAleatorio[ i ] = 90;
                                                        break;
                                                case 3:
                                                        sentidoAleatorio[ i ] = -90;
                                                        break;
                                                case 4:
                                                        sentidoAleatorio[ i ] = 180;
                                                        break;
                                        }
                                }
                        }
                        if( Deslocamento(  jogo->salas[ aSal ].inimigos[ i ].posMundo , alvo) > jogo->infoIniT.dist_manter[ jogo->salas[ aSal ].inimigos[ i ].tipo ] ){
                                jogo->salas[ aSal ].inimigos[ i ].posMundo.x = posAtual.x;
                                jogo->salas[ aSal ].inimigos[ i ].posMundo.y = posAtual.y;

                                jogo->salas[ aSal ].inimigos[ i ].recMundo.x = posAtual.x - jogo->salas[ jogo->atualSala ].inimigos[ i ].recMundo.width / 2;
                                jogo->salas[ aSal ].inimigos[ i ].recMundo.y = posAtual.y - jogo->salas[ jogo->atualSala ].inimigos[ i ].recMundo.height / 2;
                        }
                        if( CheckCollisionRecs( (Rectangle){ posAtual.x , posAtual.y , jogo->salas[ aSal ].inimigos[ i ].recMundo.width , jogo->salas[ aSal ].inimigos[ i ].recMundo.height } , jogo->MapaDesenho ) ){
                                Vector2 novaPosTela = AtualizaPosTela( jogo , posAtual );

                                jogo->salas[ aSal ].inimigos[ i ].posTela.x = novaPosTela.x;
                                jogo->salas[ aSal ].inimigos[ i ].posTela.y = novaPosTela.y;
                        }
                        batera[ i ] = 0;
                }
}


Vector2 T1Perseguicao( JOGO *jogo , Vector2 posAtual , Vector2 alvo , int tipo ){
        Vector2 posFinal;
        Vector2 passo;

//        static int nflag = 0;
//        static int flagEC = 0;
//        static int flagEB = 0;
//        static int flagDC = 0;
//        static int flagDB = 0;

        passo.x = jogo->infoIniT.vel[ tipo ] * sinalNumero( alvo.x - posAtual.x );
        passo.y = jogo->infoIniT.vel[ tipo ] * sinalNumero( alvo.y - posAtual.y );

        // Correcao flick
//        if( passox  >  CONSTANTE_ANITFLICK * passoy ) passoy = 0;


        // Correcao movimento diagonal
        if( passo.x  &&  passo.y ){
                passo.x /= sqrt(2);
                passo.y /= sqrt(2);
        }

        //Colisao
        if( !ChecaMov( *jogo , posAtual , passo.x , 0 ) ){
                passo.x *= -1;
        }
        if( !ChecaMov( *jogo , posAtual , passo.y , 0 ) ){
                passo.y *= -1;
        }

////        if( !ChecaMov( *jogo , posAtual , passo.x , 0 )  || nflag || !ChecaMov( *jogo , posAtual , 0 , passo.y )){
//        if( !ChecaMov( *jogo , posAtual , passo.x , 0 )  || nflag || !ChecaMov( *jogo , posAtual , 0 , passo.y )){
//                if(   !ChecaMov( *jogo , posAtual , passo.x , 0 ) && passo || flagEC ){
//                        flagEC = 1;
//                        nflag = 1;
//                        passo.x = -PASSOT1 / sqrt(2);
//                        passo.y = PASSOT1 / sqrt(2);
//                       flagEB = 0;
//                       flagDC = 0;
//                       flagDB = 0;
//                       flagEC = 0;
//                }
//
//                 if( ( passo.x < 0  &&  passo.y > 0) || flagEB  ){
//                        flagEB = 1;
//                        nflag = 1;
//                        passo.x = -PASSOT1 / sqrt(2);
//                        passo.y = -PASSOT1 / sqrt(2);
//                       flagEC = 0;
//                       flagDC = 0;
//                       flagDB = 0;
//                       flagEC = 0;
//                }
//
//                 if( ( passo.x > 0  &&  passo.y <= 0) || flagDC  ){
//                        flagDC = 1;
//                        nflag = 1;
//                        passo.x = PASSOT1 / sqrt(2);
//                        passo.y = PASSOT1 / sqrt(2);
//                       flagEC = 0;
//                       flagEB = 0;
//                       flagDB = 0;
//                       flagEC = 0;
//                }
//
//                 if( ( passo.x > 0  &&  passo.y > 0 ) || flagDB ){
//                        flagDB = 1;
//                        nflag = 1;
//                        passo.x = PASSOT1 / sqrt(2);
//                        passo.y = -PASSOT1 / sqrt(2);
//                       flagEC = 0;
//                       flagEB = 0;
//                       flagDC = 0;
//                       flagEC = 0;
//                 }
//        }else{
//               nflag = 0;
//               flagEC = 0;
//               flagEB = 0;
//               flagDC = 0;
//               flagDB = 0;
//               flagEC = 0;
//        }

//
//        if( !ChecaMov( *jogo , posAtual , 0 , passo.y ) ){
//                if( passo.x == 0 )
////                        if( nmrRand(1 , 2) == 1)
//                                passo.x = PASSOT1;
////                        else
////                                passo.x = -PASSOT1;
//                passo.y = 0 ;
//        }



        /// Posicao Final
        posFinal = SomaVectores( posAtual , passo );

        return posFinal;
}






        //Rascunho
//        static int flagPerseg[ QTD_MAX_T1_SALA ] = { 0 };
//        static int tipoPerseg[ QTD_MAX_T1_SALA ];
//        int quadrante; // 0 - Origem  , 1 -  Q1 , 2 - Q2 , 3 - Q3 , 4 - Q4 , 5 - EixoX , 6 - EixoY
//        static int tipoAlinhamentoAnt[ QTD_MAX_T1_SALA ];
//
//        tipoAlinhamento = tipoAlinhamentoCheck( posAtual , alvo );
//
//        if( !flagPerseg  ||  tipoAlinhamentoAnt[ i ] )
//                tipoPerseg = nmrRand( 1 , 3 );
//
//        if( passox  &&  passoy && flagPerseg ){
//                switch( tipoPerseg ){
//                        case 1:
//                                posFinal.x = posAtual.x + passox;
//                                posFinal.y = posAtual.y;
//                                break;
//                        case 2:
//                                posFinal.x = posAtual.x;
//                                posFinal.y = posAtual.y + passoy;
//                                break;
//                        case 3:
//                                posFinal.x = posAtual.x + passox / sqrt(2);
//                                posFinal.y = posAtual.y + passoy / sqrt(2);
//                                break;
//                }
//        }
//        else{
//                flagPerseg = 0;
//
//                posFinal.x = posAtual.x + passox;
//                posFinal.y = posAtual.y + passoy;
//        }
//
//        tipoAlinhamentoAnt = tipoAlinhamento;
//        return posFinal;



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

//Vector2 SegueParede( JOGO *jogo , int i , int novaBusca , Vector2 posAtual , Vector2 alvo ){
//        int parede[ MAX_INI_TELA ];
//        int distParede[ 4 ][ MAX_INI_TELA ];
//        static int angMov;
//
//
//
//        /// BUSCA
//        if( !flagBusca ){
//                flagBusca = 1;
//        }
//}

//BOOL CheckRotaDireta( JOGO *jogo , Vector2 posAtual , Vector2 alvo ){
//        float distTotal = Deslocamento( posAtual , alvo );
//        float ang = argVector( posAtual , alvo );
//        float distP = 0;
//        Vector2 pCalc;
//
//        while( distP < distTotal){
//                pCalc.x = posAtual.x + PASSO_RASTREAMENTO * cos( ang );
//                pCalc.y = posAtual.y + PASSO_RASTREAMENTO * sin( ang );
//
//                if( !ChecaMov( *jogo , pCalc , 0 , 0) )
//                        return 0;
//        }
//
//        return 1;
//}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
///
Vector2 AtualizaPosTela( JOGO *jogo , Vector2 posMundo ){
        float XTela;
        float YTela;

        XTela = (  posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x ;
        YTela = ( posMundo.y  - jogo->MapaDesenho.y ) * jogo->escalaGeral.y ;

        return (Vector2){ XTela , YTela };
}


//int tipoAlinhamentoCheck( Vector2 posAtual , Vector2 alvo ){
//        int rx = sinalNumero( alvo.x - posAtual.x );
//        int ry = sinalNumero( alvo.y - posAtual.y );
//
//        if( rx == -1 && !ry )
//                return 0;
//        if( rx == 1 && !ry )
//                return 1;
//        if( ry == -1 && !rx )
//                return 2;
//        if( ry == 1 && !rx )
//                return 3;
//
//        if( rx == 1 && ry == 1 )
//                return 4;
//        if( rx == -1 && ry == 1 )
//                return 5;
//        if( rx == -1 && ry == -1 )
//                return 6;
//        if( rx == 1 && ry == -1 )
//                return 7;
//
//        if( !rx && !ry )
//                return 9;
//}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void GeraInimigos( JOGO *jogo ){
        static int espera = 2;
        int qtdAtual = jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados;


        if( qtdAtual  <  jogo->salas[ jogo->atualSala ].qtd_inimigos_liberar ){
                if( !espera ){
                        jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados++;

//                        int spawnPerto = CalcularSpawnPerto( jogo ); // O spawn mais proximo
//
//                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].posMundo.x = jogo->salas[ jogo->atualSala ].spawns[ spawnPerto ].posMundo.x;
//                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].posMundo.y = jogo->salas[ jogo->atualSala ].spawns[ spawnPerto ].posMundo.y;

                        int spawn = nmrRand( 0 , jogo->salas[ jogo->atualSala ].qtdSpawns - 1  );
                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].posMundo.x = jogo->salas[ jogo->atualSala ].spawns[ spawn ].posMundo.x;
                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].posMundo.y = jogo->salas[ jogo->atualSala ].spawns[ spawn ].posMundo.y;

                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].tipo = jogo->salas[ jogo->atualSala ].spawns[ spawn ].tipo;

                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].VIVO = 1;
                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].saude = jogo->infoIniT.saude[ jogo->salas[ jogo->atualSala ].spawns[ spawn ].tipo ];

                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].xpDrop = jogo->infoIniT.xpDrop[ jogo->salas[ jogo->atualSala ].spawns[ spawn ].tipo ];

                        if( jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].tipo == 1)
                                jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].codItem = 3;
                        else
                                jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].codItem = nmrRand( 1 , 3 );

                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].recMundo.width = jogo->infoIniT.largMundo[ jogo->salas[ jogo->atualSala ].spawns[ spawn ].tipo ];
                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].recMundo.height = jogo->infoIniT.altMundo[ jogo->salas[ jogo->atualSala ].spawns[ spawn ].tipo ];

                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].cor = WHITE;


                }
        }

        espera = ( espera )  ?  espera - 1 : DELAY_SPAWN;
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

int CalcularSpawnPerto( JOGO *jogo ){
        int cod;
        int menor = 0;
        float distMenor = Deslocamento( jogo->jogador.PosMundo , (Vector2){jogo->salas[ jogo->atualSala ].spawns[ menor ].posMundo.x , jogo->salas[ jogo->atualSala ].spawns[ menor ].posMundo.y} );
        float dist;

        for( cod = 0 ; cod < jogo->salas[ jogo->atualSala ].qtdSpawns ; cod++ ){
                dist = Deslocamento( jogo->jogador.PosMundo , (Vector2){jogo->salas[ jogo->atualSala ].spawns[ cod ].posMundo.x , jogo->salas[ jogo->atualSala ].spawns[ cod ].posMundo.y} );
                menor = ( dist < distMenor )  ?  cod : menor;
                distMenor = ( dist < distMenor )  ?  dist : distMenor;
        }

        return menor;
}

/** \brief AtualizaDanoJogador
 *
 * \param a
 * \param b
 * \return c
 *
 */

void AtualizaDanoJogador( JOGO *jogo ){
        static int delayCor;

        if( jogo->jogador.DANO ){

                jogo->jogador.cor = RED;
                delayCor = DELAY_DANO;
                jogo->jogador.saude--;

                if(jogo->jogador.saude == 0 ) {
                        jogo->jogador.saude = SAUDE_TOTAL_JOGADOR;
                        jogo->jogador.vidas--;
//                        ReniciarLevel();
                }

//                if(jogo->jogador.vidas == 0 ) EGameOver();
                jogo->jogador.DANO = 0;
        }
        else{
                if( !delayCor )
                        jogo->jogador.cor = WHITE;
                else
                        jogo->jogador.cor = RED;
        }

        if( delayCor ) delayCor--;
}



BOOL mesmaZona( JOGO *jogo , Vector2 pos1 , Vector2 pos2 ){
        int i;
        for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtdZonas ; i++ )
                if( CheckCollisionPointRec( pos1 , jogo->salas[ jogo->atualSala ].zonas[ i ] ) )
                        if( CheckCollisionPointRec( pos2 , jogo->salas[ jogo->atualSala ].zonas[ i ] ) )
                                return 1;

        return 0;
}



/** \brief AtualizaDanoInimigo
 *
 * \param
 * \param
 * \return
 *
 */

void AtualizaDanoInimigo( JOGO *jogo ){
        static int delayCor[ 100 ] = { 0 };


        int i;

        int aSal = jogo->atualSala;

        for( i = 0 ; i < jogo->salas[ aSal ].qtd_inimigos_liberados ; i++ )
                if( jogo->salas[ aSal ].inimigos[ i ].VIVO ){
                        if( jogo->salas[ aSal ].inimigos[ i ].dano ){

                                delayCor[ i ] = DELAY_DANO;
                                jogo->salas[ jogo->atualSala ].inimigos[ i ].saude--;
                                jogo->salas[ jogo->atualSala ].inimigos[ i ].cor = RED;

                                if( !jogo->salas[ jogo->atualSala ].inimigos[ i ].saude ){

                                        jogo->salas[ jogo->atualSala ].inimigos[ i ].VIVO = 0;

                                        jogo->salas[ jogo->atualSala ].qtd_abatidos++;

                                        jogo->jogador.pontos += jogo->salas[ jogo->atualSala ].inimigos[ i ].xpDrop;

                                        if( !nmrRand( 0 , -1 + 100 / jogo->jogador.probabilidadeDrop ) ){
                                                jogo->items[ jogo->qtd_items_liberados ].recolhido =  NAO;
                                                jogo->items[ jogo->qtd_items_liberados ].posMundo = jogo->salas[ jogo->atualSala ].inimigos[ i ].posMundo;
                                                jogo->items[ jogo->qtd_items_liberados ].codItem = jogo->salas[ jogo->atualSala ].inimigos[ i ].codItem;
                                                jogo->qtd_items_liberados++;
                                        }

                                }

                                jogo->salas[ aSal ].inimigos[ i ].dano = 0;

                        }
                        else{
                                if( !delayCor[ i ] )
                                        jogo->salas[ aSal ].inimigos[ i ].cor = WHITE;
                                else
                                        jogo->salas[ aSal ].inimigos[ i ].cor = RED;
                        }

                        if( delayCor[ i ] ) delayCor[ i ]--;
                }
}





/** \brief Atualiza a posicao dos tirosJogs do jogador
 *
 * \param JOGO*
 * \param
 * \return
 *
 */

void AtualizaTirosJogador( JOGO *jogo ){
        int i;

        if( jogo->jogador.municao[ 0 ] ){
                if ( IsMouseButtonPressed(MOUSE_LEFT_BUTTON)  &&  !jogo->jogador.latencia ){
                        jogo->tirosJog[ jogo->qtd_tirosJog ].pos.x = jogo->jogador.PosMundo.x;
                        jogo->tirosJog[ jogo->qtd_tirosJog ].pos.y = jogo->jogador.PosMundo.y;
                        jogo->tirosJog[ jogo->qtd_tirosJog ].speed = 5;
                        jogo->tirosJog[ jogo->qtd_tirosJog ].Rotac = jogo->jogador.Rotac * PI / 180;
                        jogo->tirosJog[ jogo->qtd_tirosJog ].ativo = 1;
                        jogo->tirosJog[ jogo->qtd_tirosJog ].direcao.x = cos(jogo->tirosJog[ jogo->qtd_tirosJog ].Rotac);
                        jogo->tirosJog[ jogo->qtd_tirosJog ].direcao.y = sin(jogo->tirosJog[ jogo->qtd_tirosJog ].Rotac);
                        jogo->jogador.latencia = 10;
                        jogo->qtd_tirosJog++;
                }
        }

        for ( i = 0; i < jogo->qtd_tirosJog; i++){
                jogo->tirosJog[ i ].nx = jogo->tirosJog[ i ].speed * jogo->tirosJog[ i ].direcao.x;
                jogo->tirosJog[ i ].ny = jogo->tirosJog[ i ].speed * jogo->tirosJog[ i ].direcao.y;

                jogo->tirosJog[ i ].pos.x += jogo->tirosJog[ i ].nx;
                jogo->tirosJog[ i ].pos.y += jogo->tirosJog[ i ].ny;

                jogo->tirosJog[ i ].posTela.x = (jogo->tirosJog[ i ].pos.x - jogo->MapaDesenho.x) * (jogo->tela.width / PIXEL_LARGURA_MAPA);
                jogo->tirosJog[ i ].posTela.y = (jogo->tirosJog[ i ].pos.y - jogo->MapaDesenho.y) * (jogo->tela.height / PIXEL_ALTURA_MAPA);
        }


        if (jogo->jogador.latencia != 0)
                jogo->jogador.latencia--;
}



/** \brief Checa se Tiro esta colidindo com obstaculo
 *
 * \param JOGO*
 * \param
 * \return
 *
 */
void AtualizaColisaoTirosJogador( JOGO *jogo ){
        int i , j , k;
        int colisao;

        for ( j = 0 ; j < jogo->qtd_tirosJog ; j++ ){
                colisao = 1;

                for ( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtdZonas ; i++ )
                        if ( CheckCollisionPointRec( jogo->tirosJog[ j ].pos , jogo->salas[ jogo->atualSala ].zonas[ i ] ) )
                                colisao = 0;

                for ( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados ; i++ )
                        if ( jogo->salas[ jogo->atualSala ].inimigos[ i ].VIVO )
                                if ( CheckCollisionPointRec( jogo->tirosJog[ j ].pos , jogo->salas[ jogo->atualSala ].inimigos[ i ].recMundo ) ){
                                        jogo->salas[ jogo->atualSala ].inimigos[ i ].dano = 1;
                                        colisao = 1;
                                }


                if( colisao ){
                        for( k = j ; k <  jogo->qtd_tirosJog ; k++  )
                                jogo->tirosJog[ k ] = jogo->tirosJog[ k + 1 ];

                        jogo->qtd_tirosJog--;
                        j--;
                        i = 0;
                }
        }
}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

/** \brief Checa se Faca esta colidindo com obstaculo
 *
 * \param JOGO*
 * \param
 * \return
 *
 */
void AtualizaFacaColisao( JOGO *jogo ){
        int i ;

        if( jogo->faca.ativo ){
                jogo->faca.flag_colisao = 1;

                for ( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtdZonas ; i++ )
                        if ( CheckCollisionPointRec( jogo->faca.pos , jogo->salas[ jogo->atualSala ].zonas[ i ] ) )
                                jogo->faca.flag_colisao = 0;

                for ( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados ; i++ )
                        if ( jogo->salas[ jogo->atualSala ].inimigos[ i ].VIVO )
        //                        if ( CheckCollisionRecs( jogo->faca.hitbox , jogo->salas[ jogo->atualSala ].inimigos[ i ].recMundo ) ){
                                if ( CheckCollisionRecs( jogo->faca.hitbox , jogo->salas[ jogo->atualSala ].inimigos[ i ].posTela ) ){
                                        jogo->salas[ jogo->atualSala ].inimigos[ i ].dano = 1;
                                        jogo->faca.flag_colisao = 1;
                                }
        }
}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void AtualizaFaca(JOGO *jogo)
{
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && jogo->faca.disponivel == 1)
        {
                jogo->faca.pos.x = jogo->jogador.PosMundo.x;
                jogo->faca.pos.y = jogo->jogador.PosMundo.y;
                jogo->faca.speed = 3;
                jogo->faca.Rotac = jogo->jogador.Rotac * PI / 180;
                jogo->faca.ativo = 1;
                jogo->faca.direcao.x = cos(jogo->faca.Rotac);
                jogo->faca.direcao.y = sin(jogo->faca.Rotac);
                jogo->faca.posInicial.x = jogo->jogador.PosMundo.x;
                jogo->faca.posInicial.y = jogo->jogador.PosMundo.y;
                jogo->faca.disponivel = 0;
        }

        jogo->faca.hitbox = (Rectangle){jogo->faca.posTela.x,
                                        jogo->faca.posTela.y,
                                        18 * jogo->tela.width / PIXEL_LARGURA_MAPA,
                                        6 * jogo->tela.height / PIXEL_ALTURA_MAPA};

        jogo->faca.distancia = sqrt(pow(jogo->faca.pos.x - jogo->faca.posInicial.x, 2) + pow(jogo->faca.pos.y - jogo->faca.posInicial.y, 2));

        if (jogo->faca.distancia < 60  &&  !jogo->faca.flag_colisao)
        {
                jogo->faca.nx = jogo->faca.speed * jogo->faca.direcao.x;
                jogo->faca.ny = jogo->faca.speed * jogo->faca.direcao.y;

                jogo->faca.pos.x += jogo->faca.nx;
                jogo->faca.pos.y += jogo->faca.ny;
                jogo->faca.Rotac += jogo->faca.speed * 10;
        }
        else
        {
                if ( CheckCollisionRecs( jogo->faca.hitbox, jogo->jogador.PosTela ))

                {
                        jogo->faca.ativo = 0;
                        jogo->faca.disponivel = 1;
                }
        }

        jogo->faca.posTela.x = (jogo->faca.pos.x - jogo->MapaDesenho.x) * (jogo->tela.width / PIXEL_LARGURA_MAPA);
        jogo->faca.posTela.y = (jogo->faca.pos.y - jogo->MapaDesenho.y) * (jogo->tela.height / PIXEL_ALTURA_MAPA);

}



/** \brief Atualiza Status do Items
 *
 * \param *JOGO
 *
 */

 void AtualizaItems( JOGO *jogo ){
        int i;

        for( i = 0 ; i < jogo->qtd_items_liberados ; i++ )
                if( !jogo->items[ i ].recolhido )
                        if( Deslocamento( jogo->items[ i ].posMundo , jogo->jogador.PosMundo ) < DIST_COLETAR_ITEMS ){
                                jogo->items[ i ].recolhido = 1;
                                switch( jogo->items[ i ].codItem ){
                                        case 1:
                                                jogo->jogador.saude += SAUDE_TOTAL_JOGADOR / 2 ;
                                                if( SAUDE_TOTAL_JOGADOR % 2)
                                                                 jogo->jogador.saude++;
                                                if( jogo->jogador.saude > SAUDE_TOTAL_JOGADOR )
                                                        jogo->jogador.saude = 15;
                                                return;

                                        case 2:
                                                jogo->jogador.energia = ENERGIA_TOTAL;
                                                return;
                                        case 3:
                                                jogo->jogador.municao[ 0 ] += QTD_MUNICAO_DROP;
                                                return;
                                }
        }
 }




 /** \brief
  *
  * \param
  * \param
  * \return
  *
  */
#include "desenhamenu.h"
void Pause( JOGO *jogo , int tipo ){
        int i;
        int aux= 0 ;

        switch( tipo ){
                case 0:
                        do{
                                aux++;
                                i=aux;
                                aux = i;
                                BeginDrawing();
                                DrawTextEx( jogo->Res.fonteWolfen , "PAUSE" , (Vector2){  CentraTextoXEX( jogo->Res.fonteWolfen2 , "PAUSE" , 40 , 3) , jogo->tela.height / 2 } , 40 , 3 , GOLD );
                                EndDrawing();
                        }while( !IsKeyPressed( KEY_P ) );
                        break;



        }

}




/** \brief  Atualiza o level
 *
 * \param *JOGO
 *
 */

void AtualizaLevelAtual( JOGO *jogo ){


        if( !jogo->jogador.atualLevel ){
                jogo->jogador.atualLevel++;
                ExibirLevel1( jogo );
        }

        if( jogo->jogador.atualLevel == 1 )
                if( jogo->atualSala ==  4 )
                        if( jogo->salas[ jogo->atualSala ].qtd_abatidos >=  5)
//                                if( CheckCollisionRecs( jogo->jogador.PosTela , (Rectangle){ 404 - 50 , 408 -50 , 100 , 100 } ) ){
                                if( CheckCollisionRecs( jogo->jogador.PosTela , (Rectangle){ ( 404 - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( 408 - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 100 , 100 } ) ){
                                        jogo->jogador.atualLevel++;
                                        ExibirLevel2( jogo );
                                }



}




/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
#include <string.h>
void ExibirLevel1( JOGO *jogo ){
        int i , j;

        char msg[][200] = {
                "Temos uma missao para voce, bravo guerreiro.....",
                "",
                "",
                "",
                "       Recentemente nosso servico de inteligencia detectou atividades",
                "suspeitas num antigo castelo abondonado na costa da escandinavia.",
                "Suspeitamos que fugitivos nazistas, tenham construido uma base ",
                "naquelas intalacoes e mantenham prisioneiros la dentro. Sua missao",
                " e invadir o castelo e descobrir mais sobre isso.",
                "Um ultimo aviso: ",
                "       As coisa mudaram um pouco desde a ultima vez que os enfrentou....."
                "",
                "",
                "",
                "",
                "",
                "MISSAO: Encontre o mapa com a localizacao dos prisioneiros.",
        };


        int x , y , k;

        for( i = 0 ; i < 16 ; i++ )
                for( j = 0 ; j < strlen( msg[ i ] ) ; j++ ){
                        BeginDrawing();
                                ClearBackground( BLACK );
                                DrawTextEx( jogo->Res.fonteWolfen2 , "LEVEL 1" , (Vector2){ CentraTextoXEX( jogo->Res.fonteWolfen2 , "LEVEL 1" , 40 , 3 ) , 20 } , 40 , 3 , MAROON );

                                for( y = 0 ; y < i ; y++ )
                                        DrawText( msg[ y ] , 27 , 100 + 35 * y , 30 , WHITE );

                                for( x = 0 ; x <= j ; x++ )
                                        DrawText( TextFormat("%c" , msg[ i ][ x ] ) , 27 + 19 * x , 100 + 35 * i , 30 , WHITE );
//                                                        DrawTextCodepoint( GetFontDefault() , msg[ y ][ x ] , (Vector2){ 27 + 19 * x , 100 + 35 * y } , 30 , WHITE );

                        for ( k =  3000 * FPS  ; k ; k-- );

                        EndDrawing();
                }
        pausa( 7 );
}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
#include <string.h>
void ExibirLevel2( JOGO *jogo ){
        int i , j;

        char msg[][200] = {
                "Muito bem, bravo guerreiro.....",
                "",
                "",
                "",
                "       Com esse mapa vamos localizar e libertar os prisioneiros!",
                "Eles estao numa ala prisional ao sul do castelo. Siga lutando, ",
                "e olho vivo, nunca se sabe o que pode-se encontrar a frente... ",
                "",
                "",
                "",
                "",
                "",
                "MISSAO: Encontre e liberte os prisioneiros.",
        };


        int x , y , k;

        for( i = 0 ; i < 13 ; i++ )
                for( j = 0 ; j < strlen( msg[ i ] ) ; j++ ){
                        BeginDrawing();
                                ClearBackground( BLACK );
                                DrawTextEx( jogo->Res.fonteWolfen2 , "LEVEL 2" , (Vector2){ CentraTextoXEX( jogo->Res.fonteWolfen2 , "LEVEL 2" , 40 , 3 ) , 20 } , 40 , 3 , MAROON );

                                for( y = 0 ; y < i ; y++ )
                                        DrawText( msg[ y ] , 27 , 100 + 35 * y , 30 , WHITE );

                                for( x = 0 ; x <= j ; x++ )
                                        DrawText( TextFormat("%c" , msg[ i ][ x ] ) , 27 + 19 * x , 100 + 35 * i , 30 , WHITE );

                        for ( k =  3000 * FPS  ; k ; k-- );

                        EndDrawing();
                }
        pausa( 7 );
}
