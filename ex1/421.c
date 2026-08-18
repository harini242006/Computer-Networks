#include <stdlib.h>

typedef struct {
    int children[2];
} TrieNode;

TrieNode* triePool = NULL;
int nodeCount = 0;

int createNode() {
    triePool[nodeCount].children[0] = 0;
    triePool[nodeCount].children[1] = 0;
    return nodeCount++;
}

void insert(int num) {
    int curr = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (triePool[curr].children[bit] == 0) {
            triePool[curr].children[bit] = createNode();
        }
        curr = triePool[curr].children[bit];
    }
}

int findMaxXORForNum(int num) {
    int curr = 0;
    int maxXOR = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        int toggledBit = 1 - bit;
        if (triePool[curr].children[toggledBit] != 0) {
            maxXOR |= (1 << i);
            curr = triePool[curr].children[toggledBit];
        } else {
            curr = triePool[curr].children[bit];
        }
    }
    return maxXOR;
}

int findMaximumXOR(int* nums, int numsSize) {
    if (numsSize < 2) return 0;

    int maxNodes = numsSize * 31 + 2;
    triePool = (TrieNode*)malloc(maxNodes * sizeof(TrieNode));
    nodeCount = 0;

    createNode(); 
    int globalMax = 0;

    insert(nums[0]);

    for (int i = 1; i < numsSize; i++) {
        int currentMax = findMaxXORForNum(nums[i]);
        if (currentMax > globalMax) {
            globalMax = currentMax;
        }
        insert(nums[i]);
    }

    free(triePool);
    triePool = NULL;
    return globalMax;
}
