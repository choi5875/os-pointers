// compile: g++ -std=c++14 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <limits>


typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    double average;


    std::cout << "Please enter the student's id number: ";
    student.id = promptInt("", 0, 999999999);
    std::cout << student.id << "\n" << std::endl;


  
    std::string f_name_str;
    while (true) {
        std::cout << "Please enter the student's first name: ";
        std::cin >> f_name_str;
        bool valid = !f_name_str.empty();
        for (char c : f_name_str) {
            if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')) {
                valid = false;
                break;
            }
        }
        if (valid) {
            std::cout << f_name_str << "\n" << std::endl;
            break;
        }
        std::cout << "Sorry, I cannot understand your answer" << std::endl;
    }
    student.f_name = new char[f_name_str.length() + 1];
    std::strcpy(student.f_name, f_name_str.c_str());


    std::string l_name_str;
    while (true) {
        std::cout << "Please enter the student's last name: ";
        std::cin >> l_name_str;
        bool valid = !l_name_str.empty();
        for (char c : l_name_str) {
            if (!(c >= 'A' && c <= 'Z') && !(c >= 'a' && c <= 'z')) {
                valid = false;
                break;
            }
        }
        if (valid) {
            std::cout << l_name_str << "\n" << std::endl;
            break;
        }
        std::cout << "Sorry, I cannot understand your answer" << std::endl;
    }
    student.l_name = new char[l_name_str.length() + 1];
    std::strcpy(student.l_name, l_name_str.c_str());

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Please enter how many assignments were graded: ";
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        int value;
        char extra;
        if (!(ss >> value) || (ss >> extra) || value < 1 || value > 134217728) {
            std::cout << line << std::endl;
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            std::cout << "Please enter how many assignments were graded: ";
            continue;
        }
        student.n_assignments = value;
        std::cout << value << "\n" << std::endl;
        break;
    }

    student.grades = new double[student.n_assignments];

    for (int i = 0; i < student.n_assignments; ++i) {
        while (true) {
            std::cout << "Please enter grade for assignment " << i << ": ";
            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            double value;
            char extra;
            if (!(ss >> value) || (ss >> extra) || value < 0.0 || value > 1000.0) {
                std::cout << line << std::endl;
                std::cout << "Sorry, I cannot understand your answer" << std::endl;
                continue;
            }
            student.grades[i] = value;
            std::cout << value << "\n" << std::endl;
            break;
        }
    }
    std::cout << std::endl;

    calculateStudentAverage(&student, &average);

    std::cout << "Student: " << student.f_name << " " << student.l_name << " [" << student.id << "]" << std::endl;
    std::cout << "  Average grade: " << std::fixed << std::setprecision(1) << average << std::endl;

    delete[] student.f_name;
    delete[] student.l_name;
    delete[] student.grades;

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    int value;
    bool first = true;
    while (true) {
        if (first && !message.empty()) {
            std::cout << message;
            first = false;
        }
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            if (!message.empty()) std::cout << message;
            continue;
        }
        std::stringstream ss(line);
        char extra;
        if (!(ss >> value) || (ss >> extra) || value < min || value > max) {
            std::cout << "Sorry, I cannot understand your answer\n";
            if (!message.empty()) std::cout << message;
            continue;
        }
        return value;
    }
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    double value;
    bool first = true;
    while (true) {
        if (first && !message.empty()) {
            std::cout << message;
            first = false;
        }
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) {
            if (!message.empty()) std::cout << message;
            continue;
        }
        std::stringstream ss(line);
        char extra;
        if (!(ss >> value) || (ss >> extra) || value < min || value > max) {
            std::cout << "Sorry, I cannot understand your answer\n";
            if (!message.empty()) std::cout << message;
            continue;
        }
        return value;
    }
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    Student *student = (Student *)object;
    double sum = 0.0;
    for (int i = 0; i < student->n_assignments; ++i) {
        sum += student->grades[i];
    }
    if (student->n_assignments > 0)
        *avg = sum / student->n_assignments;
    else
        *avg = 0.0;
}
