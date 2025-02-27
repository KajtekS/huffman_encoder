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

shared_ptr<Node> createHuffmanTree(const vector<pair<char, int>>& sortedFreq) {
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> pq;

    for (const auto& pair : sortedFreq) {
        pq.push(make_shared<Node>(pair.first, pair.second));
    }
    while (pq.size() > 1) {
        shared_ptr<Node> left = pq.top(); pq.pop();
        shared_ptr<Node> right = pq.top(); pq.pop();

        shared_ptr<Node> newNode = make_shared<Node>('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    return pq.top();
}

void makeHuffmanCodes(shared_ptr<Node>& root, vector<bool>& code) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    code.push_back(1);
    makeHuffmanCodes(root->right, code);
    code.pop_back();

    code.push_back(0);
    makeHuffmanCodes(root->left, code);
    code.pop_back();
}

int main() {
    string input = "";
    vector<bool> code;
    fstream f, temp;

    f.open("output.bin", ios::binary | ios::out);
    temp.open("temp.txt", ios::out); // Otwieramy temp do zapisu

    char znak;
    int i = 0;
    while (cin.get(znak)) {
        if (i >= CAPACITY) break;
        temp.put(znak);
        input += znak;
        i++;
    }

    temp.close();
    temp.open("temp.txt", ios::in);

    vector<pair<char, int>> freq = frequencyTable(input);
    shared_ptr<Node> root = createHuffmanTree(freq);
    makeHuffmanCodes(root, code);

    unsigned char byte = 0;
    int bitCount = 0;

    while (temp.get(znak)) {
        const vector<bool>& huffmanCode = huffmanCodes[znak];
        for (bool bit : huffmanCode) {
            byte = (byte << 1) | bit;
            bitCount++;

            if (bitCount == 8) {
                f.put(byte);
                byte = 0;
                bitCount = 0;
            }
        }
    }

    if (bitCount > 0) {
        byte <<= (8 - bitCount);
        f.put(byte);
    }

    temp.close();
    f.close();

    return 0;
}
