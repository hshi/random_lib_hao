#include <iostream>
#include <cmath>
#include "random_hao.h"

using namespace std;

void random_checkpoint_test()
{
    int L=10; int L_check=5;
    double ran[L],ran_check[L];

    random_hao_init();
    for(int i=0;i<L;i++) ran[i]=uniform_hao();

    random_hao_init();
    for(int i=0;i<L_check;i++) ran_check[i]=uniform_hao();
    random_hao_save();
    for(int i=0; i<100; i++) uniform_hao();
    random_hao_init(-1,1);  // it is the same with: random_hao_read();
    for(int i=L_check;i<L;i++) ran_check[i]=uniform_hao();

    int flag=0;
    for(int i=0;i<L;i++) 
    {
        if( abs( ran[i]-ran_check[i] ) > 1e-12 ) flag++;
    }

    int rank=0;
#ifdef MPI_HAO
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif
    string filename="random_checkpoint_"+ to_string(rank) +".dat";
    remove( filename.c_str() );
    if(flag!=0) cout<<"Warning!!!! Random_checkpoint failed the test! "<<rank<<endl;
    if(rank==0) cout<<"PASSED! If there is no warning, Random_hao passed the checkpoint test. "<<endl;
}


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
        if(abs(pi-3.14159)<0.01) cout<<"PASSED! Uniform_hao passed the mpi test!"<<endl;
        else cout<<"Warning!!!!Uniform_hao failed the mpi test!"<<endl;
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
        if(abs(mean-0)<0.01&&abs(var-1)<0.01) cout<<"PASSED! Gaussian_hao passed the mpi test!"<<endl;
        else cout<<"Warning!!!!Gaussian_hao failed the mpi test!"<<endl;
    }
}

void random_hao_mpi_test()
{
    random_checkpoint_test();
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
    if(abs(pi-3.14159)<0.01) cout<<"PASSED! Uniform_hao passed the serial test!"<<endl;
    else cout<<"Warning!!!!Uniform_hao failed the serial test!"<<endl;
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
    if(abs(mean-0)<0.01&&abs(var-1)<0.01) cout<<"PASSED! Gaussian_hao passed the serial test!"<<endl;
    else cout<<"Warning!!!!Gaussian_hao failed the serial test!"<<endl;
}

void random_hao_serial_test()
{
    random_checkpoint_test();
    uniform_hao_serial_test();
    gaussian_hao_serial_test();
}
#endif
