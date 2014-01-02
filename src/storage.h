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
class Object;
class Storage;

class Vector;
class Oper;

class Matrix_COO;

class Dev;

class Dev
    {
    public:
        Dev()
            {
            }
        ~Dev()
            {
            }
        virtual long int vector_load(Vector *)=0;
        virtual long int matrix_load(Oper *)=0;
        virtual void release(long int)=0;
    };


class Object
    {
    public:
        Object(int d,Dev *de):dim(d),device(de)
            {
            }
        virtual ~Object()
            {
            }
        virtual long int load(void)=0;
        void * pot;
        int dim;
        Dev *device;
    };

class Storage
    {
        std::vector<Object *> objs;
        bool is_load;
        int col_el;
        Dev *device;
    public:
        std::vector<long int> ptrs;
        Storage(Dev *d):is_load(false),col_el(0),device(d)
            {
            
            }
        ~Storage()
            {
            if(is_load==true)
                {
                free();
                }
            for(int i=0;i<col_el;i++)
                {
                delete objs[i];
                }
            }
        template<class T> 
        int add_object(int dim)
            {
            T *per=new T(dim,device);
            objs.push_back(per);
            ptrs.push_back(0);
            col_el++;
            return col_el-1;
            }
        template<class T>
        T& item(int in)
            {
            return *((T *)(objs[in]->pot));
            }
        void load(void)
            {
            for(int i=0;i<col_el;i++)
                {
                ptrs[i]=objs[i]->load();
                }
            is_load=true;
            }
        void free(void)
            {
            if(is_load==true)
                is_load=false;
            else
                return;
            for(int i=0;i<col_el;i++)
                {
                device->release(ptrs[i]);
                ptrs[i]=0;
                }
            }
    };

class Vector:public Object
    {
        std::vector<complex<TYPE> > v;
    public:
        Vector(int d,Dev *de):Object(d,de)
            {
            v.resize(d,complex<TYPE>(0,0));
            pot=(void *)this;
            }
        ~Vector()
            {
            }
        complex<TYPE> & operator [](int in)
            {
            return v[in];
            }
        long int load(void)
            {
            return device->vector_load(this);
            }
        
    };

class Oper:public Object
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
        void add_matr(void);
    public:
        Oper(int d,Dev *de):Object(d,de)
            {
            first=NULL;
            last=NULL;
            num=0;
            pot=(void *)this;
            }
        ~Oper();
        Matrix_COO & operator [](const unsigned int &in);
        int size()
            {
            return num;
            }
        long int load(void)
            {
            return device->matrix_load(this);
            }
    };

class Matrix_COO
    {
    public:
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
    private:
        std::map<key,complex<TYPE> > mat;
        int dim;
    public:
        Matrix_COO(){};
        Matrix_COO(int d):dim(d){};
        ~Matrix_COO(){std::cout<<"a"<<std::endl;};
        void set_nonzero(const int &i,const int &j,const complex<TYPE> &val)
            {
            if(val.__re!=0||val.__im!=0)    
                mat[key(i,j)]=val;
            }
        void set_zero(const int &i,const int &j)
            {
            mat.erase(key(i,j));
            }
        std::map<key,complex<TYPE> >::iterator begin()
            {
            return mat.begin();
            }
        std::map<key,complex<TYPE> >::iterator end()
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
    std::cout<<"Oper"<<std::endl;
    while(first!=NULL)
        {
        teck=first;
        first=first->next;
        delete teck->m;
        delete teck;
        }
    }
#endif
