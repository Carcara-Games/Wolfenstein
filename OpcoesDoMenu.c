
#include "OpcoesDoMenu.h"


void NovoJogo( Jogo *jogo )
{
        int selecaoMenu = 0;

        do
        {
                DesenhaMenuDificuldade( jogo , selecaoMenu );   // Desenha Menu secund�rio para escolher dificuldade
                AtualizaMenu( &selecaoMenu , ITENS_NOVO_JOGO );   //Atualiza Menu secund�rio Novo jogo

                if( selecaoMenu != ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER )  )
                {
//                                      CriarNovoJogador();   //  Definir nome do jogador
//                                                        while( !IsGameOver( jogo ) && !IsEndGame( jogo ) ) //Continua avan�ando de level a menos que usu�rio receba game over, zere o jogo ou volte para o menu
                        {
//                                                                CarregarLevel( &jogo ); //Carrega as fases em sequ�ncia. Se Jogador recebe game over, zera ou pede para voltar para o menu ativa as respectivas flags
//                                                                while( !IsGameOver( jogo )  &&  !IsLevelEnd( jogo )  &&  !IsVoltarMenu( jogo )  )
                                while(  !IsKeyPressed( KEY_P ) )
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
//                AtualizaConfirmarSair( &selecaoMenu );   //Janela de confirma��o de sa�da
//                DesenharConfirmarSair( selecaoMenu , jogo);
//                 jogo->FECHAR = selecaoMenu ? SIM : NAO;
//        }while( !IsKeyPressed( KEY_ENTER ) );
        jogo->FECHAR = SIM;
}


