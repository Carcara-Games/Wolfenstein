
#include "OpcoesDoMenu.h"
#include "booleanas.h"


void NovoJOGO( JOGO *jogo )
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
                                while(  !IsGameOver( *jogo )  &&  !IsKeyPressed( KEY_HOME ) )
                                {
                                        AtualizaLevel( jogo );
                                        DesenhaLevel( jogo );
                                }
//                                jogo->atualLevel++;
                        }
                }
        }
        while( !(selecaoMenu == ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER ) ) );
}


void Continuar( JOGO *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Continuar " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void ModoHorda( JOGO *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Modo Horda " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Configurar( JOGO *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Configurar " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Ajuda( JOGO *jogo)
{
        while( !IsKeyPressed( KEY_A ) )
        {

                BeginDrawing();
                        ClearBackground( WHITE );
                        DrawText(" Ajuda " , 300 , 300 , 50 , GREEN );
                EndDrawing();
        }

}


void Sobre( JOGO *jogo)
{
        do{
                DesenhaSobre( *jogo );

        }while( IsKeyPressed( KEY_ENTER ) );
}


void Sair( JOGO *jogo)
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


