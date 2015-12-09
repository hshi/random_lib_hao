#include <iostream>
#include "random_hao.h"

using namespace std;

#ifdef MPI_HAO
void random_hao_mpi_test();
#else
void random_hao_serial_test();
#endif


int main(int argc, char** argv)
{
#ifdef MPI_HAO
    MPI_Init(&argc,&argv);
#endif

    random_hao_init();

#ifdef MPI_HAO
    if(MPI::COMM_WORLD.Get_rank()==0) cout<<"\n\n\n=======Testing======="<<endl; 
    random_hao_mpi_test();
#else
    cout<<"\n\n\n=======Testing======="<<endl;
    random_hao_serial_test();
#endif

#ifdef MPI_HAO
    MPI_Finalize();
#endif

    return 0;
}
