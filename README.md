# University Management System

A comprehensive C++ console application for managing university operations including students, faculty, courses, enrollments, grades, absences, and schedules.

## Features

### 🎓 Student Management
- Create, modify, and delete student records
- Search students by ID
- Display all registered students
- Automatic ID assignment

### 👨‍🏫 Personnel Management
- Add teaching and administrative staff
- Modify personnel information
- Remove staff members
- Search personnel by ID
- Display all personnel with color-coded output

### 📚 Course Management
- Create and manage courses with department and level information
- Assign teachers to courses
- Modify course details
- Search and display courses
- View courses taught by specific instructors

### 📝 Enrollment System
- Enroll students in courses (pending validation)
- Teacher validation of enrollments
- Display enrolled students per course
- Two-step enrollment process for security

### 📊 Grade Management
- Add grades for enrolled students
- Modify existing grades
- View student transcripts
- Display course grade reports
- Automatic enrollment verification

### 📅 Attendance Tracking
- Record student absences
- Mark absences as justified/unjustified
- Modify absence records
- View student attendance history
- Course-specific absence reports

### 🗓️ Schedule Management
- Create course schedules with days and time slots
- Modify existing schedules
- Remove course schedules
- Generate student weekly timetables
- Day-wise schedule organization

## System Architecture

### Core Classes

#### `Etudiant` (Student)
- **Attributes**: name, unique ID
- **Static Members**: student collection, ID counter
- **Methods**: CRUD operations, search functionality

#### `Personnel` (Staff)
- **Base Class** for university personnel
- **Derived Classes**: `Enseignant` (Teacher), `Administratif` (Administrative)
- **Attributes**: name, ID, personnel type
- **Methods**: information management, display functions

#### `Cours` (Course)
- **Attributes**: name, department, level, assigned teacher
- **Methods**: course management, teacher assignment
- **Static Collection**: centralized course storage

#### `Inscriptions` (Enrollments)
- **Two-tier System**: pending and validated enrollments
- **Security**: teacher validation required
- **Data Structure**: hash map for efficient lookup

#### `Note` (Grade)
- **Validation**: ensures student enrollment before grading
- **Features**: grade modification, comprehensive reporting
- **Integration**: works with enrollment system

#### `Absence` (Attendance)
- **Tracking**: absence count and justification status
- **Validation**: enrollment verification
- **Reporting**: student and course-specific views

#### `Emploi` (Schedule)
- **Structure**: course-to-schedule mapping
- **Flexibility**: multiple time slots per course
- **Student View**: personalized weekly schedules

## Technical Specifications

### Requirements
- **Language**: C++11 or later
- **Compiler**: GCC, Clang, or MSVC
- **Platform**: Cross-platform (Windows, Linux, macOS)
- **Dependencies**: Standard C++ library only

### Data Structures Used
- `std::vector` for dynamic arrays
- `std::unordered_map` for fast lookups
- `std::map` for ordered associations
- Static members for shared data

### Memory Management
- Automatic memory management using STL containers
- Pointer-based relationships between objects
- RAII principles followed

## Installation & Usage

### Compilation
```bash
g++ -std=c++11 -o university_management main.cpp
```

### Running the Program
```bash
./university_management
```

### Navigation
The system uses a menu-driven interface with numbered options:
1. Navigate using number keys
2. Follow on-screen prompts
3. Enter required information when requested
4. Use option 8 to exit from main menu

## User Interface Features

### Color-Coded Output
- 🟢 **Green**: Success messages and data display
- 🔴 **Red**: Error messages and warnings
- 🟡 **Yellow**: Warning and pending status messages
- 🔵 **Blue**: Information and status updates
- 🟣 **Purple**: Special operations and confirmations

### Menu Structure
```
Main Menu
├── Personnel Management
├── Course Management
├── Enrollment Management
├── Student Management
├── Grade Management
├── Attendance Management
├── Schedule Management
└── Exit
```

## Data Flow

1. **Personnel Setup**: Create teachers and administrative staff
2. **Course Creation**: Define courses and assign teachers
3. **Student Registration**: Add students to the system
4. **Enrollment Process**: Students enroll in courses (pending validation)
5. **Validation**: Teachers validate student enrollments
6. **Grade Entry**: Teachers add grades for enrolled students
7. **Attendance**: Track student absences
8. **Scheduling**: Create and manage course timetables

## Security Features

- **Enrollment Validation**: Only assigned teachers can validate enrollments
- **Grade Restrictions**: Grades can only be added for enrolled students
- **Attendance Verification**: Absence tracking requires valid enrollment
- **ID-based Access**: All operations require valid ID verification

## Limitations

- **Data Persistence**: Data is not saved between program runs
- **Concurrent Access**: Single-user application
- **Input Validation**: Limited input sanitization
- **Database**: Uses in-memory storage only

## Future Enhancements

- [ ] Database integration for data persistence
- [ ] Web-based interface
- [ ] Multi-user support with authentication
- [ ] Advanced reporting and analytics
- [ ] Email notifications
- [ ] Mobile application
- [ ] Backup and restore functionality

## License

This project is open source and available under the MIT License.

## Support

For issues and questions:
- Create an issue in the repository
- Provide detailed information about the problem
- Include steps to reproduce any bugs

---

**Author**: Bensaid Mohammad
**Version**: 1.0.0  
**Last Updated**: 2024
