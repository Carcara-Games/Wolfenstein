
#include "desenhajogo.h"
#include "definicoes.h"

/**     Funcao DesenhaLevel(): Desenha o level atual
    */

void DesenhaLevel( Jogo *jogo)
{
        BeginDrawing();

        DesenhaMapa( jogo );
        //DesenhaPortas( jogo );
        DesenhaPes( jogo);
        DesenhaJogador( jogo );

//        DesenhaDebug( jogo );

        EndDrawing();

        if( jogo->PASSAGEM ) PassagemPorta();
}
//##############################################################################



/**     Funcao DesenhaMapa():
    */
void DesenhaMapa( Jogo *jogo)
{
        Vector2 pos;
        pos.x = 0;
        pos.y = 0;

        DrawTexturePro( jogo->Res.Mapa , jogo->MapaDesenho , jogo->tela , pos , 0 , WHITE );
}
//##############################################################################



/**     Funcao DesenhaPes():
    */
void DesenhaPes( Jogo *jogo)
{
//        DrawTexturePro( jogo.Res.Pes[ jogo.jogador.atualStatus ][ jogo.jogador.atualFrame ] , jogo.jogador.Src , jogo.jogador.PosTela , jogo.jogador.Origin , jogo.jogador.Rotac , WHITE );
//        DrawTexturePro( jogo.Res.Pes[ jogo.jogador.atualMovTipo ][ jogo.spriteDef.atualFramePes ] , jogo.spriteDef.SrcPes , jogo.jogador.PosTelaPes , jogo.spriteDef.OriginPes , jogo.jogador.Rotac , WHITE );
        DrawTexturePro( jogo->Res.Pes[ jogo->jogador.atualMovTipo ][ jogo->spriteDef.atualFramePes ] , jogo->spriteDef.SrcPes , jogo->jogador.PosTelaPes , jogo->spriteDef.OriginPes , jogo->jogador.Rotac , WHITE );
}
//##############################################################################



/**     Funcao DesenhaJogador():
    */
void DesenhaJogador( Jogo *jogo)
{
//        DrawRectanglePro( jogo.jogador.PosTela , jogo.jogador.Origin , /*jogo.jogador.Rotac*/0 , BLUE );
//        DrawRectanglePro( jogo.jogador.PosTela , /*jogo.jogador.Origin*/ (Vector2){ 0 , 0 } , /*jogo.jogador.Rotac*/0 , BLUE );
//        DrawTexturePro( jogo.Res.Per[0][0][0] , jogo.jogador.Src , jogo.jogador.PosTela , jogo.jogador.Origin , jogo.jogador.Rotac , WHITE );
        DrawTexturePro( jogo->Res.Per[0][ jogo->jogador.atualStatus ][ jogo->spriteDef.atualFrame ] , jogo->spriteDef.Src , jogo->jogador.PosTela , jogo->spriteDef.Origin , jogo->jogador.Rotac , WHITE );
}
//##############################################################################



/**     Funcao DesenhaPortas(): Desenha as portas trancadas
    */

void DesenhaPortas( Jogo *jogo)
{
        int i ;

        for( i = 0 ; i < jogo->salas[ jogo->atualSala ].qtdPortas ; i++ )
                if( !jogo->salas[ jogo->atualSala ].portas[ i ].DESTRANCADA )
                        if( CheckCollisionPointRec( jogo->salas[ jogo->atualSala ].portas[ i ].pos , jogo->MapaDesenho ) )
                                DrawTexture( jogo->Res.Portas , ESCALA * (jogo->salas[ jogo->atualSala ].portas[ 0 ].pos.x -  jogo->MapaDesenho.x) , ESCALA * (jogo->salas[ jogo->atualSala ].portas[ 0 ].pos.y -  jogo->MapaDesenho.y) , WHITE );
}
//        for( i = 0 ; i < jogo->dadosLevel.salas[ i ].qtdPortas ; i++ )
//                DrawTextureEx( jogo->Res.Portas , jogo->dadosLevel.salas[ i ].portas.pos , jogo->dadosLevel.salas[ i ].portas.rotac , 1 , WHITE );

//##############################################################################

///Função PassagemPorta

void PassagemPorta( void )
{
        int i = FPS / 8;

        for(  ; i ; i-- )
        {
                BeginDrawing();
                        ClearBackground( BLACK );
                EndDrawing();
        }
}
//##############################################################################


///Função DesenhaDebug

void DesenhaDebug( Jogo *jogo )
{
//        int i;
//        int j;
//        Color cor;
//        char stt[] = {"\0"};

        ///Inforamacoes Gerais
        DrawText( TextFormat("( %.2f , %.2f)" , jogo->jogador.PosMundo.x , jogo->jogador.PosMundo.y ) , 10 , 10 , 60 , RAYWHITE );
        DrawText( TextFormat("RESOLUCAO:( %d , %d)" , GetScreenWidth()  , GetScreenHeight() ) , 10 , 700 , 60 , PINK );
        DrawText( TextFormat("MAPA Desenho:( %.2f , %.2f)" , jogo->MapaDesenho.x  , jogo->MapaDesenho.y ) , 10 , 80 , 60 , RAYWHITE );
        DrawText( TextFormat("MAPA Tamanho:( %.2f , %.2f)" , jogo->MapaTamanho.x  , jogo->MapaTamanho.y ) , 10 , 160 , 60 , RAYWHITE );
        DrawText( TextFormat("( atual sala : %d)" , jogo->atualSala ) , 10 , 100 , 60 , SKYBLUE );
//                if( jogo->jogador.testeFlagTiro )
//                        DrawCircle( 70 , 700 , 30 , RED );
//                DrawText( TextFormat("ARMA %d" , jogo->jogador.atualArma ) , 20 , 430 , 50 , YELLOW );
//                DrawText( TextFormat("FRAME_PER %d" , jogo->spriteDef.atualFrame ) , 20 , 550 , 25 , YELLOW );
                DrawText( TextFormat("FRAME_PES %d" , jogo->spriteDef.atualFramePes ) , 20 , 550 , 25 , YELLOW );
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
}
//##############################################################################



