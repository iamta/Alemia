#include "ExceptionHandler.h"



ExceptionHandler::ExceptionHandler(const char* exception)
{
	UserInterface::ConsoleOutput conOut = UserInterface::ConsoleOutput::getInstance();
	conOut(41, 120) << exception;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	conOut(41, 120) << "                           ";
}


ExceptionHandler::~ExceptionHandler()
{
}
