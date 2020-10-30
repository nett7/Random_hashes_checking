#include <iostream>
#include <random>
#include <string>
#include <map>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <utility>

using namespace std;

class Work {
public:
    Work(string path_) : path(std::move(path_)), answers(COUNT_OF_HASHES) {};

    void generate_hashes();

    void print_generated_hashes(ostream &stream = cout);

    void print_generated_passwords(ostream &stream = cout);

    void read_answers();

    void read_hashes_passwords();

    pair<int, int> checking_answers();


private:
    const string LETTERS = "asdfghjkl:;zxcv";
    const size_t COUNT_OF_HASHES = 100;
    const size_t PASSWORDS_LEN = 8;
    const string path;

    vector<string> answers;
    map<string, string> generated_passwords_hashes;
};

string sha256(const string str);


void Work::generate_hashes() {

    std::random_device dev;
    std::mt19937 rng(1);
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, LETTERS.size() - 1);

    stringstream stream;
    for (int i = 0; i < COUNT_OF_HASHES; i++) {
        string current_word;
        current_word.reserve(8);
        for (int j = 0; j < PASSWORDS_LEN; j++) {
            current_word += LETTERS[dist(rng)];
        }
        generated_passwords_hashes[current_word] = sha256(current_word);
    }
}

void Work::read_answers() {
    ifstream file;
    file.open(path+"/answers.txt");
    if (file.is_open()) {
        for (auto &i: answers) {
            std::getline(file, i);
        }
        file.close();
    }
}

pair<int, int> Work::checking_answers() {
    int right_count = 0;
    int k = 0;
    for (const auto &gener_answer : generated_passwords_hashes) {
        cout << answers[k] <<" "<<gener_answer.first<<endl;
        if (gener_answer.first == answers[k++]) {
            right_count++;
        }
    }
    return make_pair(right_count, COUNT_OF_HASHES - right_count);
}

void Work::print_generated_hashes(ostream &stream) {
    for (const auto &i : generated_passwords_hashes) {
        stream << i.second << "\n";
    }
}

void Work::print_generated_passwords(ostream &stream) {
    for (const auto&[first, second] : generated_passwords_hashes) {
        stream << first << "\n";
    }
}

void Work::read_hashes_passwords() {
ifstream file1, file2;
    file2.open(path +"/hashes.txt");
    file1.open(path +"/generated_passwords.txt");
    string s1, s2;
    while (file1>>s1 && file2>>s2){
        generated_passwords_hashes[move(s1)] = move(s2);
    }
    file1.close();
    file2.close();
}

string sha256(const string str) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int) hash[i];
    }
    return ss.str();
}


int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Usage:\n" << argv[0] <<" + \n"
                  "1: -g: to generate hashes and save it to file hashes.txt\n"
                  "2: -c + $pwd: to check founded passwords with generated\n " << std::endl;
        return 1;
    } else if (argc == 3 && strcmp(argv[1],"-g") == 0) {
        string path = argv[2];
        Work w(path);
        w.generate_hashes();

        ofstream file1, file2;
        file1.open(path +"/hashes.txt");
        file2.open(path +"/generated_passwords.txt");
        w.print_generated_hashes(file1);
        w.print_generated_passwords(file2);

        file1.close();
        file2.close();

        return 0;
    } else if (argc == 3 && strcmp(argv[1],"-c") == 0) {
        string path = argv[2];

        Work w(path);
        w.read_hashes_passwords();
        w.read_answers();
        cout << w.checking_answers().first << " passwords decrypted\n";
    } else {
        cerr<<"Wrong usage\n"<<argc;
    }
}