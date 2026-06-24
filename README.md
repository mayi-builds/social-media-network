# Social Media Network Simulator 🌐

A backend simulation of a social network built from scratch in C++ — no STL containers used. Models users and relationships as graphs with AVL tree-based post management, supporting friend suggestions, shortest-path queries, and chronological content feeds.

---

## Overview

This project implements the core backend of a social network, focusing on scalable data structure design and algorithmic efficiency. Users are modelled as graph vertices, friendships as edges, and each user's posts are stored in a self-balancing AVL tree sorted by creation time.

Built as part of COL106 (Data Structures & Algorithms) at IIT Delhi.

---

## Key Features

- **Graph-based social network** — users as vertices, friendships as bidirectional edges
- **Friend suggestions** — ranked by mutual friend count using BFS traversal
- **Degrees of separation** — shortest friendship path via BFS
- **AVL tree post management** — O(log n) insertion and retrieval of posts sorted by timestamp
- **All data structures built from scratch** — no STL (Graph, AVL Tree, custom sorting)

---

## Data Structures Used

| Structure | Purpose |
|-----------|---------|
| Adjacency-list Graph | Models the social network and friendship relationships |
| AVL Tree | Stores each user's posts in reverse chronological order |
| BFS Traversal | Powers friend suggestions and degree-of-separation queries |

---

## Supported Commands

### Social Network Operations
| Command | Description |
|---------|-------------|
| `ADD_USER <username>` | Adds a new user to the network |
| `ADD_FRIEND <user1> <user2>` | Creates a bidirectional friendship |
| `LIST_FRIENDS <username>` | Lists all friends in alphabetical order |
| `SUGGEST_FRIENDS <username> <N>` | Suggests up to N friends-of-friends ranked by mutual friends |
| `DEGREES_OF_SEPARATION <user1> <user2>` | Returns shortest path between two users (-1 if none) |

### User Content Operations
| Command | Description |
|---------|-------------|
| `ADD_POST <username> "<content>"` | Adds a new post for the user |
| `OUTPUT_POSTS <username> <N>` | Displays N most recent posts; -1 for all |

---

## Sample Usage

```bash
ADD_USER Alice
ADD_USER Bob
ADD_USER Charlie
ADD_FRIEND Alice Bob
ADD_FRIEND Bob Charlie
SUGGEST_FRIENDS Alice 2
DEGREES_OF_SEPARATION Alice Charlie
ADD_POST Alice "Hello World!"
OUTPUT_POSTS Alice 1
```

---

## How to Run

**Prerequisites:** `g++` installed

```bash
# Clone the repo
git clone https://github.com/YOUR_USERNAME/social-media-network.git
cd social-media-network

# Compile
bash compileCode.sh

# Run interactively
./runcode

# Or run from input file
./runcode < input.txt
```

---

## Project Structure

```
.
├── long_assignment.cpp   # Main driver — command parsing and network logic
├── classes.hpp           # All custom data structures (Graph, AVL Tree)
├── compileCode.sh        # Compilation script
├── input.txt             # Sample input for testing
└── README.md
```

---

## Implementation Highlights

- Friend suggestion uses BFS to find all friends-of-friends, counts mutual connections, and ranks with alphabetical tiebreaking — all in a single traversal
- Degrees of separation returns the full path, not just the distance, using BFS with parent tracking
- AVL tree self-balances on every insert, ensuring O(log n) post retrieval regardless of post count
- Usernames and post content are case-insensitive throughout

---

## Author

**Jagarapu Shreemayi**  
B.Tech, Mathematics & Computing  
Indian Institute of Technology Delhi
