#include <iostream>
#include "random_hao.h"

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

    random_hao_init(0,1);

#ifdef MPI_HAO
    //std::cout<<uniform_hao()<<" "<<MPI::COMM_WORLD.Get_rank()<<std::endl;
    random_hao_mpi_test();
#else
    random_hao_serial_test();
#endif

#ifdef MPI_HAO
    MPI_Finalize();
#endif

    return 0;
}
