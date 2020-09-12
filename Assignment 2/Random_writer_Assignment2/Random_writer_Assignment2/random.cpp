 /*
 * Project: Random_writer_Assignment2
 * Created by CS106 C++ Assignment Wizard 0.1
 *
 * Name: [TODO: Devender Singh]
 * Section: [TODO: enter section leader here]
 * [TODO: Describe assignment]
 */

#include <iostream>
#include <fstream>
#include "simpio.h"
#include "map.h"
#include "vector.h"
#include "random.h"

void OpenFile(ifstream & in);
void ReadFile(ifstream & in);
void Data(string line);
void AddData(string key, string ch);
void ShowData();
void ShowLine(string s);

Map<Vector<string> > keys;
Vector<string> start;
int order = 0;

int main ()
{
	Randomize();
	ifstream in;
	OpenFile(in);
	ReadFile(in);
	ShowData();
	in.close();
	return 0;
}

void OpenFile(ifstream & in)
{
	string fileName;
	while(true) {
		cout << "File Name: ";
		fileName = GetLine();
		in.open(fileName.c_str());
		if(!in.fail()) break;
		cout << "Error: File not Found." << endl;
		in.clear();
	}
	while(true) {
		cout << "Set Order(1 to 10): ";
		order = GetInteger();
		if(0 < order && order < 11 ) break;
		cout << "Invalid Input." << endl;
	}
}

void ReadFile(ifstream & in)
{
	string line;
	while(true) {
		getline(in, line);
		if(in.fail()) break;	
		Data(line);
	}
}

void Data(string line)
{
	int limit = line.length() - order;
	for(int i = 0; i <= limit; i++){
		string ch = "";
		string key = line.substr(i, order);
		if(i == 0) {
			start.add(key);
		}
		if((i + order) < line.length()){
			ch = line[i + order];
		}
		//cout << key << " : " << ch << endl;
		AddData(key, ch);
	}
}

void AddData(string key, string ch)
{
	if(!keys.containsKey(key)) {
		Vector<string> a;
		a.add(ch);
		keys.add(key, a);
	} else {
		keys[key].add(ch);
	}
	//cout << key <<" conatins: " << keys.containsKey(key) << endl;
	//cout << key << " vector: " << keys[key].getAt(0) << endl;

}

void ShowData()
{
	int max = 0;
	//int total = 0;
	string key;
	Map<Vector<string> > ::Iterator itr = keys.iterator();
	while(itr.hasNext()) {
		string s = itr.next();
		//total += keys[s].size();
		if(keys[s].size() > max) {
			max = keys[s].size();
			key = s;
		}
	}
	//cout << "Total keys: " << total << endl;
	ShowLine(key);
	for(int i = 0; i < 50; i++){
		/*Map<Vector<string> > ::Iterator itr1 = keys.iterator();
		while(itr1.hasNext()) {
			string s = itr1.next();
			double chance = (double)keys[s].size() / total;
			if(RandomChance(chance)) {
				ShowLine(s);
			}
		}*/
		int rand = RandomInteger(0, (start.size() - 1));
		ShowLine(start[rand]);
	}
}

void ShowLine(string s)
{	
	string key = s;
	string str = s;
		while(true){
			if(keys[key].size() == 0){
				cout << endl ;
				break;
			}
			int limit = keys[key].size() - 1;
			int chance = RandomInteger(0, limit);
			string ch = keys[key][chance];
			str += ch;
			key = key.substr(1) + ch;
		}
		cout << str;
}