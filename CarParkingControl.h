#include <iostream>
#include <fstream> //used for file handling purpose
#include <iomanip> //used for output formatting
#include <conio.h> //used for screen clearing purpose
#include "CarClass.h"
#include<chrono>
#include<string>


const char *filename = "MeroParkingFinal1.txt"; //For File system project
string DataBaseUsername="iucrazz";
string DataBasePass = "iucrazz123";
time_t entryT, exitT;

using namespace std;

void ParkingLotControl::removeCar()
{
    isLotEmpty=true;
    //entry_time.reset();
    //exit_time.reset();
    //entry_date.reset();
    //exit_date.reset();
    carId="None";
    entryStatus=false;
    exitStatus=false;
}
void ParkingLotControl::get_entry()
{
    int mode;
    Pcharge = 2; //Min parking charge
    isLotEmpty=false;
    
    setColor(pink,lightblue);
    animateTxt("Taking the entry records...\n");
    setColor(green,black);
    cout << "Enter the car owner name: ";
    setColor(white,black);
    cin>>name;
up:
	
	setColor(pink,lightblue);
	animateTxt("Choose Mode:::");
    setColor(yellow,black);
    cout << "\n1--->System Date&Time Mode\n2--->Manual Date&Time Mode\n\n";
    cout << "Choose Date & Time Mode::\t";
    setColor(white,black);
    cin >> mode;
    if (mode == 1)
        isSystem = true;
    else if (mode == 2)
        isSystem = false;
    else
    {
        
    	setColor(yellow,black);
		cout << "Invalid option selected!!! Try again...\n";
        goto up;
    }
    if (isSystem)
    {
        entryT = time(0); //add 20700 to compensate the time loss in case needed
        char *entryTime = ctime(&entryT);
        Entry = static_cast<string>(entryTime);
        usingSystem = true;
    }
    else
    {
    	
    	setColor(green,black);
        cout << "Enter the current date (Year/mon/day): " << endl;
        entry_date.set_date();
        setColor(green,black);
        cout << "Enter the current time: ";
        entry_time.set_time();
        usingSystem = false;
    }
    
    setColor(white,pink);
    cout << "Entry records successfully noted..." << endl;
}


void ParkingLotControl::get_exit()
{
    if (usingSystem == 1)
    {
        exitT = time(0); //add 20700 to compensate the time loss in case needed
        char *exitTime = ctime(&exitT);
        Exit = static_cast<string>(exitTime);
    }
    else
    {
    	
    	setColor(pink,lightblue);
    	animateTxt("Taking exit date and time...\n");
        
        enterDate:
        	setColor(green,black);
        	cout << "Enter the current date (Year/mon/day): " << endl;
        	exit_date.set_date();
        float netDate = checkDate();
        if (netDate < 0)
        {
        	setColor(red,black);
        	cout<<"Invalid Date provided!!! Exit Date cannot be before Entry Date i.e must be (Exit_date > Entry_date)..."<<endl;
        	goto enterDate;
		}
		
        setColor(green,black);
        cout << "Enter the current time: "<<endl;
        exit_time.set_time();
    }
    
    setColor(white,pink);
    cout << "Exit records successfully noted..." << endl;
}


void ParkingLotControl::putcarId(string Id)
{
    carId = Id;
}

double ParkingLotControl::checkTime()
{
    return difftime(exitT, entryT) / 3600; //returns time diff in hours
}


int ParkingLotControl::checkDate()
{
    return exit_date - entry_date; // returns date in hours
}

float ParkingLotControl::CheckTime()
{
    return exit_time - entry_time; // returns time in hours
}

void ParkingLotControl::calCharge()
{
    if (usingSystem == 1)
        goto system;
    else
    {
        float netDate;
        netDate = checkDate();
        if (netDate < 0)
        {
        	
    		setColor(yellow,black);
            cout << "Invalid date entered...." << endl;
            return;
        }

        else if (netDate == 0) //same day
        {
            if (CheckTime() < 0)
            {
            	
    			setColor(yellow,black);
                cout << "Invalid time entered..." << endl;
                return;
            }
            if (CheckTime() >= 3)
            {
                Pcharge = Pcharge + (CheckTime() - 3) * .5;
                return;
            }
        }
        else if (netDate == 24 && CheckTime() < 24)
        {
            Pcharge += (CheckTime() - 3) * .5;
            return;
        }
        else if (netDate > 24)
        {
            Pcharge = (netDate / 24) * 8;
            return;
        }
    }

system:
    double netTime;
    netTime = checkTime();
    if (netTime > 24)
    {
        Pcharge = (netTime / 24) * 8;
        return;
    }

    else if (netTime >= 3)
    {
        Pcharge += (netTime - 3) * .5;
        return;
    }
}

void ParkingLotControl::showTotalTime()
{
    if (usingSystem == 1)
    {
        DateTime converted;
        converted = difftime(exitT, entryT);
        if (exitStatus == 1)
        {
        	setColor(green,black);
        	converted.show();
		}
            
        else
        {
        	
    		setColor(yellow,black);
         	cout << "\tExit records not taken yet..." << endl;	
		}
        return;
    }
    else
    {
        float netDate = checkDate();
        if (netDate < 0 || exitStatus == false)
        {
        	
    		setColor(yellow,black);
            cout << "\tExit records not taken yet..." << endl;
            return;
        }
        else if (netDate == 0) //Car exit on the same day
        {
            Time t;
            t = CheckTime() * 3600; // converting basic type to class type
            t.displaynetTime();
            return;
        }
        else if (netDate == 24 && CheckTime() < 24)
        {
            Time t;
            t = CheckTime() * 3600; // converting basic type to class type
            t.displaynetTime();
            return;
        }
        else
        {
            Date d;
            d = checkDate(); // converting basic type to class type
            d.displaynetDate();
            return;
        }
    }
}

void ParkingLotControl::showTotalCarParked()
{   
	setColor(red,lightblue);
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    
    setColor(white,pink);
    animateTxt("\n\tEntry records and more info:\t");
    
    setColor(green,black);
    cout << "\n\tCar Owner: " << name << endl;
    cout << "\n\tCarID: " << carId << endl;

    if (usingSystem == 1)
    {
    	
    	setColor(white,pink);
    	animateTxt("\n\tEntry date & time:\t \n");
        
    	setColor(green,black);
        cout <<endl<< Entry << endl;
        
    	setColor(white,pink);
    	animateTxt("\n\tExit date & time:\t \n");
        if (exitStatus == 1)
        {
        	setColor(green,black);
        	cout <<endl<< Exit << endl;
		}
		else{
        	setColor(yellow,black);
        	cout<<"Exit records not taken so far!!!"<<endl;
		}
        setColor(white,pink);
        animateTxt("\n\tTotal time of staying==\t");
        showTotalTime();
    }
    else
    {
    	
    	setColor(white,pink);
    	animateTxt("\n\tEntry date & time:\t \n");
        entry_date.displayDate();
        entry_time.displayTime();
        
    	setColor(white,pink);
    	animateTxt("\n\tExit date & time:\t \n");
        if (exitStatus == 1)
        {
        	setColor(green,black);
            exit_date.displayDate();
            exit_time.displayTime();
        }
        else{
        	setColor(yellow,black);
        	cout<<"Exit records not taken so far!!!"<<endl;
		}
        
    	setColor(white,pink);
    	animateTxt("\n\tTotal time of staying==\t");
        showTotalTime();
    }
    setColor(red,lightblue);
    cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void ParkingLotControl::showCharge()
{
    if (entryStatus == 1 && exitStatus == 1)
    {
        calCharge();
        setColor(black,yellow);
        animateTxt("Exit reports and more info:\t\n");
        setColor(green,black);
        
        cout << "Car Owner: " << name << endl;
        cout << "CarID: " << carId << endl;
        setColor(black,yellow);
        animateTxt("Entry date & time:\t \n");
        if (isSystem == 1)
        {
        	setColor(green,black);
        	cout << Entry << endl;
		}
            
        else
        {
            entry_date.displayDate();
            entry_time.displayTime();
        }
        setColor(black,yellow);
        animateTxt("Exit date & time:\t\n");
        if (isSystem == 1)
        {
        	setColor(green,black);
        	cout << Exit << endl;
		}
            
        else
        {
            exit_date.displayDate();
            exit_time.displayTime();
        }
        setColor(black,yellow);
        animateTxt("\nTotal staying time: \t\n");
        showTotalTime();
        setColor(black,yellow);
        cout<<"\nTotal Parking charge: ";
        setColor(green,black);
        cout<<"  $"<<Pcharge<<" only."<<endl;
        setColor(pink,lightblue);
        cout << "\nHave a safe journey ahead...Happy TO Serve....!!!" << endl;
    }
    else
    {
    	setColor(yellow,black);
        
    	cout << "Sir please departure the car first..." << endl;
	}
        
    if (total_car_parked < 0)
    {
    	setColor(yellow,black);
        
    	cout << "There's no any car parked in our Lot...." << endl;
	}
        
}

void ParkingLotControl::operator++()
{
    ++total_car_parked;
}

void ParkingLotControl::operator--()
{
    --total_car_parked;
}

int ParkingLotControl::getTotalCar()
{
    return total_car_parked;
}
string ParkingLotControl::getCarId()
{
    return carId;
}

int ParkingLotControl::total_car_parked=0;

void delete_record()
{
    int found = 0;
    string carNo;
    setColor(green,black);
    
    cout << "\n\tEnter the car Id you want to get departured :   ";
    setColor(white,black);
    cin >> carNo;
    ifstream inFile;
    inFile.open(filename, ios::binary | ios::in);
    ofstream outFile;
    outFile.open("temp1.dat", ios::out | ios::binary);
    outFile.seekp(0, ios::beg);
    inFile.seekg(0, ios::beg);
    while (inFile.read((char *)&c, sizeof(c)))
    {
        if (c.getCarId() == carNo)
        {
            found = 1;
            break;
        }
    }
    if (found == 1)
    {
        if (c.getCarId() == carNo && c.exitStatus == false)
        {
        	setColor(yellow,black);
        	
            cout << "This car is not Departured from our DataBase yet...!!" << endl;
            return;
        }
        else
        {
            inFile.seekg(0, ios::beg);
            outFile.seekp(0, ios::beg);
            while (inFile.read((char *)&c, sizeof(c)))
            {
                if (c.getCarId() != carNo)
                    outFile.write((char *)&c, sizeof(c));
                if (c.getCarId() == carNo && c.exitStatus == 1)
                {
                    c.showCharge();
                    setColor(black,yellow);
        			
                    cout << "\n\t Car with Id " << carNo << " is successfully departured from our DateBase...\n\n";
                }
            }
            inFile.close();
            outFile.close();
            remove(filename);
            rename("temp1.dat", filename);
        }
    }
    else
    {
    	setColor(yellow,black);
        
    	cout << "Car with this ID doesn't exist in our DataBase!!!\n\n";
	}
        
}


void LoginPanel()
{
	
	setColor(red,black);
    cout << "________________________________________________________________________" << endl<<endl;
    setColor(white,blue);
    animateTxt("\t\t***WEL-COME To IUCRAZZ Car Parking Lot***   \t\t");
    setColor(yellow,black);
	cout<<"\n\t\t   ";
	setColor(black,green);
	cout<<"Administered By: IUCRazz ShaNidhi";
	setColor(red,black);
	cout<<"\t\t\t";
    setColor(red,black);
    cout << "\n________________________________________________________________________" << endl
         << endl;
	setColor(yellow,black);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    setColor(green,black);
    
    cout << "1->Login to Your ParkingLot DataBase..." << endl;
    cout << "2->Change Your Password..." << endl;
    cout << "3->Exit From the Program" << endl;
    
    setColor(yellow,black);
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    setColor(red,black);
    cout << "________________________________________________________________________" << endl;
    
}


void menu()
{
	
	setColor(yellow,black);
    cout << "===================================================================="<<endl<<endl;
    setColor(white,blue);
	animateTxt("\t\t***CAR PARKING DATA BASE***\t\t");
	setColor(yellow,black);
	cout<<"\n\t\t";
	setColor(black,green);
	cout<<"Administered By: IUCRazz ShaNidhi";
	setColor(red,black);
	cout<<"\t\t";
    setColor(yellow,black);
    cout <<endl<<endl<< "===================================================================="<<endl;
    setColor(pink,black);
    cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    setColor(green,black);
    
    cout << "\n\n\t\t1-->Park the Car" << endl;
    cout << "\t\t2-->Take Departure" << endl;
    cout << "\t\t3-->Print the Bill" << endl;
    cout << "\t\t4-->Display All Parked Cars" << endl;
    cout << "\t\t5-->Log Out" << endl<< endl;
    setColor(pink,black);
    cout <<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    setColor(green,black);
    cout << "\n\t\tEnter your choice here==\t";
}


bool checkLogin(string username,string pass)
 {
      if(DataBaseUsername==username && DataBasePass==pass)
           return true;
      else
          return false;    
  }

void changePass(string pass)
{
    DataBasePass = pass;
}

void changeUsername(string user)
{
    DataBaseUsername=user;
}  

 
string InputPass()
{
	char ch1;
	string password;
	while (ch1 != 13)
	{      	
      	ch1 = _getch();
			
      	if(ch1 == '\b' && password.length())
		{
      		cout<<'\b'<<' '<<'\b';
      		password.erase( password.end() -1 );
		}
		
		else if(ch1 != 13){
			setColor(white,black);
			cout << '*';
			password.push_back(ch1);
		}      			
	}	
	
	return password;
}
