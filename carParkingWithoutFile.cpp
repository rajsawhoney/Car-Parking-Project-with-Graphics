#include "CarParkingControl.h"
#include<conio.h>
#define parkingSize 10

int main()
{
	  fullscreen();
	  fontSize(30,30);
      ParkingLotControl p[parkingSize];
      int carNo;
      int displayCount=0;
      int recentlydeleted;
      char option, option1;
	  bool isLoginned = false;
	  bool recentDeletion=false;
	  bool firstlog = true;    
	  
	       
      loginPanel2:	
      while(1)
      {
	          
	   LoginPanel();
	   if (firstlog)
	   {
			setColor(yellow, black);
	  		
			cout << "NOTE: Your default \nUsername: 'iucrazz'\nPassword: 'iucrazz123' \nPlease change it for strong security reason..." << endl;
			setColor(red,black);
			cout << "________________________________________________________________________" << endl;
		}
		setColor(green,black);
    	cout << "\n\t\tEnter your choice here==\t";
		setColor(white,black);
		cin >> option1;
		switch (option1)
		{
		case '1':
		{
		enterAgain3:
			string userNm;
			string password;
			setColor(green, black);
	  		
			cout<<"\nPlease enter the usename==\t";
			setColor(white,black);
			cin>>userNm;
			setColor(green,black);
			cout << "\nPlease enter your login password==\t";
			password = InputPass();
						
			if (checkLogin(userNm,password))
			{								
				setColor(red,lightblue);
				cout << "\n\n\n\tSuccessfully loginned.....\t\n\n" << endl;
				isLoginned = true;
				goto DataBase2;
			}
			else
			{
				
				
				setColor(red,black);
				cout << "\n\tUsename or password not matched!!!! Please try again..." << endl;				
				isLoginned = false;
				goto enterAgain3;
			}
			break;
		}
		case '2':
		{
		enterAgain4:
			string tempPass;					
			setColor(green,black);
			cout << "\nSir Please enter your current password==\t";
			tempPass = InputPass();
			
			if (DataBasePass==tempPass)
			{				
			changePass:
				setColor(green,black);
				cout << "\n\nEnter your new and a bit stronger password===\t";				
				char ch3;
				string newPass, confirmPass;
				newPass = InputPass();
				
				setColor(green,black);
				cout<<"\n\nPlease enter ur Password again===\t";
				confirmPass = InputPass();
				
				if(newPass == confirmPass)
				{
					changePass(newPass); //Changin the Password
					char choice;
					string tempUser;				
					setColor(white,blue);
					cout << "\n\t\tPassword successfully changed..." << endl;
					firstlog = false;
				
					setColor(black,yellow);
					cout<<"Do you wish to change the username as well????[Y/N]";
					setColor(white,black);
					cin>>choice;
					if(choice=='Y' || choice=='y')
					{
					
						setColor(green,black);
				    	cout<<"Enter your new username...:\t";
				    	setColor(white,black);
				    	cin>>tempUser;
				    	changeUsername(tempUser);
				    
						setColor(white,blue);
				    	cout<<"Username successfully changed..!!\n";
					}
					
				}
									
				else
					{
						setColor(red,black);
						cout<<"\n\nPassword not matching. Please try again!!";
						goto changePass;
					}	
				
				
			}
			else
				{
					char cancel;
					setColor(yellow,black);					
					cout << "\n\t\tWrong password!!!  Please Try again... or enter 'x' to cancel..." << endl;
					setColor(white,black);
					cin>>cancel;
					if(cancel == 'x' || cancel == 'X')
						break;
					else	
						goto enterAgain3;
				}
			break;
		}
		case '3':
			char confirm1[2];
			
			setColor(black,yellow);
			cout << "Do you  really wanna exit (Y/N)??    ";
			setColor(white,black);
			cin >> confirm1;
			if (strcmp(confirm1, "Y") == 0 || strcmp(confirm1, "y") == 0)
			{
				
				setColor(white,pink);
				cout << "Thanks for visiting us...\n";
				setColor(yellow,black);
				goto last;
			}
			else
				break;
		default:
			
			setColor(yellow,black);
			cout << "Invalid option selected...\n";
			break;
		}
	}
DataBase2:	
	while (isLoginned)
	{	    	
		menu();
		setColor(white,black);
		cin >> option;
		switch (option)
		{
		case '1':
		{
		    if(carNo==parkingSize)
		    {
		    	
				setColor(yellow,black);
		        cout<<"Sorry!! The parking lot is completely FULL...Plz Try after sometime\n";
		        break;
		    }
			string Id;
			bool ifexist=false;
			
			setColor(green,black);
			cout<<"\n\nEnter the carId:\t";
			setColor(white,black);
    		cin>>Id;
    		if(carNo>0)
    		{			
			for(int j=0;j<carNo;j++)
			{
			    if (p[j].getCarId()== Id)
			     {
		   	     ifexist=true;
			    	break;
			     }			    
			}
    		}
    		else
    		    goto enterData;
			
			if(ifexist)
			{
				
				setColor(yellow,black);
				cout<<"Car with the ID "<<Id<<" already exist in our DataBase!!!"<<endl;
				break;
			}
				else
				{
				enterData:
				if(recentDeletion)
				{
				    p[recentlydeleted].putcarId(Id);
			        p[recentlydeleted].entryStatus = true;
	    		    ++p[recentlydeleted]; //increases the car num by 1
			    	p[recentlydeleted].get_entry();	
				    carNo++;  //Increasing  the index for more car entry
				    recentDeletion=false;
				}
			else
			{
				p[carNo].putcarId(Id);
			    p[carNo].entryStatus = true;
	    		++p[carNo]; //increases the car num by 1
				p[carNo].get_entry();	
				carNo++;  //Increasing  the index for more car entry
				}
				}
			break;
		}
		case '2': //Car Id is matched and is ready to get departured
		{
			string id;
			int recordNo;
			int recordFound=0;
			
			setColor(green,black);
			cout << "\n\nEnter the CarId: ";
			setColor(white,black);
			cin >> id;
			for(int i=0;i<carNo;i++)
			{
			    if (p[i].getCarId()== id)
			    {
				    recordFound=1;
				    recordNo=i;
			        break;			        
			   }
			}
			if(recordFound==1)
			{		   				
				    p[recordNo].get_exit();
					p[recordNo].exitStatus = true;
			}
		   else		   
			  {
			  	setColor(yellow,black);
			  	
			  	cout << "Sorry sir!!! There is no car with this ID in our Parking Lot!!!" << endl;
			  }
			 break;
		}
		case '3':  //Delete the particular car from the dataBase and display the charges for the departured one
 		{
			string id;
			int recordNo;
			int recordFound=0;
			
			setColor(green,black);
			cout << "\n\nEnter the CarId: ";
			setColor(white,black);
			cin >> id;
			for(int i=0;i<carNo;i++)
			{
			    if (p[i].getCarId()== id)
			    {
				    recordFound=1;
				    recordNo=i;
			        break;			        
			    }
			}			
			if(recordFound==1 && p[recordNo].exitStatus==true)
			{
			    p[recordNo].showCharge();
			    --p[recordNo];	//decreases the car num by 1
			    for(int i=0;i<carNo;i++)
			    {
			        if(i==recordNo)
			        {
			            p[recordNo].removeCar();
			            recentlydeleted=recordNo;
			            recentDeletion=true;
			        }
			       /*
			         if(i==recordNo)
			        {
			            for(int j=i;j<carNo-1;j++)			            
			                p[j]=p[j+1];  //stores all other car except that one 
			            break;    
			        }
			        */
			    }
			}
			else if(recordFound==1 && p[recordNo].exitStatus==false)
				{
					
					setColor(yellow,black);
					cout<<"This car with id "<<id<<" is still to take exit..."<<endl;
				}
			    
			    
			    else if(recordFound==0)
			    {
			    	
			    	setColor(yellow,black);
			    	cout<<"Car with Id "<<id<<" is not found in our DataBase!!"<<endl;
				}
			     
			break;
	 	}
		case '4':
		 {		
		 		setColor(white,blue);
		 		cout<<"\n\t=== View the Records in the Parking Database ===\t\n";
		 		carNo=ParkingLotControl::getTotalCar();
	    		setColor(black,yellow);
				cout<<"\n\t\tTotal car Parked in the lot==";
				setColor(green,black);
				cout<<"\t"<<carNo<<" Cars"<<endl;
				int i=0;  //since used outside the for loop
				for(i=0;i<parkingSize;i++)
				{
				    if(p[i].isLotEmpty)
				    {
				    	
				    	setColor(white,green);
				    	cout<<"\n\t  The Lot no. "<<i+1<<" is empty!!!"<<endl;
					}
				        
				   else if(!p[i].isLotEmpty)
				   {
				   	
				   	setColor(pink,black);
				   	cout << "\n\tThe Car position in the Parking Lot : " << i+1 << endl;
   				   	p[i].showTotalCarParked();				   
				   }
		    	}
		    					
				if(i==0)
				{
					
				    setColor(yellow,black);
				    cout<<"\n\tNo any records found in our DataBase "<<endl;
				}
				    
 			break;
		}

		case '5':
		{
			char confirm[1];
			
			setColor(yellow,black);
			cout << "Do you really wanna sign out (Y/N)?? ";
			setColor(white,black);
			cin >> confirm;
			if (strcmp(confirm, "Y") == 0 || strcmp(confirm, "y") == 0)
			{
				
				setColor(white,pink);
				cout << "Thanks for visiting us...\n";
				goto loginPanel2;
			}
			else
				break;
		}
		default:
			
			setColor(yellow,black);
			cout << "Invalid option selected...\n";
			break;
		}
	}
	last:
    return 0;
}
