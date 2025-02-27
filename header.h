#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>
#include <fstream>

using namespace std;

#define CAPACITY 100000

vector<pair<char, int> > frequencyTable(const string& input);

struct Node {
    char data;
    int freq;
    shared_ptr<Node> left, right;

    Node(char c, int f) : data(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) {
        return lhs->freq > rhs->freq;
    }
};

shared_ptr<Node> createHuffmanTree(const vector<pair<char, int> >& sortedFreq);

void makeHuffmanCodes(shared_ptr<Node>& root, vector<bool>& code);

unordered_map<char, vector<bool> > huffmanCodes;

#endif // HEADER_H
