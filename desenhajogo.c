
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

        DesenhaFaca(jogo);

        DesenhaObjetos( jogo );

        DesenhaInimigos( jogo );

        DesenhaPes( jogo);

        if( jogo->jogador.atualLevel == 4 )
                if( jogo->atualSala == 10 )
//        if( jogo->jogador.atualLevel == 1 )
//                if( jogo->atualSala == 0 )
                        chefao( jogo );

        DesenhaSetas( jogo );

        DesenhaJogador(jogo);

//        DesenhaDebug(jogo);
        nmrHorda( jogo );


        DesenhaHUD( jogo );

        if( jogo->jogador.atualLevel > 1 ) DesenhaMiniMapa( jogo );
//        if( jogo->jogador.atualLevel > 0 ) DesenhaMiniMapa( jogo );



        EndDrawing();

        if (jogo->PASSAGEM)
                PassagemPorta();

//        if( jogo->jogador.atualLevel == 4 )
//        if( jogo->jogador.atualLevel == 1 )

}
//##############################################################################



/**     Funcao DesenhaObjetos():
    */
void DesenhaObjetos( JOGO *jogo ){
        DesenhaBaus( jogo );
        DesenhaPortas( jogo );
//        DesenhaSpawns( jogo );
        DesenhaItems( jogo );
        desenharChave( jogo );

        if( jogo->jogador.atualLevel  == 1 )
                if( jogo->salas[ 4 ].qtd_abatidos >= 5 )
                        DesenhaItemMapa( jogo );

}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void DesenhaItemMapa( JOGO *jogo ){
        static int flag_cor = 1;
        Color cor;

        if( flag_cor ){
                cor = GREEN;
                flag_cor = 0;
        }
        else{
                cor = ORANGE;
                flag_cor = 1;
        }

        DrawRectanglePro( (Rectangle){ ( 404 - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( 408 - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 106 , 106 } , (Vector2){ 53 , 53 } , 0 , cor );
        DrawTexturePro( jogo->Res.ItemMapa , (Rectangle){ 0 , 0 , jogo->Res.ItemMapa.width , jogo->Res.ItemMapa.height } , (Rectangle){ ( 404 - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( 408 - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 100 , 100 } , (Vector2){ 50 , 50 } , 0 , WHITE );
}


/** \brief Desenha os items nao-recolhidos
 *
 * \param *JOGO
 *
 */
void DesenhaItems( JOGO *jogo ){
        int i;

        for( i = 0 ; i < jogo->qtd_items_liberados ; i++ )
                if( !jogo->items[ i ].recolhido )
                        if( CheckCollisionPointRec( jogo->items[ i ].posMundo , jogo->MapaDesenho ) )
                                switch( jogo->items[ i ].codItem ){
                                        case 1:
                                                DrawTexturePro( jogo->Res.KitMed , (Rectangle){ 0 , 0 , jogo->Res.KitMed.width , jogo->Res.KitMed.height } , (Rectangle){ ( jogo->items[ i ].posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( jogo->items[ i ].posMundo.y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 40 , 40 } , (Vector2){ 40/2 , 40/2 } , 0 , WHITE );
                                                break;
                                        case 2:
                                                DrawTexturePro( jogo->Res.KitEnergia , (Rectangle){ 0 , 0 , jogo->Res.KitEnergia.width , jogo->Res.KitEnergia.height } , (Rectangle){ ( jogo->items[ i ].posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( jogo->items[ i ].posMundo.y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 40 , 40 } , (Vector2){ 40/2 , 40/2 } , 0 , WHITE );
                                                break;
                                        case 3:
                                                DrawTexturePro( jogo->Res.Municao , (Rectangle){ 0 , 0 , jogo->Res.Municao.width , jogo->Res.Municao.height } , (Rectangle){ ( jogo->items[ i ].posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( jogo->items[ i ].posMundo.y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 40 , 40 } , (Vector2){ 40/2 , 40/2 } , 0 , WHITE );
                                                break;

//                                        DrawRectangle( ( jogo->items[ i ].posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( jogo->items[ i ].posMundo.y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 30 , 30 , RAYWHITE );
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
        for( int i = 0 ; i < jogo->salas[ jogo->atualSala ].qtdBaus ; i++)
                if( CheckCollisionPointRec( (Vector2){ jogo->jogador.PosMundo.x + DIST_ABRIR_BAUS * cos( ( PI / 180 ) * jogo->jogador.Rotac ) , jogo->jogador.PosMundo.y + DIST_ABRIR_BAUS * sin( ( PI / 180 ) * jogo->jogador.Rotac ) } ,  jogo->salas[ jogo->atualSala ].baus[ i ].posMapa ) )
                        if( !jogo->salas[ jogo->atualSala ].baus[ i ].ABERTO )
                                DrawText( "Abrir Bau [ E ]" , jogo->jogador.PosTela.x - jogo->spriteDef.Origin.x , jogo->jogador.PosTela.y - jogo->spriteDef.Origin.y - 5 , 15 , GOLD );

}
//##############################################################################



/**     Funcao DesenhaTiro(): Desenha os tiros
    */

//void DesenhaTiro(JOGO *jogo)
//{
//        int i;
//
//        for ( i = 0; i < jogo->qtd_tirosJog ; i++ ){
//                DrawTexturePro(jogo->Res.Bala, (Rectangle){0, 0, jogo->Res.Bala.width, jogo->Res.Bala.height},
//                               (Rectangle){jogo->tirosJog[i].posTela.x, jogo->tirosJog[i].posTela.y,
//                                           3 * jogo->tela.width / PIXEL_LARGURA_MAPA, 3 * jogo->tela.height / PIXEL_ALTURA_MAPA},
////                               (Vector2){3 * (jogo->tela.width / PIXEL_LARGURA_MAPA) / 2, 3 * (jogo->tela.height / PIXEL_ALTURA_MAPA) / 2}, 0, WHITE);
//                               (Vector2){3 * (jogo->tela.width / PIXEL_LARGURA_MAPA) / 2 - 60, 3 * (jogo->tela.height / PIXEL_ALTURA_MAPA) / 2 - 40}, jogo->tirosJog[i].Rotac, WHITE);
//        }
//}
void DesenhaTiro(JOGO *jogo)
{
        int i;

        for ( i = 0; i < jogo->qtd_tirosJog ; i++ ){
                DrawTexturePro(jogo->Res.Bala, (Rectangle){0, 0, jogo->Res.Bala.width, jogo->Res.Bala.height},
                               (Rectangle){jogo->tirosJog[i].posTela.x, jogo->tirosJog[i].posTela.y,
                                           3 * jogo->tela.width / PIXEL_LARGURA_MAPA, 3 * jogo->tela.height / PIXEL_ALTURA_MAPA},
//                               (Vector2){3 * (jogo->tela.width / PIXEL_LARGURA_MAPA) / 2, 3 * (jogo->tela.height / PIXEL_ALTURA_MAPA) / 2}, 0, WHITE);
                               (Vector2){3 * (jogo->tela.width / PIXEL_LARGURA_MAPA) / 2 - 60, 3 * (jogo->tela.height / PIXEL_ALTURA_MAPA) / 2 - 40},(jogo->tirosJog[i].Rotac * 180 / PI), WHITE);
        }
}


void DesenhaFaca(JOGO *jogo)

{
        if ( !jogo->faca.disponivel )
        {
                DrawTexturePro( jogo->Res.Faca , (Rectangle){ 0 , 0 , jogo->Res.Faca.width, jogo->Res.Faca.height },
                               (Rectangle){ jogo->faca.posTela.x , jogo->faca.posTela.y ,  75 * jogo->tela.width / REF_TELA_LARG ,
                                        25 * jogo->tela.height / REF_TELA_ALT } ,
                               (Vector2){ 60 * (jogo->tela.width / REF_TELA_LARG) / 2 , 20 * (jogo->tela.height / REF_TELA_ALT) / 2 } , jogo->faca.Rotac , WHITE);

//                DrawTexturePro(jogo->Res.Faca, (Rectangle){0, 0, jogo->Res.Faca.width, jogo->Res.Faca.height},
//                               jogo->faca.hitbox,
//                               (Vector2){  jogo->faca.hitbox.width / 2 , jogo->faca.hitbox.height / 2 }, jogo->faca.Rotac , WHITE);

//                        DrawTexturePro( jogo->Res.Faca, (Rectangle){0, 0, jogo->Res.Faca.width, jogo->Res.Faca.height},
//                               (Rectangle){ jogo->faca.pos.x , jogo->faca.pos.y , 10 , 10 } ,
//                               (Vector2){  10 / 2 , 10 / 2 }, jogo->faca.Rotac , WHITE);
//
        }
}




/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void DesenhaPortas(JOGO *jogo){
        int i;
        int ang;
//        Vector2 posic;

        for ( i = 0; i < jogo->salas[ jogo->atualSala ].qtdPortas ; i++)
                if ( !jogo->salas[jogo->atualSala].portas[i].DESTRANCADA )
//                        if ( CheckCollisionPointRec( jogo->salas[jogo->atualSala].portas[i].pos , jogo->MapaDesenho ) )
                        {
//                                posic.x = ( jogo->salas[jogo->atualSala].portas[i].pos.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x - cos( ( PI / 180 ) * jogo->salas[ jogo->atualSala ].portas[ i ].rotac ) * 0.5 * LARG_PORTAS * REF_TELA_LARG / jogo->tela.width;
//                                posic.y = ( jogo->salas[jogo->atualSala].portas[i].pos.y - jogo->MapaDesenho.y )  * jogo->escalaGeral.y - 0.5 * sin( ( PI / 180 ) * jogo->salas[ jogo->atualSala ].portas[ i ].rotac + PI / 2 ) *ALT_PORTAS * REF_TELA_ALT / jogo->tela.height ;
//
//                                DrawTextureEx( jogo->Res.Portas, posic, jogo->salas[ jogo->atualSala ].portas[ i ].rotac, 4.5 , WHITE );
                                ang = jogo->salas[ jogo->atualSala ].portas[ i ].rotac;

                                if( ang == 90 ){
                                        DrawTexturePro( jogo->Res.Portas , (Rectangle){ 0  , 0 , jogo->Res.Portas.width , jogo->Res.Portas.height } , (Rectangle){ ( jogo->salas[jogo->atualSala].portas[i].pos.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( jogo->salas[jogo->atualSala].portas[i].pos.y - jogo->MapaDesenho.y )  * jogo->escalaGeral.y , LARG_PORTAS * REF_TELA_LARG / jogo->tela.width , ALT_PORTAS * REF_TELA_ALT / jogo->tela.height } , (Vector2){ 0.78 * ALT_PORTAS * REF_TELA_ALT / jogo->tela.height , 0.5 * LARG_PORTAS * REF_TELA_LARG / jogo->tela.width} , ang , WHITE );
                                        return;
                                }
                                if( ang == -90 ){
//                                        ( ang == -90 ) ? ang = 90 : 1;
//                                        ( ang == 90 ) ? ang = -90 : 1;
                                        DrawTexturePro( jogo->Res.Portas , (Rectangle){ 0  , 0 , jogo->Res.Portas.width , jogo->Res.Portas.height } , (Rectangle){ ( jogo->salas[jogo->atualSala].portas[i].pos.x - jogo->MapaDesenho.x + 5 ) * jogo->escalaGeral.x , ( jogo->salas[jogo->atualSala].portas[i].pos.y - jogo->MapaDesenho.y + 5 )  * jogo->escalaGeral.y , LARG_PORTAS * REF_TELA_LARG / jogo->tela.width , ALT_PORTAS * REF_TELA_ALT / jogo->tela.height } , (Vector2){ 0.78 * ALT_PORTAS * REF_TELA_ALT / jogo->tela.height , 0.5 * LARG_PORTAS * REF_TELA_LARG / jogo->tela.width} , 90 , WHITE );
                                        return;
                                }

                                DrawTexturePro( jogo->Res.Portas , (Rectangle){ 0  , 0 , jogo->Res.Portas.width , jogo->Res.Portas.height } , (Rectangle){ ( jogo->salas[jogo->atualSala].portas[i].pos.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( jogo->salas[jogo->atualSala].portas[i].pos.y - jogo->MapaDesenho.y )  * jogo->escalaGeral.y , LARG_PORTAS * REF_TELA_LARG / jogo->tela.width , ALT_PORTAS * REF_TELA_ALT / jogo->tela.height } , (Vector2){ 0.5 * LARG_PORTAS * REF_TELA_LARG / jogo->tela.width , 0.78 * ALT_PORTAS * REF_TELA_ALT / jogo->tela.height } , ang , WHITE );
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
                        DrawTexturePro( jogo->salas[ salaAt ].baus[ i ].imagem , jogo->salas[ salaAt ].baus[ i ].src , jogo->salas[ salaAt ].baus[ i ].posTela , /*jogo->salas[ salaAt ].baus[ i ].origin*/(Vector2){ 0 , 0} , jogo->salas[ salaAt ].baus[ i ].Rotac , WHITE );

}


///**     Funcao DesenhaInimigosT1():
extern int flagTiro[ QTD_MAX_T1_SALA ];
void DesenhaInimigos( JOGO *jogo){
        int i;
        int aSal = jogo->atualSala;
        static int f_0[ 50 ] = { 0 };
        static int a_0[ 50 ] = { 0 };


        for( i = 0 ; i < jogo->salas[ aSal ].qtd_inimigos_liberados ; i++ )
                if( jogo->salas[ jogo->atualSala ].inimigos[ i ].VIVO )
                        if( CheckCollisionRecs( (Rectangle){ jogo->salas[ aSal ].inimigos[ i ].posMundo.x , jogo->salas[ aSal ].inimigos[ i ].posMundo.y , jogo->salas[ aSal ].inimigos[ i ].recMundo.width , jogo->salas[ aSal ].inimigos[ i ].recMundo.height } , jogo->MapaDesenho ) ){
                                switch( jogo->salas[ aSal ].inimigos[ i ].tipo)
                                {
                                        case 0:

//                                                DrawRectanglePro( (Rectangle){ jogo->salas[ aSal ].inimigos[ i ].posTela.x , jogo->salas[ aSal ].inimigos[ i ].posTela.y , jogo->infoIniT.largMundo[ 0 ] , jogo->infoIniT.altMundo[ 0 ] } , (Vector2){ 15 , 15} , jogo->salas[ aSal ].inimigos[ i ].Rotac , PURPLE );
                                                DrawTexturePro( jogo->Res.T0 , (Rectangle){ 1 + 94 * f_0[ i ] , 12 , 94 , 76 } ,(Rectangle){ jogo->salas[ aSal ].inimigos[ i ].posTela.x , jogo->salas[ aSal ].inimigos[ i ].posTela.y , 130 , 130 } , (Vector2){ 94 / 2.0 , 76 / 2.0 } , jogo->salas[ aSal ].inimigos[ i ].Rotac ,  jogo->salas[ jogo->atualSala ].inimigos[ i ].cor );
                                                if( !a_0[ i ] )
                                                        f_0[ i ] == 4 ? f_0[ i ] = 0 : f_0[ i ]++ , a_0[ i ] = 4;
                                                else
                                                        a_0[ i ]--;
                                                break;
                                        case 1:
        //                                        DrawRectangle( jogo->salas[ aSal ].inimigos[ i ].posTela.x , jogo->salas[ aSal ].inimigos[ i ].posTela.y , 30 , 30 , ORANGE );
//                                                DrawRectanglePro((Rectangle){ jogo->salas[ aSal ].inimigos[ i ].posTela.x , jogo->salas[ aSal ].inimigos[ i ].posTela.y , 30 , 30 } , (Vector2){ 15 , 15} , jogo->salas[ aSal ].inimigos[ i ].Rotac , ORANGE );
                                                DrawTexturePro( jogo->Res.T1[ jogo->salas[ aSal ].inimigos[ i ].atacando  ||  flagTiro[ i ]  ][ jogo->spriteDef.atualFrame_T1[ i ] ] , jogo->spriteDef.SrcT1 , jogo->salas[ aSal ].inimigos[ i ].posTela , jogo->spriteDef.OriginT1 , jogo->salas[ aSal ].inimigos[ i ].Rotac ,  jogo->salas[ aSal ].inimigos[ i ].cor );
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
        DrawText( TextFormat("ENERGIA: %d" , jogo->jogador.energia ) , 20 , 490 , 25 , GREEN );
        DrawText( TextFormat("MUNI??????O: %d" , jogo->jogador.municao[ 0 ] ) , 20 , 520 , 25 , GREEN );
        DrawText( TextFormat("SAUDE: %d" , jogo->jogador.saude ) , 20 , 550 , 25 , YELLOW );
        DrawText( TextFormat("VIDAS: %d" , jogo->jogador.vidas ) , 20 , 580 , 25 , YELLOW );
        DrawText( TextFormat("ARMA: %d" , jogo->jogador.atualArma ) , 20 , 610 , 25 , YELLOW );
        DrawText( TextFormat("PONTOS: %d" , jogo->jogador.pontos ) , 20 , 640 , 25 , YELLOW );
        DrawText( TextFormat("NMR_ABATIDOS: %d" , jogo->salas[ jogo->atualSala ].qtd_abatidos ) , 20 , 670 , 25 , YELLOW );
}
//##############################################################################



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
extern int mHorda;
extern int nHorda;

void DesenhaHUD( JOGO *jogo ){
        static int cpy_pnts;
        static int flag_pts;

        DrawTexturePro( jogo->Res.Hud_SCE , (Rectangle){ 0 , 0 , jogo->Res.Hud_SCE.width , jogo->Res.Hud_SCE.height } , (Rectangle){ 0 , 0 , HUD_LARG , HUD_ALT } , (Vector2){ 0 , 0 } , 0 , WHITE );

        // Barra da Vida
        DrawRectangle( X_0_ATRIB , Y_0_ATRIB_SAUDE , LARG_RET_ATRIB * jogo->jogador.saude / SAUDE_TOTAL_JOGADOR , ALT_RET_ATRIB , RED  );

        // Barra da Energia
        DrawRectangle( X_0_ATRIB , Y_0_ATRIB_ENERGIA , LARG_RET_ATRIB * jogo->jogador.energia / ENERGIA_TOTAL , ALT_RET_ATRIB , GREEN  );

        // Coracao
        DrawTexturePro( jogo->Res.coracao , (Rectangle){ 0 , 0 , jogo->Res.coracao.width , jogo->Res.coracao.height } , (Rectangle){ X_CORAC , Y_CORAC , LARG_CORAC , ALT_CORAC } , (Vector2){ 0 , 0 } , 0 , WHITE );

        // Energia
        DrawTexturePro( jogo->Res.KitEnergia , (Rectangle){ 0 , 0 , jogo->Res.KitEnergia.width , jogo->Res.KitEnergia.height } , (Rectangle){ X_ENERG , Y_ENERG , LARG_ENERG , ALT_ENERG } , (Vector2){ 0 , 0 } , 0 , WHITE );

        // xP
        if( cpy_pnts != jogo->jogador.pontos  ||  flag_pts ){
                DrawText( TextFormat("%d" , jogo->jogador.pontos ) , XP_X , XP_Y , XP_FONT_S , GOLD );
                if( flag_pts ) flag_pts-- ;
                else flag_pts = .3 * FPS;
        }
        else DrawText( TextFormat("%d" , jogo->jogador.pontos ) , XP_X , XP_Y , XP_FONT_S , WHITE );
        cpy_pnts = jogo->jogador.pontos;

        // MUNICAO
        DrawText( TextFormat("%3d" , jogo->jogador.municao[ 0 ] ) , MUN_X , MUN_Y , MUN_FONT_S , YELLOW );

        // Level
        if( !mHorda ) DrawText( TextFormat("%d" , jogo->jogador.atualLevel ) , LEVEL_X , LEVEL_Y , LEVEL_FONT_S , WHITE );
        else DrawText( TextFormat("%d" , nHorda ) , LEVEL_X , LEVEL_Y , LEVEL_FONT_S , WHITE );

        // Faca
        Color cor_faca , cor_fundo;
        cor_faca = ( jogo->faca.disponivel )  ?  WHITE : DARKBROWN;
        cor_fundo = ( jogo->faca.disponivel )  ?  LIGHTGRAY : DARKGRAY;

        DrawRectangle(  X_REC_FACA , Y_REC_FACA , LARG_REC_FACA , ALT_REC_FACA , cor_fundo );
        DrawTexturePro( jogo->Res.Faca , (Rectangle){ 0 , 0 , jogo->Res.Faca.width , jogo->Res.Faca.height } , (Rectangle){ X_FACA , Y_FACA , LARG_FACA , ALT_FACA } , (Vector2){ 0 , 0 } , 0 , cor_faca );

        // Nome
//        DrawText( TextFormat("%s" , jogo->jogador.nome ) , NOME_X , NOME_Y , NOME_FONT_S , WHITE );
        DrawText( jogo->jogador.nome , NOME_X , NOME_Y , NOME_FONT_S , WHITE );

        // Vidas
        DrawText( TextFormat("%d" , jogo->jogador.vidas ) , VIDAS_X , VIDAS_Y , VIDAS_FONT_S , RED );
}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
//void DesenhaRefens( JOGO* jogo ){
//        Color cor;
//
//        for( int i = 0 ; i < QTD_REFENS ; i++ )
//                if( CheckCollisionPointRec( jogo->spriteDef.refens[ i ].posMundo , jogo->MapaDesenho ) ){
//                        switch( jogo->spriteDef.refens[ i ].tipo ){
//                                case 1:
//                                        cor = BLUE;
//                                        break;
//                                case 2:
//                                        cor = GREEN;
//                                        break;
//                                case 3:
//                                        cor = PURPLE;//                                        break;
//                                case 4:
//                                        cor = PINK;//                                        break;
//                                case 5:
//                                        cor = DARKBLUE;
//                                        break;
//                                case 6:
//                                        cor = DARKBROWN;
//                                        break;
//                                case 7:
//                                        cor = VIOLET;
//                                        break;
//                        }
//
//                        DrawRectangleV( jogo->spriteDef.refens[ i ].posTela , (Vector2){ 30 , 30 } , cor );
//                        DrawRectangleV( jogo->spriteDef.refens[ i ].posTela , (Vector2){ 30 , 30 } , BLUE );
//                }
//}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
#include "fisica.h"
#include "logicajogo.h"

void desenharChave( JOGO* jogo ){
        if( jogo->jogador.atualLevel == 3){
                DrawTexture(  LoadTexture("Sprites/chave3.png") , ( 2324 - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( 1496 - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , WHITE );
                if( Deslocamento( jogo->jogador.PosMundo , (Vector2){ 2324 , 1496 } ) < 40 ){
                        jogo->jogador.atualLevel = 4;
                        PlaySound( LoadSound("Som/winLevel.wav") );
                        ExibirLevel4( jogo );
                        jogo->salas[ 10 ].portas[ 0 ].DESTRANCADA = 0;
                        jogo->salas[ 10 ].portas[ 2 ].DESTRANCADA = 1;
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
#include <math.h>
#define xh0 1260
#define yh0 1111
#define T_M1 3 * FPS
#define T_M2 3 * FPS
#define DM 15
#define vmh 70


#ifndef L_MM
        #define L_MM 300
#endif
#ifndef H_MM
        #define H_MM 300
#endif // H_MM
int vidas = vmh;
void chefao( JOGO* jogo ){
        static Vector2 posMundo = (Vector2){ xh0 , yh0 };
//        static Vector2 posMundo = (Vector2){ 110 , 600 };
        static Vector2 missil[ 14 ];
        static Vector2 missil_dire[ 14 ];
        static int missil_rot[ 14 ] = { 0 };
//        int missil_ativo[ 14 ] = { 0 };
        float missil_rotac[ 14 ] = { 0 };
        static int modo_1 = T_M1;
        static int modo_2;
        static int frame = 0;
        static float rotac = 0;
        static int aux = -1;
        static int inic = 1;
        static int inic_2 = 1;
        static int inic_3 = 3 * FPS;
//        static int vidas = 10;
        static int delay_dano = 0;
        static int delay_dano_j = 0;
        int flag_flick_x = 0;
        int flag_flick_y = 0;
        static int clock = 0;
        static int n = 0;
        Color cor = WHITE;
        Vector2 alvo = jogo->jogador.PosMundo;

        if( clock ) clock--;
        else clock = 10;

        if( inic ){

                PlayMusicStream( jogo->Res.musica_missao_impo = LoadMusicStream("Som/chefao.mp3") );
//                jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados = 0;
//                jogo->salas[ jogo->atualSala ].qtd_inimigos_liberar = 100;
//                jogo->salas[ jogo->atualSala ].qtd_abatidos = 0;
                jogo->salas[ 10 ].portas[ 0 ].DESTRANCADA = 0;
                jogo->salas[ 10 ].portas[ 1 ].DESTRANCADA = 0;
                jogo->salas[ 10 ].portas[ 2 ].DESTRANCADA = 0;
                inic = 0;
        }


        if( inic_3  ){
                PlaySound( LoadSound("Som/risada2.wav") );
                EndDrawing();
                for( int z = 10 ; z ; z-- ){
                        BeginDrawing();
                                DrawTexturePro(jogo->Res.Mapa, (Rectangle){ xh0 - jogo->MapaDesenho.width / 2 , yh0 - jogo->MapaDesenho.height / 2 , jogo->MapaDesenho.width , jogo->MapaDesenho.height } , jogo->tela, (Vector2){ 0 , 0 } , 0, WHITE );
                        EndDrawing();
                }

                while( inic_3 ){
                        BeginDrawing();
//                        DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 90 ] , (Rectangle){ 64.5 * 0 , 129 , 64.5 , 64 } , (Rectangle){ jogo->tela.width / 2 , jogo->tela.height / 2 , 170 , 190 } , (Vector2){ 85 , 95 } , 0 , WHITE );
                        DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 93 ] , (Rectangle){  0 , 0 , jogo->Res.Per[ 0 ][ 0 ][ 93 ].width , jogo->Res.Per[ 0 ][ 0 ][ 93 ].height } , (Rectangle){ jogo->tela.width / 2 , jogo->tela.height / 2 , 350 , 400 } , (Vector2){ 350 / 2 , 400 / 2 } , 0 , WHITE );
                        DrawText( "\"N??o pensou que fosse ser t??o f??cil, n???...huahuahuah\"" ,  jogo->tela.width / 2 - MeasureText("\"N??o pensou que fosse ser t??o f??cil, n???...huahuahuah" , 30) / 2 , -250 + jogo->tela.height / 2 ,  30 , GOLD );
                        inic_3--;                        EndDrawing();
                }
                BeginDrawing();
                return;
        }
        if( inic_3 ) inic_3--;
        /// SONS
        UpdateMusicStream( jogo->Res.musica_missao_impo );
        if( vidas ){
                if( vidas > 3 ){
                        /// Vozes chefao
                        if( !nmrRand( 0 , 400 ) )
                                PlaySound( LoadSound("Som/risada2.wav") );
                        else{
                                if( !nmrRand( 0 , 450 ) )
                                        PlaySound( LoadSound("Som/BossSpeak1.wav") );
                                else{
                                        if( !nmrRand( 0 , 450 ) )
                                                PlaySound( LoadSound("Som/BossSpeak2.wav") );
                                }
                        }
                }

                /// Spawn
                if( !nmrRand( 0 , 160 ) ){
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].Rotac = 0;                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].VIVO = 1;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].atacando = 0;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].cor = WHITE;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].dano = 0;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].latenciaAtaque = 0;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].posMundo.x = posMundo.x;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].posMundo.y = posMundo.y;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].codItem = nmrRand( 1 , 3 );
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].recMundo.width = jogo->infoIniT.largMundo[ 0 ];
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].recMundo.height = jogo->infoIniT.altMundo[ 0 ];
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].xpDrop = 15;
//                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].recMundo.x = posMundo.x;
//                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].recMundo.y = posMundo.y;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].tipo = 0;
                        jogo->salas[ jogo->atualSala ].inimigos[ jogo->salas[ jogo->atualSala].qtd_inimigos_liberados ].saude = 1;
                        jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados++;
                }
                aux++;
                if( aux == 8 ){
                        aux = 0;
                        frame++;
                }

                if( frame == 3 )
                        frame = 0;

                ///Mini mapa
                if( jogo->atualSala == 10  &&  vidas ){
                        DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * posMundo.x , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * posMundo.y , 5.5 , MAROON );
                        DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * posMundo.x , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * posMundo.y , 3 , RED );
                }

                rotac = -90 + argVector( (Vector2){ alvo.y - posMundo.y , alvo.x - posMundo.x } );
                rotac = - 90 +(180 / PI) * atan2( (alvo.y - posMundo.y), (alvo.x  - posMundo.x));

                if( !delay_dano_j )
                        if ( Deslocamento( jogo->jogador.PosMundo , posMundo ) < 30 ){
                                jogo->jogador.DANO = 1;
                                delay_dano_j = 35;
                }

                if( delay_dano_j ) delay_dano_j--;


                if( modo_1 ){
                        #define VEL_H .5
                        /// Anti Flick
                        if( abs( alvo.x - ( posMundo.x + VEL_H * PASSO * sinalNumero( alvo.x - posMundo.x ) ) )  < 20 )
                                if( abs( alvo.y - ( posMundo.y + VEL_H * PASSO * sinalNumero( alvo.y - posMundo.y ) ) ) > 20 )
                                        flag_flick_x = 1;
                        if( abs( alvo.y - ( posMundo.y + VEL_H * PASSO * sinalNumero( alvo.y - posMundo.y ) ) )  < 20 )
                                if( abs( alvo.x - ( posMundo.x + VEL_H * PASSO * sinalNumero( alvo.x - posMundo.x ) ) ) > 20 )
                                        flag_flick_y = 1;

                        // Correcao movimento diagonal
                        if( alvo.x - posMundo.x  > 90  &&  alvo.y - posMundo.y > 90 ){
                                if( !flag_flick_x ) posMundo.x += sqrt(2) * VEL_H * PASSO * sinalNumero( alvo.x - posMundo.x );
                                if( !flag_flick_y ) posMundo.y += sqrt(2) * VEL_H * PASSO * sinalNumero( alvo.y - posMundo.y );
                        }else{
                                if( !flag_flick_x ) posMundo.x += VEL_H * PASSO * sinalNumero( alvo.x - posMundo.x );
                                if( !flag_flick_y ) posMundo.y += VEL_H * PASSO * sinalNumero( alvo.y - posMundo.y );
                        }

                        modo_2 = T_M2;
                        modo_1--;
                        n = 0;
                }else{
                        if( modo_2 ){
                                modo_2--;

                                if( !clock )
                                        if( n < 13 ){
                                                if( nmrRand( 0 , 1) ){
                                                        if( n % 2 ){
                                                                missil[ n ] = posMundo;
                                                                missil[ n ].x += DM * cos( ( PI / 180 ) * rotac );
                                                                missil[ n ].y += DM * sin( ( PI / 180 ) * rotac );
                                                        }
                                                        else{
                                                                missil[ n ] = posMundo;
                                                                missil[ n ].x -= DM * cos( ( PI / 180 ) * rotac );
                                                                missil[ n ].y -= DM * sin( ( PI / 180 ) * rotac );
                                                        }
                                                }else{
                                                        missil[ n ] = posMundo;
                                                }

                                                missil_rotac[ n ] = argVector( (Vector2){ alvo.y - posMundo.y , alvo.x - posMundo.x } );
                                                missil_rotac[ n ] = (180 / PI) * atan2( (alvo.y - posMundo.y), (alvo.x  - posMundo.x));
                                                missil_dire[ n ].x = cos( (PI / 180) * missil_rotac[ n ] );
                                                missil_dire[ n ].y = sin( (PI / 180) * missil_rotac[ n ]);

//                                                missil_ativo[ n ] = 1;
                                                n++;

                                                if( nmrRand( 0 , 1) ){
                                                        if( n % 2 ){
                                                                missil[ n ] = posMundo;
                                                                missil[ n ].x += DM * cos( ( PI / 180 ) * rotac );
                                                                missil[ n ].y += DM * sin( ( PI / 180 ) * rotac );
                                                        }
                                                        else{
                                                                missil[ n ] = posMundo;
                                                                missil[ n ].x -= DM * cos( ( PI / 180 ) * rotac );
                                                                missil[ n ].y -= DM * sin( ( PI / 180 ) * rotac );
                                                        }
                                                }else{
                                                        missil[ n ] = posMundo;
                                                }

                                                missil_rotac[ n ] = argVector( (Vector2){ alvo.y - posMundo.y , alvo.x - posMundo.x } );
                                                missil_rotac[ n ] = (180 / PI) * atan2( (alvo.y - posMundo.y), (alvo.x  - posMundo.x));
                                                missil_dire[ n ].x = cos( (PI / 180) * missil_rotac[ n ] );
                                                missil_dire[ n ].y = sin( (PI / 180) * missil_rotac[ n ]);

//                                                missil_ativo[ n ] = 1;
                                                n++;
                                        }
                        }else{
                                modo_1 = T_M1;
                        }
                }


                for ( int j = 0 ; j < jogo->qtd_tirosJog ; j++ )
                        if( !delay_dano )
                                if ( Deslocamento( jogo->tirosJog[ j ].pos , posMundo ) < 30 ){
                                        vidas--;
                                        cor = RED;
                                        delay_dano = 25;
                                }
                if( !delay_dano )
                        if ( Deslocamento( jogo->faca.pos , posMundo ) < 30 ){
                                vidas--;
                                cor = RED;
                                delay_dano = 25;
                        }

                if( delay_dano ) delay_dano--;

                if( modo_1 )
                        DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 90 ] , (Rectangle){ 64.5 * frame , 129 , 64.5 , 64 } , (Rectangle){ ( posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( posMundo.y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 170 , 190 } , (Vector2){ 85 , 95 } , rotac , cor );
                else
                        if( modo_2 )
                                DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 90 ] , (Rectangle){ 64.5 * 3 + 64.5 * frame , 129 , 64.5 , 64 } , (Rectangle){ ( posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( posMundo.y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 170 , 190 } , (Vector2){ 85 , 95 } , rotac , cor );
                // Misseis
                for( int q = 0 ; q < 14 ; q++ )
                        if( !delay_dano_j )
//                                if( missil_ativo[ q ] )
                                        if ( Deslocamento( jogo->jogador.PosMundo , missil[ q ] ) < 10 ){
                                                jogo->jogador.DANO = 1;
                                                delay_dano_j = 35;
                                        }

                for( int e = 0 ; e < 14 ; e++ ){
//                        if( missil_ativo[ e ] ){
                                missil[ e ].x += 4.7 * VEL_H * PASSO * missil_dire[ e ].x;
                                missil[ e ].y += 4.7 * VEL_H * PASSO * missil_dire[ e ].y;
                                missil_rot[ e ] += 60;
                                if( missil_rot[ e ] == 360 )
                                        missil_rot[ e ] = 0;

//                                DrawRectanglePro( (Rectangle){ ( missil[ e ].x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( missil[ e ].y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 20 , 20 } , (Vector2){ 10 , 10 } , 45 , RAYWHITE );
//                                DrawTexturePro( jogo->Res.Per[0][0][91] , (Rectangle){ 0 , 0 , jogo->Res.Per[0][0][91].width , jogo->Res.Per[0][0][91].height } , (Rectangle){ ( missil[ e ].x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( missil[ e ].y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 40 , 40 } , (Vector2){ 20 , 20 } , missil_rot[ e ] , ORANGE );
                                DrawTexturePro( jogo->Res.Per[0][0][91] , (Rectangle){ 0 , 0 , jogo->Res.Per[0][0][91].width , jogo->Res.Per[0][0][91].height } , (Rectangle){ ( missil[ e ].x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( missil[ e ].y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 40 , 40 } , (Vector2){ 20 , 20 } , missil_rot[ e ] , WHITE );
//                        }
                }
                if( CheckCollisionPointRec( posMundo ,jogo->MapaDesenho ) ){
                        DrawRectangle( (jogo->tela.width - 650 ) / 2 , jogo->tela.height - 70 , 650 , 12 , BLACK );
                        DrawRectangle( (jogo->tela.width - 650 ) / 2 , jogo->tela.height - 70 , ( 650.0 * vidas ) / vmh , 12 , RED );
                        DrawTextEx( jogo->Res.fonteWolfen ,  "MECHA HITLER" , (Vector2){ jogo->tela.width / 2 - MeasureText("MECHA HITLER" , 35 ) / 2 , jogo->tela.height - 45 } , 35 , 5 , RED );
                }
        }else{
                if( inic_2 ){
                        inic_2 = 0;
                        StopMusicStream( jogo->Res.musica_missao_impo );
                        PlaySound( LoadSound( "Som/explo.wav" ) );
                        PlaySound( LoadSound( "Som/nooo.wav" ) );
                        jogo->salas[ 10 ].portas[ 2 ].DESTRANCADA = 1;
                        jogo->jogador.pontos += 1500;
                        frame = 0;

                        jogo->salas[ 10 ].portas[ 0 ].DESTRANCADA = 1;
                        jogo->salas[ 10 ].portas[ 1 ].DESTRANCADA = 1;
                        jogo->salas[ 10 ].portas[ 2 ].DESTRANCADA = 1;

                }
                if( frame == 79) PlaySound( LoadSound("Som/Yeeeah!.wav") );

                DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 90 ] , (Rectangle){ 64.6 * 6 , 129 , 62.5 , 64 } , (Rectangle){ ( posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( posMundo.y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 170 , 190 } , (Vector2){ 85 , 95 } , rotac , WHITE );
                DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 96 ] , (Rectangle){ 0 , 0 , jogo->Res.Per[ 0 ][ 0 ][ 96 ].width , jogo->Res.Per[ 0 ][ 0 ][ 96 ].height } , (Rectangle){ ( 1263 - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( 1115 - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 100 , 300 } , (Vector2){ 50 , 150 } , 0 , cor );

                if( clock ){
                        if( frame < 81 ){
                                DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 92 ] , (Rectangle){ ( frame % 9 ) * 100.44 , ( frame / 9 ) * 131.75 , 100.44 , 131.75 } , (Rectangle){ ( posMundo.x - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( posMundo.y - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 200 , 200 } , (Vector2){ 100 , 100 } , 0 , WHITE );
                                frame++;

                        }
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
extern int flag_calma;
#define T_E_T 40
#define A_L 1
void nmrHorda( JOGO* jogo ){
        static int inicio = 3.5 * FPS;
        static int efeito_tam = 0;
        static int flag_efeito = 0;
        static int flag_ajuda1 = 0;
        static int flag_ajuda2 = 0;
        static int flag_ajuda3 = 0;
        static int flag_ajuda4 = 0;
        static int flag_ajuda5 = 0;
        static int flag_ajuda6 = 0;
        static int flag_ajuda7 = 0;


        if( flag_calma )
                DrawTextEx( jogo->Res.fonteWolfen , TextFormat("HORDA %d" , nHorda ) , (Vector2){ ( jogo->tela.width ) / 2 - MeasureTextEx( jogo->Res.fonteWolfen , "HORDA X" , 60 , 12 ).x / 2 , jogo->tela.height / 3 }  , 60 , 10 , YELLOW );

        if( inicio ){
                DrawTextEx( jogo->Res.fonteWolfen , "Get Psyched !!" , (Vector2){ ( jogo->tela.width ) / 2 - MeasureTextEx( jogo->Res.fonteWolfen , "Get Psyched !!" , 60 + efeito_tam * A_L , 12 ).x / 2 , jogo->tela.height / 3 }  , 60 + efeito_tam * A_L , 10 , (Color){ 255, 0 , 0, 255 } );
                inicio--;
                if( !flag_efeito ){
                        efeito_tam++;

                        if( efeito_tam == T_E_T ) flag_efeito = 1;

                }else{
                        efeito_tam--;
                        if( efeito_tam == 0 ) flag_efeito = 0;
                }
        }

        if( !inicio  &&  !mHorda ){
                if( flag_ajuda1< 4 * FPS ){
                        flag_ajuda1++;
//                        DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 80] , (Rectangle){ 0 , 0 , jogo->Res.Per[ 0 ][ 0 ][ 80].width , jogo->Res.Per[ 0 ][ 0 ][ 80].height } , (Rectangle){ jogo->tela.width - 200 , 150 , 200 , 150 } , (Vector2){ 0 , 0 } , 0 , WHITE );
//                        DrawRectangle( 200 , 400 , 400 , 200 , WHITE );
                        DrawTexture( jogo->Res.Per[ 0 ][ 0 ][ 80 ] , 200 , 400 , CLITERAL(Color){ 255, 255, 255, 180 } );
                }else{
                        if( flag_ajuda2< 4 * FPS ){
                                flag_ajuda2++;
                                DrawTexture( jogo->Res.Per[ 0 ][ 0 ][ 81 ] , 200 , 400 , CLITERAL(Color){ 255, 255, 255, 180 } );
                        }else{
                                if( flag_ajuda3< 4 * FPS ){
                                        flag_ajuda3++;
                                        DrawTexture( jogo->Res.Per[ 0 ][ 0 ][ 82 ] , 200 , 400 , CLITERAL(Color){ 255, 255, 255, 180 } );
                                }else{
                                        if( flag_ajuda6< 4 * FPS ){
                                                flag_ajuda6++;
                                                DrawTexture( jogo->Res.Per[ 0 ][ 0 ][ 85 ] , 200 , 400 , CLITERAL(Color){ 255, 255, 255, 180 } );
                                        }else{
                                                if( flag_ajuda7< 4 * FPS ){
                                                        flag_ajuda7++;
                                                        DrawTexture( jogo->Res.Per[ 0 ][ 0 ][ 86 ] , 200 , 400 , CLITERAL(Color){ 255, 255, 255, 180 } );
                                                }
                                        }
                                }
                        }
                }
        }

        if( jogo->jogador.atualLevel == 2 ){
                if( flag_ajuda4< 4 * FPS ){
                        flag_ajuda4++;
                        DrawTexture( jogo->Res.Per[ 0 ][ 0 ][ 83 ] , 200 , 400 , CLITERAL(Color){ 255, 255, 255, 180 } );
                }else{
                        if( flag_ajuda5< 4 * FPS ){
                                flag_ajuda5++;
                                DrawTexture( jogo->Res.Per[ 0 ][ 0 ][ 84 ] , 200 , 400 , CLITERAL(Color){ 255, 255, 255, 180 } );
                        }
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
#ifndef L_MM
        #define L_MM 300
#endif
#ifndef H_MM
        #define H_MM 300
#endif // H_MM

#define VP 200
void DesenhaMiniMapa( JOGO* jogo ){
        static int ativo = 1;
        static int visibilidade = VP;
        static int C = 1;
        static Sound som_b;
        if( C ){
                som_b = LoadSound("Som/bot1.mp3");
                C = 0;
        }


        if( IsKeyPressed( KEY_M ) ){
                ativo = ativo ? 0 : 1;
                PlaySound( LoadSound("Som/setas.wav") );
//                visibilidade = VP;
        }

        if( IsKeyDown( KEY_PERIOD ) )
                if( visibilidade < 255 ){
                        visibilidade += 5;
                        if( !IsSoundPlaying( som_b ) ) PlaySound( som_b );
                }
        if( IsKeyDown( KEY_COMMA ) )
                if( visibilidade > 60 ){
                        visibilidade -= 5;
                        if( !IsSoundPlaying( som_b ) ) PlaySound( som_b );
                }


        if( ativo ){
                DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 95 ] , (Rectangle){ 0 , 0 , jogo->Res.Per[ 0 ][ 0 ][ 95 ].width , jogo->Res.Per[ 0 ][ 0 ][ 95 ].height } , (Rectangle){ jogo->tela.width - L_MM , 0 , L_MM , H_MM } , (Vector2){ 0 , 0 } , 0 , CLITERAL(Color){ 255, 255, 255, visibilidade } );
                DrawText( "[ M ]" , jogo->tela.width - 30 , 3 , 15 , CLITERAL(Color){ 255, 203, 0, visibilidade } );

//                DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * jogo->jogador.PosMundo.x , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * jogo->jogador.PosMundo.y , 5 , CLITERAL(Color){ 9 , 252, 26, 255 } );
                DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * jogo->jogador.PosMundo.x , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * jogo->jogador.PosMundo.y , 5.5 , LIME );
                DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * jogo->jogador.PosMundo.x , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * jogo->jogador.PosMundo.y , 3 , GREEN );
//                DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * jogo->jogador.PosMundo.x , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * jogo->jogador.PosMundo.y , 3 , LIME );

                if( jogo->jogador.atualLevel == 2 ){
                        DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * 1260 , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * 984 , 5.5 , DARKBLUE );
                        DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * 1260 , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * 984 , 3 , BLUE );
                }
                if( jogo->jogador.atualLevel == 3 ){
                        DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * 2345 , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * 1515 , 5.5 , DARKBLUE );
                        DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * 2345 , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * 1515 , 3 , BLUE );
                }
                if( jogo->jogador.atualLevel == 4 ){
                        if( jogo->atualSala >= 11  &&  jogo->atualSala <= 113  &&  vidas){
                                DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * 1261 , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * 1120 , 5.5 , DARKBLUE );
                                DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * 1261 , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * 1120 , 3 , BLUE );
                        }

                        if( !vidas ){
                                DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * 1258 , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * 2057 , 5.5 , DARKBLUE );
                                DrawCircle(  jogo->tela.width - L_MM + ( ( L_MM * 1.0 ) / jogo->Res.Mapa.width ) * 1258 , ( (H_MM * 1.0 ) / jogo->Res.Mapa.height ) * 2057 , 3 , BLUE );
                        }

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
#define IDVIS 7
void DesenhaSetas( JOGO* jogo ){
        static int vis = 255;
        static int flag = 0;
        Color cor = CLITERAL(Color){ 255, 255, 255, vis };

        if( jogo->jogador.atualLevel == 1 ){
                DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 96 ] , (Rectangle){ 0 , 0 , jogo->Res.Per[ 0 ][ 0 ][ 96 ].width , jogo->Res.Per[ 0 ][ 0 ][ 96 ].height } , (Rectangle){ ( 102 - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( 755 - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 100 , 300 } , (Vector2){ 50 , 150 } , 0 , cor );
                DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 96 ] , (Rectangle){ 0 , 0 , jogo->Res.Per[ 0 ][ 0 ][ 96 ].width , jogo->Res.Per[ 0 ][ 0 ][ 96 ].height } , (Rectangle){ ( 102 - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( 1425 - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 100 , 300 } , (Vector2){ 50 , 150 } , -90 , cor );
                DrawTexturePro( jogo->Res.Per[ 0 ][ 0 ][ 96 ] , (Rectangle){ 0 , 0 , jogo->Res.Per[ 0 ][ 0 ][ 96 ].width , jogo->Res.Per[ 0 ][ 0 ][ 96 ].height } , (Rectangle){ ( 406 - jogo->MapaDesenho.x ) * jogo->escalaGeral.x , ( 1375 - jogo->MapaDesenho.y ) * jogo->escalaGeral.y , 100 , 300 } , (Vector2){ 50 , 150 } , 180 , cor );

        }

        if( jogo->jogador.atualLevel == 4 )
                if( jogo->atualSala == 14 ){
                        if( !nmrRand( 0 , 165 ) ) PlaySound( LoadSound("Som/help1.ogg") );
                }

        if( !flag ){
                vis -= IDVIS;
                if( vis <= 0 ){
                        vis = 0;
                        flag = 1;
                }
        }else{
                vis += IDVIS;
                if( vis >= 255 ){
                        vis = 255;
                        flag = 0;
                }
        }

}







