#include <stdio.h>
#include <stdlib.h>  
#include <string.h>  
#include <time.h>    
#include "Functions.h"


HistoryNode* historyTop = NULL; // Global stack pointer for play history

// ======================= PLAY HISTORY FUNCTIONS =======================

/*
 FUNCTION: pushHistory
 PURPOSE: Adds a newly played song to the top of the play history stack.
 PARAMETERS: 
 * - int id: The unique ID of the song.
 * - const char* title: The title of the song.
 * - const char* artist: The artist of the song.
 RETURNS: void
 COMPLEXITY: O(1) Time. Inserting at the head of a linked list is instantaneous.
 LOGIC:
    1. Allocates memory for a new HistoryNode.
    2. Copies the song data into the node.
    3. Points the new node's 'next' to the current top of the stack.
    4. Reassigns the global 'historyTop' to point to this new node.
 */
void pushHistory(int id, const char* title, const char* artist) {
    HistoryNode* newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
    newNode->songID = id;
    strcpy(newNode->title, title);
    strcpy(newNode->artist, artist);
    
    newNode->next = historyTop;
    historyTop = newNode;
}

/*
 * FUNCTION: printChronological
 * PURPOSE: A recursive helper function to print the stack from bottom to top.
 * PARAMETERS: 
 * - HistoryNode* node: The current node in the recursive traversal.
 * RETURNS: void
 * COMPLEXITY: O(N) Time, O(N) Space (due to recursive call stack).
 * LOGIC:
 * 1. Base Case: If the node is NULL (end of the stack), return and stop recursing.
 * 2. Recursive Step: Call the function again with the NEXT node.
 * 3. Print Step: Only print the song details AFTER returning from the deeper 
 * recursive call. This ensures the oldest song (bottom of stack) prints first.
 */
void printChronological(HistoryNode* node) {
    if (node == NULL) return; 
    printChronological(node->next); 
    printf("ID: %d | Title: %s | Artist: %s\n", node->songID, node->title, node->artist);
}

/*
 * FUNCTION: displayHistoryChronological
 * PURPOSE: Menu wrapper to display play history from oldest to newest.
 * PARAMETERS: None
 * RETURNS: void
 * LOGIC: Checks if the history is empty. If not, it calls the recursive 
 * 'printChronological' function starting from the top of the stack.
 */
void displayHistoryChronological() {
    printf("\n--- Play History (Chronological) ---\n");
    if (historyTop == NULL) {
        printf("History is empty.\n");
        return;
    }
    printChronological(historyTop);
}

/*
 * FUNCTION: displayHistoryReverseChronological
 * PURPOSE: Displays play history from newest to oldest (standard stack order).
 * PARAMETERS: None
 * RETURNS: void
 * COMPLEXITY: O(N) Time. Iterates through the stack once.
 * LOGIC:
 * 1. Starts at 'historyTop' (the most recently played song).
 * 2. Uses a while loop to print the current node's data.
 * 3. Moves to the next node down the stack until reaching NULL.
 */
void displayHistoryReverseChronological() {
    printf("\n--- Play History (Reverse Chronological) ---\n");
    HistoryNode* current = historyTop;
    if (current == NULL) {
        printf("History is empty.\n");
        return;
    }
    while (current != NULL) {
        printf("ID: %d | Title: %s | Artist: %s\n", current->songID, current->title, current->artist);
        current = current->next;
    }
}

// ======================= PLAYLIST FUNCTIONS =======================

/*
 * FUNCTION: createSongNode
 * PURPOSE: Helper function to allocate memory and initialize a new SongNode.
 * PARAMETERS: id, title, artist.
 * RETURNS: SongNode* (Pointer to the newly created node).
 * LOGIC: Uses malloc to grab memory, copies strings using strcpy, sets 
 * prev and next pointers to NULL to prevent dangling pointers.
 */
SongNode* createSongNode(int id, const char* title, const char* artist) {
    SongNode* newNode = (SongNode*)malloc(sizeof(SongNode));
    newNode->songID = id;
    strcpy(newNode->title, title);
    strcpy(newNode->artist, artist);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/*
 * FUNCTION: addSong
 * PURPOSE: Inserts a new song into the Doubly Linked List while maintaining 
 * ascending sorted order based on SongID.
 * PARAMETERS: 
 * - SongNode** head: Double pointer to the head of the playlist.
 * - int id, const char* title, const char* artist: Song details.
 * RETURNS: void
 * COMPLEXITY: O(N) Time worst case (if inserting at the very end of a long list).
 * LOGIC:
 * 1. Creates the node.
 * 2. Empty List Check: If head is NULL, makes the new node the head.
 * 3. Insert at Head Check: If the new ID is smaller than the head's ID, 
 * rewires pointers to place the new node before the current head.
 * 4. Middle/Tail Insert: Traverses the list using a while loop until it finds 
 * a node whose NEXT ID is greater than the new ID.
 * 5. Rewires the 'next' and 'prev' pointers of the new node, the 'current' node, 
 * and the 'current->next' node to securely link the new song into the chain.
 */
void addSong(SongNode** head, int id, const char* title, const char* artist) {
    SongNode* newNode = createSongNode(id, title, artist);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    if ((*head)->songID >= id) {
        newNode->next = *head;         
        newNode->next->prev = newNode;   
        *head = newNode;               
        return;
    }
    
    SongNode* current = *head;
    while (current->next != NULL && current->next->songID < id) {
        current = current->next;
    }
    
    newNode->next = current->next; 
    if (current->next != NULL) {
        newNode->next->prev = newNode; 
    }
    current->next = newNode; 
    newNode->prev = current; 
}

/*
 * FUNCTION: deleteSong
 * PURPOSE: Removes a song from the playlist based on its SongID.
 * PARAMETERS: 
 * - SongNode** head: Double pointer to the head of the playlist.
 * - int id: The ID of the song to delete.
 * RETURNS: void
 * COMPLEXITY: O(N) Time to search for the node, O(1) to delete it.
 * LOGIC:
 * 1. Traverses the list to find the node matching the provided ID.
 * 2. If not found, prints an error message and exits.
 * 3. If the node is the head, shifts the head pointer to the next node.
 * 4. Bypasses the found node by connecting its 'prev' node directly 
 * to its 'next' node, and vice versa.
 * 5. Frees the memory of the found node.
 */
void deleteSong(SongNode** head, int id) {
    if (*head == NULL) return;
    
    SongNode* current = *head;
    while (current != NULL && current->songID != id) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Song ID %d not found.\n", id);
        return;
    }
    
    if (current == *head) *head = current->next;
    if (current->next != NULL) current->next->prev = current->prev;
    if (current->prev != NULL) current->prev->next = current->next;
    
    free(current); 
    printf("Song %d deleted.\n", id);
}

/* * FUNCTIONS: cmpTitle, cmpArtist, cmpArtistTitle
 * PURPOSE: Comparison functions required by the C standard library's qsort().
 * RETURNS: Negative integer if a < b, 0 if a == b, Positive integer if a > b.
 * LOGIC: Casts generic void pointers to SongNode double pointers, then uses 
 * strcmp to compare the string fields alphabetically.
 */
int cmpTitle(const void* a, const void* b) {
    return strcmp((*(SongNode**)a)->title, (*(SongNode**)b)->title);
}
int cmpArtist(const void* a, const void* b) {
    return strcmp((*(SongNode**)a)->artist, (*(SongNode**)b)->artist);
}
int cmpArtistTitle(const void* a, const void* b) {
    int artistCmp = strcmp((*(SongNode**)a)->artist, (*(SongNode**)b)->artist);
    if (artistCmp == 0) return strcmp((*(SongNode**)a)->title, (*(SongNode**)b)->title);
    return artistCmp;
}

/*
 * FUNCTION: displayPlaylist
 * PURPOSE: Prints the playlist to the screen sorted by a user-selected criterion, 
 * WITHOUT destroying the base linked list's SongID sorting.
 * PARAMETERS: 
 * - SongNode* head: Pointer to the head of the playlist.
 * - int sortType: 1(Title), 2(Artist), 3(Artist+Title), 4(Default ID).
 * RETURNS: void
 * COMPLEXITY: O(N log N) Time due to QuickSort algorithm. O(N) Space for array.
 * LOGIC:
 * 1. Counts the number of nodes in the linked list.
 * 2. Dynamically allocates an array of pointers to hold the nodes.
 * 3. Copies the pointers from the linked list into the array.
 * 4. Runs qsort() on the array using the appropriate comparator function.
 * 5. Iterates through the newly sorted array and prints the data.
 * 6. Frees the temporary array.
 */
void displayPlaylist(SongNode* head, int sortType) {
    if (head == NULL) {
        printf("Playlist is empty.\n");
        return;
    }
    
    int count = 0;
    SongNode* curr = head;
    while (curr) { count++; curr = curr->next; }
    
    SongNode** arr = (SongNode**)malloc(count * sizeof(SongNode*));
    curr = head;
    for (int i = 0; i < count; i++) {
        arr[i] = curr;
        curr = curr->next;
    }
    
    if (sortType == 1) qsort(arr, count, sizeof(SongNode*), cmpTitle);
    else if (sortType == 2) qsort(arr, count, sizeof(SongNode*), cmpArtist);
    else if (sortType == 3) qsort(arr, count, sizeof(SongNode*), cmpArtistTitle);
    
    printf("\n--- Playlist ---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d | Title: %s | Artist: %s\n", arr[i]->songID, arr[i]->title, arr[i]->artist);
    }
    free(arr); 
}

/*
 * FUNCTION: searchSong
 * PURPOSE: Finds and prints songs matching a specific query.
 * PARAMETERS: head, type (1=ID, 2=Title, 3=Artist), query (the search string).
 * RETURNS: void
 * COMPLEXITY: O(N) Time. Must check every node.
 * LOGIC: Uses a while loop to check the corresponding field of each node against 
 * the query. Uses strcasecmp for case-insensitive string matching.
 */
void searchSong(SongNode* head, int type, const char* query) {
    SongNode* curr = head;
    int found = 0;
    while (curr) {
        if ((type == 1 && curr->songID == atoi(query)) ||
            (type == 2 && strcasecmp(curr->title, query) == 0) ||
            (type == 3 && strcasecmp(curr->artist, query) == 0)) {
            printf("Found: ID: %d | Title: %s | Artist: %s\n", curr->songID, curr->title, curr->artist);
            found = 1;
        }
        curr = curr->next;
    }
    if (!found) printf("No matching song found.\n");
}

/*
 * FUNCTION: shufflePlaylist
 * PURPOSE: Randomizes the physical order of the nodes in the Doubly Linked List.
 * PARAMETERS: SongNode** head (Double pointer to modify the actual list head).
 * RETURNS: void
 * COMPLEXITY: O(N) Time to copy to array, O(N) to shuffle, O(N) to rewire.
 * LOGIC:
 * 1. Copies node pointers into a temporary array.
 * 2. Uses the Fisher-Yates shuffle algorithm to randomly swap pointers in the array.
 * 3. Re-assigns the *head to the first element of the shuffled array.
 * 4. Loops through the array and manually re-wires the 'next' and 'prev' 
 * pointers of every node to cement the new random order.
 */
void shufflePlaylist(SongNode** head) {
    if (*head == NULL || (*head)->next == NULL) return;
    
    int count = 0;
    SongNode* curr = *head;
    while (curr) { count++; curr = curr->next; }
    
    SongNode** arr = (SongNode**)malloc(count * sizeof(SongNode*));
    curr = *head;
    for (int i = 0; i < count; i++) { arr[i] = curr; curr = curr->next; }
    
    srand(time(NULL));
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        SongNode* temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    
    *head = arr[0];
    arr[0]->prev = NULL;
    for (int i = 0; i < count - 1; i++) {
        arr[i]->next = arr[i+1];
        arr[i+1]->prev = arr[i];
    }
    arr[count-1]->next = NULL;
    free(arr);
    printf("Playlist shuffled!\n");
}

/*
 * FUNCTION: repeatPlaylist
 * PURPOSE: Simulates repeating the entire playlist.
 * PARAMETERS: SongNode* head.
 * RETURNS: void
 * LOGIC: Traverses the list from head to tail. For each node, it prints "Playing" 
 * and pushes the song to the Play History stack. Loops twice for demonstration.
 */
void repeatPlaylist(SongNode* head) {
    if (head == NULL) return;
    printf("\n--- Repeating Playlist (2 Cycles for Demo) ---\n");
    for (int i = 0; i < 2; i++) {
        SongNode* curr = head;
        while (curr) {
            printf("Playing: %s by %s\n", curr->title, curr->artist);
            pushHistory(curr->songID, curr->title, curr->artist);
            curr = curr->next;
        }
    }
}

// ======================= MULTIPLE LIST OPERATIONS =======================

/*
 * FUNCTION: insertAtTail
 * PURPOSE: Helper function for the Set Operations (Union, Intersect, etc.). 
 * Inserts nodes directly at the end of a list without searching for order.
 * PARAMETERS: head, tail (double pointers), id, title, artist.
 * RETURNS: void
 * COMPLEXITY: O(1) Time. Because we track the 'tail', we append instantly.
 */
void insertAtTail(SongNode** head, SongNode** tail, int id, const char* title, const char* artist) {
    SongNode* newNode = createSongNode(id, title, artist);
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
}

/*
 * FUNCTION: unionLists
 * PURPOSE: Creates a third playlist containing all unique songs from list 1 and list 2.
 * PARAMETERS: SongNode* l1, SongNode* l2 (The two source playlists).
 * RETURNS: SongNode* (Pointer to the head of the new union playlist).
 * COMPLEXITY: O(N + M) Time. "Two-Pointer" approach. Extremely efficient.
 * LOGIC:
 * 1. Simultaneously traverses both sorted lists.
 * 2. Compares the current SongIDs. Inserts the smaller ID into the new list 
 * and advances only the pointer of the list that had the smaller ID.
 * 3. If IDs are equal, it inserts the song once and advances BOTH pointers.
 * 4. Once one list runs out, it appends the rest of the other list.
 */
SongNode* unionLists(SongNode* l1, SongNode* l2) {
    SongNode* head = NULL; SongNode* tail = NULL;
    while (l1 && l2) {
        if (l1->songID < l2->songID) {
            insertAtTail(&head, &tail, l1->songID, l1->title, l1->artist);
            l1 = l1->next;
        } else if (l1->songID > l2->songID) {
            insertAtTail(&head, &tail, l2->songID, l2->title, l2->artist);
            l2 = l2->next;
        } else {
            insertAtTail(&head, &tail, l1->songID, l1->title, l1->artist);
            l1 = l1->next; l2 = l2->next;
        }
    }
    while (l1) { insertAtTail(&head, &tail, l1->songID, l1->title, l1->artist); l1 = l1->next; }
    while (l2) { insertAtTail(&head, &tail, l2->songID, l2->title, l2->artist); l2 = l2->next; }
    return head;
}

/*
 * FUNCTION: intersectLists
 * PURPOSE: Creates a list of songs that exist in BOTH list 1 and list 2.
 * LOGIC: Same two-pointer approach as Union, but ONLY inserts into the new list 
 * when the IDs are identical (l1->songID == l2->songID).
 */
SongNode* intersectLists(SongNode* l1, SongNode* l2) {
    SongNode* head = NULL; SongNode* tail = NULL;
    while (l1 && l2) {
        if (l1->songID < l2->songID) l1 = l1->next;
        else if (l1->songID > l2->songID) l2 = l2->next;
        else {
            insertAtTail(&head, &tail, l1->songID, l1->title, l1->artist);
            l1 = l1->next; l2 = l2->next;
        }
    }
    return head; 
}

/*
 * FUNCTION: diffLists
 * PURPOSE: Creates a list of songs present in list 1, but NOT in list 2.
 * LOGIC: Two-pointer approach. Inserts only when l1->songID < l2->songID. 
 * If IDs match, it skips both without inserting.
 */
SongNode* diffLists(SongNode* l1, SongNode* l2) {
    SongNode* head = NULL; SongNode* tail = NULL;
    while (l1 && l2) {
        if (l1->songID < l2->songID) {
            insertAtTail(&head, &tail, l1->songID, l1->title, l1->artist);
            l1 = l1->next;
        } else if (l1->songID > l2->songID) {
            l2 = l2->next; 
        } else {
            l1 = l1->next; l2 = l2->next; 
        }
    }
    while (l1) { insertAtTail(&head, &tail, l1->songID, l1->title, l1->artist); l1 = l1->next; }
    return head; 
}

/*
 * FUNCTION: symDiffLists
 * PURPOSE: Creates a list of songs present in list 1 or list 2, but NOT BOTH (XOR).
 * LOGIC: Two-pointer approach. Inserts when l1 < l2, inserts when l1 > l2. 
 * If they are equal, it ignores them and advances both pointers.
 */
SongNode* symDiffLists(SongNode* l1, SongNode* l2) {
    SongNode* head = NULL; SongNode* tail = NULL;
    while (l1 && l2) {
        if (l1->songID < l2->songID) {
            insertAtTail(&head, &tail, l1->songID, l1->title, l1->artist);
            l1 = l1->next;
        } else if (l1->songID > l2->songID) {
            insertAtTail(&head, &tail, l2->songID, l2->title, l2->artist);
            l2 = l2->next;
        } else {
            l1 = l1->next; l2 = l2->next;
        }
    }
    while (l1) { insertAtTail(&head, &tail, l1->songID, l1->title, l1->artist); l1 = l1->next; }
    while (l2) { insertAtTail(&head, &tail, l2->songID, l2->title, l2->artist); l2 = l2->next; }
    return head;
}

