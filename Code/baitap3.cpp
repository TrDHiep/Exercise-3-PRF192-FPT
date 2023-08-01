#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMPLOYEES 100
#define EMPLOYEE_FILE_PATH "D:\\emp.txt"
#define OUTPUT_FILE_PATH "D:\\3020\\hiep.txt"

struct Employee {
    char id[5];
    char name[50];
    float salary;
};

void loadEmployees(struct Employee empList[], int *numEmployees) {
    FILE *file = fopen(EMPLOYEE_FILE_PATH, "r");
    if (file == NULL) {
        printf("Error opening file to load employees.\n");
        exit(1);
    }

    char line[100];
    fgets(line, sizeof(line), file); // Skip header line

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%s\t%s\t%f", empList[*numEmployees].id, empList[*numEmployees].name, &empList[*numEmployees].salary);
        (*numEmployees)++;
    }

    fclose(file);
}

void saveEmployees(struct Employee empList[], int numEmployees) {
    FILE *file = fopen(EMPLOYEE_FILE_PATH, "w");
    if (file == NULL) {
        printf("Error opening file to save employees.\n");
        return;
    }

    fprintf(file, "EmID\tEmName\tEmsalaryLevel\n");
    for (int i = 0; i < numEmployees; i++) {
        fprintf(file, "%s\t%s\t%.2f\n", empList[i].id, empList[i].name, empList[i].salary);
    }

    fclose(file);
}

void addEmployee(struct Employee empList[], int *numEmployees) {
    if (*numEmployees >= MAX_EMPLOYEES) {
        printf("Employee list is full. Cannot add more employees.\n");
        return;
    }

    struct Employee emp;
    printf("Enter the ID of the employee (Axxx): ");
    scanf("%s", emp.id);

    // Check if ID matches the pattern
    if (strlen(emp.id) != 4 || emp.id[0] != 'A' || !isdigit(emp.id[1]) || !isdigit(emp.id[2]) || !isdigit(emp.id[3])) {
        printf("Invalid ID format. Please enter in the format Axxx (xxx: 001-999).\n");
        return;
    }

    // Check if ID already exists
    for (int i = 0; i < *numEmployees; i++) {
        if (strcmp(empList[i].id, emp.id) == 0) {
            printf("Employee with the same ID already exists. Cannot add employee.\n");
            return;
        }
    }

    printf("Enter the name of the employee: ");
    scanf("%s", emp.name);

    while (1) {
        printf("Enter the salary of the employee (0.0 - 7.0): ");
        if (scanf("%f", &emp.salary) == 1 && emp.salary >= 0.0 && emp.salary <= 7.0) {
            break;
        } else {
            printf("Invalid salary. Please enter a value between 0.0 and 7.0.\n");
            while (getchar() != '\n');
        }
    }

    empList[*numEmployees] = emp;
    (*numEmployees)++;

    saveEmployees(empList, *numEmployees);

    printf("Employee added successfully.\n");
}

void deleteEmployee(struct Employee empList[], int *numEmployees) {
	if (*numEmployees == 0) {
        printf("No employees to delete.\n");
        return;
    }

    else {
    	char deleteId[5];

	    printf("Enter the ID of the employee to delete: ");
	    scanf("%s", deleteId);
	
	    int found = 0;
	    for (int i = 0; i < *numEmployees; i++) {
	        if (strcmp(empList[i].id, deleteId) == 0) {
	            found = 1;
	
	            // Shift elements to fill the gap
	            for (int j = i; j < *numEmployees - 1; j++) {
	                empList[j] = empList[j + 1];
	            }
	
	            (*numEmployees)--;
	            saveEmployees(empList, *numEmployees);
	
	            printf("Employee deleted successfully.\n");
	            break;
	        }
	    }
	
	    if (!found) {
	        printf("Invalid ID or employee not found.\n");
	    }
	}


}

int findEmployeeByID(struct Employee e[], int n, const char* id) {
    for (int i = 0; i < n; i++) {
        if (strcmp(e[i].id, id) == 0) {
            return i; // Return the index of the matching employee
        }
    }
    return -1; // Return -1 if employee is not found
}

void updateName(struct Employee e[], int n) {
    char id[4];
    printf("Enter the ID of the employee: ");
    scanf("%s", id);

    int index = findEmployeeByID(e, n, id);
    if (index != -1) {
        printf("Enter the new name: ");
        scanf("%s", e[index].name);
        printf("Name updated successfully!\n");
    } else {
        printf("Employee not found!\n");
    }
}

void updateSalary(struct Employee e[], int n) {
    char id[4];
    printf("Enter the ID of the employee: ");
    scanf("%s", id);

    int index = findEmployeeByID(e, n, id);
    if (index != -1) {
        float newSalary;
        printf("Enter the new salary: ");
        if (scanf("%f", &newSalary) != 1 || newSalary < 0.0 || newSalary > 7.0) {
            printf("Invalid salary! Please enter a value between 0.0 and 7.0.\n");
        } else {
            e[index].salary = newSalary;
            printf("Salary updated successfully!\n");
        }
    } else {
        printf("Employee not found!\n");
    }
}

void updateAll(struct Employee e[], int n) {
    char id[4];
    printf("Enter the ID of the employee: ");
    scanf("%s", id);

    int index = findEmployeeByID(e, n, id);
    if (index != -1) {
        float newSalary;
        printf("Enter the new salary: ");
        if (scanf("%f", &newSalary) != 1 || newSalary < 0.0 || newSalary > 7.0) {
            printf("Invalid salary! Please enter a value between 0.0 and 7.0.\n");
        } else {
            printf("Enter the new name: ");
            scanf("%s", e[index].name);
            e[index].salary = newSalary;
            printf("Name and salary updated successfully!\n");
        }
    } else {
        printf("Employee not found!\n");
    }
}

void update(struct Employee e[], int n) {
    int choice;
    printf("1. Update Name\n");
    printf("2. Update Salary\n");
    printf("3. Update All\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            updateName(e, n);
            break;
        case 2:
            updateSalary(e, n);
            break;
        case 3:
            updateAll(e, n);
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }
}

void findEmployee(struct Employee empList[], int numEmployees) {
    if (numEmployees == 0) {
        printf("No employees to find.\n");
        return;
    }

    int choice;
    printf("Find employee by:\n");
    printf("1. ID\n");
    printf("2. Name\n");
    printf("3. Show All\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: {
            char searchId[5];
            printf("Enter the ID of the employee to find: ");
            scanf("%s", searchId);

            int found = 0;
            for (int i = 0; i < numEmployees; i++) {
                if (strcmp(empList[i].id, searchId) == 0) {
                    found = 1;
                    printf("Employee found:\n");
                    printf("ID: %s\n", empList[i].id);
                    printf("Name: %s\n", empList[i].name);
                    printf("Salary: %.2f\n", empList[i].salary);
                    break;
                }
            }

            if (!found) {
                printf("Employee not found.\n");
            }
            break;
        }
        case 2: {
            char searchName[50];
            printf("Enter the name of the employee to find: ");
            scanf("%s", searchName);

            int found = 0;
            for (int i = 0; i < numEmployees; i++) {
                if (strcmp(empList[i].name, searchName) == 0) {
                    found = 1;
                    printf("Employee found:\n");
                    printf("ID: %s\n", empList[i].id);
                    printf("Name: %s\n", empList[i].name);
                    printf("Salary: %.2f\n", empList[i].salary);
                }
            }

            if (!found) {
                printf("No employees with the name '%s'.\n", searchName);
            }
            break;
        }
        case 3:
            printf("All employees:\n");
            for (int i = 0; i < numEmployees; i++) {
                printf("ID: %s\n", empList[i].id);
                printf("Name: %s\n", empList[i].name);
                printf("Salary: %.2f\n", empList[i].salary);
                printf("\n");
            }
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
    }

    // Check if there are no more employees after find operation
    if (numEmployees == 0) {
        printf("No more employees to find.\n");
        return;
    }
}

void sortEmployees(struct Employee empList[], int numEmployees) {
    if (numEmployees == 0) {
        printf("No employees to sort.\n");
        return;
    }

    // Sort the employees based on salary level
    for (int i = 0; i < numEmployees - 1; i++) {
        for (int j = 0; j < numEmployees - i - 1; j++) {
            if (empList[j].salary > empList[j + 1].salary) {
                // Swap employees
                struct Employee temp = empList[j];
                empList[j] = empList[j + 1];
                empList[j + 1] = temp;
            }
        }
    }

    printf("Employees sorted successfully.\n");

    // Check if there are no more employees after sorting
    if (numEmployees == 0) {
        printf("No more employees to sort.\n");
        return;
    }
}

void writeStatistics(struct Employee empList[], int numEmployees) {
    if (numEmployees == 0) {
        printf("No employees to generate statistics.\n");
        return;
    }

    FILE *file = fopen(OUTPUT_FILE_PATH, "w");
    if (file == NULL) {
        printf("Error opening file to write statistics.\n");
        return;
    }

    // Total number of employees
    fprintf(file, "Total number of employees: %d\n", numEmployees);

    // Employees with the same name
    fprintf(file, "Employees with the same name:\n");
    for (int i = 0; i < numEmployees; i++) {
        int sameName = 0;
        for (int j = 0; j < numEmployees; j++) {
            if (i != j && strcmp(empList[i].name, empList[j].name) == 0) {
                sameName = 1;
                break;
            }
        }
        if (sameName) {
            fprintf(file, "ID: %s\n", empList[i].id);
        }
    }

    // Employees with maximum salary level
    float maxSalary = empList[0].salary;
    for (int i = 1; i < numEmployees; i++) {
        if (empList[i].salary > maxSalary) {
            maxSalary = empList[i].salary;
        }
    }

    fprintf(file, "Employees with maximum salary level:\n");
    for (int i = 0; i < numEmployees; i++) {
        if (empList[i].salary == maxSalary) {
            fprintf(file, "ID: %s, Name: %s\n", empList[i].id, empList[i].name);
        }
    }

    fclose(file);

    printf("Statistics written to file.\n");

    // Check if there are no more employees after generating statistics
    if (numEmployees == 0) {
        printf("No more employees to generate statistics.\n");
        return;
    }
}

void menu(int *numEmployees) {
    if (*numEmployees == 0){
    	printf("===============================================================\n");
	    printf("|                     Employee Management System              |\n");
	    printf("|-------------------------------------------------------------|\n");
	    printf("| 1. Add an employee                                          |\n");
	    printf("| 0. Exit                                                     |\n");
	    printf("|-------------------------------------------------------------|\n");
	    printf("===============================================================\n");
	    printf("Enter your choice: ");
	}
	else{
		printf("===============================================================\n");
	    printf("|                     Employee Management System              |\n");
	    printf("|-------------------------------------------------------------|\n");
	    printf("| 1. Add an employee                                          |\n");
	    printf("| 2. Delete an employee                                       |\n");
	    printf("| 3. Update an employee                                       |\n");
	    printf("| 4. Find employee                                            |\n");
	    printf("| 5. Sort employees                                           |\n");
	    printf("| 6. Write statistics                                         |\n");
	    printf("| 0. Exit                                                     |\n");
	    printf("|-------------------------------------------------------------|\n");
	    printf("===============================================================\n");
	    printf("Enter your choice: ");
	}
}


int main() {
    struct Employee empList[MAX_EMPLOYEES];
    int numEmployees = 0;

    // Load existing employees from file
    loadEmployees(empList, &numEmployees);

int choice;

    do {
        menu(&numEmployees);
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printf("Exiting the Employee Management System. Goodbye!\n");
                break;
            case 1:
                addEmployee(empList, &numEmployees);
                break;
            case 2:
                deleteEmployee(empList, &numEmployees);
                break;
            case 3:
                update(empList, numEmployees);
                break;
            case 4:
                findEmployee(empList, numEmployees);
                break;
            case 5:
                sortEmployees(empList, numEmployees);
                break;
            case 6:
                writeStatistics(empList, numEmployees);
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
                break;
        }

        if (choice != 0) {
            printf("\nPress Enter (or any key) to continue or 0 to go back to the menu...");
            while (getchar() != '\n');
            char ch = getchar();
            if (ch == '0') {
                continue;
            }
        }

    } while (choice != 0);

    // Save the updated employees to file before exiting
    saveEmployees(empList, numEmployees);

    return 0;
}

