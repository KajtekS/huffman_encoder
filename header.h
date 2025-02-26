// Created by Kajetan Serweciński on 25/02/2025.

#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

vector<pair<char, int>> frequencyTable(const string& input);

struct Node {
    char data;
    int freq;
    shared_ptr<Node>left, right;

    Node(char c, int f) : data(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(const shared_ptr<Node>& lhs, const shared_ptr<Node>& rhs) {
        return lhs -> freq > rhs -> freq;
    }
};

shared_ptr<Node> createHuffmanTree(const vectr<pair<car,int>>& sortedFreq);

#endif // HEADER_H
