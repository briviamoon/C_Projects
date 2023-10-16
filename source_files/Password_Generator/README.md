# PASSWORD WIZARD

This C program serves the purpose of generating a substantial number of random passwords and saving them to a designated file. It is created with educational objectives in mind and is structured to illustrate various core concepts in C programming.

## Detailed Functionality

### User Interaction

1. **Number of Passwords**: The program begins by engaging the user to input the number of passwords they wish to generate.
2. **Password Length**: Users are prompted to specify the desired length for each generated password.
3. **Output File Name**: A user-defined name for the output file is solicited, with careful consideration to prevent buffer overflows by restricting the maximum length to 255 characters.

#### Total Password Calculation

A fundamental aspect of the program is the calculation of the total number of passwords to be generated. This is determined based on the user-specified file size and an password Length of choice.

- The formula ```numberOfPass = (((double)fileSize * 1024 * 1024) / passLength)``` is used to calculate the number of passwords in a `x MBs` file based on the given password length. Here's how it works:

1. **fileSize * 1024 * 1024**: This part converts the file size from megabytes (MB) to bytes. Since there are 1024 kilobytes (KB) in `x MBs` and 1024 bytes in 1 KB, you need to multiply the file size in MB by 1024 twice to get the total number of bytes in a `x MBs` file. This is used to represent the total space available for passwords in the `x MBs` file.

2. **/ passLength**: This part divides the total available space (in bytes) by the length of each password in characters (which are assumed to be one byte each). This division gives you the estimated number of passwords that can fit in a `x MBs` file with the given password length.

#### File Handling

File Input/Output (I/O) is at the core of the program's functionality. It employs the "`append`" mode when opening the specified file. This mode not only permits the addition of newly generated passwords but also preserves any existing content in the file.

#### Password Generation

The primary function, ```writeToFile```, manages the generation of random passwords and their subsequent appending to the output file.

#### Password Generation Function

The ```generator``` function is the workhorse behind the password generation process. It constructs random passwords with the specified length by randomly selecting characters from a predefined character set. This character set comprises numbers, lowercase and uppercase letters, and an array of special symbols, ensuring that the generated passwords exhibit a wide range of characters, making them more robust and secure.

#### Character Selection

The ```randomizer``` function is responsible for the random selection of characters from the character set. This element is crucial in creating truly random and diverse passwords.

#### Code Modularity via Header File

Good practices are showcased through the inclusion of a header file named ```passgen.h``` This header file is an organized hub for essential function declarations and includes the necessary libraries. It promotes code modularity and maintainability, adhering to best practices in software development.

#### Writing to File

Passwords are written to the output file, with each password on a separate line, accomplished through the ```fprintf``` function. Upon the successful generation and appending of all requested passwords, the output file is diligently closed.

### Educational Significance

This program offers a hands-on experience in the application of fundamental programming concepts. It provides students with the chance to explore password generation algorithms and comprehend the practical implications of ```file I/O,``` ```memory management```, and ```randomization``` techniques in the context of ```C programming```.

In summary, this in-depth project is a valuable resource for others looking to strengthen their programming skills and gain insight into real-world application scenarios. It provides a comprehensive understanding of core programming concepts while demonstrating effective code organization and modularity practices.
