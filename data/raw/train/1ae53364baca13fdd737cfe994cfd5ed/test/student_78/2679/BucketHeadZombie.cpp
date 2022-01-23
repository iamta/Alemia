#include "BucketHeadZombie.h"

BucketHeadZombie::~BucketHeadZombie()
{
	UserInterface::ConsoleOutput::getInstance(x, y) << "   ";

}

void BucketHeadZombie::draw()
{
	UserInterface::ConsoleOutput::getInstance(x, y) << "]~[";
}
