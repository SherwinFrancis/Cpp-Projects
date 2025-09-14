#include <string>

// Header guard to prevent multiple inclusion of this header file.
#ifndef _Video_H_
#define _Video_H_

// Using the standard C++ namespace for convenience.
using namespace std;

// The Video class represents a video entity with various attributes.
class Video
{
public:
    // Public members of the Video class, representing attributes of a video.
    string id;
    string name;
    string duration;
    string channel;
    int likes;
    int dislikes;

    // Default constructor for the Video class.
    Video();
};

// End of the header guard.
#endif
