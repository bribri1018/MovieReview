#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>

//string::npos
void test(std::string k);
int prompt();
int option1();
int option2();
int option3();
int exit();

using namespace std;

int main() {
    int k = 1;
    while(1) {
        k = prompt();
        if (!k) {
            return 0;
        }
    }

    string a = "My name is Brian";
    cout << a.find("Z") << "\n";
    cout << "\n";

    test("this is a test\n");
    return 0;
}

int prompt() {
    cout << "What woudl you like to do" << endl;
    cout << "1: Enter word" << endl << "2: Avg score" << endl;
    cout << "3: Pos and Neg word" << endl << "4: End" <<endl;
    int option;
    cin >> option;
    switch (option) {
        case 1: return option1();
        case 2: return option2();
        case 3: return option3();
        case 4: return exit();
    }
}

// Prompt for word, and then print count and score
int option1(){
    string target;
    cout << "You chose option 1" << endl;
    cout << "What word should I check?" << endl;
    cin >> target;

    ifstream fin("movieReviews.txt");
    string line;
    int count = 0;
    float total_score = 0;
    // variable to avoid double counting
    bool already_added = false;
    while (getline(fin, line)) {
        istringstream is(line);
        string temp_word;
        int score = 0;
        is >> score;
        while (!is.eof()) {
            is >> temp_word;
            if ((temp_word == target) and !already_added) {
                total_score += score;
                count++;
                already_added = true;
            }
        }
        // reset score and already_added
        score = 0;
        already_added = false;
    }
    fin.close();
    cout << target << " appears " << count << " times." << endl;
    cout << "The average score is " <<total_score/count;

    cout << endl << endl;
    return 1;
}

// Prompt for file, then print average score and sentiment
int option2() {
    cout << "You chose option 2" << endl;

    cout << endl << endl;    
    return 1;
}

// Prompt for file, then print mose negative and most positive word
int option3() {
    cout << "You chose option 3" << endl;

    cout << endl << endl;
    return 1;
}

void test(std::string k) {
    cout << k;
}

int exit() {
    std::cout << "Bye..." << std::endl << std::endl;
    return 0;
}