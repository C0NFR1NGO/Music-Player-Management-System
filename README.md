# 🎵 Music Playlist Management System

This repository contains a C implementation of a music playlist management system, designed to simulate features of modern music players like Spotify using a Linked List data structure. It was developed as a project for the CSL214: Data Structure and Program Design - II course.

## 🏗️ Data Structures

* 💿 **Playlist**: Implemented as a Doubly Linked List to support efficient navigation between songs using next and previous pointers. Each node represents a song containing a SongID, Title, and Artist.
* 🕰️ **Play History**: Implemented as a Stack (via a Linked List) to record and manage songs that have already been played.

## ✨ Features

The program features a menu-driven interface that allows users to perform various playlist operations and simulate a music player.

* ➕ **Add Song**: Inserts a new song while automatically keeping the playlist sorted based on SongID.
* 🗑️ **Delete Song**: Removes a specific song from the playlist using its unique SongID.
* 📋 **Display Playlist**: Shows all songs in the playlist. The output can be dynamically sorted by Title, by Artist, or first by Artist and then by Title.
* 🔍 **Search Song**: Finds specific tracks by querying the SongID, Title, or Artist.
* ⏭️ **Navigation**: Allows the user to play the next song or play the previous song in the list.
* 🔀 **Shuffle Mode**: Randomizes the order of the songs/nodes in the playlist.
* 🔁 **Repeat Mode**: Repeats and displays the playlist continuously.
* 📜 **Play History Tracker**: Automatically inserts a song into the Play History when it is played. Users can view this history in either chronological or reverse chronological order.
* 🧮 **Multi-List Operations**: Supports operations between two separate playlists (assuming both are sorted by SongID). This includes creating new playlists via Union, Intersection, Difference, and Symmetric Difference.

## 📂 File Structure

* 📄 `Functions.h`: Contains all struct definitions (`SongNode`, `HistoryNode`) and function prototypes.
* ⚙️ `Functions.c`: Contains the complete algorithmic implementation of the doubly linked list, stack history, sorting algorithms, and set operations.
* 🚀 `main.c`: Contains the main application loop, pre-loaded demo lists, and the interactive command-line menu.

## 💻 How to Compile and Run

To run this project locally, you will need a standard C compiler (like GCC).

1️⃣ Clone the repository to your local machine.
2️⃣ Open your terminal or command prompt.
3️⃣ Navigate to the directory containing the source files.
4️⃣ Compile the code using the following command:
   `gcc main.c Functions.c -o playlist_manager`
5️⃣ Run the executable:
   * 🪟 **Windows**: `playlist_manager.exe`
   * 🐧 **Linux/Mac**: `./playlist_manager`
