#include "kernels_cuda64.h"
#include "cuda64.h"


long int cuda64::vector_load(const Vector *in)
    {
    return 0;
    }

long int cuda64::matrix_load(const Oper *in)
    {
    return 0;
    }
    
void cuda64::release(long int &in)
    {
    in=0;
    }

void cuda64::matrix_vec_mul(const long int &in,const long int &out,const long int &matr)
    {
    
    }    

void cuda64::get_data(const long int &vec, void *mas,const unsigned int &num )
    {
    
    }
