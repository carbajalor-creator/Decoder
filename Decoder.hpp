//
// Created by gabri on 10/30/2025.
//

#ifndef DECODER_HPP
#define DECODER_HPP

#include <regex>
#include <string>


struct TreeNode {
    std::string word;
    TreeNode* current;
    TreeNode* left;
    TreeNode* right;
};

class Decoder {
    public:
    Decoder();
    ~Decoder();

    TreeNode* buildFromHeader(std::vector<std::pair<std::string, std::string>> &pairs);
    void treeInsert(TreeNode*& root, const std::string& word, const std::string& code);

    std::vector<std::pair<std::string, std::string>> headerVector(std::istream &hdr_stream);
    
    std::string readCodes(std::istream& code_stream);

    std::vector<std::string> decoding(const std::string& bits, const TreeNode* root);

    std::string makeOutputFilename(const std::string &inputFilename);

    void writeToOutputFile(std::ostream& out_stream, const std::vector<std::string>& tokens);

    private:
    bool isLeaf(const TreeNode* node);
    void destroyTree(TreeNode* root);
    TreeNode* root_;


};
#endif //DECODER_HPP
