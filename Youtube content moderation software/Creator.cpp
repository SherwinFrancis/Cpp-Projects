#include "Creator.h"

// Constructor
Creator::Creator(const std::string &channel_name, int regNo, int score) : Person(channel_name)
{
    this->regNo = regNo;
    this->score = score;
    like_dislike_ratio_total = 0.0;
}

// Getter for Registration Number
int Creator::getRegNo() const
{
    return regNo;
}

// Getter for Channel Name
std::string Creator::getChannelName() const
{
    return channel_name;
}

// Getter for Score
int Creator::getScore() const
{
    return score;
}

// Add a score for a video
void Creator::addScore(float score, std::string video_name)
{
    videos_and_ratios.insert(std::make_pair(video_name, score));
}

// Update and calculate the overall like/dislike ratio
bool Creator::updateLikeDislikeRatio()
{
    if (videos_and_ratios.empty())
    {
        throw NoScoreException();
    }
    else
    {
        float total = 0.0;
        for (const auto &entry : videos_and_ratios)
        {
            total += entry.second;
        }
        like_dislike_ratio_total = total / videos_and_ratios.size();
    }
    return true; // Assuming update is always successful
}

// Getter for the overall like/dislike ratio
double Creator::getLikeDislikeRatio() const
{
    return like_dislike_ratio_total;
}

// Overloaded << operator to print Creator information
std::ostream &operator<<(std::ostream &str, const Creator &s)
{
    str << "Creator: " << s.getChannelName() << ", Registration Number: " << s.getRegNo() << ", Score: " << s.getScore() << ", Like/Dislike Ratio: " << s.getLikeDislikeRatio();
    return str;
}
