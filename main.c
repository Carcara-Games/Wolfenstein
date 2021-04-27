/**     WOLFENSTEIN
    *     Autores: Manoel Narciso Filho e Matheus De Moraes Costa
    *     �ltima Modifica��o: 21/04/2021 16:36
    *
    */

#include "raylib.h"

#include "OpcoesDoMenu.h"


///MAIN
int main()
{
        IniciarJanela();  //Configura as op��es da janela
        Jogo jogo = IniciaJogo();  // Carrega recursos do jogo

        void (*opcao[])( Jogo* ) = { NovoJogo , Continuar , ModoHorda , Configurar , Ajuda , Sobre , Sair };            //Ponteiro para as opcoes do MENU
        int selecaoMenu = 0;

        while( !((IsKeyPressed( KEY_ENTER ) && selecaoMenu == ITENS_MAIN_MENU - 1 ) || WindowShouldClose() || jogo.FECHAR ) )
        {
                DesenhaMenuPrincipal(&jogo, selecaoMenu);   // Desenha menu principal

                AtualizaMenu( &selecaoMenu , 7 );   // Retorna op��o que jogador apertou enter. 7 � o n�mero de op��es do menu principal

                if (IsKeyPressed(KEY_ENTER))
                        opcao[ selecaoMenu ]( &jogo);
        }
//        DesenharObrigado();
        CloseWindow();
        return 0;
}






