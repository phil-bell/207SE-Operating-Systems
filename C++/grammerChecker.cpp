//This C++ code is used to take an input string and put words in an array 
#include <iostream> 
#include <string> 
#include <sstream> 
using namespace std;
int main() 
{ 
	//set up input string 
	string input="bot pick ball"; 
	//initalise input stream 
	stringstream currentstring(input); 
	int count=-1; string word[10]; 
	//Repeatedly put words in string array 
	while (currentstring.good()) 
		{ 
			count=count+1; currentstring >> word[count];
		} 
	string agent[] = {"bot","mike"};
	string action[] = {"pick","put","lift","drop","go"};
	string direction[] = {"forward","backwards","left","right"};
	string pronoun[] = {"I","you","we"};
	string object[] = {"nuts","plum","cat","cup"};
	string colour [] = {"red","blue"};
	
	return 0; 
}