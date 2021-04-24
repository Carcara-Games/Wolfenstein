#ifndef __OPCOESDOMENU_H_
#define __OPCOESDOMENU_H_

        #include "structsgraficos.h"
        #include "definicoes.h"
        #include "inicializar.h"

        #include "OpcoesDoMenu.h"
        #include "logicamenu.h"
        #include "logicajogo.h"

        #include "desenhamenu.h"
        #include "desenhajogo.h"

        void NovoJogo( Jogo *jogo );
        void Continuar( Jogo *jogo);
        void ModoHorda( Jogo *jogo);
        void Ajuda( Jogo *jogo);
        void Configurar( Jogo *jogo);
        void Sobre( Jogo *jogo);
        void Sair( Jogo *jogo);

#endif // __OPCOESDOMENU_H_
