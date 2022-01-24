#include "Log.h"


Log* Log::instance = NULL;

Log& Log::getInstance() {
	if (!Log::instance) {
		Log::instance = new Log();
	}
	return *Log::instance;
}

void Log::destroyInstance() {
	if (Log::instance) {
		delete Log::instance;
		Log::instance = NULL;
	}
}

void Log::logEvent(string eveniment) {
	ofstream fout("log.txt", ios::app);
	fout << eveniment << endl;
}