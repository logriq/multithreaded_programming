#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include "condition_variable_custom.h"

c_condition_variable simple_cv;
std::mutex mtx;
bool ready = false;

void worker(int id)
{
	std::unique_lock<std::mutex> lock(mtx);

	std::cout << "Thread # " << id << " is waiting..." << std::endl;

	simple_cv.wait(lock, [] { return ready; });

	std::cout << "Thread # " << id << " woke up!" << std::endl;
}

int main()
{
	std::thread t1(worker, 1);

	std::this_thread::sleep_for(std::chrono::seconds(2));

	{
		std::lock_guard<std::mutex> lock(mtx);
		ready = true;
		std::cout << "Main thread: Data is ready, signaling..." << std::endl;
	}

	simple_cv.notify_one();

	t1.join();

	std::cout << "Main thread: Work finished." << std::endl;

	return 0;
}