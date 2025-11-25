#include"iostream"
using namespace std;

class Course {
public:
    string courseCode;
    string courseName;
    int creditHours;
    int capacity;
    int enrolledStudents;

    Course(string c="", string n="", int ch=0, int cap=0) : courseCode(c), courseName(n), creditHours(ch),
                                                            capacity(cap), enrolledStudents(0) {}
    
    void display() {
        cout << "Course Code: " << courseCode << endl;
        cout << "Course Name: " << courseName << endl;
        cout << "Credit Hours: " << creditHours << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Enrolled Students: " << enrolledStudents << endl;
    }
};

class CourseNode {
public:
    Course data;
    CourseNode *left, *right;

    CourseNode(Course c): data(c), left(NULL), right(NULL) {}
};

class BST {
    CourseNode* root;

public:
    BST() : root(NULL) {}

    CourseNode* findMin(CourseNode* root) {
        if(!root) {
            cout << "Tree is empty\n";
            return NULL;
        }
        while(root->left) {
            root = root->left;
        }
        return root;
    }

    void insertCourse(CourseNode*& root, Course c) {
        if(root == NULL) {
            root =  new CourseNode(c);
            return;
        }
    
        if(c.courseCode < root->data.courseCode) {
            insertCourse(root->left, c);
        }
        else if(c.courseCode > root->data.courseCode) {
            insertCourse(root->right, c);
        }
        else {
            cout << "same val not allowed\n";
        }
    }

    CourseNode* search(CourseNode* root, Course key) {
        if(!root) {
            return NULL;
        }
        if(root->data.courseCode == key.courseCode) {
            return root;
        }
        if(key.courseCode < root->data.courseCode) 
            return search(root->left, key);
        else
            return search(root->right, key);
    }

    CourseNode* deleteNode(CourseNode* root, Course key) {
        if(!root) {
            cout << "Tree is empty\n";
            return NULL;
        }

        if(key.courseCode < root->data.courseCode) {
            root->left = deleteNode(root->left, key);
        }
        else if(key.courseCode > root->data.courseCode) {
            root->right = deleteNode(root->right, key);
        }
        else {
            // if no child
            if(!root->left && !root->right) {
                delete root;
                return NULL;
            }
            else if(!root->left) {  // only right child
                CourseNode* temp = root->right;
                delete root;
                return temp;
            } 
            else if(!root->right) {  // only left child
                CourseNode* temp = root->left;
                delete root;
                return temp;
            }
            else {   // both childs
                CourseNode* temp = findMin(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }  
        }
        return root;
    }

    void updateCourseCode(CourseNode*& root, string oldCode, string newCode) {
        // 1. Search node with oldCode
        CourseNode* node = root;
        while (node && node->data.courseCode != oldCode) {
            if (oldCode < node->data.courseCode) 
                node = node->left;
            else 
                node = node->right;
        }

        if (!node) {
            cout << "Course with code " << oldCode << " not found!\n";
            return;
        }

        // 2. Copy the course data
        Course updated = node->data;
        updated.courseCode = newCode;

        // 3. Delete old node
        Course temp(oldCode, "", 0, 0);  // only code matters for delete()
        root = deleteNode(root, temp);

        // 4. Insert updated course
        insertCourse(root, updated);

        cout << "Course code updated successfully!\n";
    }

    void inOrder(CourseNode* root) {
        if(!root) return;
        inOrder(root->left);
        root->data.display();
        inOrder(root->right);
    }
};

int main() {
    BST tree;
    CourseNode* root = NULL;   // root pointer for BST

    int choice;
    string code, name, oldCode, newCode;
    int ch, cap;

    while (true) {
        cout << "\n====== COURSE MANAGEMENT MENU ======\n";
        cout << "1. Insert Course\n";
        cout << "2. Search Course\n";
        cout << "3. Delete Course\n";
        cout << "4. Update Course Code\n";
        cout << "5. Display All Courses (InOrder)\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nEnter Course Code: ";
            cin >> code;
            cout << "Enter Course Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Credit Hours: ";
            cin >> ch;
            cout << "Enter Capacity: ";
            cin >> cap;

            Course c(code, name, ch, cap);
            tree.insertCourse(root, c);
            cout << "Course Inserted Successfully!\n";
        }

        else if (choice == 2) {
            cout << "\nEnter Course Code to Search: ";
            cin >> code;

            Course key(code, "", 0, 0);
            CourseNode* found = tree.search(root, key);

            if (found) {
                cout << "\nCourse Found:\n";
                found->data.display();
            } else {
                cout << "Course NOT found!\n";
            }
        }

        else if (choice == 3) {
            cout << "\nEnter Course Code to Delete: ";
            cin >> code;

            Course key(code, "", 0, 0);
            root = tree.deleteNode(root, key);

            cout << "Course Deleted (if existed).\n";
        }

        else if (choice == 4) {
            cout << "\nEnter Old Course Code: ";
            cin >> oldCode;
            cout << "Enter New Course Code: ";
            cin >> newCode;

            tree.updateCourseCode(root, oldCode, newCode);
        }

        else if (choice == 5) {
            cout << "\nAll Courses (Sorted by Course Code):\n";
            tree.inOrder(root);
        }

        else if (choice == 6) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}
