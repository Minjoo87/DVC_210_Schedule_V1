// Programmer: Minjoo Kim
// Programmer's ID: 1581736

#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#include <cstring> // for strtok and strcpy

#include "DynamicArray.h"

struct ClassInfo{
    string course;
    int total;
};

void updateRecords(string, DynamicArray<ClassInfo>&);

int main(){
    cout << "Programmer: Minjoo Kim\n";
    cout << "Programmer's ID: 1581736\n";
    cout << "File: " << __FILE__ << endl;
    
    // for parsing the inputfile
    char* token;
    char buf[1000];
    const char* const tab = "\t";
    
    // open the input file
    ifstream fin;
    fin.open("dvc-schedule.txt");
    if (!fin.good()) throw "I/O error";
    
    DynamicArray<string> duplicatesArray;
    DynamicArray<ClassInfo> classInfoArray;
    
    int duplicates = 0;
    int count = 0;
    
    // read the input file
    while (fin.good()){
        count++;
        
        if (count % 1000 == 0) {
            cout << '.';
            cout.flush();
        }
        
        // read the line
        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());
        if (buf[0] == 0) continue; // skip blank lines
        
        // parse the line
        const string term(token = strtok(buf, tab));
        const string section((token = strtok(0, tab)) ? token : "");
        const string course((token = strtok(0, tab)) ? token : "");
        const string instructor((token = strtok(0, tab)) ? token : "");
        const string whenWhere((token = strtok(0, tab)) ? token : "");
        if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
        
        const string subjectCode(course.begin(), course.begin() + course.find('-'));
        
        bool found = false;
        string key = term + "," +section;
        for (int i = 0; i < duplicatesArray.capacity(); i++){
            if (duplicatesArray[i] == key){
                found = true;
                duplicates++;
                break;
            }
        }
        if (!found) {
            duplicatesArray[duplicatesArray.capacity()] = key;
            updateRecords(subjectCode, classInfoArray);
        }
    }
    
    cout << endl  << "number of duplicates: " << duplicates << endl;
    
    for(int i = 0; i < classInfoArray.capacity(); i++){
        for(int j = 0; j < classInfoArray.capacity(); j++){
            if(classInfoArray[i].course < classInfoArray[j].course)
                swap(classInfoArray[i], classInfoArray[j]);
        }
    }
    
    for(int i = 0; i < classInfoArray.capacity(); i++){
        if(classInfoArray[i].course == "" || classInfoArray[i].total == 0){
            continue;
        }
        cout << classInfoArray[i].course << ", " << classInfoArray[i].total << " section" << endl;
    }
    
    fin.close();
}

void updateRecords(string course, DynamicArray<ClassInfo>& cIA){
    bool found = false;
    for (int i = 0; i < cIA.capacity(); i++){
        if (cIA[i].course == course){
            cIA[i].total++;
            found = true;
            break;
        }
    }
    if (!found){
        ClassInfo cI;
        cI.course = course;
        cI.total = 1;
        cIA[cIA.capacity()] = cI;
    }
}
