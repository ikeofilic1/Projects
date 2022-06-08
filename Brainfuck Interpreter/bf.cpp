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
#define SIZE 40000

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

bool pseudo_compile(vector<unsigned char>& vec) {
    char c;
    int count = 0, ln = 1, sz = vec.size(), i = 0;
    string str;

    while (i < sz) {
        c = vec[i++];
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

void begin(vector<unsigned char>& src, istream& in) {
    int ptr = 0, sz = src.size();
    char c;
    while (ptr < sz) {
        c = src[ptr++];
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
                        c = src[ptr++];
                        if (c == '[') ++count;
                        else if (c == ']') --count;
                    }
                }                
            }
            break;
            case ']':
                if (!tape[idx]) continue; 
                char c; int count = -1;

                do {
                    --ptr;
                    c = src[ptr-1];
                    if (c == '[') ++count;
                    else if (c == ']') --count;
                } while(count);                
        }
    }
}

void begin2(vector<unsigned char>& src, istream& in) {
    int ptr = 0, sz = src.size();
    char c;
    vector<int> st(sz>>2);
    while (ptr < sz) {
        c = src[ptr++];
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
                        c = src[ptr++];
                        if (c == '[') ++count;
                        else if (c == ']') --count;
                    }
                }
                else st.push_back(ptr);               
            }
            break;
            case ']':
                if (tape[idx]) ptr = st.back(); 
                else st.pop_back();                             
        }
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        print_err(string(argv[0])+": ", "no source code present\n", "fatal error: ");
        cerr << "program terminated" << endl;
        return -1;
    }

    vector<unsigned char> v;    
    ifstream src{argv[1], ios::ate};
    if (src) {
        streamoff end = src.tellg();
        src.seekg(0);
        streamoff sz = end - src.tellg();
        char buf[sz];
        src.read(buf, sz);
        v.assign(buf, buf+sz);
    }
    else {
        print_err(string(argv[1])+": ", "");
        perror(argv[1]);
        return -2;
    }

    idx = 0;
    if (!pseudo_compile(v)) return -1;

    istream* in = &std::cin;
    ifstream _in;
    if (argc > 2) { 
        _in.open(argv[2]);           
        if (_in) {
            std::cin.tie(0);
            in = dynamic_cast<istream*>(&_in);
        } else {
            print_warning("problem opening \""+string(WHITE)+string(argv[2])+"\". "+string(RESET)+
                "Input will be read from console instead");
            perror("");
        }
    }


    if (in == &cin) 
        cout << "Type CTRL-'d'(Linux ) or CTRL - 'z' (Windows & Unix) to exit if done" << endl;
    memset(tape, 0, sizeof(tape));
    // cout << "**Unget version - vector**\n";
    // begin(v, *in);

    cout << "**Stack version - vector**\n";
    begin2(v, *in);
    /*FILE *fp = fopen("log.txt", "w");
    for (int i = 0; i < SIZE; ++i) {
        fprintf(fp, "%03d ", tape[i]);
    }
    fclose(fp);*/
    cout << endl;
    return 0;
}

//->+>+<<[-[->>[->+>+<<]<[->>+<<]>>[-<+>]>[-<<<+>>>]<<<<]]>>. fibonacci