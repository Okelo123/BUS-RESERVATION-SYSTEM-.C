# BUS-RESERVATION-SYSTEM-.C
Welcome to Bus Reservation System. This program has been written using a c language and it is built to assertain the user's needs. It also authorize the user to accomplish various tasks as shown below:
## ATTRIBUTES
## 1. Display Available Seats
This code defines a function displayBus() that is responsible for displaying the available seats on a bus. Let's break down the code step by step as shown below;
## a).void displayBus()
This function doesn't return any value (void), and its purpose is to display the available seats on the bus.
## b).printf("Seat Number\tPassenger Name\tTicket Price\n");
This line prints a header that describes the columns to be displayed: Seat Number, Passenger Name, and Ticket Price. The \t character creates a tab space for better formatting.
## c).for (i = 0; i < MAX_SEATS; i += 4)
MAX_SEATS is the maximum number of seats on the bus. This loop jumps by 4 seats per iteration.
The inner loop prints information about each seat within the current group of 4 seats.
## d).for (j = 0; j < 4 && i + j < MAX_SEATS; j++)
-j represents each seat within the group of 4.
-The condition j < 4 && i + j < MAX_SEATS ensures that it doesn't exceed the total number of seats.
-Inside this loop, information about each seat is printed using printf()
## e).printf("%d\t\t%s\t\t%.2f\n", bus[i + j].seat_number, bus[i + j].passenger_name, bus[i + j].ticket_price);
-%d is a placeholder for the seat number (an integer).
-%s is a placeholder for the passenger's name (a string).
-%.2f is a placeholder for the ticket price (a floating-point number), limited to two decimal places.
-bus[i + j] accesses the seat information at the current index.

in simple terms the displayBus() function prints the seat number, passenger name, and ticket price for each available seat on the bus in a tabulated format, grouping them in sets of 4 seats per line, until all seats have been displayed or until the maximum number of seats is reached (MAX_SEATS).

## 2. Reserve a Seat
## a).User Input:
-Prompts the user to enter a seat number they want to reserve.
-Checks if the entered seat number is within the valid range (1 to MAX_SEATS).
## b).Validation:
-It checks if the entered seat number is invalid (less than 1 or greater than MAX_SEATS), it displays an error message and exits the function.
## c).Seat Reservation:
-It examine if the selected seat is already reserved.
-If it's reserved, it informs the user.
-If it's available:
-It help out the user to enter the passenger's name.
-It marks the seat as reserved (is_reserved = 1).
-It sets the ticket price for that seat.
-It confirms the reservation by displaying the seat number, passenger name, and ticket price.
## 3. Display Bus Details
## a).if (busCount > 0)
-It checks if there are bus schedules available (if busCount is greater than 0).
-busCount likely represents the number of bus schedules stored or tracked.
## b). printf("|   %-12s|  %-13s|   %-7s|  %-8.2f| %-10s\n",
       busDetails[i].source, busDetails[i].destination,
       busDetails[i].departure_time, busDetails[i].ticket_price, busDetails[i].current_date);
-%s and %f are format specifiers used to display strings and floating-point numbers, respectively, with specific formatting.
-The -12s, -13s, -7s, -8.2f, -10s are width specifiers used for formatting the output to align columns.
-Finally, after displaying all schedules, it adds a closing line to the table.

## 4. Get Ticket
printf("\n=== Ticket Details ===\n");
printf("Date and Time: %s", asctime(local));
printf("Passenger Name: %s\n", bus[seat - 1].passenger_name);
printf("Destination: %s\n", busDetails[busCount - 1].destination);
printf("======================\n");

## -The function prints the ticket details:
-"=== Ticket Details ===\n": Header indicating the start of ticket details.
-"Date and Time: %s", asctime(local) displays the current date and time. asctime() converts the time stored in the local structure to a string representation.
-"Passenger Name: %s\n", bus[seat - 1].passenger_name fetches the passenger name for the given seat from the bus array and prints it.
-"Destination: %s\n", busDetails[busCount - 1].destination fetches the destination for the most recent bus schedule from the busDetails array and prints it.
-"======================\n": Footer indicating the end of ticket details.
Explanation:

The function takes an argument seat, which represents the seat number for which the ticket details are being created.
It retrieves the current date and time and prints the passenger's name, the destination of the most recent bus schedule (assuming busCount represents the count of schedules), and the current date and time in a formatted manner.
## 5. Exit
It allows the user to exit the program after he/she have done all booking process
## 6. Modify Bus Details
-modifyBusDetails() function allows users to choose which detail of the latest bus schedule they want to modify and prompts them to enter new information accordingly. If there are no bus schedules available, it informs the user that there are no schedules to modify.

## 7. Delete Reservation
-If the seat is currently marked as reserved (bus[seat - 1].is_reserved is 1), the function performs the following actions:
-Marks the seat as unreserved (bus[seat - 1].is_reserved = 0).
-Sets the passenger name for that seat as "Available" using strcpy(bus[seat - 1].passenger_name, "Available").
-Resets the ticket price for that seat to 0.0 (bus[seat - 1].ticket_price = 0.0).
-Prints a message confirming the deletion of the reservation for the specified seat.
-If the seat is not reserved, it displays a message indicating that the seat is not reserved.
## 8. Cancel Booking
## void cancelBooking() {
 ##  deleteReservation();
 ## This function is responsible for canceling a booking based on a customer's request.
## a).Delegating Task:
-The cancelBooking() function doesn’t directly perform the cancellation logic itself.
-Instead, it delegates the actual cancellation task to another function named deleteReservation().

## b).Function Call:
-Upon calling cancelBooking(), it directly invokes the deleteReservation() function without any additional parameters or logic within cancelBooking() itself.

## c).Explanation:
-This code implies a straightforward approach to cancellation. It relies on the functionality provided by the deleteReservation() function to handle the cancellation of a booking based on a customer's request.
 
}

## 9. Add Bus Schedule
- This code allows user to add new schedule for the bus like ; 
 ## Source
 It allows the user to add new source if he/she is interested to add
## Destination 
It gives the user to add destination on their own interest
## Time 
It allows the user to set a new time beside the one sets
## Current Date
It allows the user to set a new current date beside the one sets to give te user another chance in case the user didn't make it that specified date
## 10. View Bus Schedules
This code allow the user to view the chedule that the bus has to avoid complication on booking time
