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
    int titleType;
    string primaryTitle;
    bool isAdult;
    string startYear;
    string endYear;
    string genre;
    int runtime;

    //Functions
    Media(); // Constructor
    ~Media(); // Destructor
    bool checkIfAdult();

private:

    unordered_set<std::string> filterTypes = {"year", "genre", "runtime"}; // What is this for?
    unordered_set<std::string> sortTypes = {"title", "type", "year", "runTime"}; // Use these to validate input with find() or count()?
    // We don't sort by type, right? We only need to sort by title (alphabetically), or year and runTime (numerically).
    // The first question the user asks already filters out the type they're looking for.
    // After that, the user is only trying to sort between those 3 things, title, year, and runtime.

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
