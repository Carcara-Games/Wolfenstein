#ifndef __INICIALIZAR_H_
#define __INICIALIZAR_H_

        #include "estruturascomplexas.h"
        #include "definicoes.h"

        void IniciarJanela( void );

        /// Carregar Pre-Jogo
        JOGO definirPreJogo( void );
        void CriaSalas( JOGO *jogo);
        void CriaZonas( JOGO *jogo);
        void CriaPortas( JOGO *jogo);
        void CriaSpawns( JOGO *jogo );
        void CriaBaus( JOGO *jogo );

        void definirTiposInimigo( JOGO *jogo );
        void definirDadosSpritesPersonagem( JOGO *jogo );
        void definirEscalaGeral( JOGO *jogo );
        void definirTela( JOGO *jogo );
        void definirMapa( JOGO *jogo );

        void carregarTexturasFontes( JOGO *jogo );
        void carregarSpritesPersonagem( JOGO *jogo );

        void CriarRefens( JOGO* jogo );

        void carregarSom( JOGO* jogo );

//#################################################################################################

        /// Inicializar NovoJogo
        void IniciaNovoJogo( JOGO *jogo );
        void inicializarJogador( JOGO *jogo);

//#################################################################################################

        void CarregarLevel( JOGO *jogo);
        void carregarSpritesPes( JOGO *jogo );
        void IntParaString( int nmr , char *str );
        void InverteStr( char *str );
        void CarregarPes( JOGO *jogo );
        void CarregarBaus( JOGO *jogo );
         JOGO preJogo( void);

        void inicializarInimigosSalas( JOGO *jogo );

        void spriteT1( JOGO *jogo );
        void spriteT0( JOGO *jogo );

#endif // __INICIALIZAR_H_
