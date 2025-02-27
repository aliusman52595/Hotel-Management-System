#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_ROOMS = 10;

// Structures
struct Customer {
    string name;
    string contactNumber;
    int numOfNights;
};

struct Room {
    int roomNumber;
    string roomType; 
    bool isBooked;
    Customer customer;
};

struct Guest {
    char name[100];
    char contact[15];
    int roomNumber;
};

// Global Variables
Room rooms[MAX_ROOMS];
Guest guests[MAX_ROOMS];
int guestCount = 0;

// Function Prototypes
void initializeRooms();
void displayAvailableRooms();
void bookRoom();
void cancelBooking();
void addGuest();
void displayGuests();
void handleCustomerCheckIn();
void handleCustomerCheckOut();
void addFeedback();
void displayFeedback();
void searchFeedback();
void searchGuest();

// ------------------------------ Room Booking Management ------------------------------
void initializeRooms() {
    for (int i = 0; i < MAX_ROOMS; i++) {
        rooms[i].roomNumber = i + 1;
        rooms[i].roomType = (i % 2 == 0) ? "Single" : "Double"; 
        rooms[i].isBooked = false;
    }
}

void displayAvailableRooms() {
    cout << "\nAvailable Rooms:\n";
    bool available = false;
    for (int i = 0; i < MAX_ROOMS; i++) {
        if (!rooms[i].isBooked) {
            cout << "Room Number: " << rooms[i].roomNumber
                 << " (" << rooms[i].roomType << ")\n";
            available = true;
        }
    }
    if (!available) {
        cout << "No rooms available.\n";
    }
}

void bookRoom() {
    int roomNumber;
    cout << "Enter Room Number to book: ";
    cin >> roomNumber;

    if (roomNumber >= 1 && roomNumber <= MAX_ROOMS && !rooms[roomNumber - 1].isBooked) {
        Room &room = rooms[roomNumber - 1];
        cout << "Enter Customer Name: ";
        cin >> room.customer.name;

        cout << "Enter Contact Number: ";
        cin >> room.customer.contactNumber;

        cout << "Enter Number of Nights: ";
        cin >> room.customer.numOfNights;

        room.isBooked = true;
        cout << "Room " << roomNumber << " booked successfully for " << room.customer.name << ".\n";
    } else {
        cout << "Room is either invalid or already booked.\n";
    }
}

void cancelBooking() {
    int roomNumber;
    cout << "Enter Room Number to cancel booking: ";
    cin >> roomNumber;

    if (roomNumber >= 1 && roomNumber <= MAX_ROOMS && rooms[roomNumber - 1].isBooked) {
        rooms[roomNumber - 1].isBooked = false;
        cout << "Booking for Room " << roomNumber << " has been cancelled.\n";
    } else {
        cout << "Room is either invalid or not booked.\n";
    }
}

// -------------------------- Guest Management --------------------------
void addGuest() {
    if (guestCount < MAX_ROOMS) {
        cout << "Enter Guest Name: ";
        cin >> guests[guestCount].name;
        cout << "Enter Guest Contact: ";
        cin >> guests[guestCount].contact;
        cout << "Enter Room Number: ";
        cin >> guests[guestCount].roomNumber;
        guestCount++;
        cout << "Guest added successfully.\n";
    } else {
        cout << "Guest limit reached.\n";
    }
}

void displayGuests() {
    cout << "\nGuests List:\n";
    for (int i = 0; i < guestCount; i++) {
        cout << "Name: " << guests[i].name
             << ", Contact: " << guests[i].contact
             << ", Room Number: " << guests[i].roomNumber << endl;
    }
}

// -------------------------- Room and Customer Management --------------------------
void handleCustomerCheckIn() {
    int roomNumber;
    cout << "Enter Room Number for check-in: ";
    cin >> roomNumber;

    if (roomNumber >= 1 && roomNumber <= MAX_ROOMS && !rooms[roomNumber - 1].isBooked) {
        rooms[roomNumber - 1].isBooked = true;
        cout << "Check-in successful for Room " << roomNumber << ".\n";
    } else {
        cout << "Room is either invalid or already occupied.\n";
    }
}

void handleCustomerCheckOut() {
    int roomNumber;
    cout << "Enter Room Number for check-out: ";
    cin >> roomNumber;

    if (roomNumber >= 1 && roomNumber <= MAX_ROOMS && rooms[roomNumber - 1].isBooked) {
        rooms[roomNumber - 1].isBooked = false;
        cout << "Check-out successful for Room " << roomNumber << ".\n";
    } else {
        cout << "Room is either invalid or not occupied.\n";
    }
}

// -------------------------- Feedback and Review System --------------------------
// Function to add feedback
void addFeedback() {
    ofstream outFile("feedbacks.txt", ios::app);
    if (!outFile) {
        cout << "Error: Could not open or create the feedback file.\n";
        return;
    }

    string feedback;
    cout << "Enter your feedback: ";
    cin.ignore(); 
    getline(cin, feedback); 

    outFile << feedback << "\n";
    cout << "Feedback added successfully.\n";
}


void displayFeedback() {
    ifstream inFile("feedbacks.txt");
    if (!inFile) {
        cout << "No feedback available or error opening the file.\n";
        return;
    }

    string feedback;
    cout << "\nFeedback List:\n";
    while (getline(inFile, feedback)) {
        cout << "- " << feedback << endl;
    }
}

// ------------------------------ Main Program ------------------------------
int main() {
    initializeRooms();
    int choice;

    do {
        cout << "\n----------------------Hotel Management System----------------------\n";
        cout << "\nRoom Booking Management:\n";
        cout << "1. Display Available Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. Cancel a Booking\n";
        cout << "\nGuest Management:\n";
        cout << "4. Add Guest\n";
        cout << "5. Display Guests\n";
        cout << "\nRoom and Customer Management:\n";
        cout << "6. Customer Check-In\n";
        cout << "7. Customer Check-Out\n";
        cout << "\nFeedback Management:\n";
        cout << "8. Add Feedback\n";
        cout << "9. Display Feedback\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAvailableRooms();
                break;
            case 2:
                bookRoom();
                break;
            case 3:
                cancelBooking();
                break;
            case 4:
                addGuest();
                break;
            case 5:
                displayGuests();
                break;
            case 6:
                handleCustomerCheckIn();
                break;
            case 7:
                handleCustomerCheckOut();
                break;
            case 8:
                addFeedback();
                break;
            case 9:
                displayFeedback();
                break;
            case 10:
                cout << "Exiting .......\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}

