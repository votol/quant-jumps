#include "defs.h"
#include "storage.h"
#include <boost/date_time/posix_time/posix_time.hpp>

class A:public Device
    {
    public:
        int dev_nom;
        A():dev_nom(0)
            {
            
            }
        ~A()
            {
            
            }
        long int vector_load(Vector *in)
            {
            for(unsigned int i=0;i<in->size();i++)
                {
                std::cout<<(*in)[i].__re<<" "<<(*in)[i].__im<<std::endl; 
                }
            return 0;
            }
        void release(long int in)
            {
            
            }
        long int matrix_load(Oper *in)
            {
            for(unsigned int k=0;k<(*in).size();k++)
                {
                std::cout<<"------------------------------------------------------------------------"<<std::endl;
                for(Matrix_COO::iterator it=(*in)[k].begin();it!=(*in)[k].end();++it)
                    {
                    std::cout<<(*it).first.row<<" "<<(*it).first.col<<" "<<(*it).second.__re<<"+"<<(*it).second.__im<<"*i"<<std::endl;
                    }
                }
            return 0;
            }
    };


int main(int argc,char ** argv)
	{
	boost::posix_time::ptime t1 = boost::posix_time::microsec_clock::local_time();
    A dev;
    Oper hem(128);
    hem[0].set_nonzero(10,20,complex<TYPE>(1,2));
    dev.matrix_load(&hem);
    boost::posix_time::ptime t2 = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration diff = t2 - t1;
    std::cout << diff.total_microseconds() <<std::endl;
    return 0;
	}
