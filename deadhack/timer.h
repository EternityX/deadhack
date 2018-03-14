#pragma once

class Timer {
private:
	std::chrono::high_resolution_clock::time_point m_start;

public:
	Timer( bool start = false ) {
		if( start )
			reset();
	}

	void reset() {
		m_start = std::chrono::high_resolution_clock::now();
	}

	ulong_t elapsed() {
		auto elapsed = std::chrono::high_resolution_clock::now() - m_start;
		return std::chrono::duration_cast< std::chrono::milliseconds >( elapsed ).count();
	}
};
