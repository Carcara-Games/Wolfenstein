#ifndef __OPCOESDOMENU_H_
#define __OPCOESDOMENU_H_

        #include "estruturascomplexas.h"
        #include "definicoes.h"
        #include "inicializar.h"

        #include "OpcoesDoMenu.h"
        #include "logicamenu.h"
        #include "logicajogo.h"

        #include "desenhamenu.h"
        #include "desenhajogo.h"

        void NovoJOGO( JOGO *jogo );
        void Continuar( JOGO *jogo);
        void ModoHorda( JOGO *jogo);
        void Ajuda( JOGO *jogo);
        void Configurar( JOGO *jogo);
        void Sobre( JOGO *jogo);
        void Sair( JOGO *jogo);



        void CriarNovoJogador( JOGO* jogo );


#endif // __OPCOESDOMENU_H_
