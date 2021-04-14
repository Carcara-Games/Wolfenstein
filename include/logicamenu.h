#ifndef __LOGICAMENU_H_
#define __LOGICAMENU_H_

        #include "raylib.h"

        char *ItensMenuPrincipal(int escolha);
        char *ItensMenuDificuldade( int escolha );
        void AtualizaMenu( int* selecao , int qtd_opcoes );
        void AtualizaConfirmarSair( int *selecao );
#endif // __LOGICAMENU_H_
