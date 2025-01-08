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

using namespace std; // Use the standard namespace

// Define a constant for infinity
const int INF1 = numeric_limits<int>::max(); // Maximum integer value

// Define the total number of nodes in the network
const int TOTAL_NODES1 = 5; // Total nodes in the network

// Define a constant for packet loss probability
const int LOSS_PROBABILITY1 = 20; // Set a fixed loss probability for demonstration

// Network class to represent the network topology and shortest path calculations
class Network1
{
private:
    // Distance matrix to store shortest distances between nodes
    vector<vector<int>> dist1; // 2D vector for distances

    // Next matrix to store the next node in the shortest path
    vector<vector<int>> next1; // 2D vector for next nodes

public:
    // Constructor to initialize the network
    Network1()
    {
        // Resize the distance and next matrices
        dist1.resize(TOTAL_NODES1, vector<int>(TOTAL_NODES1, INF1)); // Initialize distances to infinity

        next1.resize(TOTAL_NODES1, vector<int>(TOTAL_NODES1, -1)); // Initialize next nodes to -1

        // Initialize distances (example graph)
        for (int i = 0; i < TOTAL_NODES1; ++i)
        {
            dist1[i][i] = 0; // Distance to self is zero
        }

        // Set initial distances between nodes
        dist1[0][1] = 10; // Distance from node 0 to node 1
        dist1[0][2] = 5;  // Distance from node 0 to node 2
        dist1[1][2] = 2;  // Distance from node 1 to node 2
        dist1[1][3] = 1;  // Distance from node 1 to node 3
        dist1[2][1] = 3;  // Distance from node 2 to node 1
        dist1[2][3] = 9;  // Distance from node 2 to node 3
        dist1[2][4] = 2;  // Distance from node 2 to node 4
        dist1[3][4] = 4;  // Distance from node 3 to node 4
        dist1[4][3] = 6;  // Distance from node 4 to node 3
        dist1[4][0] = 7;  // Distance from node 4 to node 0

        // Run Floyd-Warshall algorithm to compute shortest paths
        floydWarshall1(); // Call the Floyd-Warshall function
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
                            dist1[i][j] = dist1[i][k] + dist1[k][j]; // Update distance
                            next1[i][j] = k; // Update next node
                        }
                    }
                }
            }
        }
    }

    // Function to print the shortest paths between nodes
    void printShortestPaths1()
    {
        cout << "Shortest paths between nodes:\n"; // Print header for shortest paths
        // Iterate through each source node
        for (int i = 0; i < TOTAL_NODES1; ++i)
        {
            // Iterate through each destination node
            for (int j = 0; j < TOTAL_NODES1; ++j)
            {
                // Check if the distance is infinite
                if (dist1[i][j] == INF1)
                {
                    cout << "INF "; // Print "INF" if no path exists
                }
                else
                {
                    cout << dist1[i][j] << " "; // Print the distance
                }
            }
            cout << endl; // New line after each row
        }
    }

    // Function to get the path from start to end
    vector<int> getPath1(int start, int end)
    {
        vector<int> path; // Vector to store the path
        // Check if a path exists
        if (dist1[start][end] == INF1) return path; // No path exists

        // Construct the path using the next matrix
        for (int at = start; at != end; at = next1[at][end])
        {
            path.push_back(at); // Add the current node to the path
        }
        path.push_back(end); // Add the destination node to the path
        return path; // Return the constructed path
    }
};

// Packet class to represent a network packet
class Packet1
{
public:
    int id1; // Packet ID
    int source1; // Source node
    int destination1; // Destination node

    // Constructor to initialize a packet
    Packet1(int id, int source, int destination) : id1(id), source1(source), destination1(destination) {}
};

// Sender class to handle packet sending
class Sender1
{
private:
    queue<Packet1> packetQueue1; // Queue to store packets to be sent
    mutex mtx1; // Mutex for thread synchronization
    condition_variable cv1; // Condition variable for signaling
    atomic<bool> stopFlag1; // Atomic flag to stop the sender
    Network1& network1; // Reference to the network
    vector<string> lossReasons1; // Store reasons for packet loss
    vector<pair<int, string>> lostPackets1; // Store lost packets with reasons

public:
    // Constructor to initialize the sender
    Sender1(Network1& net) : stopFlag1(false), network1(net)
    {
        // Initialize loss reasons
        lossReasons1 =
        {
            "Network congestion", // Reason 1
            "Interference", // Reason 2
            "Hardware failure", // Reason 3
            "Routing issues" // Reason 4
        };
    }

    // Function to send a packet
    void sendPacket1(int id, int source, int destination)
    {
        Packet1 packet(id, source, destination); // Create a new packet
        {
            lock_guard<mutex> lock(mtx1); // Lock the mutex
            packetQueue1.push(packet); // Add packet to the queue
        }
        cv1.notify_one(); // Notify one waiting thread
    }

    // Function to run the sender
    void run1()
    {
        while (!stopFlag1) // Continue until stopFlag is true
        {
            unique_lock<mutex> lock(mtx1); // Lock the mutex
            cv1.wait(lock, [this] { return !packetQueue1.empty() || stopFlag1; }); // Wait for packets or stop signal

            while (!packetQueue1.empty()) // Process packets in the queue
            {
                Packet1 packet = packetQueue1.front(); // Get the front packet
                packetQueue1.pop(); // Remove the packet from the queue
                lock.unlock(); // Unlock the mutex

                // Simulate packet loss
                if (rand() % 100 < LOSS_PROBABILITY1)
                {
                    int reasonIndex = rand() % lossReasons1.size(); // Randomly select a loss reason
                    string reason = lossReasons1[reasonIndex]; // Get the reason
                    lostPackets1.emplace_back(packet.id1, reason); // Store lost packet with reason
                    cout << "Sender1: Packet " << packet.id1 << " from Node " << packet.source1 << " to Node " << packet.destination1 << " lost. Reason: " << reason << "\n"; // Log loss
                }
                else
                {
                    cout << "Sender1: Packet " << packet.id1 << " from Node " << packet.source1 << " to Node " << packet.destination1 << " sent successfully.\n"; // Log success
                    // Simulate acknowledgment
                    this_thread::sleep_for(chrono::milliseconds(100)); // Wait for acknowledgment
                    cout << "Sender1: Acknowledgment for Packet " << packet.id1 << " received.\n"; // Log acknowledgment
                }
                lock.lock(); // Lock the mutex again
            }
        }
    }

    // Function to stop the sender
    void stop1()
    {
        stopFlag1 = true; // Set the stop flag to true
        cv1.notify_all (); // Notify all waiting threads
    }

    // Function to get the loss reasons
    const vector<string>& getLossReasons1() const
    {
        return lossReasons1; // Return the loss reasons
    }

    // Function to get the lost packets
    const vector<pair<int, string>>& getLostPackets1() const
    {
        return lostPackets1; // Return lost packets with reasons
    }
};

// Receiver class to handle packet reception
class Receiver1
{
private:
    Network1& network1; // Reference to the network
    vector<int> packetsSentPerPlayer1; // Track packets sent per player
    int totalPacketsSent1; // Total packets sent

public:
    // Constructor to initialize the receiver
    Receiver1(Network1& net) : network1(net), packetsSentPerPlayer1(TOTAL_NODES1, 0), totalPacketsSent1(0) {}

    // Function to receive packets
    void receivePackets1(Sender1& sender, int numPackets)
    {
        // Loop to send packets
        for (int i = 0; i < numPackets; ++i)
        {
            int source = rand() % TOTAL_NODES1; // Randomly select a source node
            int destination = rand() % TOTAL_NODES1; // Randomly select a destination node

            while (source == destination)
            {
                destination = rand() % TOTAL_NODES1; // Ensure source and destination are different
            }
            sender.sendPacket1(i, source, destination); // Send the packet

            packetsSentPerPlayer1[source]++; // Increment the count for the source player
            totalPacketsSent1++; // Increment total packets sent

            this_thread::sleep_for(chrono::milliseconds(50)); // Simulate time between packet sends
        }
    }

    // Function to get packets sent per player
    const vector<int>& getPacketsSentPerPlayer1() const
    {
        return packetsSentPerPlayer1; // Return the packets sent per player
    }

    // Function to get total packets sent
    int getTotalPacketsSent1() const
    {
        return totalPacketsSent1; // Return total packets sent
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
        return playerWithMaxPackets; // Return player with highest packets
    }
};

// Main function to run the program
int main()
{
    srand(static_cast<unsigned int>(time(0))); // Seed for random number generation

    Network1 network1; // Create a network instance
    Sender1 sender1(network1); // Create a sender instance
    Receiver1 receiver1(network1); // Create a receiver instance

    int choice1; // Variable to store user choice

    // Main menu loop
    do {
        cout << "\n====================================================\n"; // Menu separator
        cout << "WELCOME TO PACKET LOSS RECOVERY\n"; // Welcome message
        cout << "====================================================\n"; // Menu separator
        cout << "1) Players\n"; // Option to manage players
        cout << "2) Review\n"; // Option to review packet loss
        cout << "3) Loss Probability\n"; // Option to view loss probability
        cout << "4) Highest Packets Received per Player\n"; // New menu option
        cout << "5) Total Number of Packets\n"; // New menu option
        cout << "6) Exit\n"; // Option to exit
        cout << "Enter your choice: "; // Prompt for user input
        cin >> choice1; // Get user choice

        // Switch case to handle user choice
        switch (choice1)
        {
            case 1: // Manage players
            {
                int numPlayers1, packetsPerPlayer1; // Variables for player input
                cout << "Enter number of players: "; // Prompt for number of players
                cin >> numPlayers1; // Get number of players
                cout << "Enter number of packets per player: "; // Prompt for packets per player
                cin >> packetsPerPlayer1; // Get packets per player

                thread senderThread1(&Sender1::run1, &sender1); // Create a thread for the sender
                receiver1.receivePackets1(sender1, numPlayers1 * packetsPerPlayer1); // Receive packets
                sender1.stop1(); // Stop the sender
                senderThread1.join(); // Wait for the sender thread to finish
                break; // Break from the case
            }
            case 2: // Review packet loss
            {
                int reviewChoice1; // Variable for review choice
                cout << "\n1) Show all packet loss reasons\n"; // Option to show loss reasons
                cout << "2) Show problems according to specific packets\n"; // Option to show specific packet issues
                cout << "Enter your choice: "; // Prompt for review choice
                cin >> reviewChoice1; // Get review choice

                // Handle review choice
                if (reviewChoice1 == 1)
                {
                    const vector<string>& lossReasons1 = sender1.getLossReasons1(); // Get loss reasons
                    cout << "\nPacket Loss Reasons:\n"; // Print header for loss reasons
                    for (const auto& reason : lossReasons1) // Loop through loss reasons
                    {
                        cout << "- " << reason << "\n"; // Print each reason
                    }
                }
                else if (reviewChoice1 == 2)
                {
                    const auto& lostPackets1 = sender1.getLostPackets1(); // Get lost packets
                    cout << "\nLost Packets and Reasons:\n"; // Print header for lost packets
                    for (const auto& lostPacket : lostPackets1) // Loop through lost packets
                    {
                        cout << "Packet ID: " << lostPacket.first << ", Reason: " << lostPacket.second << "\n"; // Print packet ID and reason
                    }
                }
                else
                {
                    cout << "\nInvalid choice. Please try again.\n"; // Handle invalid choice
                }
                break; // Break from the case
            }
            case 3: // Show loss probability
                cout << "Loss : " << LOSS_PROBABILITY1 << "%\n"; // Print loss probability
                break; // Break from the case
            case 4: // Highest Packets Received per Player
            {
                int playerWithHighestPackets1 = receiver1.getPlayerWithHighestPackets1(); // Get player with highest packets
                if (playerWithHighestPackets1 != -1)
                {
                    cout << "Player " << playerWithHighestPackets1 << " received the highest packets.\n"; // Print player with highest packets
                }
                else
                {
                    cout << "No packets received by any player.\n"; // Handle case where no packets were received
                }
                break; // Break from the case
            }
            case 5: // Total Number of Packets
                cout << "Total Number of Packets Sent: " << receiver1.getTotalPacketsSent1() << "\n"; // Print total packets sent
                break; // Break from the case
            case 6: // Exit the program
                cout << "\nExiting"; // Print exit message
                for (int i = 0; i < 5; i++) // Loop to create a delay
                {
                    cout << ". "; // Print dot for visual feedback
                    sleep(1); // Sleep for 1 second
                }
                break; // Break from the case
            default: // Handle invalid choice
                cout << "\nInvalid choice. Please try again.\n"; // Print error message
        }
    } while (choice1 != 6); // Continue until user chooses to exit

    return 0; // Return success
}
