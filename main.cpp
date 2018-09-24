
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

void main_Interface(); //Displays the main menu
void search_ID(int id); //Searches the "instructor.txt" file for instructor info
void search_Dept(string dept); //Searches the "department.txt" file for department info
string search_dept(string dept); //Searches the "department.txt" file for and returns building for department that is being searched
void search_instructor(string dept); //Searches "instructor.txt" file and returns all proffesors in department given
void add_instructor(int id, string name, string dept);
bool existing_dept(string dept);
bool valid_ID(int ID);

int choice = 0; //conditional variable to check if Main Menu loop should still be running
char cont; //conditional variable to determine if the choice chosen should be repeated

int main()
{
	int ID; //holds instructor id
	string deptName; //holds deprtment name
	string instructorName = "";

	do
	{
		main_Interface(); //displays main menu
		switch (choice)
		{
		case 1: //The case for option 1 in the main menu
		
			cont = 'Y';

		while(cont == 'Y')
		{
			cout << "ENTER INSTRUCTOR ID: ";
			cin >> ID; //takes instructor id to be searched as input
			search_ID(ID); //calls function and prints out instructor info
			cout << "\n";

			cout << "\nWOULD YOU LIKE TO SEARCH ANOTHER INSTRUCTOR? (Y/N)";
			cin >> cont;
		}
			cout << "\n TO RETURN TO MENU PRESS (0): ";
			cin >> choice;

			break;

		case 2: //The case for option 2 in the main menu

			cont = 'Y';

			while (cont == 'Y')
			{
				cout << "ENTER DEPARTMENT NAME: ";
				cin >> deptName; //takes department name to be searched as input
				search_Dept(deptName); // calls function and displays department info
				cout << "\n";

				cout << "\nWOULD YOU LIKE TO SEARCH ANOTHER DEPARTMENT? (Y/N)";
				cin >> cont;
			}

			
			cout << "\n TO RETURN TO MENU PRESS (0): ";
			cin >> choice;

			break;

		case 3:

			cont = 'Y';

			while (cont == 'Y')
			{
				cout << "ENTER THE INSTRUCTOR ID: ";
				cin >> ID;
				cout << "ENTER THE INSTRUCTOR NAME: ";
				cin.ignore();
				getline(cin, instructorName, '\n');
				cout << "ENTER THE AFFILIATED DEPARTMENT NAME: ";
				cin >> deptName;
				add_instructor(ID, instructorName, deptName);

				cout << "\nWOULD YOU LIKE TO ADD ANOTHER INSTRUCTOR? (Y/N)";
				cin >> cont;
			}

			cout << "\n\n TO RETURN TO MENU PRESS (0): ";
			cin >> choice;

			break;
		case 4:
			choice = 1;

			break;
		}
	} while (choice == 0);
	
	return 0;
}

void main_Interface() //main menu
{

	cout << "===================================================================" << endl;
	cout << "\t  WELCOME TO MANHATTAN COLLEGE DATABASE \t" << endl;
	cout << "===================================================================" << endl << "\n\n";

	cout << "MENU" << endl;
	cout << "1. ENTER INSTRUCTOR ID FOR MORE INFO" << endl;
	cout << "\n2. ENTER DEPARTMENT ID FOR MORE INFO" << endl;
	cout << "\n3. ENTER NEW INSTRUCTOR TO DATABASE" << endl;
	cout << "\n4. EXIT" << endl << endl;

	cin >> choice;
}

void search_ID(int id)
{
	int ID; 
	string name;
	string dept_name;
	fstream datafile_I; //declares variable with type fstream to open file
	datafile_I.open("instructor.txt", ios::in); // opens file to be read
	
	if (datafile_I)//conditional statement to check if file was succesfully opened 
	{
		while (datafile_I >> ID) //checks to see if the file has finished reading
		{
			getline(datafile_I, name, ',');//ignores comma
			getline(datafile_I, name, ',');//reads instructor name into variable "name"
			getline(datafile_I, dept_name);//reads instructor department into variable "dept_name" 

			if (ID == id)//conditional statemnt to check if the intended ID has been found
			{
				//if yes then it prints the instructor info and terminates the search
				cout << "INSTRUCTOR ID: " << ID << endl;
				cout << "INSTRUCTOR NAME: " << name << endl;
				cout << "INSTRUCTOR DEPARTMENT: " << dept_name << endl;
				cout << "DEPARTMENT LOCATION: " << search_dept(dept_name) << endl;
				break;
			}
		}
		if (ID != id) //if not error message displayed
			cout << "THE ID DOES NOT APPEAR IN THE DATABASE.";
	}
	else //returns error message if file not opened 
	{
		cout << "FILE COULD NOT BE OPENED" << endl;
	}
	datafile_I.close(); //closes file
}

void search_Dept(string dept)
{
	int budget;
	string building;
	string dept_name;
	fstream datafile_D; //declares variable with type fstream to open file
	datafile_D.open("department.txt", ios::in); // opens file to be read


	if (datafile_D)
	{
		while (getline(datafile_D, dept_name, ','))
		{
			getline(datafile_D, building, ','); //reads department building into variable "building"
			datafile_D >> budget; //reads department budget into variable "budget"

			if (dept_name == dept) //prints department info if department searched for is found
			{
				cout << "DEPARTMENT NAME: " << dept_name << endl;
				cout << "DEPARTMENT LOCATION: " << building << endl;
				cout << "DEPARTMENT BUDGET: " << budget << endl;
				cout << "LIST OF INSTRUCTORS IN THIS DEPARTMENT" << endl;
				search_instructor(dept_name);
				break;
			}

			else //if not found it displays error message
				getline(datafile_D, dept_name);
		}

		if (dept_name != dept) 
		{
			cout << "THE DEPARTMENT NAME DOES NOT APPEAR IN THE DATABASE.";
		}
	}
	
	else
	{
		cout << "FILE COULD NOT BE OPENED" << endl;
	}
	
	datafile_D.close();
}

string search_dept(string dept) //searches department file and returns the building for department name searched
{
	string dept_name;
	string building;
	int budget;
	fstream datafileD;
	datafileD.open("department.txt", ios::in);

	if (datafileD)
	{
		while (getline(datafileD, dept_name, ','))
		{
			getline(datafileD, building, ',');
			datafileD >> budget;

			if (dept_name == dept)
			{
				break;
			}

			else
				getline(datafileD, dept_name); //if department not found then it moves to next line
		}
	}
	else
	{
		return ("FILE COULD NOT BE OPENED"); //if file not opened then it returns error message

	}

	datafileD.close();

	return building; //returns building of department searched for
}

void search_instructor(string dept) //searches for all instructor in a given department
{
	int id;
	string name;
	string dept_name;
	fstream datafileI;

	datafileI.open("instructor.txt", ios::in);
	if (datafileI)
	{
		while (datafileI >> id) //reads the entire file and prints every instructor with matching department name
		{
			getline(datafileI, name, ',');
			getline(datafileI, name, ',');
			getline(datafileI, dept_name);

			if (dept_name == dept) //if department found the print instructor name
			{
				cout << name << endl;
			}
		}
	}

	else
		cout << "FILE COULD NOT BE OPENED" << endl;

	datafileI.close();
}

//for add instructor function

bool existing_dept(string dept)
{
	int budget;
	string building;
	string dept_name;
	fstream datafile_D;
	datafile_D.open("department.txt", ios::in);

	if (datafile_D)
	{
		while (getline(datafile_D, dept_name, ','))
		{
			getline(datafile_D, building, ',');
			datafile_D >> budget;

			if (dept_name == dept)	//if dept name entered is a match
			{
				return true;
				break;
			}

			else
				getline(datafile_D, dept_name);
		}

		if (dept_name != dept)	//if dept entered does not exist
		{
			return false;
		}
	}
	else
	{
		cout << "FILE COULD NOT BE OPENED" << endl;
		
	}
	datafile_D.close();
}

bool valid_ID(int ID)
{
	int id;
	string name;
	string dept_name;
	fstream datafile_I;
	datafile_I.open("instructor.txt", ios::in);
	if (datafile_I)
	{
		while (datafile_I >> id)
		{
			getline(datafile_I, name, ',');
			getline(datafile_I, name, ',');
			getline(datafile_I, dept_name);

			if (id == ID)	//if id entered already exists
			{
				return false;
			}
		}

		if (id != ID)
		{
			return true;
		}
	}
	else
	{
		cout << "FILE COULD NOT BE OPENED" << endl;
	}
	datafile_I.close();
}

void add_instructor(int id, string name, string dept)
{
	if (valid_ID(id) == true && existing_dept(dept) == true)
	{
		fstream outputFile;	//only need to open file if we are able to add to it
		outputFile.open("instructor.txt", fstream::app);

		outputFile << endl << id << ",";
		outputFile << name << ",";
		outputFile << dept;
		cout << "Your file has been updated";
		outputFile.close();
	}
	else if (valid_ID(id) == false && existing_dept(dept) == false)
	{
		cout << "Instructor id duplicated AND department does not exist" << endl;
	}
	else if (valid_ID(id) == false)
	{
		cout << "Instructor id already exists in the file" << endl;
	}
	else if (existing_dept(dept) == false)
	{
		cout << "The department does not exist and hence the instructor record cannot be added to the database" << endl;
	}
	else
	{
		cout << "error";
	}
}
