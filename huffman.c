#include "./huffman.h"

void CreateHuffmanTree(HuffmanTree *T, float *w, char str[], int n) {
    int m, i;
    int min1, min2;
    HuffmanTree p;
    if(n <= 1) *T = NULL;
    else
    {
        m = 2*n;
        if((*T = (HuffmanTree)malloc(m*sizeof(HufmanNode)))){
            for(p = *T+1, i = 1; i <= n; p++, i++, w++){
                p->HChar = str[i-1];
                p->weight = *w;
                p->parent = 0;
                p->lchild = 0;
                p->rchild = 0;
            }
            for(;i < m; p++, i++){
                p->weight = 0;
                p->parent = 0;
                p->lchild = 0;
                p->rchild = 0;
            }
            for(i = n+1; i < m; i++){
                SelectMin(*T, i-1, &min1, &min2);
                (*T+min1)->parent = i; (*T+min2)->parent = i;
                (*T+i)->weight = (*T+min1)->weight + (*T+min2)->weight;
                (*T+i)->lchild = min1; (*T+i)->rchild = min2;
            }
        }
    }
    
}

void SelectMin(HuffmanTree T, int index, int *min1, int *min2){
    int i;
    *min1 = index;
    for(i = 1; i < index; i++){
        if((T+i)->parent == 0 && (T+i)->weight < (T + *min1)->weight) *min1 = i;
    }
    for(i = 1; i<=index; i++){
        if((T+i)->parent == 0 && i != *min1) {*min2 = i; break;}
    }
    for(i = 1; i <= index; i++){
        if((T+i)->parent == 0 && (T+i)->weight < (T + *min2)->weight && i != *min1) *min2 = i;
    }
}

void HuffmanEncode(HuffmanTree T, int n){
    int c, f, start;
    char *temp;
    HuffmanChar Hc;
    if((Hc = (char**)malloc((n+1)*sizeof(char*)))){
        if((temp = (char*)malloc(n*sizeof(char)))){
            temp[n-1] = '\0';
            for (int i = 1; i <= n; i++)
            {
                start = n - 1;
                for(c = i, f = T[c].parent; f != 0; c = f, f = T[f].parent){
                    if(T[f].lchild == c) temp[--start] = '0';
                    else temp[--start] = '1';
                }
                if((Hc[i] = (char*)malloc(sizeof(char)*(n - start)))){
                    StrCopy(Hc[i], &temp[start]);
                }
                printf("%c : %s\n", T[i].HChar, Hc[i]);
            }
        }
    }
    free(temp);
}
//根据传递过来的二进制码str解码;
void HuffmanDecode(HuffmanTree T, char str[], int n){
    int index;
    while (*str)
    {
        index = 2*n - 1;
        while(T[index].lchild != 0 && *str){
            if(*str == '0') index = T[index].lchild;
            else index = T[index].rchild;
            str++;
        }
        if(T[index].lchild == 0) printf("%c", T[index].HChar);
    }
    printf("\n");
}

void StrCopy(char *des, char * sour){
    while ((*des++ = *sour++));   
}