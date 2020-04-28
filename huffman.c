#include <stdio.h>
#include <stdlib.h>

typedef char** HuffmanChar;
typedef struct
{
    float weight;
    unsigned int parent, lchild, rchild;
}HufmanNode, *HuffmanTree;

void SelectMin(HuffmanTree T, int index, int *min1, int *min2);
void CreateHuffmanTree(HuffmanTree *T, float *w, int n);
void StrCopy(char *des, char * sour);
void HuffmanEncode(HuffmanTree T, HuffmanChar *Hc, int n);

int main(){
    float w[] = {0.05, 0.29, 0.07, 0.08, 0.14, 0.23, 0.03, 0.11};
    HuffmanTree T;
    HuffmanChar HC;
    CreateHuffmanTree(&T, w, 8);
    HuffmanEncode(T, &HC, 8);
    for(int i = 1; i <= 15; i++)
    {
        if(i<=8)printf("%d  %d  %.2f  %d  %d %s\n", i, (T+i)->parent, (T+i)->weight, (T+i)->lchild, (T+i)->rchild, HC[i]);
        else printf("%d  %d  %.2f  %d  %d\n", i, (T+i)->parent, (T+i)->weight, (T+i)->lchild, (T+i)->rchild);
    }
    return 0;
}

void CreateHuffmanTree(HuffmanTree *T, float *w, int n) {
    int m, i;
    int min1, min2;
    HuffmanTree p;
    if(n <= 1) *T = NULL;
    else
    {
        m = 2*n;
        if((*T = (HuffmanTree)malloc(m*sizeof(HufmanNode)))){
            for(p = *T+1, i = 1; i <= n; p++, i++, w++){
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

void HuffmanEncode(HuffmanTree T, HuffmanChar *Hc, int n){
    int c, f, start;
    char *temp;
    if((*Hc = (char**)malloc((n+1)*sizeof(char*)))){
        if((temp = (char*)malloc(n*sizeof(char)))){
            temp[n-1] = '\0';
            for (int i = 1; i <= n; i++)
            {
                start = n - 1;
                for(c = i, f = T[c].parent; f != 0; c = f, f = T[f].parent){
                    if(T[f].lchild == c) temp[--start] = '0';
                    else temp[--start] = '1';
                }
                if(((*Hc)[i] = (char*)malloc(sizeof(char)*(n - start)))){
                    StrCopy((*Hc)[i], &temp[start]);
                }
            }
        }
    }
    free(temp);
}

void StrCopy(char *des, char * sour){
    while ((*des++ = *sour++));   
}