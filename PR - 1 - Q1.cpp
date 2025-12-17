#include <iostream>
using namespace std;

class Time
{
public:
    int hours;
    int minutes;
    int seconds;

    void fromSeconds(int totalSeconds)
    {
        hours = totalSeconds / 3600;
        totalSeconds = totalSeconds % 3600;
        minutes = totalSeconds / 60;
        seconds = totalSeconds % 60;
    }

    void toSeconds(int &totalSeconds)
    {
        totalSeconds = hours * 3600 + minutes * 60 + seconds;
    }

    void inputHMS()
    {
        cout << "Enter Hours: ";
        cin >> hours;
        cout << "Enter Minutes: ";
        cin >> minutes;
        cout << "Enter Seconds: ";
        cin >> seconds;
    }

    void displayHMS()
    {
        cout << "Time: ";
        if(hours < 10) cout << "0";
        cout << hours << ":";
        if(minutes < 10) cout << "0";
        cout << minutes << ":";
        if(seconds < 10) cout << "0";
        cout << seconds << endl;
    }
};

int main()
{
    Time t;
    int choice;

    cout << "Choose conversion:\n";
    cout << "1. Seconds to HH:MM:SS\n";
    cout << "2. HH:MM:SS to Seconds\n";
    cin >> choice;

    if(choice == 1)
    {
        int totalSeconds;
        cout << "Enter total seconds: ";
        cin >> totalSeconds;
        t.fromSeconds(totalSeconds);
        t.displayHMS();
    }
    else if(choice == 2)
    {
        t.inputHMS();
        int totalSeconds;
        t.toSeconds(totalSeconds);
        cout << "Total Seconds: " << totalSeconds << endl;
    }
    else
    {
        cout << "Invalid choice!" << endl;
    }
}

/*
	output:
	Choose conversion:
	1. Seconds to HH:MM:SS
	2. HH:MM:SS to Seconds
	1
	Enter total seconds: 4200
	Time: 01:10:00
	
	Choose conversion:
	1. Seconds to HH:MM:SS
	2. HH:MM:SS to Seconds
	2
	Enter Hours: 03
	Enter Minutes: 56
	Enter Seconds: 15
	Total Seconds: 14175
*/