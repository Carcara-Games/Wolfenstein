/**     WOLFENSTEIN
    *     Autores: Manoel Narciso Filho e Matheus De Moraes Costa
    *     Última Modificação: 09/04/2021 16:36
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


///MAIN
int main()
{
        IniciarJanela();  //Configura as opções da janela

        Jogo jogo = IniciaJogo();  // Carrega recursos do jogo

        int selecaoMenu = 0;

        while( !((IsKeyPressed( KEY_ENTER ) && selecaoMenu == ITENS_MAIN_MENU - 1 ) || WindowShouldClose() || jogo.FECHAR ) )
        {
                DesenhaMenuPrincipal(&jogo, selecaoMenu);   // Desenha menu principal
                AtualizaMenu( &selecaoMenu , 7 );   // Retorna opção que jogador apertou enter. 7 é o número de opções do menu principal

                if (IsKeyPressed(KEY_ENTER))
                {
                        jogo.NivelMenu = 1;
                        switch( selecaoMenu )   // Escolhe ação dependendo opção escolhida no menu principal
                        {

                                case 0:   //Novo Jogo ---------------------------------------------------------------------------------------------------------------------------------------------------
                                        do
                                        {
                                                DesenhaMenuDificuldade( &jogo , selecaoMenu );   // Desenha Menu secundário para escolher dificuldade
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
                                                                        AtualizaLevel( &jogo );
                                                                        DesenhaLevel( jogo );
                                                                }
                                                                jogo.Level++;
                                                        }
                                                }
                                        }
                                        while( !(selecaoMenu == ITENS_NOVO_JOGO - 1 && IsKeyPressed( KEY_ENTER ) ) );

                                        break;

                                case 1:    //Continuar ------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                ListaJogadoresSalvos();  //Menu secundário que apresenta jogadores salvos ( cada jogador criado só pode manter um savegame para não virar uma zona)
                                        break;


                                case 2:    //Modo Horda ---------------------------------------------------------------------------------------------------------------------------------------------------
        //                                IniciarModoHorda();   //Inicia modo horda. Dificuldade única
                                        break;

                                case 3:    //Configurar ------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                AbreConfiguracoes();   //Menu secundário de configurações
                                        //Só um teste
                                        while( !IsKeyPressed( KEY_A ) )
                                        {

                                                BeginDrawing();
                                                        ClearBackground( WHITE );
                                                        DrawRectangle( 100 , 400 , 70 , 30 , RED);
                                                        DrawTriangle( (Vector2 ){ 100 , 100} , (Vector2 ){ 500 , 100} , (Vector2 ){ 400 , 400} , GREEN);
                                                EndDrawing();
                                        }
                                        break;

                                case 4:    //Ajuda ------------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                ApresentaAjuda();   // Ajudas e dicas gerais sobre o jogo e sobre os comandos

                                        break;

                                case 5:    //Sobre ------------------------------------------------------------------------------------------------------------------------------------------------------------
                                        do{
                                                DesenhaSobre( jogo );   //Apresenta autores e etc
                                        }while( !IsKeyPressed(KEY_ENTER) );

                                        break;

                                case 6:    //Sair ---------------------------------------------------------------------------------------------------------------------------------------------------
                                        selecaoMenu = 0;
                                        do
                                        {
                                                AtualizaConfirmarSair( &selecaoMenu );   //Janela de confirmação de saída
                                                DesenharConfirmarSair( selecaoMenu , &jogo);
                                                 jogo.FECHAR = selecaoMenu ? SIM : NAO;
                                        }while( !IsKeyPressed( KEY_ENTER ) );
                                        break;
                        }
                }

        }

        DesenharObrigado();
        CloseWindow();
        return 0;
}











