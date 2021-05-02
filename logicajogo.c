
#include "logicajogo.h"
#include "definicoes.h"
#include "fisica.h"
#include <math.h> // uso para atan2

/**     Funcao AtualizaLevel(): Atualiza os dados do level atual
    */
void AtualizaLevel(Jogo *jogo)
{
        AtualizaMira(jogo);
        //        AtualizaArma( &jogo );

        //        AtualizaTiros( &jogo );
        //        AtualizaRecarga( &jogo );

        AtualizaPosicao(jogo);
        AtualizaMapa(jogo);

        //        AtualizaSrcPer( jogo );
        AtualizaSrcPes(jogo);
        AtualizaOrigin(jogo);
        AtualizaOriginPes(jogo);

        EntraEmPortas(jogo);
        AtualizaAtirar(jogo);


        AtualizaFrameJogador( jogo );
        AtualizaFramePes( jogo );
        AtualizaFrameT1( jogo );

        AtualizaObjetos( jogo );

        AtualizaInimigosT1( jogo );
        AtualizaRotacT1( jogo );
        AtualizaAtaqueT1( jogo );

        AtualizaDanoJogador( jogo );

        GeraInimigos( jogo );
}
//##############################################################################


/**     Funcao AtualizaObjetos():
    */
void AtualizaObjetos( Jogo *jogo ){
        AtualizaBaus( jogo );


}
//##############################################################################





/**     Funcao AtualizaBaus():
    */
void AtualizaBaus( Jogo *jogo ){
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

void AtualizaPosicao(Jogo *jogo)
{
        Vector2 desloc = (Vector2){0, 0}; // Deslocamento
        Vector2 posAtual = jogo->jogador.PosMundo; // Deslocamento

        int movimentoTipo;
        int status = 0;
        int ang;                         // Desvio entre a fronte do jogador e o sentido de deslocamento
        const int tol = TOL_MOV_LATERAL; // Tolerancia angular para se considerar o movimento como lateral

        //Velocidade - Se usuario pressionar ctrl a velocidade aumenta
        float passo = PASSO;

        if (IsKeyDown(KEY_LEFT_CONTROL))
        {
                passo = PASSO_CORRENDO;
                movimentoTipo = 2;
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

void AtualizaMira(Jogo *jogo)
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

void AtualizaMapa(Jogo *jogo)
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

BOOL ChecaMov(Jogo jogo, Vector2 posAtual , int varx, int vary)
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

void EntraEmPortas(Jogo *jogo)
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

BOOL ChecaPortas(Jogo jogo)
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

void pausa(int tempo)
{
        int i;

        for (i = tempo * FPS; i; i--)
        {
                BeginDrawing();
                EndDrawing();
        }
}

///
void AtualizaOrigin(Jogo *jogo)
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
void AtualizaOriginPes(Jogo *jogo)
{
        /*if( jogo->jogador.atualMovTipo == 0 )*/ {
                jogo->spriteDef.OriginPes.x = jogo->jogador.PosTelaPes.width / 2;
                jogo->spriteDef.OriginPes.y = jogo->jogador.PosTelaPes.height / 2;
        }
}




///
void AtualizaFrameJogador(Jogo *jogo)
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
void AtualizaFramePes(Jogo *jogo)
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
void AtualizaAtirar(Jogo *jogo)
{
        //Pistola
        if (jogo->jogador.atualArma == 0)
        {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                        jogo->jogador.atualStatus = 2;

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

void AtualizaFrameT1(Jogo *jogo)
{
        static int aux[ QTD_MAX_T1_SALA ] = { 0 };
        static int frame[ QTD_MAX_T1_SALA ] = { 0 };
        static int antStatus = 0;
        static int flagTiro = 0;

        int ini;
        int aSal = jogo->atualSala;

        for( ini = 0 ; ini < jogo->salas[ aSal ].qtd_inimigos_liberados ; ini++)
                if( jogo->salas[ aSal ].inimigos[ ini ].VIVO ){
                        //Caso atire e preciso terminar o ciclo dos frame[ ini ]s
                        if ( jogo->salas[ aSal ].inimigos[ ini ].atacando  || flagTiro)
                        {
                                if (!flagTiro)
                                {
                                        flagTiro = 1;
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

                                if (frame[ ini ] == jogo->spriteDef.QTD_FRAMES_T1[ 1 ] )
                                {
                                        frame[ ini ] = 0;
                                        flagTiro = 0;
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



void AtualizaSrcPes(Jogo *jogo)
{
        jogo->spriteDef.SrcPes.width = jogo->Res.Pes[jogo->jogador.atualMovTipo][0].width;
        jogo->spriteDef.SrcPes.height = jogo->Res.Pes[jogo->jogador.atualMovTipo][0].height;
}

void AtualizaSrcPer(Jogo *jogo)
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

void AtualizaAtaqueT1(Jogo *jogo)
{
        Vector2 posAtual;
        int i;

        int aSal = jogo->atualSala;

        for( i = 0 ; i < jogo->salas[ aSal ].qtd_inimigos_liberados ; i++ )
                if( jogo->salas[ aSal ].inimigos[ i ].VIVO ){
                        posAtual.x = jogo->salas[ aSal ].inimigos[ i ].posMundo.x;
                        posAtual.y = jogo->salas[ aSal ].inimigos[ i ].posMundo.y;

                        if( Deslocamento( posAtual , jogo->jogador.PosMundo ) < DIST_INICIAR_ATAQUE_T1  &&  !jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque ){
                                jogo->salas[ aSal ].inimigos[ i ].atacando = 1;
                                jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque = LATENCIA_T1;
                        }

                        if(  !jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque ){
                                jogo->salas[ aSal ].inimigos[ i ].atacando = 0;
                        }

                        if( jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque <= LATENCIA_T1 / 2  &&  Deslocamento( posAtual , jogo->jogador.PosMundo ) <= DIST_EFETIVAR_ATAQUE_T1 ){
                                jogo->jogador.DANO += 1;
                        }

                        if( jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque )
                                jogo->salas[ aSal ].inimigos[ i ].latenciaAtaque--;

                }
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void AtualizaRotacT1(Jogo *jogo)
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

                }
}


/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void AtualizaInimigosT1(Jogo *jogo)
{
        Vector2 posAtual;
        int i;
        Vector2 alvo = jogo->jogador.PosMundo;

        int aSal = jogo->atualSala;

        for( i = 0 ; i < jogo->salas[ aSal ].qtd_inimigos_liberados ; i++ )
                if( jogo->salas[ aSal ].inimigos[ i ].VIVO ){
                        posAtual.x = jogo->salas[ aSal ].inimigos[ i ].posMundo.x;
                        posAtual.y = jogo->salas[ aSal ].inimigos[ i ].posMundo.y;
                        posAtual = T1Perseguicao( jogo , posAtual , alvo );

                        jogo->salas[ aSal ].inimigos[ i ].posMundo.x = posAtual.x;
                        jogo->salas[ aSal ].inimigos[ i ].posMundo.y = posAtual.y;

                        if( CheckCollisionPointRec( posAtual , jogo->MapaDesenho ) ){
                                Vector2 novaPosTela = AtualizaPosTela( jogo , posAtual );

                                jogo->salas[ aSal ].inimigos[ i ].posTela.x = novaPosTela.x;
                                jogo->salas[ aSal ].inimigos[ i ].posTela.y = novaPosTela.y;
                        }
                }
}


Vector2 T1Perseguicao( Jogo *jogo , Vector2 posAtual , Vector2 alvo ){
        Vector2 posFinal;
        Vector2 passo;

        /// Direta
        passo.x = PASSOT1 * sinalNumero( alvo.x - posAtual.x );
        passo.y = PASSOT1 * sinalNumero( alvo.y - posAtual.y );

        // Correcao flick
//        if( passox  >  CONSTANTE_ANITFLICK * passoy ) passoy = 0;


        // Correcao movimento diagonal
        if( passo.x  &&  passo.y ){
                passo.x /= sqrt(2);
                passo.y /= sqrt(2);
        }

        if( !ChecaMov( *jogo , posAtual , passo.x , 0 ) )
//                passo.x *= -1 ;
                passo.x = 0 ;
        if( !ChecaMov( *jogo , posAtual , 0 , passo.y ) )
//                passo.y *= -1 ;
                passo.y = 0 ;

        /// Posicao Final
        posFinal = SomaVectores( posAtual , passo );

        return posFinal;






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
}




/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
///
Vector2 AtualizaPosTela( Jogo *jogo , Vector2 posMundo ){
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

void GeraInimigos( Jogo *jogo ){
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

                        jogo->salas[ jogo->atualSala ].inimigos[ qtdAtual ].VIVO = 1;
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

int CalcularSpawnPerto( Jogo *jogo ){
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
 * \param
 * \param
 * \return
 *
 */

void AtualizaDanoJogador( Jogo *jogo ){

        if( jogo->jogador.DANO ){

                jogo->jogador.cor = RED;
                jogo->jogador.saude -= jogo->jogador.DANO;

                if( jogo->jogador.saude < 0 ) jogo->jogador.saude = 0;
                if(jogo->jogador.saude == 0 ) jogo->jogador.vidas--;
//                if(jogo->jogador.vidas == 0 ) EGameOver();
                jogo->jogador.DANO = 0;
        }
        else{
                jogo->jogador.cor = WHITE;
        }

}




