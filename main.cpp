#include <bits/stdc++.h>
using namespace std;

// TODO (tokenize): implement per the lesson description.

bool tokenize(string& line, vector<string>& tokens) {
    bool isSingle = false, isDouble = false, tokenActive = false;
    string curr;
    int n = line.length();

    for(int i=0;i<n;i++) {
        char c = line[i];

        if(!isSingle && !isDouble && tokenActive && isspace((unsigned char)c)) { //a complete valid token has been generated.
            tokens.push_back(curr);
            curr.clear();
            tokenActive = false;
            continue;
        }

        if(!isSingle && !isDouble && isspace((unsigned char)c)) continue; //all single spaces that come between tokens are supposed to be treated as a single whitespace.
        
        tokenActive = true;

        if (c == '\'' && !isDouble) { isSingle = !isSingle; continue; }
        if (c == '"'  && !isSingle) { isDouble = !isDouble; continue; }

        if(isDouble) {
            if(c=='\\' && i+1>=n) return false;
            if(c=='\\') {curr += line[++i]; continue;} 
        }

        if (!isSingle && c == '\\') {
            if (i + 1 < line.size()) curr += line[++i]; // trailing backslash with no quote open: keep it simple, drop it
            continue;
        }

        curr += c;
    }

    if(isSingle || isDouble) return false;
    if(tokenActive) tokens.push_back(curr);
    return true;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        vector<string> tokens;
        if(!tokenize(line, tokens)) {
            cout<<"ERR unterminated quote\n";
            continue;
        }
        for (size_t i = 0; i < tokens.size(); i++) {
            if (i) cout << ' ';
            cout << '[' << tokens[i] << ']';
        }
        cout << "\n";
    }    
}