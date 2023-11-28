#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_SEATS 50
#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 14
#define TICKET_PRICE 700.0
#define MAX_BOOKINGS 100

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int userCount = 0;

struct Reservation {
    int seat_number;
    char passenger_name[50];
    int is_reserved;
    float ticket_price;
};

struct Reservation bus[MAX_SEATS];

struct BookingHistory {
    int seat_number;
    char passenger_name[50];
    float ticket_price;
    char date[20];
};

struct BookingHistory bookingHistory[MAX_BOOKINGS];
int bookingCount = 0;

struct BusInfo {
    char bus_number[15];
    char departure_time[20];
    char destination[50];
    char current_date[10];  
    char source[50];         // New attribute: source
    float ticket_price;
};

struct BusInfo busDetails[MAX_SEATS];
int busCount = 0;

void initializeBus();
void displayBus();
void reserveSeat();
void setBusDetails();
void displayBusDetails();
void writeBusDetailsToFile();
void readBusDetailsFromFile();
void createTicket(int seat);
int createUser();
void modifyBusDetails();
void deleteReservation();
void cancelBooking();

// Function to initialize the bus
void initializeBus() {
    int i;
    for (i = 0; i < MAX_SEATS; i++) {
        bus[i].seat_number = i + 1;
        bus[i].is_reserved = 0;
        strcpy(bus[i].passenger_name, "Available");
        bus[i].ticket_price = 0.0;
    }
}

// Display available seats
void displayBus() {
    printf("Seat Number\tPassenger Name\tTicket Price\n");
    int i;
    for (i = 0; i < MAX_SEATS; i += 4) {
        int j;
        for (j = 0; j < 4 && i + j < MAX_SEATS; j++) {
            printf("%d\t\t%s\t\t%.2f\n", bus[i + j].seat_number, bus[i + j].passenger_name, bus[i + j].ticket_price);
        }
        printf("\n");
    }
}

// Reserve a seat
void reserveSeat() {
    int seat;
    printf("Enter the seat number you want to reserve: ");
    scanf("%d", &seat);

    if (seat < 1 || seat > MAX_SEATS) {
        printf("Invalid seat number. Please choose a seat between 1 and %d.\n", MAX_SEATS);
        return;
    }

    if (bus[seat - 1].is_reserved) {
        printf("Seat %d is already reserved.\n", seat);
    } else {
        printf("Enter passenger name: ");
        scanf("%s", bus[seat - 1].passenger_name); // Should use %s instead of missing & for string input
        bus[seat - 1].is_reserved = 1;
        bus[seat - 1].ticket_price = TICKET_PRICE;

        printf("\nSeat %d reserved for %s.\n", seat, bus[seat - 1].passenger_name);
        printf("Ticket Price: Ksh%.2f\n", bus[seat - 1].ticket_price); // Removed unnecessary '=='
    }
}

// Set bus details
void setBusDetails() {
    printf("Enter bus number: ");
    scanf("%s", busDetails[busCount].bus_number);

    printf("Enter departure time: ");
    scanf("%s", busDetails[busCount].departure_time);

    printf("Enter destination: ");
    scanf("%s", busDetails[busCount].destination);

    printf("Enter source: ");
    scanf("%s", busDetails[busCount].source);

    printf("Enter ticket price: ");
    scanf("%f", &busDetails[busCount].ticket_price);

    printf("Enter current date: ");
    scanf("%s", busDetails[busCount].current_date);

    busCount++;
}

// Display bus details
void displayBusDetails() {
    // Function code for displaying bus details
    if (busCount > 0) {
        printf("\n==========Welcome to the bus schedule========\n");
        printf("|   Source      |  Destination  |   Time   |  Price   | Current Date\n");
        printf("========================================================================\n");
        int i;
        for (i = 0; i < busCount; i++) {
            printf("|   %-12s|  %-13s|   %-7s|  %-8.2f| %-10s\n",
                busDetails[i].source, busDetails[i].destination,
                busDetails[i].departure_time, busDetails[i].ticket_price, busDetails[i].current_date);
        }
        printf("===================================================\n");
    } else {
        printf("No bus schedule available.\n");
    }
}

// Function to write bus details to a file
void writeBusDetailsToFile() {
    FILE *file = fopen("bus_details.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "bus_number|departure_time|destination|source|ticket_price|current_date\n");
    int i;
    for (i = 0; i < busCount; i++) {
        fprintf(file, "%s|%s|%s|%s|%.2f|%s\n", busDetails[i].bus_number, busDetails[i].departure_time,
            busDetails[i].destination, busDetails[i].source, busDetails[i].ticket_price, busDetails[i].current_date);
    }

    fclose(file);
    printf("Bus details written to file successfully.\n");
}

// Function to read bus details from a file
void readBusDetailsFromFile() {
    FILE *file = fopen("bus_details.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char header[256];
    fgets(header, sizeof(header), file); // Read and discard the header

    while (!feof(file)) {
        struct BusInfo newBus;
        if (fscanf(file, "%[^|]|%[^|]|%[^|]|%[^|]|%f|%[^\n]\n", newBus.bus_number, newBus.departure_time,
            newBus.destination, newBus.source, &newBus.ticket_price, newBus.current_date) == 6) {
            busDetails[busCount++] = newBus;
        }
    }

    fclose(file);
    printf("Bus details read from file successfully.\n");
}

// Create ticket for a reserved seat
void createTicket(int seat) {
    time_t now;
    time(&now);
    struct tm *local = localtime(&now);

    printf("\n=== Ticket Details ===\n");
    printf("Date and Time: %s", asctime(local));
    printf("Passenger Name: %s\n", bus[seat - 1].passenger_name);
    printf("Destination: %s\n", busDetails[busCount - 1].destination);
    printf("======================\n");
}

// Create a new user account
int createUser() {
    if (userCount < MAX_USERS) {
        char newUsername[MAX_USERNAME_LENGTH];
        char newPassword[MAX_PASSWORD_LENGTH];

        printf("Enter a new username: ");
        scanf("%s", newUsername);
        int i;
        for (i = 0; i < userCount; i++) {
            if (strcmp(newUsername, users[i].username) == 0) {
                printf("Username already exists. Choose another username.\n");
                return 0;
            }
        }

        printf("Enter a new password: ");
        scanf("%s", newPassword);

        strcpy(users[userCount].username, newUsername);
        strcpy(users[userCount].password, newPassword);
        userCount++;

        printf("Account created successfully!\n");
        return 1;
    } else {
        printf("Maximum user limit reached. Cannot create more accounts.\n");
        return 0;
    }
}

// Modify bus details
void modifyBusDetails() {
    if (busCount > 0) {
        printf("Select the information to modify:\n");
        printf("1. Bus Number\n");
        printf("2. Departure Time\n");
        printf("3. Destination\n");
        printf("4. Current Date\n");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter new bus number: ");
                scanf("%s", busDetails[busCount - 1].bus_number);
                break;
            case 2:
                printf("Enter new departure time: ");
                scanf("%s", busDetails[busCount - 1].departure_time);
                break;
            case 3:
                printf("Enter new destination: ");
                scanf("%s", busDetails[busCount - 1].destination);
                break;
            case 4:
                printf("Enter new current date: ");
                scanf("%s", busDetails[busCount - 1].current_date);
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } else {
        printf("No bus schedule available for modification.\n");
    }
}

// Delete reservation based on seat number
void deleteReservation() {
    int seat;
    printf("Enter the seat number you want to delete reservation for: ");
    scanf("%d", &seat);

    if (seat < 1 || seat > MAX_SEATS) {
        printf("Invalid seat number. Please choose a seat between 1 and %d.\n", MAX_SEATS);
        return;
    }

    if (bus[seat - 1].is_reserved) {
        bus[seat - 1].is_reserved = 0;
        strcpy(bus[seat - 1].passenger_name, "Available");
        bus[seat - 1].ticket_price = 0.0;
        printf("Reservation for seat %d has been deleted.\n", seat);
    } else {
        printf("Seat %d is not reserved.\n", seat);
    }
}

// Function to cancel a booking based on customer's request
void cancelBooking() {
    deleteReservation();
}

int main() {
	
    int choice;
    int seatNum;
    char username[40];
    char password[20];

    initializeBus();
    readBusDetailsFromFile(); // Load bus details from a file
    
    printf("Enter username: ");
    scanf("%s", &username);
    printf("\nEnter password: ");
    scanf("%s", &password);
    
    if(strcmp(username,"user")==0 && strcmp(password,"pass")==0) {
		
		do {
        printf("\nBus Reservation System Menu:\n");
        // Display the menu options
        printf("1. Display Available Seats\n");
        printf("2. Reserve a Seat\n");
        printf("3. Display Bus Details\n");
        printf("4. Get Ticket\n");
        printf("5. Exit\n");
        printf("6. Modify Bus Details\n");
        printf("7. Delete Reservation\n");
        printf("8. Cancel Booking\n");
        printf("9. Add Bus Schedule\n");
        printf("10. View Bus Schedules\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayBus();
                break;
            case 2:
                reserveSeat();
                break;
            case 3:
                displayBusDetails();
                break;
            case 4:
                printf("Enter the seat number to generate the ticket: ");
                scanf("%d", &seatNum);
                if (seatNum >= 1 && seatNum <= MAX_SEATS && bus[seatNum - 1].is_reserved) {
                    createTicket(seatNum);
                } else {
                    printf("Invalid seat number or seat not reserved.\n");
                }
                break;
            case 5:
                printf("Thank you for using the Bus Reservation System.\n");
                break;
            case 6:
                modifyBusDetails();
                break;
            case 7:
                deleteReservation();
                break;
            case 8:
                cancelBooking();
                break;
            case 9:
                setBusDetails();
                writeBusDetailsToFile(); // Save bus details to a file after adding a new schedule
                break;
            case 10:
                displayBusDetails();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
     } while (choice != 5);
	}else
	{
	printf("The username or password in invalid.");	
	}

    

    return 0;
}
