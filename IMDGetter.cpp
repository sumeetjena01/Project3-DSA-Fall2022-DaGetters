#include <iostream>
#include <fstream>
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

static bool isAlpha(string str) {

    // Checking if the movie has an English title.
    for(int i = 0; i < str.size(); i++) {
        char ch = str[i];
        if(!isalpha(ch)) {
            return false;
        }
    }
    return true;
}

static int convertToInt(string str) {

    int i = 0;
    try {
        i = stoi(str);
    }
    catch(exception e){
        i = -1;
    }
    return i;
}

bool IMDBData::LoadTSVFile(string filename) {

    ifstream inputFile;
    inputFile.open(filename);
    if(!inputFile.is_open()) {
        cout << "The file is not open." << endl;
    }
    string headerLine;
    getline(inputFile, headerLine);

    string dataLine;
    while (inputFile.is_open() && !inputFile.eof() && mediaList.size() < 200000) {
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

    if(sStream.good()) {

        string tConst; // Not used.
        getline(sStream, tConst, '\t');

        string titleType; // Whether it's a movie, short, TV show, etc.
        getline(sStream, titleType, '\t');

        string primaryTitle; // The ACTUAL title of the media, such as "Top Gun".
        getline(sStream, primaryTitle, '\t');

        string originalTitle; // Not used.
        getline(sStream, originalTitle, '\t');

        string adultRating;
        getline(sStream, adultRating, '\t');
        int adult = convertToInt(adultRating);
        bool isAdult = (adult == 1);

        int intStartYear = -1;
        string startYear;
        getline(sStream, startYear, '\t');
        if (startYear.compare("\\N") == 0) {
            intStartYear = 0;
        }
        else {
            intStartYear = convertToInt(startYear);
        }

        int intEndYear = -1;
        string endYear; // Not used.
        getline(sStream, endYear, '\t');
        if(endYear.compare("\\N") == 0) {
            intEndYear = 0;
        }
        else {
            intEndYear = convertToInt(endYear);
        }

        int intRunTime = -1;
        string runtime;
        getline(sStream, runtime, '\t');
        if(runtime.compare("\\N") == 0) {
            intRunTime = 0;
        }
        else {
            intRunTime = convertToInt(runtime);
        }

        string genre; // Not used.
        getline(sStream, genre, '\t');

        media->tConst = tConst;
        media->titleType = titleType;
        media->primaryTitle = primaryTitle;
        media->isAdult = isAdult;
        media->startYear = intStartYear;
        media->endYear = intEndYear;
        media->runtime = intRunTime;
        media->genre = genre;

    }
    return media;
}

void IMDBData::getMediaType(int searchInput, vector<Media*> &mediaTypeList) {

    string searchTitleType = "";
    if(searchInput == 1) {
        searchTitleType = "movie";
    }
    else if (searchInput == 2) {
        searchTitleType = "tvSeries";
    }
    else if (searchInput == 3) {
        searchTitleType = "tvEpisode";
        // Documentary is a genre, not a media type.
        // Switch this to TV Episode, so a user can sort individual episodes by highest rating.
        // "tvEpisode"
    }
    else if (searchInput == 4) {
        searchTitleType = "short";
    }
    else {
        return;
    }

    for(int i = 0; i < mediaList.size(); i++) {
        Media* media = mediaList[i];
        string titleType = media->titleType;
        if(titleType.compare(searchTitleType) == 0) {// Title Type = Whether it's a movie, show, etc.
            string primaryTitle = media->primaryTitle;
            if (isAlpha(primaryTitle))
                mediaTypeList.push_back(media);
        }
    }
}

void IMDBData::printMenu() {

    cout << "Welcome to IMDGetter!" << endl;
    cout << "_____________________" << endl;
    cout << endl;

    cout << "What would you like to search for?" << endl;
    cout << "1. Movies" << endl;
    cout << "2. TV Shows" << endl;
    cout << "3. TV Episodes" << endl;
    cout << "4. Shorts" << endl;
    int searchInput;
    cin >> searchInput;
    while (searchInput < 1 || searchInput > 4) {
        cout << "Please enter a valid input. If needed, refer the menu above. " << endl;
        cin >> searchInput;
    }
    // When the user selects one of the options, pass all of all the media types from the .TSV file into a vector.
    // But, within that function, if the movie has a 1 in the adult column, do not read that into the vector.

    vector<Media*> allMedia;
    getMediaType(searchInput, allMedia);
    vector<Media*> allMedia2 = allMedia;
    cout << "What would you like to sort by?" << endl;
    cout << "1. Title" << endl; // Alphabetical
    cout << "2. Release Year" << endl;
    cout << "3. Runtime" << endl;
    int sortInput;
    cin >> sortInput;
    //int algorithmInput;
    //cin >> algorithmInput;
    fstream timeFile;
    timeFile.open("times.txt");
    while (sortInput < 1 || sortInput > 3) {
        cout << "Please enter a valid input. If needed, refer the menu above. " << endl;
        cin >> sortInput;
    }
    //cout << mediaList.size()<<;
    // Call Quick Sort Function
    // Call Binary Insert Sort Function
    
    if (sortInput == 1) {
        //binary sort allMedia2 here
        quickSortTitle(allMedia, 0, allMedia.size() - 1);
    }
    else if (sortInput == 2) {
        quickSortYear(allMedia, 0, allMedia.size() - 1);
    }
    else {
        quickSortRuntime(allMedia, 0, allMedia.size() - 1);
    }
    cout << "\n\nafter sorting: \n";
    for (Media* i : allMedia) {
        cout << "title:" <<i->primaryTitle<< "   year: " << i->startYear << "    runtime: " <<i->runtime<< "\n" ;
    }

}
//based quickSort code off Aman powerpoint 6 (Sorting)
void IMDBData::quickSortYear(vector<Media*> &mediaTypeList, int low, int high) {
    if(low < high) {
        int pivot = partitionYear(mediaTypeList, low, high);
        //cout << "pivotidx: " << pivot << "\n";
        quickSortYear(mediaTypeList, low, pivot-1);
        quickSortYear(mediaTypeList, pivot+1, high);
    }
}
int IMDBData::partitionYear(vector<Media*> &mediaTypeList, int low, int high) {
    int pivot = mediaTypeList[low]->startYear;
    int up = low, down = high;

    //std::cout << "low: " << low << " high: " << high <<" pivot: "<<pivot<<"\n";
    while(up<down) {
        //std::cout << "up: " << up << " down: " << down << "\n";

        for(int j = up; j< high; j++) {
            if(mediaTypeList[up]->startYear > pivot) {
                break;
            }
            up++;
        }
        for(int j = high; j>low; j--) {
            if(mediaTypeList[down]->startYear < pivot ) {
                break;
            }
            down--;
        }
        if(up < down) {
            swap(mediaTypeList, up, down);
        }

    }
    swap(mediaTypeList, low, down);
    return down;

}
void IMDBData::quickSortRuntime(vector<Media*>& mediaTypeList, int low, int high) {
    if (low < high) {
        int pivot = partitionRuntime(mediaTypeList, low, high);
        //cout << "pivotidx: " << pivot << "\n";
        quickSortRuntime(mediaTypeList, low, pivot - 1);
        quickSortRuntime(mediaTypeList, pivot + 1, high);
    }
}
int IMDBData::partitionRuntime(vector<Media*>& mediaTypeList, int low, int high) {
    int pivot = mediaTypeList[low]->runtime;
    int up = low, down = high;

    //std::cout << "low: " << low << " high: " << high << " pivot: " << pivot << "\n";
    while (up < down) {
        //std::cout << "up: " << up << " down: " << down << "\n";

        for (int j = up; j < high; j++) {
            if (mediaTypeList[up]->runtime > pivot) {
                break;
            }
            up++;
        }
        for (int j = high; j > low; j--) {
            if (mediaTypeList[down]->runtime < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(mediaTypeList, up, down);
        }

    }
    swap(mediaTypeList, low, down);
    return down;

}

void IMDBData::quickSortTitle(vector<Media*>& mediaTypeList, int low, int high) {
    if (low < high) {
        int pivot = partitionTitle(mediaTypeList, low, high);
        //cout << "pivotidx: " << pivot << "\n";
        quickSortTitle(mediaTypeList, low, pivot - 1);
        quickSortTitle(mediaTypeList, pivot + 1, high);
    }
}
int IMDBData::partitionTitle(vector<Media*>& mediaTypeList, int low, int high) {
    string pivot = mediaTypeList[low]->primaryTitle;
    int up = low, down = high;

    //std::cout << "low: " << low << " high: " << high << " pivot: " << pivot << "\n";
    while (up < down) {
        //std::cout << "up: " << up << " down: " << down << "\n";

        for (int j = up; j < high; j++) {
            if (mediaTypeList[up]->primaryTitle > pivot) {
                break;
            }
            up++;
        }
        for (int j = high; j > low; j--) {
            if (mediaTypeList[down]->primaryTitle < pivot) {
                break;
            }
            down--;
        }
        if (up < down) {
            swap(mediaTypeList, up, down);
        }

    }
    swap(mediaTypeList, low, down);
    return down;

}

void IMDBData::swap(vector<Media*> &mediaTypeList, int up, int down) {
    Media* tmp = mediaTypeList[up];
    mediaTypeList[up] = mediaTypeList[down];
    mediaTypeList[down] = tmp;
}
