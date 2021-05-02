#ifndef __FISICA_H_
#define __FISICA_H_

        #include <stdlib.h>
        #include <time.h>
        #include <math.h>
        #include "raylib.h"

        Vector2 SomaVectores( Vector2 vet1 , Vector2 vet2 );

        float Deslocamento( Vector2 posInicial ,  Vector2 posFinal );
        float modVector( Vector2 vet );
        float argVector( Vector2 vet );
        int sinalNumero( float nmr );
        int nmrRand( int mini , int maxi );

#endif // __FISICA_H_
