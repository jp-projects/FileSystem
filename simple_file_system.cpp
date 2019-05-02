/*
Name: Juanyta Powell
Email : powell.juanyta@titans.easternflorida.edu
Program purpose: To allow the user to add, delete, rename, filter, and search for files on a simulated file system.

Algorithm : 
1.	Display a menu with options for adding, deleting, renaming, filtering, and searching files.
2.	Display user prompt and read user input
	a.	If user input is not valid, prompt the user to re-enter a menu selection
3.	If user selects option 1 for add
	a.	Display user prompt and read user input
	b.	open and read text file into vector
	c.	search vector for user input
	d.	if found, display message to user that file already exist
	e.	if not found, check file type of user's input
	f.	if file type is a valid type, open the text file, add the file name, close the storage file
	g.	if not a valid type, display error message 
4.	If user selects option 2 for delete
	a.	Display user prompt and read user input
	b.	open and read text file into vector
	c.	search vector for user input
	d.	if not found , display message file does not exist
	e.	if found, get file index number of vector element
	f.	Erase vector element and Update file storage
5.	If user selects option 3 for rename
	a.	Display user prompt and read user input
	b.	open and read text file into vector
	c.	search vector for user input
	d.	if found, prompt user for new file name
	e.	read file name
	f.	check file type of new file name
	g.	if file type is a valid type, open the text file, rename the file name, close the file
	h.	if not a valid type, display error message files does not exist
6.	If user selects option 4 for search
	a.	Display user prompt and read user input
	b.	open and read text file into vector
	c.	search vector for user input
	d.	if found, display message to user that file does exist
	e.	if not found, display message to user that file does not exist 
7.	If user selects option 5 for display type
	a.	open and read text file into vector
	b.  Display user prompt and read user input	
	c.	Check file type and add to vector
	d.	Sort file names in vector
8.	If user selects option 6 for display all
	a.	open and load text file into vector
	b.	Sort file names in vector
9.	If user selects option 7, display menu
10.	If user selects option 9, exit program

*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void displayMenu(int);
void addFile(ofstream&, ifstream&, vector<string>&); 
void deleteFile(ofstream&, ifstream&, vector<string>&); 
void renameFile(ofstream&, ifstream&, vector<string>&);
void searchFile(ifstream&, vector<string>&);
void displayAll(ifstream&, vector<string>&);
void displayType(ifstream&, vector<string>&);
void loadFiles(ifstream&, vector<string>&);
void sortFiles(vector<string>&);
bool search(ifstream&, vector<string>&, string);
bool checkFileType(string);
int  findIndex(vector<string>&, string);

int main()
{
	int option;
	
	displayMenu(option);	
	return 0;
	
}
/*
Function displays menu with selection options and prompts user for input.
Precondition: program has compiled with no errors.
Postcondition: menu is displayed.
*/

void displayMenu(int option)
{
	ofstream outFile;
	ifstream inFile;
	vector<string> fileVector;
	cout << "  Simple File Management System \n\n Please choose an option from the menu or enter 9 to quit. \n";
	cout << " Option 1 - Add File \n";
	cout << " Option 2 - Delete File\n";
	cout << " Option 3 - Rename File \n";
	cout << " Option 4 - Search Files\n";
	cout << " Option 5 - Display Files By Type\n";
	cout << " Option 6 - Display All Files \n";
	cout << " Option 7 - Display Menu \n";
	cout << " Option 8 - Quit \n";
	
	cin >> option;
	while (cin.fail())
	{
		cout << "You haven selected an option that is not available. \n"
				"Please choose an option from the menu or enter 9 to quit. \n";
		cin.clear(); 
		cin.ignore();
		cin >> option;
	}
	while(option != 9)
	{
		switch(option)
		{
			case 1:
				addFile(outFile, inFile, fileVector);
				break;
			case 2:
				deleteFile(outFile, inFile, fileVector);
				break;
			case 3:
				renameFile(outFile, inFile, fileVector);
				break;
			case 4:
				searchFile(inFile, fileVector);
				break;
			case 5:
				displayType(inFile, fileVector);
				break;
			case 6:
				displayAll(inFile, fileVector);
				break;
			case 7:
				displayMenu(option);
				break;
			default:
				cout << "You haven selected an option that is not available. \n";
				break;
		}
		cout << "Please choose an option from the menu or enter 9 to quit. \n";
		cin >> option;
	}
}

/*
Function adds the file name passed to the function as a parameter to the text file. 
Precondition: User has entered option 1 to added a file. 
Postcondition: File name is added to text file. Message the file has been added is displayed to the user.
*/

void addFile(ofstream& outFile, ifstream& inFile, vector<string>& fileVector)
{
	int i = 0;
	string fileName;
	bool found = false;
	bool isFileType = false;
	
	cin.ignore();
	cout << "Enter file name \n";
	getline(cin, fileName);
		
	found = search(inFile, fileVector, fileName);
	
	if(found == 1)
		cout << fileName << " already exists \n";
	else
	{
		isFileType = checkFileType(fileName);
		if(isFileType == 1)
		{
			outFile.open("files.txt", ios::app);
			outFile << fileName << endl;
			cout << fileName << " added. \n";
			outFile.close();
		}
		else
			cout <<"File extension is incorrect \n";
	}
}
/*
Function deletes the file name passed to the function and updates the text file.
Precondition: User has entered option 2 to delete a file.  
Postcondition: File name is deleted. Message the file has been deleted is displayed to the user.
*/
void deleteFile(ofstream& outFile, ifstream& inFile, vector<string>& fileVector) 
{
	bool found = false;
	string files, fileName;
	int fileIndex = 0;
	
	cin.ignore();
	cout <<"Enter file name \n";
	getline(cin, fileName);
	
	found = search(inFile, fileVector, fileName); 
	
	if(found == 0)
	{
		cout << fileName << " does not exists. \n";
	}
	else
	{	
		fileIndex = findIndex(fileVector, fileName); 
		fileVector.erase (fileVector.begin()+fileIndex);
		outFile.open("files.txt");
		for (int i = 0; i < fileVector.size(); i++)
				outFile << fileVector[i] << endl;
		cout << "File deleted \n";
		outFile.close();
	}   	
}
/*
Function renames the file name passed to the function and updates the text file..
Precondition: User has entered option 3 to rename a file.  
Postcondition: File name is renamed. Message the file has been renamed is displayed to the user.
*/
void renameFile(ofstream& outFile, ifstream& inFile, vector<string>& fileVector)
{
	string newFileName, fileName;
	bool found = false;
	int num;
	
	cin.ignore();
	cout << "Enter file name. \n";
	getline(cin, fileName);
	
	found = search(inFile, fileVector, fileName); 
	if(found == 1)
	{
		bool isFileType = false;
		int num = 0, fileIndex = 0;
		
		cout << "Enter new file name. \n";
		getline(cin, newFileName);
		
		isFileType = checkFileType(newFileName); 
		
		if(isFileType == 0)
			cout <<"File extension is incorrect \n";
		else
			num = fileName.length();
		
			
			fileIndex = findIndex(fileVector, fileName);  //find index
			fileVector[fileIndex]= fileName.replace(0,num,newFileName);
			outFile.open("files.txt");
			for (int i = 0; i < fileVector.size(); i++)
			outFile << fileVector[i] << endl;
			outFile.close();
			cout << "File renamed \n";
	}
	else
	{
		cout << fileName << " does not exists. \n";
	}
}
/*
Function searches for a file name entered by the user.
Precondition: User has entered option 4 and a file name. 
Postcondition: Function displays a statement to the user that reads if the file exist or not.
*/
void searchFile(ifstream& inFile, vector<string>& fileVector)
{
	bool found = false;
	string fileName;
	
	cin.ignore();
	cout << "Enter file name. \n";
	getline(cin, fileName);
	found = search(inFile, fileVector, fileName);
	
	if (found == 1)
		cout << fileName << " does exist. \n";
	else
		cout << fileName << " does not exist. \n";
}
/*
Function loads all file names stored in the text file into a vector, sorts the file names into alphabetical order, and displays them to the user.
Precondition: User has entered option 6 to display all files. 
Postcondition: All files are displayed n alphabetical order.
*/
void displayAll(ifstream& inFile, vector<string>& fileVector)
{
	loadFiles(inFile, fileVector);
	sortFiles(fileVector);
	
}
/*
Function loads all file names of the file type passed to the function into a vector, sorts the file names into alphabetical order, and  displays them to the user.
Precondition: User has entered option 5 to display all files of a specific type. 
Postcondition: All file names of the type passed to the function are displayed to the user in alphabetical order.
*/
void displayType(ifstream& inFile, vector<string>& fileVector)
{
	string fileType;
	int num;
	
	vector<string> fileTypeVector;
	loadFiles(inFile, fileVector);
	cin.ignore();
	cout << "Enter file type. \n";
	cin >> fileType;
	for(int i = 0; i < fileVector.size(); i++)
	{
		num = fileVector[i].length()-3;
		if(fileVector[i].substr(num,3) == fileType)
			fileTypeVector.push_back(fileVector[i]);
	}
	
	sortFiles(fileTypeVector);
}
/*
Function reads a text file and loads the file names into a vector.
Precondition: User enters option to add, delete, rename, or search and enters a file name. User enters option to diplay type or display all.
Postcondition: Files are successfully loaded into a vector.
*/
void loadFiles(ifstream& inFile, vector<string>& fileVector)
{
	string files;
	
	if(fileVector.size() > 0)
		fileVector.clear();
		
	inFile.open("files.txt");
	if (!inFile)
	{
		cout << "Text file not found \n";
	}

	while (getline(inFile, files))
	{
		if(files.size() > 0)
			fileVector.push_back(files); 
	}
	inFile.close();	
}
/*
Function sorts files in the vector alphabetically.
Precondition: User enters option to display all files or enters a file type to display all file names of a type. 
Postcondition: Files of the vector are sorted alphabetically.
*/
void sortFiles(vector<string>& fileVector)
{
	if(fileVector.size() > 0)
	{
		int i, j, letter;  
    	for (i = 0; i < fileVector.size()-1; i++) 
   		 { 
        	letter = i; 
        	for (j = i+1; j < fileVector.size() ; j++) 
          		if (fileVector[j] < fileVector[letter]) 
            		letter = j; 
  					
					swap(fileVector[letter], fileVector[i]); 
    	} 
    
    	for(i=0; i < fileVector.size(); i++)
			cout << fileVector[i] << endl;
	}
	else
		cout << "File storage has " << fileVector.size() << " files. \n";
}
/*
Function searches for a file using the file name that is passed to the function as a parameter.
Precondition: User has entered a menu option to add, delete, or rename and has entered a file name. 
Postcondition: Returns true if file name is found or false if the file is not found.
*/
bool search(ifstream& inFile, vector<string>& fileVector, string fileName)
{
	int i;
	string files;
	bool found = false;
	loadFiles(inFile, fileVector);

	i = 0;
	while(i < fileVector.size() && (found == false))
	{
		if(fileVector[i] == fileName)
			found = true;
		else
			i++;
	}
	if(found == 1)
		return true;
	else
		return false;
}
/*
Function determines if the file name passed to the function has a valid file type extension.
Precondition: User has entered a menu option to add or rename a file and has entered a file name. 
Postcondition: Returns true if file type is doc, mp3, or jpg.
*/
bool checkFileType(string fileName)
{
	bool validFileType = false;
	string fileType;
	string fileTypeArray[3] = {"doc", "mp3", "jpg"};
	
	int num = 0;
	num = fileName.length()-3;

	fileType = fileName.substr(num,3);

	for(int i = 0; i < 3; i++)
	{
		if(fileType == fileTypeArray[i])
			validFileType = true; 
	}
	return validFileType;
}
/*
Function finds the index of the file name that is passed to the function.
Precondition: User has entered a menu option to delete, or rename a file and has entered a file name. 
Postcondition: Returns the index of the file name.
*/
int findIndex(vector<string>& fileVector, string fileName)
{
	for (int i = 0; i < fileVector.size() ; i++)
	{
		if(fileVector[i] == fileName)
			return i;
	}
}
