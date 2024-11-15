# Social Network Analysis

## Overview
This project is a **C++ program** simulating a **Social Network Analysis** system. It allows users to add people, establish connections between them, explore their social network, and perform various other operations, including finding mutual friends, suggesting new friends, and finding the shortest connection path between two people.

---

## Features
1. **Add Person**  
   Add a new person to the social network.

2. **Add Connection**  
   Create a connection (friendship) between two people in the network.

3. **Display Mutual Friends**  
   View mutual friends shared between two people.

4. **Suggest Friends**  
   Get friend recommendations for a person based on their friends' connections.

5. **Display Profile**  
   View the profile of a person, including their direct connections.

6. **Find Shortest Path**  
   Find the shortest connection path between two people using **Breadth-First Search (BFS)**.

7. **Remove Connection**  
   Remove an existing connection between two people.

8. **Help Menu**  
   Provides an overview of the program and its functionalities.

9. **Exit**  
   Exit the program.

---

## How to Use
### Prerequisites
- A C++ compiler supporting C++11 or later.

### Steps
1. **Compile the Program**
   ```bash
   g++ -o social_network social_network.cpp
   ```
   
2. Run the Program
```bash
./social_network
```

3. Follow the Menu Options
You can choose options from the menu to interact with the program. Always start by adding people before performing other operations.




# Example Usage
Add People
Add people to the network:

Enter the number of people to add: 2
Enter name of person 1: Alice
Enter name of person 2: Bob
Add Connection
Connect Alice and Bob:

Enter the first person's name: Alice
Enter the second person's name: Bob
Display Mutual Friends
Find mutual friends between Alice and Bob:

Enter the first person's name: Alice
Enter the second person's name: Bob
Suggest Friends
Get friend suggestions for Alice:

Enter the name of the person: Alice
Find Shortest Path
Find the shortest path between Alice and another user:

Enter the starting person's name: Alice
Enter the target person's name: Charlie
