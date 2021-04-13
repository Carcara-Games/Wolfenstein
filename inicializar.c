
#include "inicializar.h"


/**     Funcao IniciarJanela() : Inicia janela do jogo
    */

void IniciarJanela( void )
{
        int TelaLargura = GetMonitorWidth(0);
        int TelaAltura = GetMonitorHeight (0);

        InitWindow( TelaLargura , TelaAltura , "WOLFENSTEIN" );
        SetTargetFPS( FPS );
        ToggleFullscreen();
        SetExitKey( EXITKEY );
//        DisableCursor(); Its a Top Down Shooter game, so I will need my mouse
}



/** Função  IniciaJogo() :
    */

Jogo IniciaJogo( void )
{
        Jogo jogo;

        jogo.Res.Logo =  LoadTexture("Logo/Logo.png");   // Imagem de fundo (Logo)
        jogo.Res.MenuFundo =  LoadTexture("Menu_Imagens/MenuPrincipal.png");   // Imagem do plano de fundo
        jogo.Res.TelaDeFundo =  LoadTexture("Menu_Imagens/FundoLimpo.png");
        jogo.Res.fonteWolfen =    LoadFontEx("Fontes/ReturnToCastle-MZnx.ttf"  ,96 , 0 , 0);
        jogo.Res.fonteWolfen2 =    LoadFontEx("Fontes/wolfenstein.ttf"  ,96 , 0 , 0);
        jogo.Res.FundoConfirmarSair =    LoadTexture("Menu_Imagens/FundoConfirmarSair.png");
        jogo.Res.Mapa =    LoadTexture("Mapa/Mapa.png");
        jogo.Res.Portas =    LoadTexture("Mapa/Portas.png");

        jogo.FECHAR = 0;

        jogo.tela.width = GetScreenWidth();
        jogo.tela.height = GetScreenHeight();

        jogo.jogador.XMapa = 30;
        jogo.jogador.YMapa = 570;

        return jogo;
}



/**     Funcao CarregarLevel(): Carrega os levels
    */
void CarregarLevel( Jogo *jogo)
{
//        int i;

//        switch( jogo->Level )
        {
//                case 1:
                        // Definindo Informações do level
//                        jogo->dadosLevel.TERMINADO = 0 ;
//                        jogo->dadosLevel.qtdBaus = 1 ;//alet md
//                        jogo->dadosLevel.qtdInimT1 = 1 ;//alet md
//                        jogo->dadosLevel.qtdInimT2 = 0 ;//alet md
//                        jogo->dadosLevel.qtdPortas = 1 ;//alet md
//                        jogo->dadosLevel.qtdSpawnsT1 = 2 ;//alet md

                        // Definindo Baús
//                        jogo->dadosLevel.baus = (Bau *)malloc( jogo->dadosLevel.qtdBaus * sizeof( Bau) );  // Alocando dinamicamente array dos baus

                        //Itens
//                        for( i = 0 ; i < jogo->dadosLevel.qtdBaus ; i++ )
//                        {
//                                jogo->dadosLevel.baus[ i ].ABERTO = 0 ;
//                                jogo->dadosLevel.baus[ i ].KitMedicoP = 1;
//                                jogo->dadosLevel.baus[ i ].KitMedicoG = 0;
//                                jogo->dadosLevel.baus[ i ].MunEspingarda = 0;
//                                jogo->dadosLevel.baus[ i ].MunGranada = 1;
//                                jogo->dadosLevel.baus[ i ].MunPistola = GetRandomValue( 10 , 20) ;
//                                jogo->dadosLevel.baus[ i ].MunRifle = 0;
//                                jogo->dadosLevel.baus[ i ].vidaUp = 0 ;
//                                jogo->dadosLevel.baus[ i ].XP = GetRandomValue( 10 , 100);
//                        }

                        //Posicionamento
//                        jogo->dadosLevel.baus->Rotac = 1 ;//alet md
//                        jogo->dadosLevel.baus->px = 15 ;  //alet md
//                        jogo->dadosLevel.baus->py = 15;  //alet md
//                        break;;

        }

}
//##############################################################################



/**     Função CriaSalas() : Crias as salas do jogo , definindo posição de portas e de baús , limites de vizualização ,  etc
   */

void CriaSalas( Jogo *jogo)
{
        jogo->salas[ 1 ].limEsq = 0;
        jogo->salas[ 1 ].limDir = 1490;
        jogo->salas[ 1 ].limInf = 700;
        jogo->salas[ 1 ].limSup = 560;

}
