#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <random>
#include "IMDGetter.h"
using namespace std;

// Constructor
Media::Media() {

}

// Destructor
Media::~Media() {

}

// Constructor
IMDBData::IMDBData() {

}

// Destructor
IMDBData::~IMDBData() {

}


static bool charIsAlpha(char ch) {
	return ch >= 0 && ch <= 168;
}

static bool isAlpha(string str) {

	// Checking if the movie has an English title.
	for (int i = 0; i < str.size(); i++) {
		char ch = str[i];
		if (!charIsAlpha(ch)) {
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
	catch (exception e) {
		i = -1;
	}
	return i;
}

bool IMDBData::LoadTSVFile(string filename) {

	ifstream inputFile;
	inputFile.open(filename);
	if (!inputFile.is_open()) {
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

	if (sStream.good()) {

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
		if (endYear.compare("\\N") == 0) {
			intEndYear = 0;
		}
		else {
			intEndYear = convertToInt(endYear);
		}

		int intRunTime = -1;
		string runtime;
		getline(sStream, runtime, '\t');
		if (runtime.compare("\\N") == 0) {
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

void IMDBData::getMediaType(int searchInput, vector<Media*>& mediaTypeList) {

	string searchTitleType = "";
	if (searchInput == 1) {
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

	for (int i = 0; i < mediaList.size(); i++) {
		Media* media = mediaList[i];
		string titleType = media->titleType;
		if (titleType.compare(searchTitleType) == 0) {// Title Type = Whether it's a movie, show, etc.
			string primaryTitle = media->primaryTitle;
			if (isAlpha(primaryTitle) && media->runtime > 0 && media->startYear != 0 && !media->isAdult) {
				mediaTypeList.push_back(media);
			}

		}
	}
}

void IMDBData::printMenu() {

	cout << "Welcome to IMDGetter!" << endl;
	cout << "_____________________" << endl;
	cout << endl;

	// When the user selects one of the options, pass all of all the media types from the .TSV file into a vector.
	// But, within that function, if the movie has a 1 in the adult column, do not read that into the vector.
	while (true) {
		cout << "What would you like to search for?" << endl;
		cout << "1. Movies" << endl;
		cout << "2. TV Shows" << endl;
		cout << "3. TV Episodes" << endl;
		cout << "4. Shorts" << endl;
		cout << "0. Stop Program" << endl;
		int searchInput;
		cin >> searchInput;
		while (searchInput < 0 || searchInput > 4) {
			cout << "Please enter a valid input. If needed, refer the menu above. " << endl;
			cin >> searchInput;
		}
		if (searchInput == 0) {
			break;
		}
		vector<Media*> allMedia;
		getMediaType(searchInput, allMedia);
		cout << "What would you like to sort by?" << endl;
		cout << "1. Title" << endl; // Alphabetical
		cout << "2. Release Year" << endl;
		cout << "3. Runtime" << endl;

		int sortInput;
		cin >> sortInput;
		fstream timeFile;
		timeFile.open("times.txt");
		while (sortInput < 1 || sortInput > 3) {
			cout << "Please enter a valid input. If needed, refer the menu above. " << endl;
			cin >> sortInput;
		}

		int isShuffled;
		cout << "Would you like the data to be shuffled before sorting?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. No" << endl;
		cin >> isShuffled;
		if (isShuffled == 2 && sortInput == 1) quickSortTitle(allMedia, 0, allMedia.size() - 1);
		if (isShuffled == 2 && sortInput == 2) quickSortYear(allMedia, 0, allMedia.size() - 1);
		if (isShuffled == 2 && sortInput == 3) quickSortRuntime(allMedia, 0, allMedia.size() - 1);

		vector<Media*> allMedia2 = allMedia;

		cout << "Which sort would you like to display the results of?" << endl;
		cout << "1. Quick Sort" << endl;
		cout << "2. Binary Insertion Sort" << endl;

		int algorithmInput;
		cin >> algorithmInput;

		std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point quickSortTime;
		std::chrono::high_resolution_clock::time_point binaryInsertTime;


		if (sortInput == 1) {
			// Call Quick Sort Function
			quickSortTitle(allMedia, 0, allMedia.size() - 1);
		}
		else if (sortInput == 2) {
			quickSortYear(allMedia, 0, allMedia.size() - 1);
		}
		else if (sortInput == 3) {
			quickSortRuntime(allMedia, 0, allMedia.size() - 1);
		}
		quickSortTime = std::chrono::high_resolution_clock::now();
		double quickTimeDiff = chrono::duration_cast<chrono::microseconds>(quickSortTime - beginTime).count();

		beginTime = std::chrono::high_resolution_clock::now();
		if (sortInput == 1) {
			// Call Quick Sort Function
			binaryInsertionSortStr(allMedia2);
		}
		else if (sortInput == 2) {
			binaryInsertionSortInt(allMedia2, true);
		}
		else if (sortInput == 3) {
			binaryInsertionSortInt(allMedia2, false);
		}
		binaryInsertTime = std::chrono::high_resolution_clock::now();

		double binaryTimeDiff = chrono::duration_cast<chrono::microseconds>(binaryInsertTime - beginTime).count();
		bool quickFast = quickTimeDiff - binaryTimeDiff < 0;
		float sortTimeDiff = (quickFast) ? ((quickTimeDiff - binaryTimeDiff) * -1) : (quickTimeDiff - binaryTimeDiff);

		cout << "\nFinal Results: \n";
		auto* printMedia = (algorithmInput == 1)? &allMedia : &allMedia2;
		for (Media* i : *printMedia) {
			cout << "Title: " << ((i->primaryTitle.size()>95)?(i->primaryTitle.substr(0,95)):(i->primaryTitle)) << setw(100 - i->primaryTitle.size()) << "Year: " << i->startYear << setw(20) << "Runtime: " << i->runtime << "\n";
		}
		cout << endl;

		cout << "Final Time Difference: Quick Sort took " << quickTimeDiff << " microseconds, and Binary Insertion sort took " << binaryTimeDiff << " microseconds, so quickSort was " << (sortTimeDiff) << ((quickFast) ? (" microseconds faster") : (" microseconds slower")) << " than Binary Insertion sort.\n\n\n" << endl;

		
	}
}

// The quickSort code is based off Aman's PowerPoint on Canvas (Module 6, Sorting).
void IMDBData::quickSortYear(vector<Media*>& mediaTypeList, int low, int high) {
	if (low < high) {
		int pivot = partitionYear(mediaTypeList, low, high);
		quickSortYear(mediaTypeList, low, pivot - 1);
		quickSortYear(mediaTypeList, pivot + 1, high);
	}
}

int IMDBData::partitionYear(vector<Media*>& mediaTypeList, int low, int high) {

	int pivot = mediaTypeList[low]->startYear;
	int up = low, down = high;

	while (up < down) {

		for (int j = up; j < high; j++) {
			if (mediaTypeList[up]->startYear > pivot) {
				break;
			}
			up++;
		}
		for (int j = high; j > low; j--) {
			if (mediaTypeList[down]->startYear < pivot) {
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

void IMDBData::quickSortRuntime(vector<Media*>& mediaTypeList, int low, int high) {

	if (low < high) {
		int pivot = partitionRuntime(mediaTypeList, low, high);
		quickSortRuntime(mediaTypeList, low, pivot - 1);
		quickSortRuntime(mediaTypeList, pivot + 1, high);
	}
}

int IMDBData::partitionRuntime(vector<Media*>& mediaTypeList, int low, int high) {

	int pivot = mediaTypeList[low]->runtime;
	int up = low, down = high;

	while (up < down) {

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
		quickSortTitle(mediaTypeList, low, pivot - 1);
		quickSortTitle(mediaTypeList, pivot + 1, high);
	}
}

int IMDBData::partitionTitle(vector<Media*>& mediaTypeList, int low, int high) {
	string pivot = mediaTypeList[low]->primaryTitle;
	int up = low, down = high;

	while (up < down) {

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

void IMDBData::swap(vector<Media*>& mediaTypeList, int up, int down) {

	Media* tmp = mediaTypeList[up];
	mediaTypeList[up] = mediaTypeList[down];
	mediaTypeList[down] = tmp;

}

static void shiftArray(vector<Media*>& arr, int i, int index) {
	Media* tmp = arr[i];
	for (int j = i - 1; j >= index; j--) {
		arr[j + 1] = arr[j];

	}
	arr[index] = tmp;
}
void IMDBData::binaryInsertionSortInt(vector<Media*>& mediaTypeList, bool isYearSorting)
{
	for (int i = 1; i < mediaTypeList.size(); i++)
	{
		int index = 0;
		if (isYearSorting) index = binarySearchInt(mediaTypeList, 0, i - 1, mediaTypeList.at(i)->startYear, isYearSorting);
		else index = binarySearchInt(mediaTypeList, 0, i - 1, mediaTypeList.at(i)->runtime, isYearSorting);
		//rotate(mediaTypeList.rend() - i - 1, mediaTypeList.rend() - i, mediaTypeList.rend() - index);
		shiftArray(mediaTypeList, i, index);
	}
}

int IMDBData::binarySearchInt(vector<Media*>& mediaTypeList, int low, int high, int target, bool isYearSorting) {
	while (low <= high)
	{
		int center = low + (high - low) / 2;
		int centerElement;
		if (isYearSorting) centerElement = mediaTypeList.at(center)->startYear;
		else centerElement = mediaTypeList.at(center)->runtime;

		if (target == centerElement) return ++center;
		else if (target > centerElement) low = ++center;
		else high = --center;
	}
	return low;
}

void IMDBData::binaryInsertionSortStr(vector<Media*>& mediaTypeList) {
	for (int i = 1; i < mediaTypeList.size(); i++)
	{
		int index = binarySearchStr(mediaTypeList, 0, i - 1, mediaTypeList.at(i)->primaryTitle);
		//rotate(mediaTypeList.rend() - i - 1, mediaTypeList.rend() - i, mediaTypeList.rend() - index);
		shiftArray(mediaTypeList, i, index);

	}
}

int IMDBData::binarySearchStr(vector<Media*>& mediaTypeList, int low, int high, string target) {

	while (low <= high)
	{
		int center = low + (high - low) / 2;
		string centerElement = mediaTypeList.at(center)->primaryTitle;

		if (target == centerElement) return ++center;
		else if (target > centerElement) low = ++center;
		else high = --center;
	}
	return low;
}
