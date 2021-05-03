

#include "inicializar.h"
#include "definicoes.h"


/** \brief Inicializa a janela no sistema operacional
 *
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


/** \brief  preJogo(): Incializa elementos intrinsecos do jogo, alem de carregar todas as texturas e fontes.
 *
 * \return JOGO
 *
 */
 JOGO definirPreJogo( void ){
         JOGO pre_jogo;

        definirTela( &pre_jogo );

        definirMapa( &pre_jogo );               // Define o Mapa do jogo

        definirEscalaGeral( &pre_jogo );                // Define a Escala Geral

        definirDadosSpritesPersonagem( &pre_jogo );               // Define propriedades das sprites

        carregarTexturasFontes( &pre_jogo );           //Carregar Texturas e Fontes

        definirTiposInimigo( &pre_jogo );               // Define propriedades de cada tipo de inimigo


        CriaSalas( &pre_jogo );             //Criar Salas: zonas , obstaculos fixos , spawns,  portas , baus e pontos de regeneracao





        /// Retorno
        return pre_jogo;
 }



/** \brief Crias as salas do jogo , definindo posição de portas e de baús , limites de vizualização ,  etc
 *
 * \param *JOGO
 *
 */

void CriaSalas( JOGO *jogo)
{
        CriaZonas( jogo );
        CriaPortas( jogo );
        CriaSpawns( jogo );             // Cria Spawns
        CarregarBaus( jogo );
        CriaBaus( jogo );               //Cria BAUS
}



/** \brief Inicializa a variavel JOGO para um novo jogo
 *
 * \param *JOGO
 *
 */

void IniciaNovoJogo( JOGO *jogo )
{
        jogo->FECHAR = 0;

        inicializarJogador( jogo );      // Inicializa os dados do jogador para Novo Jogo





}
//##############################################################################



/** \brief Incializa dados do  JOGADOR para Novo Jogo
 *
 * \param *JOGO
 *
 */

 void inicializarJogador( JOGO *jogo){
        ///GERAL
        jogo->jogador.saude = SAUDE_TOTAL_JOGADOR;
        jogo->jogador.vidas = VIDAS_INICIAIS_JOGADOR;
        jogo->jogador.pontos = 0;

        ///Posicao no MUNDO
        jogo->jogador.PosMundo.x = 102;
        jogo->jogador.PosMundo.y = 633;

        ///Posicao TELA
                ///Jogador
                jogo->jogador.PosTela.width =  LARG_PADRAO * jogo->tela.width / REF_TELA_LARG;
                jogo->jogador.PosTela.height =  jogo->jogador.PosTela.width * ALT_PADRAO / LARG_PADRAO;   //Altura Dependente da largura
//                jogo->jogador.PosTela.x =  jogo->escalaGeral.x * ( jogo->jogador.PosMundo.x - jogo->MapaDesenho.x );
//                jogo->jogador.PosTela.y =  jogo->escalaGeral.y * ( jogo->jogador.PosMundo.y - jogo->MapaDesenho.y );
                jogo->jogador.PosTela.x =  jogo->tela.width / 2;
                jogo->jogador.PosTela.y =  jogo->tela.height / 2;

                ///Pes
                jogo->jogador.PosTelaPes.width =  ESC_PES * jogo->jogador.PosTela.width;
                jogo->jogador.PosTelaPes.height =  ESC_PES* jogo->jogador.PosTela.height;
                jogo->jogador.PosTelaPes.x =  jogo->jogador.PosTela.x;
                jogo->jogador.PosTelaPes.y =  jogo->jogador.PosTela.y;

        ///Armas iniciais e Status iniciais
        jogo->jogador.atualArma = 0;
        jogo->jogador.atualStatus = 0;
        jogo->spriteDef.atualFrame = 0;
        jogo->jogador.latencia = 0;

        ///Sala inicial
        jogo->atualSala = 0;

        ///Passagem de portas
        jogo->PASSAGEM = 0;
 }




/** \brief Define caracteristicas da  TELA
 *
 * \param *JOGO
 *
 */

 void definirTela( JOGO *jogo ){

        ///Tela
        jogo->tela.x = 0;
        jogo->tela.y = 0;

        if( GetScreenWidth() / (float)GetScreenHeight() == REF_TELA_LARG / (float)REF_TELA_ALT ){
                        jogo->tela.width = REF_TELA_LARG;        // A tela deve ficar cheia em largura
                        jogo->tela.height = REF_TELA_ALT;        // A altura deve ser regulada para manter a proporcao
                        jogo->regulagemTela = 0;
        }else{
                if( GetScreenWidth() / (float)GetScreenHeight() > REF_TELA_LARG / (float)REF_TELA_ALT ){         //A largura e proporionalmente maior
                        jogo->tela.width = GetScreenWidth();        // A tela deve ficar cheia em largura
                        jogo->tela.height = REF_TELA_ALT * jogo->tela.width / REF_TELA_LARG ;        // A altura deve ser regulada para manter a proporcao
                        jogo->regulagemTela = 1;
                }else{          // Nesse caso a altura e proporcionalmente maior
                        jogo->tela.height = GetScreenHeight();        // A tela deve ficar cheia em altura
                        jogo->tela.width =  REF_TELA_LARG * jogo->tela.height / REF_TELA_ALT ;        // A largura deve ser regulada para manter a proporcao
                        jogo->regulagemTela = 2;
                }
        }


 }




/** \brief Define caracteristicas da  TELA
 *
 * \param *JOGO
 *
 */

 void definirMapa( JOGO *jogo ){
        ///Tamanho Da Textura MAPA
        jogo->MapaTamanho.x = jogo->Res.Mapa.width;
        jogo->MapaTamanho.y = jogo->Res.Mapa.height;

        ///Area de Extracao ( FIXA )
        jogo->MapaDesenho.x = 0;
        jogo->MapaDesenho.y = 300;
        jogo->MapaDesenho.width = PIXEL_LARGURA_MAPA;
        jogo->MapaDesenho.height = PIXEL_ALTURA_MAPA;
 }



/** \brief Define ESCALA GERAL do mapa em relacao a tela TIPO DE INIMIGO
 *
 * \param *JOGO
 *
 */
 void definirEscalaGeral( JOGO *jogo ){
        jogo->escalaGeral.x = (  jogo->tela.width / PIXEL_LARGURA_MAPA  );
        jogo->escalaGeral.y = (  jogo->tela.height / PIXEL_ALTURA_MAPA  );
 }



/** \brief Define caracteristicas de cada TIPO DE INIMIGO
 *
 * \param *JOGO
 *
 */

 void definirTiposInimigo( JOGO *jogo ){
        /// Distancia minima para o jogador
        jogo->infoIniT.dist_manter[ 0 ] = 10;
        jogo->infoIniT.dist_manter[ 1 ] = 30;
        jogo->infoIniT.dist_manter[ 2 ] = 100;

        /// Velocidade
        jogo->infoIniT.vel[ 0 ] = PASSO_T0;
        jogo->infoIniT.vel[ 1 ] = PASSO_T1;
        jogo->infoIniT.vel[ 2 ] = PASSO_T1;

        /// Pontos de Saude
        jogo->infoIniT.saude[ 0 ] = 1;
        jogo->infoIniT.saude[ 1 ] = 4;
        jogo->infoIniT.saude[ 2 ] = 2;
        inicializarInimigosSalas( jogo);

        spriteT1( jogo);
        spriteT0( jogo);

 }



/** \brief Define caracteristicas das sprites
 *
 * \param *JOGO
 *
 */

 void definirDadosSpritesPersonagem( JOGO *jogo ){
        ///QTD de status para cada arma
        jogo->spriteDef.QTD_STATUS[ 0 ] = 5;      //pistola
        jogo->spriteDef.QTD_STATUS[ 0 ] = 5;      //SMG

        ///Qtd de Frames para cada status de cada arma
                ///Pistola
                jogo->spriteDef.QTD_FRAMES[ 0 ][ 0 ] = 20;
                jogo->spriteDef.QTD_FRAMES[ 0 ][ 1 ] = 20;
                jogo->spriteDef.QTD_FRAMES[ 0 ][ 2 ] = 3;
                jogo->spriteDef.QTD_FRAMES[ 0 ][ 3 ] = 15;
                jogo->spriteDef.QTD_FRAMES[ 0 ][ 4 ] = 15;

        ///QTD de Frame para cada tipo de movimento
        jogo->spriteDef.QTD_FRAMES_PES[ 0 ] = 1;        //Repouso
        jogo->spriteDef.QTD_FRAMES_PES[ 1 ] = 20;       //Andando
        jogo->spriteDef.QTD_FRAMES_PES[ 2 ] = 20;       //Correndo
        jogo->spriteDef.QTD_FRAMES_PES[ 3 ] = 20;       //Movimento lateral para a esquerda
        jogo->spriteDef.QTD_FRAMES_PES[ 4 ] = 20;       //Movimento lateral para a direita

        /// Retangulo de extracao da textura
        jogo->spriteDef.Src.width = 258;
        jogo->spriteDef.Src.height = 220;
        jogo->spriteDef.Src.x = 0;
        jogo->spriteDef.Src.y = 0;
}


/** \brief Carrega as Texturas e Fontes
 *
 * \param *JOGO
 *
 */

void carregarTexturasFontes( JOGO *jogo )
{
        ///Texturas  Gerais
        jogo->Res.Logo =  LoadTexture("Logo/Logo.png");   // Imagem de fundo (Logo)
        jogo->Res.MenuFundo =  LoadTexture("Menu_Imagens/MenuPrincipal.png");   // Imagem do plano de fundo
        jogo->Res.TelaDeFundo =  LoadTexture("Menu_Imagens/FundoLimpo.png");
        jogo->Res.FundoConfirmarSair =    LoadTexture("Menu_Imagens/FundoConfirmarSair.png");
        jogo->Res.Mapa =    LoadTexture("Mapa/Mapa.png");
        jogo->Res.Portas =    LoadTexture("Mapa/Portas.png");
        jogo->Res.Bala = LoadTexture("Sprites/Bala.png");

        ///Fontes
        jogo->Res.fonteWolfen =    LoadFontEx("Fontes/ReturnToCastle-MZnx.ttf"  ,96 , 0 , 0);
        jogo->Res.fonteWolfen2 =    LoadFontEx("Fontes/wolfenstein.ttf"  ,96 , 0 , 0);

        ///Sprites
        carregarSpritesPersonagem( jogo);      //Jogador
        carregarSpritesPes( jogo );           //Pes do jogador
}
//##############################################################################



/**     Funcao CarregarLevel(): Carrega os levels
    */

void CarregarLevel( JOGO *jogo)
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




/**     Função CriaZonas() : Crias as zonas da sala , definindo limites de deslocamento
   */

void CriaZonas( JOGO *jogo)
{
        int i , j;

        /// Retangulos dos limites de deslocamento de cada zona de cada sala( 0-x , 1-y , 2-width , 3-height )
        int limites[ QTDSALAS ][ QTD_ZONAS_MAX][ 4 ] = {
                { //sala 00
                        { 62 , 586 , 79 ,  878 } ,    //z0
                        { 206 , 633 , 95 , 111 } ,     //z1
                        { 62 , 665 , 239 , 47 } ,      //z2
                        { 62 , 937 , 110 , 79 } ,     //z3
                        { 206 , 1210 , 96 , 110 } ,    //z4
                        { 62 , 1241 , 240 , 47 } ,   //z5
                        { 62 , 1386 , 607 , 78 } ,   //z6
                        { 367 , 1209 , 79 , 254 }     //z7
                },

                { //sala 01
                        { 750 , 1386 , 143 , 78 }    //z0
                },

                { //sala 02
                        { 255 , 826 , 303 , 303 }     //z0
                },

                { //sala 03
                        { 366 , 601 , 80 ,  144 }     //z0
                },


                { //sala 04
                        { 255 , 314 , 303 ,  207 }     //z0
                },

                { //sala 05
                        { 638 , 378 , 206 ,  79 } ,    //z0
                        { 702 , 218 , 78 , 239 } ,     //z1
                        { 702 , 218 , 272 , 78 }       //z3
                },

                { //sala 06
                        { 1055 , 162 , 413 ,  191 }     //z0
                },

                { //sala 07
                        { 1550 , 217 , 79 ,  80 } ,    //z0
                },

                { //sala 08
                        { 1222 , 434 , 80 ,  431 } ,    //z0
                        { 1126 , 610 , 271 ,  46 }    //z1
                },

                { //sala 09
                        { 982 , 610 , 64 ,  191 }    //z0
                },

                { //sala 10
                        { 965 , 978 , 592 ,  271 } ,    //z0
                        { 1172 , 945 , 177 ,  336 } ,    //z1
                        { 1311 , 1073 , 278 ,  80 }     //z2
                },

                { //sala 11
                        { 1669 , 1073 , 368 ,  80 } ,    //z0
                        { 1765 , 1120 , 112 ,  65 } ,    //z1
                        { 1797 , 1073 , 48 ,  480 } ,    //z2
                        { 1797 , 1473 , 80 , 80 }       //z3
                },

                { //sala 12
                        { 2117 , 961 , 321 ,  320 } ,    //z0
                        { 2189 , 1217 , 48 ,  96 } ,    //z1
                        { 2317 , 1222 , 47 ,  91 }     //z2
                },

                { //sala 13
                        { 1957 , 1473 , 448 ,  80 } ,    //z0
                        { 1989 , 1441 , 48 ,  144 } ,    //z1
                        { 2101 , 1441 , 48 ,  144 } ,    //z2
                        { 2213 , 1441 , 48 ,  144 } ,    //z3
                        { 2325 , 1441 , 48 ,  144 }    //z4
                },

                { //sala 14
                        { 1221 , 1361 , 80 ,  368 }     //z0
                },

                { //sala 15
                        { 1221 , 1809 , 80 ,  432 } ,    //z0
                        { 1045 , 1841 , 432 , 79 } ,    //z1
                        { 1045 , 1892 , 112 ,  61 } ,    //z2
                        { 1365 , 1881 , 112 ,  72 } ,    //z3
                        { 1045 , 2017 , 432 ,  80 } ,    //z4
                        { 1045 , 2161 , 432 , 80 }    //z5
                }

        };

        //Quantidade de zonas de cada sala
        jogo->salas[ 0 ].qtdZonas =  8;
        jogo->salas[ 1 ].qtdZonas =  1;
        jogo->salas[ 2 ].qtdZonas =  1;
        jogo->salas[ 3 ].qtdZonas =  1;
        jogo->salas[ 4 ].qtdZonas =  1;
        jogo->salas[ 5 ].qtdZonas =  3;
        jogo->salas[ 6 ].qtdZonas =  1;
        jogo->salas[ 7 ].qtdZonas =  1;
        jogo->salas[ 8 ].qtdZonas =  2;
        jogo->salas[ 9 ].qtdZonas =  1;
        jogo->salas[ 10 ].qtdZonas =  3;
        jogo->salas[ 11 ].qtdZonas =  4;
        jogo->salas[ 12 ].qtdZonas =  3;
        jogo->salas[ 13 ].qtdZonas =  5;
        jogo->salas[ 14 ].qtdZonas =  1;
        jogo->salas[ 15 ].qtdZonas =  6;


        //Atribuindo Limites
        for( i = 0 ; i < QTDSALAS ; i++)
                for( j = 0 ; j < jogo->salas[ i ].qtdZonas; j++){
                        jogo->salas[ i ].zonas[ j ].x = limites[ i ][ j ][ 0 ] + jogo->jogador.PosTela.width / ( 2.0 * RAZAO_SOLID_JOGADOR );
                        jogo->salas[ i ].zonas[ j ].y = limites[ i ][ j ][ 1 ] + jogo->jogador.PosTela.height / ( 2.0 * RAZAO_SOLID_JOGADOR );
                        jogo->salas[ i ].zonas[ j ].width = limites[ i ][ j ][ 2 ] - jogo->jogador.PosTela.width / RAZAO_SOLID_JOGADOR;
                        jogo->salas[ i ].zonas[ j ].height = limites[ i ][ j ][ 3 ] - jogo->jogador.PosTela.height / RAZAO_SOLID_JOGADOR;
                }
}



/**     Função CriaPortas() : Crias as portas da sala , definindo posicao de entrada e posicao de destino
   *                    obs: Portas se comportam como teleportes - alteram posicao do jogado
   */

void CriaPortas( JOGO *jogo)
{
        int i , j;
        int pos[ QTDSALAS ][ 10 ][ 2 ] = {           //As posicoes  das portas ( x-0 , y - 1 ) de cada porta de cada sala
                { //sala 00
                        { 670 , 1425 },    //p1
                        { 406 , 1208 }      //p2
                },

                { //sala 01
                        { 749 , 1424 }      //p1
                },

                { //sala 02
                        { 405 , 1129 },   //p1
                        { 406 , 825 }      //p2
                },

                { //sala 03
                        { 405 , 745 },    //p1
                        { 406 , 600 }      //p2
                },

                { //sala 04
                        { 405 , 521 },    //p1
                        { 558 , 417 }      //p2
                },

                { //sala 05
                        { 637 , 416 },      //p1
                        { 974 , 257 }    //p2
                },

                { //sala 06
                        { 1053 , 256 },    //p1
                        { 1470 , 257 },    //p2
                        { 1261 , 353 }      //p3
                },

                { //sala 07
                        { 1549 , 256 }    //p1
                },

                { //sala 08
                        { 1262 , 432 },    //p1
                        { 1125 , 633 },    //p2         //PORTA ESPECIAL PENSAR EM ALGO DEPOIS
                        { 1261 , 865 }    //p3
                },

                { //sala 09
                        { 1046 , 632 }    //p1          //Porta Especial
                },

                { //sala 10
                        { 1259 , 944 },    //p1
                        { 1589 , 1113 },    //p2
                        { 1260 , 1281 }    //p3
                },

                { //sala 11
                        { 1668 , 1112 },    //p1
                        { 2037 , 1113 },    //p2
                        { 1887 , 1513 }    //p3
                },

                { //sala 12
                        { 2116 , 1112 },    //p1
                },

                { //sala 13
                        { 1956 , 1513 },    //p1
                },

                { //sala 14
                        { 1261 , 1360 },    //p1
                        { 1260 , 1729 }     //p2
                },

                { //sala 15
                        { 1261 , 1808 },    //p1
                }

        };
        float rotac[ QTDSALAS ][ 10 ] = {           //A rotacao das portas
                {  -90 /*p1*/ , 0/*p2*/ } ,     //sala00
                {  90 /*p1*/ } ,     //sala01
                {  180 /*p1*/ , 0/*p2*/ } ,     //sala02
                {  180 /*p1*/ , 0/*p2*/ } ,     //sala03
                {  180 /*p1*/ , -90/*p2*/ } ,     //sala04
                {  90 /*p1*/ , -90/*p2*/ } ,     //sala05
                {  90 /*p1*/ , -90/*p2*/ , 180/*p3*/ } ,     //sala06
                {  90 /*p1*/ } ,     //sala07
                {  0 /*p1*/ , 90/*p2*/ , 180/*p3*/ } ,     //sala08
                {  -90 /*p1*/ } ,     //sala09
                {  0 /*p1*/ , -90/*p2*/ , 180/*p3*/ } ,     //sala10
                {  90 /*p1*/ , -90/*p2*/ , -90/*p3*/ } ,     //sala11
                {  90 /*p1*/ } ,     //sala12
                {  90 /*p1*/ } ,     //sala13
                {  0 /*p1*/ , 180/*p2*/ } ,     //sala14
                {  0 /*p1*/ } ,     //sala15

        };

        int status[ QTDSALAS ][ 10 ] = {           //O status de trancada/destrancada das portas ( destrancada=1 , trancada = 0 ) de cada porta de cada sala
                {  1 /*p1*/ , 1/*p2*/ },     //sala00
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
                {  1 /*p1*/ , 2/*p2*/ },     //sala00
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

                        jogo->salas[ i ].portas[ j ].rotac = rotac[ i ][ j ];

                        jogo->salas[ i ].portas[ j ].DESTRANCADA = status[ i ][ j ];
                        jogo->salas[ i ].portas[ j ].alteraPSala = alterarPSala[ i ][ j ];
                }
}


#include <string.h>
/** \brief Carrega as sprites do personagem
 *
 * \param *JOGO
 *
 */

void carregarSpritesPersonagem( JOGO *jogo )
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
}

///
void carregarSpritesPes( JOGO *jogo ){
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


///
void CriaSpawns(JOGO *jogo)
{
        jogo->salas[ 0 ].qtdSpawns = 5;
        jogo->salas[ 1 ].qtdSpawns = 0;
        jogo->salas[ 2 ].qtdSpawns = 2;
        jogo->salas[ 3 ].qtdSpawns = 0;
        jogo->salas[ 4 ].qtdSpawns = 2;
        jogo->salas[ 5 ].qtdSpawns = 2;
        jogo->salas[ 6 ].qtdSpawns = 3;
        jogo->salas[ 7 ].qtdSpawns = 0;
        jogo->salas[ 8 ].qtdSpawns = 3;
        jogo->salas[ 9 ].qtdSpawns = 0;
        jogo->salas[ 10 ].qtdSpawns = 7;
        jogo->salas[ 11 ].qtdSpawns = 0;
        jogo->salas[ 12 ].qtdSpawns = 4;
        jogo->salas[ 13 ].qtdSpawns = 2;
        jogo->salas[ 14 ].qtdSpawns = 0;
        jogo->salas[ 15 ].qtdSpawns = 0;

    int locais[ QTDSALAS ][ MAX_SPAWN_SALAS ][ 2] =
        {
                {// sala 0
                        {148 , 978 },
                        {230 , 1240},
                        {270 , 1300},
                        {400 , 1322},
                        {540 , 1425}
                },

                {// sala 1
                        {/*Nenhum*/}
                },

                {// sala 2
                        {320, 880},
                        {500, 880}
                },

                {// sala 3
                        {/*Nenhum*/}
                },

                {// sala 4
                        {300, 350},
                        {520, 350}
                },

                {// sala 5
                        {800, 418},
                        {850, 260}
                },

                {// sala 6
                     {1260, 200},
                     {1380, 200},
                     {1380, 270}
                },

                {// sala 7
                        {/*Nenhum*/}
                },

                {// sala 8
                        {1260, 592},
                        {1260, 730},
                        {1380, 270}
                },

                {// sala 9
                        {/*Nenhum*/}
                },

                {// sala 10
                        {1010, 1010},
                        {1010, 1110},
                        {1010, 1210},
                        {1260, 1060},
                        {1480, 1010},
                        {1480, 1110},
                        {1480, 1210}
                },

                {// sala 11
                        {/*Nenhum*/}
                },

                {// sala 12
                        {2238, 1018},
                        {2368, 1018},
                        {2238, 1220},
                        {2368, 1220}
                },

                {// sala 13
                        {2150, 1515},
                        {2350, 1515}
                },

                {// sala 14
                        {/*Nenhum*/}
                },

                {// sala 15
                        {/*Nenhum*/}
                }

     };

        int tipo[QTDSALAS][ MAX_SPAWN_SALAS ] = {
                {  1 /*s1*/ , 0/*s2*/ , 0 /*s3*/ , 0/*s4*/ , 0/*s5*/  },     //sala00
                {  /*NENHUM*/ },      //sala01
                {  1 /*s1*/ , 0/*s2*/ },      //sala02
                {  /*NENHUM*/ },      //sala03
                {  1 /*s1*/ , 1/*s2*/ },      //sala04
                {  0 /*s1*/ , 0/*s2*/ },      //sala05
                {  0 /*s1*/ , 0/*s2*/ , 1/*p3*/ },      //sala06
                {  /*NENHUM*/ },      //sala07
                {  1 /*s1*/ , 2/*s2*/ , 0/*p3*/ },      //sala08
                {  /*NENHUM*/ },      //sala09
                {  0 /*s1*/ , 1/*s2*/ , 0 /*s3*/ , 1/*s4*/ , 0/*s5*/ , 2/*s6*/ , 2/*s7*/ },      //sala10
                { /*NENHUM*/  },      //sala11
                {  0 /*s1*/ , 0/*s2*/ , 0 /*s3*/ , 0/*s4*/ },      //sala12
                {  1 /*s1*/ , 2 /*s1*/ },      //sala13
                {  /*NENHUM*/  },      //sala14
                { /*NENHUM*/ }      //sala15


        };

     /// Atribuicao
     int i , j;
        for ( i = 0 ; i < QTDSALAS ; i++ )
                for ( j = 0 ; j < jogo->salas[ i ].qtdSpawns ; j++ ){
                        jogo->salas[ i ].spawns[ j ].posMundo.x = locais[ i ][ j ][ 0 ];
                        jogo->salas[ i ].spawns[ j ].posMundo.y = locais[ i ][ j ][ 1 ];

                        jogo->salas[ i ].spawns[ j ].posMundo.width = LARG_MUNDO_SPAWN;
                        jogo->salas[ i ].spawns[ j ].posMundo.height = ALT_MUNDO_SPAWN;

                        jogo->salas[ i ].spawns[ j ].tipo = tipo[ i ][ j ];


        }

}



/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void CriaBaus( JOGO *jogo ){
        Vector2 pos[ QTDSALAS ][ MAX_BAUS_SALA ] = {
               { //sala 00
                        { 156 , 962 },    //b1
                        { 282 , 1251 }    //b2
                },

                { //sala 01
                        { 806 , 1386 },      //b1
                        { 806 , 1447 },      //b2
                        { 876 , 1409 }      //b3
                },

                { //sala 02
                        { 261 , 1105 }   //b1
                },

                { //sala 03
                        //Nenhum
                },

                { //sala 04
                        { 262 , 496 },      //b1
                        { 533 , 324 }      //b2
                },

                { //sala 05
                        //Nenhum
                },

                { //sala 06
                        //Nenhum
                },

                { //sala 07
                        { 1574 , 220 },    //b1
                        { 1574 , 280 },    //b2
                        { 1612 , 242 }      //b3
                },

                { //sala 08
                        { 1284 , 754 },    //b1
                },

                { //sala 09
                        { 983 , 691 },    //b2
                        { 997 , 782 }    //b7
                },

                { //sala 10
                        { 967 , 1002 },    //b1
                        { 967 , 1194 },    //b2
                        { 1538 , 1194 }    //b3
                },

                { //sala 11
                        //Nenhum                },

                { //sala 12
                        { 2263 , 964 }    //b1
                },

                { //sala 13
                        { 1998 , 1444 },    //b1
                        { 2108 , 1444 },    //b2
                        { 2221 , 1444 },    //b3
                        { 2334 , 1444 },    //b4
                        { 1998 , 1566 },    //b5
                        { 2108 , 1566 },    //b6
                        { 2221 , 1566 },    //b7
                        { 2334 , 1566 }    //b8
                },

                { //sala 14
                        //Nenhum
                },

                { //sala 15
                        { 1045 , 2043 },    //b1
                        { 1045 , 2188 },    //b2
                        { 1461 , 2188 }    //b3
                }

        };

        /// Rotacao
        float rotac[ QTDSALAS ][ 10 ] = {           //A rotacao dos baus
                {  90 /*b1*/ , 90/*b2*/ } ,     //sala00
                {  0 /*b1*/ , 180/*b2*/ , 90/*b3*/ } ,     //sala01
                {  180 /*b1*/ } ,     //sala02
                { /*Nenhum*/ } ,     //sala03
                {  180 /*b1*/ , 90/*b2*/ } ,     //sala04
                { /*Nenhum*/ } ,     //sala05
                {  /*Nenhum*/ } ,     //sala06
                {  0 /*b1*/ , 180/*b2*/ , 90/*b3*/ } ,     //sala07
                {  90 /*b1*/ } ,     //sala08
                {  -90 /*b1*/  , 180/*b2*/ } ,     //sala09
                {  -90 /*b1*/ , -90/*b2*/ , 90/*b3*/ } ,     //sala10
                { /*Nenhum*/ } ,     //sala11
                {  0 /*b1*/ } ,     //sala12
                {  0 /*b1*/ , 0/*b2*/ , 0/*b3*/, 0/*b4*/ , 180/*b5*/, 180/*b6*/ , 180/*b7*/, 180/*b8*/ } ,     //sala13
                {  0 /*b1*/ } ,     //sala14
                {  -90 /*b1*/ , -90/*b2*/ , 90/*b3*/ }     //sala15
        };

        ///Numero de Baus por sala
        jogo->salas[ 0 ].qtdBaus =  2;
        jogo->salas[ 1 ].qtdBaus =  3;
        jogo->salas[ 2 ].qtdBaus =  1;
        jogo->salas[ 3 ].qtdBaus =  0;
        jogo->salas[ 4 ].qtdBaus =  2;
        jogo->salas[ 5 ].qtdBaus =  0;
        jogo->salas[ 6 ].qtdBaus =  0;
        jogo->salas[ 7 ].qtdBaus =  3;
        jogo->salas[ 8 ].qtdBaus =  1;
        jogo->salas[ 9 ].qtdBaus =  2;
        jogo->salas[ 10 ].qtdBaus =  3;
        jogo->salas[ 11 ].qtdBaus =  0;
        jogo->salas[ 12 ].qtdBaus =  1;
        jogo->salas[ 13 ].qtdBaus =  8;
        jogo->salas[ 14 ].qtdBaus =  0;
        jogo->salas[ 15 ].qtdBaus =  3;

        ///Atribuicao
        int sala , bau;
        for( sala = 0 ; sala < QTDSALAS ; sala++ )
                for( bau = 0 ; bau < jogo->salas[ sala ].qtdBaus ; bau++ ){
                        jogo->salas[ sala ].baus[ bau ].posMapa.x = pos[ sala ][ bau ].x;
                        jogo->salas[ sala ].baus[ bau ].posMapa.y = pos[ sala ][ bau ].y;
                        jogo->salas[ sala ].baus[ bau ].Rotac = rotac[ sala ][ bau ];

                        //Tamanho Constante no mapa global
                        jogo->salas[ sala ].baus[ bau ].posMapa.width = BAU_LARGURA;
                        jogo->salas[ sala ].baus[ bau ].posMapa.height = BAU_COMPRIMENTO;

                        //Imagem
                        jogo->salas[ sala ].baus[ bau ].imagem = jogo->Res.BauFechado;
                        jogo->salas[ sala ].baus[ bau ].posTela.width = BAU_LARGURA * jogo->escalaGeral.x;
                        jogo->salas[ sala ].baus[ bau ].posTela.height = BAU_COMPRIMENTO * jogo->escalaGeral.y;

                        jogo->salas[ sala ].baus[ bau ].src = (Rectangle){ 0 , 0 , jogo->Res.BauFechado.width , jogo->Res.BauFechado.height };
                        jogo->salas[ sala ].baus[ bau ].ABERTO = 0;

//                        jogo->salas[ sala ].baus[ bau ].origin.x = jogo->escalaGeral.x * jogo->Res.BauFechado.width / 2;
//                        jogo->salas[ sala ].baus[ bau ].origin.y = jogo->escalaGeral.y * jogo->Res.BauFechado.height / 2;
                }
}

void CarregarBaus( JOGO *jogo ){
        jogo->Res.BauFechado = LoadTexture( "Sprites/Baús/BauVermelho.png");
        jogo->Res.BauAberto = LoadTexture( "Sprites/Baús/BauVermelhoAberto.png");

}

void inicializarInimigosSalas( JOGO *jogo ){
        int sala[QTD_SALAS_SPAWN] = {0, 2, 4, 5, 6, 8, 10, 12, 13};
        int i;

        /// Porta que sera liberada ao se matar todos os inimigos necessarios
        jogo->salas[0].porta_a_ser_liberada = 2;
        jogo->salas[2].porta_a_ser_liberada = 2;
        jogo->salas[4].porta_a_ser_liberada = 2;
        jogo->salas[5].porta_a_ser_liberada = 2;
        jogo->salas[6].porta_a_ser_liberada = 3;
        jogo->salas[8].porta_a_ser_liberada = 3;
        jogo->salas[10].porta_a_ser_liberada = 2;
        jogo->salas[12].porta_a_ser_liberada = 1; //N precisa
        jogo->salas[13].porta_a_ser_liberada = 1; //N precisa

        /// Quantidade de inimigos para liberar porta 'porta_a_ser_liberada'
        jogo->salas[0].qtd_inimigos_liberar = 5;
        jogo->salas[2].qtd_inimigos_liberar = 8;
        jogo->salas[4].qtd_inimigos_liberar = 7;
        jogo->salas[5].qtd_inimigos_liberar = 8;
        jogo->salas[6].qtd_inimigos_liberar = 15;
        jogo->salas[8].qtd_inimigos_liberar = 3;
        jogo->salas[10].qtd_inimigos_liberar = 2;
        jogo->salas[12].qtd_inimigos_liberar = 3; //N precisa
        jogo->salas[13].qtd_inimigos_liberar = 3; //N precisa

        /// Zerar inimigos ja liberados
        for( i = 0 ; i < QTD_SALAS_SPAWN ; i++)
                jogo->salas[ sala[ i ] ].qtd_inimigos_liberados = 0;

        /// Zerar inimigos ja abatidos
        for( i = 0 ; i < QTD_SALAS_SPAWN ; i++)
                jogo->salas[ sala[ i ] ].qtd_abatidos = 0;

        /// Atribuir VIVO para todos os inimigos
        /// Zerar latencia de ataque para todos os inimigos
        int j;
        for( i = 0 ; i < QTD_SALAS_SPAWN ; i++)
                for( j = 0 ; j < jogo->salas[ sala[ i ] ].qtd_inimigos_liberar ; j++){
                        jogo->salas[ sala[ i ] ].inimigos[ i ].VIVO = 1;                        jogo->salas[ sala[ i ] ].inimigos[ i ].latenciaAtaque = 0;

                }


        /// Atribuir tamanhos
        for( i = 0 ; i < QTD_SALAS_SPAWN ; i++)
                for( j = 0 ; j < jogo->salas[ sala[ i ] ].qtd_inimigos_liberar ; j++){
                        jogo->salas[ sala[ i ] ].inimigos[ j ].posTela.width = MAPA_LQ_T1 * jogo->tela.width / REF_TELA_LARG;
                        jogo->salas[ sala[ i ] ].inimigos[ j ].posTela.height = MAPA_LQ_T1 * jogo->tela.width / REF_TELA_LARG;
                        jogo->salas[ sala[ i ] ].inimigos[ j ].posTelaSolid.width = MAPA_LQ_T1 * jogo->tela.width / REF_TELA_LARG;
                        jogo->salas[ sala[ i ] ].inimigos[ j ].posTelaSolid.height = MAPA_LQ_T1 * jogo->tela.width / REF_TELA_LARG;

                }
}



/** \brief Carrega as spites do inimigos tipo T1 e define valores
 *
 * \param *jogo
 *
 */

void spriteT1( JOGO *jogo ){
        jogo->spriteDef.QTD_FRAMES_T1[ 0 ] = 21; //Andando
        jogo->spriteDef.QTD_FRAMES_T1[ 1 ] = 61; //Ataque


        int status , frame;
        char nmr[10];
        const char comum[] = "Sprites/T1/";
        char pasta[][100] = {
                "movimento/",
                "ataque/",
                " ",
                " ",
                " "
        };

        char fim[] = ".png";
        char arquivo[100];

                for( status = 0 ; status < QTD_STATUS_T1 ; status++ )
                        for( frame = 0 ; frame < jogo->spriteDef.QTD_FRAMES_T1[ status ] ; frame++ )
                        {
                                TextCopy( arquivo , comum );
                                strcat( arquivo , pasta[status] );

                                IntParaString( frame , nmr );
                                strcat( arquivo , nmr );

                                strcat( arquivo , fim );

                                jogo->Res.T1[status][frame] = LoadTexture( arquivo );
                        }

        //Jogador extracao de textura
        jogo->spriteDef.SrcT1.height = SRC_LQ_T1_0;
        jogo->spriteDef.SrcT1.width = SRC_LQ_T1_0;
        jogo->spriteDef.SrcT1.x = SRC_X_T1_0;
        jogo->spriteDef.SrcT1.y = SRC_Y_T1_0;

        //Origin
        jogo->spriteDef.OriginT1.x = MAPA_LQ_T1 / 2.0;
        jogo->spriteDef.OriginT1.y = MAPA_LQ_T1 / 2.0;
}



/** \brief Carrega as spites do inimigos tipo T0 e define valores
 *
 * \param *jogo
 *
 */

void spriteT0( JOGO *jogo ){
        jogo->Res.T0 = LoadTexture("Sprites/aranhas2.png");

//        jogo->spriteDef.QTD_FRAMES_T1[ 0 ] = 7; //Andando
//        jogo->spriteDef.QTD_FRAMES_T1[ 1 ] = 4; //morrendo
//
//
//        int status , frame;
//        char nmr[10];
//        const char comum[] = "Sprites/T1/";
//        char pasta[][100] = {
//                "movimento/",
//                "ataque/",
//                " ",
//                " ",
//                " "
//        };
//
//        char fim[] = ".png";
//        char arquivo[100];
//
//                for( status = 0 ; status < QTD_STATUS_T1 ; status++ )
//                        for( frame = 0 ; frame < jogo->spriteDef.QTD_FRAMES_T1[ status ] ; frame++ )
//                        {
//                                TextCopy( arquivo , comum );
//                                strcat( arquivo , pasta[status] );
//
//                                IntParaString( frame , nmr );
//                                strcat( arquivo , nmr );
//
//                                strcat( arquivo , fim );
//
//                                jogo->Res.T1[status][frame] = LoadTexture( arquivo );
//                        }
//
//        //Jogador extracao de textura
//        jogo->spriteDef.SrcT1.height = SRC_LQ_T1_0;
//        jogo->spriteDef.SrcT1.width = SRC_LQ_T1_0;
//        jogo->spriteDef.SrcT1.x = SRC_X_T1_0;
//        jogo->spriteDef.SrcT1.y = SRC_Y_T1_0;
//
//        //Origin
//        jogo->spriteDef.OriginT1.x = MAPA_LQ_T1 / 2.0;
//        jogo->spriteDef.OriginT1.y = MAPA_LQ_T1 / 2.0;
}
















