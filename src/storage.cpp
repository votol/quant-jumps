#include "storage.h"

Vector::Vector(int d):dim(d)
    {
    v.resize(d,complex<TYPE>(0,0));
    }
Vector::~Vector()
    {
    }
complex<TYPE> & Vector::operator [](int in)
    {
    return v[in];
    }
unsigned int & Vector::size()
    {
    return dim;
    }
Oper::Oper(int d,int nt):dim(d),num_t(nt)
    {
    first=NULL;
    last=NULL;
    num=0;
    }
Oper::~Oper()
    {
    while(first!=NULL)
        {
        teck=first;
        first=first->next;
        delete teck->m;
        delete teck;
        }
    }
unsigned int& Oper::size()
    {
    return num;
    }
void Oper::add_matr(void)
    {
    if(last==NULL)
        {
        first=new ms_list;
        first->next=NULL;
        first->m=new Matrix_COO(dim,num_t);
        last=first;
        }
    else
        {
        last->next=new ms_list;
        last=last->next;
        last->next=NULL;
        last->m=new Matrix_COO(dim,num_t);
        }
    num++;
    }

Matrix_COO & Oper::operator [](const unsigned int &in)
    {
    if(in>=num)
        {
        while(in>=num)
            {
            add_matr();
            }
        return *(last->m);
        }
    else
        {
        unsigned int i=0;
        teck=first;
        while(in!=i)
            {
            teck=teck->next;
            i++;
            }
        return *(teck->m);
        }
    }

Matrix_COO::key::key():col(0),row(0)
    {
    }
Matrix_COO::key::key(const int &i,const int &j):col(i),row(j)
    {
    }
Matrix_COO::key::key(const key &in)
    {
    col=in.col;
    row=in.row;
    }
Matrix_COO::key::~key()
    {
    }
Matrix_COO::key & Matrix_COO::key::operator =(const Matrix_COO::key &in)
    {
    col=in.col;
    row=in.row;
    return *this;
    }
bool operator<(const Matrix_COO::key &a,const Matrix_COO::key &b)
    {
    if(a.row!=b.row)
        return a.row<b.row;
    else
        return a.col<b.col;
    }

Matrix_COO::Matrix_COO()
    {
    }
Matrix_COO::Matrix_COO(unsigned int d,unsigned int nt):dim(d),num_t(nt)
    {
    coe_t=new complex<TYPE>[num_t];
    }
Matrix_COO::~Matrix_COO()
    {
    delete coe_t;std::cout<<"matr"<<std::endl;
    }
void Matrix_COO::set_nonzero(const int &i,const int &j,const complex<TYPE> &val)
    {
    if(val.__re!=0||val.__im!=0)    
        mat[key(i,j)]=val;
    }
void Matrix_COO::set_zero(const int &i,const int &j)
    {
    mat.erase(key(i,j));
    }
Matrix_COO::iterator Matrix_COO::begin()
    {
    return mat.begin();
    }
Matrix_COO::iterator Matrix_COO::end()
    {
    return mat.end();
    }
complex<TYPE> & Matrix_COO::operator [](unsigned int i)
    {
    if(i<num_t)
        {
        return coe_t[i];
        }
    else
        {
        }
    }
