// Time24-12-RoutineInSourceObj.cpp : Defines the entry point for the console application.
//
/*
conversion from time24 to time 12 using operator in time24

*/

#include "stdafx.h"
#include <string>
#include <iostream>

class Time12
{
	bool pm;			//true = pm, false = am
	int hours;			// 1 to 12
	int minutes;		// 0 to 59
public:
	Time12(): pm(true), hours(0), minutes(0) // no Arg constructor
	{}
	Time12(bool amPm, int hours_, int minutes_): pm(amPm), hours(hours_), minutes(minutes_) // 3 ARG constructor
	{}
	void display() const					// format : 11:59 p.m.
	{
		std::cout << hours << ':';
		if (minutes < 10)
			std::cout << '0';				// add extra zero range 1 - 9
		std::cout << minutes << ' ';
		std::string am_pm = pm ? "p.m." : "a.m.";
		std::cout << am_pm;
	}

};
class Time24
{
	int hours;			// 0 to 23
	int minutes;		// 0 to 59
	int seconds;		// 0 to 59
public:
	Time24() : hours(0), minutes(0), seconds(0) // no argument constructor
	{}
	Time24(int hours_, int minutes_, int seconds_): hours(hours_), minutes(minutes_), seconds(seconds_) // 3 ARG constructor
	{}
	void display() const	// format 23:15:01
	{
		if (hours < 10)
			std::cout << '0';
		std::cout << hours << ':';
		if (minutes < 10)
			std::cout << '0';
		std::cout << minutes << ':';
		if (seconds < 10)
			std::cout << '0';
		std::cout << seconds;
	}
	operator Time12() const; //conversion operator
};



Time24::operator Time12() const // conversion operator
{
	int hours24 = hours;
	bool pm = hours < 12 ? false : true; // find am/pm 
															
	int roundMinutes = seconds < 30 ? minutes : minutes + 1; // round seconds
	if (roundMinutes == 60)		// carry minutes?
	{
		roundMinutes = 0;
		++hours24;
		if (hours24 == 12 || hours24 == 24)		// carry hours?
			pm = (pm == true) ? false : true; // toggle am/pm
	}
	int hours12 = (hours24 < 13) ? hours24 : hours24 - 12;
	if (hours12 == 0)			// 00 is 12 a.m.
	{
		hours12 = 12;
		pm = false;
	}
	return Time12(pm, hours12, roundMinutes);
}

int main()
{
	int hours, minutes, seconds;

	while (true) // get 24 hours time from User
	{
		std::cout << "Enter time in 24hours format: \n";
		std::cout << "  Hours (0 to 23): ";
		std::cin >> hours;
		if (hours > 23) // quit if hours > 23
			return(1);
		std::cout << "  Minutes: ";
		std::cin >> minutes;
		if (minutes > 59)
			return(1);
		std::cout << "  Seconds: ";
		std::cin >> seconds;
		if (seconds > 59)
			return(1);

		Time24 t24(hours, minutes, seconds);		// make a time24
		std::cout << "You entered: " ; // display the time24
		t24.display(); 

		Time12 t12 = t24;	//converts time24 to time12 

		std::cout << "\n 12-hour time: "; // display equivalent time12
		t12.display();
		std::cout << std::endl; 
	}


	system("pause");
	return 0;
}