
#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "Decoder.hpp"
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    if (argc != 3) { //checking there are only 2 command line arguments
        std::cerr << "Usage: " << argv[0] << " header_file code_file" << std::endl;
        return 1;
    }
    std::string headerFilename = argv[1];
    std::string codeFilename = argv[2];

    //checking header file errors
    std::ifstream hdr_stream(headerFilename);
    if (!hdr_stream.is_open()) { //checking if header file can be opened
        std::cerr << "Could not open header file " << headerFilename << std::endl;
        return 1;
    }
    char first;
    while (hdr_stream >> std::noskipws >> first) {
        if (std::isalpha(first)) {
            break;
        }
        else {
            std::cerr << "Error: Header file must start with a letter" << std::endl;
            return 1;
        }
    }
    hdr_stream.clear();
    hdr_stream.seekg(0);

    //checking code file errors
    std::ifstream code_stream(codeFilename);
    if (!code_stream.is_open()) { //checking if code file can be opened
        std::cerr << "Could not open code file " << codeFilename << std::endl;
        return 1;
    }
    char firstBit;
    while (code_stream >> std::noskipws >> firstBit) {
        if (firstBit == '0' || firstBit == '1') {
            break;
        }
        else {
            std::cerr << "Error: Code file must start with a 0 or 1" << std::endl;
        }
    }
    code_stream.clear();
    code_stream.seekg(0);

    //create output file
    std::string outputFilename = fs::path(codeFilename).stem().string() + ".tokens_decoded";
    std::ofstream output_stream(outputFilename);
    if (!output_stream.is_open()) {
        std::cerr << "Could not create output file " << outputFilename << std::endl;
        return 1;
    }

    //decoder stuff
    Decoder decoder;
    auto headerPairs = decoder.headerVector(hdr_stream);
    TreeNode* root = decoder.buildFromHeader(headerPairs);
    std::string bits = decoder.readCodes(code_stream);
    auto decodedWords = decoder.decoding(bits, root);

    //writing to output file
    decoder.writeToOutputFile(output_stream, decodedWords);


    //checks if input files exist
    //checks if output file can be written to
    //calls function to read header file
    //constructs an instance of the decoder Huffman tree using vector
    return 0;
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.