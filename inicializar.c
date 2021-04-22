
#include "inicializar.h"
#include "definicoes.h"


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
        jogo.Res.Per =    LoadTexture("Sprites/Top_Down_Survivor/handgun/idle/survivor-idle_handgun_0.png");

        jogo.FECHAR = 0;

        //Tela
        jogo.tela.x = 0;
        jogo.tela.y = 0;
        jogo.tela.width = GetScreenWidth();
        jogo.tela.height = GetScreenHeight();

        //Posição Jogador Tela
        jogo.jogador.PosTela.width =  70;
        jogo.jogador.PosTela.height =  70;
        jogo.jogador.PosTela.x =  ( jogo.tela.width - jogo.jogador.PosTela.width) / 2;
        jogo.jogador.PosTela.y =  ( jogo.tela.height  -  jogo.jogador.PosTela.height ) / 2;

//        jogo.jogador.Origin.x = jogo.jogador.PosTela.x + jogo.jogador.PosTela.width / 2;
//        jogo.jogador.Origin.y = jogo.jogador.PosTela.y + jogo.jogador.PosTela.height / 2;
        jogo.jogador.Origin.x = 0;
        jogo.jogador.Origin.y = 0;

        //Posicao Jogador Mundo
        jogo.jogador.PosMundo.x = 102;
        jogo.jogador.PosMundo.y = 603;

        //Ajuste do Mapa do Jogo

        jogo.MapaTamanho.x = jogo.Res.Mapa.width;
        jogo.MapaTamanho.y = jogo.Res.Mapa.height;

        jogo.MapaDesenho.width = jogo.tela.width / ESCALA;
        jogo.MapaDesenho.height = jogo.tela.height / ESCALA;

        //Sala inicial
        jogo.atualSala = 0;

        //Criar Salas e zonas
        CriaSalas( &jogo );

        //Cria Portas
        CriaPortas( &jogo );

        //Passagem de portas
        jogo.PASSAGEM = 0;
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
        CriaZonas( jogo );
//        CriaPortas( jogo );

}


/**     Função CriaZonas() : Crias as zonas da sala , definindo limites de deslocamento
   */

void CriaZonas( Jogo *jogo)
{
        int i , j;
        int limites[ QTDSALAS ][ 20 ][ 4 ] = {           //Os limites de deslocamento(esq - 0 , sup - 1 , dir - 2 , inf - 3 ) de cada zona de cada sala
                { //sala 00
                        { 74 , 597 , 131 ,  1452 } ,    //z0
                        { 219 , 648 , 288 , 730 } ,     //z1
                        { 129 , 675 , 219 , 702 } ,      //z2
                        { 129 , 946 , 159 , 1008} ,     //z3
                        { 219 , 1224 , 288 , 1308 } ,    //z4
                        { 129 , 1254 , 219 , 1278 } ,   //z5
                        { 129 , 1398 , 660 , 1452 } ,   //z6
                        { 378 , 1219 , 432 , 1399 },     //z7
                        { 93 , 591 , 111 , 597 },    //p0
                        { 660 , 1416 , 669 , 1434 },    //p1
                        { 399 , 1215 , 414 , 1221 },     //p2
                },

                { //sala 01
                        { 765 , 1398 , 879 , 1452 },    //z11
                        { 753 , 1416 , 765 , 1437 }    //p1
                },

                { //sala 02
                        { 267 , 830 , 546 ,  1116 } ,    //z0
                        { 396 , 1113 , 417 , 1125 } ,     //z1
                        { 396 , 828 , 417 , 834 }       //z3
                },

                { //sala 03
                        { 381 , 612 , 432 ,  732 } ,    //z0
                        { 396 , 732 , 414 , 744 } ,     //z1
                        { 396 , 603 , 417 , 609 }       //z3
                },


                { //sala 04
                        { 267 , 327 , 543 ,  507 } ,    //z0
                        { 396 , 507 , 414 , 516 } ,     //z1
                        { 546 , 408 , 558 , 426 }       //z3
                },

                { //sala 05
                        { 651 , 390 , 831 ,  444 } ,    //z0
                        { 717 , 231 , 771 , 384 } ,     //z1
                        { 771 , 231 , 960 , 282 } ,      //z3
                        { 960 , 946 , 975 , 267} ,     //p
                        { 639 , 408 , 654 , 426 } ,    //p
                },

        };

        //Quantidade de zonas de cada sala
        jogo->salas[ 0 ].qtdZonas =  12;
        jogo->salas[ 1 ].qtdZonas =  2;
        jogo->salas[ 2 ].qtdZonas =  3;
        jogo->salas[ 3 ].qtdZonas =  3;
        jogo->salas[ 4 ].qtdZonas =  3;
        jogo->salas[ 5 ].qtdZonas =  5;


        //Atribuindo Limites
//        for( i = 0 ; i < QTDSALAS ; i++)
        for( i = 0 ; i < 5 ; i++)
                for( j = 0 ; j < jogo->salas[ i ].qtdZonas; j++)
                {
                        jogo->salas[ i ].zonas[ j ].esq = limites[ i ][ j ][ 0 ];
                        jogo->salas[ i ].zonas[ j ].sup = limites[ i ][ j ][ 1 ];
                        jogo->salas[ i ].zonas[ j ].dir = limites[ i ][ j ][ 2 ];
                        jogo->salas[ i ].zonas[ j ].inf = limites[ i ][ j ][ 3 ];

                }
}


/**     Função CriaPortas() : Crias as portas da sala , definindo posicao de entrada e posicao de destino
   *                    obs: Portas se comportam como teleportes - alteram posicao do jogado e eventualmente atualSala
   */

void CriaPortas( Jogo *jogo)
{
        int i , j;
        int pos[ QTDSALAS ][ 10 ][ 2 ] = {           //As posicoes  das portas ( x-0 , y - 1 ) de cada porta de cada sala
                { //sala 00
                        { 669 , 1425 },    //p1
                        { 405 , 1215 }      //p2
                },

                { //sala 01
                        { 753 , 1425 },      //p1
                },

                { //sala 02
                        { 405 , 1123 },    //p1
                        { 405 , 841 },      //p2
                }


        };
        float rotac[ QTDSALAS ][ 10 ] = {           //A rotacao das portas ( x-0 , y - 1 ) de cada porta de cada sala
                {  0 /*p1*/ , -90/*p2*/ } ,     //sala00
                {  90 /*p1*/ } ,     //sala01
                {  180 /*p1*/ , 0/*p2*/ } ,     //sala03

        };

        int entrada[ QTDSALAS ][ 10 ][ 2 ] = {           //As coordenadas de entrada das portas ( x-0 , y - 1 ) de cada porta de cada sala
                { //sala 00
                        { 669 , 1425 } ,    //p1
                        { 405 , 1215 }      //p2
                },

                { //sala 01
                        { 753 , 1425 } ,    //p1
                },

                { //sala 02
                        { 405 , 1123 } ,    //p1
                        { 405 , 829 }      //p2
                },

                { //sala 03
                        { 405 , 744 } ,    //p1
                        { 405 , 612 }      //p2
                }


        };

        int destino[ QTDSALAS ][ 10 ][ 2 ] = {           //As coordenadas de destino das portas ( x-0 , y - 1 ) de cada porta de cada sala
                { //sala 00
                        { 756 , 1425 },     //p1
                        { 405 , 1120 }      //p2
                },

                { //sala 01
                        { 663+3 , 1425 },     //p1
                },

                { //sala 02
                        { 405 , 1219 } ,    //p1
                        { 405 , 744 }     //p2
                },

                { //sala 03
                        { 405 , 1222 } ,    //p1
                        { 405 , 1 }     //p2
                }

        };

        int status[ QTDSALAS ][ 10 ] = {           //O status de trancada/destrancada das portas ( destrancada=1 , trancada = 0 ) de cada porta de cada sala
                { 1/*p1*/ , 1/*p2*/ },      //sala00
                { 1/*p1*/ },      //sala01
                { 1/*p1*/ , 1/*p2*/ },      //sala02
        };


        int alterarPSala[ QTDSALAS ][ 10 ] = {           //A sala para qual as portas levam
                {  1 /*p1*/ , 2/*p2*/ },      //sala00
                {  0 /*p1*/ },      //sala01
                {  0 /*p1*/ , 3/*p2*/ }      //sala02

        };

        //Quantidade de portas de cada sala
        jogo->salas[ 0 ].qtdPortas =  2;
        jogo->salas[ 1 ].qtdPortas =  1;
        jogo->salas[ 2 ].qtdPortas =  2;
        jogo->salas[ 3 ].qtdPortas =  2;


        //Atribuindo Valores
//        for( i = 0 ; i < QTDSALAS ; i++)
        for( i = 0 ; i < 4 ; i++)
                for( j = 0 ; j < jogo->salas[ i ].qtdPortas; j++)
                {
                        jogo->salas[ i ].portas[ j ].pos.x = pos[ i ][ j ][ 0 ];
                        jogo->salas[ i ].portas[ j ].pos.y = pos[ i ][ j ][ 1 ];

                        jogo->salas[ i ].portas[ j ].entrada.x = entrada[ i ][ j ][ 0 ];
                        jogo->salas[ i ].portas[ j ].entrada.y = entrada[ i ][ j ][ 1 ];

                        jogo->salas[ i ].portas[ j ].destino.x = destino[ i ][ j ][ 0 ];
                        jogo->salas[ i ].portas[ j ].destino.y = destino[ i ][ j ][ 1 ];

                        jogo->salas[ i ].portas[ j ].DESTRANCADA = status[ i ][ j ];
                        jogo->salas[ i ].portas[ j ].alteraPSala = alterarPSala[ i ][ j ];


                }
}
