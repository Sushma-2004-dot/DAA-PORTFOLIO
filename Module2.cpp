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

int main() 

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
        
        cout << "5. Exit\n";
        
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
        
                cout << "Exiting the program.\n";
        
                break;
        
            default:
        
                cout << "Invalid choice, please try again.\n";
        
        }
    } 

    while (userChoice != 5);
    

    // ---------------------------------------------------------------------

    // DIJKSTRA

    // Initialize variables

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

