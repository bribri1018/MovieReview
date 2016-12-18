#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <map>
#include <set>

//string::npos
void test(std::string k);
int prompt();
int option1();
int option2(int option);
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
        case 2: return option2(0);
        case 3: return option3();
        case 4: return exit();
    }
}

// Prompt for word, and then print count and score
int option1() {
    string target;
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
int option2(int option) {
    set<string> targets;
    map<string, float> target_score;
    map<string, float> target_count;
    cout << "Give me the filename" << endl;
    string filename;
    cin >> filename;

    ifstream target_file(filename.c_str());
    string target;
    while (target_file) {
        target_file >> target;
        targets.insert(target);
        target_score[target] = 0;
        target_count[target] = 0;
    }
    target_file.close();
    int num_words = targets.size();
    ifstream fin("movieReviews.txt");
    string line;
    // variable to avoid double counting
    bool already_added = false;
    while (getline(fin, line)) {
        istringstream is(line);
        string temp_word;
        int score = 0;
        is >> score;
        while (!is.eof()) {
            is >> temp_word;
            if ((targets.find(temp_word) != targets.end()) and 
                !already_added) {
                target_count[temp_word] += 1;
                target_score[temp_word] += score;
                already_added = true;
            }
        }
        already_added = false;
    }
    fin.close();

    float file_score = 0;
    string pos_word;
    string neg_word;
    float pos_score = 0;
    float neg_score = 4;
    float temp_score;
    for (string str : targets) {
        temp_score = target_score[str] / target_count[str];
        if (temp_score > pos_score) {
            pos_score = temp_score;
            pos_word = str;
        }
        if (temp_score < neg_score) {
            neg_score = temp_score;
            neg_word = str;
        }
        file_score += temp_score;
    }
    file_score = file_score/num_words;

    if (option == 1) {
        cout << "Most positive word is: " << pos_word << " with score " << pos_score << endl;
        cout << "Most negative word is: " << neg_word << " with score " << neg_score << endl;
        return 1;
    }

    string sentiment = "positive";
    if (file_score < 2) {
        sentiment = "negative";
    }
    cout << "The avg score of " << filename << " is " << file_score << endl;
    cout << "Overall sentiment is " << sentiment << endl;

    cout << endl << endl;
    return 1;
}

// Prompt for file, then print mose negative and most positive word
int option3() {
    return option2(1);
}

int exit() {
    std::cout << "Bye..." << std::endl << std::endl;
    return 0;
}