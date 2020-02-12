#include<bits/stdc++.h>
#include <iostream>
#include<cstring>
#include "Addgraphics.h"

bool isNumber(string);


using namespace std;
class TypeError
{
    char msg[100];

  public:
    TypeError(char s[])
    {
        strcpy(msg, s);
    }
    void showError()
    {
    	setColor(yellow,black);
        cout << msg << " Please enter valid type" << endl;
//        exit(1);
    }
};

class Negative
{
    char msg[100];

  public:
    Negative(char s[])
    {
        strcpy(msg, s);
    }
    void showError()
    {
        setColor(yellow,black);
		cout << msg << " Please enter +ve datas!" << endl;
        return;
    }
};

class Invalid
{
    char msg[100];

  public:
    Invalid(char s[])
    {
        strcpy(msg, s);
    }
    void showError()
    {
    	setColor(yellow,black);
        cout << msg << " Please enter valid data!" << endl;
         return;
    }
};

class Date
{
  private:
    int year, month, day;
    string syear,smonth,sday;

  public:
    Date()
    {
    }
    Date(int netTime)
    {
        year = netTime / (24 * 360);
        month = (int(netTime) % (24 * 360)) / (30 * 24);
        day = ((int(netTime) % (24 * 360)) % (30 * 24)) / 24;
    }
    void set_date()
    {
    again:
        try
        {
        	setColor(black,yellow);
            cout << "In YYYY:MM:DD Format Only Please!\n";
            setColor(white,black);
			cin.clear();           
            getline(cin,syear,':');
            getline(cin,smonth,':');
            getline(cin,sday);
            
			if (!isNumber(syear) || !isNumber(smonth) || !isNumber(sday))
                throw TypeError("Type Error.");
            
            year=atoi(syear.c_str());
            month=atoi(smonth.c_str());
            day=atoi(sday.c_str());
                                         

            if (year < 0 || month < 0 || day < 0)
                throw Negative("Negative date entered!!");
            if (year < 1000 || year > 2020 || month > 12 || day > 32)
                throw Invalid("Invalid date entered!!");
            
        }
        catch (TypeError t)
        {
            t.showError();
            goto again;
        }
        catch (Negative n)
        {
            n.showError();
            goto again;
        }
        catch (Invalid t)
        {
            t.showError();
            goto again;
        }
    }
    int operator-(Date d2)
    {
        Date d;
        int total_days;
        total_days = (year * 360 + month * 30 + day) - (d2.year * 360 + d2.month * 30 + d2.day);
        d.year = total_days / 360;
        d.month = (total_days % 360) / 30;
        d.day = (total_days % 360) % 30;
        return d.year * 360 * 24 + d.month * 30 * 24 + d.day * 24;
    }

    void displayDate()
    {
        char m = ' ', d = ' ';
        if (month < 10)
            m = '0';
        if (day < 10)
            d = '0';
        setColor(green,black);
        cout << "\n\tDate: " << year << " / " << m << month << " / " << d << day << endl;
    }

    void displaynetDate()
    {
    	setColor(green,black);
        cout<<"\t" << year << " Years " << month << " Months " << day << " Days" << endl;
    }
};

class Time
{
  private:
    int hour, min, sec;    
	string hr_s, min_s, sec_s;  
    string format;

  public:
    Time()
    {
    }
    Time(float netTime)
    {
        hour = netTime / 3600;
        min = (int(netTime) % 3600) / 60;
        sec = (int(netTime) % 3600) % 60;
    }

    void set_time()
    {
    again:
        try
        {    
        	setColor(black,yellow);
        	cin.clear();           
            cout << "\nIn HH:MM:SS & 12 Hours Format Only Please!\n";
            setColor(white,black);
            getline(cin, hr_s, ':');
			getline(cin, min_s, ':');
			getline(cin, sec_s);
			           
            if (!isNumber(hr_s) || !isNumber(min_s) || !isNumber(sec_s))
                throw TypeError("Type Error.");
			
			hour=atoi(hr_s.c_str());
			min=atoi(min_s.c_str());
			sec=atoi(sec_s.c_str());
            
        tmformat:
            setColor(green,black);
            cout << "Enter the Time format AM/PM: ";
            if (hour < 0 || min < 0 || sec < 0)
                throw Negative("Negative time entered!!");
            if (hour > 12 || min > 59 || sec > 59)
                throw Invalid("Invalid time entered!!");            

			setColor(white,black);
            cin >> format;
            if(format == "pm" || format == "PM" || format == "am" || format == "AM")
            {}
			
            	
            else
            	goto tmformat;
            transform(format.begin(), format.end(), format.begin(), ::toupper);
        }
        catch (TypeError t)
        {
            t.showError();
            goto again;
        }
        catch (Negative n)
        {
            n.showError();
            goto again;
        }
        catch (Invalid t)
        {
            t.showError();
            goto again;
        }
    }

    float operator-(Time t2)
    {
        Time t;
        int total_sec;
        total_sec = ((12 + hour) * 3600 + min * 60 + sec) - (t2.hour * 3600 + t2.min * 60 + t2.sec);
        t.hour = total_sec / 3600;
        t.min = (total_sec % 3600) / 60;
        t.sec = (total_sec % 3600) % 60;
        if (t2.hour == 12 && t2.format == format)
            return 12 + t.hour + t.min / 60.0 + t.sec / 3600.0;
        else if (t2.hour > hour && format == t2.format)
            return 12 + t.hour + t.min / 60.0 + t.sec / 3600.0;
        else
            return t.hour + t.min / 60.0 + t.sec / 3600.0;
    }

    void displayTime()
    {
        char flag[2];
        char h = ' ', m = ' ', s = ' ';
        if (format == "PM")
            strcpy(flag, "PM");
        else
            strcpy(flag, "AM");
        if (hour < 10)
            h = '0';
        if (min < 10)
            m = '0';
        if (sec < 10)
            s = '0';
        setColor(green,black);
        cout << "\n\tTime: " << h << hour << ":" << m << min << ":" << s << sec << " " << flag << endl;
    }

    void displaynetTime()
    {
    	setColor(green,black);
        cout<<"\t" << hour << " Hours " << min << " Minutes " << sec << " Seconds" << endl;
    }
};

bool isNumber(string s) 
{ 
	for (int i = 0; i < s.length(); i++) 
		if (isdigit(s[i]) == false) 
			return false; 
	return true; 
}
