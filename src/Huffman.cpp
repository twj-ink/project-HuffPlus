#pragma once
#include "Huffman.h"
#include <bitset>
#include <sstream> // std::stringstream
#include <iostream>

void HuffmanCompressor::compress(std::istream& in, std::ostream& out) {
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string data = buffer.str();

    buildTree(data);

    std::string encoded;
    for (unsigned char c : data) {
        encoded += codeMap[c];
    }

    // 输出：原始长度，编码串
    out << data.size() << "\n";
    out << encoded << "\n";
}

void HuffmanCompressor::decompress(std::istream& in, std::ostream& out) {
    size_t originalSize;
    std::string encoded;;
    in >> originalSize;
    in >> encoded;

    std::string decoded;
    std::string cur;
    for (char bit : encoded) {
        cur.push_back(bit);
        if (decodeMap.count(cur)) {
            decoded.push_back(decodeMap[cur]);
            cur.clear();
        }
    }

    // 输出：原字符串
    out << decoded;
}

// 使用优先队列构建哈夫曼树
void buildTree(const std::string& data) {

}

void buildCodes(HuffmanNode* node, const std::string& prefix) {
}