#include <iostream>
#include <fstream>
#include <vector>
 /*Vectors are the dynamic arrays that are used to store data.It is different from arrays which store sequential data and are static in nature, 
Vectors provide more flexibility to the program. Vectors can adjust their size automatically when an element is inserted or deleted from it.*/
#include <string>
using namespace std;

// Task class to represent individual tasks
class Task {
public:
    string description;
    bool completed; //bool contains two element 1 for true and  0 for false.

    Task(const string& desc) : description(desc),  completed(false) {}
    /*Task(const string& desc): This is a constructor for the Task class, which takes a const string& desc parameter. 
    This parameter (desc) represents the description of the task that will be passed when creating a new Task object*/

    /* description(desc),- This line initializes the description member variable with the value passed to the constructor (desc). 
    This initialization happens before the body of the constructor ({}) executes.*/
    
    /*Initialization of completed: completed(false): Similarly, completed is another member variable of the Task class (likely declared as bool completed;). This line initializes the completed member variable with false.
     This indicates that by default, when a new Task object is created, it is initialized as not completed.*/

    // Method to mark task as completed
    void markCompleted() {
        completed = true;
    
    }

    // Method to get task details
    string getDetails() const {
        return (completed ? "[X] " : "[ ] ") + description;
    }
};

// TaskList class to manage a list of tasks
class TaskList {
private:
    vector<Task> tasks; //Declaration: This line declares a vector named tasks that holds objects of type Task
    string filename;

public:
    TaskList(const string& fname) : filename(fname) {
        loadTasks();
    }

    // Method to add a task
    void addTask(const string& desc) {
        tasks.emplace_back(desc); //emplace_back(desc) is a function that constructs a Task object directly in place at the end of the vector tasks,
        // using desc as the argument for the Task constructor.
        // This avoids the overhead of creating a temporary object and then copying or moving it into the vector.
        saveTasks();
    }

    // Method to mark a task as completed
    void completeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markCompleted();
            saveTasks();
        }
    }

    // Method to display all tasks
    void displayTasks() const {
        if (tasks.empty()) {
            cout << "No tasks found!" << endl;
        } else {
            for (size_t i = 0; i < tasks.size(); ++i) {
                cout << i + 1 << ". " << tasks[i].getDetails() << endl;
            }
        }
    }

private:
    // Method to load tasks from file
    void loadTasks() {
        ifstream infile(filename);
        if (!infile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string desc;
        while (getline(infile, desc)) {
            tasks.emplace_back(desc);
            string completed;
            getline(infile, completed);
            if (completed == "1") {
                tasks.back().markCompleted();
            }
        }
        infile.close();
    }

    // Method to save tasks to file
    void saveTasks() {
        ofstream outfile(filename);
        if (!outfile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        for (const auto& task : tasks) {
            outfile << task.description << endl;
            outfile << (task.completed ? "1" : "0") << endl;
        }
        outfile.close();
    }
};

// Main function to demonstrate the To-Do List
int main() {
    TaskList todoList("tasks.txt");
    int choice;
    string taskDescription;

    do {
        cout << "\n===== To-Do List =====\n";
        cout << "1. Add Task\n";
        cout << "2. Complete Task\n";
        cout << "3. Display Tasks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear buffer

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                getline(cin, taskDescription);
                todoList.addTask(taskDescription);
                break;
            case 2:
                int index;
                cout << "Enter task index to complete: ";
                cin >> index;
                todoList.completeTask(index - 1);
                break;
            case 3:
                todoList.displayTasks();
                break;
            case 4:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
