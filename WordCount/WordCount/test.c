#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 函数声明
int countCharacters(FILE* file);    //字符数统计 （空格，水平制表符，换行符均算字符）
int countWords(FILE* file);         //单词数统计 （由空格或逗号分割开的都视为单词）

int main(int argc, char* argv[]) {
    char* parameter = argv[1];
    char* filename = argv[2];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法找到此文件 %s\n", filename);
        return 1;
    }

    int result = 0;
    if (strcmp(parameter, "-c") == 0) {
        result = countCharacters(file);
        printf("字符数: %d\n", result);
    }
    else if (strcmp(parameter, "-w") == 0) {
        result = countWords(file);
        printf("单词数: %d\n", result);
    }
    else {
        printf("输入的参数无效: %s\n", parameter);
        return 1;
    }

    fclose(file);
    return 0;
}

// 统计字符数
int countCharacters(FILE *file) {
    int count = 0;
    int fileeachChar;
    while ((fileeachChar = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

// 统计单词数
int countWords(FILE *file) {
    int count = 0;
    bool inWord = false;          //根据是否为字母来判断是否分割为单词
    int fileeachChar;
    while ((fileeachChar = fgetc(file)) != EOF) {
        if ((fileeachChar > 'a' && fileeachChar < 'z') || fileeachChar > 'A' && fileeachChar < 'Z') {
            inWord = true;
        }
        else if(fileeachChar = ',') {                     //当出现“，”或空格时，分割为单词
            if (inWord) {
                count++;
                inWord = false;
            }
        }
        else if(fileeachChar == 32){
            if (inWord) {
                count++;
                inWord = false;
            }
        }
        else {
            inWord = true;
        }
    }
    if (inWord) {
        count++;
    }
    return count;
}
