#include "./huffman.h"

int main(){
    float w[] = {0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};//字符权加值
    char str[] = "abcdefgh";//字符串
    char code[] = "00011010101110111100111111";//明文
    int len = 8;
    HuffmanTree T;
    HuffmanChar HC;
    CreateHuffmanTree(&T, w, str, len);
    printf("huffman编码:\n");
    HuffmanEncode(T, len);
    printf("二进制字符串:%s\n", code);
    printf("huffman解码结果:");
    HuffmanDecode(T, code, len);
    return 0;
}