#include "defs.h"
#include "storage.h"
#include <boost/date_time/posix_time/posix_time.hpp>

class A:public Dev
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
            for(int i=0;i<in->dim;i++)
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
                for(std::map<Matrix_COO::key,complex<TYPE> >::iterator it=(*in)[k].begin();it!=(*in)[k].end();++it)
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
    A per_d;
    Storage a(&per_d);
    int ind;
    ind=a.add_object<Oper>(100);
    a.item<Oper>(ind)[0].set_nonzero(10,15,complex<TYPE>(0,1));
    a.load();
    a.free();
    boost::posix_time::ptime t2 = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration diff = t2 - t1;
    std::cout << diff.total_microseconds() <<"dsfsdfsdfssdfsdf" <<std::endl;
    return 0;
	}
