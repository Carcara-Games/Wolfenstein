/**     WOLFENSTEIN
    *     Autores: Manoel Narciso Filho e Matheus De Moraes Costa
    *     Última Modificação: 21/04/2021 16:36
    *
    */

#include "raylib.h"

#include "structsgraficos.h"
#include "inicializar.h"

#include "logicamenu.h"
#include "logicajogo.h"

#include "desenhamenu.h"
#include "desenhajogo.h"
#include "definicoes.h"

///Protótipos
void NovoJogo( Jogo *jogo );
void Continuar( Jogo *jogo);
void ModoHorda( Jogo *jogo);
void Ajuda( Jogo *jogo);
void Configurar( Jogo *jogo);
void Sobre( Jogo *jogo);
void Sair( Jogo *jogo);


///MAIN
int main()
{
        IniciarJanela();  //Configura as opções da janela

        Jogo jogo = IniciaJogo();  // Carrega recursos do jogo
        void (*opcao[])( Jogo* ) = { NovoJogo , Continuar , ModoHorda , Configurar , Ajuda , Sobre , Sair };

        int selecaoMenu = 0;


        while( !((IsKeyPressed( KEY_ENTER ) && selecaoMenu == ITENS_MAIN_MENU - 1 ) || WindowShouldClose() || jogo.FECHAR ) )
        {
                DesenhaMenuPrincipal(&jogo, selecaoMenu);   // Desenha menu principal

                AtualizaMenu( &selecaoMenu , 7 );   // Retorna opção que jogador apertou enter. 7 é o número de opções do menu principal

                if (IsKeyPressed(KEY_ENTER))
                        opcao[ selecaoMenu]( &jogo);
        }
//        DesenharObrigado();
        CloseWindow();
        return 0;
}

void NovoJogo( Jogo *jogo )
{
        int selecaoMenu = 0;

        do
        {
                DesenhaMenuDificuldade( jogo , selecaoMenu );   // Desenha Menu secundário para escolher dificuldade
                AtualizaMenu( &selecaoMenu , ITENS_NOVO_JOGO );   //Atualiza Menu secundário Novo jogo

                if( selecaoMenu != ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER )  )
                {
//                                      CriarNovoJogador();   //  Definir nome do jogador
//                                                        while( !IsGameOver( jogo ) && !IsEndGame( jogo ) ) //Continua avançando de level a menos que usuário receba game over, zere o jogo ou volte para o menu
                        {
//                                                                CarregarLevel( &jogo ); //Carrega as fases em sequência. Se Jogador recebe game over, zera ou pede para voltar para o menu ativa as respectivas flags
//                                                                while( !IsGameOver( jogo )  &&  !IsLevelEnd( jogo )  &&  !IsVoltarMenu( jogo )  )
                                while(  !IsKeyPressed( KEY_P ) )
                                {
                                        AtualizaLevel( jogo );
                                        DesenhaLevel( *jogo );
                                }
                                jogo->Level++;
                        }
                }
        }
        while( !(selecaoMenu == ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER ) ) );
}


void Continuar( Jogo *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Continuar " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void ModoHorda( Jogo *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Modo Horda " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Configurar( Jogo *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Configurar " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Ajuda( Jogo *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Ajuda " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Sobre( Jogo *jogo)
{
        do{
                DesenhaSobre( *jogo );

        }while( IsKeyPressed( KEY_ENTER ) );
}


void Sair( Jogo *jogo)
{
//        int selecaoMenu = 0;
//        do
//        {
//                AtualizaConfirmarSair( &selecaoMenu );   //Janela de confirmação de saída
//                DesenharConfirmarSair( selecaoMenu , jogo);
//                 jogo->FECHAR = selecaoMenu ? SIM : NAO;
//        }while( !IsKeyPressed( KEY_ENTER ) );
        jogo->FECHAR = SIM;
}







