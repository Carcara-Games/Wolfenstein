
#include "inicializar.h"
#include "definicoes.h"


/**     Funcao IniciarJanela() : Inicia janela do jogo
    */

void IniciarJanela( void )
{
        ///Resolucao do Usuario
        int TelaLargura = GetMonitorWidth(0);
        int TelaAltura = GetMonitorHeight (0);

        ///Confuguracao de Janela
        InitWindow( TelaLargura , TelaAltura , "WOLFENSTEIN" );
        SetTargetFPS( FPS );
        ToggleFullscreen();
        SetExitKey( EXITKEY );
}


/** Função  IniciaJogo() :
    */

Jogo IniciaJogo( void )
{
        Jogo jogo;
        jogo.FECHAR = 0;

        ///Armas iniciais e Status iniciais
        //Inicial
        jogo.jogador.atualArma = 0;
        jogo.jogador.atualStatus = 0;
        jogo.spriteDef.atualFrame = 0;

        ///QTD de status para cada arma
        jogo.spriteDef.QTD_STATUS[ 0 ] = 5;      //pistola
        jogo.spriteDef.QTD_STATUS[ 0 ] = 5;      //SMG

                //Qtd de Frames para cada status de cada arma
                        //Pistola
        jogo.spriteDef.QTD_FRAMES[ 0 ][ 0 ] = 20;
        jogo.spriteDef.QTD_FRAMES[ 0 ][ 1 ] = 20;
        jogo.spriteDef.QTD_FRAMES[ 0 ][ 2 ] = 3;
        jogo.spriteDef.QTD_FRAMES[ 0 ][ 3 ] = 16;
        jogo.spriteDef.QTD_FRAMES[ 0 ][ 4 ] = 15;

        ///QTD de Frame para cada tipo de movimento
        jogo.spriteDef.QTD_FRAMES_PES[ 0 ] = 1;        //Repouso
        jogo.spriteDef.QTD_FRAMES_PES[ 1 ] = 20;       //Andando
        jogo.spriteDef.QTD_FRAMES_PES[ 2 ] = 20;       //Correndo
        jogo.spriteDef.QTD_FRAMES_PES[ 3 ] = 20;       //Movimento lateral para a esquerda
        jogo.spriteDef.QTD_FRAMES_PES[ 4 ] = 20;       //Movimento lateral para a direita

        ///Carregar Texturas e Fontes
        carregarTexturasFontes( &jogo );

        ///Tela
        jogo.tela.x = 0;
        jogo.tela.y = 0;

        if( GetScreenWidth() / (float)GetScreenHeight() == REF_TELA_LARG / (float)REF_TELA_ALT ){
                        jogo.tela.width = REF_TELA_LARG;        // A tela deve ficar cheia em largura
                        jogo.tela.height = REF_TELA_ALT;        // A altura deve ser regulada para manter a proporcao
                        jogo.regulagemTela = 0;
        }else{
                if( GetScreenWidth() / (float)GetScreenHeight() > REF_TELA_LARG / (float)REF_TELA_ALT ){         //A largura e proporionalmente maior
                        jogo.tela.width = GetScreenWidth();        // A tela deve ficar cheia em largura
                        jogo.tela.height = REF_TELA_ALT * jogo.tela.width / REF_TELA_LARG ;        // A altura deve ser regulada para manter a proporcao
                        jogo.regulagemTela = 1;
                }else{          // Nesse caso a altura e proporcionalmente maior
                        jogo.tela.height = GetScreenHeight();        // A tela deve ficar cheia em altura
                        jogo.tela.width =  REF_TELA_LARG * jogo.tela.height / REF_TELA_ALT ;        // A largura deve ser regulada para manter a proporcao
                        jogo.regulagemTela = 2;
                }
        }


        ///Posicao Jogador Tela
                ///Per
                jogo.jogador.PosTela.width =  LARG_PADRAO * jogo.tela.width / REF_TELA_LARG;
                jogo.jogador.PosTela.height =  jogo.jogador.PosTela.width * ALT_PADRAO / LARG_PADRAO;   //Altura Dependente da largura
                jogo.jogador.PosTela.x =  jogo.tela.width / 2;
                jogo.jogador.PosTela.y =  jogo.tela.height / 2;
        //        jogo.jogador.PosTela.x =  ( jogo.tela.width - jogo.jogador.PosTela.width) / 2;
        //        jogo.jogador.PosTela.y =  ( jogo.tela.height  -  jogo.jogador.PosTela.height ) / 2;

                ///Pes
                jogo.jogador.PosTelaPes.width =  ESC_PES * jogo.jogador.PosTela.width;
                jogo.jogador.PosTelaPes.height =  ESC_PES* jogo.jogador.PosTela.height;
                jogo.jogador.PosTelaPes.x =  jogo.jogador.PosTela.x;
                jogo.jogador.PosTelaPes.y =  jogo.jogador.PosTela.y;

        ///Posicao Jogador No Mundo
        jogo.jogador.PosMundo.x = 102;
        jogo.jogador.PosMundo.y = 603;

        ///Ajuste do Mapa do Jogo
                ///Tamanho Da Textura MAPA
                jogo.MapaTamanho.x = jogo.Res.Mapa.width;
                jogo.MapaTamanho.y = jogo.Res.Mapa.height;

                ///Area de Extracao ( FIXA )
                jogo.MapaDesenho.width = PIXEL_LARGURA_MAPA;
                jogo.MapaDesenho.height = PIXEL_ALTURA_MAPA;

        ///Sala inicial
        jogo.atualSala = 0;

        ///Criar Salas e zonas
        CriaSalas( &jogo );

        ///Cria Portas
        CriaPortas( &jogo );

        ///Passagem de portas
        jogo.PASSAGEM = 0;

        ///Retorno
        return jogo;
}
//##############################################################################



/** Função  carregarTexturasFontes() :
    */

void carregarTexturasFontes( Jogo *jogo )
{
        ///Texturas  Gerais
        jogo->Res.Logo =  LoadTexture("Logo/Logo.png");   // Imagem de fundo (Logo)
        jogo->Res.MenuFundo =  LoadTexture("Menu_Imagens/MenuPrincipal.png");   // Imagem do plano de fundo
        jogo->Res.TelaDeFundo =  LoadTexture("Menu_Imagens/FundoLimpo.png");
        jogo->Res.FundoConfirmarSair =    LoadTexture("Menu_Imagens/FundoConfirmarSair.png");
        jogo->Res.Mapa =    LoadTexture("Mapa/Mapa.png");
        jogo->Res.Portas =    LoadTexture("Mapa/Portas.png");

        ///Fontes
        jogo->Res.fonteWolfen =    LoadFontEx("Fontes/ReturnToCastle-MZnx.ttf"  ,96 , 0 , 0);
        jogo->Res.fonteWolfen2 =    LoadFontEx("Fontes/wolfenstein.ttf"  ,96 , 0 , 0);

        ///Sprites
        CarregarPersonagemImagens( jogo);      //Jogador
        CarregarPes( jogo );           //Pes do jogador
}
//##############################################################################



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
                        { 399 , 1215 , 414 , 1221 }     //p2
                },

                { //sala 01
                        { 765 , 1398 , 879 , 1452 },    //z0
                        { 753 , 1416 , 765 , 1437 }    //p1
                },

                { //sala 02
                        { 267 , 830 , 546 ,  1116 } ,    //z0
                        { 396 , 1113 , 417 , 1125 } ,     //p1
                        { 396 , 828 , 417 , 834 }       //p2
                },

                { //sala 03
                        { 381 , 612 , 432 ,  732 } ,    //z0
                        { 396 , 732 , 414 , 754 } ,     //p1
                        { 396 , 593 , 417 , 629 }       //p2
                },


                { //sala 04
                        { 267 , 327 , 543 ,  507 } ,    //z0
                        { 396 , 497 , 414 , 520 } ,     //p1
                        { 526 , 408 , 568 , 426 }       //p2
                },

                { //sala 05
                        { 651 , 390 , 831 ,  444 } ,    //z0
                        { 717 , 231 , 771 , 390 } ,     //z1
                        { 771 , 231 , 960 , 282 } ,      //z3
                        { 960 , 246 , 975 , 267} ,     //p1
                        { 619 , 408 , 674 , 426 }    //p2
                },

                { //sala 06
                        { 1065 , 171 , 1460 ,  342 } ,    //z0
                        { 1056 , 246 , 1071 , 267 } ,     //p1
                        { 1456 , 249 , 1477 , 273 } ,     //p2
                        { 1251 , 299 , 1275 , 374 }       //p3
                },

                { //sala 07
                        { 1560 , 231 , 1617 ,  285 } ,    //z0
                        { 1519 , 249 , 1577 , 267 }      //p1
                },

                { //sala 08
                        { 1236 , 447 , 1290 ,  852 } ,    //z0
                        { 1134 , 624 , 1368 ,  645 } ,    //z1
                        { 1251 , 420 , 1272 , 447 } ,     //p1
                        { 1116 , 627 , 1134 , 639 } ,     //p2
                        { 1251 , 852 , 1272 , 870 }       //p3
                },

                { //sala 09
                        { 990 , 618 , 1038 ,  792 } ,    //z0
                        { 1032 , 627 , 1050 , 639 }     //p1
                },

                { //sala 10
                        { 981 , 993 , 1542 ,  1236 } ,    //z0
                        { 1179 , 960 , 1338 ,  1266 } ,    //z1
                        { 1542 , 1080 , 1575 ,  1146 } ,    //z2
                        { 1251 , 936 , 1269 , 964 } ,     //p1
                        { 1575 , 1104 , 1593 , 1122 } ,     //p2
                        { 1251 , 1263 , 1272 , 1287 }       //p3
                },

                { //sala 11
                        { 1677 , 1083 , 2028 ,  1143 } ,    //z0
                        { 1770 , 1140 , 1869 ,  1176 } ,    //z1
                        { 1806 , 1161 , 1836 ,  1545 } ,    //z2
                        { 1827 , 1482 , 1869 , 1545 } ,      //z3
                        { 1659 , 1110 , 1680 , 1119 } ,     //p1
                        { 2025 , 1110 , 2040 , 1116 } ,     //p2
                        { 1863 , 1509 , 1887 , 1518 }       //p3
                },

                { //sala 12
                        { 2127 , 972 , 2427 ,  1272 } ,    //z0
                        { 2199 , 1272 , 2229 ,  1305 } ,    //z1
                        { 2325 , 1272 , 2358 ,  1305 } ,    //z2
                        { 2115 , 1110 , 2124 , 1119 }      //p1
                },

                { //sala 13
                        { 1965 , 1482 , 2397 ,  1545 } ,    //z0
                        { 1998 , 1449 , 2028 ,  1576 } ,    //z1
                        { 2109 , 1449 , 2142 ,  1576 } ,    //z2
                        { 2223 , 1449 , 2253 ,  1576 } ,    //z3
                        { 2334 , 1449 , 2364 ,  1576 } ,    //z4
                        { 1959 , 1497 , 1965 , 1518 }      //p1
                },

                { //sala 14
                        { 1230 , 1371 , 1293 ,  1722 } ,    //z0
                        { 1254 , 1356 , 1266 , 1368 }  ,    //p1
                        { 1254 , 1716 , 1266 , 1731 }      //p2
                },

                { //sala 15
                        { 1230 , 1818 , 1293 ,  2232 } ,    //z0
                        { 1053 , 2169 , 1467 , 2232 } ,    //p1
                        { 1056 , 1851 , 1467 , 1911 } ,    //z2
                        { 1053 , 1911 , 1149 ,  1944 } ,    //z3
                        { 1374 , 1911 , 1467 ,  1944 } ,    //z4
                        { 1053 , 2028 , 1467 , 2088 } ,    //z5
                        { 1254 , 1803 , 1266 , 1815 }     //p1
                }

        };

        //Quantidade de zonas de cada sala
        jogo->salas[ 0 ].qtdZonas =  12;
        jogo->salas[ 1 ].qtdZonas =  2;
        jogo->salas[ 2 ].qtdZonas =  3;
        jogo->salas[ 3 ].qtdZonas =  3;
        jogo->salas[ 4 ].qtdZonas =  3;
        jogo->salas[ 5 ].qtdZonas =  5;
        jogo->salas[ 6 ].qtdZonas =  4;
        jogo->salas[ 7 ].qtdZonas =  2;
        jogo->salas[ 8 ].qtdZonas =  5;
        jogo->salas[ 9 ].qtdZonas =  2;
        jogo->salas[ 10 ].qtdZonas =  6;
        jogo->salas[ 11 ].qtdZonas =  7;
        jogo->salas[ 12 ].qtdZonas =  4;
        jogo->salas[ 13 ].qtdZonas =  6;
        jogo->salas[ 14 ].qtdZonas =  3;
        jogo->salas[ 15 ].qtdZonas =  7;


        //Atribuindo Limites
        for( i = 0 ; i < QTDSALAS ; i++)
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
                        { 753 , 1425 }      //p1
                },

                { //sala 02
                        { 405 , 1123 },   //p1
                        { 405 , 841 }      //p2
                },

                { //sala 03
                        { 405 , 747 },    //p1
                        { 405 , 603 }      //p2
                },

                { //sala 04
                        { 405 , 522 },    //p1
                        { 557 , 417 }      //p2
                },

                { //sala 05
                        { 633 , 417 },      //p1
                        { 981 , 258 }    //p2
                },

                { //sala 06
                        { 1055 , 258 },    //p1
                        { 1476 , 258 },    //p2
                        { 1263 , 357 }      //p3
                },

                { //sala 07
                        { 1551 , 258 }    //p1
                },

                { //sala 08
                        { 1263 , 429 },    //p1
                        { 1190 , 633 },    //p2
                        { 1263 , 870 }    //p3
                },

                { //sala 09
                        { 1128 , 633 }    //p1
                },

                { //sala 10
                        { 1260 , 939 },    //p1
                        { 1596 , 1113 },    //p2
                        { 1260 , 1284 }    //p3
                },

                { //sala 11
                        { 1665 , 1113 },    //p1
                        { 2043 , 1113 },    //p2
                        { 1881 , 1512 }    //p3
                },

                { //sala 12
                        { 2112 , 1113 },    //p1
                },

                { //sala 13
                        { 1953 , 1512 },    //p1
                },

                { //sala 14
                        { 1260 , 1356 },    //p1
                        { 1260 , 1734 }     //p2
                },

                { //sala 15
                        { 1260 , 1803 },    //p1
                }

        };
//        float rotac[ QTDSALAS ][ 10 ] = {           //A rotacao das portas ( x-0 , y - 1 ) de cada porta de cada sala
//                {  0 /*p1*/ , -90/*p2*/ } ,     //sala00
//                {  90 /*p1*/ } ,     //sala01
//                {  180 /*p1*/ , 0/*p2*/ } ,     //sala03
//                {  180 /*p1*/ , -90/*p2*/ } ,     //sala04
//                {  90 /*p1*/ , -90/*p2*/ } ,     //sala05
//                {  90 /*p1*/ , -90/*p2*/ , 180/*p3*/ } ,     //sala06
//                {  90 /*p1*/ } ,     //sala07
//                {  0 /*p1*/ , 90/*p2*/ , 180/*p3*/ } ,     //sala08
//                {  -90 /*p1*/ } ,     //sala09
//                {  0 /*p1*/ , -90/*p2*/ , 180/*p3*/ } ,     //sala10
//                {  90 /*p1*/ , -90/*p2*/ , -90/*p3*/ } ,     //sala11
//                {  -90 /*p1*/ } ,     //sala12
//                {  -90 /*p1*/ } ,     //sala13
//                {  0 /*p1*/ , 180/*p2*/ } ,     //sala14
//                {  0 /*p1*/ } ,     //sala15
//
//        };

        int entrada[ QTDSALAS ][ 10 ][ 2 ] = {           //As coordenadas de entrada das portas ( x-0 , y - 1 ) de cada porta de cada sala
                { //sala 00
                        { 669 , 1425 },    //p1
                        { 405 , 1215 }      //p2
                },

                { //sala 01
                        { 753 , 1425 }      //p1
                },

                { //sala 02
                        { 405 , 1123 },   //p1
                        { 405 , 828 }      //p2
                },

                { //sala 03
                        { 405 , 747 },    //p1
                        { 405 , 600 }      //p2
                },

                { //sala 04
                        { 405 , 522 },    //p1
                        { 556 , 417 }      //p2
                },

                { //sala 05
                        { 639 , 417 },      //p1
                        { 975 , 258 }    //p2
                },

                { //sala 06
                        { 1055 , 258 },    //p1
                        { 1476 , 258 },    //p2
                        { 1263 , 357 }      //p3
                },

                { //sala 07
                        { 1545 , 258 }    //p1
                },

                { //sala 08
                        { 1263 , 429 },    //p1
                        { 1128 , 633 },    //p2
                        { 1263 , 870 }    //p3
                },

                { //sala 09
                        { 1050 , 633 }    //p1
                },

                { //sala 10
                        { 1260 , 939 },    //p1
                        { 1596 , 1113 },    //p2
                        { 1260 , 1284 }    //p3
                },

                { //sala 11
                        { 1665 , 1113 },    //p1
                        { 2043 , 1113 },    //p2
                        { 1881 , 1512 }    //p3
                },

                { //sala 12
                        { 2112 , 1113 }    //p1
                },

                { //sala 13
                        { 1957 , 1512 }    //p1
                },

                { //sala 14
                        { 1260 , 1356 },    //p1
                        { 1260 , 1734 }     //p2
                },

                { //sala 15
                        { 1260 , 1803 }    //p1
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
                        { 405 , 738 }     //p2
                },

                { //sala 03
                        { 405 , 837 } ,    //p1
                        { 405 , 510 }     //p2
                },

                { //sala 04
                        { 405 , 612 },    //p1
                        { 651 , 417 }      //p2
                },

                { //sala 05
                        { 546 , 417 },      //p1
                        { 1065 , 258 }    //p2
                },

                { //sala 06
                        { 963 , 258 },    //p1
                        { 1563 , 258 },    //p2
                        { 1263 , 444 }      //p3
                },

                { //sala 07
                        { 1461 , 258 }    //p1
                },

                { //sala 08
                        { 1263 , 342 },    //p1
                        { 1035 , 633 },    //p2
                        { 1263 , 957 }    //p3
                },

                { //sala 09
                        { 1137 , 633 }    //p1
                },

                { //sala 10
                        { 1260 , 855 },    //p1
                        { 1680 , 1113 },    //p2
                        { 1260 , 1371 }    //p3
                },

                { //sala 11
                        { 1578 , 1113 },    //p1
                        { 2130 , 1113 },    //p2
                        { 1968 , 1512 }    //p3
                },

                { //sala 12
                        { 2028 , 1113 }    //p1
                },

                { //sala 13
                        { 1866 , 1512 }    //p1
                },

                { //sala 14
                        { 1260 , 1271 },    //p1
                        { 1260 , 1818 }     //p2
                },

                { //sala 15
                        { 1260 , 1716 }    //p1
                }

        };

        int status[ QTDSALAS ][ 10 ] = {           //O status de trancada/destrancada das portas ( destrancada=1 , trancada = 0 ) de cada porta de cada sala
                {  1 /*p1*/ , 1/*p2*/ },      //sala00
                {  1 /*p1*/ },      //sala01
                {  1 /*p1*/ , 1/*p2*/ },      //sala02
                {  1 /*p1*/ , 1/*p2*/ },      //sala03
                {  1 /*p1*/ , 1/*p2*/ },      //sala04
                {  1 /*p1*/ , 1/*p2*/ },      //sala05
                {  1 /*p1*/ , 1/*p2*/ , 1/*p3*/ },      //sala06
                {  1 /*p1*/ },      //sala07
                {  1 /*p1*/ , 1/*p2*/ , 1/*p3*/ },      //sala08
                {  1 /*p1*/ },      //sala09
                {  1 /*p1*/ , 1/*p2*/ , 1/*p3*/ },      //sala10
                {  1 /*p1*/ , 1/*p2*/ , 1/*p3*/ },      //sala11
                {  1 /*p1*/ },      //sala12
                {  1 /*p1*/ },      //sala13
                {  1 /*p1*/ , 1/*p2*/ },      //sala14
                {  1 /*p1*/ }      //sala15
        };


        int alterarPSala[ QTDSALAS ][ 10 ] = {           //A sala para qual as portas levam
                {  1 /*p1*/ , 2/*p2*/ },      //sala00
                {  0 /*p1*/ },      //sala01
                {  0 /*p1*/ , 3/*p2*/ },      //sala02
                {  2 /*p1*/ , 4/*p2*/ },      //sala03
                {  3 /*p1*/ , 5/*p2*/ },      //sala04
                {  4 /*p1*/ , 6/*p2*/ },      //sala05
                {  5 /*p1*/ , 7/*p2*/ , 8/*p3*/ },      //sala06
                {  6 /*p1*/ },      //sala07
                {  6 /*p1*/ , 9/*p2*/ , 10/*p3*/ },      //sala08
                {  8 /*p1*/ },      //sala09
                {  8 /*p1*/ , 11/*p2*/ , 14/*p3*/ },      //sala10
                {  10 /*p1*/ , 12/*p2*/ , 13/*p3*/ },      //sala11
                {  11 /*p1*/ },      //sala12
                {  11 /*p1*/ },      //sala13
                {  10 /*p1*/ , 15/*p2*/ },      //sala14
                {  14 /*p1*/ }      //sala15

        };

        //Quantidade de portas de cada sala
        jogo->salas[ 0 ].qtdPortas =  2;
        jogo->salas[ 1 ].qtdPortas =  1;
        jogo->salas[ 2 ].qtdPortas =  2;
        jogo->salas[ 3 ].qtdPortas =  2;
        jogo->salas[ 4 ].qtdPortas =  2;
        jogo->salas[ 5 ].qtdPortas =  2;
        jogo->salas[ 6 ].qtdPortas =  3;
        jogo->salas[ 7 ].qtdPortas =  1;
        jogo->salas[ 8 ].qtdPortas =  3;
        jogo->salas[ 9 ].qtdPortas =  1;
        jogo->salas[ 10 ].qtdPortas =  3;
        jogo->salas[ 11 ].qtdPortas =  3;
        jogo->salas[ 12 ].qtdPortas =  1;
        jogo->salas[ 13 ].qtdPortas =  1;
        jogo->salas[ 14 ].qtdPortas =  2;
        jogo->salas[ 15 ].qtdPortas =  1;


        //Atribuindo Valores
        for( i = 0 ; i < QTDSALAS ; i++)
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


#include <string.h>
///
void CarregarPersonagemImagens( Jogo *jogo )
{
        int arma , status , frame;
        char nmr[10];
        const char comum[] = "Sprites/Personagem/";
        char pasta[][100] = {
                "pistola/",
                "smg/",
                " ",
                " ",
                " "
        };

        const char subpasta[][100] = {
                "repouso/",
                "movimento/",
                "atirando/",
                "coronhada/",
                "recarregando/"
        };
        char fim[] = ".png";
        char arquivo[100];

        for( arma = 0 ; arma < QTD_ARMAS ; arma++ )
                for( status = 0 ;status < jogo->spriteDef.QTD_STATUS[ arma ] ; status++ )
                        for( frame = 0 ; frame < jogo->spriteDef.QTD_FRAMES[ arma ][ status ] ; frame++ )
                        {
                                TextCopy( arquivo , comum );
                                strcat( arquivo , pasta[arma] );
                                strcat( arquivo , subpasta[status] );

                                IntParaString( frame , nmr );
                                strcat( arquivo , nmr );

                                strcat( arquivo , fim );

                                jogo->Res.Per[arma][status][frame] = LoadTexture( arquivo );
                        }

        //Jogador extracao de textura
        jogo->spriteDef.Src.height = jogo->Res.Per[0][0][0].height;
        jogo->spriteDef.Src.width = jogo->Res.Per[0][0][0].width;
        jogo->spriteDef.Src.x = 0;
        jogo->spriteDef.Src.y = 0;
}

///
void CarregarPes( Jogo *jogo )
{
        int status , frame;
        char nmr[10];
        const char comum[] = "Sprites/Personagem/Pes/";
        char pasta[][100] = {
                "repouso/",
                "andando/",
                "correndo/",
                "lateralEsquerda/",
                "lateralDireita/"
        };

        char fim[] = ".png";
        char arquivo[100];

                for( status = 0 ; status < QTD_STATUS_PES ; status++ )
                        for( frame = 0 ; frame < jogo->spriteDef.QTD_FRAMES_PES[ status ] ; frame++ )
                        {
                                TextCopy( arquivo , comum );
                                strcat( arquivo , pasta[status] );

                                IntParaString( frame , nmr );
                                strcat( arquivo , nmr );

                                strcat( arquivo , fim );

                                jogo->Res.Pes[status][frame] = LoadTexture( arquivo );
                        }

        //Jogador extracao de textura
        jogo->spriteDef.SrcPes.height = jogo->Res.Pes[0][0].height;
        jogo->spriteDef.SrcPes.width = jogo->Res.Pes[0][0].width;
        jogo->spriteDef.SrcPes.x = 0;
        jogo->spriteDef.SrcPes.y = 0;
}


void IntParaString( int nmr , char *str )
{
        int tam = 0;
        int cop = nmr;

        do{
                str[ tam ] = cop % 10 + 48;     //Para transformar digito decimal inteiro em digito em ASCII
                str[ tam + 1] = '\0';
                cop /= 10;
                tam++;
        }while( cop );

        InverteStr( str );
}

void InverteStr( char *str )
{
        int i , j;
        int temp;
        int tam = strlen( str );

        for( i = 0 , j = tam - 1 ; i <= j ; i++ , j-- )
        {
                temp = str[ i ];
                str[ i ] =  str[ j ];
                str[ j] =  temp;
        }


}
