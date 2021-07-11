#include "tree.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void printTree(tree T, nodeptr target);

int main(int argc, char * argv[])
{
    tree T;
    nodeptr target;
    int ret, option, data;

    T = createTree();
    assert(T != NULL);

    printTree(T, NULL);
    printf("\n");

    while (1)
    {
        printf(">> 0. insert\n");
        printf("   1. find\n");
        printf("   2. delete\n");
        printf("   3. quit\n");
        printf(">> ");
        ret = scanf("%d", &option);
        assert(ret == 1);

        if (option == 3)
            break;

        printf(">> Data: ");
        ret = scanf("%d", &data);
        assert(ret == 1);

        switch (option)
        {
        case 0:
            ret = insertElement(T, data);
            assert(ret == 0);
            target = NULL;
            break;
        case 1:
            target = findElement(T, data);
            if (target == NULL)
                printf("   not found\n");
            break;
        case 2:
            ret = deleteElement(T, data);
            if (ret == -1)
                printf("   no deletion\n");
            target = NULL;
            break;
        default:
            break;
        }

        printTree(T, target);
        printf("\n");
    }

    destroyTree(T);

    return 0;
}

static int _getDepth(nodeptr root)
{
    int ldepth, rdepth, ret;

    if (root == NULL)
        return 0;
    else
    {
        ldepth = _getDepth(root->left);
        rdepth = _getDepth(root->right);
        if (ldepth > rdepth)
            ret = ldepth + 1;
        else
            ret = rdepth + 1;
    }

    return ret;
}

static void _buildHeap(nodeptr root, nodeptr heap[], int index)
{
    if (root != NULL)
    {
        heap[index] = root;
        _buildHeap(root->left, heap, index * 2);
        _buildHeap(root->right, heap, index * 2 + 1);
    }
}

static int _getItemWidth(nodeptr root)
{
    int ret, data;

    ret = 1;
    data = root->data;

    if (data < 0)
    {
        ret += 1;
        data = -1 * data;
    }

    while (data > 9)
    {
        data /= 10;
        ret += 1;
    }

    return ret;
}

static int _getMaxItemWidth(nodeptr root)
{
    int lwith, rwidth, ret;

    if (root == NULL)
        return 0;
    else
    {
        lwith = _getMaxItemWidth(root->left);
        rwidth = _getMaxItemWidth(root->right);
        ret = _getItemWidth(root);
        if (lwith > ret && lwith > rwidth)
            ret = lwith;
        else if (rwidth > ret && rwidth > lwith)
            ret = rwidth;
    }

    return ret;
}

void printTree(tree T, nodeptr target)
{
    nodeptr root;
    nodeptr * heap;
    int depth, size, width;
    int start_space, inner_space;

    root = T->root;

    if (root == NULL)
    {
        printf("dummy head\n");
        return;
    }

    depth = _getDepth(root);
    size = 1 << depth;
    heap = (nodeptr *)malloc(sizeof(nodeptr) * size);
    assert(heap != NULL);
    /* heap[0] is not used */
    for (int i = 1; i < size; i++)
        heap[i] = NULL;

    _buildHeap(root, heap, 1);

    width = _getMaxItemWidth(root);
    if (target != NULL)
        width += 2;

    for (int i = 1; i <= depth; i++)
    {
        start_space = ((1 << (depth - i)) * (width + 1) - 1) / 2 - width / 2;
        inner_space = (1 << (depth - i)) * (width + 1) - width;

        if (start_space != 0)
            printf("%*c", start_space, ' ');
        for (int j = (1 << (i - 1)); j < (1 << i) - 1; j++)
        {
            if (heap[j] == NULL)
                printf("%*c%*c", -1 * width, '#', inner_space, ' ');
            else if (heap[j] == target)
                printf("[%*d]%*c", -1 * (width - 2), heap[j]->data, inner_space, ' ');
            else
                printf("%*d%*c", -1 * width, heap[j]->data, inner_space, ' ');
        }
        if (heap[(1 << i) - 1] == NULL)
            printf("%*c\n", -1 * width, '#');
        else if (heap[(1 << i) - 1] == target)
            printf("[%*d]\n", -1 * (width - 2), heap[(1 << i) - 1]->data);
        else
            printf("%*d\n", -1 * width, heap[(1 << i) - 1]->data);
    }

    free(heap);
}
