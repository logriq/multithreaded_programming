#pragma once
#include <iostream>
#include <mutex>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

using namespace std::chrono_literals;

class c_condition_variable
{
private:
	std::mutex mtx;
	std::atomic < bool> notified = false;
public:
	template<typename Predicate>
	void wait(std::unique_lock<std::mutex>& lock, Predicate pred)
	{
		while (!pred())
		{
			lock.unlock();
			while (!notified.load())
			{
				std::this_thread::sleep_for(1ms);
			}
			lock.lock();
		}
		notified.store(false);
	}

	void notify_one()
	{
		notified.store(true);
	}

	void notify_all()
	{
		notified.store(true);
	}
};