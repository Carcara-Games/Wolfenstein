typedef struct{
        char nome[ 10 ][ 100 ];
        int pnts[ 10 ];
}PONTUAC;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
        FILE* arq;
        PONTUAC pontuac;
        arq = fopen("high_scores" , "rb");
        fread( &pontuac , sizeof( PONTUAC ) , 1 , arq );
        fclose( arq );

        for( int i = 0 ; i < 10 ; i++ )
                printf("i = %d   >    %d  -  %s \n" , i , pontuac.pnts[ i ] , pontuac.nome[ i ] );


        getchar();

}
