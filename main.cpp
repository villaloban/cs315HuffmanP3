#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <iomanip>

#include "BinSearchTree.hpp"
#include "PriorityQueue.hpp"
#include "Scanner.hpp"
#include "utils.hpp"
#include "HuffmanTree.hpp"



int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = "input_output";
    const std::string inputFileName = std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);
    const std::string inputFilePath = dirName + "/" + inputFileName;

    // build the path to the .tokens output file.
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";
    const std::string wordFreqFileName = dirName + "/" + inputFileBaseName + ".freq";


    // The next several if-statement make sure that the input file, the directory exist
    // and that the output file is writeable.
     if( error_type status; (status = regularFileExistsAndIsAvailable(inputFilePath)) != NO_ERROR )
        exitOnError(status, inputFilePath);


    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR )
        exitOnError(status, dirName);

    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);


    std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName); // create a file system path using the output file.

    auto fileToWords = Scanner(inputFilePath);
    if( error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
	    exitOnError(status, inputFilePath);

    if (error_type status; (status = writeVectorToFile(wordTokensFileName, words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    BinSearchTree bst;
    bst.bulkInsert(words);

    std::vector<std::pair<std::string, int >> wordCounts;
    bst.inorderCollect(wordCounts);

    int totalTokens = static_cast<int> (words.size());
    int uniqueWords = static_cast<int>(wordCounts.size());
    unsigned height = bst.height();
    int minfreq = 0;
    int maxfreq = 0;

    if (uniqueWords > 0) {
        minfreq = wordCounts.at(0).second;
        maxfreq = wordCounts.at(0).second;
        for (auto & wordCount : wordCounts) {
            if (wordCount.second < minfreq)
                minfreq = wordCount.second;
            if (wordCount.second > maxfreq)
                maxfreq = wordCount.second;
        }
    }

    std::cout << "BST height: " << height << "\n";
    std::cout << "BST unique words: " << uniqueWords << "\n";
    std::cout << "Total tokens: " << totalTokens << "\n";
    std::cout << "Min frequency: " << minfreq << "\n";
    std::cout << "Max frequency: " << maxfreq << "\n";

    std::vector<TreeNode*> nodes;
    for (auto & wordCount : wordCounts) {
        TreeNode* node = new  TreeNode(wordCount.first);
        node->setCount(wordCount.second);
        nodes.push_back(node);
    }
    PriorityQueue priority_queue(nodes);

    std::ofstream out(wordFreqFileName);
    if (!out.is_open())
        std::cout << "Error writing to " << wordFreqFileName << "\n";

    const std::vector<TreeNode*>& sortedItems = priority_queue.items();
    for (auto node : sortedItems) {
        out << std::setw(10) << node->getCount() << " " << node->value() << "\n";
    }

    out.close();

    const std::string HeaderfileName = dirName + "/" + inputFileBaseName + ".hdr";
    const std::string EncodedFileName = dirName + "/" + inputFileBaseName + ".code";

    HuffmanTree huffTree = HuffmanTree::buildFromCounts(wordCounts);

    std::ofstream hdrOut(HeaderfileName);
    if (!hdrOut.is_open())
        std::cout << "Error writing to " << HeaderfileName << "\n";

    huffTree.writeHeader(hdrOut);
    hdrOut.close();

    std::ofstream endcodeOut(EncodedFileName);
    if (!endcodeOut.is_open())
        std::cout << "Errror writing to " << EncodedFileName << "\n";

    huffTree.encode(words, endcodeOut);
    endcodeOut.close();


    return 0;
}
