#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define NUM_TEAMS 20
#define SQUAD_SIZE 53

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char name[26];
    int kitNumber;
    char club[30];
    Date birthDate;
    char position[20];
} Player;

typedef struct {
    char teamName[21];
    Player players[SQUAD_SIZE];
    int activeSize;
} Team;

Team league[NUM_TEAMS];
int enrolledTeams = 0;

void display_menu() {
    printf("\nMenu:\n");
    printf("1. Enroll Club\n");
    printf("2. Add Player\n");
    printf("3. Search and Update Player\n");
    printf("4. Display Club Statistics\n");
    printf("0. Exit\n");
}

void enroll_club() {
    if (enrolledTeams >= NUM_TEAMS) {
        printf("Maximum number of teams reached.\n");
        return;
    }
    printf("Enter club name: ");
    scanf(" %[^\n]", league[enrolledTeams].teamName);
    league[enrolledTeams].activeSize = 0;
    enrolledTeams++;
    printf("Club enrolled successfully.\n");
}

bool is_duplicate(Player players[], int count, char name[], int kitNumber) {
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].name, name) == 0 || players[i].kitNumber == kitNumber) {
            return true;
        }
    }
    return false;
}

void add_player() {
    if (enrolledTeams == 0) {
        printf("No clubs available. Enroll a club first.\n");
        return;
    }

    printf("Select a club by number:\n");
    for (int i = 0; i < enrolledTeams; i++) {
        printf("%d. %s\n", i + 1, league[i].teamName);
    }

    int teamIndex;
    scanf("%d", &teamIndex);
    teamIndex--;

    if (teamIndex < 0 || teamIndex >= enrolledTeams || league[teamIndex].activeSize >= SQUAD_SIZE) {
        printf("Invalid selection or team is full.\n");
        return;
    }

    Player newPlayer;
    printf("Enter player name: ");
    scanf(" %[^\n]", newPlayer.name);
    printf("Enter unique kit number (1-99): ");
    scanf("%d", &newPlayer.kitNumber);
    printf("Enter birth date (day month year): ");
    scanf("%d %d %d", &newPlayer.birthDate.day, &newPlayer.birthDate.month, &newPlayer.birthDate.year);
    printf("Enter position: ");
    scanf(" %[^\n]", newPlayer.position);
    strcpy(newPlayer.club, league[teamIndex].teamName);

    if (is_duplicate(league[teamIndex].players, league[teamIndex].activeSize, newPlayer.name, newPlayer.kitNumber)) {
        printf("Duplicate player name or kit number. Player not added.\n");
    } else {
        league[teamIndex].players[league[teamIndex].activeSize] = newPlayer;
        league[teamIndex].activeSize++;
        printf("Player added successfully.\n");
    }
}

void search_update() {
    char searchName[26];
    int kitNumber, choice;
    printf("Search by 1. Name or 2. Kit Number? ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter player name: ");
        scanf(" %[^\n]", searchName);
    } else if (choice == 2) {
        printf("Enter kit number: ");
        scanf("%d", &kitNumber);
    } else {
        printf("Invalid choice.\n");
        return;
    }

    bool found = false;
    for (int i = 0; i < enrolledTeams; i++) {
        for (int j = 0; j < league[i].activeSize; j++) {

            if ((choice == 1 && strcasecmp(league[i].players[j].name, searchName) == 0) ||
                (choice == 2 && league[i].players[j].kitNumber == kitNumber)) {
                printf("Player found:\n");
                printf("  Name: %s\n  Kit Number: %d\n  Club: %s\n  Birth Date: %02d-%02d-%04d\n  Position: %s\n",
                       league[i].players[j].name, league[i].players[j].kitNumber, league[i].players[j].club,
                       league[i].players[j].birthDate.day, league[i].players[j].birthDate.month, league[i].players[j].birthDate.year,
                       league[i].players[j].position);

                printf("Update player details (leave blank to keep current value):\n");

                printf("Enter new name [%s]: ", league[i].players[j].name);
                char newName[26];
                scanf(" %[^\n]", newName);
                if (strlen(newName) > 0) {
                    strcpy(league[i].players[j].name, newName);
                }

                printf("Enter new kit number [%d]: ", league[i].players[j].kitNumber);
                int newKitNumber;
                if (scanf("%d", &newKitNumber) == 1) {
                    league[i].players[j].kitNumber = newKitNumber;
                }

                printf("Enter new birth date (day month year) [%02d-%02d-%04d]: ", league[i].players[j].birthDate.day, league[i].players[j].birthDate.month, league[i].players[j].birthDate.year);
                int newDay, newMonth, newYear;
                if (scanf("%d %d %d", &newDay, &newMonth, &newYear) == 3) {
                    league[i].players[j].birthDate.day = newDay;
                    league[i].players[j].birthDate.month = newMonth;
                    league[i].players[j].birthDate.year = newYear;
                }

                printf("Enter new position [%s]: ", league[i].players[j].position);
                char newPosition[20];
                scanf(" %[^\n]", newPosition);
                if (strlen(newPosition) > 0) {
                    strcpy(league[i].players[j].position, newPosition);
                }

                printf("Player details updated successfully.\n");
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) {
        printf("Player not found.\n");
    }
}


void display_club_statistics() {
    for (int i = 0; i < enrolledTeams; i++) {
        printf("Club: %s, Players: %d\n", league[i].teamName, league[i].activeSize);
        int ageSum = 0;
        for (int j = 0; j < league[i].activeSize; j++) {
            int age = 2024 - league[i].players[j].birthDate.year;
            ageSum += age;
            printf("  Name: %s, Kit: %d, Position: %s, Age: %d\n", league[i].players[j].name, league[i].players[j].kitNumber, league[i].players[j].position, age);
        }
        printf("Average Age: %.2f\n", league[i].activeSize ? (float)ageSum / league[i].activeSize : 0.0);
    }
}

int main() {
    int choice;
    do {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enroll_club();
                break;
            case 2:
                add_player();
                break;
            case 3:
                search_update();
                break;
            case 4:
                display_club_statistics();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 0);

    return 0;
}
