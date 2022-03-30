#include <iostream>
#include <chrono>
#include <utility>

/*
	Tme counting tool
	How to use:
	{
		Benchmark<std::chrono::nanoseconds> b;

		// Code to examinate

		size_t elapsed = b.elapsed();
	}
	or
	{
		Benchmark<std::chrono::milliseconds> b(true);

		// Code to examinate
	}
	object will write the time value in the given units to stderr
*/

template<typename D = std::chrono::microseconds>
class Benchmark
{
public:
	Benchmark(bool printOnExit = false) : m_print(printOnExit)
	{
		start = std::chrono::high_resolution_clock::now();
	}
	typename D::rep elapsed() const
	{
		auto end = std::chrono::high_resolution_clock::now();
		auto result = std::chrono::duration_cast<D>(end - start);
		return result.count();
	}
	~Benchmark()
	{
		auto result = elapsed();
		if (m_print)
		{
			std::cerr << "Time: " << result << "\n";
		}
	}
private:
	std::chrono::high_resolution_clock::time_point start;
	bool m_print = true;
};
