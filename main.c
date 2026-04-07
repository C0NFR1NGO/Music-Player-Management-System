#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <time.h>    
#include "Functions.h"
// ======================= MAIN & MENU =======================

/*
 * FUNCTION: main
 * PURPOSE: Entry point. Contains the infinite loop for the user interface menu.
 * LOGIC: Initializes the main playlist and the 'currentPlaying' pointer. Uses a 
 * switch-like if/else structure to process user input and call the functions.
 */
int main() {
    SongNode* playlist = NULL;
    SongNode* currentPlaying = NULL; 
    int choice;
    
    SongNode* list2 = NULL;
    addSong(&list2, 2, "Shape of You", "Ed Sheeran");
    addSong(&list2, 4, "Blinding Lights", "The Weeknd");

    while (1) {
        printf("\n=== Music Playlist Management System ===\n");
        if (currentPlaying) {
            printf(">>> NOW PLAYING: %s by %s <<<\n", currentPlaying->title, currentPlaying->artist);
        }
        printf("1. Add Song\n2. Delete Song\n3. Display Playlist\n4. Search Song\n");
        printf("5. Shuffle Mode\n6. Repeat Playlist\n7. Play a Specific Song\n");
        printf("8. View Play History (Chronological)\n9. View Play History (Reverse)\n");
        printf("10. Demo List Operations\n11. Play Next Song\n12. Play Previous Song\n0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        if (choice == 0) break;
        
        if (choice == 1) {
            int id; char title[100], artist[100];
            printf("Enter Song ID: "); scanf("%d", &id);
            getchar(); 
            printf("Enter Title: "); fgets(title, 100, stdin); title[strcspn(title, "\n")] = 0; 
            printf("Enter Artist: "); fgets(artist, 100, stdin); artist[strcspn(artist, "\n")] = 0;
            addSong(&playlist, id, title, artist);
            printf("Song added successfully.\n");
        }
        else if (choice == 2) {
            int id;
            printf("Enter Song ID to delete: "); scanf("%d", &id);
            deleteSong(&playlist, id);
        }
        else if (choice == 3) {
            int sortMode;
            printf("1. By Title\n2. By Artist\n3. By Artist then Title\n4. Default (SongID)\nSort Type: ");
            scanf("%d", &sortMode);
            displayPlaylist(playlist, sortMode);
        }
        else if (choice == 4) {
            int sType; char query[100];
            printf("Search by: 1. ID 2. Title 3. Artist: ");
            scanf("%d", &sType);
            getchar();
            printf("Enter query: "); fgets(query, 100, stdin); query[strcspn(query, "\n")] = 0;
            searchSong(playlist, sType, query);
        }
        else if (choice == 5) {
            shufflePlaylist(&playlist);
        }
        else if (choice == 6) {
            repeatPlaylist(playlist);
        }
        else if (choice == 7) {
            int id;
            printf("Enter Song ID to play: "); scanf("%d", &id);
            SongNode* curr = playlist;
            while (curr && curr->songID != id) curr = curr->next;
            if (curr) {
                currentPlaying = curr; 
                printf("Playing: %s by %s\n", curr->title, curr->artist);
                pushHistory(curr->songID, curr->title, curr->artist); 
            } else {
                printf("Song not found in playlist.\n");
            }
        }
        else if (choice == 8) displayHistoryChronological();
        else if (choice == 9) displayHistoryReverseChronological();
        else if (choice == 10) {
            printf("\n--- Demonstrating List Operations ---\n");
            printf("List 1 (Current Playlist):\n"); displayPlaylist(playlist, 4);
            printf("\nList 2 (Pre-loaded):\n"); displayPlaylist(list2, 4);
            
            SongNode* uni = unionLists(playlist, list2);
            printf("\nUnion:"); displayPlaylist(uni, 4);
            
            SongNode* inter = intersectLists(playlist, list2);
            printf("\nIntersection:"); displayPlaylist(inter, 4);
            
            SongNode* diff = diffLists(playlist, list2);
            printf("\nDifference (L1 - L2):"); displayPlaylist(diff, 4);
            
            SongNode* symDiff = symDiffLists(playlist, list2);
            printf("\nSymmetric Difference:"); displayPlaylist(symDiff, 4);
        }
        else if (choice == 11) { 
            if (currentPlaying != NULL && currentPlaying->next != NULL) {
                currentPlaying = currentPlaying->next; 
                printf("Playing Next: %s by %s\n", currentPlaying->title, currentPlaying->artist);
                pushHistory(currentPlaying->songID, currentPlaying->title, currentPlaying->artist);
            } else if (currentPlaying != NULL) {
                printf("You are at the end of the playlist.\n");
            } else {
                printf("No song is currently playing. Use Option 7 to start playing.\n");
            }
        }
        else if (choice == 12) { 
            if (currentPlaying != NULL && currentPlaying->prev != NULL) {
                currentPlaying = currentPlaying->prev; 
                printf("Playing Previous: %s by %s\n", currentPlaying->title, currentPlaying->artist);
                pushHistory(currentPlaying->songID, currentPlaying->title, currentPlaying->artist);
            } else if (currentPlaying != NULL) {
                printf("You are at the beginning of the playlist.\n");
            } else {
                printf("No song is currently playing. Use Option 7 to start playing.\n");
            }
        }
    }
    return 0;
}