//
// Created by gabri on 10/30/2025.
//
#include "Decoder.hpp"

#include <ios>
#include <vector>
#include <utility>
#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

Decoder::Decoder() : root_(nullptr) {}

Decoder::~Decoder() {
    destroyTree(root_);
}

void Decoder::destroyTree(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    destroyTree(root->left);
    destroyTree(root->right);
    delete root;
}

std::vector<std::pair<std::string, std::string>> Decoder::headerVector(std::istream &hdr_stream) {
    std::vector<std::pair<std::string, std::string>> hdrVector;
    if (hdr_stream) {
        std::string line;
        while (std::getline(hdr_stream, line)) { //loop to iterate through input file
            std::istringstream lineStream(line);
            std::string word;
            std::string code;

            if (lineStream >> word >> code) { //separating line into word and code variables
                hdrVector.emplace_back(word, code); //adding pair to vector
            }
        }
    }
    return hdrVector;
}

TreeNode *Decoder::buildFromHeader(std::vector<std::pair<std::string, std::string>> &pairs) {
    root_ = nullptr;
    for (auto &pair : pairs) {
        std::string word = pair.first; //assigning variable to word
        std::string code = pair.second; //assigning variable to code
        treeInsert(root_, word, code); //calling insert function
    }
    return root_;
}

void Decoder::treeInsert(TreeNode*& root, const std::string& word, const std::string& code) {
    if (root == nullptr) {
        root = new TreeNode(); //creating root node
    }
    TreeNode* current = root; //setting current to root
    for (const char i : code) { //loop to iterate through code
        if (i == '0') { //checking if character at i is 0
            if (current->left == nullptr) {
                current->left = new TreeNode(); //if left is null create new node
            }
            current = current->left; //traverse left
        }
        else if (i == '1') { //checking if character at i is 1
            if (current->right == nullptr) {
                current->right = new TreeNode(); //if right is null create new node
            }
            current = current->right; //traverse right
        }
    }
    current->word = word; //once reached end of code assign word to current node
}

std::string Decoder::readCodes(std::istream &code_stream) {
    //read bits from stream
    std::string line;
    std::string bits;

    while (std::getline(code_stream, line)) { //loop that iterates through input file
        for (const char i : line) { //loop that iterates through line in input file
            if (i == '0' || i == '1') { //if line at i is a 0 or a 1 added to bits string
                bits += i;
            }
        }
    }
    //std::cout << bits << std::endl;
    return bits; //returns string
}

bool Decoder::isLeaf(const TreeNode* node) {
    if (node == nullptr) { //if root is null then
        return false;
    }
    if (node->left == nullptr && node->right == nullptr) { //checks if left and right subtree are null if so true
        return true;
    }
    return false;
}

std::vector<std::string> Decoder::decoding(const std::string &bits, const TreeNode* root) {
    //traverse the tree with the bits from readCodes
    std::vector<std::string> result;
    const TreeNode *current = root;

    for (const char bit : bits) { //loops through bits string
        /*
        if (isLeaf(current)) { //checking if current node is a leaf
            result.push_back(current->word); //if so word is added to decoded result vector
            current = root; //current is set back to root of huffman tree
        } */
        if (bit == '0') { //checking if bits at i is a 0
            current = current->left; //if so traverse left
        }
        else if (bit == '1') { //checking if bits at i is a 1
            current = current->right; //if so traverse right
        }
        if (current == nullptr) {
            std::cerr << "Error: Bitstream ended while traversal was at internal node \n";
            exit(1);
        }
        if (isLeaf(current)) {
            result.push_back(current->word);
            current = root;
        }
    }
    return result;
}

std::string Decoder::makeOutputFilename(const std::string& inputFilename) {
    fs::path inputPath(inputFilename);
    return inputPath.stem().string() + ".tokens_decoded";
}

void Decoder::writeToOutputFile(std::ostream &out_stream, const std::vector<std::string> &decodedWords) {
    for (const auto & decodedWord : decodedWords) {
        out_stream << decodedWord << "\n"; //prints one word per line
    }
}



