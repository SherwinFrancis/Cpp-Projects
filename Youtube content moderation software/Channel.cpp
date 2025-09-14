#include "Channel.h"

// Implement member functions here

Channel::Channel()
{
    // Default constructor implementation
}

Channel::Channel(const std::string &channelName, double avgScore) : name(channelName), averageScore(avgScore)
{
}

std::string Channel::getName() const
{
    return name;
}

void Channel::setName(const std::string &channelName)
{
    name = channelName;
}

double Channel::getAverageScore() const
{
    return averageScore;
}

void Channel::setAverageScore(double avgScore)
{
    averageScore = avgScore;
}

// Implement other member functions, if needed

Channel::~Channel()
{
    // Destructor implementation, if needed
}
