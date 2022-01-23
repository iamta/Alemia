#include "Sun.h"
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>


void Sun::CheckSun(int decreaser)
{
	srand(time(NULL));
	int randomNumber;
	
	ratePower = 8;

	ratePower = ratePower - (decreaser*2);
	
	
	randomNumber = rand() % 1000 + 1;

	

	if (ratePower>2)
	{
		if (randomNumber % ratePower == 0)
		{
			SetSun = 1;
		}
	}
	else
	{
		if (randomNumber % 2 == 0)
		{
			SetSun = 1;
		}
	}
	
	
	
	
	

	if (SetSun == 1)
	{
		randomNumber = rand() % 9 + 1;
		whichSun = randomNumber;
	}

	
}