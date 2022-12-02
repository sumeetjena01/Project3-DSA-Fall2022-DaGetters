#ifndef PROJECT3AMENU_IMDGETTER_H
#define PROJECT3AMENU_IMDGETTER_H
#endif //PROJECT3AMENU_IMDGETTER_H
#include <iostream>
using namespace std;

class Media {

public:

    // Members
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

};

void Media::checkIfAdult (int input) {
    // If the adult column is 1, don't read in input.
    // Otherwise, read in the input.
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
    // When the user selects one of the options, pass all of those options from the .XSLM file into a vector.
    // EX: If the user types in 1, pass all the movies from the .XSLM file into a vector to be sorted later.
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



