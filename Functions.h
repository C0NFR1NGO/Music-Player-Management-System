#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Cross-platform compatibility for case-insensitive string comparison
#ifdef _WIN32
    #define strcasecmp _stricmp
#endif

// ======================= DATA STRUCTURES =======================

typedef struct SongNode {
    int songID;
    char title[100];
    char artist[100];
    struct SongNode* prev; 
    struct SongNode* next; 
} SongNode;

typedef struct HistoryNode {
    int songID;
    char title[100];
    char artist[100];
    struct HistoryNode* next;
} HistoryNode;

// Extern declaration so other files (like main.c) can access the global history
extern HistoryNode* historyTop;

// ======================= PLAY HISTORY FUNCTIONS =======================
void pushHistory(int id, const char* title, const char* artist);
void printChronological(HistoryNode* node);
void displayHistoryChronological(void);
void displayHistoryReverseChronological(void);

// ======================= PLAYLIST FUNCTIONS =======================
SongNode* createSongNode(int id, const char* title, const char* artist);
void addSong(SongNode** head, int id, const char* title, const char* artist);
void deleteSong(SongNode** head, int id);

// Sorting comparators
int cmpTitle(const void* a, const void* b);
int cmpArtist(const void* a, const void* b);
int cmpArtistTitle(const void* a, const void* b);

void displayPlaylist(SongNode* head, int sortType);
void searchSong(SongNode* head, int type, const char* query);
void shufflePlaylist(SongNode** head);
void repeatPlaylist(SongNode* head);

// ======================= MULTIPLE LIST OPERATIONS =======================
void insertAtTail(SongNode** head, SongNode** tail, int id, const char* title, const char* artist);
SongNode* unionLists(SongNode* l1, SongNode* l2);
SongNode* intersectLists(SongNode* l1, SongNode* l2);
SongNode* diffLists(SongNode* l1, SongNode* l2);
SongNode* symDiffLists(SongNode* l1, SongNode* l2);

#endif // FUNCTIONS_H