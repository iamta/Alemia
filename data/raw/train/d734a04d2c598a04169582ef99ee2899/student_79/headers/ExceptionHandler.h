#pragma once
#include "ConsoleOutput.h"
#include <chrono>
#include <thread>

class ExceptionHandler
{
public:
	ExceptionHandler(const char* exception);
	~ExceptionHandler();
};

