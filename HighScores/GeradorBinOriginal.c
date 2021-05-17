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

        strcpy( pontuac.nome[ 0 ] , "Lampiao" );
        strcpy( pontuac.nome[ 1 ] , "Chuck, o Norris");
        strcpy( pontuac.nome[ 2 ] , "Ojuara");
        strcpy( pontuac.nome[ 3 ] , "Ronaldinho Gaucho, o bruxo");
        strcpy( pontuac.nome[ 4 ] , "Ze da pamonha");
        strcpy( pontuac.nome[ 5 ] , "Napoleao");
        strcpy( pontuac.nome[ 6 ] , "Leticia");
        strcpy( pontuac.nome[ 7 ] , "Spider");
        strcpy( pontuac.nome[ 8 ] , "Tirulipa");
        strcpy( pontuac.nome[ 9 ] , "Abirobaldo");

        pontuac.pnts[ 0 ] = 15000;
        pontuac.pnts[ 1 ] = 7000;
        pontuac.pnts[ 2 ] = 4500;
        pontuac.pnts[ 3 ] = 3000;
        pontuac.pnts[ 4 ] = 2500;
        pontuac.pnts[ 5 ] = 1800;
        pontuac.pnts[ 6 ] = 2500;
        pontuac.pnts[ 7 ] = 1100;
        pontuac.pnts[ 8 ] = 500;
        pontuac.pnts[ 9 ] = 300;

        arq = fopen("high_scores" , "wb");
        fwrite( &pontuac , sizeof( PONTUAC ) , 1 , arq );

        fclose( arq );
}
