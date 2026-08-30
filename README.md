# Quadratic Equation Solver

## Ordinary Library

Author: ZDA
Version: 1.1
Date: August 2026 (Summer School)
Warning: This library was created for educational purposes only.

About the Project

This program is designed to solve linear and quadratic equations of the form:

ax² + bx + c = 0

The program determines the type of equation, finds the number of roots, and calculates their values when they exist.

### Features

- Solving quadratic equations
- Solving linear equations
- Detecting equations with no roots
- Detecting equations with one root
- Detecting equations with two roots
- Detecting equations with an infinite number of roots
- Checking the correctness of user input
- Comparing floating-point numbers using EPS precision
- Displaying colored text in the console
- Displaying the equation and solution using different colors
- Outputting ASCII art from document.txt
- Checking user login and password
- Registering new users
- Checking whether a username already exists
- Hashing passwords using the FNV-1a algorithm
- Reading and writing user data to a file
- Displaying the ASCII image of the authorized user
- Testing the equation solver using predefined test cases
- Displaying information about failed tests

### Project Structure

The program is divided into several functions:

Function Description
- SolvEquation - Determines the type of equation
- SolvLine - Solves linear equations
- SolvSquare" - Solves quadratic equations
- CompFloat - Compares floating-point numbers
- InputValues - Reads equation coefficients
- InputWithColorComment - Reads a floating-point value with a colored prompt
- PrintValues - Displays the solution
- PrintfColorArgument - Displays the equation using a specified color
- PrintfColor - Displays a string using a specified color
- PrintASCII - Displays an ASCII image from a text file
- RunOneTest - Runs and checks one test case
- RunAllTest - Runs all predefined test cases
- PrintTestFailOneRoot - Displays information about a failed one-root test
- PrintTestFailTwoRoot - Displays information about a failed two-root test
- fnv32_hash - Calculates the FNV-1a hash of a string
- CheckLoginPassword - Checks the user's login and password and displays the user's ASCII image
- IsLoginExists - Checks whether a username already exists in the user database
- Registration - Registers a new user and saves their data to the user database

Floating-Point Precision

Floating-point numbers are compared using the EPS (epsilon) constant.

This helps reduce errors caused by the limited precision of floating-point arithmetic.

Console Output

The TXLib library is used to change the color of text displayed in the console.

Different colors are used to display the equation, results, prompts, and other program messages.

User Authentication

The program includes a simple user authentication system.

It supports:

- User registration
- Login and password verification
- Username existence checking
- Password hashing using FNV-1a
- Saving user information to a file
- Displaying an ASCII image associated with the authorized user

The authentication system is implemented for educational purposes and should not be considered secure for real-world applications.

Testing

The equation solver includes predefined test cases.

Tests can check different situations, including:

- Equations with no roots
- Equations with one root
- Equations with two roots
- Linear equations
- Equations with infinitely many solutions
- Incorrect input
