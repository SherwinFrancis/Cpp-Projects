#ifndef CHANNEL_H
#define CHANNEL_H

#include <string>
#include <deque>
#include "Video.h" // Assuming you have a Video class

class Channel
{
public:
    std::string name;
    double averageScore; // Average score of all videos in the channel
    std::deque<Video> videos;
    // Constructors
    Channel(); // Default constructor
    Channel(const std::string &channelName, double avgScore);

    // Getter and setter functions
    std::string getName() const;
    void setName(const std::string &channelName);

    double getAverageScore() const;
    void setAverageScore(double avgScore);

    // Other member functions, if needed

    // Destructor, if needed
    ~Channel();
};

#endif // CHANNEL_H
