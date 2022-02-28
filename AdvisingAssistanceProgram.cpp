// AdvisingAssistanceProgram.cpp
// Jessica McAlum
// SNHU CS 300
// February 20, 2022

#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>


using namespace std;
using std::cout; 
using std::cin;
using std::endl; 
using std::string;

// Defines structure to hold course information
struct Course {
   string courseNumber;
   string courseTitle;
   vector<string> prerequisites;
};

// Displays course number and title
void displayCourse(Course course) {
   cout << course.courseNumber << ", " << course.courseTitle << endl;
    
}

// Displays course with prerequisites
void printCourse(Course course) {
   cout << endl;
   cout << course.courseNumber << ", " << course.courseTitle << endl;
   if (course.prerequisites.size() > 0) {
      cout << "Prerequisites: ";
      for (int i = 0; i < course.prerequisites.size(); i++) {
         if (i == (course.prerequisites.size() - 1)) {
            cout << course.prerequisites.at(i) << endl;
         }
         else {
            cout << course.prerequisites.at(i) << ", ";
         }
      }

   }
   cout << endl;
}

// Loads courses from a file, creates course objects
// and places them in a vector data structure
vector<Course> loadCourses(string fileName) {
   ifstream inFS;
   bool fileRead = true; 
   string line;
   vector<Course> courses;
    
   inFS.open(fileName);
   if (!inFS.is_open()) {
      cout << "Could not open file" << endl;
   }
    
   while (!inFS.eof()) {
      getline(inFS, line);
      vector<string> courseInfo;
        
      // Parses each line in file
      stringstream ss(line);
      while (ss.good()) {
         string substr;
         getline(ss, substr, ',');
         courseInfo.push_back(substr);
      }
      // Creates course objects
      Course course;
      course.courseNumber = courseInfo.at(0);
      course.courseTitle = courseInfo.at(1);
         if (courseInfo.size() > 2) {
            for (int i = 2; i < courseInfo.size(); i++) {
               course.prerequisites.push_back(courseInfo.at(i));
            }    
         }
      // Places each course object in vector
      courses.push_back(course);
   
   }
    
   inFS.close();
   cout << "\nCourses have successfully loaded.\n" << endl;

   return courses;
    
}

// Partition the vector of courses into two parts, low and high
size_t partition(vector<Course>& courses, size_t begin, size_t end) {
   // Set low and high equal to begin and end
   size_t low = begin;
   size_t high = end;

   // Pick the middle element as pivot point
   size_t pivot = begin + ((end - begin) / 2);

   bool done = false;
   // Whilte not done
   while (!done) {
      // keep incrementing low index while courses[low] < courses[pivot]
      while (courses.at(low).courseNumber < courses.at(pivot).courseNumber) {
         low += 1;
      }

      // keep decrementing high index while courses[pivot] < courses[high]
      while (courses.at(pivot).courseNumber < courses.at(high).courseNumber) {
         high -= 1;
      }

      /*If there are zero or one elements remaining,
      all courses are partitioned. Return high*/
      if (low >= high) {
         done = true;
      }
        
      // else swap the low and high courses
      else {
         swap(courses.at(low), courses.at(high));

         // move low and high closer ++low, --high
         low += 1;
         high -= 1;
      }
   }

   return high;
}

// Performs a quick sort on course number
void quickSort(vector<Course>& courses, size_t begin, size_t end){
   // Set mid equal to 0
   size_t mid = 0;

   /* Base case: If therre are 1 or zero courses to sort,
   partition is already sorted otherwise if begin is greater
   than or equal to end then return*/
   if (begin >= end) {
      return;
   }

   /* Partition courses into low and high such that 
   midpoint is location of last element in low */
   mid = partition(courses, begin, end);

   // recursively sort low partition (begin to mid)
   quickSort(courses, begin, mid);

   // recursively sort high partition (mid+1 to end)
   quickSort(courses, mid + 1, end);
    
}

// Changes string from user input to upper case
char change_case(char c) {
   if (std::isupper(c))
      return std::tolower(c);
   else
      return std::toupper(c);
}

int main() {

   // Vector to hold all the courses
   vector<Course> courses;
    
   std::string userCourse;

   char choice = '0';
   while (choice != '9') {
      cout << "Menu:" << endl;
      cout << "  1. Load Data Structure" << endl;
      cout << "  2. Print Course List" << endl;
      cout << "  3. Print Course" << endl;
      cout << "  9. Exit" << endl;
      cout << "What would you like to do? Enter choice: ";
      cin >> choice;

      switch (choice) {

         case '1':

            // Load the file data into the data structure
            courses = loadCourses("ABCU_Advising_Program_Input.txt");
           

            break;

         case '2':
            
            // Quick sorts courses
            quickSort(courses, 0, courses.size() - 1);
            quickSort(courses, 0, courses.size() - 1);

            // Prints alphanumberic list of all courses
            cout << endl;
            cout << "Here is a sample schedule : \n" << endl;
            for (int i = 0; i < courses.size(); i++) {
               displayCourse(courses.at(i));
            }

            cout << endl;
            
            break;

         case '3':
             
            // Prompts and gets user input for course they would like the info for
            cout << "What course do you want to know about ? Enter course number : " << endl;
            cin >> userCourse;
            std::transform(userCourse.begin(), userCourse.end(), userCourse.begin(), change_case);
            
            // Prints course number, title, and the prerequisites
            for (int i = 0; i < courses.size(); i++) {
               if (courses.at(i).courseNumber == userCourse) {
                  printCourse(courses.at(i));
               }  
            }

            break;
         
         case '9':
            break;

         default: 

            // Informs user of invalid input
            cout << choice << " is not a valid input.\n" << endl;
            break;
      }
   }

   cout << "\nThank you for using the course planner!" << endl;

   return 0;
}