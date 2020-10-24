#include <iostream> 
#include <iomanip>
#include <string>
#include <fstream>

class DateTime {

private:
	int day, month, year, hour, min, sec;

public:
	DateTime(int d, int m, int y, int h, int mi, int s) { day = d; month = m; year = y; hour = h ; min = mi; sec = s; };
	DateTime(std::string input, std::string del1, std::string del2, std::string del3);
	void Print();
	DateTime& operator++();
	DateTime operator++(int);
	DateTime& operator--();
	DateTime operator--(int);
	DateTime operator+(int add);
	DateTime operator-(int sub);
	bool operator==(const DateTime& dt);
	bool operator!=(const DateTime& dt);
	bool operator>(const DateTime& dt);
	bool operator<(const DateTime& dt);
	int operator[](int index);
	friend std::ostream& operator <<(std::ostream& output, const DateTime& dt);
	int operator-(const DateTime& dt);

	int GetDay() { return day; };
	int GetMOnth() { return month; };
	int GetYear() { return year; };
	int GetHour() { return hour; };
	int GetMinute() { return min; };
	int GetSecond() { return sec; };
};

//##############################################################################################################################################


int main()
{

	DateTime dat1(31, 12, 2020, 23, 59, 59);			//konstruktor 1
	std::cout << "1. datum a cas: ";
	dat1.Print();										//funkcia print
	
	DateTime dat2("1.1.2021 0:0:0","."," ",":");		//konstruktor 2
	std::cout << "2. datum a cas: ";
	dat2.Print(); 

	if (dat1 == dat2) {									//operator ==
		std::cout << "Datum a cas je zhodny. \n";
	}
	else {
		std::cout << "Datum a cas nie je zhodny. \n";
	}

	if (dat1 > dat2) {									//operator >
		std::cout << "Datum 1 je neskorsi ako Datum 2. \n";
	}
	else {
		std::cout << "Datum 1 je skorsi ako Datum 2. \n";
	}



	std::cout << "Ich rozdiel v sekundach je: " << dat1 - dat2 << std::endl;		//operator -

	std::cout << "3.datum  (1. datum a cas + 65 sekund): ";
	DateTime dat3 = dat1 + 65;							//operator +
	dat3.Print();										

	std::cout << "4.datum  (3. datum - 156 sekund): ";
	DateTime dat4 = dat3 - 156;							//operator -
	std::cout << dat4;									//operator <<

	std::cout << "dat4++: ";											
	std::cout << dat4++;								//operatory ++
	
	std::cout << "++dat4: ";
	std::cout << ++dat4;

	std::cout << "dat4--: ";
	std::cout << dat4--;								//operatory --

	std::cout << "--dat4: ";
	std::cout << --dat4;

	return 0;
}

//##############################################################################################################################################


DateTime::DateTime(std::string input, std::string del1, std::string del2, std::string del3)
{
	int pos = 0;
	int list[3] = { 0,0,0 };
	int n = 0;
	std::string temp;
	std::string date;
	std::string time;
	
	if ((pos = input.find(del2)) == std::string::npos) {			//najde, kde sa oddeluje datum a cas
		std::cout << "Nespravny format vstupu. Ukoncujem program. \n";
		exit(1);
	}		

	date = input.substr(0, pos);		//priradi datum az po prvu medzeru do datumu
	input.erase(0, pos + del2.length());		//odstrani medzeru medzi nimi
	time = input;			//priradi zvysok zapisu ako cas
	pos = 0;
		
	while ((pos = date.find(del1)) != std::string::npos) {		//priradenie datumu
		temp = date.substr(0, pos);
		list[n] = std::stoi(temp);
		date.erase(0, pos + del1.length());
		n++;
	}
	day = list[0];
	month = list[1];
	year = std::stoi(date);
	n = 0;
	pos = 0;

	while ((pos = time.find(del3)) != std::string::npos) {		//priradenie casu
		temp = time.substr(0, pos);
		list[n] = std::stoi(temp);
		time.erase(0, pos + del3.length());
		n++;
	}
	hour = list[0];
	min = list[1];
	sec = std::stoi(time);
}

void DateTime::Print()
{
	std::cout << std::setfill('0') << std::setw(2) << day << "." << std::setfill('0') << std::setw(2) << month << "." << year << " " << std::setfill('0') << std::setw(2) << hour << ":" << std::setfill('0') << std::setw(2) << min << ":" << std::setfill('0') << std::setw(2) << sec << std::endl;
}

DateTime& DateTime::operator++()
{
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	sec++;
	if (sec == 60) {
		sec = 0;
		min++;

		if (min == 60) {
			min = 0;
			hour++;

			if (hour == 24) {
				hour = 0;
				day++;

				if (day == daysInMonth[month - 1]+1) {
					day = 1;
					month++;

					if (month == 13) {
						month = 1;
						year++;

					}
				}
			}
		}
	}
	return *this;
}

DateTime DateTime::operator++(int)
{
	int d = day, m = month, y = year, h = hour, mi = min, s = sec;
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	
	sec++;
	if (sec == 60) {
		sec = 0;
		min++;

		if (min == 60) {
			min = 0;
			hour++;

			if (hour == 24) {
				hour = 0;
				day++;

				if (day == daysInMonth[month - 1]+1) {
					day = 1;
					month++;

					if (month == 13) {
						month = 1;
						year++;

					}
				}
			}
		}
	}
	
	return DateTime(d, m, y, h, mi, s);
}

DateTime& DateTime::operator--()
{
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	sec--;
	if (sec == -1) {
		sec = 59;
		min--;

		if (min == -1) {
			min = 59;
			hour--;

			if (hour == -1) {
				hour = 23;
				day--;

				if (day == 0) {
					month--;

					if (month == 0) {
						month = 12;
						year--;
					}
					day = daysInMonth[month - 1];

					
				}
			}
		}
	}


	return *this;

}

DateTime DateTime::operator--(int)
{
	int d = day, m = month, y = year, h = hour, mi = min, s = sec;
	int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	if (sec == -1) {
		sec = 59;
		min--;

		if (min == -1) {
			min = 59;
			hour--;

			if (hour == -1) {
				hour = 23;
				day--;

				if (day == 0) {
					month--;

					if (month == 0) {
						month = 12;
						year--;
					}
					day = daysInMonth[month - 1];


				}
			}
		}
	}
	return DateTime(d, m, y, h, mi, s);

}

DateTime DateTime::operator+(int add)
{
	int DaysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int delitel = 0;

	sec += add;
	if (sec >= 60) {
		min += sec / 60;
		sec %= 60;
		
	}
	if (min >= 60) {
		hour += min / 60;
		min %= 60;
		
	}
	if (hour >= 24) {
		day += hour / 24;
		hour %= 24;
		
	}
	if (day > DaysInMonth[month-1]) {
		
		while (day / DaysInMonth[month - 1] != 0) {
			day -= DaysInMonth[month - 1];
			month ++;

			if (month > 12) {
				year ++;
				month = 1;
				
			}

		}

	}
	

	DateTime out(day, month, year,hour, min, sec);
	return out;
}

DateTime DateTime::operator-(int sub)
{
	int DaysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	sec -= sub;

	if (sec < 0) {
		min += sec / 60 - 1;
		sec = 60 + (sec % 60);

		if (min < 0) {
			hour += min / 60 - 1;
			min = 60 + (min % 60);

			if (hour < 0) {
				day += hour / 24 - 1;

				hour = 24 + (hour % 24);

				if (day < 1) {
					do {
						if (month == 1) {
							day += DaysInMonth[11];
							month = 12;
							year--;
						}
						else {
							day += DaysInMonth[month - 2];
							month--;
						}
					} while (day / DaysInMonth[month - 1] != 0 && day == 0);




				}
			}
		}
	}
	
	DateTime out(day, month, year, hour, min, sec);
	return out;
}

bool DateTime::operator==(const DateTime& dt)
{
	if (year == dt.year && month == dt.month && day == dt.day && hour == dt.hour && min == dt.min && sec == dt.sec) {
		return true;
	}
	else {
		return false;
	}
}

bool DateTime::operator!=(const DateTime& dt)
{
	if (year == dt.year && month == dt.month && day == dt.day && hour == dt.hour && min == dt.min && sec == dt.sec) {
		return false;
	}
	else {
		return true;
	}
}

bool DateTime::operator>(const DateTime& dt)
{

	if (year > dt.year) {
		return true;
	}
	else if (year < dt.year) {
		return false;
	}
	else {
		if (month > dt.month) {
			return true;
		}
		else if (month < dt.month) {
			return false;
		}
		else {
			if (day > dt.day) {
				return true;
			}
			else if (day < dt.day) {
				return false;
			}
			else {
				if (hour > dt.hour) {
					return true;
				}
				else if (hour < dt.hour) {
					return false;
				}
				else {
					if (min > dt.min) {
						return true;
					}
					else if (min < dt.min) {
						return false;
					}
					else {
						if (sec > dt.sec) {
							return true;
						}
						else if (sec < dt.sec) {
							return false;
						}
					}
				}
			}
		}
	}

}

bool DateTime::operator<(const DateTime& dt)
{
	if (year > dt.year) {
		return false;
	}
	else if (year < dt.year) {
		return true;
	}
	else {
		if (month > dt.month) {
			return false;
		}
		else if (month < dt.month) {
			return true;
		}
		else {
			if (day > dt.day) {
				return false;
			}
			else if (day < dt.day) {
				return true;
			}
			else {
				if (hour > dt.hour) {
					return false;
				}
				else if (hour < dt.hour) {
					return true;
				}
				else {
					if (min > dt.min) {
						return false;
					}
					else if (min < dt.min) {
						return true;
					}
					else {
						if (sec > dt.sec) {
							return false;
						}
						else if (sec < dt.sec) {
							return true;
						}
					}
				}
			}
		}
	}
}

int DateTime::operator[](int index)
{
	if (index == 0) return sec;
	else if (index == 1) return min;
	else if (index == 2) return hour;
	else if (index == 3) return day;
	else if (index == 4) return month;
	else if (index == 5) return year;
	else {
		std::cout << "Chybny index \n";
		//return NULL;		//????
	}
}

int DateTime::operator-(const DateTime& dt)
{
	int DaysInMonth[12] = { 1,-2,1,0,1,0,1,1,0,1,0,1 };		//rozdiel od zakladu 30 (pocet dni v mesiaci)
	int AdditionalDays = 0;
	int diff[6] = { 0,0,0,0,0,0 };
	int diff2[6] = { 0,0,0,0,0,0 };
	int i = month;
	if (year > dt.year) i++;		//neviem ani preco, ale bez tohto to nejde
	int navyse = 0;

	if (year != dt.year) {		//ak je rozdielny rok, treba pridat 12 mesiacov do pocitania navyse
		navyse=12;
	}


	while (i != (dt.month + navyse)){				//prechadza cez mesiace a pridava dni navyse
		AdditionalDays += DaysInMonth[(i - 1)%12];

		if (year > dt.year) {
			i--;
			if (i == 0) i = 24;
		}
		else {
			i++;
			if (i == 25) i = 1;
		}
		
	} ;

	diff[0] = (year - dt.year);
	diff[1] = diff[0] * 12;		//premeni roky na mesiace
	diff2[0] = (year - dt.year);

	diff[1] += (month - dt.month);		//odpocita skutocne mesiace
	diff[2] = diff[1] * 30 - AdditionalDays;		//premeni mesiace na dni... vynasobi zakladnymi 30 a prida dni navyse
	diff2[1] += (month - dt.month);
	//----------------------------------------------------

	diff[2] += (day - dt.day);		//odpocita skutocne dni
	diff[3] = diff[2] * 24;		//premeni dni na hodiny
	diff2[2] += (day - dt.day);

	diff[3] += (hour - dt.hour);		//odpocita skutocne hodiny
	diff[4] = diff[3] * 60;		//premeni hodiny na minuty
	diff2[3] += (hour - dt.hour);

	diff[4] += (min - dt.min);		//odpocita skutocne minuty
	diff[5] = diff[4] * 60;		//premeni minuty na sekundy
	diff2[4] += (min - dt.min);

	diff[5] += (sec - dt.sec);		//odpocita skutocne sekundy
	diff2[5] += (sec - dt.sec);

	
	return diff[5];
} 

std::ostream& operator<<(std::ostream& output, const DateTime& dt)
{
	output << std::setfill('0') << std::setw(2) << dt.day << "." << std::setfill('0') << std::setw(2) << dt.month << "." << dt.year  << " " << std::setfill('0') << std::setw(2) << dt.hour << ":" << std::setfill('0') << std::setw(2) << dt.min << ":" << std::setfill('0') << std::setw(2) << dt.sec << std::endl;
	return output;
}
