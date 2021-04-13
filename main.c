/**     WOLFENSTEIN
    *     Autores: Manoel Narciso Filho e Matheus De Moraes Costa
    *     �ltima Modifica��o: 09/04/2021 16:36
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

///Prot�tipos


///MAIN
int main()
{
        IniciarJanela();  //Configura as op��es da janela

        Jogo jogo = IniciaJogo();  // Carrega recursos do jogo

        int selecaoMenu = 0;

        while( !((IsKeyPressed( KEY_ENTER ) && selecaoMenu == ITENS_MAIN_MENU - 1 ) || WindowShouldClose() || jogo.FECHAR ) )
        {
                DesenhaMenuPrincipal(&jogo, selecaoMenu);   // Desenha menu principal
                AtualizaMenu( &selecaoMenu , 7 );   // Retorna op��o que jogador apertou enter. 7 � o n�mero de op��es do menu principal

                if (IsKeyPressed(KEY_ENTER))
                {
                        jogo.NivelMenu = 1;
                        switch( selecaoMenu )   // Escolhe a��o dependendo op��o escolhida no menu principal
                        {

                                case 0:   //Novo Jogo ---------------------------------------------------------------------------------------------------------------------------------------------------
                                        do
                                        {
                                                DesenhaMenuDificuldade( &jogo , selecaoMenu );   // Desenha Menu secund�rio para escolher dificuldade
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
        //                                ListaJogadoresSalvos();  //Menu secund�rio que apresenta jogadores salvos ( cada jogador criado s� pode manter um savegame para n�o virar uma zona)
                                        break;


                                case 2:    //Modo Horda ---------------------------------------------------------------------------------------------------------------------------------------------------
        //                                IniciarModoHorda();   //Inicia modo horda. Dificuldade �nica
                                        break;

                                case 3:    //Configurar ------------------------------------------------------------------------------------------------------------------------------------------------------
        //                                AbreConfiguracoes();   //Menu secund�rio de configura��es
                                        //S� um teste
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
                                                AtualizaConfirmarSair( &selecaoMenu );   //Janela de confirma��o de sa�da
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











