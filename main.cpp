#include <iostream>
#include "IMDGetter.h"
using namespace std;

int main() {

    PrintMenu();
    return 0;
}

/*
 The purpose of the project is to take in a large dataset, and sort it using two algorithms, and compare the times.

 My part involves just handling input validation.
 So, if the user wants to see a list of all the movies on IMDb, I have to read in all the movies from the .XSLM file, and put them into a vector.
 From there, my teammate will sort the movies, and print them out.

 The issue is how to read data from a .XSLM file, and put it into a vector.

 If you run the program, there are basically 3 questions that pop up. I only have to deal with the first one.
 If the user selects a "1" for Movies, then I read in all the movies from the TSV file, and place them into a vector.

 */