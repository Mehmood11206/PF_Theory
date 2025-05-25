#include <stdio.h>      // For input/output functions like printf, scanf, fopen, etc.
#include <stdlib.h>     // For general-purpose functions like exit
#include <string.h>     // For string handling functions like strcpy, strlen, strcspn
#include <ctype.h>      // For character handling like toupper()

// Define maximum constants
#define MAX_QUESTIONS 10             // Max number of questions to read from file
#define MAX_LINE_LENGTH 200          // Max characters per line for questions and options

// Function to load questions, options, and answers from a file
int loadQuestions(char questions[][MAX_LINE_LENGTH], char options[][4][MAX_LINE_LENGTH], char answers[]) {
    FILE *file = fopen("questions.txt", "r");  // Open the questions file in read mode
    if (file == NULL) {                        // Check if file couldn't be opened
        printf("Error: Cannot open questions.txt file\n");
        return 0;
    }

    int i = 0;                                  // Counter for number of questions
    char line[MAX_LINE_LENGTH];                // Buffer to read lines from file

    // Read until end of file or max questions reached
    while (i < MAX_QUESTIONS && fgets(line, MAX_LINE_LENGTH, file)) {
        // Skip blank or empty lines
        if (strlen(line) <= 1) continue;

        // Remove newline character from question line
        line[strcspn(line, "\n")] = '\0';
        strcpy(questions[i], line);           // Store the question text

        // Read 4 options for each question
        for (int j = 0; j < 4; j++) {
            if (!fgets(line, MAX_LINE_LENGTH, file)) break; // Break if not enough lines
            line[strcspn(line, "\n")] = '\0';               // Remove newline
            strcpy(options[i][j], line);                    // Store the option
        }

        // Read the correct answer for this question
        if (fgets(line, MAX_LINE_LENGTH, file)) {
            answers[i] = toupper(line[0]);  // Store answer in uppercase (e.g., A, B, C, D)
        } else {
            answers[i] = 'X';               // Store 'X' if answer is missing
        }

        i++;  // Move to next question
    }

    fclose(file);     // Close the file after reading
    return i;         // Return total number of questions loaded
}

int main() {
    // Arrays to store loaded data
    char questions[MAX_QUESTIONS][MAX_LINE_LENGTH];            // Question text
    char options[MAX_QUESTIONS][4][MAX_LINE_LENGTH];           // 4 options for each question
    char answers[MAX_QUESTIONS];                               // Correct answers (A/B/C/D)

    char userAnswer;       // Store user's answer input
    int score = 0;         // Initialize score counter

    // Load data from file
    int numQuestions = loadQuestions(questions, options, answers);

    // Check if any question was loaded
    if (numQuestions == 0) {
        printf("No questions found in file.\n");
        return 1;  // Exit if no questions loaded
    }

    // Introduction
    printf("Welcome to the Quiz!\n");
    printf("Answer each question by typing A, B, C, or D\n\n");

    // Loop through all loaded questions
    for (int i = 0; i < numQuestions; i++) {
        printf("Question %d: %s\n", i + 1, questions[i]);     // Print question number and text

        // Print 4 options
        for (int j = 0; j < 4; j++) {
            printf("  %c) %s\n", 'A' + j, options[i][j]);     // Print option as A), B), etc.
        }

        // Ask user for their answer and validate input
        do {
            printf("Your answer (A/B/C/D): ");
            scanf(" %c", &userAnswer);        // Read user input
            userAnswer = toupper(userAnswer); // Convert to uppercase for comparison
        } while (userAnswer < 'A' || userAnswer > 'D'); // Keep asking until valid

        // Compare user's answer with the correct one
        if (userAnswer == answers[i]) {
            printf("Correct!\n");     // If correct, show message
            score++;                  // Increase score
        } else {
            printf("Wrong! The correct answer was %c\n", answers[i]); // Show correct answer
        }

        printf("\n");  // Add space before next question
    }

    // Final score summary
    printf("Quiz finished!\n");
    printf("Your score: %d out of %d\n", score, numQuestions); // Display result

    return 0;  // End of program
}
