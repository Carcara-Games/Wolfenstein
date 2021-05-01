
#include "desenhajogo.h"
#include "definicoes.h"

/**     Funcao DesenhaLevel(): Desenha o level atual
    */

void DesenhaLevel(Jogo *jogo)
{
        BeginDrawing();

        DesenhaMapa(jogo);

        DesenhaTiro(jogo);

        DesenhaObjetos( jogo );

        DesenhaInimigosT1( jogo );

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
void DesenhaObjetos( Jogo *jogo ){
        DesenhaBaus( jogo );
        DesenhaPortas( jogo );
        DesenhaSpawns( jogo );

}



/**     Funcao DesenhaMapa():
    */
void DesenhaMapa(Jogo *jogo)
{
        Vector2 pos;
        pos.x = 0;
        pos.y = 0;

        DrawTexturePro(jogo->Res.Mapa, jogo->MapaDesenho, jogo->tela, pos, 0, WHITE);
}
//##############################################################################

/**     Funcao DesenhaPes():
    */

void DesenhaPes(Jogo *jogo)
{
        DrawTexturePro(jogo->Res.Pes[jogo->jogador.atualMovTipo][jogo->spriteDef.atualFramePes], jogo->spriteDef.SrcPes, jogo->jogador.PosTelaPes, jogo->spriteDef.OriginPes, jogo->jogador.Rotac, WHITE);
}
//##############################################################################

/**     Funcao DesenhaJogador():
    */

void DesenhaJogador(Jogo *jogo)
{
        DrawTexturePro(jogo->Res.Per[0][jogo->jogador.atualStatus][jogo->spriteDef.atualFrame], jogo->spriteDef.Src, jogo->jogador.PosTela, jogo->spriteDef.Origin, jogo->jogador.Rotac, WHITE);
}
//##############################################################################



/**     Funcao DesenhaPortas(): Desenha as portas trancadas
    */

void DesenhaTiro(Jogo *jogo)
{
        static int qtd_balas_ativas = 0;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)  &&  !jogo->jogador.latencia)
        {
                jogo->tiro[qtd_balas_ativas].pos.x = jogo->jogador.PosMundo.x;
                jogo->tiro[qtd_balas_ativas].pos.y = jogo->jogador.PosMundo.y;
                jogo->tiro[qtd_balas_ativas].speed = 5;
                jogo->tiro[qtd_balas_ativas].Rotac = jogo->jogador.Rotac * PI / 180;
                jogo->tiro[qtd_balas_ativas].ativo = 1;
                jogo->tiro[qtd_balas_ativas].direcao.x = cos(jogo->tiro[qtd_balas_ativas].Rotac);
                jogo->tiro[qtd_balas_ativas].direcao.y = sin(jogo->tiro[qtd_balas_ativas].Rotac);
                jogo->jogador.latencia = 10;
                qtd_balas_ativas++;
        }

        for (int i = 0; i < qtd_balas_ativas; i++)
        {

                jogo->tiro[i].nx = jogo->tiro[i].speed * jogo->tiro[i].direcao.x;
                jogo->tiro[i].ny = jogo->tiro[i].speed * jogo->tiro[i].direcao.y;

                jogo->tiro[i].pos.x += jogo->tiro[i].nx;
                jogo->tiro[i].pos.y += jogo->tiro[i].ny;

                jogo->tiro[i].posTela.x = (jogo->tiro[i].pos.x - jogo->MapaDesenho.x) * (jogo->tela.width / PIXEL_LARGURA_MAPA);
                jogo->tiro[i].posTela.y = (jogo->tiro[i].pos.y - jogo->MapaDesenho.y) * (jogo->tela.height / PIXEL_ALTURA_MAPA);

                // DrawCircleV(jogo->tiro[i].posTela, 10, MAROON);

                // mudar rela height pra variavel global
                DrawTexturePro(jogo->Res.Bala, (Rectangle){0, 0, jogo->Res.Bala.width, jogo->Res.Bala.height},
                               (Rectangle){jogo->tiro[i].posTela.x, jogo->tiro[i].posTela.y,
                                           3 * jogo->tela.width / PIXEL_LARGURA_MAPA, 3 * jogo->tela.height / PIXEL_ALTURA_MAPA},
                               (Vector2){3 * (jogo->tela.width / PIXEL_LARGURA_MAPA) / 2, 3 * (jogo->tela.height / PIXEL_ALTURA_MAPA) / 2}, 0, WHITE);
        }

        if (qtd_balas_ativas == 20)
        {
                qtd_balas_ativas = 0;
        }

        if (jogo->jogador.latencia != 0)
        {
                jogo->jogador.latencia--;
        }
}

///
void DesenhaPortas(Jogo *jogo)
{
        int i;
        Vector2 posic;

        for (i = 0; i < jogo->salas[jogo->atualSala].qtdPortas; i++)
                if (!jogo->salas[jogo->atualSala].portas[i].DESTRANCADA)
                        if (CheckCollisionPointRec(jogo->salas[jogo->atualSala].portas[i].pos, jogo->MapaDesenho))
                        {
                                posic.x = jogo->salas[jogo->atualSala].portas[i].pos.x - jogo->MapaDesenho.x;
                                posic.y = jogo->salas[jogo->atualSala].portas[i].pos.y - jogo->MapaDesenho.y;

                                DrawTextureEx(jogo->Res.Portas, posic, jogo->salas[jogo->atualSala].portas[i].rotac, 1, WHITE);
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
void DesenhaBaus( Jogo *jogo ){
//        Texture2D imagem;
        int  i;

//        DrawTexture( jogo->Res.BauFechado , 10 , 10 , WHITE);
//        if( CheckCollisionRecs( jogo->salas[  ].baus[0].posMapa , jogo->MapaDesenho ) ){
//                DrawTexturePro( jogo->Res.BauFechado , (Rectangle){ 0 , 0 , jogo->Res.BauFechado.width , jogo->Res.BauFechado.height } , (Rectangle){ (jogo->salas[0].baus[0].posRec.x - jogo->MapaDesenho.x + jogo->salas[0].baus[0].posRec.width / 2 ) * (  jogo->tela.width / PIXEL_LARGURA_MAPA  )  , ( jogo->salas[0].baus[0].posRec.y - jogo->MapaDesenho.y + jogo->salas[0].baus[0].posRec.height / 2) * (  jogo->tela.height / PIXEL_ALTURA_MAPA) , 31 * (  jogo->tela.width / PIXEL_LARGURA_MAPA  )  , 21 * (  jogo->tela.height / PIXEL_ALTURA_MAPA) } , (Vector2){  jogo->salas[0].baus[0].posRec.width / 2 * (  jogo->tela.width / PIXEL_LARGURA_MAPA  ) ,21 * (  jogo->tela.height / PIXEL_ALTURA_MAPA) } , 90 , WHITE);

        for( i = 0 ; i < jogo->salas[ salaAt ].qtdBaus ; i++)
                if( CheckCollisionRecs( jogo->salas[ salaAt ].baus[ i ].posMapa , jogo->MapaDesenho ) ){
//                if( CheckCollisionPointRec( (Vector2){ jogo->salas[ salaAt ].baus[ i ].posMapa.x , jogo->salas[ salaAt ].baus[ i ].posMapa.y } , jogo->MapaDesenho ) ){
//                        DrawRing( (Vector2){ 400 , 400 } , 80 , 160 , 0 , 180 , 20 , RED );
                        DrawTexturePro( jogo->salas[ salaAt ].baus[ i ].imagem , jogo->salas[ salaAt ].baus[ i ].src , jogo->salas[ salaAt ].baus[ i ].posTela , jogo->salas[ salaAt ].baus[ i ].origin , jogo->salas[ salaAt ].baus[ i ].Rotac , WHITE );
//                        DrawTexturePro( jogo->Res.BauAberto , (Rectangle){ 0 , 0 , 512 , 347 } , jogo->salas[ salaAt ].baus[ i ].posTela , jogo->salas[ salaAt ].baus[ i ].origin , jogo->salas[ salaAt ].baus[ i ].Rotac , WHITE );
                }
//                        imagem =  ( jogo->salas[ jogo->atualSala ].baus[ i ].ABERTO ) ?  jogo->Res.BauAberto :  jogo->Res.BauFechado;
//                        DrawTexturePro( jogo->Res.BauFechado , (Rectangle){ 0 , 0 , jogo->Res.BauFechado.width , jogo->Res.BauFechado.height } , (Rectangle){ (jogo->salas[0].baus[0].posRec.x - jogo->MapaDesenho.x + jogo->salas[0].baus[0].posRec.width / 2 ) * (  jogo->tela.width / PIXEL_LARGURA_MAPA  )  , ( jogo->salas[0].baus[0].posRec.y - jogo->MapaDesenho.y + jogo->salas[0].baus[0].posRec.height / 2) * (  jogo->tela.height / PIXEL_ALTURA_MAPA) , 31 * (  jogo->tela.width / PIXEL_LARGURA_MAPA  )  , 21 * (  jogo->tela.height / PIXEL_ALTURA_MAPA) } , (Vector2){  jogo->salas[0].baus[0].posRec.width / 2 * (  jogo->tela.width / PIXEL_LARGURA_MAPA  ) , jogo->salas[0].baus[0].posRec.height / 2* (  jogo->tela.width / PIXEL_LARGURA_MAPA  )  , 21 * (  jogo->tela.height / PIXEL_ALTURA_MAPA) } , 90 , WHITE);
//                        DrawRectangleV( (Vector2){ ( jogo->salas[ jogo->atualSala ].baus[ i ].pos.x - jogo->MapaDesenho.x )  , ( jogo->salas[ jogo->atualSala ].baus[ i ].pos.y - jogo->MapaDesenho.y )  } , (Vector2){ 17 / ESCALA , 31 / ESCALA } , BLUE );
//                        DrawRectangleV( (Vector2){ ( jogo->salas[ jogo->atualSala ].baus[ i ].pos.x - jogo->MapaDesenho.x )  , ( jogo->salas[ jogo->atualSala ].baus[ i ].pos.y - jogo->MapaDesenho.y )  } , (Vector2){ 17 / ESCALA , 31 / ESCALA } , BLUE );
//                }
}

///**     Funcao DesenhaInimigosT1():

void DesenhaInimigosT1( Jogo *jogo)
{
        int i;

        for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados ; i++ )
//                        if( jogo->salas[ jogo->atualSala ].inimigosT1[ i ].VIVO )
                                if( CheckCollisionPointRec( jogo->salas[ jogo->atualSala ].inimigosT1[ i ].posMundo , jogo->MapaDesenho ) )
                                        DrawRectangle( jogo->salas[ jogo->atualSala ].inimigosT1[ i ].posTela.x , jogo->salas[ jogo->atualSala ].inimigosT1[ i ].posTela.y , 30 , 30 , ORANGE );

        DrawText( TextFormat("(%.2f , %.2f)" ,  jogo->salas[ 0 ].inimigosT1[ 0 ].posTela.x , jogo->salas[ 0 ].inimigosT1[ 0 ].posTela.y ), 300 , 500 , 30 , RED );
        DrawText( TextFormat("(%.2f , %.2f)" ,  jogo->salas[ 0 ].inimigosT1[ 0 ].posMundo.x , jogo->salas[ 0 ].inimigosT1[ 0 ].posMundo.y ), 300 , 550 , 30 , RED );

}
//##############################################################################

///**     Funcao DesenhaSpawns():

void DesenhaSpawns( Jogo *jogo)
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

void DesenhaDebug(Jogo *jogo)
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
                        px[ i ] = jogo->salas[ jogo->atualSala ].inimigosT1[ i ].posMundo.x;
                        py[ i ] = jogo->salas[ jogo->atualSala ].inimigosT1[ i ].posMundo.y;
                }
                laten = 50;
        }
        else
                laten--;

        for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtd_inimigos_liberados ; i++ )
                DrawText( TextFormat("INIM T1 %d | VIVO: %d | POS(%.0f , %.0f) " , i , jogo->salas[ jogo->atualSala ].inimigosT1[ i ].VIVO , px[ i ] , py[ i ] ) , 700 , 100 + 30*i , 25 , VIOLET );

        #include "logicajogo.h"
//        DrawText(TextFormat("MENOR  = %d   |  DIST= %.0f" , CalcularSpawnPerto( jogo ) , distancia( jogo->jogador.PosMundo , jogo->salas[ jogo->atualSala ].spawns[ CalcularSpawnPerto( jogo ) ]. ) ) , 20 , 400 ,50 , DARKBLUE);

}
//##############################################################################


