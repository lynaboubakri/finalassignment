//MusicRecommender.cpp
// - User chooses a genre (Pop, Rock, Hip-Hop, Jazz, Kids, Top2025)
// - User chooses a year interval (1975-1999, 2000-2011, 2011-2020, 2021-2025, or Top2025 special)
// - Program picks a random song from the selected set and prints "Title by Artist (Year) - Views"
// - User can request another recommendation (same filter), pick a new genre, or exit.

#include <iostream>    //cin, cout
#include <vector>     //vector container
#include <string>    //string
#include <cstdlib>  //rand(), srand()
#include <ctime>   //time() for seeding rand
#include <limits> //numeric_limits for input cleaning

using namespace std;

// Simple struct to represent a song (title, artist, year, views string)
struct Song {
    string title;
    string artist;
    int year;
    string views;
};

// Utility: filter a vector<Song> by year range (inclusive)
vector<Song> filterByYear(const vector<Song>& list, int startYear, int endYear) {
    vector<Song> out;
    for (const Song& s : list) {
        if (s.year >= startYear && s.year <= endYear) out.push_back(s);
    }
    return out;
}

// Utility: safely read an int in a range [minVal,maxVal]
int readIntInRange(int minVal, int maxVal) {
    int x;
    while (true) {
        if (cin >> x) {
            if (x >= minVal && x <= maxVal) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // clear rest of line
                return x;
            }
        }
        // invalid input
        cout << "Invalid input. Please enter a number between "<< minVal << " and " << maxVal << ":";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Utility: pick a random index 0..n-1 (assumes n>0)
int randomIndex(int n) {
    return rand() % n;
}

// Print the song 
void printSong(const Song& s) {
    cout << "\nWe recommend: \"" << s.title << "\" by " << s.artist << " (" << s.year << ") - " << s.views << " views\n" << endl;
}

int main() {
    // Seed random generator with current system time so results vary each run

    srand(static_cast<unsigned int>(time(nullptr)));

    // ---------------------------------
    // Category song databases
    // Each vector contains ~10 entries as requested
    // ---------------------------------
    vector<Song> pop = {
        {"Thriller", "Michael Jackson", 1982, "1.2B"},
        {"Like a Prayer", "Madonna", 1989, "450M"},
        {"...Baby One More Time", "Britney Spears", 1999, "780M"},
        {"Shape of You", "Ed Sheeran", 2017, "6B"},
        {"Blinding Lights", "The Weeknd", 2020, "5B"},
        {"Rolling in the Deep", "Adele", 2010, "2.3B"},
        {"Firework", "Katy Perry", 2010, "1.5B"},
        {"Flowers", "Miley Cyrus", 2023, "1B"},
        {"Vampire", "Olivia Rodrigo", 2023, "320M"},
        {"Top 2025 New Pop Song", "Artist TBD", 2025, "Fresh Release"}
    };

    vector<Song> rock = {
        {"Bohemian Rhapsody", "Queen", 1975, "1.8B"},
        {"Hotel California", "Eagles", 1977, "800M"},
        {"Smells Like Teen Spirit", "Nirvana", 1991, "1.6B"},
        {"Wonderwall", "Oasis", 1995, "1.2B"},
        {"Numb", "Linkin Park", 2003, "2.1B"},
        {"Boulevard of Broken Dreams", "Green Day", 2004, "650M"},
        {"Radioactive", "Imagine Dragons", 2012, "1.4B"},
        {"Believer", "Imagine Dragons", 2017, "2.3B"},
        {"Enemy", "Imagine Dragons", 2021, "1B"},
        {"Top 2025 Rock Anthem", "Artist TBD", 2025, "Fresh Release"}
    };

    vector<Song> hiphop = {
        {"Rapper's Delight", "The Sugarhill Gang", 1979, "50M"},
        {"Lose Yourself", "Eminem", 2002, "1.9B"},
        {"In Da Club", "50 Cent", 2003, "2B"},
        {"Gold Digger", "Kanye West ft. Jamie Foxx", 2005, "800M"},
        {"Empire State of Mind", "Jay-Z ft. Alicia Keys", 2009, "1.2B"},
        {"HUMBLE.", "Kendrick Lamar", 2017, "1.7B"},
        {"God's Plan", "Drake", 2018, "2.1B"},
        {"SICKO MODE", "Travis Scott", 2018, "1.4B"},
        {"Industry Baby", "Lil Nas X & Jack Harlow", 2021, "1.1B"},
        {"Top 2025 Hip-Hop Hit", "Artist TBD", 2025, "Fresh Release"}
    };

    vector<Song> jazz = {
        {"Take Five", "Dave Brubeck", 1959, "300M"},
        {"So What", "Miles Davis", 1959, "200M"},
        {"Feeling Good", "Nina Simone", 1965, "400M"},
        {"What a Wonderful World", "Louis Armstrong", 1967, "500M"},
        {"Autumn Leaves", "Bill Evans Trio", 1960, "150M"},
        {"Birdland", "Weather Report", 1977, "120M"},
        {"Spain", "Chick Corea", 1972, "100M"},
        {"Come Away With Me", "Norah Jones", 2002, "350M"},
        {"All of Me", "John Legend", 2013, "2B"},
        {"Top 2025 Jazz Piece", "Artist TBD", 2025, "Fresh Release"}
    };

    vector<Song> kids = {
        {"Baby Shark Dance", "Pinkfong", 2016, "13B"},
        {"Let It Go", "Idina Menzel (Frozen)", 2013, "2.5B"},
        {"Do You Want to Build a Snowman?", "Frozen Cast", 2013, "500M"},
        {"How Far I'll Go", "Auli'i Cravalho (Moana)", 2016, "1.1B"},
        {"Hakuna Matata", "The Lion King Cast", 1994, "800M"},
        {"Circle of Life", "The Lion King Cast", 1994, "600M"},
        {"Under the Sea", "Sebastian (The Little Mermaid)", 1989, "700M"},
        {"You're Welcome", "Dwayne Johnson (Moana)", 2016, "500M"},
        {"We Don't Talk About Bruno", "Encanto Cast", 2021, "600M"},
        {"Top 2025 Kids Song", "Artist TBD", 2025, "Fresh Release"}
    };

    // Special Top 2025 collection (we will use this for the "Top 2025" interval)
    vector<Song> top2025 = {
        {"New Horizons", "Future Artist", 2025, "Fresh Release"},
        {"AI Symphony", "Virtual DJ", 2025, "Fresh Release"},
        {"Skyline Dreams", "Pop Star X", 2025, "Fresh Release"},
        {"Electric Love 2.0", "DJ Nova", 2025, "Fresh Release"},
        {"Neon Lights", "Rising Star Y", 2025, "Fresh Release"},
        {"Rebirth", "Hip-Hop Prodigy", 2025, "Fresh Release"},
        {"Moonlit Groove", "Jazz Collective", 2025, "Fresh Release"},
        {"Galaxy Flow", "Electronic Band Z", 2025, "Fresh Release"},
        {"Hope Rising", "Pop Icon", 2025, "Fresh Release"},
        {"Final Frontier", "Legend Comeback", 2025, "Fresh Release"}
    };

    // -------------------------
    // Main program loop
    // -------------------------

    bool done = false;
    while (!done) {
        // 1) Choose genre
        cout << "Choose a genre:\n";
        cout << "1. Pop\n2. Rock\n3. Hip-Hop\n4. Jazz\n5. Kids\n6. Top 2025 (special)\n";
        cout << "Enter your choice (1-6): ";
        int genreChoice = readIntInRange(1, 6);

        // Pointer/reference to selected vector
        vector<Song> selectedList;
        switch (genreChoice) {
        case 1: selectedList = pop; break;
        case 2: selectedList = rock; break;
        case 3: selectedList = hiphop; break;
        case 4: selectedList = jazz; break;
        case 5: selectedList = kids; break;
        case 6:
            // If user selects Top 2025 genre directly, we will use top2025 list.
            selectedList = top2025;
            break;
        }

        bool backToGenre = false;
        while (!backToGenre) {
            // 2) Choose year interval
            cout << "\nChoose a year interval:\n";
            cout << "1. 1975 - 1999\n2. 2000 - 2011\n3. 2011 - 2020\n4. 2021 - 2025\n5. Top 2025 (special)\n";
            cout << "Enter your choice (1-5): ";
            int yearChoice = readIntInRange(1, 5);

            vector<Song> pool; // filtered songs to pick from
            if (yearChoice == 5) {
                // Top 2025 special: use the top2025 list regardless of chosen genre,
                // because "Top2025" is a cross-genre special collection.
                pool = top2025;
            }
            else {
                int startY = 1975, endY = 1999;
                if (yearChoice == 1) { startY = 1975; endY = 1999; }
                else if (yearChoice == 2) { startY = 2000; endY = 2011; }
                else if (yearChoice == 3) { startY = 2011; endY = 2020; }
                else if (yearChoice == 4) { startY = 2021; endY = 2025; }

                pool = filterByYear(selectedList, startY, endY);
            }

            // If pool empty -> inform user and let them choose another interval or genre
            if (pool.empty()) {
                cout << "\nNo songs found for this selection. Try a different interval or genre.\n";
                cout << "1. Try another interval (same genre)\n2. Choose new genre\n3. Exit\n";
                cout << "Enter (1-3): ";
                int fallback = readIntInRange(1, 3);
                if (fallback == 1) continue;       // loop back to interval selection
                if (fallback == 2) break;          // break to outer genre loop
                done = true; break;                // exit program
            }

            // 3) Pick a random song from pool
            int idx = randomIndex(static_cast<int>(pool.size()));
            printSong(pool[idx]);

            // 4) Ask what user wants next
            cout << "What would you like to do next?\n";
            cout << "1. Another recommendation (same genre & interval)\n";
            cout << "2. Choose a new genre\n";
            cout << "3. Exit\n";
            cout << "Enter your choice (1-3): ";
            int action = readIntInRange(1, 3);
            if (action == 1) {
                continue; // same genre & interval -> loop and recommend again
            }
            else if (action == 2) {
                backToGenre = true; // break inner loop back to genre choice
            }
            else {
                done = true;       // exit everything
                break;
            }
        } // end inner interval loop
    } // end main loop

    // Final message
    cout << "\nThanks for using the Music Recommender prototype!\n";
    return 0; // indicate success to the OS
}