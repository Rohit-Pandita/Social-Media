#include <iostream> // Includes the standard input/output library
#include <vector>   // Includes the vector library for dynamic arrays
#include <unordered_map> // Includes the unordered_map library for hash maps
#include <unordered_set> // Includes the unordered_set library for hash sets
#include <queue>    // Includes the queue library for BFS traversal
#include <limits>   // Includes the limits library for numeric limits
#include <algorithm> // Includes the algorithm library for functions like remove

using namespace std; // Allows usage of standard library functions without std::

class SocialNetwork {
private:
    unordered_map<string, vector<string>> adjList; // Stores the social network as an adjacency list

public:
    void addPerson(const string &person) {
        if (adjList.count(person) == 0) { // Checks if the person is not already in the network
            adjList[person] = {}; // Adds the person with an empty list of connections
            cout << person << " added to the network.\n";
        } else {
            cout << person << " is already in the network.\n"; // Message if the person already exists
        }
    }

    void addConnection(const string &person1, const string &person2) {
        if (adjList.count(person1) && adjList.count(person2)) { // Ensures both people are in the network
            adjList[person1].push_back(person2); // Adds a connection from person1 to person2
            adjList[person2].push_back(person1); // Adds a connection from person2 to person1
            cout << "Connection added between " << person1 << " and " << person2 << ".\n";
        } else {
            cout << "One or both people are not in the network. Please add them first.\n"; // Error message
        }
    }

    void removeConnection(const string &person1, const string &person2) {
        if (adjList.count(person1) && adjList.count(person2)) { // Ensures both people exist
            auto &friends1 = adjList[person1]; // References the connections of person1
            auto &friends2 = adjList[person2]; // References the connections of person2

            // Removes person2 from person1's connections
            friends1.erase(remove(friends1.begin(), friends1.end(), person2), friends1.end());
            // Removes person1 from person2's connections
            friends2.erase(remove(friends2.begin(), friends2.end(), person1), friends2.end());

            cout << "Connection removed between " << person1 << " and " << person2 << ".\n";
        } else {
            cout << "One or both people are not in the network.\n"; // Error message
        }
    }

    void displayMutualFriends(const string &person1, const string &person2) {
        if (adjList.count(person1) && adjList.count(person2)) { // Ensures both people exist
            // Converts person1's connections to a set for efficient lookup
            unordered_set<string> friendsOfPerson1(adjList[person1].begin(), adjList[person1].end());
            cout << "Mutual friends of " << person1 << " and " << person2 << ": ";
            bool foundMutual = false;

            // Iterates over person2's connections
            for (const auto &friendName : adjList[person2]) {
                if (friendsOfPerson1.count(friendName)) { // Checks if the connection is mutual
                    cout << friendName << " ";
                    foundMutual = true;
                }
            }
            if (!foundMutual) cout << "None"; // Displays "None" if no mutual friends found
            cout << endl;
        } else {
            cout << "One or both people are not in the network.\n"; // Error message
        }
    }

    void suggestFriends(const string &person) {
        if (adjList.count(person)) { // Checks if the person exists
            unordered_set<string> directFriends(adjList[person].begin(), adjList[person].end()); // Stores direct friends
            unordered_set<string> suggestions; // Stores friend suggestions

            // Loops through each direct friend
            for (const auto &friendName : adjList[person]) {
                // Loops through each friend's connections
                for (const auto &friendOfFriend : adjList[friendName]) {
                    // Suggests if not already a direct friend or the person itself
                    if (friendOfFriend != person && !directFriends.count(friendOfFriend)) {
                        suggestions.insert(friendOfFriend);
                    }
                }
            }

            cout << "Friend suggestions for " << person << ": ";
            if (suggestions.empty()) {
                cout << "None"; // Displays "None" if no suggestions found
            } else {
                for (const auto &suggestion : suggestions) {
                    cout << suggestion << " "; // Displays each suggestion
                }
            }
            cout << endl;
        } else {
            cout << person << " is not in the network.\n"; // Error message
        }
    }

    void displayPersonProfile(const string &person) {
        if (adjList.count(person)) { // Checks if the person exists
            cout << "Profile of " << person << ":\n";
            cout << "Direct connections: ";
            if (adjList[person].empty()) cout << "None"; // Displays "None" if no connections
            else for (const auto &conn : adjList[person]) cout << conn << " "; // Lists connections
            cout << endl;
        } else {
            cout << person << " is not in the network.\n"; // Error message
        }
    }

    void findShortestPath(const string &start, const string &end) {
        if (adjList.count(start) == 0 || adjList.count(end) == 0) { // Ensures both people exist
            cout << "One or both people are not in the network.\n";
            return;
        }

        unordered_map<string, string> parent; // Stores the path
        queue<string> q; // Queue for BFS
        unordered_set<string> visited; // Tracks visited nodes

        q.push(start); // Starts BFS from 'start'
        visited.insert(start);
        parent[start] = "";

        bool found = false;

        // BFS traversal
        while (!q.empty() && !found) {
            string person = q.front();
            q.pop();

            for (const string &neighbor : adjList[person]) {
                if (!visited.count(neighbor)) { // Visits unvisited neighbors
                    visited.insert(neighbor);
                    q.push(neighbor);
                    parent[neighbor] = person;

                    if (neighbor == end) { // Stops if 'end' is found
                        found = true;
                        break;
                    }
                }
            }
        }

        if (!found) {
            cout << "No connection path between " << start << " and " << end << ".\n"; // No path found
            return;
        }

        vector<string> path; // Stores the shortest path
        for (string at = end; !at.empty(); at = parent[at]) { // Traces back using 'parent'
            path.push_back(at);
        }

        cout << "Shortest path between " << start << " and " << end << ": ";
        for (auto it = path.rbegin(); it != path.rend(); ++it) { // Prints the path in reverse
            cout << *it << (it + 1 == path.rend() ? "\n" : " -> ");
        }
    }
};

int main() {
    SocialNetwork sn; // Creates a SocialNetwork object
    int choice;
    string person1, person2;

    cout << "\n                                                   GROUP-34 _ BATCH-3\n " << endl;
    cout << "\n *** Social Network Analysis ***\n " << endl;
    cout << "\n FIRST ADD SOME PEOPLE AND THEN GO FOR REMAINING OPTIONS\n" << endl;

    do {
        // Menu display and user interaction
        cout << "\n--- Social Network Menu ---\n";
        cout << "1. Add Person\n2. Add Connection\n3. Display Mutual Friends\n";
        cout << "4. Suggest Friends\n5. Display Profile\n";
        cout << "6. Find Shortest Path\n7. Remove Connection\n8. Help\n9. Exit\n";
        cout << "Enter your choice (1-9): ";

        while (!(cin >> choice) || choice < 1 || choice > 9) {
            cin.clear(); // Clears invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores leftover input
            cout << "Invalid choice. Please enter a number between 1 and 9: ";
        }

        switch (choice) {
        case 1:
            int numPeople;
            cout << "Enter the number of people to add: ";
            while (!(cin >> numPeople) || numPeople < 1) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter a positive integer: ";
            }
            for (int i = 0; i < numPeople; ++i) {
                cout << "Enter name of person " << i + 1 << ": ";
                cin >> person1;
                sn.addPerson(person1);
            }
            break;
        case 2:
            cout << "Enter the first person's name: ";
            cin >> person1;
            cout << "Enter the second person's name: ";
            cin >> person2;
            sn.addConnection(person1, person2);
            break;
        case 3:
            cout << "Enter the first person's name: ";
            cin >> person1;
            cout << "Enter the second person's name: ";
            cin >> person2;
            sn.displayMutualFriends(person1, person2);
            break;
        case 4:
            cout << "Enter the person's name: ";
            cin >> person1;
            sn.suggestFriends(person1);
            break;
        case 5:
            cout << "Enter the person's name: ";
            cin >> person1;
            sn.displayPersonProfile(person1);
            break;
        case 6:
            cout << "Enter the start person's name: ";
            cin >> person1;
            cout << "Enter the end person's name: ";
            cin >> person2;
            sn.findShortestPath(person1, person2);
            break;
        case 7:
            cout << "Enter the first person's name: ";
            cin >> person1;
            cout << "Enter the second person's name: ";
            cin >> person2;
            sn.removeConnection(person1, person2);
            break;
        case 8:
            cout << "HELP - MENU INSTRUCTIONS:\n";
            cout << "1. Add Person: Add one or more people to the network.\n";
            cout << "2. Add Connection: Establish a connection between two people.\n";
            cout << "3. Display Mutual Friends: Find common friends between two people.\n";
            cout << "4. Suggest Friends: Suggest potential friends for a person.\n";
            cout << "5. Display Profile: View a person's profile and their connections.\n";
            cout << "6. Find Shortest Path: Discover the shortest connection path between two people.\n";
            cout << "7. Remove Connection: Remove a connection between two people.\n";
            cout << "8. Help: Display this menu.\n";
            cout << "9. Exit: Exit the program.\n";
            break;
        case 9:
            cout << "Exiting the program.\n"; // Exit message
            break;
        default:
            cout << "Invalid choice. Try again.\n"; // Invalid choice handling
        }
    } while (choice != 9);

    return 0;
}
