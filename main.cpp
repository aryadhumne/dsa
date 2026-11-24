#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <stack>
#include <iomanip>
#include <sstream>
#include <queue>
#include <string>

using namespace std;

// Structure to store subject details
struct Subject {
    string name;
    double marks;
};

// Structure to store student information
struct Student {
    int id;
    string name;
    string department;
    int semester;
    vector<Subject> subjects;
    double attendance;

    // Calculate average marks
    double average() const {
        if (subjects.empty()) return 0;

        double total = 0;

        for (const auto& sub : subjects) {
            total += sub.marks;
        }

        return total / subjects.size();
    }

    // Calculate grade
    string grade() const {
        double avg = average();

        if (avg >= 90) return "A+";
        if (avg >= 80) return "A";
        if (avg >= 70) return "B";
        if (avg >= 60) return "C";
        if (avg >= 40) return "D";

        return "F";
    }
};

// Main data structures
vector<Student> students;

// Hash Map for fast student searching
unordered_map<int, int> studentIndex;

// Stack for recent activities
stack<string> history;



// Safe integer input
int readInt(string message, int minValue, int maxValue) {
    string line;
    int value;
    char extra;

    while (true) {
        cout << message;
        getline(cin, line);

        stringstream ss(line);

        if (ss >> value && !(ss >> extra) &&
            value >= minValue && value <= maxValue) {
            return value;
        }

        cout << "Invalid input! Please enter a valid number.\n";
    }
}

// Safe decimal input
double readDouble(string message, double minValue,
                  double maxValue) {
    string line;
    double value;
    char extra;

    while (true) {
        cout << message;
        getline(cin, line);

        stringstream ss(line);

        if (ss >> value && !(ss >> extra) &&
            value >= minValue && value <= maxValue) {
            return value;
        }

        cout << "Invalid input! Enter a value between "
             << minValue << " and " << maxValue << ".\n";
    }
}

// Safe text input
string readText(string message) {
    string value;

    while (true) {
        cout << message;
        getline(cin, value);

        if (value.find_first_not_of(" \t") != string::npos) {
            return value;
        }

        cout << "Input cannot be empty!\n";
    }
}

// Rebuild Hash Map
void rebuildIndex() {
    studentIndex.clear();

    for (int i = 0; i < (int)students.size(); i++) {
        studentIndex[students[i].id] = i;
    }
}

// Search student using Hash Map
int searchStudent(int id) {
    auto it = studentIndex.find(id);

    if (it == studentIndex.end()) {
        return -1;
    }

    return it->second;
}

// Save student records in file
void saveData() {
    ofstream file("students.txt");

    if (!file) {
        cout << "Error: Unable to save student records!\n";
        return;
    }

    for (const auto& s : students) {
        file << s.id << " "
             << quoted(s.name) << " "
             << quoted(s.department) << " "
             << s.semester << " "
             << s.attendance << " "
             << s.subjects.size();

        for (const auto& sub : s.subjects) {
            file << " "
                 << quoted(sub.name) << " "
                 << sub.marks;
        }

        file << "\n";
    }

    file.close();
}

// Load student records from file
void loadData() {
    ifstream file("students.txt");

    if (!file) {
        return;
    }

    Student s;

    while (file >> s.id
                >> quoted(s.name)
                >> quoted(s.department)
                >> s.semester
                >> s.attendance) {

        size_t count;

        if (!(file >> count) || count == 0) {
            break;
        }

        s.subjects.clear();

        bool valid = true;

        for (size_t i = 0; i < count; i++) {
            Subject sub;

            if (!(file >> quoted(sub.name) >> sub.marks)) {
                valid = false;
                break;
            }

            s.subjects.push_back(sub);
        }

        if (!valid) break;

        if (s.id > 0 &&
            s.semester >= 1 && s.semester <= 8 &&
            s.attendance >= 0 && s.attendance <= 100 &&
            searchStudent(s.id) == -1) {

            students.push_back(s);
            rebuildIndex();
        }
    }

    file.close();
}

// Add new student
void addStudent() {
    Student s;

    cout << "\n========== ADD STUDENT ==========\n";

    s.id = readInt("Enter Student ID: ", 1, 1000000000);

    if (searchStudent(s.id) != -1) {
        cout << "Student ID already exists!\n";
        return;
    }

    s.name = readText("Enter Student Name: ");

    s.department = readText("Enter Department: ");

    s.semester = readInt("Enter Semester (1-8): ", 1, 8);

    int subjectCount = readInt("\nHow many subjects does this student have? (1-20): ", 1, 20);

    cout << "\nEnter details of " << subjectCount << " subjects:\n";

    for (int i = 0; i < subjectCount; i++) {
        Subject sub;

        cout << "\nSubject " << i + 1 << "\n";

        sub.name = readText("Enter Subject Name: ");

        sub.marks = readDouble(
            "Enter Subject Marks (0-100): ", 0, 100
        );

        s.subjects.push_back(sub);
    }

    s.attendance = readDouble(
        "\nEnter Attendance Percentage: ", 0, 100
    );

    students.push_back(s);

    rebuildIndex();
    saveData();

    history.push("Added student: " + s.name);

    cout << "\nStudent added successfully!\n";
}

// Display student information
void displayStudent(const Student& s) {
    cout << "\n================================\n";
    cout << "STUDENT ACADEMIC DETAILS\n";
    cout << "================================\n";

    cout << "Student ID: " << s.id << "\n";
    cout << "Name: " << s.name << "\n";
    cout << "Department: " << s.department << "\n";
    cout << "Semester: " << s.semester << "\n";

    cout << "\nSUBJECT-WISE MARKS\n";

    for (const auto& sub : s.subjects) {
        cout << sub.name << " : "
             << sub.marks << "/100\n";
    }

    cout << fixed << setprecision(2);

    cout << "\nAverage Marks: " << s.average() << "%\n";
    cout << "Attendance: " << s.attendance << "%\n";
    cout << "Grade: " << s.grade() << "\n";

    cout << "================================\n";
}

// Display all student records
void displayAll() {
    if (students.empty()) {
        cout << "\nNo student records found!\n";
        return;
    }

    for (const auto& s : students) {
        displayStudent(s);
    }
}

// Search student
void findStudent() {
    cout << "\n========== SEARCH STUDENT ==========\n";

    int id = readInt("Enter Student ID: ", 1, 1000000000);

    int index = searchStudent(id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    displayStudent(students[index]);
}

// Update student information
void updateStudent() {
    cout << "\n========== UPDATE STUDENT ==========\n";

    int id = readInt("Enter Student ID: ", 1, 1000000000);

    int index = searchStudent(id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    Student& s = students[index];

    cout << "\nUpdating record of: " << s.name << "\n";

    for (int i = 0; i < (int)s.subjects.size(); i++) {
        cout << "\nSubject: " << s.subjects[i].name << "\n";

        s.subjects[i].marks = readDouble(
            "Enter New Marks (0-100): ", 0, 100
        );
    }

    s.attendance = readDouble(
        "\nEnter New Attendance: ", 0, 100
    );

    saveData();

    history.push("Updated student: " + s.name);

    cout << "\nStudent record updated successfully!\n";
}

// Delete student
void deleteStudent() {
    cout << "\n========== DELETE STUDENT ==========\n";

    int id = readInt("Enter Student ID: ", 1, 1000000000);

    int index = searchStudent(id);

    if (index == -1) {
        cout << "Student not found!\n";
        return;
    }

    string name = students[index].name;

    students.erase(students.begin() + index);

    rebuildIndex();
    saveData();

    history.push("Deleted student: " + name);

    cout << "\nStudent deleted successfully!\n";
}

// Sort students by average marks
void sortStudents() {
    if (students.empty()) {
        cout << "\nNo student records available!\n";
        return;
    }

    sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return a.average() > b.average();
        });

    rebuildIndex();

    cout << "\n========== STUDENT RANKINGS ==========\n";

    for (int i = 0; i < (int)students.size(); i++) {
        cout << "\nRank: " << i + 1;
        displayStudent(students[i]);
    }

    history.push("Generated student rankings");
}

// Priority Queue comparator
struct CompareStudent {
    bool operator()(const Student& a, const Student& b) const {
        return a.average() < b.average();
    }
};

// Find top 5 performers using Priority Queue
void topPerformers() {
    if (students.empty()) {
        cout << "\nNo student records available!\n";
        return;
    }

    priority_queue<Student, vector<Student>, CompareStudent> pq;

    for (const auto& s : students) {
        pq.push(s);
    }

    cout << "\n========== TOP 5 PERFORMERS ==========\n";

    int rank = 1;

    while (!pq.empty() && rank <= 5) {
        Student s = pq.top();
        pq.pop();

        cout << "\nRank " << rank << ": " << s.name
             << " | Average: " << s.average() << "%\n";

        rank++;
    }
}

// Generate academic report
void generateReport() {
    if (students.empty()) {
        cout << "\nNo records available!\n";
        return;
    }

    double totalMarks = 0;
    double totalAttendance = 0;

    int passed = 0;
    int failed = 0;
    int toppers = 0;
    int attendanceShortage = 0;

    for (const auto& s : students) {
        totalMarks += s.average();
        totalAttendance += s.attendance;

        if (s.average() >= 40)
            passed++;
        else
            failed++;

        if (s.average() >= 90)
            toppers++;

        if (s.attendance < 75)
            attendanceShortage++;
    }

    int n = students.size();

    cout << fixed << setprecision(2);

    cout << "\n========== ACADEMIC REPORT ==========\n";

    cout << "Total Students: " << n << "\n";

    cout << "Average Marks: "
         << totalMarks / n << "%\n";

    cout << "Average Attendance: "
         << totalAttendance / n << "%\n";

    cout << "Passed Students: " << passed << "\n";

    cout << "Failed Students: " << failed << "\n";

    cout << "Pass Percentage: "
         << (passed * 100.0 / n) << "%\n";

    cout << "Top Performers (90%+): " << toppers << "\n";

    cout << "Attendance Shortage (<75%): "
         << attendanceShortage << "\n";

    cout << "=====================================\n";
}

// Show recent activities using Stack
void showHistory() {
    if (history.empty()) {
        cout << "\nNo recent activities!\n";
        return;
    }

    stack<string> temp = history;

    cout << "\n========== RECENT ACTIVITIES ==========\n";

    while (!temp.empty()) {
        cout << "- " << temp.top() << "\n";
        temp.pop();
    }
}

// Main function
int main() {
    loadData();

    int choice;

    do {
        cout << "\n\n";
        cout << "========================================\n";
        cout << "       STUDENT ACADEMIC DASHBOARD       \n";
        cout << "========================================\n";

        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort Student Rankings\n";
        cout << "7. View Top 5 Performers\n";
        cout << "8. Generate Academic Report\n";
        cout << "9. View Recent Activities\n";
        cout << "0. Exit\n";

        choice = readInt("\nEnter Your Choice: ", 0, 9);

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayAll();
                break;

            case 3:
                findStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                sortStudents();
                break;

            case 7:
                topPerformers();
                break;

            case 8:
                generateReport();
                break;

            case 9:
                showHistory();
                break;

            case 0:
                saveData();
                cout << "\nThank you for using Student Academic Dashboard!\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
