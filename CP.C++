#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

class SocialNetwork {
private:
    unordered_map<string, vector<string>> adjList;

public:
    void addPerson(const string &person) {
        if (adjList.count(person) == 0) {
            adjList[person] = {};
            cout << person << " added to the network.\n";
        } else {
            cout << person << " is already in the network.\n";
        }
    }

    void addConnection(const string &person1, const string &person2) {
        if (adjList.count(person1) && adjList.count(person2)) {
            adjList[person1].push_back(person2);
            adjList[person2].push_back(person1);
            cout << "Connection added between " << person1 << " and " << person2 << ".\n";
        } else {
            cout << "One or both people are not in the network. Please add them first.\n";
        }
    }

    void removeConnection(const string &person1, const string &person2) {
        if (adjList.count(person1) && adjList.count(person2)) {
            auto &friends1 = adjList[person1];
            auto &friends2 = adjList[person2];

            friends1.erase(remove(friends1.begin(), friends1.end(), person2), friends1.end());
            friends2.erase(remove(friends2.begin(), friends2.end(), person1), friends2.end());

            cout << "Connection removed between " << person1 << " and " << person2 << ".\n";
        } else {
            cout << "One or both people are not in the network.\n";
        }
    }

    void displayMutualFriends(const string &person1, const string &person2) {
        if (adjList.count(person1) && adjList.count(person2)) {
            unordered_set<string> friendsOfPerson1(adjList[person1].begin(), adjList[person1].end());
            cout << "Mutual friends of " << person1 << " and " << person2 << ": ";
            bool foundMutual = false;
            for (const auto &friendName : adjList[person2]) {
                if (friendsOfPerson1.count(friendName)) {
                    cout << friendName << " ";
                    foundMutual = true;
                }
            }
            if (!foundMutual) cout << "None";
            cout << endl;
        } else {
            cout << "One or both people are not in the network.\n";
        }
    }

    void suggestFriends(const string &person) {
        if (adjList.count(person)) {
            unordered_set<string> directFriends(adjList[person].begin(), adjList[person].end());
            unordered_set<string> suggestions;

            // Loop through each of the direct friends
            for (const auto &friendName : adjList[person]) {
                // Loop through each friend of the direct friend
                for (const auto &friendOfFriend : adjList[friendName]) {
                    // Add to suggestions if the person is not the same and it's not already a direct friend
                    if (friendOfFriend != person && !directFriends.count(friendOfFriend) && adjList.count(friendOfFriend)) {
                        suggestions.insert(friendOfFriend);
                    }
                }
            }

            cout << "Friend suggestions for " << person << ": ";
            if (suggestions.empty()) {
                cout << "None";
            } else {
                for (const auto &suggestion : suggestions) {
                    cout << suggestion << " ";
                }
            }
            cout << endl;
        } else {
            cout << person << " is not in the network.\n";
        }
    }

    void displayPersonProfile(const string &person) {
        if (adjList.count(person)) {
            cout << "Profile of " << person << ":\n";
            cout << "Direct connections: ";
            if (adjList[person].empty()) cout << "None";
            else for (const auto &conn : adjList[person]) cout << conn << " ";
            cout << endl;
        } else {
            cout << person << " is not in the network.\n";
        }
    }

    void findShortestPath(const string &start, const string &end) {
        if (adjList.count(start) == 0 || adjList.count(end) == 0) {
            cout << "One or both people are not in the network.\n";
            return;
        }

        unordered_map<string, string> parent;
        queue<string> q;
        unordered_set<string> visited;

        q.push(start);
        visited.insert(start);
        parent[start] = "";

        bool found = false;

        while (!q.empty() && !found) {
            string person = q.front();
            q.pop();

            for (const string &neighbor : adjList[person]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                    parent[neighbor] = person;

                    if (neighbor == end) {
                        found = true;
                        break;
                    }
                }
            }
        }

        if (!found) {
            cout << "No connection path between " << start << " and " << end << ".\n";
            return;
        }

        vector<string> path;
        for (string at = end; !at.empty(); at = parent[at]) {
            path.push_back(at);
        }

        cout << "Shortest path between " << start << " and " << end << ": ";
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            cout << *it << (it + 1 == path.rend() ? "\n" : " -> ");
        }
    }
};

int main() {
    SocialNetwork sn;
    int choice;
    string person1, person2;

    cout << "\n                                                   GROUP-34 _ BATCH-3\n" << endl;
    cout << "\n *** Social Network Analysis ***\n" << endl;
    cout << "\n FIRST ADD SOME PEOPLE AND THEN GO FOR REMAINING OPTIONS\n" << endl;

    do {
        cout << "\n--- Social Network Menu ---\n";
        cout << "1. Add Person\n2. Add Connection\n3. Display Mutual Friends\n";
        cout << "4. Suggest Friends\n5. Display Profile\n";
        cout << "6. Find Shortest Path\n7. Remove Connection\n8. Help\n9. Exit\n";
        cout << "Enter your choice (1-9): ";

        while (!(cin >> choice) || choice < 1 || choice > 9) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
                cout << "Enter the name of the person: ";
                cin >> person1;
                sn.suggestFriends(person1);
                break;

            case 5:
                cout << "Enter the name of the person: ";
                cin >> person1;
                sn.displayPersonProfile(person1);
                break;

            case 6:
                cout << "Enter the starting person's name: ";
                cin >> person1;
                cout << "Enter the target person's name: ";
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
                cout << "\n--- Help Menu ---\n";
                cout << "This program simulates a social network. You can add people, connect them, and explore their network.\n";
                cout << "Options:\n1: Add a new person.\n2: Connect two people.\n3: Find mutual friends.\n";
                cout << "4: Get friend suggestions.\n5: View a person's profile.\n6: Find shortest connection path.\n7: Remove a connection between two people.\n";
                break;

            case 9:
                cout << "Exiting the program... THANKYOU !\n";
                break;
        }
    } while (choice != 9);

    return 0;
}
