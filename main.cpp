#include "header.h"

vector<pair<char, int>> frequencyTable(const string& input) {
    unordered_map<char, int> freq;
    for (char c : input) {
        freq[c]++;
    }
    vector<pair<char, int>> sorted_freq(freq.begin(), freq.end());
    sort(sorted_freq.begin(), sorted_freq.end(), [](const pair<char, int>& p1, const pair<char, int>& p2) {
        return p1.second > p2.second;
    });
    return sorted_freq;
}

shared_ptr<Node> createHuffmanTree(const vectr<pair<car,int>>& sortedFreq) {
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> pq;

    for (const auto& pair: sortedFreq) {
        pq.push(make_shared<Node>(pair.first, pair.second));
    }
    while (!pq.empty()) {
        shared_ptr<Node> left = pq.top(); pq.pop();
        shared_ptr<Node> right = pq.top(); pq.pop();

        shared_ptr<Node> newNode = make_shared<Node>('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

int main() {
    const string input = "alala";
    vector<pair<char, int>> freq = frequencyTable(input);
    for (const auto& pair : freq) {
        cout << pair.first << " " << pair.second << endl;
    }
    return 0;
}
