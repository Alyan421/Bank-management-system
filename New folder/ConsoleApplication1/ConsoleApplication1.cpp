#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<ctime>

using namespace std;

class Student {
public:
	int id;
	string name;
	double marks;
	Student(){}
	Student(int a, string n, double m) {
		id = a;
		name = n;
		marks = m;
	}
	void addStd() {
		ofstream fin;
		cin >> id;
		cin >> name;
		cin >> marks;
		fin.open("Hello.txt", ios::app);
		fin.write(reinterpret_cast<char*>(this), sizeof(*this));
		fin.close();
	}
	void update() {
		fstream file;
		int n;
		cout << "Enter ID\n";
		cin >> n;
		file.open("Hello.txt", ios::ate | ios::in | ios::out);
		file.seekp(0);
	
		while (file.read(reinterpret_cast<char*>(this), sizeof(*this))) {
			if (id == n) {
				cout << "Enter Details";
				cin >> marks;
				file.seekp(-(long)sizeof(*this), ios_base::cur);
				file.write(reinterpret_cast<char*>(this), sizeof(*this));
			}
		}
	}

	void readfromfile(){
		ifstream fin;
		fin.open("Hello.txt", ios::in);
		while (fin.read(reinterpret_cast<char*>(this), sizeof(*this))) {
			display();
		}
		fin.close();
	}

	void remove1() {
		ifstream fin;
		ofstream fout;
		int n;
		cout << "Enter ID\n";
		cin >> n;
		fin.open("Hello.txt",ios::in );
		fout.open("copy.txt", ios::out);
		fin.read(reinterpret_cast<char*>(this), sizeof(*this));
		while (fin) {
			if (id != n){
				fout.write(reinterpret_cast<char*>(this), sizeof(*this));
			}
			fin.read(reinterpret_cast<char*>(this), sizeof(*this));
		}
		fout.close();
		fin.close();
		remove("Hello.txt");
		rename("copy.txt", "Hello.txt");

	}
	void display() {
		cout << id << " " << name << " " << marks << " " << endl;
	} 
};


int main() {
	int size;
	cout << "How many students";
	cin >> size;
	Student std;
	for (int i = 0; i < 2; i++) {
		std.addStd();
	}
	std.readfromfile();
	std.update();
	std.readfromfile();

}