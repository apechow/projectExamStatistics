/* 
 FUNCTIONS, FILES, and ARRAYS
 
 Project Exam Statistics
 
 ==> Annabella Chow <==
 
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 15;

//declaring functions
void introduction();
string getFileName();
void readFile(string name[], int score[], int maxArraySize, int &arraySize, string fileName);
double calcAverage(int score[], int arraySize);
void resortHighToLowScore(string name[], int score[], int arraySize);
string writeArrays(string name[], int score[], int arraySize, string fileName);
void displayCalcs(string outFile, int numOfStudents, double classAve);

int main()
{   //declaring/initializing variables
    string name[100];
    int score[100];
    double classAve;
    int arraySize = 0;
    string inFileName, outFileName;

    //calls functions
    introduction(); //print introduction
    inFileName = getFileName(); // get file name
    readFile(name, score, MAX_SIZE, arraySize, inFileName); // read file and put in two arrays
    classAve = calcAverage(score, arraySize); // get class average
    resortHighToLowScore(name, score, arraySize); // resort the arrays to descending order
    outFileName = writeArrays(name, score, arraySize, inFileName); // get outfile name and write arrays to file
    displayCalcs(outFileName, arraySize, classAve); // display all calculations
    return 0;
}

/* This function prints the welcome and purpose
of the program*/
void introduction() {
    cout << "Welcome!" << endl;
    cout << "This program provides exam statistics for a CIS class." << endl;
}

/* 
 This function prompts the user to enter
 file name and then returns it
 */
string getFileName() {
    string fileName;

    cout << "What is the input file's name? ";
    getline(cin, fileName);

    return fileName;
}

/* This function reads the file and sorts into two arrays - 
one with the student name and the other with the score */
void readFile(string name[], int score[], int maxArraySize, int &arraySize, string fileName){
    ifstream inFile;

    // declaring vars
    string line, temp, test;
    int i = 0;

    inFile.open(fileName); //open file

    if (!inFile) { //check file opens
        cout << "File \"" << fileName << "\" could not be opened!" << endl;
        exit (EXIT_FAILURE);
    }

    while (i < maxArraySize && getline(inFile, line)) {// in while loop to stop reading at the end of file
    //and that list does not reach past array size
        stringstream temp(line);       // to allow reading from string temp
        getline(temp, name[i], ';');  // read the student's name from temp into names[i]: stop at the ';'
        temp >> score[i];             // read the student's score from temp into scores[i]
        i++;                             
    }
    arraySize = i; // send it back to main
    
    // used to test if there is more data in the input file 
    if (arraySize == maxArraySize && getline(inFile, test)) {
        cout << "The array is full and there's more data in the file." << endl;
        cout << "The program ends here!" << endl;
        exit(EXIT_FAILURE);
    }
    inFile.close();
}

/* This function calculates the class average base on the score array*/
double calcAverage(int score[], int arraySize) {
    double total = 0; // initializing var
    double average; 

    for (int i = 0; i < arraySize; i++) {
        total += score[i]; // calc total scores
    }

    average = total / arraySize; // calc average

    return average;
}

/* This function resorts the two arrays by 
descending order of scores*/
void resortHighToLowScore(string name[], int score[], int arraySize) {
    string tempVar;
    int biggestScore;
    int biggestScoreIndex;

    for (int i = 0; i < arraySize + 1; i++) {
        biggestScore = score[i]; //initializing var to find biggest #
        biggestScoreIndex = i; //reinitializes each time so if there is no need to change, 
                                //no change will occur
        for (int j = i + 1; j < arraySize; j++) {
            if (score[j] > biggestScore) {
                biggestScore = score[j]; //updates to check in next loop
                biggestScoreIndex = j; // keep tracks of position
            }
        }

        //updates score array
        score[biggestScoreIndex] = score[i];
        score[i] = biggestScore;

        // also update name array
        tempVar = name[biggestScoreIndex];
        name[biggestScoreIndex] = name[i];
        name[i] = tempVar;
    }   
}

/* This function creates a new output file with updated name
And writes the updated arrays into the file*/
string writeArrays(string name[], int score[], int arraySize, string fileName) {
    ofstream outFile;
    //initializing var
    string newLine;

    fileName[0] = toupper(fileName.at(0)); // updates name with upperCase
    string newOutFileName = "sorted" + fileName;

    outFile.open(newOutFileName); // open new file

    if (!outFile.is_open()) { //check that file is open
        cout << "File \"" << fileName << "\" could not be opened!" << endl;
        exit (EXIT_FAILURE); 
    }

    for (int i = 0; i < arraySize; i++) {
        outFile << name[i] << "; " << score[i] << endl;
    }
    return newOutFileName;
}

/* This function displays num of students and class average
and also prints the new output file name*/
void displayCalcs(string outFile, int numOfStudents, double classAve) {
    cout << "Sorted data has been saved to \"" << outFile << "\"" << endl;  //informs new output file name
    cout << numOfStudents << " students took the final exam." << endl; //display num of students
    cout << fixed << setprecision(2) << classAve << " is the class average."  << endl; // display class average with two decimal digits
}
