//
// Created by Ali Kooshesh on 9/27/25.
//

#include "Scanner.hpp"

#include <utility>
#include <iostream>
#include <fstream>

#include "utils.hpp"

Scanner::Scanner(std::filesystem::path inputPath) {
    inputPath_ = std::move(inputPath);
}


//makes a char unsigned to prevent negative ascii values and lowers the char
//in order to read easier
bool isLetter(char& c) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return c >= 'a' && c <= 'z' ;
}

std::string Scanner::readWord(std::istream &in) {
    std::string token;
    char c;
    //read until you get a first valid letter
    while (in.get(c)) {
        if (isLetter(c)){
            token += c;
            break;
        }
    }
    //if the string is empty after the first check then return the str its not valid
    if (token.empty())
        return token;

    //read the rest of the word
    while (in.get(c)) {
        if (isLetter(c)) {
            token += c;
        }
        //check if theres an aposterphie
        else if (c == '\'') {
            //look at the next position to check if its a valid letter
            if (in.peek() == EOF)
                break;
            //if the letter is valid add it
            char next = static_cast<char>(in.peek());
            if (isLetter(next)) {
                token += c;
                continue;
            }
            break;
        }
        else {
            break;
        }

    }
    //return the final word
    return token;
}

error_type Scanner::tokenize(std::vector<std::string>& words) {
    namespace fs = std::filesystem;
    if (inputPath_.has_parent_path()) {
        if (!exists(inputPath_.parent_path()))
            return DIR_NOT_FOUND;
    }
    if (!exists(inputPath_))
        return FILE_NOT_FOUND;

    std::ifstream inFS(inputPath_);
    if (!inFS.is_open())
        return UNABLE_TO_OPEN_FILE;
    while (inFS) {
        std::string w = readWord(inFS);
        if (w.empty())
            break;
        words.push_back(w);
    }

    return NO_ERROR;
}


error_type Scanner::tokenize(std::vector<std::string> &words, const std::filesystem::path &outputFile) {
    error_type rt = tokenize(words);
    if (rt != NO_ERROR)
        return rt;
    std::ofstream oFS(outputFile);
    if (!oFS.is_open())
        return UNABLE_TO_OPEN_FILE_FOR_WRITING;

    for (const auto & word : words) {
        oFS << word << '\n';
        if (!oFS) {
            return FAILED_TO_WRITE_FILE;
        }
    }


    return NO_ERROR;
}
