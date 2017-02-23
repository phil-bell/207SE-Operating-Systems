#include <iostream> //imports the iostream library so it can print to the screen
#include <string> //imports the string library so i can use strings 

using namespace std; //creates the namespace
 
int main() //creates the main method
{
	string name = "Philip Bell"; //sets the string name to my name
	int i = 0; //sets the int i to 0
	int iterator = 2; //sets the iterator to 2
	int nameSize = name.size(); //gets the length of the string name
	for (i=0;i<nameSize;i += incrementor) //loops through until i is not less then the length of the string, instrements at teh rate set by the incrementor
	{
		if (name[i+1] != '\0') //if it is not the end of the string it does the following
		{
			cout << name[i]; //outputs the current value from the string
			cout << name[i+1] << endl; //ouputs the next value in the string and makes a new line
		}
		else //if the end of the string has been reached it does the following
		{
			cout << name[i] << endl; //outputs the current value in the string and makes a new line
		}
	}
}
