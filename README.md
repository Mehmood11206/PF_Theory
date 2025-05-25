# Quiz Program

A simple C program that implements a quiz system. The program reads questions, options, and answers from a file and allows users to take the quiz.

## Features
- Reads questions from a text file
- Multiple choice questions (A, B, C, D options)
- Score tracking
- User-friendly interface

## How to Use
1. Compile the program:
   ```
   gcc source.c -o quiz
   ```
2. Run the program:
   ```
   ./quiz
   ```
3. Answer the questions by typing A, B, C, or D

## File Structure
- `source.c`: Main program code
- `questions.txt`: Contains questions, options, and answers
- `.gitignore`: Specifies files to be ignored by git

## Question File Format
The questions.txt file should follow this format:
```
Question 1
Option A
Option B
Option C
Option D
A
Question 2
...
``` 