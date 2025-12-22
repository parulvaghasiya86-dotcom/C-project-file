#include <iostream>
using namespace std;

class Vehicle {
private:
    int vehicleID;
    char manufacturer[50];
    char model[50];
    int year;
public:
    static int totalVehicles;
    Vehicle(int id=0,const char manu[]="",const char mod[]="",int yr=0){
        vehicleID=id;
        int i=0; while(manu[i]!='\0'){ manufacturer[i]=manu[i]; i++; } manufacturer[i]='\0';
        i=0; while(mod[i]!='\0'){ model[i]=mod[i]; i++; } model[i]='\0';
        year=yr;
        totalVehicles++;
    }
    ~Vehicle(){ totalVehicles--; }
    int getVehicleID(){ return vehicleID; }
    virtual void display(){
        cout<<"ID: "<<vehicleID<<", Manufacturer: "<<manufacturer<<", Model: "<<model<<", Year: "<<year<<endl;
    }
};

int Vehicle::totalVehicles=0;

class Car : public Vehicle {
private:
    char fuelType[20];
public:
    Car(int id=0,const char manu[]="",const char mod[]="",int yr=0,const char fuel[]="") : Vehicle(id,manu,mod,yr){
        int i=0; while(fuel[i]!='\0'){ fuelType[i]=fuel[i]; i++; } fuelType[i]='\0';
    }
    void display() override {
        Vehicle::display();
        cout<<"Fuel: "<<fuelType<<endl;
    }
};

class ElectricCar : public Car {
private:
    int batteryCapacity;
public:
    ElectricCar(int id=0,const char manu[]="",const char mod[]="",int yr=0,int battery=0) : Car(id,manu,mod,yr,"Electric"){
        batteryCapacity=battery;
    }
    void display() override {
        Car::display();
        cout<<"Battery: "<<batteryCapacity<<" kWh"<<endl;
    }
};

class Aircraft {
private:
    int flightRange;
public:
    Aircraft(int range=0){ flightRange=range; }
    void displayAircraft(){ cout<<"Flight Range: "<<flightRange<<" km"<<endl; }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar(int id=0,const char manu[]="",const char mod[]="",int yr=0,const char fuel[]="",int range=0) : Car(id,manu,mod,yr,fuel), Aircraft(range){}
    void display(){
        Car::display();
        Aircraft::displayAircraft();
    }
};

class SportsCar : public ElectricCar {
private:
    int topSpeed;
public:
    SportsCar(int id=0,const char manu[]="",const char mod[]="",int yr=0,int battery=0,int speed=0) : ElectricCar(id,manu,mod,yr,battery){
        topSpeed=speed;
    }
    void display() override {
        ElectricCar::display();
        cout<<"Top Speed: "<<topSpeed<<" km/h"<<endl;
    }
};

class Sedan : public Car {
public:
    Sedan(int id=0,const char manu[]="",const char mod[]="",int yr=0,const char fuel[]="") : Car(id,manu,mod,yr,fuel){}
};

class SUV : public Car {
public:
    SUV(int id=0,const char manu[]="",const char mod[]="",int yr=0,const char fuel[]="") : Car(id,manu,mod,yr,fuel){}
};

class VehicleRegistry {
private:
    Vehicle* vehicles[100];
    int count;
public:
    VehicleRegistry(){ count=0; }
    void addVehicle(Vehicle* v){ if(count<100) vehicles[count++]=v; }
    void displayAll(){ for(int i=0;i<count;i++){ vehicles[i]->display(); cout<<"--------"<<endl; } }
    void searchByID(int id){ for(int i=0;i<count;i++){ if(vehicles[i]->getVehicleID()==id){ vehicles[i]->display(); return; } } cout<<"Not Found"<<endl; }
};

int main(){
    VehicleRegistry registry;
    int choice;
    do{
        cout<<"\n1.Add 2.Show 3.Search 4.Exit Choice: ";
        cin>>choice;
        if(choice==1){
            int type,id,year,battery,speed,range;
            char manu[50],mod[50],fuel[20];
            cout<<"Type:1.Car 2.ECar 3.FlyCar 4.Sports 5.Sedan 6.SUV: "; cin>>type;
            cout<<"ID Manufacturer Model Year (Example: 101 Toyota Fortuner 2022): "; cin>>id>>manu>>mod>>year;
            if(type==1){ cout<<"Fuel (Example: Petrol): "; cin>>fuel; registry.addVehicle(new Car(id,manu,mod,year,fuel)); }
            else if(type==2){ cout<<"Battery (Example: 75): "; cin>>battery; registry.addVehicle(new ElectricCar(id,manu,mod,year,battery)); }
            else if(type==3){ cout<<"Fuel Range (Example: Petrol 500): "; cin>>fuel>>range; registry.addVehicle(new FlyingCar(id,manu,mod,year,fuel,range)); }
            else if(type==4){ cout<<"Battery Speed (Example: 85 240): "; cin>>battery>>speed; registry.addVehicle(new SportsCar(id,manu,mod,year,battery,speed)); }
            else if(type==5){ cout<<"Fuel (Example: Petrol): "; cin>>fuel; registry.addVehicle(new Sedan(id,manu,mod,year,fuel)); }
            else if(type==6){ cout<<"Fuel (Example: Diesel): "; cin>>fuel; registry.addVehicle(new SUV(id,manu,mod,year,fuel)); }
        }
        else if(choice==2) registry.displayAll();
        else if(choice==3){ int searchID; cout<<"ID: "; cin>>searchID; registry.searchByID(searchID); }
    }while(choice!=4);
    cout<<"Total Vehicles: "<<Vehicle::totalVehicles<<endl;
}

/*
	output:	
	1.Add 2.Show 3.Search 4.Exit Choice: 1
	Type:1.Car 2.ECar 3.FlyCar 4.Sports 5.Sedan 6.SUV: 5
	ID Manufacturer Model Year (Example: 101 Toyota Fortuner 2022): 7856 BMW M3 2019
	Fuel (Example: Petrol): diesel
	
	1.Add 2.Show 3.Search 4.Exit Choice: 3
	ID: 7856
	ID: 7856, Manufacturer: BMW, Model: M3, Year: 2019
	Fuel: diesel
	
	1.Add 2.Show 3.Search 4.Exit Choice: 2
	ID: 7856, Manufacturer: BMW, Model: M3, Year: 2019
	Fuel: diesel
	--------

	1.Add 2.Show 3.Search 4.Exit Choice: 4
	Total Vehicles: 1
*/