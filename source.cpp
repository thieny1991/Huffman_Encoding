#include <iostream>
#include<vector>
//#include<stdio.h>
#include<fstream>
#include <string.h>
#include<sstream>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sstream>
#include<queue>
//#include <bits/stdc++.h>
using namespace std;
void childProcess(char c, vector<char>cStr, string outfileName);
int encodingFile(string fileName);
void printVector(vector<char>cStr);
void printFrequencies(vector<int>f,vector<int>c);
void removeAllChar(char c, vector<char>&str);
vector<int> getSortedAsciiListByFrequencies(vector<int> symbolFrequencyList);
bool readInputFile(const char* inputFile, vector<char>&cStr, vector<int> &symbolFrequeny);

//ENTRY TO PROGRAM
int main(int argc, char*argv[]) {
	string inputFileName = argv[1];
	vector<char> str;
	if (argc > 0) {
		encodingFile(inputFileName);
	}
	return 0;
	}

bool readInputFile(const char* inputFile, vector<char>&cStr,vector<int> &symbolFrequeny) {
	ifstream ifs(inputFile);
	stringstream  ss;
	char av;
	if (ifs.is_open()) {
		while (ifs.get(av)) {
			
			cStr.push_back(av);
			if (av == '\n' || av == '\r')
				continue;
			else {
				symbolFrequeny[av] += 1;
			}
		}
		return 1;
	}
	else {
		cout << "Error in opening file" << endl;
		return 0;
	}
}

int encodingFile(string fileName) {
	vector<char>cStr;
	vector<int> symbolFrequencyList(256, 0);
	vector<int> sortedAsciiByFrequency;
	if (readInputFile(fileName.c_str(), cStr, symbolFrequencyList)) {
		sortedAsciiByFrequency = getSortedAsciiListByFrequencies(symbolFrequencyList);
		printFrequencies(sortedAsciiByFrequency,symbolFrequencyList);
		//cout << "This is parent " << getpid() << endl;
		pid_t pid;
		char charToBeDecoded;
		static int n = sortedAsciiByFrequency.size();
		cout << "Original Message:\t";
		printVector(cStr);
		for (int i = 0; i < sortedAsciiByFrequency.size();i++) {
			stringstream ss;
			charToBeDecoded=static_cast<char>(sortedAsciiByFrequency[i]);
			ss << charToBeDecoded;
			string fileName="";
			ss >> fileName;
			fileName.append(".txt");
			pid = fork();
			if (pid == 0) {
				//cout << "This is child " << getpid() << endl;
				childProcess(charToBeDecoded, cStr, fileName);
				exit(0);
			}
			else{
				removeAllChar(charToBeDecoded, cStr);
			}
			//blocks the calling process until one of its child process exits or a signal is received
			wait(NULL);
			ifstream inputFile(fileName);
			string decodeBits;
			if (inputFile.is_open()) {
				getline(inputFile, decodeBits);
				cout <<"Symbol "<<charToBeDecoded<<" code:\t"<<decodeBits << endl;
			}
			if (i<(sortedAsciiByFrequency.size() - 1))
				cout << "Remaining Message:\t";
			printVector(cStr);
			inputFile.close();
		}
	}
}
void removeAllChar(char c, vector<char>&str) {
	for (int i = 0;i < str.size();i++) {
		if (str[i] == c) {
			str.erase(str.begin() + i);
			--i;
		}
	}
}
void printVector(vector<char> cStr) {
	for (int i = 0; i < cStr.size();i++) {
		cout << cStr[i];
	}
	cout << endl;
}//end printVectorChar

void printFrequencies(vector<int> f, vector<int> c) {
	for (int i = 0; i < f.size();i++) {
		if (f[i] != 0)
			cout << static_cast<char>(f[i]) << " frequency = " << c[f[i]] << endl;
	}
}//end printVectorChar

vector<int> getSortedAsciiListByFrequencies(vector<int> symbolFrequencyList) {
	vector<int> presentSymbols;
	int  f1 = 0, f2 = 0,ascii1, ascii2 = 0;
	for ( ascii1 = 0;ascii1 < symbolFrequencyList.size();ascii1++) {
		f1 = symbolFrequencyList[ascii1];
		if (f1 != 0) {
			if (presentSymbols.empty())
				presentSymbols.push_back(ascii1);
			else {
				int size = presentSymbols.size();
				for (int k = 0; k < size;k++) {
					ascii2 = presentSymbols[k];
					f2 = symbolFrequencyList[ascii2];
					if (f1 > f2) {
						presentSymbols.insert(presentSymbols.begin() + k, ascii1);
						break;
					}//end if
					//if f1 is smallest, push to the end 
					else if (f1 <= symbolFrequencyList[presentSymbols.back()]
						&&ascii1!=presentSymbols.back()) {
						presentSymbols.push_back(ascii1);
					}//end for
				}//end else
			}//end 
		}//end if
	}//end for
	return presentSymbols;
}


/**This method receive a character, symbol frequency, and a string and encode the character
*	into a string bits, then write out the result to a c.txt file
*@param: char c, vector<int> frequencies, string
*@return: void
*/

void childProcess(char c, vector<char>str, string outFileName) {

	string decodeBits;
	for (int i = 0; i < str.size();i++) {
		if (c == str[i]) {
			decodeBits.append("1");
		}
		else if (str[i]=='\r'||str[i]=='\n'){
			continue;
		}
		else {
			decodeBits.append("0");
		}
	}
	ofstream outFile;
	//cout << "outFile =" + outFileName;
	//cout << " Bits " << decodeBits << endl;
	outFile.open(outFileName.c_str());
	outFile << decodeBits;
	outFile.close();
}