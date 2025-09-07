#include "Huffman.h"
#include <bitset>
#include <sstream> // std::stringstream
#include <iostream>

void HuffmanCompressor::writeBits(std::ostream& out, const std::string& bits) {
    unsigned char byte = 0;
    int count = 0;

    for (char bit : bits) {
        byte = (byte << 1) | (bit - '0');
        count++;

        if (count == 8) {
            out.put(byte);
            byte = 0;
            count = 0;
        }
    }

    if (count > 0) {
        byte <<= (8 - count);
        out.put(byte);
    }
}

std::string HuffmanCompressor::readBits(std::istream& in) {
    std::string bits;
    unsigned char byte;

    // 不断读取一个字节
    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        // 遍历8位使用位运算提取字节的每一位
        for (int i = 7; i >= 0; i--) {
            bits.push_back(((byte >> i) & 1) ? '1' : '0');
        }
    }

    return bits;
}


void HuffmanCompressor::compress(std::istream& in, std::ostream& out) {
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string data = buffer.str();

    size_t originalSize = data.size();

    buildTree(data);

    std::string encoded;
    for (unsigned char c : data) {
        encoded += codeMap[c];
    }

    /* // 输出：原始长度，编码串
     *  out << data.size() << "\n";
     *  out << encoded << "\n";
     */
    /* 这里并没有达到 **压缩** 的效果，采用写入比特流的方法来完成 */
    // 先写入原始数据的 **字节大小**，对于ASCII字符，字符数=字节数；
    // ATTENTION：这里没考虑多字节字符
    
    // 写入原始数据的字节大小
    out.write(reinterpret_cast<const char*>(&originalSize), sizeof(originalSize));

    // 将比特序列写入文件，按照字节存储
    writeBits(out, encoded);
}

void HuffmanCompressor::decompress(std::istream& in, std::ostream& out) {
    size_t originalSize;
    std::string encoded;

    // in >> originalSize;
    in.read(reinterpret_cast<char*>(&originalSize), sizeof(originalSize));
    // in >> encoded;
    encoded = readBits(in);

    std::string decoded;
    std::string cur;
    for (char bit : encoded) {
        cur.push_back(bit);
        if (decodeMap.count(cur)) {
            decoded.push_back(decodeMap[cur]);
            cur.clear();
        }
    }

    // // 校验解压数据是否与原始数据大小一致
    // if (decoded.size() != originalSize) {
    //     std::cerr << "解压失败，数据大小不匹配！" << std::endl;
    //     return;
    // }

    // 输出：原字符串
    out << decoded;
}

// 使用优先队列构建哈夫曼树
void HuffmanCompressor::buildTree(const std::string& data) {
    // 统计字符串中各个字符出现的频次
    std::unordered_map<unsigned char, int> freq;
    for (unsigned char c : data) freq[c]++;

    // 把每个字符和频次作为树的节点，存入最小堆中
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> pq;
    for (auto& [c, f] : freq) {
        pq.push(new HuffmanNode(c, f));
    }

    // 不断取出两个最小的节点，两两合并再存入
    // 默认父亲节点的字符是0
    while (pq.size() > 1) {
        auto left = pq.top(); pq.pop();
        auto right = pq.top(); pq.pop();
        auto parent = new HuffmanNode(0, left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    root = pq.top();

    // 构建压缩的字符-编码表
    buildCodes(root, "");
}

void HuffmanCompressor::buildCodes(HuffmanNode* node, const std::string& prefix) {
    if (!node) return;
    if (!node->left && !node->right) {
        codeMap[node->ch] = prefix;
        decodeMap[prefix] = node->ch;
    }
    buildCodes(node->left, prefix + "0");
    buildCodes(node->right, prefix + "1");
}