#include <iostream>
#include "IMDGetter.h"
using namespace std;

// Constructor
Media::Media() {

}

// Destructor
Media::~Media(){

}

// Constructor
IMDBData::IMDBData() {

}

// Destructor
IMDBData::~IMDBData() {

}

bool Media::checkIfAdult () {

    // If the adult column is 1, don't read in input.
    // Otherwise, read in the input.
    return isAdult;

}

bool IMDBData::LoadTSVFile(string filename) {

    ifstream inputFile(filename);
    if(!inputFile.is_open()) {
        cout << "The file is not open." << endl;
    }
    string headerLine;
    getline(inputFile, headerLine);

    string dataLine;
    while (inputFile.is_open() && !inputFile.eof()) {
        getline(inputFile, dataLine);
        Media* media = CreateMediaData(dataLine);
        mediaList.push_back(media);
    }
    inputFile.close();
    return true;

}

Media* IMDBData::CreateMediaData(string line) {

    Media* media = new Media();
    stringstream sStream(line);

    while(sStream.good()) {

        string tConst; // Not used.
        getline(sStream, tConst, '\t');

        string titleType; // Whether it's a movie, short, documentary, or TV show.
        getline(sStream, titleType, '\t');

        string primaryTitle; // The ACTUAL title of the media, such as "Top Gun".
        getline(sStream, primaryTitle, '\t');

        string originalTitle; // Not used.
        getline(sStream, originalTitle, '\t');

        string adultRating;
        getline(sStream, adultRating, '\t');
        int adult = stoi(adultRating);
        bool isAdult = (adult == 1);

        string startYear;
        getline(sStream, startYear, '\t');
        int intStartYear = stoi(startYear);

        string endYear; // Not used.
        getline(sStream, endYear, '\t');
        int intEndYear = stoi(endYear);

        string runtime;
        getline(sStream, runtime, '\t');
        int realRuntime = stoi(runtime);

        string genre; // Not used.
        getline(sStream, genre, '\t');

        media->tConst = tConst;
        media->titleType = stoi(titleType);
        media->primaryTitle = primaryTitle;
        media->isAdult = isAdult;
        media->startYear = startYear;
        media->endYear = endYear;
        // media->runtime = runtime; *Have to fix this!*

    }
    return media;
}

void IMDBData::getMediaType(int searchInput, vector<Media*> &mediaTypeList) {

    for(int i = 0; i < mediaList.size(); i++) {
        Media* mediaType = mediaList[i];
        if(mediaType->titleType == (searchInput)) { // Title Type = Whether it's a movie, show, etc.
            mediaTypeList.push_back(mediaType);
        }
    }
}

void IMDBData::PrintMenu() {

    cout << "Welcome to IMDGetter!" << endl;
    cout << "_____________________" << endl;
    cout << endl;

    cout << "What would you like to search for?" << endl;
    cout << "1. Movies" << endl;
    cout << "2. TV Shows" << endl;
    cout << "3. Documentaries" << endl;
    cout << "4. Shorts" << endl;
    int searchInput;
    cin >> searchInput;
    while (searchInput < 1 || searchInput > 4) {
        cout << "Please enter a valid input. If needed, refer the menu above. " << endl;
        cin >> searchInput;
    }
    // When the user selects one of the options, pass all of all the media types from the .TSV file into a vector.
    // But, within that function, if the movie has a 1 in the adult column, do not read that into the vector.

    if (searchInput == 1) {
        vector<Media*> movies;
        getMediaType(searchInput, movies);
    }
    else if (searchInput == 2) {
        vector<Media*> shows;
        getMediaType(searchInput, shows);
    }
    else if (searchInput == 3) {
        vector<Media*> documentary;
        getMediaType(searchInput, documentary);
    }
    else if (searchInput == 4) {
        vector<Media*> shorts;
        getMediaType(searchInput, shorts);
    }

    cout << "What would you like to sort by?" << endl;
    cout << "1. Title" << endl; // Alphabetical
    cout << "2. Release Year" << endl;
    cout << "3. Runtime" << endl;
    int sortInput;
    cin >> sortInput;
    while (sortInput < 1 || sortInput > 3) {
        cout << "Please enter a valid input. If needed, refer the menu above. " << endl;
        cin >> sortInput;
    }

    cout << "How would you like to perform your search?" << endl;
    cout << "1. Quick Sort" << endl;
    cout << "2. Binary Insertion Sort" << endl;
    int algorithmInput;
    cin >> algorithmInput;

    while (algorithmInput == 1) {
        // Call Quick Sort Function
        cout << "Quick Sort = Called" << endl;
        break;
    }
    while (algorithmInput == 2) {
        // Call Binary Insertion Sort Function
        cout << "Binary Insertion Sort = Called" << endl;
        break;
    }
    while (algorithmInput != 1 && algorithmInput != 2) {
        // Print error message.
        cout << "Please enter a valid input. If needed, refer the menu above. " << endl;
        cin >> algorithmInput;
        if (algorithmInput == 1) {
            // Call the Quick Sort function, then comment out the next line.
            cout << "Quick Sort = Called" << endl;
        }
        if (algorithmInput == 2) {
            // Call the Binary Insertion Sort function, then comment out the next line.
            cout << "Binary Insertion Sort = Called" << endl;
        }
    }
}
