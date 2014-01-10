#include "defs.h"
#include "storage.h"
#include <boost/date_time/posix_time/posix_time.hpp>

int main(int argc,char ** argv)
	{
	boost::posix_time::ptime t1 = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::ptime t2 = boost::posix_time::microsec_clock::local_time();
    boost::posix_time::time_duration diff = t2 - t1;
    std::cout << diff.total_microseconds() <<std::endl;
    return 0;
	}
