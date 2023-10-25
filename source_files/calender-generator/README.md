# Calendar Generator using Zeller's Congruence

This C program is designed to generate calendars for any given day, month, and year using Zeller's Congruence. It provides you with the day of the week for the specified date and can optionally print the entire calendar for the year.

## Table of Contents

- [Introduction](#introduction)
- [How to Use](#how-to-use)
- [Program Structure](#program-structure)
- [Zeller's Congruence](#zellers-congruence)
- [Author](#author)
- [License](#license)

## Introduction

The Calendar Generator is a simple C program that utilizes Zeller's Congruence to calculate the day of the week for a given date. It also allows you to view a full year's calendar. The program was developed by [Your Name].

## How to Use

1. Compile the source code by running the appropriate compiler command (e.g., `gcc calendar.c -o calendar`).
2. Execute the program and provide a day, month, and year when prompted.
3. The program will calculate and display the day of the week for the specified date.
4. You can choose to view the full year's calendar (optional).
5. The program will display the calendar for the entire year.

## Program Structure

- `main.c`: Contains the main program logic, including user input, Zeller's Congruence calculation, and calendar display.
- `zeller.c`: Implements the Zeller's Congruence algorithm to find the day of the week.
- `calendar.h`: Header file containing function declarations.

## Zeller's Congruence

Zeller's Congruence is an algorithm used to find the day of the week for a given date. It is based on a formula that takes into account the day, month, year, and century. The program uses this formula to determine the day of the week.

## Author

- [Brivia Allan]
- GitHub: [briviamoon](https://github.com/yourusername)

## License

This program is open-source and available under the [MIT License](LICENSE). You are free to use, modify, and distribute it according to the terms of the license.
