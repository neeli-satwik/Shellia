#include <bits/stdc++.h>
using namespace std;

bool tokenize(int& start, const string& line, vector<string>& tokens, bool& hitPipe) {
    bool isSingle = false, isDouble = false, tokenActive = false;
    string curr;
    int n = (int)line.length();
    hitPipe = false;

    int i;
    for (i = start; i < n; i++) {
        char c = line[i];

        if (c == '|' && !isSingle && !isDouble) { hitPipe = true; break; }

        if (!isSingle && !isDouble && isspace((unsigned char)c)) {
            if (tokenActive) {
                tokens.push_back(curr);
                curr.clear();
                tokenActive = false;
            }
            continue;
        }

        tokenActive = true;

        if (c == '\'' && !isDouble) { isSingle = !isSingle; continue; }
        if (c == '"'  && !isSingle) { isDouble = !isDouble; continue; }

        if (isDouble && c == '\\') {
            if (i + 1 >= n) return false;
            curr += line[++i];
            continue;
        }

        if (!isSingle && !isDouble && c == '\\') {
            if (i + 1 < n) curr += line[++i];
            continue;
        }

        curr += c;
    }

    if (isSingle || isDouble) return false;
    if (tokenActive) tokens.push_back(curr);

    start = hitPipe ? i + 1 : i;
    return true;
}

bool retrieveCommands(const string& line, vector<vector<string>>& commands) {
    int index = 0, n = (int)line.size();
    bool afterPipe = false;

    while (index < n) {
        vector<string> tokens;
        bool hitPipe = false;
        if (!tokenize(index, line, tokens, hitPipe)) return false;

        if (tokens.empty()) {
            if (!hitPipe && !afterPipe && commands.empty()) break; // blank line, no commands at all
            return false; // empty command: leading "|", "a||b", etc.
        }

        commands.push_back(tokens);
        afterPipe = hitPipe;
    }

    if (afterPipe) return false; // trailing "|" with nothing after it
    return true;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (line.empty()) continue;
        vector<vector<string>> commands;
        if (!retrieveCommands(line, commands)) {
            cout << "ERR syntax error: empty command in pipeline\n";
            continue;
        }
        for (size_t i = 0; i < commands.size(); i++) {
            for (size_t j = 0; j < commands[i].size(); j++) {
                if (j) cout << ' ';
                cout << commands[i][j];
            }
            if(i<commands.size()-1) cout << " | ";
        }
        cout << "\n";
    }
}