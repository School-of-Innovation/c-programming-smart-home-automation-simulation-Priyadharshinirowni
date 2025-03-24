#include <stdio.h>

// Function prototypes
void initializeSystem(int rooms, int lights[], int temps[], int motion[], int locks[]);
void toggleLight(int rooms, int lights[]);
void readTemperature(int rooms, int temps[]);
void detectMotion(int rooms, int motion[]);
void securitySystem(int rooms, int locks[]);
void analyzeHouseStatus(int rooms, int lights[], int temps[], int motion[], int locks[]);
void autoLockCheck(int *motionCount, int locks[], int rooms);
void temperatureAlert(int rooms, int temps[]);
void energySavingMode(int rooms, int lights[]);

int main() {
    int rooms;

    // Taking user input for number of rooms
    printf("Enter number of rooms: ");
    scanf("%d", &rooms);

    // Declaring arrays to store system states
    int lights[rooms], temps[rooms], motion[rooms], locks[rooms];

    // Initializing the system
    initializeSystem(rooms, lights, temps, motion, locks);

    int choice, motionCount = 0;

    do {
        // Display the menu
        printf("\n===== Smart Home Menu =====\n");
        printf("1. Toggle Light\n");
        printf("2. Read Temperature\n");
        printf("3. Check Motion Sensor\n");
        printf("4. Lock/Unlock Security System\n");
        printf("5. House Status Summary\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                toggleLight(rooms, lights);
                break;
            case 2:
                readTemperature(rooms, temps);
                break;
            case 3:
                detectMotion(rooms, motion);
                motionCount++;
                autoLockCheck(&motionCount, locks, rooms);
                break;
            case 4:
                securitySystem(rooms, locks);
                break;
            case 5:
                analyzeHouseStatus(rooms, lights, temps, motion, locks);
                temperatureAlert(rooms, temps);
                energySavingMode(rooms, lights);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// Function to initialize system with default states
void initializeSystem(int rooms, int lights[], int temps[], int motion[], int locks[]) {
    for (int i = 0; i < rooms; i++) {
        lights[i] = 0;     // All lights OFF
        temps[i] = 22 + (i % 5); // Assigning random temperatures between 22-26°C
        motion[i] = 0;     // No motion detected
        locks[i] = 1;      // All doors Locked
    }
    printf("\nSystem initialized. All lights OFF, doors LOCKED, no motion detected.\n");
}

// Function to toggle light ON/OFF for a room
void toggleLight(int rooms, int lights[]) {
    int room;
    printf("Enter room number to toggle light (1-%d): ", rooms);
    scanf("%d", &room);

    if (room >= 1 && room <= rooms) {
        lights[room - 1] = !lights[room - 1];
        printf("Light in Room %d is now %s.\n", room, lights[room - 1] ? "ON" : "OFF");
    } else {
        printf("Invalid room number!\n");
    }
}

// Function to read temperature of a room
void readTemperature(int rooms, int temps[]) {
    int room;
    printf("Enter room number to check temperature (1-%d): ", rooms);
    scanf("%d", &room);

    if (room >= 1 && room <= rooms) {
        printf("Temperature in Room %d: %d°C\n", room, temps[room - 1]);
    } else {
        printf("Invalid room number!\n");
    }
}

// Function to detect motion in rooms
void detectMotion(int rooms, int motion[]) {
    int detected = 0;
    for (int i = 0; i < rooms; i++) {
        if (motion[i]) {
            printf("Motion detected in Room %d!\n", i + 1);
            detected = 1;
        }
    }
    if (!detected) {
        printf("No motion detected in the house.\n");
    }
}

// Function to lock/unlock doors
void securitySystem(int rooms, int locks[]) {
    int room;
    printf("Enter room number to toggle lock (1-%d): ", rooms);
    scanf("%d", &room);

    if (room >= 1 && room <= rooms) {
        locks[room - 1] = !locks[room - 1];
        printf("Door in Room %d is now %s.\n", room, locks[room - 1] ? "LOCKED" : "UNLOCKED");
    } else {
        printf("Invalid room number!\n");
    }
}

// Function to display house status
void analyzeHouseStatus(int rooms, int lights[], int temps[], int motion[], int locks[]) {
    printf("\n===== House Status =====\n");
    for (int i = 0; i < rooms; i++) {
        printf("Room %d: Light %s, Temp %d°C, Motion %s, Door %s\n",
               i + 1, 
               lights[i] ? "ON" : "OFF", 
               temps[i], 
               motion[i] ? "Detected" : "No Motion", 
               locks[i] ? "Locked" : "Unlocked");
    }
}

// Auto-lock feature: Locks doors if no motion is detected for 5 inputs
void autoLockCheck(int *motionCount, int locks[], int rooms) {
    if (*motionCount >= 5) {
        printf("\nNo motion detected for a while. Auto-locking all doors...\n");
        for (int i = 0; i < rooms; i++) {
            locks[i] = 1; // Lock all doors
        }
        *motionCount = 0; // Reset count
    }
}

// Alerts if temperature crosses 30°C
void temperatureAlert(int rooms, int temps[]) {
    for (int i = 0; i < rooms; i++) {
        if (temps[i] > 30) {
            printf("WARNING: Room %d has high temperature: %d°C!\n", i + 1, temps[i]);
        }
    }
}

// Suggests turning off lights if all are ON for too long
void energySavingMode(int rooms, int lights[]) {
    int allOn = 1;
    for (int i = 0; i < rooms; i++) {
        if (!lights[i]) {
            allOn = 0;
            break;
        }
    }
    if (allOn) {
        printf("\nAll lights are ON for too long! Consider turning them OFF to save energy.\n");
    }
}
