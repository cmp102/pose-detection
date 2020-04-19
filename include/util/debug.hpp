#pragma once

#define debug(msg)

#define DEBUG_FILE_LINE std::cerr << "Debug: " << __FILE__  << ":" << __LINE__ << "\n";

#ifdef DEBUG_LOGS
#include <iostream>
#define debug(msg) \
	DEBUG_FILE_LINE \
	std::cerr \
	<< "Function: " << __FUNCTION__ << "\n" \
	<< "Msg: "<< msg << "\n\n";
#endif

#define debug_timer_start(id)
#define debug_timer_finish(id)

#ifdef DEBUG_TIMERS
#include <iostream>
#include <chrono>
#include <ctime>

#define debug_timer_start(id) \
   auto START_TIMER ## id = std::chrono::system_clock::now();\
	std::time_t START_TIME ## id = std::chrono::system_clock::to_time_t(START_TIMER ## id);\
	DEBUG_FILE_LINE \
	std::cerr \
	<< "Function: " << __FUNCTION__ << "\n" \
	<< "Timer " << #id  << " started at: "<< std::ctime(&START_TIME ## id) << "\n\n";

#define debug_timer_finish(id) \
   auto FINISH_TIMER ## id = std::chrono::system_clock::now();\
	std::time_t FINISH_TIME ## id = std::chrono::system_clock::to_time_t(START_TIMER ## id);\
   std::chrono::duration<double> ELAPSED_SECONDS ## id = START_TIMER ## id-FINISH_TIMER ## id;\
	DEBUG_FILE_LINE \
 	std::cerr \
	<< "Function: " << __FUNCTION__ << "\n" \
	<< "Timer " << #id " finished at: "<< std::ctime(&FINISH_TIME ## id) << "\n" \
	<< "Elapsed time: " << ELAPSED_SECONDS ## id.count() << "s\n\n";
#endif
