# YouTube Content Moderation Software (C++ Project)

This project simulates a YouTube content platform, providing functionality for both **users** and **creators**. Users can explore, view, and rate videos, while creators can manage their videos and track channel performance.

---

## What this project does

The program allows:

### **Users**
1. **Get videos** – Display 20 videos based on a keyword. Users can select a video to watch and like/dislike it. Videos are stored in a queue.  
2. **Get video recommendations** – Display the top 10 videos based on like/dislike ratio. Videos are stored in a list.  
3. **Trending channels** – Display the top 10 channels based on average channel scores. Channels are stored in a deque.  
4. **Exit** – Exit the program.

### **Creators**
1. **Show channel score** – Calculate and display the creator’s channel score based on video performance.  
2. **Create a video** – Add a new video with name, duration, and metadata to the database.  
3. **Manage a video** – Rename, reset likes/dislikes, or delete videos. Videos are managed using a `map` or `set`.  
4. **Exit** – Exit the program.

---

## Implementation

### **Classes**
- **Person** – Base class for all users.  
- **User** – Derived class with user-specific functionality.  
- **Creator** – Derived class with creator-specific functionality; optionally a custom iterable container for videos.  
- **VideoDatabase** – Handles reading, storing, and updating video data.

### **Main Features**
- Supports two user types: **users** and **creators**.  
- Videos are randomly displayed based on keywords.  
- Video recommendations are ranked using **like/dislike ratio**.  
- Channel scores rank creators based on their video performance.  
- Handles large video databases with appropriate error handling.  
- Uses STL containers (`queue`, `list`, `deque`, `map`, `set`) and algorithms to efficiently manage data.  
- Exception handling for file operations.

---



