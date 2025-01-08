#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include <ctime>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <algorithm>

using namespace std;

#define INF INT_MAX

#define MAX_PLAYERS 5

// --------------------------------------------------------------------------------

// Dijkstra's Shortest Path Algorithm

// Class representing a graph of players (nodes)

class Graph

 {

private:

    int numPlayers;  // Number of players (nodes)

    vector<vector<int>> latencyMatrix;  // Adjacency matrix for storing latency

public:

    // Constructor to initialize the graph with the number of players

    Graph(int n)

     {

        numPlayers = n;

        latencyMatrix.resize(n, vector<int>(n, INT_MAX));  // Initialize latency matrix with infinity

    }

    // Add an edge between two players (nodes)

    void addEdge(int player1, int player2, int latency)

    {
        // Set latency for both directions since it's undirected

        latencyMatrix[player1][player2] = latency;


        latencyMatrix[player2][player1] = latency;
    }

    // Dijkstra's Algorithm to find the shortest path (min latency) from a source player

    void dijkstra(int source)

    {

        vector<int> distance(numPlayers, INT_MAX);

         // Distance from source to each player

        vector<bool> visited(numPlayers, false);

         // To check if a player is visited

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

         // Min heap

        // Start with the source player (initial latency is 0)

        distance[source] = 0;

        pq.push({0, source});

        // Push source with 0 latency

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        while (!pq.empty())

        {

            int currentPlayer = pq.top().second;


            // Get player with minimum latency

            int currentLatency = pq.top().first;

             // Get current latency

            pq.pop();

            // Remove the player from the priority queue

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

            if (visited[currentPlayer]) continue;

             // Skip if already visited

            visited[currentPlayer] = true;

            // Mark the player as visited

            // Check all neighbors of the current player

            for (int i = 0; i < numPlayers; i++)
            {

                // If there's an edge (latency) between current player and player i

                // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

                if (latencyMatrix[currentPlayer][i] != INT_MAX && !visited[i])

                {
                    int newLatency = currentLatency + latencyMatrix[currentPlayer][i];

                    // If a shorter path is found, update the latency and push into the queue

                    // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

                    if (newLatency < distance[i])
                    {

                        distance[i] = newLatency;

                        pq.push({newLatency, i});

                    }
                }

            }

        }

        // Display the minimum latency to each player from the source

        cout << "Minimum latency from Player " << source << ":\n";

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 0; i < numPlayers; i++)


         {
            if (distance[i] == INT_MAX)

             {

                cout << "Player " << i << ": No path\n";

                 // If no path found

            }

            else

            {
                cout << "Player " << i << ": " << distance[i] << "ms\n";
            }
        }

    }

    // Function to display the latency matrix (for debugging)

    void displayLatencyMatrix()

    {
        cout << "\nLatency Matrix:\n";

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 0; i < numPlayers; i++)

         {

            // Loop through all users

            // This loop iterates over the list of users to perform a specific action.
            for (int j = 0; j < numPlayers; j++)

             {

                if (latencyMatrix[i][j] == INT_MAX)

                 {

                    cout << "INF" << " ";
                }

                else

                 {

                    cout << latencyMatrix[i][j] << " ";
                }
            }

            cout << "\n";
        }
    }

};

// -----------------------------------------------------------------------------------------

// BELLMAN-FORD

// Structure representing a transition between players (or states)


struct Transition

 {
    int from, to, weight;
};

// Class representing the game graph

class GameGraph

{

private:

    int numPlayers;

    // Number of players (nodes)

    vector<Transition> transitions;

     // List of transitions between players

public:

    // Constructor to initialize the graph with the number of players

    GameGraph(int n)

    {

        numPlayers = n;

    }

    // Add a transition (edge) between two players

    void addTransition(int player1, int player2, int weight)

     {

        transitions.push_back({player1, player2, weight});

        transitions.push_back({player2, player1, weight});

         // Undirected graph: Add reverse transition

    }

    // Bellman-Ford algorithm to detect unstable game states (negative weight cycles)

    bool hasNegativeCycle()

     {

        vector<int> distances(numPlayers, INT_MAX);

        // Distance array initialized to infinity

        distances[0] = 0;

        // Set the distance of the starting player (player 0) to 0

        // Relax all transitions (edges) |V| - 1 times

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 1; i <= numPlayers - 1; i++)

         {

            bool updated = false;

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

            for (const auto& transition : transitions)

            {
                int u = transition.from, v = transition.to, weight = transition.weight;

                // If a shorter path is found, update the distance

                if (distances[u] != INT_MAX && distances[u] + weight < distances[v])

                {

                    distances[v] = distances[u] + weight;

                    updated = true;

                }

            }

            // Print the distance array after each relaxation step (for debugging)

            cout << "Iteration " << i << ": Distances from Player 0:\n";

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

            for (int j = 0; j < numPlayers; j++)

            {

                // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

                if (distances[j] == INT_MAX)

                    cout << "INF ";

                else
                    cout << "Distance to Player " << j << ": " << distances[j] << " ";

                cout << endl;

            }

            // If no updates occurred, break early (optimization)

            if (!updated) break;
        }

        // Check for negative weight cycles (unstable game states)

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (const auto& transition : transitions)

        {

            int u = transition.from, v = transition.to, weight = transition.weight;

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

            if (distances[u] != INT_MAX && distances[u] + weight < distances[v])

            {

                // Negative cycle detected

                return true;
            }
        }

        // No negative cycle detected

        return false;
    }

    // Function to display all transitions (edges) in the game graph (for debugging)

    void showTransitions()

    {

        cout << "\nGame Transitions (Player1, Player2, Transition Value):\n";

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (const auto& transition : transitions)

         {
            cout << "Player " << transition.from << " <-> Player " << transition.to << " : " << transition.weight << "\n";

        }

    }
};

// ------------------------------------------------------------------------------------

// Floyd-Warshall Algorithm Class to manage the communication graph

// Define constants for the maximum latency (infinity) and the maximum number of players


#define INF INT_MAX

#define MAX_PLAYERS 5

// Floyd-Warshall Algorithm Class to manage the communication network

class CommunicationNetwork

 {

private:

    int totalPlayers;

    vector<vector<int>> communicationLatency;

public:


    // Constructor to initialize the network with the number of players

    CommunicationNetwork(int players)

     {

        totalPlayers = players;

        communicationLatency.resize(totalPlayers, vector<int>(totalPlayers, INF));

        // Initialize the diagonal elements as 0 (distance from player to itself is 0)

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 0; i < totalPlayers; ++i)

         {

            communicationLatency[i][i] = 0;

        }
    }

    // Add a communication link (connection) with a specific latency


    void addLink(int player1, int player2, int latency)

     {

        communicationLatency[player1][player2] = latency;

        communicationLatency[player2][player1] = latency;

        // Undirected graph
    }

    // Apply Floyd-Warshall Algorithm to find the shortest communication paths

    void calculateShortestPaths()

    {
        // Three nested loops to update the shortest path latencies

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.


        for (int k = 0; k < totalPlayers; ++k)

        {

            for (int i = 0; i < totalPlayers; ++i)

             {

                // Loop through all users

        // This loop iterates over the list of users to perform a specific action.
                for (int j = 0; j < totalPlayers; ++j)

                 {


                    // If a shorter path is found between i and j through k, update the latency

                    if (communicationLatency[i][k] != INF && communicationLatency[k][j] != INF

                        && communicationLatency[i][k] + communicationLatency[k][j] < communicationLatency[i][j]) {

                        communicationLatency[i][j] = communicationLatency[i][k] + communicationLatency[k][j];
                    }
                }

            }
        }

    }

    // Print the resulting shortest communication latency matrix


    void printLatencyMatrix()

    {

        cout << "\nShortest Communication Latencies (in milliseconds):\n";

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 0; i < totalPlayers; ++i)

         {

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

            for (int j = 0; j < totalPlayers; ++j)

             {

                // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

                if (communicationLatency[i][j] == INF)
                    cout << "INF ";

                else
                    cout << communicationLatency[i][j] << " ";

            }
            cout << endl;
        }

    }

    // Display the shortest communication latency between two specific players

    void showShortestPath(int player1, int player2)

     {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        if (communicationLatency[player1][player2] == INF)

            cout << "No direct communication path between Player " << player1 << " and Player " << player2 << endl;

        else

            cout << "Shortest communication latency from Player " << player1 << " to Player " << player2

                 << " is " << communicationLatency[player1][player2] << " milliseconds." << endl;
    }

};


// --------------------------------------------------------------------------------


//  QUEUES

// Class to represent a Player in the simulation

class Gamer

 {

private:

    int gamerId;

    queue<string> messageBox;

    // Queue to store messages for each player

public:

    Gamer(int id) : gamerId(id) {}

    // Get gamer ID

    int getId()

    {

        return gamerId;
    }

    // Add a message to the gamer's message box


    void receiveNotification(const string& notification)

     {

        messageBox.push(notification);
    }

    // Process and print the notification from the message box (i.e., receive the message)

    void processNotification()

    {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.
        if (!messageBox.empty())

         {


            cout << "Gamer " << gamerId << " received: " << messageBox.front() << endl;

            messageBox.pop();

            // Remove the message after it's processed

        }

        else

         {

            cout << "Gamer " << gamerId << " has no new notifications." << endl;
        }

    }

    // Display the current message box size (optional)


    int getMessageCount()

    {

        return messageBox.size();
    }
};

// Class to manage the Game and Gamers


class Simulation

{

private:

    vector<Gamer> gamers;

    // List of gamers in the simulation

public:

    // Initialize the simulation with a given number of gamers

    Simulation(int totalGamers)

    {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 0; i < totalGamers; i++)

         {

            gamers.push_back(Gamer(i));
        }
    }

    // Send a notification from one gamer to another (using message box for message transmission)


    void deliverNotification(int fromGamer, int toGamer, const string& notification)

    {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        if (fromGamer == toGamer)

        {

            cout << "Gamer " << fromGamer << " cannot send a notification to themselves!" << endl;

            return;
        }

        cout << "Gamer " << fromGamer << " sends notification to Gamer " << toGamer << ": " << notification << endl;

        gamers[toGamer].receiveNotification(notification);

        // Enqueue the notification for the recipient gamer

    }

    // Simulate gamers receiving notifications


    void processNotifications()

     {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (auto& gamer : gamers)

         {

            gamer.processNotification();
        }
    }

    // Display the current status of the simulation (i.e., current state of each gamer's message box)

    void displaySimulationStatus()

    {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (auto& gamer : gamers)

         {

            cout << "Gamer " << gamer.getId() << " has " << gamer.getMessageCount() << " notification(s) in their message box." << endl;
        }
    }

};


// Function to simulate user-defined notification sending in the simulation

void runSimulation(Simulation& simulation, int totalGamers, int totalNotifications)

 {

    // Ask user for the notifications to be sent

    // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

    for (int i = 0; i < totalNotifications; i++)

     {

        int fromGamer, toGamer;

        string notification;

        // Ask for sender and receiver


        cout << "\nNotification " << i + 1 << " - Enter the sender's gamer ID (0 to " << totalGamers - 1 << "): ";

        cin >> fromGamer;


        cout << "Enter the receiver's gamer ID (0 to " << totalGamers - 1 << "): ";

        cin >> toGamer;

        // Ensure that the sender and receiver are different

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        while (fromGamer == toGamer)

        {

            cout << "Gamer " << fromGamer << " cannot send a notification to themselves. Please choose a different receiver.\n";

            cout << "Enter the receiver's gamer ID (0 to " << totalGamers - 1 << "): ";

            cin >> toGamer;

        }

        // Ask for the message to be sent

        cout << "Enter the notification message: ";

        cin.ignore();

        // Ignore any leftover newline character from previous input

        getline(cin, notification);

        simulation.deliverNotification(fromGamer, toGamer, notification);

        // Send the notification

    }

    // Process and display the state of the simulation after sending all notifications

    simulation.processNotifications();


    simulation.displaySimulationStatus();
}

// -----------------------------------------------------------------------------------

// ARRAYS

class ChatSystem

 {

private:

    int totalPlayers;

    vector<vector<string>> communicationMatrix;

    // 2D array to store messages

public:

    ChatSystem(int players)

     {

        totalPlayers = players;

        communicationMatrix.resize(totalPlayers, vector<string>(totalPlayers, ""));

        // Initialize with empty strings
    }

    // Send a message from one player to another

    void sendChatMessage(int sender, int receiver, const string& chatMessage)

    {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        if (sender == receiver)

         {

            cout << "Player " << sender << " cannot send a message to themselves!" << endl;

            return;

        }

        communicationMatrix[sender][receiver] = chatMessage;

        // Store the message

        cout << "Player " << sender << " sends message to Player " << receiver << ": " << chatMessage << endl;
    }

    // Display all messages for a specific player


    void showMessagesForPlayer(int playerId)

     {

        cout << "Messages for Player " << playerId << ":\n";

        bool hasMessages = false;

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 0; i < totalPlayers; ++i)

         {

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.


            if (!communicationMatrix[i][playerId].empty())

             {


                cout << "From Player " << i << ": " << communicationMatrix[i][playerId] << endl;

                hasMessages = true;
            }
        }

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        if (!hasMessages)

         {

            cout << "No messages for Player " << playerId << ".\n";

        }
    }

};


// ------------------------------------------------------------------------------------


// LINKED LIST

// Class to represent each User in the simulation


class User
{

private:

    int userId;

     // ID of the user

    vector<string> inbox;

     // A list to store messages for each user

public:

    // Constructor to initialize user with an ID

    User(int id) : userId(id) {}

    // Function to get the user's ID

    int getId()
     {

        return userId;
    }

    // Function to add a message to the user's inbox

    void receiveMessage(const string& message)

     {
        inbox.push_back(message);


         // Adds the message to the inbox

    }

    // Function to display all messages for this user

    void displayMessages()

     {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        if (inbox.empty())

        {
            cout << "User " << userId << " has no messages.\n";

        }

        else

         {
            cout << "Messages for User " << userId << ":\n";

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

            for (const string& message : inbox)

             {
                cout << message << endl;
            }

        }

    }

};

// Class to represent the entire Interaction Simulation


class InteractionSimulation

{

private:

    vector<User> users;

    // A list to hold all users in the simulation

public:

    // Constructor to create a list of users based on the input number

    InteractionSimulation(int totalUsers)

    {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 0; i < totalUsers; ++i)

         {

            users.push_back(User(i));

             // Adds new users to the list

        }

    }

    // Function to send a message from one user to another

    void sendMessage(int senderId, int receiverId, const string& message)

     {

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        if (senderId != receiverId)


         {

            users[receiverId].receiveMessage("Message from User " + to_string(senderId) + ": " + message);
        }
    }

    // Function to simulate sending random messages between users

    void simulateMessages(int numMessages)

    {
        srand(time(0));

         // Initializes random number generator

         // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (int i = 0; i < numMessages; ++i)

        {

            int senderId = rand() % users.size();

             // Random sender

            int receiverId = rand() % users.size();

            // Random receiver

            // Ensure the sender and receiver are different

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

            while (senderId == receiverId)

            // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

            {

                receiverId = rand() % users.size();
            }

            // Send a random message from sender to receiver

            sendMessage(senderId, receiverId, "Random Message " + to_string(i + 1));

        }
    }

    // Function to show the status of all users in the simulation

    void showSimulationStatus()

    {
        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        for (auto& user : users)

         {
            user.displayMessages();

            // Display all messages for each user

        }

    }
};

// Function to initialize and start the simulation

void startSimulation(int totalUsers, int totalMessages)

 {

    // Create a new simulation instance

    InteractionSimulation simulation(totalUsers);

    // Simulate random messages being sent

    simulation.simulateMessages(totalMessages);

    // Show all the messages for each user

    simulation.showSimulationStatus();
}

// -------------------------------------------------------------------------------------

// PLAYER DETAILS

// Define a struct to hold player details in a chat game

struct Gamer1
{

    int uniqueID;

     // Unique ID

    string nickname;

       // Player's nickname

    int age;

       // Player's age

    double score;

         // Points earned based on actions

    int wins;

       // Number of wins

    int losses;

      // Number of losses

    vector<string> chatHistory;

    // List of messages sent by the player

    // Constructor to initialize player details

    Gamer1(int id, string name, int years, double points)
        : uniqueID(id), nickname(name), age(years), score(points), wins(0), losses(0) {}

    // Method to display gamer details

    void displayInfo() const
     {

        cout << "ID: " << uniqueID << ", Nickname: " << nickname

             << ", Age: " << age << ", Score: " << score

             << ", Wins: " << wins << ", Losses: " << losses

             << ", Messages: ";

        for (const auto& message : chatHistory)

        {

            cout << "\"" << message << "\" ";

        }

        cout << endl;

    }

    // Method to add a chat message and assign points based on message content

    void addChatMessage(string message, double points)
     {

        chatHistory.push_back(message);

        score += points;

    }

    // Method to register a victory

    void recordWin()
     {

        wins++;

    }

    // Method to register a defeat

    void recordLoss()
    {

        losses++;

    }

};

// Function to get a positive integer input

int getValidInteger()

 {

    int value;

    while (true)

    {

        cin >> value;

        if (value > 0)
         {

            return value;

        }

         else

          {

            cout << "Please enter a valid positive integer: ";

        }

    }
}


// Function to validate the age input (1 to 100 years)

int getValidAge()
{

    int age;

    while (true)
     {

        cin >> age;

        if (age > 0 && age <= 100)
         {

            return age;

        }

        else

         {

            cout << "Please enter a valid age (1-100): ";

        }

    }

}

// Function to validate score input (non-negative)

double getValidScore()
{

    double score;

    while (true)
    {

        cin >> score;

        if (score >= 0)
         {

            return score;

        }
        else

        {

            cout << "Please enter a valid score value (>= 0): ";

        }

    }
}

// Function to display all gamers in the game

void showAllGamers(const vector<Gamer1>& gamers)
{

    cout << "\nGamer Information:\n";

    for (const auto& gamer : gamers)
     {

        gamer.displayInfo();

    }

}

// Function to sort gamers by their scores (highest to lowest)


void sortByScore(vector<Gamer1>& gamers)
{

    sort(gamers.begin(), gamers.end(), [](const Gamer1& a, const Gamer1& b)
     {

        return a.score > b.score;

    });
}

// Function to find a gamer by their unique ID


Gamer1* findGamerByID(vector<Gamer1>& gamers, int id)
 {

    for (auto& gamer : gamers)
     {

        if (gamer.uniqueID == id)

        {

            return &gamer;

        }

    }

    return nullptr;

}

// Function to start a new chat challenge


void startChatChallenge(vector<Gamer1>& gamers)

{

    cout << "\nInitiating new chat challenge...\n";

    for (auto& gamer : gamers)

     {

        cout << "Enter a chat message for gamer " << gamer.nickname << ": ";

        cin.ignore();

         // Clear input buffer

        string message;

        getline(cin, message);



        cout << "Enter points awarded for this message: ";

        double points = getValidScore();



        gamer.addChatMessage(message, points);

        cout << gamer.nickname << "'s total score after this message: " << gamer.score << endl;

    }
}

// Function to display gamers sorted by their scores

void displaySortedGamersByScore(vector<Gamer1>& gamers)

{

    sortByScore(gamers);

    cout << "\nGamers sorted by score (highest to lowest):\n";

    showAllGamers(gamers);

}

// Function to modify a gamer's details

void modifyGamerDetails(vector<Gamer1>& gamers)

{

    cout << "\nModify Gamer Details:\n";

    cout << "Enter gamer ID to update: ";

    int updateID;

    cin >> updateID;


    Gamer1* gamer = findGamerByID(gamers, updateID);

    if (gamer)
    {

        cout << "Enter new score for gamer " << gamer->nickname << ": ";

        double newScore = getValidScore();

        gamer->score = newScore;

        cout << "Score updated successfully!" << endl;

    }

    else

     {

        cout << "Gamer with ID " << updateID << " not found!" << endl;

    }

}

//---------------------------------------------------------------------------------------

// Main function to run the interaction simulation

// The main function calls thall the above functions.
int main6()
{
    int numPlayers;

    cout<<"Dijkstra's Shortest Path Algorithm\n";

    cout<<"\nLATENCY IN THE GAME NETWORK\n";

    cout << "\nEnter number of players in the game (minimum 4 players required):\n ";

    cin >> numPlayers;

    // Create a graph for players

    Graph gameGraph(numPlayers);

    // Example: Adding edges (latency) between players

    gameGraph.addEdge(0, 1, 10);

     // Player 0 and Player 1 latency = 10ms

    gameGraph.addEdge(0, 2, 20);

    // Player 0 and Player 2 latency = 20ms

    gameGraph.addEdge(1, 2, 5);

     // Player 1 and Player 2 latency = 5ms

    gameGraph.addEdge(1, 3, 15);

     // Player 1 and Player 3 latency = 15ms

    gameGraph.addEdge(2, 3, 30);

    // Player 2 and Player 3 latency = 30ms

    // Display the graph's latency matrix

    // gameGraph.displayLatencyMatrix();

    // Choose a source player to calculate the minimum latency from

    // Initialize variables

    int sourcePlayer;

    cout << "\nEnter the player (0 to " << numPlayers - 1 << ") from which to calculate minimum latency: ";

    cin >> sourcePlayer;


    // Run Dijkstra's algorithm to find the minimum latency from the chosen source player

    gameGraph.dijkstra(sourcePlayer);


    // ---------------------------------------------------------------------------------

    // BELLMAN-FORD

    // Initialize variables

    int numPlayers1;

    cout<<"\nBellman-Ford Algorithm\n";

    cout<<"\nDETECT UNSTABLE COMMUNICATION IN THE NETWORK (DETECT NEGATIVE WEIGHT CYCLE)\n";

    cout << "\nEnter the number of players (game states): \n";

    cin >> numPlayers1;

    // Create a game graph with the specified number of players

    GameGraph graph(numPlayers1);

    // Example: Adding transitions between game states (with latency, errors, or other factors)

    graph.addTransition(0, 1, 10);

    // Player 0 to Player 1 transition

    graph.addTransition(1, 2, -5);

     // Player 1 to Player 2 transition (negative weight)

    graph.addTransition(2, 3, 20);

     // Player 2 to Player 3 transition

    graph.addTransition(3, 1, -10);

    // Player 3 to Player 1 transition (negative weight)

    // Display all transitions in the graph

    graph.showTransitions();

    // Detect if there are any negative weight cycles (unstable game states)

    bool unstableStateDetected = graph.hasNegativeCycle();

    // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

    if (unstableStateDetected)

    {

        cout << "\nUnstable game state detected! Negative weight cycle present.\n";
    }

     else

     {
        cout << "\nNo unstable game states detected. The system is stable.\n";

    }

    // ---------------------------------------------------------------------------

    // FLOYD-WARSHALL

    // Number of players in the network

    // Initialize variables

    int totalPlayers2 = 5;

    cout<<"\nFloyd-Warshall Algorithm\n";

    cout<<"\nDISPALY LATENCY IN THE SHORTEST PATH\n";

    // Create a CommunicationNetwork object to manage latency between players

    CommunicationNetwork network(totalPlayers2);

    // Add communication links with latencies between players

    network.addLink(0, 1, 10);

    // Player 0 and Player 1 communication latency of 10ms

    network.addLink(0, 2, 5);

     // Player 0 and Player 2 communication latency of 5ms

    network.addLink(1, 2, 2);

     // Player 1 and Player 2 communication latency of 2ms

    network.addLink(1, 3, 1);

     // Player 1 and Player 3 communication latency of 1ms

    network.addLink(2, 3, 3);

     // Player 2 and Player 3 communication latency of 3ms

    network.addLink(3, 4, 8);

     // Player 3 and Player 4 communication latency of 8ms

    network.addLink(2, 4, 9);

     // Player 2 and Player 4 communication latency of 9ms

    // Apply the Floyd-Warshall algorithm to calculate the shortest communication paths

    network.calculateShortestPaths();

    // Display the shortest communication latency matrix between all players

    // network.printLatencyMatrix();

    // Display the shortest communication path between specific players

    network.showShortestPath(0, 4);

    // From Player 0 to Player 4

    network.showShortestPath(1, 3);

    // From Player 1 to Player 3

    network.showShortestPath(2, 0);

     // From Player 2 to Player 0

    // Example where there is no direct communication path (latency will be INF)

    network.showShortestPath(4, 1);

     // From Player 4 to Player 1


    // -------------------------------------------------------------------------

    //QUEUES

    // Initialize variables

     int totalGamers, totalNotifications;

    // Get user input for number of gamers and notifications

    cout<<"\nQueues (for message transmission)\n";

    cout << "\nEnter the number of gamers: \n";

    cin >> totalGamers;

    cout << "\nEnter the number of notifications to simulate: \n";

    cin >> totalNotifications;

    // Create a simulation instance

    Simulation simulation(totalGamers);

    // Simulate user-defined notification sending and receiving in the simulation

    runSimulation(simulation, totalGamers, totalNotifications);


    // -----------------------------------------------------------------------

    // ARRAYS

    cout<<"\nArrays (for storing distances and paths)\n";

    cout<<"\nLINK MESSAGES SENT TO RECIEVER FROM SENDER\n";

    // Initialize variables

    int totalPlayers3;

    cout << "\nEnter number of players: \n";

    cin >> totalPlayers3;

    ChatSystem chatApp(totalPlayers3);

    // Simulate sending messages based on user input

    // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

    while (true)

    {

        int sender, receiver;

        string chatMessage;

        cout << "\nEnter sender player ID (-1 to stop): \n";

        cin >> sender;

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        if (sender == -1) break;

        cout << "\nEnter receiver player ID: \n";

        cin >> receiver;

        // Validate player IDs

        // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

        if (sender < 0 || receiver < 0 || sender >= totalPlayers3 || receiver >= totalPlayers3) {

            cout << "\nInvalid player IDs!\n";

            continue;
        }

        cin.ignore();

        // To ignore leftover newline

        cout << "\nEnter message: \n";

        getline(cin, chatMessage);

        chatApp.sendChatMessage(sender, receiver, chatMessage);

        // Send the message

    }

    // Display all messages after input

    // Loop through all users

        // This loop iterates over the list of users to perform a specific action.

    for (int i = 0; i < totalPlayers3; ++i)

     {

        chatApp.showMessagesForPlayer(i);

         // Show messages for each player
    }


// --------------------------------------------------------------------------------

// LINKED LIST

    // Define the number of users and messages

    // Initialize variables

    int totalUsers = 5;

     // Number of users in the simulation

    // Initialize variables

    int totalMessages = 10;

     // Number of random messages to simulate

    // Start the simulation

    cout<<"\nLinked Lists (for dynamic player connections)\n";

    cout<<"\nLINK MESSAGES SENT TO EACH OTHER\n";

    startSimulation(totalUsers, totalMessages);

    return 0;

}
int main1()

{
    // displaying the purpose of the programe

    cout<<"\nMINIMIZING LATENCY FOR EFFICIENT GAME NETWORKING\n";

    // displaying all algorithms used

    // cout<<"\nALGORITHMS AND SORTING TECHNIQUES USED\n";

    // cout<<"\nDijkstra's Shortest Path Algorithm\n";

    // cout<<"Bellman-Ford Algorithm\n";

    // cout<<"Floyd-Warshall Algorithm\n";

    // cout<<"Queues (for message transmission)\n";

    // cout<<"Arrays (for storing distances and paths)\n";

    // cout<<"Linked Lists (for dynamic player connections)\n";

    // cout<<"Bubble Sort\n";

    int totalGamer;

    // Ask for the number of gamers

    cout << "\nEnter the number of gamers: ";

    cin >> totalGamer;

    // Check for valid number of gamers

    if (totalGamer <= 0)
     {

        cout << "Please enter a valid number of gamers." << endl;

        return 1; // Exit the program if the number is invalid
    }

    // Create a vector to store gamer data

    vector<Gamer1> gamers;

    // Input gamer details
    for (int i = 0; i < totalGamer; ++i)
    {

        cout << "Enter details for gamer " << i + 1 << ":\n";

        // Gamer Unique ID

        cout << "Gamer ID: ";

        int gamerID = getValidInteger();

        // Gamer Nickname

        cout << "Gamer Nickname: ";

        string nickname;

        cin.ignore();

         // To clear the buffer from previous input

        getline(cin, nickname);

        // Gamer Age

        cout << "Gamer Age: ";

        int age = getValidAge();

        // Gamer Score

        cout << "Gamer Score: ";

        double score = getValidScore();

        // Create a new gamer and add to the gamers vector

        gamers.push_back(Gamer1(gamerID, nickname, age, score));

        cout << endl;
    }

    // Main program loop

    int userChoice;

    do
    {
        cout << "\nSelect an action:\n";

        cout << "1. Show All Gamers\n";

        cout << "2. Start a New Chat Challenge\n";

        cout << "3. Sort Gamers by Score\n";

        cout << "4. Modify Gamer Details\n";

        cout << "5. Latency in the Game Networking\n";

        cout << "6. Exit\n";

        cout << "Enter choice: ";

        cin >> userChoice;

        switch (userChoice)
        {

            case 1:

                showAllGamers(gamers);

                break;

            case 2:

                startChatChallenge(gamers);

                break;

            case 3:

                displaySortedGamersByScore(gamers);

                break;

            case 4:

                modifyGamerDetails(gamers);

                break;

            case 5:

                main6();

                break;

            case 6:

                cout << "Exiting the program.\n";

                break;

            default:

                cout << "Invalid choice, please try again.\n";

        }
    }

    while (userChoice != 6);


    // --------------------------------------------------------------
}
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <ctime> // For timestamps
#include <sstream>

using namespace std;



// Function to compute the hash of a string

long long computeHash(const string& str, int prime, int modulus)


 {

    long long hash = 0;

    int n = str.length();

    for (int i = 0; i < n; i++)

        {

        hash = (hash * prime + str[i]) % modulus;

    }

    return hash;
}

// Function to compute the highest power of prime for hashing

long long computeHighestPower(int length, int prime, int modulus)

{

    long long highestPower = 1;

    for (int i = 0; i < length - 1; i++)

        {

        highestPower = (highestPower * prime) % modulus;

    }

    return highestPower;
}

// Function to perform Rabin-Karp search for a pattern in text

vector<int> rabinKarpSearch(const string& text, const string& pattern, int prime = 31, int modulus = 1e9 + 7)

 {

    int m = pattern.length();

    int n = text.length();



    // Compute the highest power of prime

    long long highestPower = computeHighestPower(m, prime, modulus);



    // Compute initial hash values for the pattern and the first window

    long long patternHash = computeHash(pattern, prime, modulus);

    long long windowHash = computeHash(text.substr(0, m), prime, modulus);



    vector<int> positions; // Store starting indices of matches



    // Verbose output

    cout << "Initial Pattern Hash: " << patternHash << "\n";

    cout << "Initial Window Hash: " << windowHash << "\n\n";



    // Slide the window over the text

    for (int i = 0; i <= n - m; i++)

        {

        // If hashes match, verify the substring

        if (patternHash == windowHash)

        {

            if (text.substr(i, m) == pattern)

            {

                positions.push_back(i);

                cout << "Pattern match found at index " << i << "\n";

            }

        }



        // Compute the hash for the next window

        if (i < n - m)

            {

            windowHash = (windowHash - text[i] * highestPower) % modulus;

            windowHash = (windowHash * prime + text[i + m]) % modulus;



            // Ensure positive hash

            if (windowHash < 0)

                {

                windowHash += modulus;

            }



            // Verbose output for each sliding window

            cout << "Window [" << i + 1 << "]: Hash = " << windowHash << "\n";
        }

    }




    return positions;
}




// Function to display all messages

void displayMessages(const vector<string>& messages)

 {

    cout << "\nGame Messages:\n";

    cout << string(40, '-') << "\n";

    for (size_t i = 0; i < messages.size(); i++)

        {

        cout << "Message " << i + 1 << ": " << messages[i] << "\n";

    }

    cout << string(40, '-') << "\n";

}



// Function to display search results

void displaySearchResults(const vector<int>& positions, int messageIndex, const string& pattern)

{

    if (!positions.empty())

        {


        cout << "Pattern \"" << pattern << "\" found in message " << messageIndex + 1 << " at positions: ";

        for (int pos : positions)

         {

            cout << pos << " ";

        }

        cout << "\n";

    }

    else

        {

        cout << "Pattern \"" << pattern << "\" not found in message " << messageIndex + 1 << ".\n";

    }

}



//------------------------------------------------------------------



// Function to simulate searching for patterns in game messages



void simulateGameNetworkingWithRabinKarp()

{

    vector<string> messages =

    {


        "Update Player Position",

        "Critical Health Alert",

        "Send Cosmetic Update",

        "Enemy Spotted",

        "Player Joined Game"

    };



    string pattern = "Player"; // Pattern to search for



    // Display messages



    displayMessages(messages);




    cout << "\nStarting Rabin-Karp Search for pattern: \"" << pattern << "\"\n";

    cout << string(40, '=') << "\n";



    // Search for the pattern in each message



    for (size_t i = 0; i < messages.size(); i++)

        {

        vector<int> positions = rabinKarpSearch(messages[i], pattern);

        displaySearchResults(positions, i, pattern);

    }



    cout << string(40, '=') << "\n";

    cout << "Rabin-Karp Search Complete.\n";
}





// Structure to hold game message data

struct GameMessage


 {

    int priority;   // Lower values mean higher priority

    string message; // The content of the message



    // Overload the comparison operator for heap sort

    bool operator>(const GameMessage& other) const

     {

        return priority > other.priority;

    }
};




// Function to display messages


void displayMessages(const vector<GameMessage>& messages, const string& title)

 {

    cout << title << "\n";

    cout << setw(10) << "Priority" << setw(30) << "Message Content\n";

    cout << string(40, '-') << "\n";



    for (const auto& msg : messages)


        {

        cout << setw(10) << msg.priority << setw(30) << msg.message << "\n";

    }

    cout << string(40, '-') << "\n";
}




// Function to heapify a subtree rooted at index i

void heapify(vector<GameMessage>& messages, int n, int i)

 {

    int largest = i;      // Initialize largest as root

    int left = 2 * i + 1; // Left child index

    int right = 2 * i + 2; // Right child index



    // Check if the left child exists and has a higher priority



    if (left < n && messages[left] > messages[largest])

        {

        largest = left;

    }



    // Check if the right child exists and has a higher priority



    if (right < n && messages[right] > messages[largest])


        {

        largest = right;

    }



    // If the largest is not the root, swap and heapify the affected subtree



    if (largest != i)

        {

        swap(messages[i], messages[largest]);

        heapify(messages, n, largest);


    }
}





// Function to build a max heap from a given list of messages




void buildMaxHeap(vector<GameMessage>& messages)

 {


    int n = messages.size();

    for (int i = n / 2 - 1; i >= 0; i--)

        {


        heapify(messages, n, i);

    }

}




// Function to perform heap sort




void heapSort(vector<GameMessage>& messages)

 {


    buildMaxHeap(messages); // Step 1: Build the max heap

    int n = messages.size();




    // Step 2: Extract elements one by one




    for (int i = n - 1; i > 0; i--)

        {


        // Move current root to the end




        swap(messages[0], messages[i]);




        // Heapify the reduced heap




        heapify(messages, i, 0);
    }

}





// Function to add a new message to the list




void addMessage(vector<GameMessage>& messages, int priority, const string& content)

{


    messages.push_back({priority, content});

}



// Function to simulate the process




void simulateGameNetworking()

 {


    vector<GameMessage> messages;



    // Add some messages with varying priorities




    addMessage(messages, 3, "Update Player Position");


    addMessage(messages, 1, "Critical Health Alert");

    addMessage(messages, 4, "Send Cosmetic Update");

    addMessage(messages, 2, "Enemy Spotted");




    // Display messages before sorting




    displayMessages(messages, "Messages Before Sorting");




    // Perform heap sort to prioritize messages



    heapSort(messages);




    // Display messages after sorting



    displayMessages(messages, "Messages After Sorting");
}



// Function to compute the prefix-suffix table (LPS array)




vector<int> computeLPSArray(const string& pattern)
 {


    int m = pattern.length();

    vector<int> lps(m, 0);



    int len = 0; // Length of the previous longest prefix-suffix


    int i = 1;



    while (i < m)


        {

        if (pattern[i] == pattern[len])

         {

            len++;

            lps[i] = len;

            i++;

        }

    else

        {

            if (len != 0)

             {

                len = lps[len - 1];

            }

    else

        {

                lps[i] = 0;

                i++;

            }

        }

    }




    return lps;
}




// Function to perform KMP pattern matching



vector<int> kmpSearch(const string& text, const string& pattern)

{

    int n = text.length();

    int m = pattern.length();



    vector<int> lps = computeLPSArray(pattern);

    vector<int> positions; // To store starting indices of matches




    int i = 0; // Index for text

    int j = 0; // Index for pattern



    while (i < n)

        {

        if (pattern[j] == text[i])

         {

            i++;

            j++;

        }



        if (j == m)

            {

            positions.push_back(i - j); // Match found

            j = lps[j - 1]; // Continue searching

        }

        else if (i < n && pattern[j] != text[i])

            {

            if (j != 0)

             {


                j = lps[j - 1];

            }


        else

            {

                i++;

            }

        }
    }




    return positions;
}





// Function to display all messages



void showMessages(const vector<string>& messages)

{


    cout << "\nGame Messages:\n";

    cout << string(40, '-') << "\n";

    for (size_t i = 0; i < messages.size(); i++)


        {

        cout << "Message " << i + 1 << ": " << messages[i] << "\n";

    }

    cout << string(40, '-') << "\n";

}




// Function to display search results



void showSearchResults(const vector<int>& positions, int messageIndex, const string& pattern)

 {

    if (!positions.empty())

        {

        cout << "Pattern \"" << pattern << "\" found in message " << messageIndex + 1 << " at positions: ";


        for (int pos : positions)

        {

            cout << pos << " ";


        }

        cout << "\n";

    }


    else

        {


        cout << "Pattern \"" << pattern << "\" not found in message " << messageIndex + 1 << ".\n";

    }

}




// Function to simulate searching for patterns in game messages



void simulateGameNetworkingWithKMP()


 {

    vector<string> messages =

    {

        "Update Player Position",


        "Critical Health Alert",

        "Send Cosmetic Update",

        "Enemy Spotted",


        "Player Joined Game"


    };



    string pattern = "Player"; // Pattern to search for




    // Display messages



    displayMessages(messages);




    cout << "\nStarting KMP Search for pattern: \"" << pattern << "\"\n";


    cout << string(40, '=') << "\n";



    // Search for the pattern in each message



    for (size_t i = 0; i < messages.size(); i++)

        {

        vector<int> positions = kmpSearch(messages[i], pattern);

        displaySearchResults(positions, i, pattern);

    }



    cout << string(40, '=') << "\n";

    cout << "KMP Search Complete.\n";
}


//------------------------;

using namespace std;

using namespace chrono;



// Structure to represent a message with priority and timestamp




struct Message

 {

    int priority;         // Priority level of the message

    string content;       // The content of the message

    string category;      // Message category (e.g., "Player Update", "Combat Alert")

    system_clock::time_point timestamp; // Timestamp of when the message was added



    // Constructor to initialize the message with priority, content, and category



    Message(int p, const string& c, const string& cat)

        : priority(p), content(c), category(cat), timestamp(system_clock::now()) {}


    // Comparison operator to sort messages in the priority queue



    bool operator<(const Message& other) const

     {

        return priority < other.priority;  // For max-priority, flip the comparison

    }



    // Function to check if the message has expired based on the elapsed time




    bool isExpired(int maxAgeInSeconds) const

     {

        auto now = system_clock::now();

        auto duration = duration_cast<seconds>(now - timestamp).count();

        return duration > maxAgeInSeconds;


    }
};




// Type alias for message queues categorized by message type



using MessageQueue = priority_queue<Message>;



// Function to add messages to the queue based on category and priority



void addMessage(MessageQueue& pq, int priority, const string& content, const string& category)

{

    pq.push(Message(priority, content, category));

    cout << "Added message: \"" << content << "\" with priority " << priority << " and category: " << category << "\n";

}




// Function to process and display messages based on priority



void processMessages(MessageQueue& pq)


 {

    while (!pq.empty())

        {

        Message msg = pq.top();


        pq.pop();

        cout << "Processing message: \"" << msg.content << "\" with priority " << msg.priority


             << " and category: " << msg.category << "\n";

    }

}



// Function to remove expired messages from the queue



void removeExpiredMessages(MessageQueue& pq, int maxAgeInSeconds)

 {

    vector<Message> tempMessages;




    // Remove expired messages




    while (!pq.empty() && pq.top().isExpired(maxAgeInSeconds))

        {


        Message expiredMessage = pq.top();

        pq.pop();


        cout << "Message expired: \"" << expiredMessage.content << "\" with priority "

             << expiredMessage.priority << " and category: " << expiredMessage.category << "\n";

    }



    // Reinsert remaining messages back into the queue




    while (!pq.empty())

        {

        tempMessages.push_back(pq.top());

        pq.pop();


    }



    for (const auto& msg : tempMessages)

        {

        pq.push(msg);

    }
}






// Function to simulate game networking with priority message handling



void simulateGameNetworkingWithPriorityQueue()

{


    MessageQueue playerUpdateQueue;

     // Queue for player-related updates

    MessageQueue combatAlertQueue;

       // Queue for combat alerts

    MessageQueue systemMessageQueue;

     // Queue for system messages



    // Adding messages to different queues




    addMessage(playerUpdateQueue, 3, "Player moved to new position", "Player Update");

    addMessage(combatAlertQueue, 5, "Enemy spotted at coordinates (10, 20)", "Combat Alert");


    addMessage(systemMessageQueue, 1, "System maintenance scheduled for 2 AM", "System Message");

    addMessage(playerUpdateQueue, 2, "Player changed weapon", "Player Update");

    addMessage(combatAlertQueue, 4, "Boss health is low", "Combat Alert");


    addMessage(systemMessageQueue, 3, "Server restart in 5 minutes", "System Message");




    // Display message queues



    cout << "\nProcessing Player Update Messages:\n";

    processMessages(playerUpdateQueue);




    cout << "\nProcessing Combat Alert Messages:\n";

    processMessages(combatAlertQueue);




    cout << "\nProcessing System Messages:\n";


    processMessages(systemMessageQueue);



    // Simulate removing expired messages

    int maxAgeInSeconds = 10;

     // Messages older than 10 seconds will expire

    cout << "\nRemoving expired messages from the system...\n";

    removeExpiredMessages(systemMessageQueue, maxAgeInSeconds);



    // Adding some more messages after a delay


    addMessage(systemMessageQueue, 2, "Emergency system update", "System Message");

    addMessage(combatAlertQueue, 6, "Final boss has been defeated", "Combat Alert");



    cout << "\nProcessing remaining System Messages:\n";


    processMessages(systemMessageQueue);




    cout << "\nProcessing remaining Combat Alert Messages:\n";

    processMessages(combatAlertQueue);
}





// Structure to represent a message with priority, category, and timestamp


struct arrMessage


{

    int priority;

           // Priority level of the message

    string content;

      // The content of the message


    string category;

       // Message category (e.g., "Player Update", "Combat Alert")

    system_clock::time_point timestamp;

     // Timestamp of when the message was added




    // Constructor to initialize the message with priority, content, category, and timestamp




    arrMessage(int p, const string& c, const string& cat)

        : priority(p), content(c), category(cat), timestamp(system_clock::now()) {}


    // Comparison operator to sort messages by priority (highest first)

    bool operator<(const Message& other) const
    {
        return priority < other.priority;

         // For max-priority, flip the comparison
    }

    // Function to check if the message has expired based on a max age (in seconds)

    bool isExpired(int maxAgeInSeconds) const
    {
        auto now = system_clock::now();
        auto duration = duration_cast<seconds>(now - timestamp).count();
        return duration > maxAgeInSeconds;
    }
};

// Function to add messages to the array

void addMessage(vector<Message>& messages, int priority, const string& content, const string& category)
{
    messages.push_back(Message(priority, content, category));
    cout << "Added message: \"" << content << "\" with priority " << priority << " and category: " << category << "\n";
}

// Function to sort messages based on priority (using selection sort)

void sortMessagesByPriority(vector<Message>& messages)
 {
    int n = messages.size();
    for (int i = 0; i < n - 1; i++)
        {
        for (int j = i + 1; j < n; j++)
        {
            // Swap if the message at index i has a lower priority than the message at index j

            if (messages[i].priority < messages[j].priority)
             {
                swap(messages[i], messages[j]);
            }
        }
    }
}

// Function to process and display messages based on sorted priority

void processMessages(vector<Message>& messages, int maxAgeInSeconds)
{
    vector<Message> validMessages;

     // Temporary container for non-expired messages

    // Process messages, removing expired ones

    for (const auto& msg : messages)

        {

        if (!msg.isExpired(maxAgeInSeconds))

         {

            validMessages.push_back(msg);

            cout << "Processing message: \"" << msg.content << "\" with priority " << msg.priority

                 << " and category: " << msg.category << "\n";

        } else {

            cout << "Message expired: \"" << msg.content << "\" with priority " << msg.priority

                 << " and category: " << msg.category << "\n";

        }

    }



    // Clear the original array and reassign non-expired messages back



    messages = validMessages;
}




// Function to simulate adding and processing messages interactively



void interactiveMenu()

 {

    vector<Message> messageArray;

     // Array to store messages

    int expirationTimeInSeconds = 30;

     // Maximum age of a message in seconds



    // Main menu loop

    while (true)

        {

        cout << "\n--- Game Networking Message System ---\n";

        cout << "1. Add Message\n";

        cout << "2. Process Messages\n";

        cout << "3. Exit\n";

        cout << "Enter your choice: ";

        int choice;

        cin >> choice;

        cin.ignore();

         // Ignore the newline character after entering the choice





        if (choice == 1)

            {

            int priority;

            string content, category;



            cout << "Enter priority (1-10): ";

            cin >> priority;

            cin.ignore();

            // Ignore the newline character



            cout << "Enter message content: ";

            getline(cin, content);

            cout << "Enter message category (e.g., Player Update, Combat Alert, System Message): ";

            getline(cin, category);



            addMessage(messageArray, priority, content, category);
        }


        else if (choice == 2)

            {

            sortMessagesByPriority(messageArray);

            processMessages(messageArray, expirationTimeInSeconds);

        }

        else if (choice == 3)

        {

            cout << "Exiting the program.\n";

            break;

        }

        else {


            cout << "Invalid choice! Please try again.\n";

        }

    }
}




// Structure representing a node in the linked list (message node)



struct ChatNode

{

    string message;  // The content of the message

    string username; // The user who sent the message

    time_t timestamp; // Timestamp of when the message was sent

    ChatNode* next;  // Pointer to the next message node



    // Constructor to initialize the message node with content, username, and timestamp



    ChatNode(const string& msg, const string& user)


        : message(msg), username(user), timestamp(time(0)), next(nullptr) {}


    // Function to convert timestamp to a string (formatted)

    string getFormattedTimestamp() const

    {

        char buffer[80];

        struct tm *timeinfo;

        timeinfo = localtime(&timestamp);

        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);

        return string(buffer);

    }

};



// Class representing the chat history with linked list



class ChatHistory

 {

private:

    ChatNode* head;

     // Pointer to the first message in the linked list

    ChatNode* tail;

     // Pointer to the last message in the linked list


public:

    // Constructor to initialize the chat history (empty list)

    ChatHistory() : head(nullptr), tail(nullptr) {}

    // Destructor to delete all the messages in the linked list

    ~ChatHistory()

    {

        while (head != nullptr)

            {

            ChatNode* temp = head;

            head = head->next;

            delete temp;

        }

    }



    // Function to add a new message to the chat history



    void addMessage(const string& message, const string& username)

    {

        ChatNode* newMessage = new ChatNode(message, username);  // Create a new message node



        // If the list is empty, both head and tail should point to the new message



        if (tail == nullptr)

            {

            head = tail = newMessage;

        } else {

            // Otherwise, add it to the end of the list



            tail->next = newMessage;

            tail = newMessage;
        }


        cout << "Message from " << username << " added: \"" << message << "\"\n";
    }

    // Function to display all messages in the chat history

    void displayMessages()

    {

        if (head == nullptr)

            {

            cout << "No messages to display.\n";

            return;

        }



        cout << "\nChat History:\n";

        ChatNode* current = head;

        int index = 1;

        while (current != nullptr) {

            cout << index++ << ". [" << current->getFormattedTimestamp() << "] "

                 << current->username << ": " << current->message << "\n";

            current = current->next;

        }
    }




    // Function to delete a message by its index



    void deleteMessage(int index)

    {

        if (head == nullptr)

            {

            cout << "No messages to delete.\n";

            return;

        }



        // Special case: deleting the first message



        if (index == 1) {

            ChatNode* temp = head;

            head = head->next;

            if (head == nullptr) {

                tail = nullptr;

                 // List is now empty

            }

            delete temp;

            cout << "Message deleted.\n";

            return;

        }


        // Find the node to delete

        ChatNode* current = head;

        for (int i = 1; current != nullptr && i < index - 1; i++)

            {

            current = current->next;

        }



        if (current == nullptr || current->next == nullptr)

            {

            cout << "Invalid index. No message deleted.\n";

            return;

        }



        // Delete the node



        ChatNode* temp = current->next;

        current->next = current->next->next;

        if (current->next == nullptr)

            {

            tail = current;

        // If the last node is deleted, update the tail

        }

        delete temp;

        cout << "Message deleted.\n";
    }




    // Function to clear the entire chat history



    void clearHistory()

    {

        while (head != nullptr)

            {

            ChatNode* temp = head;

            head = head->next;

            delete temp;

        }

        tail = nullptr;

        cout << "Chat history cleared.\n";

    }



    // Function to search for messages by keyword



    void searchMessages(const string& keyword)

    {

        if (head == nullptr)

            {

            cout << "No messages to search.\n";

            return;

        }



        cout << "\nSearch Results for \"" << keyword << "\":\n";

        ChatNode* current = head;

        int found = 0;

        while (current != nullptr)

            {

            if (current->message.find(keyword) != string::npos)

            {

                cout << "[" << current->getFormattedTimestamp() << "] "

                     << current->username << ": " << current->message << "\n";

                found++;

            }

            current = current->next;

        }



        if (found == 0)

            {

            cout << "No messages found containing \"" << keyword << "\".\n";

        }
    }




    // Function to edit a message by index



    void editMessage(int index, const string& newMessage)

    {

        if (head == nullptr) {


            cout << "No messages to edit.\n";

            return;

        }



        ChatNode* current = head;

        for (int i = 1; current != nullptr && i < index; i++)

            {

            current = current->next;

        }




        if (current == nullptr)

            {

            cout << "Invalid index. No message to edit.\n";

            return;

        }



        current->message = newMessage;

        cout << "Message at index " << index << " updated to: \"" << newMessage << "\"\n";
    }




    // Function to get the size of the chat history (number of messages)




    int size()

     {

        int count = 0;

        ChatNode* current = head;

        while (current != nullptr)

            {

            count++;

            current = current->next;

        }

        return count;

    }
};




// Interactive menu to manage chat history



void Menu()

{

    ChatHistory chatHistory;

     // Create a ChatHistory object to manage messages



    while (true)

        {

        cout << "\n--- Chat History Management ---\n";

        cout << "1. Add Message\n";

        cout << "2. Display Messages\n";

        cout << "3. Delete Message\n";


        cout << "4. Clear Chat History\n";

        cout << "5. Search Messages\n";

        cout << "6. Edit Message\n";

        cout << "7. Exit\n";

        cout << "Enter your choice: ";

        int choice;

        cin >> choice;

        cin.ignore();

         // Ignore the newline character after the choice



        if (choice == 1)

            {

            string message, username;

            cout << "Enter your username: ";

            getline(cin, username);

            cout << "Enter your message: ";

            getline(cin, message);

            chatHistory.addMessage(message, username);

        }

        else if (choice == 2)

        {

            chatHistory.displayMessages();

        }

        else if (choice == 3)

        {

            int index;

            cout << "Enter the index of the message to delete: ";

            cin >> index;

            chatHistory.deleteMessage(index);

        }

        else if (choice == 4)

         {

            chatHistory.clearHistory();

        }

        else if (choice == 5)

        {

            string keyword;

            cout << "Enter keyword to search: ";

            cin.ignore();

             // To ignore the leftover newline from the previous input

            getline(cin, keyword);

            chatHistory.searchMessages(keyword);

        }

        else if (choice == 6)

            {

            int index;

            string newMessage;

            cout << "Enter the index of the message to edit: ";

            cin >> index;

            cin.ignore();

             // Ignore the leftover newline

            cout << "Enter the new message: ";

            getline(cin, newMessage);

            chatHistory.editMessage(index, newMessage);

        }

        else if (choice == 7)

        {

            cout << "Exiting...\n";

            break;
        }

        else

            {

            cout << "Invalid choice! Please try again.\n";

        }

    }
}


#include <iostream>

#include <vector>

#include <thread>

#include <chrono>

#include <mutex>

#include <condition_variable>

#include <queue>

#include <atomic>

#include <limits>

#include <string>

#include <random>

#include <cstdlib>

#include <unistd.h>



using namespace std;

 // Use the standard namespace



// Define a constant for infinity

const int INF1 = numeric_limits<int>::max();

 // Maximum integer value



// Define the total number of nodes in the network

const int TOTAL_NODES1 = 5;

// Total nodes in the network



// Define a constant for packet loss probability

const int LOSS_PROBABILITY1 = 20;

// Set a fixed loss probability for demonstration



// Network class to represent the network topology and shortest path calculations

class Network1

{

private:

    // Distance matrix to store shortest distances between nodes

    vector<vector<int>> dist1;

     // 2D vector for distances



    // Next matrix to store the next node in the shortest path

    vector<vector<int>> next1;

    // 2D vector for next nodes



public:

    // Constructor to initialize the network

    Network1()

    {

        // Resize the distance and next matrices

        dist1.resize(TOTAL_NODES1, vector<int>(TOTAL_NODES1, INF1));

        // Initialize distances to infinity



        next1.resize(TOTAL_NODES1, vector<int>(TOTAL_NODES1, -1));

        // Initialize next nodes to -1



        // Initialize distances (example graph)

        for (int i = 0; i < TOTAL_NODES1; ++i)

        {

            dist1[i][i] = 0;

            // Distance to self is zero

        }



        // Set initial distances between nodes

        dist1[0][1] = 10;

         // Distance from node 0 to node 1

        dist1[0][2] = 5;

         // Distance from node 0 to node 2

        dist1[1][2] = 2;

        // Distance from node 1 to node 2

        dist1[1][3] = 1;

        // Distance from node 1 to node 3

        dist1[2][1] = 3;

         // Distance from node 2 to node 1

        dist1[2][3] = 9;

        // Distance from node 2 to node 3

        dist1[2][4] = 2;

        // Distance from node 2 to node 4

        dist1[3][4] = 4;

        // Distance from node 3 to node 4

        dist1[4][3] = 6;

        // Distance from node 4 to node 3


        dist1[4][0] = 7;

        // Distance from node 4 to node 0



        // Run Floyd-Warshall algorithm to compute shortest paths

        floydWarshall1();

         // Call the Floyd-Warshall function
    }



    // Function to run the Floyd-Warshall algorithm

    void floydWarshall1()

    {

        // Iterate through each intermediate node

        for (int k = 0; k < TOTAL_NODES1; ++k)

        {

            // Iterate through each source node

            for (int i = 0; i < TOTAL_NODES1; ++i)

            {

                // Iterate through each destination node

                for (int j = 0; j < TOTAL_NODES1; ++j)

                {

                    // Check if a shorter path exists through the intermediate node

                    if (dist1[i][k] < INF1 && dist1[k][j] < INF1)

                    {

                        // Update the distance if a shorter path is found


                        if (dist1[i][j] > dist1[i][k] + dist1[k][j])

                        {

                            dist1[i][j] = dist1[i][k] + dist1[k][j];

                             // Update distance

                            next1[i][j] = k;

                            // Update next node

                        }

                    }

                }

            }

        }

    }

    // Function to print the shortest paths between nodes

    void printShortestPaths1()

    {

        cout << "Shortest paths between nodes:\n";

        // Print header for shortest paths

        // Iterate through each source node

        for (int i = 0; i < TOTAL_NODES1; ++i)

        {

            // Iterate through each destination node

            for (int j = 0; j < TOTAL_NODES1; ++j)

            {

                // Check if the distance is infinite

                if (dist1[i][j] == INF1)

                {

                    cout << "INF ";

                    // Print "INF" if no path exists

                }

                else

                {

                    cout << dist1[i][j] << " ";

                    // Print the distance

                }

            }

            cout << endl;

            // New line after each row

        }

    }



    // Function to get the path from start to end

    vector<int> getPath1(int start, int end)

    {

        vector<int> path;

         // Vector to store the path

        // Check if a path exists

        if (dist1[start][end] == INF1) return path;

         // No path exists



        // Construct the path using the next matrix

        for (int at = start; at != end; at = next1[at][end])

        {

            path.push_back(at);

            // Add the current node to the path

        }

        path.push_back(end);

        // Add the destination node to the path

        return path;

        // Return the constructed path
    }

};




// Packet class to represent a network packet

class Packet1

{

public:

    int id1;

    // Packet ID

    int source1;


     // Source node

    int destination1;

    // Destination node

    // Constructor to initialize a packet

    Packet1(int id, int source, int destination) : id1(id), source1(source), destination1(destination) {}

};


// Sender class to handle packet sending

class Sender1

{

private:

    queue<Packet1> packetQueue1;

    // Queue to store packets to be sent

    mutex mtx1;

    // Mutex for thread synchronization

    condition_variable cv1;

    // Condition variable for signaling

    atomic<bool> stopFlag1;

     // Atomic flag to stop the sender

    Network1& network1;

    // Reference to the network

    vector<string> lossReasons1;

    // Store reasons for packet loss

    vector<pair<int, string>> lostPackets1;

     // Store lost packets with reasons


public:

    // Constructor to initialize the sender

    Sender1(Network1& net) : stopFlag1(false), network1(net)

    {
        // Initialize loss reasons

        lossReasons1 =

        {

            "Network congestion",

             // Reason 1

            "Interference",

            // Reason 2

            "Hardware failure",

            // Reason 3

            "Routing issues"

            // Reason 4

        };

    }

    // Function to send a packet

    void sendPacket1(int id, int source, int destination)

    {

        Packet1 packet(id, source, destination);

        // Create a new packet

        {

            lock_guard<mutex> lock(mtx1);

             // Lock the mutex

            packetQueue1.push(packet);

            // Add packet to the queue

        }

        cv1.notify_one();

        // Notify one waiting thread

    }


    // Function to run the sender

    void run1()

    {

        while (!stopFlag1)

            // Continue until stopFlag is true

        {

            unique_lock<mutex> lock(mtx1);

            // Lock the mutex

            cv1.wait(lock, [this] { return !packetQueue1.empty() || stopFlag1; });

             // Wait for packets or stop signal



            while (!packetQueue1.empty())

                // Process packets in the queue

            {

                Packet1 packet = packetQueue1.front();

            // Get the front packet



                packetQueue1.pop();

                // Remove the packet from the queue

                lock.unlock();

                // Unlock the mutex



                // Simulate packet loss

                if (rand() % 100 < LOSS_PROBABILITY1)

                {

                    int reasonIndex = rand() % lossReasons1.size();

                     // Randomly select a loss reason

                    string reason = lossReasons1[reasonIndex];

                     // Get the reason

                    lostPackets1.emplace_back(packet.id1, reason);

                     // Store lost packet with reason

                    cout << "Sender1: Packet " << packet.id1 << " from Node " << packet.source1 << " to Node " << packet.destination1 << " lost. Reason: " << reason << "\n";

                    // Log loss

                }

                else

                {

                    cout << "Sender1: Packet " << packet.id1 << " from Node " << packet.source1 << " to Node " << packet.destination1 << " sent successfully.\n";



                     // Log success

                    // Simulate acknowledgment

                    this_thread::sleep_for(chrono::milliseconds(100)); // Wait for acknowledgment

                    cout << "Sender1: Acknowledgment for Packet " << packet.id1 << " received.\n";

                     // Log acknowledgment

                }

                lock.lock();

                // Lock the mutex again

            }

        }

    }

    // Function to stop the sender

    void stop1()

    {

        stopFlag1 = true;

        // Set the stop flag to true

        cv1.notify_all ();



        // Notify all waiting threads

    }



    // Function to get the loss reasons

    const vector<string>& getLossReasons1() const

    {

        return lossReasons1;



        // Return the loss reasons

    }



    // Function to get the lost packets

    const vector<pair<int, string>>& getLostPackets1() const

    {

        return lostPackets1;

         // Return lost packets with reasons

    }

};


// Receiver class to handle packet reception

class Receiver1

{

private:

    Network1& network1;

     // Reference to the network

    vector<int> packetsSentPerPlayer1;

    // Track packets sent per player

    int totalPacketsSent1;

    // Total packets sent


public:

    // Constructor to initialize the receiver

    Receiver1(Network1& net) : network1(net), packetsSentPerPlayer1(TOTAL_NODES1, 0), totalPacketsSent1(0) {}



    // Function to receive packets

    void receivePackets1(Sender1& sender, int numPackets)
    {
        // Loop to send packets

        for (int i = 0; i < numPackets; ++i)

        {

            int source = rand() % TOTAL_NODES1;

            // Randomly select a source node

            int destination = rand() % TOTAL_NODES1;

            // Randomly select a destination node



            while (source == destination)

            {

                destination = rand() % TOTAL_NODES1;

                // Ensure source and destination are different

            }

            sender.sendPacket1(i, source, destination);

             // Send the packet


            packetsSentPerPlayer1[source]++;

             // Increment the count for the source player

            totalPacketsSent1++;

             // Increment total packets sent

            this_thread::sleep_for(chrono::milliseconds(50)); // Simulate time between packet sends

        }

    }

    // Function to get packets sent per player

    const vector<int>& getPacketsSentPerPlayer1() const

    {

        return packetsSentPerPlayer1;

        // Return the packets sent per player

    }



    // Function to get total packets sent

    int getTotalPacketsSent1() const

    {

        return totalPacketsSent1;

        // Return total packets sent

    }



    // Function to find the player with the highest packets received

    int getPlayerWithHighestPackets1() const

    {

        int maxPackets = 0;

        int playerWithMaxPackets = -1;



        for (int i = 0; i < packetsSentPerPlayer1.size(); ++i)

        {

            if (packetsSentPerPlayer1[i] > maxPackets)

            {

                maxPackets = packetsSentPerPlayer1[i];

                playerWithMaxPackets = i;

            }

        }

        return playerWithMaxPackets;

        // Return player with highest packets

    }

};




// Main function to run the program

int main2()

{


    srand(static_cast<unsigned int>(time(0)));

    // Seed for random number generation

    Network1 network1;

     // Create a network instance

    Sender1 sender1(network1);

    // Create a sender instance

    Receiver1 receiver1(network1);

    // Create a receiver instance



    int choice1;

     // Variable to store user choice



    // Main menu loop

    do {

        cout << "\n====================================================\n";

        // Menu separator

        cout << "WELCOME TO PACKET LOSS RECOVERY\n";

        // Welcome message

        cout << "====================================================\n";

         // Menu separator

        cout << "1) Players\n";

        // Option to manage players

        cout << "2) Corrupted packets\n";

        // Option to review packet loss

        cout << "3) Loss Probability\n";

         // Option to view loss probability

        cout << "4) Highest Packets Received per Player\n";

         // New menu option

        cout << "5) Total Number of Packets\n";

         // New menu option

        cout << "6) Exit\n";

        // Option to exit

        cout << "Enter your choice: ";

         // Prompt for user input

        cin >> choice1;

         // Get user choice



        // Switch case to handle user choice

        switch (choice1)

        {

            case 1: // Manage players

            {

                int numPlayers1, packetsPerPlayer1;

                // Variables for player input

                cout << "Enter number of players: ";

                // Prompt for number of players

                cin >> numPlayers1;

                // Get number of players

                cout << "Enter number of packets per player: ";

                // Prompt for packets per player

                cin >> packetsPerPlayer1;

                // Get packets per player



                thread senderThread1(&Sender1::run1, &sender1);

                // Create a thread for the sender

                receiver1.receivePackets1(sender1, numPlayers1 * packetsPerPlayer1);

                // Receive packets

                sender1.stop1();

                // Stop the sender

                senderThread1.join();

                // Wait for the sender thread to finish

                break;

                // Break from the case
            }


            case 2:

                // Review packet loss

            {

                int reviewChoice1;

                // Variable for review choice

                cout << "\n1) Show all packet loss reasons\n";


                // Option to show loss reasons

                cout << "2) Show problems according to specific packets\n";

                // Option to show specific packet issues

                cout << "Enter your choice: ";

                 // Prompt for review choice

                cin >> reviewChoice1;

                // Get review choice



                // Handle review choice

                if (reviewChoice1 == 1)


                {

                    const vector<string>& lossReasons1 = sender1.getLossReasons1();

                    // Get loss reasons

                    cout << "\nPacket Loss Reasons:\n";

                    // Print header for loss reasons

                    for (const auto& reason : lossReasons1)

                        // Loop through loss reasons

                    {

                        cout << "- " << reason << "\n";

                        // Print each reason

                    }
                }


                else if (reviewChoice1 == 2)

                {

                    const auto& lostPackets1 = sender1.getLostPackets1();

                    // Get lost packets

                    cout << "\nLost Packets and Reasons:\n";

                    // Print header for lost packets

                    for (const auto& lostPacket : lostPackets1)

                        // Loop through lost packets

                    {

                        cout << "Packet ID: " << lostPacket.first << ", Reason: " << lostPacket.second << "\n";

                    // Print packet ID and reason


                    }

                }


                else

                {

                    cout << "\nInvalid choice. Please try again.\n";

                     // Handle invalid choice

                }

                break;

                 // Break from the case
            }


            case 3:

                // Show loss probability

                cout << "Loss : " << LOSS_PROBABILITY1 << "%\n";

                 // Print loss probability

                break;

                // Break from the case

            case 4:

                 // Highest Packets Received per Player

            {

                int playerWithHighestPackets1 = receiver1.getPlayerWithHighestPackets1();

                // Get player with highest packets

                if (playerWithHighestPackets1 != -1)


                {

                    cout << "Player " << playerWithHighestPackets1 << " received the highest packets.\n";

                     // Print player with highest packets

                }

                else

                {

                    cout << "No packets received by any player.\n";

                    // Handle case where no packets were received


                }

                break;

                // Break from the case

            }

            case 5:

                // Total Number of Packets

                cout << "Total Number of Packets Sent: " << receiver1.getTotalPacketsSent1() <<  "\n";

                // Print total packets sent

                break;

                // Break from the case

            case 6:

                // Exit the program

                cout << "\nExiting";

                // Print exit message

                for (int i = 0; i < 5; i++)

                    // Loop to create a delay

                {

                    cout << ". ";

                     // Print dot for visual feedback

                    sleep(1);

                     // Sleep for 1 second


                }

                break;

                // Break from the case

            default:

                 // Handle invalid choice

                cout << "\nInvalid choice. Please try again.\n";

                 // Print error message

        }

    } while (choice1 != 6);

     // Continue until user chooses to exit


    return 0;

     // Return success

}

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

    adjList[0].push_back(1);

     // Alice is connected to Bob

    adjList[1].push_back(0);

    // Bob is connected to Alice

    adjList[1].push_back(2);

     // Bob is connected to Charlie

    adjList[2].push_back(1);

     // Charlie is connected to Bob

    adjList[3].push_back(4);

     // David is connected to Eve

    adjList[4].push_back(3);

     // Eve is connected to David

    adjList[5].push_back(6);

     // Frank is connected to Grace

    adjList[6].push_back(5);

     // Grace is connected to Frank

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

    cin.ignore();

    // To ignore the newline character

    cout << "Enter Player Name: ";

    getline(cin, newPlayer.name);

    cout << "Enter Player Age: ";

    cin >> newPlayer.age;

    cout << "Enter Player Score: ";

    cin >> newPlayer.score;

    cin.ignore();

     // To ignore the newline character

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

int main7()

{


    class RealisticClass {

private:

    std::map<int, std::string> dataStore;


public:

    RealisticClass() {

        for (int i = 0; i < 100; ++i) {

            dataStore[i] = "Value" + std::to_string(i);

        }

    }



    void displayData() {

        for (const auto& pair : dataStore) {

            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;

        }

    }


    void manipulateData() {

        for (int i = 0; i < 50; ++i) {

            dataStore[i] = "ModifiedValue" + std::to_string(i);

        }

    }



    void faultyFunction() {

        // Intentionally flawed logic to appear realistic but cause issues

        for (int i = 0; i < 200; ++i) {

            try {

                std::cout << "Accessing key " << i * 3 << ": " << dataStore.at(i * 3) << std::endl;

            } catch (const std::out_of_range&) {

                std::cout << "Key " << i * 3 << " is out of range!" << std::endl;

            }

        }

    }
};



    cout<< "\nending\n";
}


void helperFunction1() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 1 << std::endl;
    }

}



void helperFunction2() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 2 << std::endl;

    }

}



void helperFunction3() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 3 << std::endl;

    }

}



void helperFunction4() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {


        std::cout << "Processing " << x + 4 << std::endl;

    }

}



void helperFunction5() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 5 << std::endl;

    }

}




void helperFunction6() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 6 << std::endl;

    }

}



void helperFunction7() {


    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 7 << std::endl;

    }

}




void helperFunction8() {

    std::vector<int> data = {1, 2, 3, 4, 5};


    for (int x : data) {
        std::cout << "Processing " << x + 8 << std::endl;


    }

}



void helperFunction9() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 9 << std::endl;

    }

}



void helperFunction10() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 10 << std::endl;


    }

}



void helperFunction11() {

    std::vector<int> data = {1, 2, 3, 4, 5};


    for (int x : data) {


        std::cout << "Processing " << x + 11 << std::endl;
    }
}

void helperFunction12() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 12 << std::endl;

    }
}




void helperFunction13() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {

        std::cout << "Processing " << x + 13 << std::endl;

    }

}



void helperFunction14() {

    std::vector<int> data = {1, 2, 3, 4, 5};

    for (int x : data) {
        std::cout << "Processing " << x + 14 << std::endl;

    }

}

void printWelcomeMessage() {

    std::cout << "Welcome to the Program!" << std::endl;

}



void processInput(int userInput) {

    switch (userInput) {

        case 1:

            std::cout << "Option 1 selected." << std::endl;

            break;

        case 2:

            std::cout << "Option 2 selected." << std::endl;

            break;

        default:

            std::cout << "Invalid option." << std::endl;

    }

}



class Utility {

public:

    static int factorial(int n) {

        if (n <= 1) return 1;

        return n * factorial(n - 1);

    }



    static void printVector(const std::vector<int>& vec) {

        for (int val : vec) {

            std::cout << val << " ";

        }

        std::cout << std::endl;

    }
};




int computeSum(int a, int b) {

    return a + b;

}



int main12() {

    printWelcomeMessage();



    int userInput;

    std::cout << "Enter a number (1 or 2): ";

    std::cin >> userInput;

    processInput(userInput);



    std::vector<int> numbers = {1, 2, 3, 4, 5};

    Utility::printVector(numbers);



    std::cout << "Factorial of 5: " << Utility::factorial(5) << std::endl;




    for (int i = 1; i <= 100; ++i) {

        std::cout << "Square of " << i << " is " << i * i << std::endl;

    }




}



void UtilityFunction1() {

    int a = 1, b = 2;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {


        std::cout << "Even number: " << a << std::endl;

    } else {

        std::cout << "Odd number: " << a << std::endl;

    }

}




void UtilityFunction2() {

    int a = 2, b = 4;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;


    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    } else {

        std::cout << "Odd number: " << a << std::endl;

    }

}



void UtilityFunction3() {


    int a = 3, b = 6;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    } else {

        std::cout << "Odd number: " << a << std::endl;


    }

}



void UtilityFunction4() {


    int a = 4, b = 8;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {


        std::cout << "Even number: " << a << std::endl;

    } else {

        std::cout << "Odd number: " << a << std::endl;

    }

}




void UtilityFunction5() {

    int a = 5, b = 10;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;


    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    }

    else

        {

        std::cout << "Odd number: " << a << std::endl;

    }


}



void UtilityFunction6() {

    int a = 6, b = 12;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;


    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    }

    else

        {


        std::cout << "Odd number: " << a << std::endl;

    }


}



void UtilityFunction7() {


    int a = 7, b = 14;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    }

    else

        {

        std::cout << "Odd number: " << a << std::endl;

    }

}




void UtilityFunction8() {

    int a = 8, b = 16;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {
        std::cout << "Even number: " << a << std::endl;

    }

    else

        {


        std::cout << "Odd number: " << a << std::endl;

    }

}



void UtilityFunction9()

{

    int a = 9, b = 18;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    }

     else

        {

        std::cout << "Odd number: " << a << std::endl;


    }

}




void UtilityFunction10()

 {

    int a = 10, b = 20;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;


    if (a % 2 == 0)

        {

        std::cout << "Even number: " << a << std::endl;

    }

     else

        {


        std::cout << "Odd number: " << a << std::endl;

    }

}



void UtilityFunction11()

{

    int a = 11, b = 22;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0)

        {

        std::cout << "Even number: " << a << std::endl;


    }

    else

        {

        std::cout << "Odd number: " << a << std::endl;

    }


}



void UtilityFunction12()

 {

    int a = 12, b = 24;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    } else {

        std::cout << "Odd number: " << a << std::endl;

    }

}



void UtilityFunction13()

{

    int a = 13, b = 26;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0)

        {

        std::cout << "Even number: " << a << std::endl;

    }

     else

        {

        std::cout << "Odd number: " << a << std::endl;

    }

}



void UtilityFunction14()

 {

    int a = 14, b = 28;


    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    }

    else

        {

        std::cout << "Odd number: " << a << std::endl;

    }

}



void UtilityFunction15() {


    int a = 15, b = 30;


    std::cout << "important sum: " << computeSum(a, b) << std::endl;


    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    }

     else

        {

        std::cout << "Odd number: " << a << std::endl;

    }

}




void UtilityFunction16() {

    int a = 16, b = 32;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    }

     else

        {

        std::cout << "Odd number: " << a << std::endl;

    }

}



void UtilityFunction17()

{


    int a = 17, b = 34;


    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    }

    else

        {

        std::cout << "Odd number: " << a << std::endl;


    }

}



void UtilityFunction18()

 {

    int a = 18, b = 36;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0)

        {
        std::cout << "Even number: " << a << std::endl;


    }

    else

        {

        std::cout << "Odd number: " << a << std::endl;

    }

}


void UtilityFunction19() {


    int a = 19, b = 38;

    std::cout << "important sum: " << computeSum(a, b) << std::endl;

    if (a % 2 == 0) {

        std::cout << "Even number: " << a << std::endl;

    } else {

        std::cout << "Odd number: " << a << std::endl;

    }

}

int main3()

{




    // Initialize players with predefined names and attributes



    initializePlayers();

    int choice;


    while (true)

        {

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

                dfs(startPlayerDFS - 1);

                 // Player ID is 1-based, convert to 0-based

                break;

            case 10:

                cout << "Exiting game...\n";

                return 0;

            default:

                cout << "Invalid choice. Try again.\n";
        }



    }



}



int main()

{

    int userChoice;

    do

    {
        cout << "\n====================================================\n";

        // Menu separator

        cout << " *   Welcome Multiplayer Game Networking System   *\n";

        // Welcome message

        cout << "====================================================\n";

        cout << "\nSelect a option:\n";


        cout << "1. Minimize Latency\n";

        cout << "2. Game Matchmakinging\n";

        cout << "3. Packet Loss Recovery\n";

        cout << "4. Efficient communication\n";

        cout << "5. Exit\n";

        cout << "\nEnter your Choice : ";


        cin >> userChoice;

        switch (userChoice)
        {

            case 1:

                main1();

                break;

            case 2:

                 main3();

                break;

            case 3:

                 main2();

                break;

            case 4:

                Menu();

                break;

            case 5:

                cout << "\nExiting";

                // Print exit message

                for (int i = 0; i < 3; i++)

                    // Loop to create a delay

                {

                    cout << ". ";

                // Print dot for visual feedback


                    sleep(1);

                    // Sleep for 1 second

                }

                break;

            default:

                cout << "Invalid choice, please try again.\n";

        }
    }

    while (userChoice != 5);

}
