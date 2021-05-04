
#include "desenhajogo.h"
#include "definicoes.h"
#include "estruturascomplexas.h"

/**     Funcao DesenhaLevel(): Desenha o level atual
    */

void DesenhaLevel(JOGO *jogo)
{
        BeginDrawing();

        DesenhaMapa(jogo);

        DesenhaTiro(jogo);

        DesenhaObjetos( jogo );

        DesenhaInimigos( jogo );

        DesenhaPes( jogo);
        DesenhaJogador(jogo);

        DesenhaDebug(jogo);

        EndDrawing();

        if (jogo->PASSAGEM)
                PassagemPorta();
}
//##############################################################################



/**     Funcao DesenhaObjetos():
    */
void DesenhaObjetos( JOGO *jogo ){
        DesenhaBaus( jogo );
        DesenhaPortas( jogo );
        DesenhaSpawns( jogo );
        DesenhaItems( jogo );

}



/** \brief Desenha os items nao-recolhidos
 *
 * \param *JOGO
 *
 */
void DesenhaItems( JOGO *jogo ){
        int i;

        for( i = 0 ; i < jogo->qtd_items_liberados ; i++ )
                if( !jogo->items[ i ].recolhido ){
                        DrawRectangle( 100 , 1000 , 30 , 30 , DARKPURPLE );
                }


}


/**     Funcao DesenhaMapa():
    */
void DesenhaMapa(JOGO *jogo)
{
        Vector2 pos;
        pos.x = 0;
        pos.y = 0;

        DrawTexturePro(jogo->Res.Mapa, jogo->MapaDesenho, jogo->tela, pos, 0, WHITE);
}
//##############################################################################

/**     Funcao DesenhaPes():
    */

void DesenhaPes(JOGO *jogo)
{
        DrawTexturePro(jogo->Res.Pes[jogo->jogador.atualMovTipo][jogo->spriteDef.atualFramePes], jogo->spriteDef.SrcPes, jogo->jogador.PosTelaPes, jogo->spriteDef.OriginPes, jogo->jogador.Rotac, WHITE);
}
//##############################################################################

/**     Funcao DesenhaJogador():
    */

void DesenhaJogador(JOGO *jogo)
{
        DrawTexturePro(jogo->Res.Per[0][jogo->jogador.atualStatus][jogo->spriteDef.atualFrame], jogo->spriteDef.Src, jogo->jogador.PosTela, jogo->spriteDef.Origin, jogo->jogador.Rotac, jogo->jogador.cor);
}
//##############################################################################



/**     Funcao DesenhaPortas(): Desenha as portas trancadas
    */

void DesenhaTiro(JOGO *jogo)
{
        int i;

        for ( i = 0; i < jogo->qtd_tirosJog ; i++ ){
                DrawTexturePro(jogo->Res.Bala, (Rectangle){0, 0, jogo->Res.Bala.width, jogo->Res.Bala.height},
                               (Rectangle){jogo->tirosJog[i].posTela.x, jogo->tirosJog[i].posTela.y,
                                           3 * jogo->tela.width / PIXEL_LARGURA_MAPA, 3 * jogo->tela.height / PIXEL_ALTURA_MAPA},
                               (Vector2){3 * (jogo->tela.width / PIXEL_LARGURA_MAPA) / 2, 3 * (jogo->tela.height / PIXEL_ALTURA_MAPA) / 2}, 0, WHITE);
        }
}

///
void DesenhaPortas(JOGO *jogo)
{
        int i;
        Vector2 posic;

        for ( i = 0; i < jogo->salas[ jogo->atualSala ].qtdPortas ; i++)
                if ( !jogo->salas[jogo->atualSala].portas[i].DESTRANCADA )
                        if ( CheckCollisionPointRec( jogo->salas[jogo->atualSala].portas[i].pos , jogo->MapaDesenho ) )
                        {
                                posic.x = ( jogo->salas[jogo->atualSala].portas[i].pos.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x - 0.5 * LARG_PORTAS * REF_TELA_LARG / jogo->tela.width;
                                posic.y = ( jogo->salas[jogo->atualSala].portas[i].pos.y - jogo->MapaDesenho.y )  * jogo->escalaGeral.y - 0.5 * ALT_PORTAS * REF_TELA_ALT / jogo->tela.height ;

                                DrawTextureEx( jogo->Res.Portas, posic, jogo->salas[ jogo->atualSala ].portas[ i ].rotac, 4.5 , WHITE );
//                                DrawTexturePro( jogo->Res.Portas, posic, jogo->salas[ jogo->atualSala ].portas[ i ].rotac, 5 , WHITE );
                        }
        //                                DrawTexture( jogo->Res.Portas , ESCALA * (jogo->salas[ jogo->atualSala ].portas[ 0 ].pos.x -  jogo->MapaDesenho.x) , ESCALA * (jogo->salas[ jogo->atualSala ].portas[ 0 ].pos.y -  jogo->MapaDesenho.y) , WHITE );
}
//        for( i = 0 ; i < jogo->dadosLevel.salas[ i ].qtdPortas ; i++ )

//##############################################################################

///Funcao PassagemPorta

void PassagemPorta(void)
{
        int i = FPS / 8;

        for (; i; i--)
        {
                BeginDrawing();
                ClearBackground(BLACK);
                EndDrawing();
        }
}
//##############################################################################

#define salaAt jogo->atualSala
void DesenhaBaus( JOGO *jogo ){
        int  i;

        for( i = 0 ; i < jogo->salas[ salaAt ].qtdBaus ; i++)
                if( CheckCollisionRecs( jogo->salas[ salaAt ].baus[ i ].posMapa , jogo->MapaDesenho ) )
                        DrawTexturePro( jogo->salas[ salaAt ].baus[ i ].imagem , jogo->salas[ salaAt ].baus[ i ].src , jogo->salas[ salaAt ].baus[ i ].posTela , jogo->salas[ salaAt ].baus[ i ].origin , jogo->salas[ salaAt ].baus[ i ].Rotac , WHITE );

}

///**     Funcao DesenhaInimigosT1():

void DesenhaInimigos( JOGO *jogo){
        int i;
        int aSal = jogo->atualSala;

        for( i = 0 ; i < jogo->salas[ aSal ].qtd_inimigos_liberados ; i++ )
                if( jogo->salas[ jogo->atualSala ].inimigos[ i ].VIVO )
                        if( CheckCollisionRecs( (Rectangle){ jogo->salas[ aSal ].inimigos[ i ].posMundo.x , jogo->salas[ aSal ].inimigos[ i ].posMundo.y , jogo->salas[ aSal ].inimigos[ i ].recMundo.width , jogo->salas[ aSal ].inimigos[ i ].recMundo.height } , jogo->MapaDesenho ) ){
                                switch( jogo->salas[ aSal ].inimigos[ i ].tipo)
                                {
                                        case 0:
                                                DrawRectanglePro( (Rectangle){ jogo->salas[ aSal ].inimigos[ i ].posTela.x , jogo->salas[ aSal ].inimigos[ i ].posTela.y , jogo->infoIniT.largMundo[ 0 ] , jogo->infoIniT.altMundo[ 0 ] } , (Vector2){ 15 , 15} , jogo->salas[ aSal ].inimigos[ i ].Rotac , PURPLE );
        //                                        DrawTexturePro( jogo->Res.T0 , (Rectangle){ 0 , 10 , 71 , 71 } ,(Rectangle){ jogo->salas[ aSal ].inimigos[ i ].posTela.x , jogo->salas[ aSal ].inimigos[ i ].posTela.y , 130 , 130 } , (Vector2){0 , 0} , jogo->salas[ aSal ].inimigos[ i ].Rotac ,  WHITE );
                                                break;
                                        case 1:
        //                                        DrawRectangle( jogo->salas[ aSal ].inimigos[ i ].posTela.x , jogo->salas[ aSal ].inimigos[ i ].posTela.y , 30 , 30 , ORANGE );
                                                DrawRectanglePro((Rectangle){ jogo->salas[ aSal ].inimigos[ i ].posTela.x , jogo->salas[ aSal ].inimigos[ i ].posTela.y , 30 , 30 } , (Vector2){ 15 , 15} , jogo->salas[ aSal ].inimigos[ i ].Rotac , ORANGE );
//                                                DrawTexturePro( jogo->Res.T1[ jogo->salas[ aSal ].inimigos[ i ].atacando ][jogo->spriteDef.atualFrame_T1[ i ] ] , jogo->spriteDef.SrcT1 , jogo->salas[ aSal ].inimigos[ i ].posTela , jogo->spriteDef.OriginT1 , jogo->salas[ aSal ].inimigos[ i ].Rotac ,  jogo->salas[ aSal ].inimigos[ i ].cor );
                                                break;
                                        case 2:
                                                break;
                                }
                        }
}
//##############################################################################

///**     Funcao DesenhaSpawns():

void DesenhaSpawns( JOGO *jogo)
{
        int i;
        Vector2 pontoNaTela;

        for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtdSpawns ; i++ )
                if( CheckCollisionRecs( jogo->salas[ jogo->atualSala ].spawns[ i ].posMundo , jogo->MapaDesenho ) ){
                        pontoNaTela.x = jogo->salas[ jogo->atualSala ].spawns[ i ].posMundo.x * jogo->escalaGeral.x;
                        pontoNaTela.x = jogo->salas[ jogo->atualSala ].spawns[ i ].posMundo.y * jogo->escalaGeral.y;
                        DrawCircleV(  pontoNaTela ,  30 , PURPLE );
                }


}
//##############################################################################

///Funcao DesenhaDebug

void DesenhaDebug(JOGO *jogo)
{
        int i;
        static int laten = 50;
        static float px[30] , py[30];
        //        int j;
        //        Color cor;
        //        char stt[] = {"\0"};

        ///Inforamacoes Gerais
        DrawText( TextFormat("( %.2f , %.2f)" , jogo->jogador.PosMundo.x , jogo->jogador.PosMundo.y ) , 10 , 10 , 60 , YELLOW );


//        DrawText( TextFormat("PosTelaxy( %.2f , %.2f)" , jogo->jogador.PosTela.x , jogo->jogador.PosTela.y ) , 10 , 100 , 40 , SKYBLUE );
//        DrawText( TextFormat("PosTelawh( %.2f , %.2f)" , jogo->jogador.PosTela.width , jogo->jogador.PosTela.height ) , 10 , 180 , 40 , GREEN );
//        DrawText( TextFormat("RESOLUCAO:( %d , %d)" , GetScreenWidth()  , GetScreenHeight() ) , 10 , 700 , 60 , PINK );
//        DrawText( TextFormat("MAPA Desenho:( %.2f , %.2f)" , jogo->MapaDesenho.x  , jogo->MapaDesenho.y ) , 10 , 600 , 50 , RAYWHITE );
//        DrawText( TextFormat("MAPA Tamanho:( %.2f , %.2f)" , jogo->MapaTamanho.x  , jogo->MapaTamanho.y ) , 10 , 160 , 60 , RAYWHITE );
//        DrawText( TextFormat("( atual sala : %d)" , jogo->atualSala ) , 10 , 100 , 60 , SKYBLUE );
//                if( jogo->jogador.testeFlagTiro )
//                        DrawCircle( 70 , 700 , 30 , RED );
//                DrawText( TextFormat("ARMA %d" , jogo->jogador.atualArma ) , 20 , 430 , 50 , YELLOW );
//                DrawText( TextFormat("FRAME_PER %d" , jogo->spriteDef.atualFrame ) , 20 , 550 , 25 , YELLOW );
//                DrawText( TextFormat("FRAME_PES %d" , jogo->spriteDef.atualFramePes ) , 20 , 550 , 25 , YELLOW );
//                DrawText( TextFormat("STATUS %d" , jogo->jogador.atualStatus ) , 20 , 500 , 50 , YELLOW );

//                DrawText( TextFormat("MOV_TIPO : %d" , jogo->jogador.atualMovTipo ) , 600 , 20 , 50 , GREEN );
//                DrawText( TextFormat("ROTAC : %f" , jogo->jogador.Rotac ) , 10 , 300 , 40 , ORANGE );

        ///Portas entrada -> destino
        //        for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtdPortas ; i++ ){

        //                DrawText( TextFormat("p%d=(%.0f  ,  %.0f)->(%.0f  ,  %.0f)", i + 1 , jogo->salas[ jogo->atualSala ].portas[ i ] .entrada.x , jogo->salas[ jogo->atualSala ].portas[ i ] .entrada.y  , jogo->salas[ jogo->atualSala ].portas[ i ] .destino.x , jogo->salas[ jogo->atualSala ].portas[ i ] .destino.y ) , 25 , 180 + 40 * i , 25 , YELLOW );

        //                TextCopy( stt , ( ( jogo->salas[ jogo->atualSala ].portas[ i ].DESTRANCADA )  ?  "D" : "T" ) );

        //                cor = ( jogo->salas[ jogo->atualSala ].portas[ i ].DESTRANCADA )  ?  GREEN : RED ;
        //                DrawText( TextFormat(stt, i + 1 , jogo->salas[ jogo->atualSala ].portas[ i ].entrada.x , jogo->salas[ jogo->atualSala ].portas[ i ] .entrada.y  , jogo->salas[ jogo->atualSala ].portas[ i ] .destino.x , jogo->salas[ jogo->atualSala ].portas[ i ] .destino.y ) , 1 , 180 + 40 * i , 25 , cor );

        //                DrawText( TextFormat("s%d" , jogo->salas[ jogo->atualSala ].portas[ i ].alteraPSala ) , 420 , 180 + 40 * i , 25 , PURPLE );

        //        }

//        DrawText( TextFormat("( %.2f , %.2f)" , jogo->MapaDesenho.x , jogo->MapaDesenho.y ) , 10 , 70 , 30 , WHITE );
//        DrawText( TextFormat("( %.2f , %.2f)" , ESCALA * (jogo->salas[ jogo->atualSala ].portas[ 0 ].pos.x -  jogo->MapaDesenho.x) , ESCALA * (jogo->salas[ jogo->atualSala ].portas[ 0 ].pos.y -  jogo->MapaDesenho.y ) ) , 10 , 70 , 30 , WHITE );
//        DrawText( TextFormat("( %.2f , %.2f)" , ESCALA * (jogo->salas[ jogo->atualSala ].portas[ 1 ].pos.x -  jogo->MapaDesenho.x) , ESCALA * (jogo->salas[ jogo->atualSala ].portas[ 1 ].pos.y -  jogo->MapaDesenho.y ) ) , 10 , 70 , 30 , WHITE );
//        DrawText( TextFormat(" P=%d , Z=%d " , jogo->salas[ jogo->atualSala ].qtdPortas , jogo->salas[ 0 ].qtdZonas ) , 10 , 100 , 60 , GREEN );
//        DrawText( TextFormat(" P=%d , Z=%d " , jogo->salas[ jogo->atualSala ].qtdPortas , jogo->salas[ 0 ].qtdZonas ) , 10 , 100 , 60 , GREEN );
//        DrawText( TextFormat(" xP = %.2f  |  yP=%.2f " , jogo->salas[ jogo->atualSala ].portas[ 0 ].pos.x , jogo->salas[ jogo->atualSala ].portas[ 0 ].pos.y ) , 10 , 200 , 40 , SKYBLUE );
//        DrawText( TextFormat(" xP = %.2f  |  yP=%.2f " , jogo->salas[ jogo->atualSala ].portas[ 1 ].pos.x , jogo->salas[ jogo->atualSala ].portas[ 1 ].pos.y ) , 10 , 200 , 40 , SKYBLUE );
        DrawText( TextFormat(" xB = %.2f  |  yB=%.2f " , jogo->salas[ jogo->atualSala ].baus[ 0 ].posMapa.x , jogo->salas[ jogo->atualSala ].baus[0].posMapa.y ) , 10 , 650 , 40 , SKYBLUE );

        ///Inimigos
        DrawText( TextFormat("Inimigos Gerados:    LIM : %d   |  %d" , jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados , jogo->salas[ jogo->atualSala ].qtd_inimigos_liberar ) , 10 , 100 , 30 , YELLOW );
        if( !laten){
                for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados ; i++ ){
                        px[ i ] = jogo->salas[ jogo->atualSala ].inimigos[ i ].posMundo.x;
                        py[ i ] = jogo->salas[ jogo->atualSala ].inimigos[ i ].posMundo.y;
                }
                laten = 50;
        }
        else
                laten--;

        for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados ; i++ )
                DrawText( TextFormat("INIM T1 %d | VIVO: %d | POS(%.0f , %.0f) | T(%.0f , %.0f) | A=%d | L = %d" , i , jogo->salas[ jogo->atualSala ].inimigos[ i ].VIVO , px[ i ] , py[ i ] , jogo->salas[ jogo->atualSala ].inimigos[ i ].posTela.width , jogo->salas[ jogo->atualSala ].inimigos[ i ].posTela.height , jogo->salas[ jogo->atualSala ].inimigos[ i ].atacando , jogo->salas[ jogo->atualSala ].inimigos[ i ].latenciaAtaque ) , 500 , 50 + 30*i , 20 , SKYBLUE );

//        #include "logicajogo.h"
//        DrawText(TextFormat("MENOR  = %d   |  DIST= %.0f" , CalcularSpawnPerto( jogo ) , distancia( jogo->jogador.PosMundo , jogo->salas[ jogo->atualSala ].spawns[ CalcularSpawnPerto( jogo ) ]. ) ) , 20 , 400 ,50 , DARKBLUE);
//        DrawText( TextFormat("DANO: %d" , jogo->jogador.DANO ) , 20 , 600 , 25 , RED );


        ///JOGADOR
        DrawText( TextFormat("SAUDE: %d" , jogo->jogador.saude ) , 20 , 630 , 25 , YELLOW );
        DrawText( TextFormat("VIDAS: %d" , jogo->jogador.vidas ) , 20 , 660 , 25 , YELLOW );
        DrawText( TextFormat("ARMA: %d" , jogo->jogador.atualArma ) , 20 , 690 , 25 , YELLOW );
        DrawText( TextFormat("PONTOS: %d" , jogo->jogador.pontos ) , 20 , 720 , 25 , YELLOW );
        DrawText( TextFormat("NMR_ABATIDOS: %d" , jogo->salas[ jogo->atualSala ].qtd_abatidos ) , 20 , 750 , 25 , YELLOW );
}
//##############################################################################


