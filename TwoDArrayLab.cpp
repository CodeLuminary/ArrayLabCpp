#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <sstream>

using namespace std;
//This function is meant to take in a string and split it using space than return the number of text after split
int txLength(string tx){
		string ch;int cnt = 0;
	for(int i = 0; i < tx.length(); i++){//Loop through the text
		ch = tx.substr(i,1); //Look for space in text
		if(strcmp(ch.c_str()," ")==0){//Check if character is space
			cnt++; //Increment counter variable
		}
	}
	return cnt + 1;//Return number of text
}
//This function is meant to take in a string and split it using tab('#t') than return the number of text after split
int txLength2(string tx){
		string ch;int cnt = 0;
	for(int i = 0; i < tx.length(); i++){//Loop through the text
		ch = tx.substr(i,1);//Look for #t in text
		if(strcmp(ch.c_str(),"\t")==0){//Check if character is \t
			cnt++;//Increment counter variable
		}
	}
	return cnt + 1;//Return number of text
}

string * splitString(string tx){
	string ch;int cnt = 0;
	
	//return cnt;
	int len = txLength(tx);//Get length of text
	string * newStr = new string[len]; //Create new string array
	int cnt2 = 0; int start = 0; int sz;
	for(int i = 0; i < tx.length(); i++){ //Loop through string content
		ch = tx.substr(i,1); //Extract each character
		if(strcmp(ch.c_str()," ")==0){//Check if extracted character is space
			newStr[cnt2++] = tx.substr(start,i-(start));//Store in string array
			start = i + 1; //Reset substring start position
			if(cnt2 == (len-1)){//Check if it's the last index
				newStr[cnt2] = tx.substr(start,(len-start)); //Store the last content in string array
			}
		}
	}
	return newStr;
}
//This function takes in a string and split them using \t and return an array
string * splitString2(string tx){
	string ch;int cnt = 0;
	
	//return cnt;
	int len = txLength2(tx);//Get length of text
	string * newStr = new string[len]; //Create new string array
	int cnt2 = 0; int start = 0; int sz;
	for(int i = 0; i < tx.length(); i++){ //Loop through string content
		ch = tx.substr(i,1);//Extract each character
		if(strcmp(ch.c_str(),"\t")==0){//Check if extracted character is tab
			newStr[cnt2++] = tx.substr(start,i-(start));//Store in string array
			start = i + 1;//Reset substring start position
			if(cnt2 == (len-1)){//Check if it's the last index
				newStr[cnt2] = tx.substr(start,(len-start));//Store the last content in string array
			}
		}
	}
	return newStr;
}
//This function takes in a string and convert it to all lower case
string toLower(string tx){
	transform(tx.begin(),tx.end(),tx.begin(), ::tolower);
	return tx;
}
//This function convert int, double values to string
string toString(double x){ 
  ostringstream ss;
  ss << x;
  string ab = ss.str();
  return ab;
}

void wordFinder(string fileName){
		string line;//Create a variable to store each line
		int pos = 0; //Variable pos is meant to count each line of the file
		int rows= 1; int cols; //This holds rows and column values
		bool isSizeGotten = false;//This holds if size is gotten
		int currentPos = 0;
		string text = "";//This holds the word table content
		string text2 = ""; //This holds the search content
	ifstream myfile(fileName.c_str());
	if(myfile.is_open()){
		while(getline(myfile,line)){
			pos++;
			if(strcmp(toLower(splitString(line)[0]).c_str(),toLower("Size").c_str())==0){ //Check if this line is the line that specify the size
				rows = atoi(splitString(line)[1].substr(0,1).c_str()); //Get row value
				cols = atoi(splitString(line)[1].substr(1,1).c_str());//Get column value
				isSizeGotten = true; //Set isSizeGotten to true
				currentPos = pos;
			}
			else{
				if(isSizeGotten){
					if(pos <= (currentPos + rows)){//Check if the current position is more than the word table length
						cols = txLength2(line); //Reget column value
						//cout << "co-" << cols << '\n';
						for(int i = 0; i < txLength2(line); i++){ //Loop through the word table
							
							text += splitString2(line)[i]; //Store value in variable text
						
						}
						
						text += " ";
					}
					else{
						text2 += line + " "; //Store word to search for in variable text2
					}			
				}
			}		
		}	
		text = text.substr(0, text.length()-1);	//Remove extra spaces
		text2 = text2.substr(0,text2.length()-2);	//Remove extra spaces
		char arr[txLength(text)][splitString(text)[0].length()];//Create a dynamic array
		for(int i= 0; i < txLength(text); i++){//Loop through the words to search for
			for(int j=0; j < splitString(text)[0].length(); j++){//Loop through the string array return from splitString and store each value in the new array
				arr[i][j] = splitString(text)[i].c_str()[j];
			}
		}
		string colText = ""; string rowText=""; string diaText = "";string diaText2 = "";//Create variable to store row text, column text diagonal text
		for(int i = 0; i < 24; i++){ //Loop to write space
			cout << " ";
		}
		cout << "Row  " << "Column      " << "Direction" << '\n';
		int t2len = txLength(text2);//Get the length 
		int len2 = splitString(text)[0].length();//Reget length of column
		for(int u = 0; u < t2len; u++){	//Loop through each text to search for		
			cout << splitString(text2)[u] ; //Print each text to find
			string txtToFind = splitString(text2)[u]; //Get length of text
			int txt2Len = txtToFind.length();
			string res = ""; //Create a variable to store result
			bool isFound = false;
			for(int i = txt2Len; i < 26; i++){//Loop to add space
				cout << " ";
			}
			
			for(int i = 0; i < txLength(text); i++){//Loop through the arr
				rowText = ""; colText = "";diaText = ""; diaText2 = ""; //Reinitialize variable
				for(int j = 0; j < len2;j++){
				  rowText += arr[i][j]; //Store each horizontal content in rowText
				  colText += arr[j][i]; //Store each vertical content is colText
				  int diff = len2-i; //Get difference between the search text length and current row index
				  	if(j < diff){ //Check if j column index is less the diff
						diaText += arr[i+j][j]; //Store each buttom diagonal content is diatext
						diaText2 += arr[j][i+j]; //Store each top diagonal content is diaText
					}
					if(txt2Len <= rowText.length()){//Check if search text length is less than rowText
						for(int e = 0; e <= (rowText.length()-txt2Len); e++){
							string newTx = rowText.substr(e,txt2Len);//Extract from rowText
							string newTx2 = toLower(txtToFind);//Convert search text to lower case
							if(strcmp(toLower(newTx).c_str(),newTx2.c_str())==0){//Check if search text is found and set isFound to true
								res += toString(i) + "      " + toString(j-(txt2Len-1)) + "       Horizontal";//Store result to print
								isFound = true;
								cout << res << '\n';
								break;
							}
						}
						
					}
					if(txt2Len <= colText.length()){//Check if search text length is less than colText
						for(int e = 0; e <= (colText.length()-txt2Len); e++){//
							string newTx = colText.substr(e,txt2Len);//Extract from colText
							string newTx2 = toLower(txtToFind);//Convert search text to lower case
							if(strcmp(toLower(newTx).c_str(),newTx2.c_str())==0){//Check if search text is found and set isFound to true
								res += toString(j-(txt2Len-1)) + "      " + toString(i) + "       Vertical";//Store result to print
								isFound = true;
								cout << res << '\n';
								break;
							}
						}
						if(isFound){
							break;
						}
					}
					if(txt2Len <= diaText.length()){//Check if search text length is less than diaText
						for(int e = 0; e <= (diaText.length()-txt2Len); e++){
							string newTx = diaText.substr(e,txt2Len);//Extract from diaText
							string newTx2 = toLower(txtToFind);//Convert search text to lower case
							if(strcmp(toLower(newTx).c_str(),newTx2.c_str())==0){//Check if search text is found and set isFound to true
								res += toString(j) + "      " + toString(i+j-(txt2Len+1)) + "       Diagonal";//Store result to print
								isFound = true;
								cout << res << '\n';
								break;
							}
						}
					}
						if(txt2Len <= diaText2.length()){//Check if search text length is less than diaText2
						for(int e = 0; e <= (diaText2.length()-txt2Len); e++){
							string newTx = diaText2.substr(e,txt2Len);//Extract from diaText2
							string newTx2 = toLower(txtToFind);//Convert search text to lower case
							if(strcmp(toLower(newTx).c_str(),newTx2.c_str())==0){//Check if search text is found and set isFound to true
								res +=  toString(j-(txt2Len-1))  + "      " + toString(i+j-(txt2Len-1)) +"       Diagonal"; //Store result to print
								isFound = true;
								cout << res << '\n';
								break;
							}
						}
					}
				}	    
			}
			if(!isFound){//If search is not found
				cout << "Not Found" << '\n';
			}	
			cout << '\n';
		}
		myfile.close();
		
		cout << '\n' << '\n';
		
		for(int i= 0; i < txLength(text); i++){//Loop through the words to search for
			for(int j=0; j < splitString(text)[0].length(); j++){//Loop through the string array return from splitString and store each value in the new array
				cout << arr[i][j] << '\t';
			}
				cout << '\n';
		}
	}
	else{
		cout << "Unable to open file";
	}
}
//This function is meant to print an array
void printArray(int ar[9][9]){
	//Loop through the array and print it
	for(int i = 0; i < 9; i++){
		for(int j = 0; j < 9; j++){
			cout << ar[i][j] << '\t';			
		}
		cout << '\n';
	}
}

void sudoku(string fileName){
	string line;  //Create a variable to store each line of the text
	ifstream myfile(fileName.c_str()); int pos = 0;
	string content = "";
	if(myfile.is_open()){//Try to open file
		while(getline(myfile,line)){//Loop through the file
			for(int i = 0; i < txLength2(line);i++){//Loop each content in each line and store the content in variable content
				content += splitString2(line)[i];
			}
			content += " ";
		}
		int arr[9][9]; //Create an integer array
		//This loop split the value of variable content using space and store each character in the array arr
		for(int i = 0; i <9; i++){ 
			for(int j = 0; j < 9; j++){
				arr[i][j] = ((int) splitString(content)[i].c_str()[j])-48; //Character return ascii value when converted to integer thus to get raw integer 48 have to be subtracted
			}
		}
		int newArr[9]; //Create a new variable to store the test content
		bool isSudokuOk = true; //Create and set boolean variable to true
		for(int i = 0; i <9; i++){ //Loop the array arr
			for(int j = 0; j < 9; j++){
				if(j <= 6 && i <= 6){//Check if the current index is less or equal to 3 less than 9
					for(int k = i; k < i+3; k++){
						for(int l = j; l <j+3; l++){
							newArr[(i-k)*(l-j)] = arr[k][j]; //Store arr content in newArr
						}
					}
					for(int m = 0; m < 9; m++){ //Loop through newArr
						if(newArr[m]>9 || newArr[m] < 1){//Check if each index value is greater than 9 or less than 1
							isSudokuOk = false;
						}
						for(int n = 0; n < 9; n++){//Loop through newArr
							if(n != m){//Check if the current index n is not same as m
								if(newArr[m]==newArr[n]){//Check if an index value is same as another index value
									isSudokuOk = false;
								}
							}
						}
					}
				}			
			}
		}
		cout << "Is Sudoku Ok: ";
		if(isSudokuOk){
			cout << "True" <<'\n';
		}
		else{
		   cout << "False" << '\n';
		}
		printArray(arr);
		myfile.close();
	}
	else{
		cout << "Unable to open file";
	}
//	return pos + 1;
}

int main(){
	//wordFinder("wordFind.txt");
	//sudoku("sudoku.txt");
}
