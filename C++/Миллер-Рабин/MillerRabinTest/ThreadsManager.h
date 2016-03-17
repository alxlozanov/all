#include <thread>
#include <future>
#include <mutex>
#include <fstream>
#include <stdio.h>

#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/special_functions/pow.hpp>
#include<boost\multiprecision\cpp_int.hpp>
#include<boost\any.hpp>


using namespace boost::multiprecision;
using namespace std;

class ThreadsManager
{

public:
	ThreadsManager();
	virtual ~ThreadsManager();

	typedef void(*callback)(uint64_t, uint64_t, uint64_t, uint64_t*, std::mutex *locker, FILE *file, std::vector<uint128_t> *spps);

	void parallel_by_cores(std::atomic<bool> *temp_completed_threads, FILE*file, uint64_t max_count, uint64_t *numbers, int step, int step_low_border, callback func, int sub_threads_count = 0);
	void wait_for_end();
	
	// �������� ����(� ������� ��������� ���������)
	FILE *FOUT_FILE;
protected:

	int STEP;
	int STEP_LOW_BORDER;

	atomic<bool> *COMPLETED_THREADS;
	mutex locker;

	int THREADS_COUNT;
	thread *THREADS;
};
