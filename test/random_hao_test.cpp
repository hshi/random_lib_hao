#include <iostream>
#include "random_hao.h"

using std::cout;
using std::endl;

#ifdef MPI_HAO
void uniform_hao_mpi_test()
{
    int L=10000000;
    int incircle=0;
    double pi;
    for(int i=0; i<L; i++)
    {
        double x=uniform_hao();
        double y=uniform_hao();
        if((x*x+y*y)<=1.0) incircle++;
    }
    pi=(incircle*4.0)/(L*1.0);
    double sumpi=0;
    MPI_Reduce(&pi,&sumpi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
   
    if(MPI::COMM_WORLD.Get_rank()==0)
    {
        //cout<<sumpi/MPI::COMM_WORLD.Get_size()<<endl;
        pi=sumpi/MPI::COMM_WORLD.Get_size();
        if(abs(pi-3.14159)<0.01) cout<<"Uniform_hao passed the mpi test!\n";
        else cout<<"Warning!!!!Uniform_hao failed the mpi test!\n";
    }
}

void gaussian_hao_mpi_test()
{
    int L=10000000;
    double mean=0; double var=0;
    for(int i=0; i<L; i++)
    {
        double tmp=gaussian_hao();
        mean+=tmp;
        var+=tmp*tmp;
    }
    mean=mean/L; var=var/L;
   
    double summean=0;
    MPI_Reduce(&mean,&summean,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    double sumvar=0;
    MPI_Reduce(&var,&sumvar,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(MPI::COMM_WORLD.Get_rank()==0)
    {
        //cout<<summean/MPI::COMM_WORLD.Get_size()<<endl;
        //cout<<sumvar/MPI::COMM_WORLD.Get_size()<<endl;
        mean=summean/MPI::COMM_WORLD.Get_size();
        var=sumvar/MPI::COMM_WORLD.Get_size();
        if(abs(mean-0)<0.01&&abs(var-1)<0.01) cout<<"Gaussian_hao passed the mpi test!\n";
        else cout<<"Warning!!!!Gaussian_hao failed the mpi test!\n";
    }
}

void random_hao_mpi_test()
{
    uniform_hao_mpi_test();
    gaussian_hao_mpi_test();
}


#else
void uniform_hao_serial_test()
{
    int L=10000000;
    int incircle=0;
    double pi;
    for(int i=0; i<L; i++)
    {
        double x=uniform_hao();
        double y=uniform_hao();
        if((x*x+y*y)<=1.0) incircle++;
    }
    pi=(incircle*4.0)/(L*1.0);
    if(abs(pi-3.14159)<0.01) cout<<"Uniform_hao passed the serial test!\n";
    else cout<<"Warning!!!!Uniform_hao failed the serial test!\n";
}

void gaussian_hao_serial_test()
{
    int L=10000000;
    double mean=0; double var=0;
    for(int i=0; i<L; i++)
    {
        double tmp=gaussian_hao();
        mean+=tmp;
        var+=tmp*tmp; 
    }
    mean=mean/L; var=var/L;
    if(abs(mean-0)<0.01&&abs(var-1)<0.01) cout<<"Gaussian_hao passed the serial test!\n";
    else cout<<"Warning!!!!Gaussian_hao failed the serial test!\n";
}

void random_hao_serial_test()
{
    uniform_hao_serial_test();
    gaussian_hao_serial_test();
}
#endif
