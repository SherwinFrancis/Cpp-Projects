#ifndef VIDEODATA_H
#define VIDEODATA_H

#include <string>

// This header file defines a structure called VideoData, which represents information about a video.

// The VideoData structure has the following members:
struct VideoData {
    std::string video_id;        // Unique identifier for the video
    std::string video_name;      // Name or title of the video
    std::string video_duration;  // Duration of the video
    int no_likes;                // Number of likes the video has received
    int no_dislikes;             // Number of dislikes the video has received
    std::string channel_name;    // Name of the channel to which the video belongs
};

#endif
