#ifndef __INICIALIZAR_H_
#define __INICIALIZAR_H_

        #include "structsgraficos.h"
        #include "definicoes.h"

        void IniciarJanela( void );
        Jogo IniciaJogo( void );
        void CarregarLevel( Jogo *jogo);
        void carregarTexturasFontes( Jogo *jogo );
        void CriaSalas( Jogo *jogo);
        void CriaZonas( Jogo *jogo);
        void CriaPortas( Jogo *jogo);
        void CarregarPersonagemImagens( Jogo *jogo );
        void CarregarPes( Jogo *jogo );
        void IntParaString( int nmr , char *str );
        void InverteStr( char *str );
        void CarregarPes( Jogo *jogo );
        void inicializarSpawns( Jogo *jogo );
        void inicializarBaus( Jogo *jogo );
        void CarregarBaus( Jogo *jogo );

        void inicializarInimigosSalas( Jogo *jogo );


#endif // __INICIALIZAR_H_
