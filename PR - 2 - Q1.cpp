#include <iostream>
#include <string>
using namespace std;

class Train
{
private:
    int trainNumber;
    string trainName;
    string source;
    string destination;
    string trainTime;
    static int trainCount;

public:
    Train()
    {
        trainNumber = 0;
        trainName = "";
        source = "";
        destination = "";
        trainTime = "";
        trainCount++;
    }

    Train(int number, string name, string src, string dest, string time)
    {
        trainNumber = number;
        trainName = name;
        source = src;
        destination = dest;
        trainTime = time;
        trainCount++;
    }

    ~Train()
    {
        trainCount--;
    }

    int getTrainNumber() const { return trainNumber; }

    void inputTrainDetails()
    {
        cout << "Enter Train Number: ";
        cin >> trainNumber;
        cin.ignore();

        cout << "Enter Train Name: ";
        getline(cin, trainName);

        cout << "Enter Source: ";
        getline(cin, source);

        cout << "Enter Destination: ";
        getline(cin, destination);

        cout << "Enter Train Time: ";
        getline(cin, trainTime);
    }

    void displayTrainDetails() const
    {
        cout << "Train Number: " << trainNumber << endl;
        cout << "Train Name: " << trainName << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Train Time: " << trainTime << endl;
    }

    static int getTrainCount() { return trainCount; }
};

int Train::trainCount = 0;

class RailwaySystem
{
private:
    Train trains[100];
    int totalTrains;

public:
    RailwaySystem()
    {
        totalTrains = 0;
    }

    void addTrain()
    {
        if (totalTrains < 100)
        {
            cout << "\nAdding new train record:\n";
            trains[totalTrains].inputTrainDetails();
            totalTrains++;
            cout << "Train record added successfully!\n";
        }
        else
        {
            cout << "Cannot add more trains. Storage full!\n";
        }
    }

    void displayAllTrains() const
    {
        if (totalTrains == 0)
        {
            cout << "No train records available!\n";
            return;
        }

        for (int i = 0; i < totalTrains; i++)
        {
            cout << "\nTrain " << i + 1 << " details:\n";
            trains[i].displayTrainDetails();
        }
    }

    void searchTrainByNumber(int number) const
    {
        for (int i = 0; i < totalTrains; i++)
        {
            if (trains[i].getTrainNumber() == number)
            {
                cout << "\nTrain Found:\n";
                trains[i].displayTrainDetails();
                return;
            }
        }
        cout << "Train with number " << number << " not found!\n";
    }
};

int main()
{
    RailwaySystem system;

    cout << "Enter at least 3 initial train records:\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "\nTrain " << i + 1 << ":\n";
        system.addTrain();
    }

    int choice;
    do
    {
        cout << "\n--- Railway Reservation System Menu ---\n";
        cout << "1. Add New Train Record\n";
        cout << "2. Display All Train Records\n";
        cout << "3. Search Train by Number\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            system.addTrain();
            break;
        case 2:
            system.displayAllTrains();
            break;
        case 3:
        {
            int number;
            cout << "Enter Train Number to search: ";
            cin >> number;
            system.searchTrainByNumber(number);
            break;
        }
        case 4:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}
