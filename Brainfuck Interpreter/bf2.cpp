#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <system_error>
#include <vector>
#include <array>
#include <cstdio>
#include <cstring>
#include <cassert>

#define ERROR "\x1b[38;2;255;0;0m"
#define WHITE "\x1b[38;2;255;255;255m"
#define WARNING "\x1b[38;2;255;255;0m"
#define RESET "\x1b[0m"
#define SALMON "\x1b[38;2;255;128;114m"
#define BLUE "\x1b[38;2;114;128;255m"
#define CLR "\033c"
#define SIZE 30000

#define LEN(x) ({   __typeof__(x) _x = (x);\
                    int val = 0;\
                    while (_x != 0) _x/=10, ++val;\
                    val;  \
                })

static unsigned char tape[SIZE] = {}; 
int idx;

using namespace std;

void print_line(string str, int ln, int pos) {
    int width = LEN(ln);
    cout << "  "<< ln << " | " << str.substr(0, pos-1) << SALMON 
    << str[pos-1] << RESET << str.substr(pos) << endl;

    cout << "  ";
    while (width-- > 0) cout << ' ';
    cout << " | ";
    while (--pos > 0) cout << ' ';
    cout << SALMON << '^' << RESET << endl;
}

void print_err(string white, string msg, string err="error: ") {
    cerr << WHITE << white << ERROR << err << RESET << msg;
}

void err1(int ln, int pos, string file="file") {
    print_err("\n\x1b[1mat "+file+":"+to_string(ln)+":"+to_string(pos)+": ", 
        "expected '[' before ']' token\n");
}

void err2(int ln, int pos, string file="file") {
    print_err(string("\n\x1b[1mat "+file+":")+to_string(ln)+":"+to_string(pos)+": ", 
        "expected ']' before end of file\n");
}

void print_warning(string msg) {  
    cerr << endl << WARNING << "Warning: " << RESET << msg << endl;
}

bool pseudo_compile(ifstream& src) {
    char c = 0;
    int count = 0, ln = 1;
    string str;

    while (src.get(c)) {
        str += c;

        if (c == '[') {
            ++count;
        }
        else if (c == ']') {
            if (!count) {
                err1(ln, str.size());
                print_line(str, ln, str.size());
                return false; 
            }            
            --count;
        }
        else if (c == '\n') {
            str.clear(), ++ln;
        }
    }

    if (count) {
        err2(ln, str.size());
        print_line(str+" ", ln, str.size()+1);
        return false;
    }

    return true;
}

void begin(ifstream& src, istream& in, bool dfs=false) {
    char c;
    while (src.get(c)) {
        switch (c) {
            case '>' :
                ++idx;
                if (idx == SIZE) 
                    idx = 0;
                break;
            case '<' :
                if (!idx) 
                    idx = SIZE;
                --idx;
                break;
            case '+':
                ++tape[idx];
                break;
            case '-':
                --tape[idx];
                break;
            case '.': 
                cout << tape[idx]; //change to use compile switch
                break;                
            case ',':
                //if (in.rdbuf() == std::cin.rdbuf()) cout << "> "; //if I use a buffer
                if (in.eof()) tape[idx] = 0; //for cat
                else in.get((char&)tape[idx]);
                break;
            case '[':
            {
                if (!tape[idx]) {
                    char c; int count = 1;
                    while(count) {
                        src.get(c);
                        if (c == '[') ++count;
                        else if (c == ']') --count;
                    }
                }                
            }
            break;
            case ']':
                if (!tape[idx]) continue; 
                char c; int count = -1;
                src.unget();

                do {
                    src.unget();
                    if (!src) {cout << src.rdstate() << endl; exit(-1);} 
                    c = src.peek();
                    if (c == '[') ++count;
                    else if (c == ']') --count;
                } while(count);
                src.get();
        }
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        print_err(string(argv[0])+": ", "no source code present\n", "fatal error: ");
        cerr << "program terminated" << endl;
        return -1;
    }

    ifstream src {argv[1]};
    if (!src.is_open()) {
        print_err(string(argv[0])+": ", "");
        perror(argv[1]);
        return -2;
    }

    idx = 0;
    if (pseudo_compile(src, true)) { //default should be false
        src.clear();
        src.seekg(0);
        cout << CLR;
    }else return -1;

    int i = 2; 
    istream* in = &std::cin;
    ifstream _in;
    bool flag = 1;
    while (i < argc) {
        if (argv[i][0] != '-') { 
            _in.open(argv[i]);           
            if (_in) {
                //ios_base::sync_with_stdio(false);
                std::cin.tie(0);
                in = dynamic_cast<istream*>(&_in);
                flag = 0;
                break;
            } else {
                string str = "problem opening \""+string(WHITE)+string(argv[i])+"\". "+string(RESET)+
                    "Input will be read from console instead";
                print_warning(str);
                perror("");
            }
        }
        ++i;
    }

    if (flag) 
        cout << "Type CTRL-'d'(Linux ) or CTRL - 'z' (Windows & Unix) to exit if done" << endl;
    memset(tape, 0, sizeof(tape));
    cout << "**Unget version**\n";
    begin(src, *in);

    FILE *fp = fopen("log.txt", "w");
    for (int i = 0; i < SIZE; ++i) {
        fprintf(fp, "%d ", tape[i]);
    }
    fclose(fp);
    cout << endl;
    return 0;
}

//->+>+<<[-[->>[->+>+<<]<[->>+<<]>>[-<+>]>[-<<<+>>>]<<<<]]>>. fibonacci