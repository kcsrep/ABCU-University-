//============================================================================
// Name        : ABCU-Univercisty.cpp
// Author      : Kimberly Castro
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Project 2 ABCU-University code
//============================================================================

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

//define a structure to hold course information
struct Course{
  string title;
  string number;
  vector<string>prerequisites;
};

//structure for hashtable
struct HashTable {
  int size;
  vector<vector<Course>> table;

  // Constructor
  HashTable(int s) : size(s), table(s, vector<Course>()) {}

  // Hash function to compute an index for the given course number
  int hashFunction(const string& key) {
      int sum = 0;
      for (char ch : key) {
          sum += ch;
      }
      return sum % size;
  }

  // Function to insert a course into the hash table
  void insert(const Course& course) {
      int index = hashFunction(course.number);
      table[index].push_back(course); // Add this line to insert the course
  }

  // Function to search for a course by its number
  Course* search(const string& number) {
      int index = hashFunction(number);
      for (Course& course : table[index]) {
          if (course.number == number) {
              return &course;
          }
      }
      return nullptr;
  }
};

// Sort by course number
bool sortCourses(const Course& a, const Course& b) {
  return a.number < b.number; 
}

//reads and loads the file and adss the course to the hashtable
void loadDataStructure(string dataFile, vector<Course> &list, HashTable& hashTable){
  ifstream infile(dataFile);
  string line;
  string courseNumber,courseTitle;

  if(infile.is_open()){

    while(!infile.eof()){
      Course course;
      getline(infile,line);
      stringstream ss(line);
      getline(ss,courseNumber,',');
      getline(ss,courseTitle,',');
      course.number=courseNumber;
      course.title=courseTitle;
      
      while(getline(ss,courseNumber,',')){
        course.prerequisites.push_back(courseNumber);
      }
      list.push_back(course);
      hashTable.insert(course);
      sort(list.begin(),list.end(), sortCourses);
    }
    cout<<"\nData Structures Loaded\n";
  }
    
  else{
    cout << "Error: File not found" << endl;
  } 
}

//initializes the hashtable based off the list of courses
void hashtable(vector<Course> &list, HashTable &hash, string key){
  hash.size=list.size();
  hash.table.resize(hash.size);
  for(int i=0;i<list.size();i++){
    hash.insert(list[i]);
  }
}

//prints the courses alphanumerically
void printCourses(const vector<Course>& list) {
  for (const auto& course : list) {
      cout << course.number << " " << course.title << endl;
  }
}

//searches the hashtable and prints the course using coursenumber as key
void printCourseDetails(HashTable& hashTable, const string& courseNumber) {
  Course* course = hashTable.search(courseNumber);
  if (course) {
      cout << "Course Number: " << course->number << endl;
      cout << "Course Title: " << course->title << endl;
      cout << "Prerequisites: ";
      for (const auto& prereq : course->prerequisites) {
          cout << prereq << " ";
      }
      cout << endl;
  } else {
      cout << "Course not found." << endl;
  }
}

//main function 
int main() {
  int user_input;
  vector<Course>list;
  string courseNumber;

  // Initialize the table with a size of 10
  HashTable table(15); 

  string dataFile = "";

  cout << "Welcome to the course planner.\n\nPLease enter the file to be loaded" << endl;
  getline(cin, dataFile);
  cout<<endl;

    //displays menu
    do{

      cout<<"\n1. Load Data Structures\n"
      <<"2. Print Course List.\n"
      <<"3. Print Course.\n"
      <<"9. Exit\n";
      cin>>user_input;
      switch(user_input){
        case 1:          
          loadDataStructure(dataFile, list, table); 
          break;

        case 2:
          printCourses(list);
         break;

        case 3:
          cout << "Enter course number: ";
          cin>>courseNumber;
          transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
          printCourseDetails(table, courseNumber);
          break;
        case 9:
          cout<< "Exiting program" << endl;
          exit(0);
         break;

        default:
          while(true){
            cout << "Invalid input. Please try again.\n";
            cin>>user_input;
            if(user_input == 1 || user_input == 2 || user_input == 3 || user_input == 9){
              break;
            }
          }

      }
  }while(user_input != 9);     
}