
#include "desenhamenu.h"
#include "definicoes.h"

/** Funcao DesenhaMenuPrincipal() : Desenha o menu quando programa esta na parte inicial
    *
    */

#define COR_MENU_COMUM WHITE          // Cor do texto do menu nao selecionado
#define COR_MENU_SELECAO GOLD          // Cor do texto do menu selecionado
Music musMenu;
void DesenhaMenuPrincipal(JOGO* jogo, int selecao )
{
        static int flag_inic = 1;
//        int i ;
//
//        const int QTD_OPCOES = 7;     // Quantidade de opcoes no menu
//        const int FONT_SIZE = 30;   // Tamanho da fonte
//
//        const int VARIACAO_ALTURA = FONT_SIZE * 1.5;    // Variacao de altura entre cada item dado pelo tamanho da letra
//        const int ALTURA_ITEM_0 = GetScreenWidth() / 4;   //Posicao Y do primeiro item menu

        if( flag_inic ){
                musMenu = LoadMusicStream("Som/MusicMenu2.mp3");
                PlayMusicStream( musMenu );
                flag_inic = 0;
        }


        if( jogo->jogador.venceu )
                UpdateMusicStream( jogo->Res.musica_final );
        else
                UpdateMusicStream( musMenu );

        BeginDrawing();

                //Desenhar Plano de Fundo
                DrawTexturePro( jogo->Res.MenuFundo[ selecao ] , (Rectangle){ 0 , 0 , jogo->Res.MenuFundo[ selecao ].width , jogo->Res.MenuFundo[ selecao ].height } , jogo->tela  , (Vector2){ 0 , 0 } , 0 , WHITE );
//                DrawTexturePro( LoadTexture("Menu_Imagens/MenuPrincipal.png") , (Rectangle){ 0 , 0 , jogo->Res.MenuFundo.width , jogo->Res.MenuFundo.height } , jogo->tela  , (Vector2){ 0 , 0 } , 0 , WHITE );
//                NomeWolfenEntrada( jogo , selecao );  //Nome Wolfenstein com efeito de entrada
//                DrawTextureEx( jogo->Res.Logo , (Vector2 ){ 5 , 5 } , 0 ,  .2 , WHITE );  //Mini logo no canto superior esquerdo

//                //Itens N?o Selecionados
//                for( i = 0 ; i < QTD_OPCOES ; i++)
//                        DrawText( opcoes[ i ]  , CentraTextoX( opcoes[ i ] , FONT_SIZE ) , ALTURA_ITEM_0 + i * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_COMUM  );
//
//                //Item Selecionado
//                DrawText( opcoes[ selecao ] , CentraTextoX( opcoes[ selecao ] , FONT_SIZE) , ALTURA_ITEM_0 + selecao * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_SELECAO);
//
        EndDrawing();

}
//##############################################################################



/**     Funcao DesenhaMenuDificuldade() : Desenha o menu de escolha de dificuldade
    */

#define RECRUTA 0
#define SOLDADO 1
#define VETERANO 2
#define CHUCK_NORRIS 3
#define VOLTAR 4

void DesenhaMenuDificuldade( JOGO *jogo , int selecao )
{
        int i ;

        const int QTD_OPCOES = 4;     // Quantidade de opcoes no menu
        const int FONT_SIZE = 30;   // Tamanho da fonte
        const int FONT_SIZE_M1 = 50;   // Tamanho da fonte
        const int FONT_SIZE_M2 = 20;   // Tamanho da fonte

        const int VARIACAO_ALTURA = FONT_SIZE * 1.5;    // Variacao de altura entre cada item dado pelo tamanho da letra
        const int ALTURA_ITEM_0 = GetScreenWidth() / 4;   //Posicao Y do primeiro item menu
        const int ALTURA_ITEM_VOLTAR = ALTURA_ITEM_0 + QTD_OPCOES * VARIACAO_ALTURA + 30 ;   //Posicao Y do primeiro item menu

//        Rectangle imagem;
//        imagem.height = jogo->Res.TelaDeFundo.height ;
//        imagem.width = jogo->Res.TelaDeFundo.width ;
//        imagem.x = 0 ;
//        imagem.y = 0 ;

//        Vector2 pos = (Vector2 ){ 0 , 0 };

        UpdateMusicStream( musMenu );


        BeginDrawing();
                //Desenhar Plano de Fundo
                DrawTexturePro( jogo->Res.TelaDeFundo , (Rectangle){ 0 , 0 , jogo->Res.TelaDeFundo.width , jogo->Res.TelaDeFundo.height } , jogo->tela  , (Vector2){ 0 , 0 } , 0 , WHITE );

                DrawText( ItensMenuDificuldade( 5 ) , CentraTextoX( ItensMenuDificuldade( 5 ) , FONT_SIZE_M1 ) , ALTURA_ITEM_0 - 70 , FONT_SIZE_M1 , WHITE);
                DrawText( ItensMenuDificuldade( 6 ) , CentraTextoX( ItensMenuDificuldade( 6 ) , FONT_SIZE_M2 ) , GetScreenHeight() - 30 , FONT_SIZE_M2 , WHITE);

                //Itens N?o Selecionados
                for( i = 0 ; i < QTD_OPCOES ; i++)
                        DrawText( TextFormat( ItensMenuDificuldade( i ) )  , CentraTextoX( ItensMenuDificuldade( i ) , FONT_SIZE ) , ALTURA_ITEM_0 + i * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_COMUM  );

                DrawText( ItensMenuDificuldade( VOLTAR ) , CentraTextoX( ItensMenuDificuldade( VOLTAR) , FONT_SIZE) , ALTURA_ITEM_VOLTAR , FONT_SIZE , COR_MENU_COMUM);

                //Item Selecionado
                if( selecao != VOLTAR)
                        DrawText( ItensMenuDificuldade( selecao ) , CentraTextoX( ItensMenuDificuldade( selecao) , FONT_SIZE) , ALTURA_ITEM_0 + selecao * VARIACAO_ALTURA , FONT_SIZE , COR_MENU_SELECAO);
                else
                        DrawText( ItensMenuDificuldade( selecao ) , CentraTextoX( ItensMenuDificuldade( selecao) , FONT_SIZE) , ALTURA_ITEM_VOLTAR , FONT_SIZE , COR_MENU_SELECAO);
        EndDrawing();


}
//##############################################################################



/**     Funcao DesenharObrigado(): Desenha obrigado na tela
    */
void DesenharObrigado( void )
{
        char obrigado[] = "Obrigado por jogar!";
        int fontsize = 50;
        int i;

        for( i = FPS * 2 ; i ; i-- )
        {
                BeginDrawing();
                        ClearBackground( BLACK );
                        DrawText( obrigado , CentraTextoX( obrigado , fontsize ) , GetScreenHeight() / 2 , fontsize , RAYWHITE);
                EndDrawing();
        }


}
//##############################################################################



/**     Funcao NomeWolfenEntrada() : Escreve Wolfenstein com efeito legal
    */

#define HWOLF 150    //Posicao Y na tela do nome Wolfenstein
#define FONT_SIZE_WOLF 130    // Tamanho na tela do nome Wolfenstein
#define MULT 5
#define ESP_WOLF 7
#include <math.h>
void NomeWolfenEntrada( JOGO *jogo , int selecao  )
{
        static int i = 0 , j = 10 * MULT;
        int k , f , L1 , L2;
        const char Nome[ 12 ] = "WOLFENSTEIN";
        char Escreva[ 12 ] = "           ";

        if( jogo->NivelMenu != 0  &&  selecao != ITENS_MAIN_MENU - 1  &&  selecao != ITENS_MAIN_MENU - 2 )  // Em SAIR e em SOBRE n?o renicia o efeito do nome
        {
                jogo->NivelMenu = 0;
                i = 0;
                j = 10 * MULT;
        }
        //Sobrescreve com nome certo de 0 at? i e do final at? j
        if( i <= j )
        {
                for( k = 0 , f = 11 * MULT ; k <= i &&  f >= j ; k++ , f-- )
                {
                        L1 = k / MULT;
                        L2 = ceil( f / MULT);

                        Escreva[ L1 ] = Nome[ L1 ];
                        Escreva[ L2 ] = Nome[ L2 ];
                }
                i++;
                j--;
        }
        else
                TextCopy( Escreva , Nome );

        DrawTextEx( jogo->Res.fonteWolfen ,  Escreva , (Vector2){ CentraTextoXEX( jogo->Res.fonteWolfen , Escreva , FONT_SIZE_WOLF , ESP_WOLF  )  ,  HWOLF / ( 27 - i ) }  , FONT_SIZE_WOLF , ESP_WOLF , WHITE );


}
//##############################################################################



/**     Funcao CentraTextoX() : Centraliza o texto em relacao ? largura da tela
    *           -> Entradas: Endere?o do texto e Tamanho da fonte.
    */

int CentraTextoX( char *texto , int fontsize )
{
        return ( GetScreenWidth() - MeasureText( texto , fontsize ) ) / 2 ;
}
//##############################################################################



/**     Funcao CentraTextoXEX() : Centraliza o texto em rela??o ? largura da tela extendida
    *           -> Entradas: Tipo de fonte , Endere?o do texto ,Tamanho da fonte e Espa?amento.
    */

int CentraTextoXEX( Font fonte , char *texto , float fontsize , float space)
{
        return ( GetScreenWidth() - MeasureTextEx( fonte , texto , fontsize , space ).x ) / 2 ;
}
//##############################################################################



/**     Funcao DesenhaSobre(): Desenha a janela de informa??es sobre a autoria do jogo
    */
#include "logicajogo.h"
void DesenhaSobre( JOGO jogo)
{
//        long int tempoInicial;
//        BOOL sair = false;
//        const int fonte = 25 ;
//        const int escala = 1.3;

//        Rectangle Janela ;
//        Janela.width = escala * jogo.Res.FundoConfirmarSair.width;
//        Janela.height = escala * jogo.Res.FundoConfirmarSair.height;
//        Janela.x = ( GetScreenWidth() - Janela.width ) / 2; // ( jogo->janela.width - Janela.width ) / 2
//        Janela.y = 2 * ( GetScreenHeight() - Janela.height ) / 3; //2 * ( jogo->janela.height - escala * jogo.Res.FundoConfirmarSair.height ) / 3
//
//        int ESPY = 18 , ESPX = 25;
//
//        do{
//                BeginDrawing();
//
//                        DrawTexture( jogo.Res.TelaDeFundo , 1 , 1 , WHITE );
//                        NomeWolfenEntrada( &jogo , ITENS_MAIN_MENU - 1 );
//                        DrawTextureEx(  jogo.Res.FundoConfirmarSair , (Vector2 ){ Janela.x , Janela.y } , 0 , escala , WHITE );
//
//                        DrawTextEx( jogo.Res.fonteWolfen ,    "WOLFENSTEIN 1.0" , (Vector2 ){ Janela.x + ESPX , Janela.y + ESPY } , fonte , 3 , WHITE );
//                        DrawText(TextFormat("Escrito por : ") , Janela.x + 2 * ESPX ,  Janela.y + 3 * ESPY , fonte , WHITE );
//                        DrawText("-Manoel Narciso Filho" , Janela.x + 3 * ESPX ,  Janela.y + 5 * ESPY , fonte , WHITE );
//                        DrawText("-Matheus De Moraes Costa" , Janela.x + 3 * ESPX ,  Janela.y + 7 * ESPY , fonte , WHITE );
//                        DrawText("BRASIL 2021" , Janela.x + ( Janela.width - MeasureText( "BRASIL 2021" , fonte ) ) / 2 , Janela.y + Janela.height - 85 , fonte , WHITE );
//                        DrawText("VOLTAR" , Janela.x + ( Janela.width - MeasureText( "VOLTAR" , fonte ) ) / 2 , Janela.y + Janela.height - 45 , fonte , GOLD );
//
//                EndDrawing();
//        }while( !IsKeyPressed( KEY_ENTER ) );
//
        for( int z = 10 ; z ; z-- ){
                BeginDrawing();
                        if( jogo.jogador.venceu ) UpdateMusicStream( jogo.
                                                                    Res.musica_final );
                        else UpdateMusicStream( musMenu );
                        DrawTexture( jogo.Res.TelaDeFundo , 1 , 1 , WHITE );
                EndDrawing();
        }


        for( int z = 10 ; z ; z-- ){
                BeginDrawing();
                        UpdateMusicStream( jogo.Res.musica_final );
//                        NomeWolfenEntrada( &jogo , ITENS_MAIN_MENU - 1 );
                        DrawTextureEx(  jogo.Res.FundoConfirmarSair , (Vector2 ){( jogo.tela.width - 1.4 * jogo.Res.FundoConfirmarSair.width ) / 2 , 2 * ( jogo.tela.height - 1.3 * jogo.Res.FundoConfirmarSair.height ) / 3 } , 0 , 1.3 , WHITE );

                        DrawTextEx( jogo.Res.fonteWolfen ,    "WOLFENSTEIN 1.0" , (Vector2 ){( jogo.tela.width - 1.3 * jogo.Res.FundoConfirmarSair.width ) / 2 + 18 , 2 * ( jogo.tela.height - 1.3 * jogo.Res.FundoConfirmarSair.height ) / 3 + 25 } , 25 , 3 , WHITE );
                        DrawText(TextFormat("Escrito por : ") ,( jogo.tela.width - 1.3 * jogo.Res.FundoConfirmarSair.width ) / 2 + 2 * 18 ,  2 * ( jogo.tela.height - 1.3 * jogo.Res.FundoConfirmarSair.height ) / 3 + 3 * 25 , 25 , WHITE );
                        DrawText("-Manoel Narciso Reis Soares Filho" ,( jogo.tela.width - 1.3 * jogo.Res.FundoConfirmarSair.width ) / 2 + 3 * 18 ,  2 * ( jogo.tela.height - 1.3 * jogo.Res.FundoConfirmarSair.height ) / 3 + 5 * 25 , 25 , WHITE );
                        DrawText("-Matheus De Moraes Costa" ,( jogo.tela.width - 1.3 * jogo.Res.FundoConfirmarSair.width ) / 2 + 3 * 18 ,  2 * ( jogo.tela.height - 1.3 * jogo.Res.FundoConfirmarSair.height ) / 3 + 7 * 25 , 25 , WHITE );
//                        DrawText("UFRGS 1? SEMESTRE" ,( jogo.tela.width - 1.3 * jogo.Res.FundoConfirmarSair.width ) / 2 + ( 1.3 * jogo.Res.FundoConfirmarSair.width - MeasureText( "UFRGS 1? SEMESTRE" , 25 ) ) / 2 , 2 * ( jogo.tela.height - 1.3 * jogo.Res.FundoConfirmarSair.height ) / 3 + 1.3 * jogo.Res.FundoConfirmarSair.height - 85 , 25 , WHITE );
                        DrawText("BRASIL 2021" ,( jogo.tela.width - 1.3 * jogo.Res.FundoConfirmarSair.width ) / 2 + ( 1.3 * jogo.Res.FundoConfirmarSair.width - MeasureText( "BRASIL 2021" , 25 ) ) / 2 , 2 * ( jogo.tela.height - 1.3 * jogo.Res.FundoConfirmarSair.height ) / 3 + 1.3 * jogo.Res.FundoConfirmarSair.height - 85 , 25 , WHITE );
                        DrawText("VOLTAR" ,( jogo.tela.width - 1.3 * jogo.Res.FundoConfirmarSair.width ) / 2 + ( 1.3 * jogo.Res.FundoConfirmarSair.width - MeasureText( "VOLTAR" , 25 ) ) / 2 , 2 * ( jogo.tela.height - 1.3 * jogo.Res.FundoConfirmarSair.height ) / 3 + 1.3 * jogo.Res.FundoConfirmarSair.height- 45 , 25 , GOLD );
                EndDrawing();
        }

        do{
                BeginDrawing();
                EndDrawing();
        }while( !IsKeyPressed( KEY_ENTER )  );
}
//##############################################################################



/**     Funcao DesenharConfirmarSair() : Retorna os itens do menu de escolha de dificuldade
    */
void DesenharConfirmarSair( int selecao , JOGO *jogo )
{
        Rectangle Janela ;
        Janela.width = 550;
        Janela.height = 100;
        Janela.x = ( GetScreenWidth() - Janela.width ) / 2;
        Janela.y = ( GetScreenHeight() - Janela.height ) / 2;
        const int fonte = 30 ;

        Color cor0;
        Color cor1;

        BeginDrawing();
                if( jogo->jogador.venceu ) UpdateMusicStream( jogo->Res.musica_final );
                else UpdateMusicStream( musMenu );
                DrawTexture( jogo->Res.TelaDeFundo , 1 , 1 , WHITE );
                NomeWolfenEntrada( jogo , ITENS_MAIN_MENU - 1 );
//                DrawTexturePro(  jogo->Res.FundoConfirmarSair , Janela , Janela , (Vector2 ){ Janela.x , Janela.y } ,  0 , WHITE );
                DrawTextureEx(  jogo->Res.FundoConfirmarSair , (Vector2 ){ Janela.x , Janela.y } , 0 , 1 , WHITE );

                cor0 = selecao ? WHITE : GOLD;
                cor1 = selecao ? GOLD : WHITE;

                DrawText("Tem certeza ?" , Janela.x + Janela.width / 3 - 40 ,  Janela.y + Janela.height / 2, fonte , WHITE );
                DrawText("  ~ " , Janela.x + Janela.width / 3 - 50 ,  Janela.y + Janela.height / 2 + 65, fonte , cor0 );
                DrawText("NAO" , Janela.x + Janela.width / 3 - 50 ,  Janela.y + Janela.height / 2 + 85, fonte , cor0 );
                DrawText("SIM" , Janela.x + 2 * Janela.width / 3 - 50 ,  Janela.y + Janela.height / 2 + 85 , fonte , cor1 );

        EndDrawing();
}
//##############################################################################
