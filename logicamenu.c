
#include "logicamenu.h"

/**     Funcao ItensMenuPrincipal() :
     */

char *ItensMenuPrincipal(int escolha)
{
        static char opcao[ 7 ][ 30 ] =             {
                                                                                "Novo Jogo" ,  // 0       //Items do menu
                                                                                "Continuar" ,   // 1
                                                                                "Modo Horda" ,  // 2
                                                                                "Configurar" , // 3
                                                                                "Ajuda" ,    // 4
                                                                                "Sobre" ,   // 5
                                                                                "Sair"    // 6
                                                                        };

        return opcao[ escolha ];
}
//##############################################################################



/**     Funcao ItensMenuDificuldade() : Retorna os itens do menu de escolha de dificuldade
    */

char *ItensMenuDificuldade( int escolha )
{
        static char itens[ 7 ][ 70 ] = {
                "Recruta",
                "Soldado",
                "Coronel",
                "Chuck Norris",
                "Voltar",
                "Escolha a sua patente:",
                "ALERTA: COM GRANDES PODERES VEM GRANDES RESPONSABILIDADES..."
         };

        return itens[ escolha ];
}
//##############################################################################



/**      Funcao AtualizaMenu() : Atualiza a seleção de algum menu
    *                   ->Entradas: Endereço da variável seleção e quantidade de opções do menu
    */

void AtualizaMenu(  int* selecao , int qtd_opcoes )
{

        if( IsKeyPressed( KEY_DOWN)  &&  *selecao < qtd_opcoes - 1  )
        {
                PlaySound( LoadSound("Som/setas.wav") );
                (*selecao)++;
                return;
        }

        if( IsKeyPressed( KEY_UP)  &&  *selecao > 0 )
        {
                PlaySound( LoadSound("Som/setas.wav"));
                (*selecao)--;
                return;
        }

}
//##############################################################################



/**     Funcao AtualizaConfirmarSair() : Retorna os itens do menu de escolha de dificuldade
    */
void AtualizaConfirmarSair( int *selecao )
{

        if( ( IsKeyPressed( KEY_DOWN) || IsKeyPressed( KEY_RIGHT) ) &&  !*selecao  )
        {
                (*selecao)++;
                PlaySound( LoadSound("Som/setas.wav") );
                return;
        }

        if( ( IsKeyPressed( KEY_UP) || IsKeyPressed( KEY_LEFT) ) &&  *selecao )
        {
                (*selecao)--;
                PlaySound( LoadSound("Som/setas.wav") );
                return;
        }

}
//##############################################################################
