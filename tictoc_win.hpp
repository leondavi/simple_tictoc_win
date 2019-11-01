#pragma once 

#include <chrono>
#include <cstdint>
#include <functional>
#include <sstream>
#include <vector>
#include <string>

class CurrentTime {
	std::chrono::high_resolution_clock m_clock;

public:
	inline uint64_t milliseconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>
			(m_clock.now().time_since_epoch()).count();
	}

	inline uint64_t CurrentTime::microseconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>
			(m_clock.now().time_since_epoch()).count();
	}	

	inline uint64_t CurrentTime::nanoseconds()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>
			(m_clock.now().time_since_epoch()).count();
	}
};







class tictoc
{
private: 
	CurrentTime ct;
	uint8_t units;
	uint64_t tic_time;
	uint64_t toc_time;
	uint64_t elapsed_time; 
	bool tic_called_once;


public:
	typedef enum Tunit{milli,micro,nano};//in seconds 
	std::vector<std::string> units_str_vec = { "[ms]","[mrs]","[ns]" };
	tictoc(Tunit units = milli) : units(units),tic_called_once(false)
	{
		
		tic_time = 0;
		toc_time = 0;
	}

	inline uint64_t get_time()
	{
		uint64_t res;
		switch (units)
		{
			case milli: { res = ct.milliseconds(); break; }
			case micro: { res = ct.microseconds(); break; }
			case nano: { res = ct.nanoseconds(); break; }
			default: {res = 0; }
		}
		return res;
	}

	inline void tic()
	{
		tic_time = get_time();
		tic_called_once = true;
	}

	inline uint64_t toc()
	{
		toc_time = get_time();
		elapsed_time = toc_time - tic_time;
		return elapsed_time;
	}

	inline uint64_t get_elapsed()
	{
		toc();
		if (tic_called_once)
		{
			return this->elapsed_time;
		}
		else
		{
			throw "tic wasn't called - but elapsed was called";
		}
		return 0;
	}

	inline std::string units_str()
	{
		return units_str_vec[units];
	}

	inline std::string elapsed_str()
	{
		if (tic_called_once)
		{
			std::stringstream ss;
			ss << elapsed_time << units_str_vec[units];
			return ss.str();
		}
		else
		{
			throw "tic wasn't called - but elapsed was called";
		}
		return "";
	}
};
