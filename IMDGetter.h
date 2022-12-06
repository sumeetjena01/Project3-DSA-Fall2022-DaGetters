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
    static bool isAlpha(string str);

};

class IMDBData {

public:

    // Members
    vector<Media*> mediaList;

    // Functions
    IMDBData(); // Constructor
    ~IMDBData(); // Destructor
    void printMenu();
    bool LoadTSVFile(string filename);
    static Media* CreateMediaData(string line);
    void getMediaType(int searchInput, vector<Media*> &mediaTypeList);

private:

    void swap(vector<Media*> &mediaTypeList, int up, int down);
    void quickSortYear(vector<Media*> &mediaTypeList, int low, int high);
    int partitionYear(vector<Media*> &mediaTypeList, int low, int high);
    void quickSortRuntime(vector<Media*>& mediaTypeList, int low, int high);
    int partitionRuntime(vector<Media*>& mediaTypeList, int low, int high);
    void quickSortTitle(vector<Media*>& mediaTypeList, int low, int high);
    int partitionTitle(vector<Media*>& mediaTypeList, int low, int high);
    void binaryInsertionSortInt(vector<Media *> &mediaTypeList, bool isYearSorting);
    int binarySearchInt(vector<Media*>& mediaTypeList, int low, int high, int target, bool isYearSorting);
    void binaryInsertionSortStr(vector<Media*>& mediaTypeList);
    int binarySearchStr(vector<Media*>& mediaTypeList, int low, int high, string target);

};
