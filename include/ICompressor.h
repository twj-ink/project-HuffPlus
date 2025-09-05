#pragma once
#include <iostream>
#include <string>

class ICompressor {
public:
    virtual std::string name() = 0; // 压缩算法名称
    virtual void compress(std::istream& in, std::ostream& out) = 0;
    virtual void decompress(std::istream& in, std::ostream& out) = 0;
    virtual ~ICompressor() = default;
};