# Project Title:
# QUIZ APP



Group Members: 

Areeba (24k-0596)

Aqsa (24k-0599)

Sila (24k-0703)

Submission Date:
20-04-2025

# 1. Executive Summary 
•	Overview: The project involved designing and implementing a quiz application using C++ with a focus on Object-Oriented Programming (OOP) principles. The application allowed users to select a subject and quiz type (Multiple Choice Questions or True/False) and then take turns answering questions. The system was built entirely without file handling and featured basic GUI-style console interactions to enhance user experience. Key OOP concepts such as classes, inheritance, and polymorphism were integrated into the project’s structure. Tools like Visual Studio and Visual Studio Code were used for development and testing. The main tasks included planning the structure, implementing core functionalities, and refining the program to be functional and engaging.

•	Key Findings: The project successfully demonstrated the practical use of OOP in C++. Core achievements included the effective use of inheritance, with specialized quiz types (MCQs and True/False) derived from a base Question class, and the use of virtual functions to implement polymorphism. The final application supported gameplay and flexible quiz topic selection—all without relying on file input/output. Additionally, the project helped solidify understanding of OOP concepts in a hands-on and meaningful way.

# 2. Introduction 
•	Background: This project was centered around creating a simple, interactive, file-less quiz application using C++ to demonstrate the practical implementation of Object-Oriented Programming (OOP) concepts. The project was particularly relevant in the context of learning OOP, as it provided an opportunity to apply theoretical knowledge such as class structures, inheritance, and polymorphism in a functional and engaging application. The added use of basic GUI-style elements through the console further enhanced the experience, making the quiz feel more intuitive and interactive.

•	Project Objective: 
1.	To develop a functional quiz application in C++
2.	To implement and demonstrate OOP concepts like inheritance, polymorphism, and encapsulation
3.	To allow quiz customization based on subject and question type (MCQs or True/False).
4.	To build a structured program using class hierarchies and modular code design through this project, the team aimed to bridge the gap between theoretical knowledge and practical programming in OOP.
   
# 3. Project Description 
•	Scope: The project included the following components and features:
1.	Support players to participate in the quiz.
2.	Subject selection for the quiz (e.g., Math, Science, etc.)
3.	Choice between different types of questions: Multiple Choice Questions (MCQs) and True/False.
4.	Display of questions and calculation of individual player scores.
5.	Use of object-oriented principles such as class design, inheritance, and polymorphism.

Exclusions from the project included advanced features such as file handling, persistent data storage, or graphical user interfaces beyond basic console output. The focus remained on keeping the project simple, functional, and educational.

•	Technical Overview: Microsoft Visual Studio and Visual Studio Code for coding, testing, and debugging. C++ as the programming language, chosen for its strong support of OOP concepts.

# 4. Methodology 
•	Approach: The team followed a collaborative and iterative development approach. Initially, the group discussed and finalized the project idea—a quiz app that demonstrates OOP concepts. Weekly discussions and updates helped track progress and ensure everyone was aligned. The work was divided based on components and class structures. Throughout development, the team stayed in communication, regularly sharing updates and seeking feedback. The group leader reviewed each completed section to provide input and maintain consistency across the project.

•	Roles and Responsibilities: 

o	Member 1: Was responsible for designing and implementing the core quiz logic, including the class structures, inheritance, and polymorphism features. This member handled the main functionality of the quiz flow and question management in the code.

o	Member 2: Focused on researching and implementing GUI-style console interactions to improve the user experience. Worked on visual elements like formatted output and user prompts.

o	Member 3: Also contributed to the research and implementation of GUI components, including screen organization, output readability, and overall presentation. Helped ensure the application felt interactive and clean from a user’s perspective.

# 5. Project Implementation 
•	Design and Structure: Used a question class with MCQ and TRUE/False as derived classes. Polymorphism was applied using virtual functions. 

•	Functionalities Developed:
o	Question class: 
1.	Display function to display question (purely virtual).
2.	Check answer function to check if the answer matches the correct answer for a particular question.(overridden in the derived classes)
o	Player class:  
1.	Stores name and score of the player
2.	Add points function increase score if answer is correct.

•	Challenges Faced: implementing GUI was challenging since it was our first time working with it but YouTube tutorials and online resources helped a lot. Since file handling was excluded, all data had to be managed in memory during runtime, which slightly limited question scalability but simplified debugging.


# 6. Results 
•	Project Outcomes: The quiz app worked as expected, allowing players to select subjects and question types. Scores were calculated and displayed successfully. OOP concepts like inheritance and polymorphism were clearly demonstrated.

•	Screenshots and Illustrations:

![image](https://github.com/user-attachments/assets/9b4e0922-0bd7-4ee2-a803-e0cbb0c388c9)

•	Testing and Validation: Tested multiple quiz sessions with different subjects and question types.
# 7. Conclusion 
• Summary of Findings: The project successfully demonstrated the use of OOP concepts in a functional quiz application. Inheritance and polymorphism were effectively utilized to handle different question types, and the player mode was fully operational, providing an interactive quiz experience.

• Final Remarks: This project offered valuable hands-on experience in applying OOP principles. While the scope was limited to a basic console interface, it laid a solid foundation for future development and improvement of more complex quiz system

