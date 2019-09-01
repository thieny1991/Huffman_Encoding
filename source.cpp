#include <iostream>
#include<vector>
#include<fstream>
#include <algorithm>
#include <string>
#include<unistd.h>
#include<sys/types.h>
#include<sstream>

//#include <bits/stdc++.h>
using namespace std;
void childProcess(char character, vector<int> frequencies, string line);
int main(int argc, char**argv) {

	//vector<vector<char>> presentSymbols(256,vector<char>(2,'NULL'));
	vector<int> symbolFrequency(256, 0);
	
	string fileName = "";
	cin >> fileName;
	ifstream inputFile;
	inputFile.open(fileName);
	//ifstream inputFile(argv[1], ios::in);
	//ofstream outputFile(argv[2], ios::out);
	if (inputFile.is_open()) {
		
		string line;
		//while (getline(inputFile,line)) {
			getline(inputFile, line);
			cout << line<<endl;
			for (int i = 0; i < line.length();i++) {
				symbolFrequency[line[i]]++;
			}//end for
			vector<int> presentSymbols;
			for (int i = 0; i < symbolFrequency.size();i++) {
				if (symbolFrequency[i] != 0) {
					presentSymbols.push_back(i);
				}//end if
			}//end for
			for (char a : presentSymbols) {
			//cout << a;
		}
		cout << "This is parent " << getpid() << endl;
		pid_t pid;
		for (int i = 0; i < presentSymbols.size();i++) {
			pid = fork();
			//if the child processor was created successfully
			if (pid == 0) {
				cout << "This is child " << getpid();
				cout << " ascii value =" << presentSymbols[i] << endl;
				childProcess(presentSymbols[i], symbolFrequency, line);
				//change values of i to get out of this for loop in the child process
				i = presentSymbols.size();
			}
		}//end for
	

	}
	else {
		cout << "Cannot open file!";
	}
	inputFile.close();
	return 0;
	}

void childProcess(char c, vector<int> symbolFrequency, string line) {

	stringstream ss;
	ss << c;
	string outFileName;
	ss >> outFileName;
	outFileName.append(".txt");

	string decodeBits;
	cout << "char =" << c << endl;
	cout << "line " << line << endl;
	for (int i = 0; i < line.length();i++) {
		if (c == line[i]) {
			//cout << " 1";
			decodeBits.append("1");
		}
		else if (symbolFrequency[c] > symbolFrequency[line[i]])
		{
			//cout << "0";
			decodeBits.append("0");
		}
		else if (symbolFrequency[c] == symbolFrequency[line[i]]
			&& (c<line[i])) {
			decodeBits.append("0");
		}
	}
	ofstream outFile;
	cout << "outFile =" + outFileName;
	cout << " Bits " << decodeBits << endl;
	outFile.open(outFileName.c_str());
	outFile << decodeBits;
	outFile.close();
}


		//sorted presentSymbols by frequency
		/*vector<char> presentSymbols;
		for (int i = 0;i < symbolFrequency.size();i++) {
			if (symbolFrequency[i] != 0) {
				if(presentSymbols.empty())
					presentSymbols.push_back(i);
				else {
					int size = presentSymbols.size();
					for (int k=0; k < size;k++) {
						if (symbolFrequency[i] > symbolFrequency[presentSymbols[k]]) {
							presentSymbols.insert(presentSymbols.begin()+k,static_cast<char>(i));
							break;

						}
						else if (symbolFrequency[i] == symbolFrequency[presentSymbols[k]]) {
							presentSymbols.insert(presentSymbols.begin()+k+1, static_cast<char>(i));
							break;
						//symbolFrequency already in order, hen if frequency(i)=frequency(presentSymbols[k])
							//i is always larger than presentSymbols[k]
						}
						else if (symbolFrequency[i] < symbolFrequency[presentSymbols.back()]) {
							presentSymbols.push_back(i);
						}
					}
				}
			}
		}
		for (char a : presentSymbols) {
			//cout << a;
		}
		//sort presentSymbols
		cout << "This is parent " << getpid() << endl;
		pid_t pid;
		static int n =presentSymbols.size();
		for (int i = 0; i < presentSymbols.size();i++) {
			pid = fork();
			if (pid == 0) {
				cout << "This is child " << getpid() << endl;
				childProcess(i, symbolFrequency, presentSymbols, line);
				i = presentSymbols.size();
			}
		}
	

	}

	else {
		cout << "Cannot open file!";
	}
	inputFile.close();
	//system("PAUSE");
	return 0;
}

void childProcess(int n, vector<int> symbolFrequency, vector<char> presentSymbols,string line) {
	
	stringstream ss;
	ss << presentSymbols[n];
	string outFileName;
	ss >> outFileName;
	outFileName.append(".txt");
	
	string decodeBits;
	cout << "n =" << n << endl;
	cout << "line " << line << endl;
	for (int i = 0; i < line.length();i++) {
		if (presentSymbols[n] == line[i]) {
			//cout << " 1";
			decodeBits.append("1");
		}
		else if (symbolFrequency[presentSymbols[n]] > symbolFrequency[line[i]])
		{
			//cout << "0";
			decodeBits.append("0");
		}
		else if (symbolFrequency[presentSymbols[n]] == symbolFrequency[line[i]]
			&&(presentSymbols[n]<line[i])) {
			decodeBits.append("0");
		}
	}
	ofstream outFile;
	cout << "outFile =" + outFileName;
	cout << " Bits " << decodeBits << endl;
	outFile.open(outFileName.c_str());
	outFile << decodeBits;
	outFile.close();
}
*/
//vector<int> decompress()