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
    MessageQueue playerUpdateQueue;    // Queue for player-related updates
    MessageQueue combatAlertQueue;     // Queue for combat alerts
    MessageQueue systemMessageQueue;   // Queue for system messages

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
    int maxAgeInSeconds = 10;  // Messages older than 10 seconds will expire
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
    int priority;                // Priority level of the message
    string content;              // The content of the message
    string category;             // Message category (e.g., "Player Update", "Combat Alert")
    system_clock::time_point timestamp; // Timestamp of when the message was added

    // Constructor to initialize the message with priority, content, category, and timestamp

    arrMessage(int p, const string& c, const string& cat)
        : priority(p), content(c), category(cat), timestamp(system_clock::now()) {}

    // Comparison operator to sort messages by priority (highest first)

    bool operator<(const Message& other) const
    {
        return priority < other.priority;  // For max-priority, flip the comparison
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
    vector<Message> validMessages;  // Temporary container for non-expired messages

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
    vector<Message> messageArray;  // Array to store messages
    int expirationTimeInSeconds = 30;  // Maximum age of a message in seconds

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
        cin.ignore();  // Ignore the newline character after entering the choice

        if (choice == 1)
            {
            int priority;
            string content, category;

            cout << "Enter priority (1-10): ";
            cin >> priority;
            cin.ignore();  // Ignore the newline character

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
    ChatNode* head;  // Pointer to the first message in the linked list
    ChatNode* tail;  // Pointer to the last message in the linked list

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
                tail = nullptr;  // List is now empty
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
    ChatHistory chatHistory;  // Create a ChatHistory object to manage messages

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
        cin.ignore();  // Ignore the newline character after the choice

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
            cin.ignore(); // To ignore the leftover newline from the previous input
            getline(cin, keyword);
            chatHistory.searchMessages(keyword);
        }
        else if (choice == 6)
            {
            int index;
            string newMessage;
            cout << "Enter the index of the message to edit: ";
            cin >> index;
            cin.ignore(); // Ignore the leftover newline
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

// Main function
int main()

 {
    cout << "Game Networking Simulation with Rabin-Karp Algorithm\n";
    cout << string(50, '=') << "\n";

    // Run the simulation
    simulateGameNetworkingWithRabinKarp();

    cout << "\nSimulation Complete.\n";

        cout << "Game Networking Simulation\n";
    cout << string(30, '=') << "\n";

    // Run the simulation
    simulateGameNetworking();

    cout << "\nSimulation Complete.\n";

    cout << "Game Networking Simulation with KMP Algorithm\n";
    cout << string(50, '=') << "\n";

    // Run the simulation
    simulateGameNetworkingWithKMP();

    cout << "\nSimulation Complete.\n";

    cout << "Game Networking Simulation with Priority Queue for Messages (Using Arrays)\n";
    cout << string(50, '=') << "\n";

    // Start the interactive menu for adding and processing messages
    Menu();

     cout << "Welcome to the Enhanced Chat History Management System\n";
    interactiveMenu();

    return 0;
}


