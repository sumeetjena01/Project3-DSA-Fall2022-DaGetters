#ifndef PROJECT3AMENU_IMDGETTER_H
#define PROJECT3AMENU_IMDGETTER_H
#endif //PROJECT3AMENU_IMDGETTER_H
#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>

using namespace std;

class Media {

public:

    // Members
    string tConst;
    string titleType;
    string primaryTitle;
    bool isAdult;
    string startYear;
    string endYear;
    string genre;
    int runtime;

    // Functions
    void checkIfAdult(int input);
    void PrintMenu();
    static bool LoadTSVFile(string filename, vector<Media*> &list);
    static Media* CreateMediaData(string line);


private:

    unordered_set<std::string> filterTypes = {"year", "genre", "runtime"};
    unordered_set<std::string> sortTypes = {"title", "type", "year", "runTime"}; //Use these to validate input with find() or count()?

};

void Media::checkIfAdult (int input) {
    // If the adult column is 1, don't read in input.
    // Otherwise, read in the input.
}

// After that^ is done, pass the data into a vector, to be sorted later.

bool Media::LoadTSVFile(string filename, vector<Media*> &list) {

    ifstream inputFile(filename);
    if(!inputFile.is_open()) {
        cout << "The file is not open." << endl;
    }
    string headerLine;
    getline(inputFile, headerLine);

    string dataLine;
    while (inputFile.is_open() && !inputFile.eof()) {
        getline(inputFile, dataLine);
        Media* mediaData = CreateMediaData(dataLine);
        list.push_back(mediaData);
    }
    inputFile.close();
    return true;

}

Media* Media::CreateMediaData(string line) {

    Media* mediaData = new Media();
    stringstream sStream(line);

    while(sStream.good()) {
        string tConst;
        getline(sStream, tConst, '\t');

        string titleType;
        getline(sStream, titleType, '\t');

        string primaryTitle;
        getline(sStream, primaryTitle, '\t');

        string startYear;
        getline(sStream, startYear, '\t');
        int intStartYear = stoi(startYear);

        string endYear;
        getline(sStream, endYear, '\t');
        int intEndYear = stoi(endYear);

        string runtime;
        getline(sStream, runtime, '\t');
        int realRuntime = stoi(runtime);

        mediaData->tConst = tConst;
        mediaData->titleType = titleType;
        mediaData->primaryTitle = primaryTitle;
        mediaData->startYear = startYear;
        mediaData->endYear = endYear;
        // mediaData->runtime = runtime; *Have to fix.* 

    }
    return mediaData;
}

void Media::PrintMenu() {

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
    // When the user selects one of the options, pass all of those options from the .TSV file into a vector.
    // EX: If the user types in 1, pass all the movies from the .TSV file into a vector to be sorted later.
    // But, within that function, if the movie has a 1 in the adult column, do not read that into the vector.

    cout << "What would you like to sort by?" << endl;
    cout << "1. Title" << endl;
    cout << "2. Release Year" << endl;
    cout << "3. Runtime" << endl;
    int sortInput;
    cin >> sortInput;
    while (sortInput < 1 || sortInput > 3) {
        cout << "Please enter a valid input. If needed, refer the menu above. " << endl;
        cin >> sortInput;
    }

    // If they pick 1, meaning they want to see movies, should I sort the vector here?

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
