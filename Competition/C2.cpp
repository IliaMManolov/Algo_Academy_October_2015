#include <bits/stdc++.h>

using namespace std;

struct SuffixTreeNode
{
    struct SuffixTreeNode *children[128];

    struct SuffixTreeNode *suffixLink;

    int start;
    int *end;

    int suffixIndex;
};

typedef struct SuffixTreeNode Node;

char text[200002];
Node *root = NULL;


Node *lastNewNode = NULL;
Node *activeNode = NULL;

int activeEdge = -1;
int activeLength = 0;


int remainingSuffixCount = 0;
int leafEnd = -1;
int *rootEnd = NULL;
int *splitEnd = NULL;
int size1 = -1;
int size2 = 0;

Node *newNode(int start, int *end)
{
    Node *node =(Node*) malloc(sizeof(Node));
    int i;
    for (i = 0; i < 256; i++)
          node->children[i] = NULL;

    node->suffixLink = root;
    node->start = start;
    node->end = end;

    node->suffixIndex = -1;
    return node;
}

int edgeLength(Node *n) {
    if(n == root)
        return 0;
    return *(n->end) - (n->start) + 1;
}

int walkDown(Node *currNode)
{
    if (activeLength >= edgeLength(currNode))
    {
        activeEdge += edgeLength(currNode);
        activeLength -= edgeLength(currNode);
        activeNode = currNode;
        return 1;
    }
    return 0;
}

void extendSuffixTree(int pos)
{
    leafEnd = pos;

    remainingSuffixCount++;

    lastNewNode = NULL;

    while(remainingSuffixCount > 0) {

        if (activeLength == 0)
            activeEdge = pos;

        if (activeNode->children[text[activeEdge]] == NULL)
        {
            activeNode->children[text[activeEdge]] =
                                          newNode(pos, &leafEnd);

            if (lastNewNode != NULL)
            {
                lastNewNode->suffixLink = activeNode;
                lastNewNode = NULL;
            }
        }
        else
        {
            Node *next = activeNode->children[text[activeEdge]];
            if (walkDown(next))
            {
                continue;
            }
            if (text[next->start + activeLength] == text[pos])
            {
                if(lastNewNode != NULL && activeNode != root)
                {
                    lastNewNode->suffixLink = activeNode;
                    lastNewNode = NULL;
                }
                activeLength++;

                break;
            }

            splitEnd = (int*) malloc(sizeof(int));
            *splitEnd = next->start + activeLength - 1;

            Node *split = newNode(next->start, splitEnd);
            activeNode->children[text[activeEdge]] = split;

            split->children[text[pos]] = newNode(pos, &leafEnd);
            next->start += activeLength;
            split->children[text[next->start]] = next;

            if (lastNewNode != NULL)
            {
                lastNewNode->suffixLink = split;
            }

            lastNewNode = split;
        }

        remainingSuffixCount--;
        if (activeNode == root && activeLength > 0)
        {
            activeLength--;
            activeEdge = pos - remainingSuffixCount + 1;
        }
        else if (activeNode != root)
        {
            activeNode = activeNode->suffixLink;
        }
    }
}

void setSuffixIndexByDFS(Node *n, int labelHeight)
{
    if (n == NULL)  return;

    int leaf = 1;
    int i;
    for (i = 0; i < 256; i++)
    {
        if (n->children[i] != NULL)
        {
            leaf = 0;
            setSuffixIndexByDFS(n->children[i], labelHeight +
                                  edgeLength(n->children[i]));
        }
    }
    if (leaf == 1)
    {
        for(i= n->start; i<= *(n->end); i++)
        {
            if(text[i] == char(30))
            {
                n->end = (int*) malloc(sizeof(int));
                *(n->end) = i;
            }
        }
        n->suffixIndex = size1 - labelHeight;
    }
}

void freeSuffixTreeByPostOrder(Node *n)
{
    if (n == NULL)
        return;
    int i;
    for (i = 0; i < 256; i++)
    {
        if (n->children[i] != NULL)
        {
            freeSuffixTreeByPostOrder(n->children[i]);
        }
    }
    if (n->suffixIndex == -1)
        free(n->end);
    free(n);
}

void buildSuffixTree()
{
    size1 = strlen(text);
    int i;
    rootEnd = (int*) malloc(sizeof(int));
    *rootEnd = - 1;

    root = newNode(-1, rootEnd);

    activeNode = root;
    for (i=0; i<size1; i++)
        extendSuffixTree(i);
    int labelHeight = 0;
    setSuffixIndexByDFS(root, labelHeight);
}

int doTraversal(Node *n, int labelHeight, int* maxHeight,
int* substringStartIndex)
{
    if(n == NULL)
    {
        return -4;
    }
    int i=0;
    int ret = -1;
    if(n->suffixIndex < 0)
    {
        for (i = 0; i < 256; i++)
        {
            if(n->children[i] != NULL)
            {
                ret = doTraversal(n->children[i], labelHeight +
                    edgeLength(n->children[i]),
                    maxHeight, substringStartIndex);

                if(n->suffixIndex == -1)
                    n->suffixIndex = ret;
                else if((n->suffixIndex == -2 && ret == -3) ||
                    (n->suffixIndex == -3 && ret == -2) ||
                    n->suffixIndex == -4)
                {
                    n->suffixIndex = -4;
                    if(*maxHeight < labelHeight)
                    {
                        *maxHeight = labelHeight;
                        *substringStartIndex = *(n->end) -
                            labelHeight + 1;
                    }
                }
            }
        }
    }
    else if(n->suffixIndex > -1 && n->suffixIndex < size2)
        return -2;
    else if(n->suffixIndex >= size2)
        return -3;
    return n->suffixIndex;
}

void getLongestCommonSubstring()
{
    int maxHeight = 0;
    int substringStartIndex = 0;
    doTraversal(root, 0, &maxHeight, &substringStartIndex);

    int k;
    for (k=0; k<maxHeight; k++)
        ;
    cout<<k<<endl;
}

int main()
{
    string hue, hua;
    getline(cin, hue);
    getline(cin, hua);

    size2 = hua.size();
    string uopa = hue+char(30)+hua+char(31);
    strcpy(text, uopa.c_str());
    buildSuffixTree();
    getLongestCommonSubstring();

    return 0;
}
