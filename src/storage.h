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
#include <vector>
#include <map>
#include <iterator>
#include <iostream>
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
        virtual long int vector_load(const Vector *)=0;
        virtual long int matrix_load(const Oper *)=0;
        virtual void release(long int &)=0;
        
        virtual void matrix_vec_mul(const long int &,const long int &,const long int &)=0;            
        
        virtual void get_data(const long int &, void *,const unsigned int & )=0;
    };


class Vector
    {
        std::vector<complex<TYPE> > v;
        unsigned int dim;
    public:
        Vector(int d);
        ~Vector();
        complex<TYPE> & operator [](int in);
        unsigned int & size();
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
        int num_t;
        void add_matr(void);
    public:
        Oper(int d,int nt);
        ~Oper();
        Matrix_COO & operator [](const unsigned int &in);
        unsigned int& size();
    };

class Matrix_COO
    {
        class key
            {
            public:
                int col;
                int row;
                key();
                key(const int &i,const int &j);
                key(const key &in);
                ~key();
                key & operator =(const key &in);
            };
        friend bool operator <(const key &a,const key &b);
        std::map<key,complex<TYPE> > mat;
        unsigned int dim;
        unsigned int num_t;
        complex<TYPE> *coe_t;
    public:
        typedef std::map<key,complex<TYPE> >::iterator iterator; 
        Matrix_COO();
        Matrix_COO(unsigned int d,unsigned int nt);
        ~Matrix_COO();
        void set_nonzero(const int &i,const int &j,const complex<TYPE> &val);
        void set_zero(const int &i,const int &j);
        iterator begin();
        iterator end();
        complex<TYPE> & operator [](unsigned int i);
    };

#endif
