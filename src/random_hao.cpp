#include <math.h> 
#include "random_hao.h"

void random_hao_init(int seed, int gtype)
{
#ifdef MPI_HAO
 MPI_Bcast(&seed,1,MPI_INT,0,MPI_COMM_WORLD );
 MPI_Bcast(&gtype,1,MPI_INT,0,MPI_COMM_WORLD );
#endif
 //If seed is 0, random set the seed
 if(seed==0) seed = make_sprng_seed();
 init_sprng(gtype,seed,SPRNG_DEFAULT); 
}

double uniform_hao()
{
 return sprng();
}

double gaussian_hao()
{
#define pi 3.14159265358979324
 double tmp=sprng();
 //log(tmp) will be NA, if tmp==0
 if(tmp==0) tmp+=1e-300;
 return sqrt(-2.0*log(tmp))*cos(2.0*pi*sprng());
}
