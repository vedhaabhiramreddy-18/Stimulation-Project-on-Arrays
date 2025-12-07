#include <stdio.h>
#include <string.h>

struct song {
    char name[50];
    char artist[50];
};

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Add song
void addSong() {
    struct song s;
    FILE *fp = fopen("playlist.txt", "a");

    if (!fp) {
        printf("File error!\n");
        return;
    }

    printf("Enter Song Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = 0;

    printf("Enter Artist Name: ");
    fgets(s.artist, sizeof(s.artist), stdin);
    s.artist[strcspn(s.artist, "\n")] = 0;

    fprintf(fp, "%s,%s\n", s.name, s.artist);
    fclose(fp);

    printf("Song added successfully!\n");
}

// Display playlist
void display() {
    FILE *fp = fopen("playlist.txt", "r");
    char line[100];

    if (!fp) {
        printf("Playlist empty!\n");
        return;
    }

    printf("\n--- PLAYLIST ---\n");
    while (fgets(line, sizeof(line), fp))
        printf("%s", line);

    fclose(fp);
}

// Search song
void search() {
    FILE *fp = fopen("playlist.txt", "r");
    char key[50], line[100];
    int found = 0;

    if (!fp) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Song Name to search: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, key)) {
            printf("Found: %s", line);
            found = 1;
        }
    }

    if (!found)
        printf("Song not found!\n");

    fclose(fp);
}

// Delete song
void deleteSong() {
    FILE *fp = fopen("playlist.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char key[50], line[100];
    int found = 0;

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    printf("Enter Song Name to delete: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, key))
            found = 1;
        else
            fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");

    if (found)
        printf("Song deleted successfully!\n");
    else
        printf("Song not found!\n");
}

// Edit song
void editSong() {
    FILE *fp = fopen("playlist.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char key[50], line[100];
    struct song s;
    int found = 0;

    if (!fp || !temp) {
        printf("File error!\n");
        return;
    }

    printf("Enter Song Name to edit: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, key)) {
            printf("Enter New Song Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = 0;

            printf("Enter New Artist Name: ");
            fgets(s.artist, sizeof(s.artist), stdin);
            s.artist[strcspn(s.artist, "\n")] = 0;

            fprintf(temp, "%s,%s\n", s.name, s.artist);
            found = 1;
        } else {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("playlist.txt");
    rename("temp.txt", "playlist.txt");

    if (found)
        printf("Song updated successfully!\n");
    else
        printf("Song not found!\n");
}

// Main
int main() {
    int ch;

    while (1) {
        printf("\n--- MUSIC PLAYLIST MENU ---\n");
        printf("1. Add Song\n");
        printf("2. Display Playlist\n");
        printf("3. Search Song\n");
        printf("4. Delete Song\n");
        printf("5. Edit Song\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &ch);
        clearBuffer();   

        switch (ch) {
            case 1: addSong(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: deleteSong(); break;
            case 5: editSong(); break;
            case 6: return 0;
            default: printf("Invalid option\n");
        }
    }
}
