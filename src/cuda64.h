/*
 * Описан класс для проведения вычислений на видеокарте с использованием
 * cuda. Все ядра которые здесь используются предполагается запскать с
 * геометрией 64 нити в блоке. 
 */
#ifndef __cuda64_h_
#define __cuda64_h_
#include "storage.h"

class cuda64:public Device
    {
    public:
        unsigned int num_dev;
        cuda64():num_dev(0){};
        cuda64(int n):num_dev(n){};
        long int vector_load(const Vector *);
        long int matrix_load(const Oper *);
        void release(long int &);
        
        void matrix_vec_mul(const long int &,const long int &,const long int &);            
        
        void get_data(const long int &, void *,const unsigned int & );
    };



#endif
