#include <iostream>
#include <string>
#include <exception>
using namespace std;

class invalid_argument : public exception {};
class runtime_error : public exception {};

// Base Task class
class Task {
public:
    string projectName;
    string dueDate;
    int priority;
public:
    Task(string project, string date, int prio)
    {
        projectName = project;
        dueDate = date;
        priority = prio;
    }
    virtual void display()
    {
        cout << "Project: " << projectName << endl;
        cout << "Due Date: " << dueDate << endl;
        cout << "Priority: " << priority << endl;
    }
    string getDueDate() const
    {
        return dueDate;
    }
    int getPriority() const
    {
        return priority;
    }
};

// Derived class from Task class
class ExtendedTask : public Task
{
private:
    string assignee;
public:
    ExtendedTask(string project, string date, int prio, string assign) : Task(project, date, prio)
    {
        assignee = assign;
    }
    void display() //override
    {
        Task::display();
        cout << "Assignee: " << assignee << endl;
    }
};

// Linked List Node
template <class T>
class Node {
public:
    T* data;
    Node<T>* next;
    Node(T* item)
    {
        data = item;
        next = nullptr;
    }
};

// Task Manager class
class TaskManager {
private:
    Node<Task>* head;
public:
    TaskManager()
    {
        head = nullptr;
    }
    void addTask(Task* task)
    {
        Node<Task>* newNode = new Node<Task>(task);
        if (head == nullptr)
        {
            head = newNode;
        }
        else {
            Node<Task>* currNode = head;
            while (currNode->next != nullptr)
            {
                currNode = currNode->next;
            }
            currNode->next = newNode;
        }
        cout << "Task added successfully." << endl;
    }
    void deleteTask(string projectName)
    {
        if (head == nullptr) {
            cout << "No tasks to delete." << endl;
            return;
        }

        Node<Task>* currNode = head;
        Node<Task>* prevNode = nullptr;
        while (currNode != nullptr)
        {
            if (currNode->data->projectName == projectName)
            {
                if (prevNode == nullptr)
                {
                    head = currNode->next;
                }
                else
                {
                    prevNode->next = currNode->next;
                }
                delete currNode->data;
                delete currNode;
                cout << "Task deleted successfully." << endl;
                return;
            }
            prevNode = currNode;
            currNode = currNode->next;
        }
        cout << "Task not found." << endl;
    }
    void displayTasks() {
        if (head == nullptr) {
            throw std::runtime_error();
            return;
        }
        Node<Task>* currNode = head;
        while (currNode != nullptr) {
            currNode->data->display();
            cout << endl;
            currNode = currNode->next;
        }
    }
    void searchTaskByDueDate(string dueDate) {
        if (head == nullptr)
        {
            cout << "No tasks to search." << endl;
            return;
        }
        Node<Task>* currNode = head;
        bool found = false;
        while (currNode != nullptr)
        {
            if (currNode->data->getDueDate() == dueDate)
            {
                currNode->data->display();
                cout << endl;
                found = true;
            }
            currNode = currNode->next;
        }
        if (!found)
        {
            cout << "Task not found." << endl;
        }
    }
    void searchTaskByPriority(int priority)
    {
        if (head == nullptr)
        {
            cout << "No tasks to search." << endl;
            return;
        }
        Node<Task>* currNode = head;
        bool found = false;
        while (currNode != nullptr)
        {
            if (currNode->data->getPriority() == priority)
            {
                currNode->data->display();
                cout << endl;
                found = true;
            }
            currNode = currNode->next;
        }
        if (!found) {
            cout << "No tasks found." << endl;
        }
    }
    ~TaskManager()
    {
        Node<Task>* currNode = head;
        while (currNode != nullptr)
        {
            Node<Task>* nextNode = currNode->next;
            delete currNode->data;
            delete currNode;
            currNode = nextNode;
        }
    }
};

//main function
int main() {
    int z;
    TaskManager taskManager;
    cout << "Choice 1 - To create new project " << endl;
    cout << "Choice 2 - To delete existing project" << endl;
    cout << "Choice 3 - To display All projects " << endl;
    cout << "Choice 4 - To Search existing project by Due Date" << endl;
    cout << "Choice 5 - To Search existing project by its priority " << endl;
    cout << "Choice 6 - To exit from portal" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    do {
        z = 0;

        try
        {
            while (1)
            {
                cout << "Enter your choice: ";
                int choice;
                cin >> choice;
                switch (choice) {
                case 1: {
                    cout << "Enter project name: ";
                    string project;
                    cin >> project;
                    cout << "Enter due date: ";
                    string date;
                    cin >> date;
                    cout << "Enter priority: ";
                    int priority;
                    cin >> priority;
                    if (cin.fail())
                        throw std::runtime_error();
                    cout << "Enter the name , who has assigned with this project";
                    string assignee;
                    cin >> assignee;
                    Task* task;
                    if
                        (assignee.empty())
                    {
                        task = new Task(project, date, priority);
                    }
                    else {
                        task = new ExtendedTask(project, date, priority, assignee);
                    }
                    taskManager.addTask(task);
                    break;
                }
                case 2: {
                    cout << "Enter project name to delete: ";
                    string project;
                    cin >> project;
                    taskManager.deleteTask(project);
                    break;
                }
                case 3: {
                    taskManager.displayTasks();
                    break;
                }
                case 4: {
                    cout << "Enter due date to search: ";
                    string dueDate;
                    cin >> dueDate;
                    taskManager.searchTaskByDueDate(dueDate);
                    break;
                }
                case 5: {
                    cout << "Enter priority to search: ";
                    int priority;
                    cin >> priority;
                    if (cin.fail())
                        throw std::runtime_error();
                    taskManager.searchTaskByPriority(priority);
                    break;
                }
                case 6: {
                    cout << "Exiting program..." << endl;
                    return 0;
                }
                default:
                    if (choice < 1 || choice > 6)
                        throw std::invalid_argument();
                    break;
                }
            }
        }
        catch (std::invalid_argument &i)
        {
            cout << "Error: Invalid choice. Please enter a choice between 1-6 only." << endl;
            z = 1;
        }
        catch (std::runtime_error &r)
        {
            cout << "Error: No task is added to display. Please add some tasks by entering choice 1." << endl;
            z = 1;
        }
        catch (exception &e)
        {
            cout << "Error: An error occurred while reading the input. Please check the data type (priority = integer, rest all are strings)." << endl;
        }
        catch (...)
        {
            cout << "An unknown error occurred during execution." << endl;
        }
    } while (z);
}
