/*
* ---------------------------------------------------------------------
* Коментарий 1
* Описан класс Object, который является родителем для классов хранилищь
* матриц CSR и векторов. В этом классе есть указатель на потомок в виде
* void * по которому можно получать доступ к интерфейсу потомка, также
* есть функторы, которые вызываются для записи на устройства и освобож
* дения памяти. Эти функторы инициализируются в конструкторе потомка.
* Функции для функторов написаны в специальном классе Dev, в котором ле
* жат все функции которые работают с устройством      
* ---------------------------------------------------------------------
*    
*/
#ifndef __storage_h_
#define __storage_h_
#include "defs.h"
#include "complex.h"

class Vector;
class Oper;

class Matrix_COO;

class Device;

class Device
    {
    public:
        Device()
            {
            }
        ~Device()
            {
            }
        virtual long int vector_load(Vector *)=0;
        virtual long int matrix_load(Oper *)=0;
        virtual void release(long int)=0;
    };


class Vector
    {
        std::vector<complex<TYPE> > v;
        unsigned int dim;
    public:
        Vector(int d):dim(d)
            {
            v.resize(d,complex<TYPE>(0,0));
            }
        ~Vector()
            {
            }
        complex<TYPE> & operator [](int in)
            {
            return v[in];
            }
        unsigned int & size()
            {
            return dim;
            }
    };

class Oper
    {
        struct ms_list
            {
            Matrix_COO *m;
            ms_list *next;
            };
        ms_list *first;
        ms_list *last;
        ms_list *teck;
        unsigned int num;
        int dim;
        void add_matr(void);
    public:
        Oper(int d):dim(d)
            {
            first=NULL;
            last=NULL;
            num=0;
            }
        ~Oper();
        Matrix_COO & operator [](const unsigned int &in);
        unsigned int& size()
            {
            return num;
            }
    };

class Matrix_COO
    {
        class key
            {
            public:
                int col;
                int row;
                key():col(0),row(0){};
                key(const int &i,const int &j):col(i),row(j){};
                key(const key &in)
                    {
                    col=in.col;
                    row=in.row;
                    }
                ~key(){};
                key & operator =(const key &in)
                    {
                    col=in.col;
                    row=in.row;
                    return *this;
                    }
            };
        friend bool operator <(const key &a,const key &b);
        std::map<key,complex<TYPE> > mat;
        int dim;
    public:
        typedef std::map<key,complex<TYPE> >::iterator iterator; 
        Matrix_COO(){};
        Matrix_COO(int d):dim(d){};
        ~Matrix_COO(){};
        void set_nonzero(const int &i,const int &j,const complex<TYPE> &val)
            {
            if(val.__re!=0||val.__im!=0)    
                mat[key(i,j)]=val;
            }
        void set_zero(const int &i,const int &j)
            {
            mat.erase(key(i,j));
            }
        iterator begin()
            {
            return mat.begin();
            }
        iterator end()
            {
            return mat.end();
            }
    };
bool operator<(const Matrix_COO::key &a,const Matrix_COO::key &b)
    {
    if(a.row!=b.row)
        return a.row<b.row;
    else
        return a.col<b.col;
    }


void Oper::add_matr(void)
    {
    if(last==NULL)
        {
        first=new ms_list;
        first->next=NULL;
        first->m=new Matrix_COO(dim);
        last=first;
        }
    else
        {
        last->next=new ms_list;
        last=last->next;
        last->next=NULL;
        last->m=new Matrix_COO(dim);
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
#endif
