# Learning Center

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![C++](https://img.shields.io/badge/language-C++17-brightgreen.svg)

## About
Learning Center is a C++ application developed as part of the "Object-Oriented Programming" course at [Technology University of Lodz](https://p.lodz.pl/) during Semester, Spring 2025. The project implements a command-line interface (CLI) application for managing a learning center, allowing users to add and remove students, teachers, classrooms, and lessons. It demonstrates proficiency in object-oriented programming principles, such as encapsulation, inheritance, and polymorphism, using modern C++ and CMake.

## Features
- Add and remove students, teachers, classrooms, and lessons via a user-friendly CLI menu.
- Robust input validation and data management using OOP techniques.
- Unit tests implemented with the Boost.Test framework to ensure functionality.
- Utilizes Boost's `ptime` for handling date and time in lesson scheduling.

## Technologies Used
- **Language**: C++17
- **Build System**: CMake 3.20+
- **Compiler**: GCC 10+, Clang 12+, or MSVC 2019+
- **Dependencies**: Boost 1.75+ (for `Boost.Test` and `ptime`)

## Getting Started

### Prerequisites
Ensure you have the following installed:
- CMake 3.20 or higher
- A C++17-compliant compiler (e.g., GCC, Clang, MSVC)
- Git for cloning the repository
- Boost 1.75 or higher

### Installation
1. Clone the repository:
```bash
git clone https://github.com/RochuOfficial/OOP-Project.git
cd LearningCenter
  ```

2. Build a build directory:
```bash
mkdir build && cd build
```

3. Configure the project with CMake:
```bash
cmake ..
```

4. Build the project:
```bash
cmake --build .
```

### Running Tests
To run the unit tests (using Boost.Test):
```bash
cd build
ctest
```

## Project Structure
- `src/`: Core source files for the application logic
- `include/`: Header files with class definitions
- `tests/`: Unit tests using Boost.Test
- `cmake/`: Custom CMake configuration files

## Learning Outcomes
Through this project, I gained experience in:
- Applying OOP principles (encapsulation, inheritance, polymorphism) in C++.
- Designing a modular CLI application with user input handling.
- Writing and running unit tests with Boost.Test.
- Configuring and managing a cross-platform build system with CMake.
- Handling and throwing exceptions.