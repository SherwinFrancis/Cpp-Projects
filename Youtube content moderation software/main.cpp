// Importing all of the required libraries

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include "Creator.h"
#include "User.h"
#include <queue>
#include <limits>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include "Video.h"
#include "Channel.h"
#include <iomanip>
#include "videoData.h"
using namespace std;
// Function to delete a video from a file
void deleteVideo(const string &videoId, const string &filename)
{
    // Open the input file for reading and create a temporary output file
    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    // Check if the input file is successfully opened
    if (!inFile)
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Create a vector to store video data
    vector<VideoData> videoList;
    string line;

    // Read data from the input file and populate the vector
    while (getline(inFile, line))
    {
        stringstream ss(line);
        VideoData video;

        // Parse comma-separated values from the line
        getline(ss, video.video_id, ',');
        getline(ss, video.video_name, ',');
        getline(ss, video.video_duration, ',');
        ss >> video.no_likes;
        ss.ignore();
        ss >> video.no_dislikes;
        ss.ignore();
        getline(ss, video.channel_name);

        // Add the video data to the vector
        videoList.push_back(video);
    }

    // Close the input file
    inFile.close();

    // Use remove_if and erase to remove the video with the specified ID
    auto it = std::remove_if(videoList.begin(), videoList.end(),
                             [&videoId](const VideoData &video)
                             {
                                 return video.video_id == videoId;
                             });

    // Check if the video with the specified ID was found
    if (it != videoList.end())
    {
        // Erase elements from it to the end of the vector
        videoList.erase(it, videoList.end());

        // Write the updated video list to the temporary output file
        for (const auto &video : videoList)
        {
            outFile << video.video_id << ","
                    << video.video_name << ","
                    << video.video_duration << ","
                    << video.no_likes << ","
                    << video.no_dislikes << ","
                    << video.channel_name << endl;
        }

        // Close the temporary output file
        outFile.close();

        // Remove the original file and rename the temporary file
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());

        // Print a success message
        cout << "Video deleted successfully." << endl;
    }
    else
    {
        // Close the temporary output file and remove it
        outFile.close();
        remove("temp.txt");

        // Print a message indicating that the video ID was not found
        cout << "Video ID not found." << endl;
    }
}
// Function to filter videos by channel and print the results
std::map<std::string, std::vector<Video>> filterVideosByChannelAndPrint(const std::string &filename, const std::string &targetChannel)
{
    // Map to store videos grouped by channel
    std::map<std::string, std::vector<Video>> channelVideos;

    // Open the input file for reading
    std::ifstream file(filename);
    std::string line;
    char delimiter = ',';

    // Check if the file is successfully opened
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open file '" << filename << "'" << std::endl;
        return channelVideos;
    }

    // Read data from the file and populate the channelVideos map
    while (getline(file, line))
    {
        std::istringstream iss(line);
        Video video;

        // Parse comma-separated values from the line
        if (getline(iss, video.id, delimiter) &&
            getline(iss, video.name, delimiter) &&
            getline(iss, video.duration, delimiter) &&
            iss >> video.likes &&
            iss.ignore(std::numeric_limits<std::streamsize>::max(), delimiter) &&
            iss >> video.dislikes &&
            iss.ignore(std::numeric_limits<std::streamsize>::max(), delimiter) &&
            getline(iss, video.channel))
        {
            // Check if the video belongs to the target channel
            if (video.channel == targetChannel)
            {
                // Add the video to the corresponding channel in the map
                channelVideos[video.channel].push_back(video);
            }
        }
    }

    // Close the input file
    file.close();

    // Print the videos belonging to the target channel
    for (const auto &video : channelVideos[targetChannel])
    {
        std::cout << "Video ID: " << video.id << ", Name: " << video.name << ", Duration: " << video.duration
                  << ", Likes: " << video.likes << ", Dislikes: " << video.dislikes << ", Channel: " << video.channel << std::endl;
    }

    // Return the map containing filtered videos
    return channelVideos;
}

// Function to reset likes and dislikes for a specific video
void resetLikesDislikes(const string &videoId, const string &filename)
{
    // Open the input file for reading and create a temporary output file
    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    // Check if the input file is successfully opened
    if (!inFile)
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Create a vector to store video data
    vector<VideoData> videoList;
    string line;

    // Read data from the input file and populate the vector
    while (getline(inFile, line))
    {
        stringstream ss(line);
        VideoData video;

        // Parse comma-separated values from the line
        getline(ss, video.video_id, ',');
        getline(ss, video.video_name, ',');
        getline(ss, video.video_duration, ',');
        ss >> video.no_likes;
        ss.ignore();
        ss >> video.no_dislikes;
        ss.ignore();
        getline(ss, video.channel_name);

        // Add the video data to the vector
        videoList.push_back(video);
    }

    // Close the input file
    inFile.close();

    // Flag to track whether likes and dislikes are updated
    bool updated = false;

    // Iterate through the vector and reset likes and dislikes for the specified video
    for (auto &video : videoList)
    {
        if (video.video_id == videoId)
        {
            video.no_likes = 0;
            video.no_dislikes = 0;
            updated = true;
        }
    }

    // Write the updated video list to the temporary output file
    for (const auto &video : videoList)
    {
        outFile << video.video_id << ","
                << video.video_name << ","
                << video.video_duration << ","
                << video.no_likes << ","
                << video.no_dislikes << ","
                << video.channel_name << endl;
    }

    // Close the temporary output file
    outFile.close();

    // If likes and dislikes are updated, remove the original file and rename the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Likes and dislikes reset successfully." << endl;
    }
    else
    {
        // If the video ID was not found, remove the temporary file
        remove("temp.txt");
        cout << "Video ID not found." << endl;
    }
}

// Function to update the name of a video by video ID
void updateVideoName(const string &videoId, const string &newVideoName, const string &filename)
{
    // Open the input file for reading and create a temporary output file
    ifstream inFile(filename);
    ofstream outFile("temp.txt");

    // Check if the input file is successfully opened
    if (!inFile)
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    // Create a vector to store video data
    vector<VideoData> videoList;
    string line;

    // Read data from the input file and populate the vector
    while (getline(inFile, line))
    {
        stringstream ss(line);
        VideoData video;

        // Parse comma-separated values from the line
        getline(ss, video.video_id, ',');
        getline(ss, video.video_name, ',');
        getline(ss, video.video_duration, ',');
        ss >> video.no_likes;
        ss.ignore();
        ss >> video.no_dislikes;
        ss.ignore();
        getline(ss, video.channel_name);

        // Add the video data to the vector
        videoList.push_back(video);
    }

    // Close the input file
    inFile.close();

    // Flag to track whether the video name is updated
    bool updated = false;

    // Update the video name if the video ID matches
    for (auto &video : videoList)
    {
        if (video.video_id == videoId)
        {
            video.video_name = newVideoName;
            updated = true;
        }
    }

    // Write the updated data to the temporary output file
    for (const auto &video : videoList)
    {
        outFile << video.video_id << ","
                << video.video_name << ","
                << video.video_duration << ","
                << video.no_likes << ","
                << video.no_dislikes << ","
                << video.channel_name << endl;
    }

    // Close the temporary output file
    outFile.close();

    // If the video name is updated, replace the original file with the temporary file
    if (updated)
    {
        remove(filename.c_str());
        rename("temp.txt", filename.c_str());
        cout << "Video name updated successfully." << endl;
    }
    else
    {
        // If the video ID was not found, remove the temporary file
        remove("temp.txt");
        cout << "Video ID not found." << endl;
    }
}

// Function to convert minutes to HH:MM format
std::string convertMinutesToHHMM(int minutes)
{
    // Calculate hours and remaining minutes
    int hours = minutes / 60;
    int remainingMinutes = minutes % 60;

    // Create an output string stream for formatting
    std::ostringstream formattedTime;

    // Format the hours and remaining minutes with leading zeros if necessary
    formattedTime << std::setw(2) << std::setfill('0') << hours << ":"
                  << std::setw(2) << std::setfill('0') << remainingMinutes;

    // Return the formatted time as a string
    return formattedTime.str();
}

//Function to calculate score of the video by taking in a video object
double calculateScore(const Video &video)
{
    return static_cast<double>(video.likes) / (video.likes + video.dislikes);
}

// Function to extract a number from a string and return it incremented by 1
int extractNumberFromString(const std::string &input)
{
    // Find the first digit in the input string
    auto digitPosition = std::find_if(input.begin(), input.end(), ::isdigit);

    // Create a substring starting from the first digit to the end of the string
    std::string numberString(digitPosition, input.end());

    try
    {
        // Convert the substring to an integer and increment it by 1
        return std::stoi(numberString) + 1;
    }
    catch (const std::invalid_argument &e)
    {
        // Handle invalid argument exception (e.g., if the string is not a valid number)
        std::cerr << "Invalid argument: " << e.what() << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        // Handle out-of-range exception (e.g., if the number is too large)
        std::cerr << "Out of range: " << e.what() << std::endl;
    }

    // Return 0 in case of any errors
    return 0;
}

// Function to output the average score for a specific channel
void outputChannelScore(const std::string &filename, const std::string &targetChannel)
{
    // Open the video file for reading
    std::ifstream videoFile(filename);
    if (!videoFile.is_open())
    {
        std::cerr << "Error opening the video file.\n";
        return;
    }

    // Variables to store data from each line
    std::string line;
    char delimiter = ',';
    double totalScore = 0.0;
    int videoCount = 0;

    // Read data from the file and calculate the total score and count for the target channel
    while (getline(videoFile, line))
    {
        std::istringstream iss(line);
        Video video;

        // Parse comma-separated values from the line
        if (getline(iss, video.id, delimiter) &&
            getline(iss, video.name, delimiter) &&
            getline(iss, video.duration, delimiter) &&
            (iss >> video.likes) &&
            iss.ignore(std::numeric_limits<std::streamsize>::max(), delimiter) &&
            (iss >> video.dislikes))
        {
            iss.ignore();
            getline(iss, video.channel);

            // Check if the video belongs to the target channel
            if (video.channel == targetChannel)
            {
                // Calculate the score and update total score and count
                totalScore += calculateScore(video);
                videoCount++;
            }
        }
    }

    // Close the video file
    videoFile.close();

    // Check if any videos were found for the target channel
    if (videoCount > 0)
    {
        // Calculate the average score
        double averageScore = totalScore / videoCount;

        // Output the result
        std::cout << "Average score for channel '" << targetChannel << "': " << averageScore << "\n";
    }
    else
    {
        // Output a message if no videos were found for the target channel
        std::cout << "No videos found for the channel '" << targetChannel << "'.\n";
    }
}


// Function to move the file cursor to the end of the file and add a newline
//EOF stands for end of file
void moveToEOF(const std::string &filename)
{
    // Open the file in append mode to move the cursor to the end
    std::ofstream outputFile(filename, std::ios::app);

    // Check if the file is successfully opened
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Add a newline character at the end of the file
    outputFile << '\n';

    // Close the file
    outputFile.close();
}
void split(const std::string &s, char delimiter, std::vector<std::string> &tokens)
{
    // Create an input string stream from the input string
    std::istringstream iss(s);

    // Variable to store each token
    std::string token;

    // Use getline with the specified delimiter to extract tokens from the input stream
    while (std::getline(iss, token, delimiter))
    {
        // Add each token to the vector
        tokens.push_back(token);
    }
}
// Function to display the creator and the user menus
void displayCreatorMenu()
{
    std::cout << "Creator Menu Options:\n";
    std::cout << "1. Show channel score\n";
    std::cout << "2. Create a video\n";
    std::cout << "3. Manage a video\n";
    std::cout << "4. Exit the program\n";
}
void displayUserMenu()
{
    std::cout << "Please enter your choice:\n";
    std::cout << "Press 1 to display 20 videos and their respective channels based on a keyword.\n";
    std::cout << "Press 2 to display top 10 videos based on their like/dislike ratio.\n";
    std::cout << "Press 3 to display top 10 channels with the best scores.\n";
    std::cout << "Press 4 to exit the program.\n";
}
// Function to search for videos based on a keyword
void searchVideos(const std::string &keyword)
{
    // Open the video file for reading
    std::ifstream videoFile("fake_youtube_data_updated.txt");
    if (!videoFile.is_open())
    {
        std::cerr << "Error opening the video file.\n";
        return;
    }

    // Variables to store data from each line
    std::string line;
    char delimiter = ',';
    const int maxResults = 20;

    // Vector to store matching videos
    std::vector<Video> matchingVideos;

    // Read data from the file and search for matching videos
    while (getline(videoFile, line))
    {
        std::istringstream iss(line);
        Video video;

        // Parse comma-separated values from the line
        if (getline(iss, video.id, delimiter) &&
            getline(iss, video.name, delimiter) &&
            getline(iss, video.duration, delimiter) &&
            (iss >> video.likes) &&
            iss.ignore(std::numeric_limits<std::streamsize>::max(), delimiter) &&
            (iss >> video.dislikes))
        {
            iss.ignore();
            getline(iss, video.channel);

            // Check if any field contains the keyword
            if (video.id.find(keyword) != std::string::npos ||
                video.name.find(keyword) != std::string::npos ||
                video.duration.find(keyword) != std::string::npos ||
                video.channel.find(keyword) != std::string::npos)
            {
                matchingVideos.push_back(video);
            }
        }
    }

    // Close the video file
    videoFile.close();

    // Shuffle the matching videos
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 g(seed);
    std::shuffle(matchingVideos.begin(), matchingVideos.end(), g);

    // Output the matching videos (up to maxResults)
    std::cout << "Matching videos:\n";
    for (int i = 0; i < std::min(static_cast<int>(matchingVideos.size()), maxResults); ++i)
    {
        const Video &video = matchingVideos[i];
        std::cout << "ID: " << video.id
                  << ", Name: " << video.name
                  << ", Duration: " << video.duration
                  << ", Likes: " << video.likes
                  << ", Dislikes: " << video.dislikes
                  << ", Channel: " << video.channel << std::endl;
    }

    // Output a message if no matching videos were found
    if (matchingVideos.empty())
    {
        std::cout << "No matching videos found.\n";
    }
}
std::vector<Creator> creatorObject;
std::vector<User> userObject;

// Function to extract the first string before a comma on the last line of a file
std::string extractFirstStringBeforeCommaOnLastLine(const std::string &filePath)
{
    // Open the file for reading
    std::ifstream file(filePath);
    
    // Variables to store data from each line
    std::string line;
    std::string firstString;

    // Check if the file is successfully opened
    if (file.is_open())
    {
        // Read lines from the file
        while (std::getline(file, line))
        {
            // Use a string stream to extract the first string before a comma
            std::istringstream iss(line);
            std::getline(iss, firstString, ',');
        }

        // Close the file
        file.close();
    }
    else
    {
        // Output an error message if the file cannot be opened
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }

    // Return the extracted first string
    return firstString;
}

// Function to display videos from a specific channel
void displayVideosByChannel(const std::string &filename, const std::string &targetChannel)
{
    // Open the file for reading
    std::ifstream inputFile(filename);

    // Check if the file is successfully opened
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Variables to store data from each line
    std::string line;
    std::vector<Video> videos;

    // Read lines from the file
    while (std::getline(inputFile, line))
    {
        // Split the line into fields using the comma as a delimiter
        std::vector<std::string> fields;
        split(line, ',', fields);

        // Check if the line has the expected number of fields (6 in this case)
        if (fields.size() == 6)
        {
            // Create a Video object and populate its fields
            Video video;
            video.id = fields[0];
            video.name = fields[1];
            video.duration = fields[2];
            video.likes = std::stoi(fields[3]);
            video.dislikes = std::stoi(fields[4]);
            video.channel = fields[5];

            // Add the video to the vector
            videos.push_back(video);
        }
    }

    // Close the file
    inputFile.close();

    // Output videos from the specified channel
    std::cout << "Videos from channel " << targetChannel << ":" << std::endl;
    for (const Video &video : videos)
    {
        if (video.channel == targetChannel)
        {
            std::cout << "Video ID: " << video.id << std::endl;
            std::cout << "Video Name: " << video.name << std::endl;
            std::cout << "Duration: " << video.duration << std::endl;
            std::cout << "Likes: " << video.likes << std::endl;
            std::cout << "Dislikes: " << video.dislikes << std::endl;
            std::cout << "Channel: " << video.channel << std::endl;
            std::cout << "-----------------------------" << std::endl;
        }
    }
}

void getBestVideos(const std::string &filename, const std::string &keyword)
{
    std::ifstream videoFile(filename);
    if (!videoFile.is_open())
    {
        std::cerr << "Error opening the video file.\n";
        return;
    }

    std::string line;
    char delimiter = ',';
    const int maxResults = 10;

    std::vector<Video> matchingVideos;

    while (getline(videoFile, line))
    {
        std::istringstream iss(line);
        Video video;

        if (getline(iss, video.id, delimiter) &&
            getline(iss, video.name, delimiter) &&
            getline(iss, video.duration, delimiter) &&
            (iss >> video.likes) &&
            iss.ignore(std::numeric_limits<std::streamsize>::max(), delimiter) &&
            (iss >> video.dislikes))
        {
            iss.ignore();
            getline(iss, video.channel);

            if (video.id.find(keyword) != std::string::npos ||
                video.name.find(keyword) != std::string::npos ||
                video.duration.find(keyword) != std::string::npos ||
                video.channel.find(keyword) != std::string::npos)
            {
                matchingVideos.push_back(video);
            }
        }
    }

    videoFile.close();

    std::sort(matchingVideos.begin(), matchingVideos.end(), [](const Video &a, const Video &b)
              {
                  double ratioA = static_cast<double>(a.likes) / (a.likes + a.dislikes);
                  double ratioB = static_cast<double>(b.likes) / (b.likes + b.dislikes);
                  return ratioA > ratioB; });

    std::cout << "Best 20 videos for keyword '" << keyword << "':\n";
    for (int i = 0; i < std::min(static_cast<int>(matchingVideos.size()), maxResults); ++i)
    {
        const Video &video = matchingVideos[i];
        double ratio = static_cast<double>(video.likes) / (video.likes + video.dislikes);
        std::cout << "Rank " << i + 1 << ": ID: " << video.id
                  << ", Name: " << video.name
                  << ", Duration: " << video.duration
                  << ", Likes: " << video.likes
                  << ", Dislikes: " << video.dislikes
                  << ", Channel: " << video.channel
                  << ", Like/Dislike Ratio: " << ratio << std::endl;
    }

    if (matchingVideos.empty())
    {
        std::cout << "No matching videos found.\n";
    }
}


// Function to search for a specific video by its ID
Video searchForSpecificvideo(const std::string &videoId)
{
    // Open the video file for reading
    std::ifstream videoFile("fake_youtube_data_updated.txt");
    // Check if the file is successfully opened
    if (!videoFile.is_open())
    {
        std::cerr << "Error opening the video file.\n";
        return Video();// Return an empty Video object if the file cannot be opened
    }

    else
    {
        char delimiter = ',';
        std ::string line;
        // Read lines from the file
        while (getline(videoFile, line))
        {
            std::istringstream iss(line);
            Video video;
            // Parse comma-separated values from the line
            if (getline(iss, video.id, delimiter) &&
                getline(iss, video.name, delimiter) &&
                getline(iss, video.duration, delimiter) &&
                (iss >> video.likes) &&
                iss.ignore(std::numeric_limits<std::streamsize>::max(), delimiter) &&
                (iss >> video.dislikes))
            {
                iss.ignore();
                getline(iss, video.channel);
                // Check if the video ID matches the specified ID
                if (video.id == videoId)
                {
                    std::cout << "Video found!\n";
                    std::cout << "ID: " << video.id
                              << ", Name: " << video.name
                              << ", Duration: " << video.duration
                              << ", Likes: " << video.likes
                              << ", Dislikes: " << video.dislikes
                              << ", Channel: " << video.channel << std::endl;
                    return video;
                    videoFile.close();
                }
            }
        }
        videoFile.close();
    }
    return Video();
}

void incrementLikes(const std::string &videoId, const std::string &filePath)
{
    // Open the input file for reading
    std::ifstream inFile(filePath);
    std::vector<Video> videos;

    // Check if the input file is successfully opened
    if (inFile.is_open())
    {
        std::string line;

        // Read lines from the file
        while (getline(inFile, line))
        {
            std::istringstream iss(line);
            Video video;

            // Parse comma-separated values from the line
            getline(iss, video.id, ',');
            getline(iss, video.name, ',');
            getline(iss, video.duration, ',');
            iss >> video.likes;
            iss.ignore();
            iss >> video.dislikes;
            iss.ignore();
            getline(iss, video.channel);

            // Increment likes if the video ID matches the specified ID
            if (video.id == videoId)
            {
                video.likes++;
            }

            // Add the video to the vector
            videos.push_back(video);
        }

        // Close the input file
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    // Open the output file for writing
    std::ofstream outFile(filePath);
    if (outFile.is_open())
    {
        // Write the updated video data to the output file
        for (const auto &video : videos)
        {
            outFile << video.id << ","
                    << video.name << ","
                    << video.duration << ","
                    << video.likes << ","
                    << video.dislikes << ","
                    << video.channel << "\n";
        }

        // Close the output file
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    // Output a message indicating successful like increment
    std::cout << "Likes for video with ID '" << videoId << "' incremented by 1." << std::endl;
}
// Function to increment dislikes for a specific video
void incrementDislikes(const std::string &videoId, const std::string &filePath)
{
    // Open the input file for reading
    std::ifstream inFile(filePath);
    std::vector<Video> videos;

    // Check if the input file is successfully opened
    if (inFile.is_open())
    {
        std::string line;

        // Read lines from the file
        while (getline(inFile, line))
        {
            std::istringstream iss(line);
            Video video;

            // Parse comma-separated values from the line
            getline(iss, video.id, ',');
            getline(iss, video.name, ',');
            getline(iss, video.duration, ',');
            iss >> video.likes;
            iss.ignore();
            iss >> video.dislikes;
            iss.ignore();
            getline(iss, video.channel);

            // Increment dislikes if the video ID matches the specified ID
            if (video.id == videoId)
            {
                video.dislikes++;
            }

            // Add the video to the vector
            videos.push_back(video);
        }

        // Close the input file
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    // Open the output file for writing
    std::ofstream outFile(filePath);
    if (outFile.is_open())
    {
        // Write the updated video data to the output file
        for (const auto &video : videos)
        {
            outFile << video.id << ","
                    << video.name << ","
                    << video.duration << ","
                    << video.likes << ","
                    << video.dislikes << ","
                    << video.channel << "\n";
        }

        // Close the output file
        outFile.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return;
    }

    // Output a message indicating successful dislike increment
    std::cout << "Dislikes for video with ID '" << videoId << "' incremented by 1." << std::endl;
}

// Function to display the top channels with the best scores
void displayTopChannels(const std::string &filename)
{
    // Open the video file for reading
    std::ifstream videoFile(filename);
    if (!videoFile.is_open())
    {
        std::cerr << "Error opening the video file.\n";
        return;
    }

    std::string line;
    char delimiter = ',';

    // Container to store channels
    std::deque<Channel> channels;

    // Read lines from the video file
    while (getline(videoFile, line))
    {
        std::istringstream iss(line);
        Video video;

        // Parse comma-separated values from the line
        if (getline(iss, video.id, delimiter) &&
            getline(iss, video.name, delimiter) &&
            getline(iss, video.duration, delimiter) &&
            (iss >> video.likes) &&
            iss.ignore(std::numeric_limits<std::streamsize>::max(), delimiter) &&
            (iss >> video.dislikes))
        {
            iss.ignore();
            getline(iss, video.channel);

            // Find the channel in the list of channels
            auto it = std::find_if(channels.begin(), channels.end(), [&](const Channel &c)
                                   { return c.name == video.channel; });

            // If the channel doesn't exist, create a new one
            if (it == channels.end())
            {
                Channel newChannel;
                newChannel.name = video.channel;
                newChannel.averageScore = 0.0;
                channels.push_back(newChannel);
                it = std::prev(channels.end());
            }

            // Add the video to the channel's video list and update the average score
            it->videos.push_back(video);
            it->averageScore += calculateScore(video);
        }
    }

    // Close the video file
    videoFile.close();

    // Calculate the average score for each channel
    for (Channel &channel : channels)
    {
        if (!channel.videos.empty())
        {
            channel.averageScore /= channel.videos.size();
        }
    }

    // Sort channels based on average score in descending order
    std::sort(channels.begin(), channels.end(), [](const Channel &a, const Channel &b)
              { return a.averageScore > b.averageScore; });

    // Display the top 10 channels with the best scores
    std::cout << "Top 10 channels with best scores:\n";
    for (int i = 0; i < std::min(static_cast<int>(channels.size()), 10); ++i)
    {
        const Channel &channel = channels[i];
        std::cout << "Rank " << i + 1 << ": " << channel.name << " (Average Score: " << channel.averageScore << ")\n";
    }
}
template <typename T>
int validation(const std::string &oneWord, const std::string &twoWord)
{
    // Open the output file for appending
    std::ofstream outputFile("users.txt", std::ios::app);

    // Combine two words to create the username to check
    std::string usernameToCheck = oneWord + " " + twoWord;

    // Open the input file for reading
    std::ifstream inputFile("users.txt");

    // Check if the input file is open
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening the validation file.\n";
        return -1;
    }
    else
    {
        // Map to store valid usernames and their types
        std::unordered_map<std::string, bool> validUsernames;

        // Read lines from the input file
        std::string line;
        while (getline(inputFile, line))
        {
            std::string ignoredFirstWord, currentFirstWord, currentSecondWord;

            // Parse the line to get the current username and type
            std::istringstream iss(line);
            iss >> ignoredFirstWord >> currentFirstWord >> currentSecondWord;
            std::string currentUsername = currentFirstWord + " " + currentSecondWord;

            double number;

            // Check if the line contains a number (indicating it's a creator)
            if (iss >> number)
            {
                validUsernames[currentUsername] = true;
            }
            else
            {
                validUsernames[currentUsername] = false;
            }
        }

        // Close the input file
        inputFile.close();

        // Check if the username is in the map of valid usernames
        auto it = validUsernames.find(usernameToCheck);
        if (it != validUsernames.end())
        {
            // Check the type of the username and return the appropriate code
            if (it->second)
            {
                std::cout << "Username is valid and belongs to a creator!\n";
                return 0;
            }
            else
            {
                std::cout << "Username is valid and is a regular user.\n";
                return 1;
            }
        }
        else
        {
            // If the username is not in the file, prompt the user to choose a type
            std::cout << "Username is not yet in the file \n Enter 1 if you are a creator and 2 if you are a user:\n";
            int choice;
            std::cin >> choice;

            // Process the user's choice
            if (choice == 1)
            {
                std::cout << "You are a creator!\n";
                std::cout << "Please enter your creator number:\n";
                int creatorNumber;
                std::cin >> creatorNumber;
                std::cout << "Please enter the score of your channel:\n";
                double score;
                std::cin >> score;
                std::cout << "New creator. Adding to the file.\n";

                // Append the new creator to the output file
                outputFile << creatorNumber << " " << oneWord << " " << twoWord << " " << score << "\n";

                // Assuming the existence of a Creator class and a global vector creatorObject
                Creator creator(oneWord + " " + twoWord, creatorNumber, score);
                creatorObject.push_back(creator);

                return 0;
            }
            else if (choice == 2)
            {
                std::cout << "You are a user!\n";
                std::cout << "Please enter your user number:\n";
                int userNumber;
                std::cin >> userNumber;
                std::cout << "New username. Adding to the file.\n";

                // Append the new user to the output file
                outputFile << "\n";
                outputFile << userNumber << " " << oneWord << " " << twoWord << "\n";
                User user(oneWord + " " + twoWord, userNumber);
                userObject.push_back(user);

                return 1;
            }
            else
            {
                std::cout << "Invalid choice\n";
                return -1;
            }

            // Close the output file
            outputFile.close();
        }
    }
}
int main()
{
    std::cout << "Welcome to the YouTube app!\n";
    std::cout << "Hello! Please enter the username (two words):\n";
    string oneWord, twoWord;
    std::cin >> oneWord >> twoWord;
    std::string userWord = oneWord + " " + twoWord;

    int validationResult = validation<int>(oneWord, twoWord);
    std::cout << "Validation result: " << validationResult << endl;

    if (validationResult == 0)
    {
        int validationResult = 0;
        bool isCreatorRunning = true;
        int choiceForCreator;
        while (isCreatorRunning)
        {
            std::cout << "Creator Menu Options:\n";
            std::cout << "1. Implement creator option 1\n";
            std::cout << "2. Implement creator option 2\n";
            std::cout << "3. Implement creator option 3\n";
            std::cout << "4. Exit the program\n";

            std::cout << "Enter your choice (1-4):\n";
            std::cin >> choiceForCreator;

            if (choiceForCreator == 1)
            {

                std::cout << "You chose Creator Option 1\n";
                std::cout << "Please enter the name of the channel that you would like to see the score of:\n";
                std::string combinedWord = oneWord + " " + twoWord;
                std::cin >> oneWord;
                std::cin >> twoWord;
                combinedWord = oneWord + " " + twoWord;
                outputChannelScore("fake_youtube_data_updated.txt", combinedWord);
                isCreatorRunning = true;
            }
            else if (choiceForCreator == 2)
            {
                int videoId = extractNumberFromString(extractFirstStringBeforeCommaOnLastLine("fake_youtube_data_updated.txt"));
                string newVideoId = "video_" + to_string(videoId);
                cout << newVideoId << endl;
                string videoName;
                cout << "Please enter the name of the video (two words):\n";
                string videoOneWord, videoTwoWord;
                cin >> videoOneWord >> videoTwoWord;
                videoName = videoOneWord + " " + videoTwoWord;
                cout << "Please enter the duration of the video in minutes:\n";
                int videoDurationInt;
                cin >> videoDurationInt;
                string videoDuration = convertMinutesToHHMM(videoDurationInt);
                int videoLikes = 0;
                int videoDislikes = 0;
                string videoChannel = userWord;
                ofstream outputFile("fake_youtube_data_updated.txt", ios::app);
                moveToEOF("fake_youtube_data_updated.txt");
                outputFile << newVideoId << "," << videoName << "," << videoDuration << "," << videoLikes << "," << videoDislikes << "," << videoChannel << "\n";
                outputFile.close();
                isCreatorRunning = true;
            }
            else if (choiceForCreator == 3)
            {
                std::cout << "You chose Creator Option 3\n";
                auto videosByChannel = filterVideosByChannelAndPrint("fake_youtube_data_updated.txt", userWord);
                std::vector<Video> videos;
                std::cout << "Select 1) rename a video, 2) reset likes/dislikes and 3) delete the video";
                int choice;
                std::cin >> choice;
                if (choice == 1)
                {
                    std::cout << "Enter the video id: ";
                    std::string videoId;
                    std::cin >> videoId;
                    std::cout << "Enter the new name: ";
                    std::string newName;
                    std::string firstWord;
                    std::string secondWord;
                    std::cin >> firstWord;
                    std::cin >> secondWord;
                    newName = firstWord + " " + secondWord;
                    updateVideoName(videoId, newName, "fake_youtube_data_updated.txt");
                }
                if (choice == 2)
                {
                    std::cout << "Enter the video id: ";
                    std::string videoId;
                    std::cin >> videoId;
                    resetLikesDislikes(videoId, "fake_youtube_data_updated.txt");
                }
                if (choice == 3)
                {
                    std::cout << "Enter the video id: ";
                    std::string videoId;
                    std::cin >> videoId;
                    deleteVideo(videoId, "fake_youtube_data_updated.txt");
                }

                isCreatorRunning = true;
            }
            else if (choiceForCreator == 4)
            {

                isCreatorRunning = false;
                std::cout << "Thank you for using our service!\n";
                std::cout << "The program has now exited and finished.\n";
                break;
            }
            else
            {
                std::cout << "Invalid choice\n";
                return -1;
            }
        }
    }
    else if (validationResult == 1)
    {

        bool isRunning = true;
        int choiceForUser;
        while (isRunning)
        {
            displayUserMenu();
            std::cout << "Enter your choice (1-4):\n";
            std::cin >> choiceForUser;
            if (choiceForUser == 1)
            {
                std::cout << "This option will display 20 videos based on the keyword that you will enter.\n";
                while (1)
                {
                    string keyword;
                    std::cout << "Enter a keyword to search for videos: ";
                    std::cout << "Enter 'exit' to exit the search and return to the main menu :";
                    std::cin >> keyword;

                    if (keyword == "exit")
                    {
                        std::cout << "Exiting search.\n";
                        std::cout << "Returning to main menu.\n";
                        break;
                    }
                    std::cout << "Searching for videos with keyword: " << keyword << endl;
                    searchVideos(keyword);
                    std::cout << "Search complete.Would you like to view a video or return to the main menu?\n";
                    std::cout << "Enter the video id of the video you would like to view or type in 'exit' to return to the main menu: ";
                    string videoId;
                    std::cin >> videoId;
                    if (videoId == "exit")
                    {
                        std::cout << "Returning to main menu.\n";
                        break;
                    }
                    Video video = searchForSpecificvideo(videoId);
                    std::cout << "Do you like or dislike this video?\n";
                    std::cout << "Enter 'like' if you like the video or 'dislike' if you dislike the video: " << endl;
                    string likeOrDislike;
                    std::cin >> likeOrDislike;
                    if (likeOrDislike == "like")
                    {
                        incrementLikes(videoId, "fake_youtube_data_updated.txt");
                    }
                    else if (likeOrDislike == "dislike")
                    {
                        incrementDislikes(videoId, "fake_youtube_data_updated.txt");
                    }
                    else
                    {
                        std::cout << "Invalid choice\n";
                        while (1)
                        {
                            std::cout << "Enter 'like' if you like the video or 'dislike' if you dislike the video: ";
                            std::cin >> likeOrDislike;
                            if (likeOrDislike == "like")
                            {
                                incrementLikes(videoId, "fake_youtube_data_updated.txt");
                                break;
                            }
                            else if (likeOrDislike == "dislike")
                            {
                                incrementDislikes(videoId, "fake_youtube_data_updated.txt");
                                break;
                            }
                            else
                            {
                                std::cout << "Invalid choice\n";
                            }
                        }
                    }
                }
            }
            else if (choiceForUser == 2)
            {
                std::cout << "Enter the keyword you want to search for: ";
                string keyword;
                std::cin >> keyword;
                getBestVideos("fake_youtube_data_updated.txt", keyword);
            }
            else if (choiceForUser == 3)
            {

                displayTopChannels("fake_youtube_data_updated.txt");
                std::cout << "Enter the channel name of the channel you want to view: ";
                string channelName;
                string oneWord, twoWord;
                std::cin >> oneWord >> twoWord;
                channelName = oneWord + " " + twoWord;
                string line;
                ifstream fileStream("fake_youtube_data_updated.txt");
                bool found = false;
                while (std::getline(fileStream, line))
                {
                    while (!found)
                    {
                        if (line.find(channelName) == std::string::npos)
                        {

                            std::cout << "Enter the channel name of the channel you want to view: ";
                            std::cin >> oneWord >> twoWord;
                            channelName = oneWord + " " + twoWord;
                        }
                        else
                        {
                            found = true;
                        }
                    }
                }
                cout << "Displaying videos from channel: " << channelName << endl;
                displayVideosByChannel("fake_youtube_data_updated.txt", channelName);
                cout << "Enter the video id of the video you want to view: ";
                string videoId;
                std::cin >> videoId;
                searchForSpecificvideo(videoId);
                cout << "Do you like or dislike this video?\n";
                cout << "Enter 'like' if you like the video or 'dislike' if you dislike the video: ";
                string likeOrDislike;
                std::cin >> likeOrDislike;
                if (likeOrDislike == "like")
                {
                    incrementLikes(videoId, "fake_youtube_data_updated.txt");
                }
                else if (likeOrDislike == "dislike")
                {
                    incrementDislikes(videoId, "fake_youtube_data_updated.txt");
                }
                else
                {
                    while (likeOrDislike != "like" && likeOrDislike != "dislike")
                    {
                        cout << "Invalid choice. Enter 'like' or 'dislike': ";
                        std::cin >> likeOrDislike;
                        if (likeOrDislike == "like")
                        {
                            incrementLikes(videoId, "fake_youtube_data_updated.txt");
                            break;
                        }
                        else if (likeOrDislike == "dislike")
                        {
                            incrementDislikes(videoId, "fake_youtube_data_updated.txt");
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
            else if (choiceForUser == 4) // Option for exiting the program
            {
                isRunning = false;
                std::cout << "Thank you for using our service!\n";
                std::cout << "The program has now exited and finished.\n";
            }
            else
            {
                std::cout << "Invalid choice\n";
                return -1;
            }
        }
    }

    return 0;
}
