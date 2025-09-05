#pragma once
#include "ICompressor.h"
#include <vector>
#include <unordered_map>
#include <queue> // priority_queue

// Huffman 树节点的结构
struct HuffmanNode {
    unsigned char ch; // 字符
    long long freq;   // 频率，使用64位整数防止大文件溢出
    HuffmanNode* left;
    HuffmanNode* right;

    // 构造函数
    HuffmanNode(unsigned char ch_, long long freq_) 
    : ch(ch_), freq(freq_), left(nullptr), right(nullptr) {};
};

// 比较器：按照频率大小排序，便于找到频率最小的节点
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; // 倒序排列，最小堆
    }
};

// Huffman 压缩器实现，基于统一接口
class HuffmanCompressor : public ICompressor {
public:
    std::string name() override { return "Huffman"; }
    void compress(std::istream& in, std::ostream& out) override;
    void decompress(std::istream& in, std::ostream& out) override;

private:
    void buildTree(const std::string& data); // 构建哈夫曼树
    void buildCodes(HuffmanNode* node, const std::string& prefix); // 构建字符编码

    std::unordered_map<unsigned char, std::string> codeMap; // 字符与编码的映射
    std::unordered_map<std::string, unsigned char> decodeMap; // 编码与字符的映射
    HuffmanNode* root = nullptr; // 树的根节点
};