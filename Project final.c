#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

/// Patient Management
void registerPatient() {
    FILE *file = fopen("patients.txt", "a");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }
    fseek(file, -1, SEEK_END);
    char lastChar = fgetc(file);
    if (lastChar !='\n') {
        fprintf(file,"\n");
    }

    int id, age;
    char name[MAX_PATIENTS];
    char gender[MAX_PATIENTS];

    printf("Enter Patient ID: ");
    scanf("%d", &id);

    printf("Enter Patient Name: ");
    scanf(" %[^\n]s", name);

    printf("Enter Patient Age: ");
    scanf("%d", &age);

    printf("Enter Patient Gender: ");
    scanf("%s", gender);

    fprintf(file, "%d,%s,%d,%s\n", id, name, age, gender);
    fclose(file);
    printf("Patient registered successfully and saved to file!\n");
}

void displayPatientByID() {
    FILE *file = fopen("patients.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file. Make sure patients.txt exists.\n");
        return;
    }

    int searchID;
    printf("Enter Patient ID to search: ");
    scanf("%d", &searchID);

    int id, age;
    char name[MAX_PATIENTS];
    char gender[MAX_PATIENTS];
    int found = 0;

    while (fscanf(file, "%d,%[^,],%d,%s\n", &id, name, &age, gender) != EOF) {
        if (id == searchID) {
            printf("\nPatient Details:\n");
            printf("ID: %d\nName: %s\nAge: %d\nGender: %s\n", id, name, age, gender);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Patient with ID %d not found.\n", searchID);
    }

    fclose(file);
}


// Appointment Segment
typedef struct {
    int patientId;
    char date[20];
    char time[10];
} Appointment;

Appointment apnts[MAX_PATIENTS];/*apnts=Appoinmenments*/
int apntCount = 0;/*apntCount=Appoinmenment_Count*/

/* Function to save appointments to a text file */
void saveAppointmentsToFile() {
    FILE *file = fopen("appointments.txt", "w");
    if (file == NULL) {
        perror("Error saving appointments");
        return;
    }
    for (int i = 0; i < apntCount; i++) {
        fprintf(file, "%d,%s,%s\n",
                apnts[i].patientId, apnts[i].date, apnts[i].time);/*apnts=Appoinmenments apntCount=Appoinmenment_Count*/
    }
    fclose(file);
}

/* Function to load appointments from a text file */
void loadAppointmentsFromFile() {
    FILE *file = fopen("appointments.txt", "r");
    if (file == NULL) {
        return;
    }
    while (fscanf(file, "%d,%19[^,],%9s\n",
                  &apnts[apntCount].patientId, apnts[apntCount].date,/*apnts=Appoinmenments apntCount=Appoinmenment_Count*/
                  apnts[apntCount].time) == 3) {
        apntCount++;
    }
    fclose(file);
}

/* Appointment functions in Segment parts */
void scheduleAppointment() {
    if (apntCount < MAX_PATIENTS) {
        printf("Please Enter Patient ID for appointment: ");
        scanf("%d", &apnts[apntCount].patientId);/*apnts=Appoinmenments apntCount=Appoinmenment_Count*/
        printf("Enter Appointment Date (DD-MM-YYYY): ");
        scanf("%s", apnts[apntCount].date);/*apnts=Appoinmenments apntCount=Appoinmenment_Count*/
        printf("Enter Appointment Time (HH-MM)or(HH:MMam/pm): ");
        scanf("%s", apnts[apntCount].time);/*apnts=Appoinmenments apntCount=Appoinmenment_Count*/
        apntCount++;
        saveAppointmentsToFile();
        printf("Appointment scheduled successfully!\n");
    } else {
        printf("Appointment limit reached!\n");
    }
}

void displayAppointments() {
    if (apntCount == 0) {
        printf("No appointments scheduled.\n");
        return;
    }
    printf("\nScheduled Appointments:\n");
    for (int i = 0; i < apntCount; i++) {
        printf("Patient ID: %d , Date: %s , Time: %s \n",
               apnts[i].patientId, apnts[i].date, apnts[i].time);
    }
}


/// Doctor Segment
typedef struct {
    int doctorId;
    char name[100];
    char specialization[100];
} Doctor;

Doctor doctors[MAX_PATIENTS];
int doctorCount = 0;

// Function to save doctors to a text file
void saveDoctorsToFile() {
    FILE *file = fopen("doctors.txt", "a");
    if (file == NULL) {
        perror("Error saving doctors");
        return;
    }
    for (int i = 0; i < doctorCount; i++) {
        fprintf(file, "%d,%s,%s\n",
                doctors[i].doctorId, doctors[i].name, doctors[i].specialization);
    }
    fclose(file);
}

// Function to load doctors from a text file
void loadDoctorsFromFile() {
    FILE *file = fopen("doctors.txt", "r");
    if (file == NULL) {
        return;
    }
    while (fscanf(file, "%d,%99[^,],%99s\n",
                  &doctors[doctorCount].doctorId, doctors[doctorCount].name,
                  doctors[doctorCount].specialization) == 3) {
        doctorCount++;
    }
    fclose(file);
}

// Doctor functions
void addDoctor() {
    if (doctorCount < MAX_PATIENTS) {
        printf("Enter Doctor ID: ");
        scanf("%d", &doctors[doctorCount].doctorId);
        getchar();

        printf("Enter Doctor Name: ");
        scanf(" %[^\n]s", doctors[doctorCount].name);

        printf("Enter Doctor Specialization: ");
        scanf(" %[^\n]s", doctors[doctorCount].specialization);

        doctorCount++;
        saveDoctorsToFile();
        printf("Doctor added successfully!\n");
    } else {
        printf("Doctor limit reached!\n");
    }
}

void displayDoctors() {
    if (doctorCount == 0) {
        printf("No doctors registered.\n");
        return;
    }
    printf("\nRegistered Doctors:\n");
    for (int i = 0; i < doctorCount; i++) {
        printf("Doctor ID: %d, Name: %s, Specialization: %s\n",
               doctors[i].doctorId, doctors[i].name, doctors[i].specialization);
    }
}

/// Billing Segment
typedef struct {
    int patientId;
    float amount;
} Billing;

Billing billings[MAX_PATIENTS];
int billingCount = 0;

// Function to save billing data to a text file
void saveBillsToFile() {
    FILE *file = fopen("billings.txt", "a");
    if (file == NULL) {
        perror("Error saving bills");
        return;
    }
    for (int i = 0; i < billingCount; i++) {
        fprintf(file, "%d,%.2f\n", billings[i].patientId, billings[i].amount);
    }
    fclose(file);
}

// Function to load billing data from a text file
void loadBillsFromFile() {
    FILE *file = fopen("billings.txt", "r");
    if (file == NULL) {
        return;
    }
    while (fscanf(file, "%d,%f\n", &billings[billingCount].patientId,
                  &billings[billingCount].amount) == 2) {
        billingCount++;
    }
    fclose(file);
}

// Billing functions
void addBill() {
    if (billingCount < MAX_PATIENTS) {
        printf("Enter Patient ID for billing: ");
        scanf("%d", &billings[billingCount].patientId);
        printf("Enter Amount: ");
        scanf("%f", &billings[billingCount].amount);
        billingCount++;
        saveBillsToFile();
        printf("Billing information added successfully!\n");
    } else {
        printf("Billing limit reached!\n");
    }
}

void displayBills() {
    if (billingCount == 0) {
        printf("No billing information available.\n");
        return;
    }
    printf("\nBilling Information:\n");
    for (int i = 0; i < billingCount; i++) {
        printf("Patient ID: %d, Amount: %.2f\n",
               billings[i].patientId, billings[i].amount);
    }
}

/// Main Menu and Main Function
void menu() {
    int choice;
    do {
        printf("\nHospital Management System\n");
        printf("1. Register Patient\n");
        printf("2. Display Patient by ID\n");
        printf("3. Schedule Appointment\n");
        printf("4. Display Appointments\n");
        printf("5. Add Doctor\n");
        printf("6. Display Doctors\n");
        printf("7. Add Bill\n");
        printf("8. Display Bills\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: registerPatient(); break;
            case 2: displayPatientByID(); break;
            case 3: scheduleAppointment(); break;
            case 4: displayAppointments(); break;
            case 5: addDoctor(); break;
            case 6: displayDoctors(); break;
            case 7: addBill(); break;
            case 8: displayBills(); break;
            case 9: printf("Exiting...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
}

int main() {

    loadAppointmentsFromFile();
    loadDoctorsFromFile();
    loadBillsFromFile();

    menu();
    return 0;
}

