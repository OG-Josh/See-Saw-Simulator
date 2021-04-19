/*
* Copyright (C) Josh Y. - All Rights Reserved
* Unauthorized copying of this file, via any medium is strictly prohibited
* Proprietary and confidential
* Written by Josh Y. <joyang112@gmail.com>, June 2017
*/
//Libraries:
//================================
#include "head.h"
#include "source.cpp"

using namespace std;

//Declare global variables and functions
Semaphore* s;

LONG cMax = 1; // maximum amount of threads (Basically semaphore available!)
int alive_threads = 2; // amount of threads

float FredHeight;
float WilmaHeight;
bool FLAG = false;

//Documentations:
//================================

DWORD WINAPI FredSee(LPVOID lpParameter) {

	s->WaitForSemaphore(INFINITE); // check whether we can start new thread
	cout << "================================" << endl;
	cout << "Started Fred's thread: \n"; // starting
	cout << "================================" << endl;

	int num = 0;
	for (int i = 0; i < 10; i++) {
		
		cout << "Fred: " << FredHeight << endl;
		cout << "Wilma: " << WilmaHeight << endl;

		if ((FLAG == false && FredHeight < 7) || (FLAG == true && FredHeight == 1))
		{
			if (FLAG == true)
			{
				FLAG = false;
			}
			FredHeight += 1;
			WilmaHeight -= 1;
		}
		else if ((FLAG == true && FredHeight > 1) || (FLAG == false && FredHeight == 7))
		{
			if (FLAG == false)
			{
				cout << "--------------------------------" << endl;
				cout << "Fred is FALLING . . . " << endl;
				cout << "--------------------------------" << endl;
				FLAG = true;
			}

			FredHeight -= 1.5;
			WilmaHeight += 1.5;
		}
		

		Sleep(1000);

	}
	//cout << "Fred is tired! \n";

	s->LeaveSemaphore(); // leaving semaphore

	alive_threads--; // 1 thread is dead, reduce the amount of alive threads

	return(0);

}

DWORD WINAPI WilmaSaw(LPVOID lpParameter) {

	s->WaitForSemaphore(INFINITE);
	cout << "================================" << endl;
	cout << "Switched to Wilma's thread: \n";
	cout << "================================" << endl;

	for (int i = 0; i < 10; i++) {

		cout << "Fred: " << FredHeight << endl;
		cout << "Wilma: " << WilmaHeight << endl;

		if ((FLAG == false && WilmaHeight < 7) || (FLAG == true && WilmaHeight == 1))
		{
			if (FLAG == true)
			{
				cout << "--------------------------------" << endl;
				cout << "Wilma is FALLING . . . " << endl;
				cout << "--------------------------------" << endl;
				FLAG = false;
			}
			WilmaHeight += 1.5;
			FredHeight -= 1.5;
		}
		else if ((FLAG == true && WilmaHeight > 1) || (FLAG == false && WilmaHeight == 7))
		{
			
			if (FLAG == false)
			{
				FLAG = true;
			}
			WilmaHeight -= 1;
			FredHeight += 1;
		}

		Sleep(1000);

	}
	//cout << "Wilma is tired! \n";

	s->LeaveSemaphore();

	alive_threads--;

	return(0);

}

int main(int argc, char* argv[])
{
	std::cout << "Fred & Wilma See-Saw Simulation: ";
	std::cout << "By Joshua Yang for CPSC 380" << std::endl;

	std::cout << "Simulation started!" << std::endl;

	cout << "================================" << endl;

	//Data declaration
	FredHeight = 1.0;
	WilmaHeight = 7.0;

	s = new Semaphore(cMax); // creating semaphore

	// starting threads
	CreateThread(NULL, 0, FredSee, NULL, 0, NULL);

	CreateThread(NULL, 0, WilmaSaw, NULL, 0, NULL);
	
	//=============================

	while (alive_threads != 0) {} // check whether all threads died
	s -> ~Semaphore(); // destroying semaphore 
	/*Thread joins main thread

	FredSee.join();
	WilmaSaw.join();

	
	*/ //=============================

	//Finish Simulation
	std::cout << "Simulation Completed!" << std::endl;

	//=============================

	//Return data
	return 0;
	
	//=============================
}


//References:
//system("pause");

//Algorithm Setup			|			Corresponding C++ Statements
//Run 10 time as our condition
//Sleep(1s) to print every sec 
//Synchronize 2 thread while 1 active
//simulator completed = join threads
//time 0 = PerA @ low end(1f)
//time 0 = PerB @ high end(7ft)
//
//
//
//