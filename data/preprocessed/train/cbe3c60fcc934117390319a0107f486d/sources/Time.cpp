#include "Time.h"
#include <iostream>

using namespace std;

void timer::Ttimer()
{
	unsigned long seconds = 10;
	timer t;
	t.start();
	cout << "timer started . . ." << endl;
	//while (true) {
	//	if (t.elapsedTime() >= seconds) {
	//		break;
	//	}
	//	else {
	//		// do other things
	//	}
	//}
	cout << seconds << " seconds elapsed" << endl;
}
