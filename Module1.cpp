#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <sstream>
#include <algorithm>
#include <climits>
#include <iomanip>

 // For setw


using namespace std;



// Player structure


struct Player

 {
    int id;
// Unique player ID

    string name;
// Player name

    int age;
// Player age

    int score;
  // Player score


    vector<string> chatMessages;
// List of chat messages sent by the player


    string experience;
  // Player experience level (Beginner, Intermediate, Expert)


};

vector<Player> players;
// Vector to store all players


vector<vector<int>> adjList;

 // Adjacency list to represent player connections


// Initialize predefined players with 2-word chat messages


void initializePlayers()

{

// Sample players initialization with different attributes and messages

    players.push_back({1, "Alice", 25, 100, {"Hello world" }, "Beginner"});


    players.push_back({2, "Bob", 22, 150, {"Hi all"}, "Intermediate"});

    players.push_back({3, "Charlie", 28, 120, { "Fun game"}, "Advanced"});

    players.push_back({4, "David", 30, 80, { "Let's play"}, "Intermediate"});

    players.push_back({5, "Eve", 27, 200, {"I�m ready"}, "Expert"});

    players.push_back({6, "Frank", 24, 60, { "Let�s play"}, "Beginner"});

    players.push_back({7, "Grace", 23, 90, {"Hello world"}, "Intermediate"});

    players.push_back({8, "Hannah", 26, 130, {"Ready game", }, "Advanced"});

    players.push_back({9, "Ivy", 29, 110, {"Let�s start"}, "Intermediate"});

    players.push_back({10, "Jack", 21, 70, {"Let�s play"}, "Beginner"});

    players.push_back({11, "Kim", 31, 105, { "Let's go"}, "Intermediate"});

    players.push_back({12, "Liam", 32, 140, {"Nice try"}, "Advanced"});

    players.push_back({13, "Mona", 24, 115, {"Hello guys"}, "Beginner"});

    players.push_back({14, "Noah", 27, 125, {"What�s up"}, "Expert"});

    players.push_back({15, "Olivia", 22, 100, {"Good luck"}, "Intermediate"});

    players.push_back({16, "Paul", 29, 130, { "I�m ready"}, "Advanced"});

    players.push_back({17, "Quinn", 24, 95, {"Let's go"}, "Intermediate"});

    players.push_back({18, "Rachel", 26, 150, {"Good luck"}, "Expert"});

    players.push_back({19, "Sam", 28, 110, { "Let�s play"}, "Intermediate"});

    players.push_back({20, "Tina", 31, 135, { "Let�s do this"}, "Advanced"});

    players.push_back({21, "Ursula", 22, 120, {"Let�s go"}, "Beginner"});

    players.push_back({22, "Vera", 29, 140, {"Good luck"}, "Expert"});

    players.push_back({23, "Will", 23, 105, {"Ready to win"}, "Intermediate"});

    players.push_back({24, "Xander", 25, 115, {"Good luck"}, "Intermediate"});

    players.push_back({25, "Yara", 30, 125, {"Let�s go", }, "Advanced"});

    players.push_back({26, "Zara", 24, 100, { "Let�s start"}, "Beginner"});

    players.push_back({27, "Aaron", 32, 160, {"Let�s go"}, "Expert"});

    players.push_back({28, "Beth", 25, 90, {"Hey everyone"}, "Intermediate"});

    players.push_back({29, "Carl", 26, 140, {"Good luck"}, "Advanced"});

    players.push_back({30, "Diana", 30, 120, { "Let�s play"}, "Beginner"});

    players.push_back({31, "Ethan", 29, 110, { "Good game"}, "Intermediate"});

    players.push_back({32, "Fay", 23, 130, {"Let�s go"}, "Expert"});

    players.push_back({33, "Gage", 27, 115, {"Good luck"}, "Advanced"});

    players.push_back({34, "Holly", 25, 95, { "Let�s win"}, "Intermediate"});

    players.push_back({35, "Iris", 22, 105, {"Let�s go"}, "Intermediate"});

    players.push_back({36, "James", 28, 125, {"Good game"}, "Expert"});

    players.push_back({37, "Kate", 27, 130, { "Good luck"}, "Beginner"});

    players.push_back({38, "Leo", 23, 110, { "Good game"}, "Intermediate"});

    players.push_back({39, "Mia", 24, 140, {"We�re ready"}, "Expert"});

    players.push_back({40, "Nina", 25, 120, { "Good luck"}, "Advanced"});

    players.push_back({41, "Oscar", 30, 135, { "Let�s play"}, "Intermediate"});

    players.push_back({42, "Paige", 23, 110, { "Let�s win"}, "Beginner"});

    players.push_back({43, "Quincy", 28, 125, {"Ready for this"}, "Advanced"});

    players.push_back({44, "Riley", 25, 90, {"Good luck"}, "Intermediate"});

    players.push_back({45, "Steve", 29, 150, { "Good game"}, "Expert"});

    players.push_back({46, "Toby", 22, 80, {"Game on"}, "Beginner"});

    players.push_back({47, "Ulysses", 28, 125, {"Ready to play"}, "Advanced"});

    players.push_back({48, "Vince", 30, 140, {"Good luck"}, "Expert"});

    players.push_back({49, "Wendy", 23, 120, {"I�m here"}, "Intermediate"});

    players.push_back({50, "Xander", 29, 130, {"Good luck"}, "Beginner"});



    // Create adjacency list for player connections (you can customize this)

    adjList = vector<vector<int>>(players.size());



    // Add some sample connections for these players

    adjList[0].push_back(1);  // Alice is connected to Bob

    adjList[1].push_back(0);  // Bob is connected to Alice

    adjList[1].push_back(2);  // Bob is connected to Charlie

    adjList[2].push_back(1);  // Charlie is connected to Bob

    adjList[3].push_back(4);  // David is connected to Eve

    adjList[4].push_back(3);  // Eve is connected to David

    adjList[5].push_back(6);  // Frank is connected to Grace

    adjList[6].push_back(5);  // Grace is connected to Frank

    // Add more connections as needed...
}




// Helper function to split string into words



vector<string> splitWords(const string& str) {


    vector<string> words;


    stringstream ss(str);

    string word;

    while (ss >> word) {

        words.push_back(word);

  // Add each word from the chat message to the vector

    }


    return words;

// Return the vector containing all words

}





// Breadth-First Search (BFS) for exploring player connections



void bfs(int startPlayer) {

    vector<bool> visited(players.size(), false);
 // Track visited players

    queue<int> q;
  // Queue to store players to visit


    visited[startPlayer] = true;
// Mark the starting player as visited


    q.push(startPlayer);

// Get the first player in the queue



    cout << "\nBFS starting from player " << players[startPlayer].name << ":\n";




    while (!q.empty()) {


        int player = q.front();


        q.pop();

        cout << players[player].name << " ";

// Remove that player from the queue

// Print the player name

// Visit all neighbors of the current player

//----------------------------------------------//


        for (int neighbor : adjList[player]) {

            if (!visited[neighbor]) {

                visited[neighbor] = true;

                q.push(neighbor);

            }

        }
    }


    cout << endl;


}



// Depth-First Search (DFS) for exploring player connections


void dfs(int startPlayer) {

    vector<bool> visited(players.size(), false);

    stack<int> s;

    visited[startPlayer] = true;

    s.push(startPlayer);



    cout << "\nDFS starting from player " << players[startPlayer].name << ":\n";

    while (!s.empty()) {

        int player = s.top();

        s.pop();

        cout << players[player].name << " ";



        for (int neighbor : adjList[player]) {

            if (!visited[neighbor]) {

                visited[neighbor] = true;

                s.push(neighbor);

            }

        }
    }



    cout << endl;


}



// Display the menu options


void displayMenu() {

    cout << "\n===== Multiplayer Chat Game =====\n";

    cout << "1. Display Players\n";

    cout << "2. Add Players\n";

    cout << "3. Delete Players\n";

    cout << "4. Most Active Player\n";

    cout << "5. Least Active Player\n";

    cout << "6. Selection Sort Based on Score\n";

    cout << "7. Find Most Frequent Words in Chats\n";

    cout << "8. BFS - Find Player Connections\n";

    cout << "9. DFS - Find Player Connections\n";

    cout << "10. Exit\n";


}



// Display player details



void displayPlayers() {

    if (players.empty()) {

        cout << "No players available.\n";

        return;

    }



    cout << "\n";

    cout << left << setw(5) << "ID" << setw(15) << "Name" << setw(5) << "Age"



         << setw(8) << "Score" << setw(12) << "Experience" << "Chat Messages\n";

    cout << "---------------------------------------------------------------\n";



    for (const auto& player : players) {

        cout << left << setw(5) << player.id << setw(15) << player.name << setw(5) << player.age

             << setw(8) << player.score << setw(12) << player.experience;


        for
            (const auto& msg : player.chatMessages) {

            cout << msg << " ";
        }


        cout << endl;
    }

}





// Add a player to the list




void addPlayer() {

    Player newPlayer;

    cout << "Enter Player ID: ";

    cin >> newPlayer.id;

    cin.ignore();  // To ignore the newline character

    cout << "Enter Player Name: ";

    getline(cin, newPlayer.name);

    cout << "Enter Player Age: ";

    cin >> newPlayer.age;

    cout << "Enter Player Score: ";

    cin >> newPlayer.score;

    cin.ignore();  // To ignore the newline character

    cout << "Enter Player Experience: ";

    getline(cin, newPlayer.experience);



    // Restrict chat messages to 2 words only

    string chatMessage1, chatMessage2;

    cout << "Enter first 2-word chat message: ";

    getline(cin, chatMessage1);

    cout << "Enter second 2-word chat message: ";

    getline(cin, chatMessage2);

    newPlayer.chatMessages.push_back(chatMessage1);

    newPlayer.chatMessages.push_back(chatMessage2);



    players.push_back(newPlayer);

    adjList.push_back(vector<int>());

    cout << "Player added successfully.\n";


}





// Delete a player from the list

void deletePlayer() {

    int id;

    cout << "Enter Player ID to delete: ";

    cin >> id;



    // Use find_if to search for player by ID


    bool found = false;

    for (auto it = players.begin(); it != players.end(); ++it) {

        if (it->id == id) {

            players.erase(it);

            adjList.erase(adjList.begin() + (it - players.begin()));

            found = true;

            break;

        }

    }



    if (found) {

        cout << "Player deleted successfully.\n";

    } else {

        cout << "Player not found.\n";

    }
}




// Most Active Player



void mostActivePlayer() {

    if (players.empty()) {



        cout << "No players available.\n";

        return;



    }



    int maxMessages = 0;

    string activePlayer;




    // Find the player with the maximum messages



    for (const auto& player : players) {

        if (player.chatMessages.size() > maxMessages) {

            maxMessages = player.chatMessages.size();

            activePlayer = player.name;

        }



    }



    if (maxMessages > 0) {

        cout << "Most Active Player: " << activePlayer << " with " << maxMessages << " messages.\n";

    } else {

        cout << "No player has sent any messages.\n";

    }

}





// Least Active Player

void leastActivePlayer() {

    if (players.empty()) {

        cout << "No players available.\n";

        return;


    }



    int minMessages = INT_MAX;

    string inactivePlayer;




    // Find the player with the minimum messages



    for (const auto& player : players) {

        if (player.chatMessages.size() < minMessages) {

            minMessages = player.chatMessages.size();

            inactivePlayer = player.name;

        }



    }



    if (minMessages < INT_MAX) {

        cout << "Least Active Player: " << inactivePlayer << " with " << minMessages << " messages.\n";

    } else {

        cout << "No player has sent any messages.\n";



    }


}




// Find Most Frequent Words in Chats


void findMostFrequentWords() {

    map<string, int> wordCount;

    for (const auto& player : players) {


        for (const auto& message : player.chatMessages) {

            vector<string> words = splitWords(message);

            for (const string& word : words) {

                wordCount[word]++;

            }

        }

    }



    cout << "\nMost Frequent Words in Chats:\n";

    for (const auto& entry : wordCount) {

        cout << left << setw(15) << entry.first << " - " << entry.second << " occurrences\n";


    }
}





// Selection Sort based on player score

void selectionSortBasedOnScore() {

    for (int i = 0; i < players.size() - 1; i++) {

        int minIdx = i;

        for (int j = i + 1; j < players.size(); j++) {

            if (players[j].score < players[minIdx].score) {

                minIdx = j;

            }

        }

        if (minIdx != i) {

            swap(players[i], players[minIdx]);

        }

    }



    cout << "\nPlayers sorted by score:\n";

    displayPlayers();
}




int main() {

    // Initialize players with predefined names and attributes

    initializePlayers();



    int choice;


    while (true) {

        displayMenu();

        cout << "Enter your choice: ";

        cin >> choice;



        // Clear the input buffer to avoid issues with getline after cin

        cin.ignore();




        switch (choice) {

            case 1:

                displayPlayers();

                break;

            case 2:

                addPlayer();

                break;

            case 3:

                deletePlayer();

                break;

            case 4:

                mostActivePlayer();

                break;

            case 5:

                leastActivePlayer();

                break;

            case 6:

                selectionSortBasedOnScore();

                break;

            case 7:

                findMostFrequentWords();

                break;

            case 8:

                int startPlayerBFS;

                cout << "Enter player ID for BFS: ";

                cin >> startPlayerBFS;

                bfs(startPlayerBFS - 1);

                 // Player ID is 1-based, convert to 0-based

                break;

            case 9:

                int startPlayerDFS;

                cout << "Enter player ID for DFS: ";

                cin >> startPlayerDFS;

                dfs(startPlayerDFS - 1);  // Player ID is 1-based, convert to 0-based

                break;

            case 10:

                cout << "Exiting game...\n";

                return 0;

            default:

                cout << "Invalid choice. Try again.\n";
        }



    }



}




