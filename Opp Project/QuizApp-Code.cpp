#include <iostream>
#include <string>
#include "raylib.h"

using namespace std;

// Constants
const int MAX_QUESTIONS = 10;
const int MAX_OPTIONS = 4;
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

// Base Question class
class Question {
protected:
    string text;
    int points;
public:
    Question(string t, int p) : text(t), points(p) {}
    Question() {}

    virtual void display(int posY) = 0; // Pure virtual function
    virtual bool checkAnswer(string answer) = 0;
    int getPoints() { return points; }
    string getText() { return text; }
};

// True/False Question
class TrueFalseQuestion : public Question {
    bool correctAnswer;
public:
    TrueFalseQuestion(string t, int p, bool correct) : Question(t, p), correctAnswer(correct) {}
    TrueFalseQuestion() {}

    void display(int posY) {
        DrawText(text.c_str(), 50, posY, 20, BLACK);
        DrawText("(True/False)", 50, posY + 30, 20, DARKGRAY);
    }
    
    bool checkAnswer(string answer) {
        if (answer == "true" || answer == "True" || answer == "t" || answer == "T" || answer == "1") {
            return correctAnswer == true;
        }
        return correctAnswer == false;
    }
};

// Multiple Choice Question
class MultipleChoiceQuestion : public Question {
    string options[MAX_OPTIONS];
    int correctOption;
    int numOptions;

public:
    MultipleChoiceQuestion(string t, int p, string opts[], int correct)
        : Question(t, p), correctOption(correct), numOptions(4) {
        for (int i = 0; i < numOptions; i++) {
            options[i] = opts[i];
        }
    }
    MultipleChoiceQuestion() {}
    
    void display(int posY) {
        DrawText(text.c_str(), 50, posY, 20, BLACK);
        
        for (int i = 0; i < numOptions; i++) {
            string optionText = to_string(i+1) + ". " + options[i];
            DrawText(optionText.c_str(), 70, posY + 40 + (i * 30), 20, DARKBLUE);
        }
    }
    
    bool checkAnswer(string answer) {
        int choice;
        try {
            choice = stoi(answer);
        } catch (...) {
            return false;
        }
        return choice == correctOption;
    }
};

// Player class
class Player {
    string name;
    int score;
public:
    Player(string n) : name(n), score(0) {}
    
    void addPoints(int p) { score += p; }
    int getScore() { return score; }
    string getName() { return name; }

    bool operator>(Player p) {
        return(score > p.score);
    }

    bool operator==(Player p) {
        return(score == p.score);
    }
};

// Quiz class
class Quiz {
    Question* mcq_questions[2][MAX_QUESTIONS]; // 2 subjects (math and chem)
    Question* bool_questions[2][MAX_QUESTIONS]; // 2 subjects (math and chem)
    int math_mcq_Questions, chem_mcq_Questions, math_bool_Questions, chem_bool_Questions;
    int currentQuestionIndex;
    bool quizComplete;
    int selectedOption;
    string playerAnswer;
    bool answerSubmitted;
    bool answerCorrect;
    Player* currentPlayer;

public:
    Quiz() : math_mcq_Questions(0), chem_mcq_Questions(0),
    math_bool_Questions(0), chem_bool_Questions(0), 
    currentQuestionIndex(0), quizComplete(false), 
    selectedOption(-1), answerSubmitted(false), answerCorrect(false) {}

    void addQuestion(Question* q, string subject, string type) {
        if(subject == "math") { 
            if(type == "mcq") {
                if (math_mcq_Questions < MAX_QUESTIONS) {
                    mcq_questions[0][math_mcq_Questions++] = q;
                }
            } else {
                if (math_bool_Questions < MAX_QUESTIONS) {
                    bool_questions[0][math_bool_Questions++] = q;
                }
            }   
        } else { 
            if(type == "mcq") {
                if (chem_mcq_Questions < MAX_QUESTIONS) {
                    mcq_questions[1][chem_mcq_Questions++] = q;
                }
            } else {
                if (chem_bool_Questions < MAX_QUESTIONS) {
                    bool_questions[1][chem_bool_Questions++] = q;
                }
            } 
        }
    }
    
    void start(Player* p) {
        currentPlayer = p;
        currentQuestionIndex = 0;
        quizComplete = false;
        selectedOption = -1;
        playerAnswer = "";
        answerSubmitted = false;
    }
    
    void update(int subjectChoice, int questionType) {
        if (quizComplete) return;
        
        if (!answerSubmitted) {
            if (questionType == 1) { // MCQ
                if (IsKeyPressed(KEY_ONE)) selectedOption = 1;
                if (IsKeyPressed(KEY_TWO)) selectedOption = 2;
                if (IsKeyPressed(KEY_THREE)) selectedOption = 3;
                if (IsKeyPressed(KEY_FOUR)) selectedOption = 4;
                
                if (selectedOption != -1 && IsKeyPressed(KEY_ENTER)) {
                    playerAnswer = to_string(selectedOption);
                    answerSubmitted = true;
                    answerCorrect = mcq_questions[subjectChoice-1][currentQuestionIndex]->checkAnswer(playerAnswer);
                    if (answerCorrect) {
                        currentPlayer->addPoints(mcq_questions[subjectChoice-1][currentQuestionIndex]->getPoints());
                    }
                }
            } else { // True/False
                if (IsKeyPressed(KEY_T)) {
                    playerAnswer = "true";
                    answerSubmitted = true;
                    answerCorrect = bool_questions[subjectChoice-1][currentQuestionIndex]->checkAnswer(playerAnswer);
                    if (answerCorrect) {
                        currentPlayer->addPoints(bool_questions[subjectChoice-1][currentQuestionIndex]->getPoints());
                    }
                } else if (IsKeyPressed(KEY_F)) {
                    playerAnswer = "false";
                    answerSubmitted = true;
                    answerCorrect = bool_questions[subjectChoice-1][currentQuestionIndex]->checkAnswer(playerAnswer);
                    if (answerCorrect) {
                        currentPlayer->addPoints(bool_questions[subjectChoice-1][currentQuestionIndex]->getPoints());
                    }
                }
            }
        } else {
            if (IsKeyPressed(KEY_ENTER)) {
                answerSubmitted = false;
                selectedOption = -1;
                playerAnswer = "";
                
                int maxQuestions = (questionType == 1) ? 
                    (subjectChoice == 1 ? math_mcq_Questions : chem_mcq_Questions) :
                    (subjectChoice == 1 ? math_bool_Questions : chem_bool_Questions);
                
                if (++currentQuestionIndex >= maxQuestions) {
                    quizComplete = true;
                }
            }
        }
    }
    
    void draw(int subjectChoice, int questionType) {
        BeginDrawing();
        ClearBackground(YELLOW);
        
        if (!quizComplete) {
            // Display current question
            if (subjectChoice == 1) { // Math
                if (questionType == 1) { // MCQ
                    mcq_questions[0][currentQuestionIndex]->display(100);
                } else { // True/False
                    bool_questions[0][currentQuestionIndex]->display(100);
                }
            } else { // Chemistry
                if (questionType == 1) { // MCQ
                    mcq_questions[1][currentQuestionIndex]->display(100);
                } else { // True/False
                    bool_questions[1][currentQuestionIndex]->display(100);
                }
            }
            
            // Display instructions based on question type
            if (questionType == 1) { // MCQ
                DrawText("Select an option (1-4) and press Enter", 50, 300, 20, DARKGRAY);
            } else { // True/False
                DrawText("Press T for True or F for False", 50, 300, 20, DARKGRAY);
            }
            
            // Show feedback after answer submission
            if (answerSubmitted) {
                if (answerCorrect) {
                    DrawText("Correct!", 50, 350, 30, GREEN);
                    DrawText(("+" + to_string(mcq_questions[subjectChoice-1][currentQuestionIndex]->getPoints()) + " points").c_str(), 50, 390, 20, GREEN);
                } else {
                    DrawText("Incorrect!", 50, 350, 30, RED);
                }
                DrawText("Press Enter to continue", 50, 450, 20, DARKGRAY);
            }
        } else {
            // Quiz complete screen
            DrawText("Quiz Complete!", 250, 200, 40, BLUE);
            DrawText(("Final Score: " + to_string(currentPlayer->getScore())).c_str(), 250, 250, 30, BLACK);
            DrawText("Press Enter to return to main menu", 200, 350, 20, DARKGRAY);
        }
        
        // Display player info
        DrawText(("Player: " + currentPlayer->getName()).c_str(), 800, 20, 20, PINK);
        DrawText(("Score: " + to_string(currentPlayer->getScore())).c_str(), 800, 50, 20, PINK);
        
        EndDrawing();
    }
    
    bool isComplete() const { return quizComplete; }
};

int main() {
    // Initialize window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Quiz App");
    SetTargetFPS(60);

    // Create quiz 
    Quiz quiz;

    // Math MCQ questions
    string mathMCQOptions1[] = {"e^x^1/2", "e^x^1/2 / x^1/2", "e^x^1/2 / 2x^1/2 ", "2x^1/2*e^x^1"};
    string mathMCQOptions2[] = {"none", "a2 + 2ab + b2", "a2", "b2"};
    string mathMCQOptions3[] = {"none", "a2 + 2ab + b2", "a2", "(a+b)(a-b)"};
    string mathMCQOptions4[] = {"1","5","1/5","0"};
    string mathMCQOptions5[] = {"x^3","2x","1/x","x"};
    
    MultipleChoiceQuestion math_mcq_q[5] = {
        MultipleChoiceQuestion("If y=e^x^1/2 then dy/dx:", 2, mathMCQOptions1, 3),
        MultipleChoiceQuestion("(a+b)^2 = ", 2, mathMCQOptions2, 2),
        MultipleChoiceQuestion("a2 - b2 = ", 2, mathMCQOptions3, 4),
        MultipleChoiceQuestion("lim x to 0 sin5x / x = ?", 2, mathMCQOptions4, 2),
        MultipleChoiceQuestion("What is the derivative of f(x)=x^2:", 2, mathMCQOptions5, 2)
    };
    
    // Chemistry MCQ questions
    string chemMCQOptions1[] = {"H2O", "C2O", "NO2", "CO"};
    string chemMCQOptions2[] = {"Limestone","Bauxite","Granite","Lead"};
    string chemMCQOptions3[] = {"H2O", "C2O", "NO2", "CO"};
    string chemMCQOptions4[] = {"Neon","Fluorine","Chlorine","Oxygen"};
    string chemMCQOptions5[] = {"Oxygen","Hydrogen","Sulphur","Nitrogen"};
    
    MultipleChoiceQuestion chem_mcq_q[5] = {
        MultipleChoiceQuestion("Water = ", 2, chemMCQOptions1, 1),
        MultipleChoiceQuestion("The most important Aluminium ore is?", 2, chemMCQOptions2, 2),
        MultipleChoiceQuestion("Cabon monoxide = ", 2, chemMCQOptions3, 4),
        MultipleChoiceQuestion("Which of the following non-metals is most electronegative?", 2, chemMCQOptions4, 2),
        MultipleChoiceQuestion("Which of the following is commonly found in the acids?", 2, chemMCQOptions5, 2),
    };
    
    // True/False questions
    TrueFalseQuestion math_bool_q[5] = {
        TrueFalseQuestion("Integral of cos(x)dx = sinx+c", 2, true),
        TrueFalseQuestion("(a+b)^2 = a^2 + 2a + b^2 ", 2, false),
        TrueFalseQuestion("a^2 - b^2 = (a+b)(a-b) ", 2, true),
        TrueFalseQuestion("If f(x) = ln(x) then f'(x) = x", 2, false),
        TrueFalseQuestion("The derivative of x^2 = 2x^2", 2, false)
    };
    
    TrueFalseQuestion chem_bool_q[5] = {
        TrueFalseQuestion("water = H2O ", 2, true),
        TrueFalseQuestion("chemistry = study of energy ", 2, false),
        TrueFalseQuestion("Cabonmono Oxide = CO ", 2, true),
        TrueFalseQuestion("Helium is the Noble Gas ", 2, true),
        TrueFalseQuestion("Distillation is the process which converts solid state directly into gaseous state ", 2, false)
    };

    // Add questions to quiz
    for(int i = 0; i < 5; i++) { 
        quiz.addQuestion(&math_bool_q[i], "math", "bool"); 
        quiz.addQuestion(&chem_bool_q[i], "chem", "bool");
        quiz.addQuestion(&math_mcq_q[i], "math", "mcq");
        quiz.addQuestion(&chem_mcq_q[i], "chem", "mcq");
    }

    // Create players
    Player player1("Player1");
    Player player2("Player2");
    Player* currentPlayer = &player1;
    
    // Game state variables
    enum GameState { MENU, SUBJECT_SELECTION, QUESTION_TYPE_SELECTION, PLAYING_QUIZ, RESULTS };
    GameState currentState = MENU;
    int subjectChoice = 0;
    int questionType = 0;
    
    // Main game loop
    while (!WindowShouldClose()) {
        switch (currentState) {
            case MENU: {
                BeginDrawing();
                ClearBackground(YELLOW);
                DrawText("Quiz Game", 400, 200, 40, BLUE);
                DrawText("Press Enter to Start", 390, 300, 20, DARKGRAY);
                EndDrawing();
                
                if (IsKeyPressed(KEY_ENTER)) {
                    currentState = SUBJECT_SELECTION;
                }
                break;
            }
            
            case SUBJECT_SELECTION: {
                BeginDrawing();
                ClearBackground(YELLOW);
                DrawText("Select Subject:", 50, 200, 30, BLACK);
                DrawText("1. Mathematics", 100, 250, 25, DARKBLUE);
                DrawText("2. Chemistry", 100, 300, 25, DARKBLUE);
                EndDrawing();
                
                if (IsKeyPressed(KEY_ONE)) {
                    subjectChoice = 1; // Math
                    currentState = QUESTION_TYPE_SELECTION;
                } else if (IsKeyPressed(KEY_TWO)) {
                    subjectChoice = 2; // Chemistry
                    currentState = QUESTION_TYPE_SELECTION;
                }
                break;
            }
            
            case QUESTION_TYPE_SELECTION: {
                BeginDrawing();
                ClearBackground(YELLOW);
                DrawText("Select Question Type:", 50, 200, 30, BLACK);
                DrawText("1. Multiple Choice", 100, 250, 25, DARKBLUE);
                DrawText("2. True/False", 100, 300, 25, DARKBLUE);
                EndDrawing();
                
                if (IsKeyPressed(KEY_ONE)) {
                    questionType = 1; // MCQ
                    currentState = PLAYING_QUIZ;
                    quiz.start(currentPlayer);
                } else if (IsKeyPressed(KEY_TWO)) {
                    questionType = 2; // True/False
                    currentState = PLAYING_QUIZ;
                    quiz.start(currentPlayer);
                }
                break;
            }
            
            case PLAYING_QUIZ: {
               // quiz.draw(subjectChoice, questionType);
                quiz.update(subjectChoice, questionType);
                quiz.draw(subjectChoice, questionType);
                
                if (quiz.isComplete()) {
                    if (currentPlayer == &player1) {
                        currentPlayer = &player2;
                        currentState = SUBJECT_SELECTION;
                    } else {
                        currentState = RESULTS;
                    }
                }
                break;
            }
            
            case RESULTS: {
                if (IsKeyPressed(KEY_ENTER)) {
                    currentState = MENU;
                    // Reset players for new game
                    player1 = Player("Player1");
                    player2 = Player("Player2");
                    currentPlayer = &player1;
                }
                
                BeginDrawing();
                ClearBackground(YELLOW);
                
                DrawText("Final Results", 300, 100, 40, BLUE);
                
                DrawText(("Player 1: " + to_string(player1.getScore())).c_str(), 300, 200, 30, 
                        (player1 > player2) ? GREEN : (player1 == player2) ? BLACK : RED);
                DrawText(("Player 2: " + to_string(player2.getScore())).c_str(), 300, 250, 30, 
                        (player2 > player1) ? GREEN : (player1 == player2) ? BLACK : RED);
                
                if (player1 > player2) {
                    DrawText("Player 1 wins!", 300, 350, 30, GREEN);
                } else if (player2 > player1) {
                    DrawText("Player 2 wins!", 300, 350, 30, GREEN);
                } else {
                    DrawText("It's a tie!", 300, 350, 30, BLUE);
                }
                
                DrawText("Press Enter to return to main menu", 250, 450, 20, DARKGRAY);
                EndDrawing();
                break;
            }
        }
    }

    CloseWindow();
    return 0;
}
