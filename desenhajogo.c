
#include "desenhajogo.h"
#include "definicoes.h"

/**     Funcao DesenhaMapa():
    */
void DesenhaMapa( Jogo jogo)
{
        Vector2 pos;
        pos.x = 0;
        pos.y = 0;

        DrawTexturePro( jogo.Res.Mapa , jogo.MapaDesenho , jogo.tela , pos , 0 , WHITE );
        DrawText( TextFormat("( %.2f , %.2f)" , jogo.jogador.PosMundo.x , jogo.jogador.PosMundo.y ) , 10 , 10 , 60 , MAROON );
        DrawText( TextFormat("( atual sala : %d)" , jogo.atualSala ) , 10 , 100 , 60 , SKYBLUE );
//        DrawText( TextFormat("( %.2f , %.2f)" , jogo.MapaDesenho.x , jogo.MapaDesenho.y ) , 10 , 70 , 30 , WHITE );
//        DrawText( TextFormat("( %.2f , %.2f)" , ESCALA * (jogo.salas[ jogo.atualSala ].portas[ 0 ].pos.x -  jogo.MapaDesenho.x) , ESCALA * (jogo.salas[ jogo.atualSala ].portas[ 0 ].pos.y -  jogo.MapaDesenho.y ) ) , 10 , 70 , 30 , WHITE );
//        DrawText( TextFormat("( %.2f , %.2f)" , ESCALA * (jogo.salas[ jogo.atualSala ].portas[ 1 ].pos.x -  jogo.MapaDesenho.x) , ESCALA * (jogo.salas[ jogo.atualSala ].portas[ 1 ].pos.y -  jogo.MapaDesenho.y ) ) , 10 , 70 , 30 , WHITE );
//        DrawText( TextFormat(" P=%d , Z=%d " , jogo.salas[ jogo.atualSala ].qtdPortas , jogo.salas[ 0 ].qtdZonas ) , 10 , 100 , 60 , GREEN );
//        DrawText( TextFormat(" P=%d , Z=%d " , jogo.salas[ jogo.atualSala ].qtdPortas , jogo.salas[ 0 ].qtdZonas ) , 10 , 100 , 60 , GREEN );
//        DrawText( TextFormat(" xP = %.2f  |  yP=%.2f " , jogo.salas[ jogo.atualSala ].portas[ 0 ].pos.x , jogo.salas[ jogo.atualSala ].portas[ 0 ].pos.y ) , 10 , 200 , 40 , SKYBLUE );
//        DrawText( TextFormat(" xP = %.2f  |  yP=%.2f " , jogo.salas[ jogo.atualSala ].portas[ 1 ].pos.x , jogo.salas[ jogo.atualSala ].portas[ 1 ].pos.y ) , 10 , 200 , 40 , SKYBLUE );
}
//##############################################################################


/**     Funcao DesenhaJogador():
    */
void DesenhaJogador( Jogo jogo)
{
        DrawRectanglePro( jogo.jogador.PosTela , jogo.jogador.Origin , /*jogo.jogador.Rotac*/0 , BLUE );
}
//##############################################################################

/**     Funcao DesenhaLevel(): Desenha o level atual
    */

void DesenhaLevel( Jogo jogo)
{
        BeginDrawing();

        DesenhaMapa( jogo );
        //DesenhaPortas( jogo );
        DesenhaJogador( jogo );


        EndDrawing();

        //if( jogo.PASSAGEM ) PassagemPorta();
}
//##############################################################################



/**     Funcao DesenhaPortas(): Desenha as portas trancadas
    */

void DesenhaPortas( Jogo jogo)
{
        int i ;

        for( i = 0 ; i < jogo.salas[ jogo.atualSala ].qtdPortas ; i++ )
                if( !jogo.salas[ jogo.atualSala ].portas[ i ].DESTRANCADA )
                        if( CheckCollisionPointRec( jogo.salas[ jogo.atualSala ].portas[ i ].pos , jogo.MapaDesenho ) )
                                DrawTexture( jogo.Res.Portas , ESCALA * (jogo.salas[ jogo.atualSala ].portas[ 0 ].pos.x -  jogo.MapaDesenho.x) , ESCALA * (jogo.salas[ jogo.atualSala ].portas[ 0 ].pos.y -  jogo.MapaDesenho.y) , WHITE );
}
//        for( i = 0 ; i < jogo.dadosLevel.salas[ i ].qtdPortas ; i++ )
//                DrawTextureEx( jogo.Res.Portas , jogo.dadosLevel.salas[ i ].portas.pos , jogo.dadosLevel.salas[ i ].portas.rotac , 1 , WHITE );

//##############################################################################

///Fun��o PassagemPorta

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
