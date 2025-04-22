//сортировка сначала по должности, потом по зарплате с помощью гномьей сортировки.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

struct EmployeeData {
    std::string Surname;
    std::string Position;
    int DayOfBirth, MonthOfBirth, YearOfBirth;
    int WorkExperience;
    int Salary;
};

std::vector<EmployeeData> loadEmployeeData(const std::string& filename) {
    std::vector<EmployeeData> employeeData;
    std::ifstream file(filename);    
    try{  
        if (file.fail()) {
            throw std::runtime_error("Couldn't open the file");
        }
        std::string text;
        while (std::getline(file, text)) {
            std::istringstream iss(text);
            EmployeeData employee;
            std::string elem;
            //считываение значений            

            try {
                std::getline(iss, employee.Surname, ' ');
                std::getline(iss, employee.Position, ' ');
                std::getline(iss, elem, ' ');
                employee.DayOfBirth = std::stoi(elem);
                std::getline(iss, elem, ' ');
                employee.MonthOfBirth = std::stoi(elem);
                std::getline(iss, elem, ' ');
                employee.YearOfBirth = std::stoi(elem);
                std::getline(iss, elem, ' ');
                employee.WorkExperience = std::stoi(elem);
                std::getline(iss, elem, ' ');
                employee.Salary = std::stoi(elem);
                //сохранение объекта в вектор
                employeeData.push_back(employee);
            }
            catch (const std::invalid_argument&) { 
                std::cerr << "Invalid number format for employee: " << employee.Surname << std::endl;
                continue;
            }
            catch (const std::out_of_range&) {
                std::cerr << "Number out of range for employee: " << employee.Surname << std::endl;
                continue;
            }
        }
        file.close();
    }
    catch (const std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;       
    }
    return employeeData;
}

//сортирорка
std::vector<EmployeeData> gnomeSort(std::vector<EmployeeData>& dataToSort) {
    int index = 0;
    int size = dataToSort.size();

    while (index < size) {
        if (index == 0) {
            index++;
        }
        if (dataToSort[index].Position < dataToSort[index - 1].Position ||
            (dataToSort[index].Position == dataToSort[index - 1].Position &&
                dataToSort[index].Salary < dataToSort[index - 1].Salary)) {
            std::swap(dataToSort[index], dataToSort[index - 1]);
            index--;
        }
        else {
            index++;
        }
    }
    return dataToSort;
}

int main() {
    const std::string filename = "C:\\data.txt";    
    std::vector<EmployeeData> employees = loadEmployeeData(filename);  
    std::vector<EmployeeData> sortedEmployees = gnomeSort(employees);

    //вывод отсортированных данных 
    try {
        std::ofstream outFile("C:\\newfile4445.txt");
        if (!outFile.is_open()) {
            std::cerr << "Could not open output file!" << std::endl;
            return 1;
        }

        for (int i = 0; i < sortedEmployees.size(); i++) {
        outFile << sortedEmployees[i].Surname << " - "
            << sortedEmployees[i].Position << ", "
            << sortedEmployees[i].DayOfBirth << "/" << sortedEmployees[i].MonthOfBirth << "/" << sortedEmployees[i].YearOfBirth << ", "
            << sortedEmployees[i].WorkExperience << "  "
            << sortedEmployees[i].Salary << " " << std::endl;
        }
        std::cout << "The data has been saved to a file!";
        outFile.close();
    }
    catch (const std::runtime_error& ex) {
        std::cout << ex.what() << std::endl;
    }
    
    return 0;
}