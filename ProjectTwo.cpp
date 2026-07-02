#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// ===============================
// Course Structure
// ===============================
struct Course {
    string courseId;
    string title;
    vector<string> prerequisites;
};

// ===============================
// Load Courses From CSV
// ===============================
vector<Course> loadCourses(const string& filename) {
    vector<Course> courses;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "ERROR: Could not open file: " << filename << endl;
        return courses;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, title, prereq;

        Course course;

        getline(ss, id, ',');
        getline(ss, title, ',');

        course.courseId = id;
        course.title = title;

        while (getline(ss, prereq, ',')) {
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq);
            }
        }

        courses.push_back(course);
    }

    file.close();
    return courses;
}

// ===============================
// Print All Courses (Sorted)
// ===============================
void printCourseList(vector<Course>& courses) {
    sort(courses.begin(), courses.end(),
         [](const Course& a, const Course& b) {
             return a.courseId < b.courseId;
         });

    cout << "\n=== COURSE LIST ===\n";
    for (auto& c : courses) {
        cout << c.courseId << ": " << c.title << endl;
    }
    cout << endl;
}

// ===============================
// Print One Course
// ===============================
void printCourseInfo(const vector<Course>& courses, const string& id) {
    for (auto& c : courses) {
        if (c.courseId == id) {
            cout << "\nCourse: " << c.courseId << " - " << c.title << endl;
            cout << "Prerequisites: ";

            if (c.prerequisites.empty()) {
                cout << "None\n\n";
            } else {
                for (size_t i = 0; i < c.prerequisites.size(); i++) {
                    cout << c.prerequisites[i];
                    if (i < c.prerequisites.size() - 1) cout << ", ";
                }
                cout << "\n\n";
            }
            return;
        }
    }

    cout << "Course not found.\n\n";
}

// ===============================
// MAIN MENU
// ===============================
int main() {
    vector<Course> courses;
    string filename;
    int choice = 0;

    while (choice != 9) {
        cout << "==============================\n";
        cout << "   ABCU Course Planner\n";
        cout << "==============================\n";
        cout << "1. Load Data Structure\n";
        cout << "2. Print Course List\n";
        cout << "3. Print Course Information\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter filename (example: courses.csv): ";
            cin >> filename;
            courses = loadCourses(filename);
            if (!courses.empty()) {
                cout << "Data loaded successfully.\n\n";
            }
            break;

        case 2:
            if (courses.empty()) {
                cout << "ERROR: Load data first.\n\n";
            } else {
                printCourseList(courses);
            }
            break;

        case 3:
            if (courses.empty()) {
                cout << "ERROR: Load data first.\n\n";
            } else {
                cout << "Enter course ID (example: CSCI200): ";
                cin >> filename;
                printCourseInfo(courses, filename);
            }
            break;

        case 9:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n\n";
        }
    }

    return 0;
}
