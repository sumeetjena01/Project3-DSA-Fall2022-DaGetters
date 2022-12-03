#include <iostream>
#include "IMDGetter.h"
using namespace std;

int main() {

    IMDBData imdbGetter; // Object
    imdbGetter.LoadTSVFile("title.basics.tsv");
    imdbGetter.PrintMenu();
    return 0;
}

/*

 The purpose of the project is to take in a large dataset, and sort it using two algorithms, and compare the times.
 So, if the user wants to see a list of all the movies on IMDb, we have to read in all the movies from the .TSV file, and put them into a vector.
 From there, we will sort the movies by 1 of 3 things: Title, Release year, or Runtime.
 Likewise, if the user wants to see a list of all the shows, we repeat the same process. 

 */
