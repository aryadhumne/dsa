# 🎓 Student Academic Dashboard

A **console-based C++ application** that manages student academic records using core Data Structures: `vector`, `unordered_map`, `stack`, and `priority_queue`.

---

## 📋 About the Project

The **Student Academic Dashboard** is a terminal-based student management system built as a Data Structures & Algorithms project in C++. It allows you to manage complete student academic profiles — including subject-wise marks, attendance, grades, and rankings — all persisted to a local file (`students.txt`).

### 🔧 Data Structures Used

| Data Structure | Purpose |
|---|---|
| `vector<Student>` | Stores all student records dynamically |
| `unordered_map<int, int>` | Hash map for O(1) student lookup by ID |
| `stack<string>` | Tracks recent activity history (LIFO) |
| `priority_queue` | Extracts top 5 performers efficiently |
| `sort` (STL) | Ranks students by average marks |

### 📌 Features

- ✅ **Add Student** — Register a new student with 5 subject marks and attendance
- ✅ **Display All Students** — View complete academic details of every student
- ✅ **Search Student** — Instant lookup by Student ID using a hash map
- ✅ **Update Student** — Modify marks and attendance of an existing student
- ✅ **Delete Student** — Remove a student record permanently
- ✅ **Sort & Rank Students** — Sort all students by average marks (descending)
- ✅ **Top 5 Performers** — Find the top 5 students using a priority queue
- ✅ **Academic Report** — Summary stats: pass/fail count, averages, attendance shortage
- ✅ **Recent Activities** — View the last N operations using a stack
- ✅ **File Persistence** — All records are auto-saved to `students.txt`

### 🏅 Grading Scale

| Average Marks | Grade |
|---|---|
| ≥ 90% | A+ |
| ≥ 80% | A  |
| ≥ 70% | B  |
| ≥ 60% | C  |
| ≥ 40% | D  |
| < 40% | F  |

---

## 🗂️ Project Structure

```
student-dashboard/
├── main.cpp               # Full C++ source code
├── student_dashboard.exe  # Compiled executable (Windows)
├── students.txt           # Auto-generated data file (created on first save)
└── README.md              # This file
```

---

## ⚙️ Prerequisites

Make sure you have a C++ compiler installed:

- **Windows**: [MinGW-w64 / MSYS2](https://www.msys2.org/) with `g++` (C++17 or later)
- **Linux/macOS**: `g++` via `build-essential` or Xcode Command Line Tools

Verify your compiler:
```bash
g++ --version
```

---

## 🚀 How to Execute

### Step 1 — Navigate to the Project Directory

Open your **terminal / Command Prompt / PowerShell** and go to the project folder:

```bash
cd path\to\student-dashboard
```

> **Example (Windows):**
> ```
> cd C:\Users\hp\.gemini\antigravity\scratch\student-dashboard
> ```

---

### Step 2 — Compile the Code

```bash
g++ -std=c++17 -o student_dashboard main.cpp
```

> On **Linux/macOS**, the output file has no `.exe` extension:
> ```bash
> g++ -std=c++17 -o student_dashboard main.cpp
> ```

You should see **no errors or warnings** if compilation is successful.

---

### Step 3 — Run the Program

**Windows (Command Prompt / PowerShell):**
```bash
.\student_dashboard.exe
```

**Linux / macOS:**
```bash
./student_dashboard
```

The interactive dashboard menu will appear in your terminal:

```
========================================
       STUDENT ACADEMIC DASHBOARD
========================================
1. Add Student
2. Display All Students
3. Search Student
4. Update Student
5. Delete Student
6. Sort Student Rankings
7. View Top 5 Performers
8. Generate Academic Report
9. View Recent Activities
0. Exit
```

---

## 🖥️ Sample Usage

### Adding a Student
```
Enter Student ID: 101
Enter Student Name: Alice Johnson
Enter Department: Computer Science
Enter Semester (1-8): 3

Enter details of 5 subjects:

Subject 1
Enter Subject Name: Data Structures
Enter Subject Marks (0-100): 92

Subject 2
Enter Subject Name: Mathematics
Enter Subject Marks (0-100): 88
...

Enter Attendance Percentage: 91.5

Student added successfully!
```

### Generating Report
```
========== ACADEMIC REPORT ==========
Total Students: 10
Average Marks: 74.30%
Average Attendance: 83.20%
Passed Students: 9
Failed Students: 1
Pass Percentage: 90.00%
Top Performers (90%+): 2
Attendance Shortage (<75%): 3
=====================================
```

---

## 💾 Data Persistence

- All student records are **automatically saved** to `students.txt` after every add, update, or delete.
- The file is **loaded on startup** so your data is never lost between sessions.
- Do **not manually edit** `students.txt` — it uses a structured format read by the program.

---

## ⚠️ Notes

- Each student must have exactly **5 subjects**.
- Student IDs must be **unique** positive integers (1 to 1,000,000,000).
- Semester must be between **1 and 8**.
- Marks and attendance must be between **0 and 100**.
- Attendance below **75%** is flagged as a shortage in the academic report.

---

## 👨‍💻 Author

Built as a **Data Structures & Algorithms** project in C++.  
Demonstrates practical use of `vector`, `unordered_map`, `stack`, `priority_queue`, and file I/O.
