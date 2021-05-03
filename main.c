/**     WOLFENSTEIN
    *     Autores: Manoel Narciso Filho e Matheus De Moraes Costa
    *     Última Modificação: 21/04/2021 16:36
    *
    */

#include "raylib.h"

#include "inicializar.h"
#include "OpcoesDoMenu.h"


///MAIN
int main()
{
        IniciarJanela();  //Configura as opcoes da janela
        JOGO jogo = definirPreJogo();          // Inicializa fontes, texturas e informacoes gerais do jogo
        IniciaNovoJogo( &jogo );  // Incializa informacoes para Novo Jogo

        void (*opcao[])( JOGO* ) = { NovoJOGO , Continuar , ModoHorda , Configurar , Ajuda , Sobre , Sair };            //Ponteiro para as opcoes do MENU
        int selecaoMenu = 0;

        while( !((IsKeyPressed( KEY_ENTER ) && selecaoMenu == ITENS_MAIN_MENU - 1 ) || WindowShouldClose() || jogo.FECHAR ) )
        {
                DesenhaMenuPrincipal(&jogo, selecaoMenu);   // Desenha menu principal

                AtualizaMenu( &selecaoMenu , 7 );   // Retorna opção que jogador apertou enter. 7 é o número de opções do menu principal

                if (IsKeyPressed(KEY_ENTER))
                        opcao[ selecaoMenu ]( &jogo);
        }
//        DesenharObrigado();
        CloseWindow();
        return 0;
}






