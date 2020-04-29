#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include <stdio.h>
#include <stdlib.h>

typedef char** HuffmanChar;
typedef struct
{
    char HChar;
    float weight;
    unsigned int parent, lchild, rchild;
}HufmanNode, *HuffmanTree;

void SelectMin(HuffmanTree T, int index, int *min1, int *min2);
void CreateHuffmanTree(HuffmanTree *T, float *w, char str[], int n);
void StrCopy(char *des, char * sour);
void HuffmanEncode(HuffmanTree T, int n);
void HuffmanDecode(HuffmanTree T, char str[], int n);

#endif