#ifndef _CREATOR_H_
#define _CREATOR_H_

#include <iostream>
#include <string>
#include <map>
#include <stdexcept>
#include "Person.h"

// Custom exception class for handling the case when a Creator has no score.
class NoScoreException : public std::exception
{
};

// The Creator class represents a person who is also a content creator on a channel.
class Creator : public Person
{
public:
    // Constructor for the Creator class.
    Creator(const std::string &channel_name, int regNo, int score);

    // Getter methods for retrieving information about the Creator.
    int getRegNo() const;
    int getScore() const;
    std::string getChannelName() const;
    double getLikeDislikeRatio() const;

    // Method to add a score for a specific video.
    void addScore(float score, std::string video_name);

    // Method to update the overall like/dislike ratio of the Creator.
    bool updateLikeDislikeRatio();

    // Overloaded output stream operator to facilitate printing Creator information.
    friend std::ostream &operator<<(std::ostream &str, const Creator &s);

private:
    // Private members of the Creator class.
    int score;
    int regNo;
    std::string channel_name;
    std::multimap<std::string, float> videos_and_ratios; // Mapping of video names to their respective like/dislike ratios.
    float like_dislike_ratio_total;                      // Total like/dislike ratio of all videos.
};

// Overloaded output stream operator for printing Creator information.
std::ostream &operator<<(std::ostream &str, const Creator &s);

#endif
