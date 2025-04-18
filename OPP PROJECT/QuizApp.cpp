#include <iostream>
#include <string>
using namespace std;

// Constants
const int MAX_QUESTIONS = 10;
const int MAX_OPTIONS = 4;

// Base Question class
class Question {
protected:
    string text;
    int points;
public:
    Question(string t, int p) : text(t), points(p) {}
    Question() {}

    virtual void display() = 0; // Pure virtual function
    virtual bool checkAnswer(string answer) = 0;
    int getPoints() { return points; }
};

// True/False Question
class TrueFalseQuestion : public Question {
    bool correctAnswer;
public:
    TrueFalseQuestion(string t, int p, bool correct) : Question(t, p), correctAnswer(correct) {}
    TrueFalseQuestion() {}

    void display() {
        cout << text << " (True/False)" << endl;
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
    string options[MAX_QUESTIONS][MAX_OPTIONS];
    int correctOption;
    int numOptions, row;

public:
    MultipleChoiceQuestion(string t, int p, string opts[][4],int row, int correct)
        : Question(t, p), correctOption(correct), numOptions(4), row(row) {
        for (int i = 0; i < numOptions; i++) {
            options[row][i] = opts[row][i];
        }
    }
    MultipleChoiceQuestion() {}
    
    void display() {
        cout << text << endl;
        for(int i=row; i<=row; i++)
        {  for (int j = 0; j < numOptions; j++) {
            cout << (j+1) << ". " << options[i][j] << endl;
        }
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

    bool operator>(Player p)
    {
        return(score > p.score);
    }

    bool operator==(Player p)
    {
        return(score == p.score);
    }
};

// Quiz class
class Quiz {
    Question* mcq_questions[2][MAX_QUESTIONS]; // 2 subjects (math and chem)
    Question* bool_questions[2][MAX_QUESTIONS]; // 2 subjects (math and chem)
    int math_mcq_Questions, chem_mcq_Questions, math_bool_Questions, chem_bool_Questions;

public:
    Quiz() : math_mcq_Questions(0), chem_mcq_Questions(0),
    math_bool_Questions(0), chem_bool_Questions(0) {}

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
        cout << "Welcome to the Quiz, " << p->getName() << "!\n";
        int choice, type;
        string answer;
    
        cout << "1-Maths\n2-Chemistry\nChoose subject: "; 
        cin >> choice;
        cout << "1-MCQ's\n2-True/False\nChoose type of question: ";   
        cin >> type;
    
        switch(choice) 
        {
            case 1: // Math
                if(type == 1) { // MCQ
                    for (int i = 0; i < math_mcq_Questions; i++) {
                        cout << "\nQuestion " << (i+1) << ":\n";
                        mcq_questions[0][i]->display();
                    
                        cout << "Your answer: ";
                        cin >> answer;
                    
                        if (mcq_questions[0][i]->checkAnswer(answer)) {
                            cout << "Correct! +" << mcq_questions[0][i]->getPoints() << " points\n";
                            p->addPoints(mcq_questions[0][i]->getPoints());
                        } else {
                            cout << "Incorrect!\n";
                        }
                    }
                } else { // True/False
                    for (int i = 0; i < math_bool_Questions; i++) {
                        cout << "\nQuestion " << (i+1) << ":\n";
                        bool_questions[0][i]->display();
                    
                        cout << "Your answer: ";
                        cin >> answer;
                    
                        if (bool_questions[0][i]->checkAnswer(answer)) {
                            cout << "Correct! +" << bool_questions[0][i]->getPoints() << " points\n";
                            p->addPoints(bool_questions[0][i]->getPoints());
                        } else {
                            cout << "Incorrect!\n";
                        }
                    }
                }
                cout << "\nQuiz complete! Final score: " << p->getScore() << "\n";
                break;
                
            case 2: // Chemistry
                if(type == 1) { // MCQ
                    for (int i = 0; i < chem_mcq_Questions; i++) {
                        cout << "\nQuestion " << (i+1) << ":\n";
                        mcq_questions[1][i]->display();
                    
                        cout << "Your answer: ";
                        cin >> answer;
                    
                        if (mcq_questions[1][i]->checkAnswer(answer)) {
                            cout << "Correct! +" << mcq_questions[1][i]->getPoints() << " points\n";
                            p->addPoints(mcq_questions[1][i]->getPoints());
                        } else {
                            cout << "Incorrect!\n";
                        }
                    }
                } else { // True/False
                    for (int i = 0; i < chem_bool_Questions; i++) {
                        cout << "\nQuestion " << (i+1) << ":\n";
                        bool_questions[1][i]->display();
                    
                        cout << "Your answer: ";
                        cin >> answer;
                    
                        if (bool_questions[1][i]->checkAnswer(answer)) {
                            cout << "Correct! +" << bool_questions[1][i]->getPoints() << " points\n";
                            p->addPoints(bool_questions[1][i]->getPoints());
                        } else {
                            cout << "Incorrect!\n";
                        }
                    }
                }
                cout << "\nQuiz complete! Final score: " << p->getScore() << "\n\n\n";
                break;
        }
    }
};

int main() {
    // Create quiz 
    Quiz quiz;

    // Math MCQ questions
    string mathMCQOptions[5][4] = {
            {"e^x^1/2", "e^x^1/2 / x^1/2", "e^x^1/2 / 2x^1/2 ", "2x^1/2*e^x^1"}, {"none", "a2 + 2ab + b2", "a2", "b2"},
            {"none", "a2 + 2ab + b2", "a2", "(a+b)(a-b)"}, {"1","5","1/5","0"},{"x^3","2x","1/x","x"}
    };
    
    MultipleChoiceQuestion math_mcq_q[5] = {
        MultipleChoiceQuestion("If y=e^x^1/2 then dy/dx:", 2, mathMCQOptions,0, 3),
        MultipleChoiceQuestion("(a+b)^2 = ", 2, mathMCQOptions,1, 2),
        MultipleChoiceQuestion("a2 - b2 = ", 2, mathMCQOptions,2, 4),
        MultipleChoiceQuestion("lim x to 0 sin5x / x = ?", 2, mathMCQOptions,3, 2),
        MultipleChoiceQuestion("What is the derivative of f(x)=x^2:", 2, mathMCQOptions,4, 2)
    };
    
    // Chemistry MCQ questions
    string chemMCQOptions[5][4] = {
            {"H2O", "C2O", "NO2", "CO"},{"Limestone","Bauxite","Granite","Lead"}, {"H2O", "C2O", "NO2", "CO"},
            {"Neon","Fluorine","Chlorine","Oxygen"}, {"Oxygen","Hydrogen","Sulphur","Nitrogen"}
    };
    
    MultipleChoiceQuestion chem_mcq_q[5] = {
        MultipleChoiceQuestion("Water = ", 2, chemMCQOptions,0, 1),
        MultipleChoiceQuestion("The most important Aluminium ore is?", 2, chemMCQOptions,1, 2),
        MultipleChoiceQuestion("Cabon monoxide = ", 2, chemMCQOptions,2, 4),
        MultipleChoiceQuestion("Which of the following non-metals is most electronegative?", 2, chemMCQOptions,3, 2),
        MultipleChoiceQuestion("Which of the following is commonly found in the acids?", 2, chemMCQOptions,4, 2),
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

    
    // Create player 1
    Player player1("Player1");
    // Start the quiz 
    quiz.start(&player1);


    // Create player 2
    Player player2("Player2");
    // Start the quiz 
    quiz.start(&player2);


    if(player1 > player2)
    { cout<<"\nPalyer 1 won the Quiz\n";
    }
    else if(player1 == player2){
        cout<<"\nTie\n";
    }
    else{
        cout<<"\nPalyer 2 won the Quiz\n"; 
    }

return 0;
}
