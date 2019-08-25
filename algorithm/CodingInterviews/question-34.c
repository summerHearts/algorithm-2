//
//  question-34.c
//  algorithm
//
//  Created by Kai on 2019/8/25.
//  Copyright © 2019 kai. All rights reserved.
//

#include "question-34.h"
#include "binary-tree-level-order-traversal-2.h"
#include <stdlib.h>

typedef struct CustomArray {
    int *nums;
    int capacity;
    int count;
}CustomArray;

CustomArray *createCustomArray(int capacity);
void arrayPush(CustomArray *ary, int value);
void arrayPop(CustomArray *ary);
void printCustomArray(CustomArray *ary);
int sumOfCustomArray(CustomArray *ary);
void sumOfNodesInPathEqualsToValueCore(TreeNode *tree, int target, CustomArray *ary);

void sumOfNodesInPathEqualsToValue(TreeNode *tree, int target) {
    if (tree == NULL) return;
    
    int treeH = height(tree);
    CustomArray *ary = createCustomArray(treeH);
    
    sumOfNodesInPathEqualsToValueCore(tree, target, ary);
}

// MARK:- 辅助函数

/**
 创建一个类似栈先进后出顺序的数组，但是支持从头开始遍历。

 @param capacity 数组容量
 @return 数组
 */
CustomArray *createCustomArray(int capacity) {
    int *nums = calloc(capacity, sizeof(int));
    CustomArray *ary = malloc(sizeof(CustomArray));
    ary->nums = nums;
    ary->capacity = capacity;
    ary->count = 0;
    return ary;
}

/**
 将新值拼接到数组末尾，数组计数加一

 @param ary 数组
 @param value 新值
 */
void arrayPush(CustomArray *ary, int value) {
    ary->nums[ary->count] = value;
    ary->count++;
}

/**
 移除数组末尾元素，并将数组计数减一

 @param ary 数组
 */
void arrayPop(CustomArray *ary) {
    ary->nums[ary->count - 1] = 0;
    ary->count--;
}

void printCustomArray(CustomArray *ary) {
    for (int i = 0; i < ary->count; i++) {
        printf("%d ", ary->nums[i]);
    }
    printf("\n");
}

int sumOfCustomArray(CustomArray *ary) {
    int result = 0;
    for (int i = 0; i < ary->count; i++) {
        result += ary->nums[i];
    }
    return result;
}

/*
 借助辅助数组，遍历每个节点，分两种情况：
    1）节点为空，判断数组和是否等于目标值，是，则打印数组，否则返回
    2）节点不为空，将节点值拼接到数组末尾
 递归节点的左右子节点，并在最后将当前节点值从数组末尾移除
 */
void sumOfNodesInPathEqualsToValueCore(TreeNode *tree, int target, CustomArray *ary) {
    if (tree == NULL) return;
    arrayPush(ary, tree->val);
    
    if (tree->left == NULL && tree->right == NULL) {
        if (sumOfCustomArray(ary) == target) {
            printCustomArray(ary);
        }
    } else {
        sumOfNodesInPathEqualsToValueCore(tree->left, target, ary);
        sumOfNodesInPathEqualsToValueCore(tree->right, target, ary);
    }
    arrayPop(ary);
}

// MARK:- 测试函数

void testSumOfNodesInPathEqualsToValue1(void) {
    const int size = 5;
    int nums[size] = {10, 5, 12, 4, 7};
    int value = 22;
    TreeNode *tree = createBinaryTree(nums, size);
    printf("%s\n", __func__);
    sumOfNodesInPathEqualsToValue(tree, value);
}

void testSumOfNodesInPathEqualsToValue2(void) {
    const int size = 5;
    int nums[size] = {10, 5, 12, 4, 7};
    int value = 19;
    TreeNode *tree = createBinaryTree(nums, size);
    printf("%s\n", __func__);
    sumOfNodesInPathEqualsToValue(tree, value);
}

void testSumOfNodesInPathEqualsToValue3(void) {
    const int size = 5;
    int nums[size] = {10, 5, 12, 4, 7};
    int value = 15;
    TreeNode *tree = createBinaryTree(nums, size);
    printf("%s\n", __func__);
    sumOfNodesInPathEqualsToValue(tree, value);
}

void testSumOfNodesInPathEqualsToValue4(void) {
    const int size = 6;
    int nums[size] = {10, 5, 12, 4, 7, 13};
    int value = 22;
    TreeNode *tree = createBinaryTree(nums, size);
    printf("%s\n", __func__);
    sumOfNodesInPathEqualsToValue(tree, value);
}

void testSumOfNodesInPathEqualsToValue(void) {
    testSumOfNodesInPathEqualsToValue1();
    testSumOfNodesInPathEqualsToValue2();
    testSumOfNodesInPathEqualsToValue3();
    testSumOfNodesInPathEqualsToValue4();
}