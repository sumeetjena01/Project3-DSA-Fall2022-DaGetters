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
    int startYear;
    int endYear;
    string genre;
    int runtime;

    //Functions
    Media(); // Constructor
    ~Media(); // Destructor
    bool checkIfAdult();
    static int convertToInt(string str);

private:

    unordered_set<std::string> filterTypes = {"year", "genre", "runtime"}; // What is this for? - Sumeet
    unordered_set<std::string> sortTypes = {"title", "type", "year", "runTime"}; // Use these to validate input with find() or count()?

    // We don't sort by type, right? We only need to sort by title (alphabetically), or year and runTime (numerically). - Sumeet
    // The first question the user asks, already filters out the type of media they're looking for.
    // After that, the user is only trying to sort between those 3 things, title, year, and runtime.
    // If the user wants to see movies, all the movies will be loaded into a vector called "movies" (Line 187 in the IMDGetter.cpp file)
    // From there, we just sort the vector using an algorithm, right? - Sumeet

};

class IMDBData {

public:

    // Members
    vector<Media*> mediaList;

    // Functions
    IMDBData(); // Constructor
    ~IMDBData(); // Destructor
    void checkIfAdult(int input);
    void PrintMenu();
    bool LoadTSVFile(string filename);
    static Media* CreateMediaData(string line);
    void getMediaType(int searchInput, vector<Media*> &mediaTypeList);

};
