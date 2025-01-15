#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Defines the structure used for employee information
struct {
    char name[100];
    int ID;
    float salary;
    char department[50];
    int years_of_experience;
    float performance_score;
} typedef Employee;

//Function to add new employees to the list
Employee* addEmployee(Employee *employee, int *count) {

    //Increased for each new employee added
    *count += 1;
    employee = (Employee*) realloc(employee, (*count) * sizeof(Employee));

    getchar();

    printf("\nEnter name of employee: ");
    fgets(employee[*count - 1].name, sizeof(employee[*count - 1].name), stdin);

    size_t length = strlen(employee[*count - 1].name);
    if (length > 0 && employee[*count - 1].name[length - 1] == '\n') {
        employee[*count - 1].name[length - 1] = '\0';
    }

    printf("Enter employee ID: ");
    scanf("%d", &employee[*count - 1].ID);

    printf("Enter salary: ");
    scanf("%f", &employee[*count - 1].salary);

    printf("Enter department: ");
    scanf("%s", &employee[*count - 1].department);

    printf("Enter years of experience: ");
    scanf("%d", &employee[*count - 1].years_of_experience);

    //Calculates performance score
    employee[*count - 1].performance_score = 0.3 * employee[*count - 1].years_of_experience + 0.7 * employee[*count - 1].salary / 1000;

    return employee;

}

//Updates existing emplyees details
void updateEmployee(Employee *employee, int count) {

    int id;
    int id_match = 0;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i <= (count)-1; i++) {
        if (id == employee[i].ID) {
            printf("Enter new salary: ");
            scanf("%f", &employee[i].salary);
            printf("Enter new department: ");
            scanf("%s", &employee[i].department);

            //Recalculates performance score
            employee[i].performance_score = 0.3 * employee[i].years_of_experience + 0.7 * employee[i].salary / 1000;

            printf("\nEmployee information updated successfully!\n");

            id_match++;
            break;
        } 
    }

    if (id_match == 0){
        printf("No such ID found\n");
    }

}

//Sort employees by their performance score in descending order
void sortEmployeesByPerformance(Employee *employee, int count) {

    //Sorting function (Like a bubble sort)
    for (int i = 0; i <= (count)-1; i++) {
        
        for (int j = i + 1; j <= (count)-1; j++) {
            if (employee[i].performance_score < employee[j].performance_score) {
                int temp = employee[j].performance_score;
                employee[j].performance_score = employee[i].performance_score;
                employee[i].performance_score = temp;

            }
        }
    }
}

//Displays all employees information
void displayEmployees(Employee *employee, int count) {

    //Calls the sort employee function
    sortEmployeesByPerformance(employee, count);

    printf("\nEmployee Records (sorted by Performance Score): \n");

    for (int i = 0; i <= count - 1; i++) {
        printf("\nName: %s\n", employee[i].name);
        printf("Employee ID: %d\n", employee[i].ID);
        printf("Salary: %.2f\n", employee[i].salary);
        printf("Department: %s\n", employee[i].department);
        printf("Years of Experience: %d\n", employee[i].years_of_experience);
        printf("Performance Score: %.2f\n", employee[i].performance_score);
    }

}

//Function to search for an employee by any part of their name
void searchEmployee(Employee *employee, int count) {

    //Calls the sort employee function
    sortEmployeesByPerformance(employee, count);

    char nameSearch[100];
    int name_match = 0;

    printf("Enter name to search: ");
    scanf("%s", nameSearch);

    printf("\nSearch Results: \n");

    for (int i = 0; i <= count - 1; i++) { 
        if (strstr(employee[i].name, nameSearch) != NULL) {

            printf("\nName: %s\n", employee[i].name);
            printf("Employee ID: %d\n", employee[i].ID);
            printf("Salary: %.2f\n", employee[i].salary);
            printf("Department: %s\n", employee[i].department);
            printf("Years of Experience: %d\n", employee[i].years_of_experience);
            printf("Performance Score: %.2f\n", employee[i].performance_score);

            name_match++;
        }
    }

    if (name_match == 0){
        printf("No such name found\n");
    }

}

//Main function that runes the managment system
int main() {

    Employee *employee = NULL;
    int count = 0;

    while (1) {
        int choice;
        printf("\nEmployee Performance Management System\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Display All Employees\n");
        printf("4. Search Employee by Name\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting...\n");
            break;
        } else if (choice == 1) {
            employee = addEmployee(employee, &count);
        } else if (choice == 2) {
            updateEmployee(employee, count);
        } else if (choice == 3) {
            displayEmployees(employee, count);
        } else if (choice == 4) { 
            searchEmployee(employee, count);
        } else {
            printf("Enter a valid input!\n");
        }
    }

    free(employee);

    return 0;

}