
#include "fisica.h"


/** \brief Calcula o sinal de algum numero
 *
 * \param Numero float
 * \param
 * \return -1(NEGATIVO) , 1(POSITIVO) , 0(ZERO)
 *
 */

int sinalNumero( float nmr ){

        if(nmr == 0) return 0;

        return ( nmr > 0 ) ? 1 : -1;


}

/** \brief Gera numero inteiro  aleatorio
 *
 * \param Valor inteirominimo
 * \param Valor inteiro maximo
 * \return Numero aleatorio inteiro pertencente a [ min , max ]
 *
 */

int nmrRand( int mini , int maxi ){
        srand( time(NULL) );

        return mini + rand() % ( maxi + 1 - mini );
}



/** \brief Calcula o delocamento entre dois pontos
 *
 * \param Ponto A
 * \param Ponto B
 * \return Deslocamento
 *
 */

float Deslocamento(Vector2 posInicial, Vector2 posFinal)
{
        int deslocX, deslocY;

        deslocX = posFinal.x - posInicial.x;
        deslocY = posFinal.y - posInicial.y;

        return sqrt(pow(deslocX, 2) + pow(deslocY, 2));
}



/** \brief Calcula Modulo de Vector
 *
 * \param Vector
 * \return Modulo
 *
 */

float modVector(Vector2 vet)
{
        return sqrt(pow(vet.x, 2) + pow(vet.y, 2));
}



/** \brief Calcula argumento de Vector
 *
 * \param Vector
 * \return Argumento
 *
 */

float argVector(Vector2 vet)
{
        return (180 / PI) * atan2(vet.y, vet.x);
}



/** \brief Retorna o vector resultante da soma de dois vectores
 *
 * \param Vector A
 * \param Vector B
 * \return Vector C = A + B
 *
 */

Vector2 SomaVectores(Vector2 vet1, Vector2 vet2)
{
        return (Vector2){vet1.x + vet2.x, vet1.y + vet2.y};
}
