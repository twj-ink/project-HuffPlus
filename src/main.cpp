#include "Huffman.h"
#include <fstream>
#include <iostream>

int main() {
    HuffmanCompressor huff;

    // 压缩文件
    std::ifstream input("../test/input.txt", std::ios::binary);
    std::ofstream compressed("../test/output.huffp", std::ios::binary);
    huff.compress(input, compressed);
    input.close();
    compressed.close();

    // 解压文件
    std::ifstream compressed_input("../test/output.huffp", std::ios::binary);
    std::ofstream output("../test/decompressed.txt", std::ios::binary);
    huff.decompress(compressed_input, output);
    compressed_input.close();
    output.close();

    std::cout << "Compress and decompress have done!\nCheck the files in test dir!\n";
    return 0;
}