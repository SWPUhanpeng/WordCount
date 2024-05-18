#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ��������
int countCharacters(FILE* file);    //�ַ���ͳ�� ���ո�ˮƽ�Ʊ�������з������ַ���
int countWords(FILE* file);         //������ͳ�� ���ɿո�򶺺ŷָ�Ķ���Ϊ���ʣ�

int main(int argc, char* argv[]) {
    char* parameter = argv[1];
    char* filename = argv[2];

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("�޷��ҵ����ļ� %s\n", filename);
        return 1;
    }

    int result = 0;
    if (strcmp(parameter, "-c") == 0) {
        result = countCharacters(file);
        printf("�ַ���: %d\n", result);
    }
    else if (strcmp(parameter, "-w") == 0) {
        result = countWords(file);
        printf("������: %d\n", result);
    }
    else {
        printf("����Ĳ�����Ч: %s\n", parameter);
        return 1;
    }

    fclose(file);
    return 0;
}

// ͳ���ַ���
int countCharacters(FILE *file) {
    int count = 0;
    int fileeachChar;
    while ((fileeachChar = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

// ͳ�Ƶ�����
int countWords(FILE *file) {
    int count = 0;
    bool inWord = false;          //�����Ƿ�Ϊ��ĸ���ж��Ƿ�ָ�Ϊ����
    int fileeachChar;
    while ((fileeachChar = fgetc(file)) != EOF) {
        if ((fileeachChar > 'a' && fileeachChar < 'z') || fileeachChar > 'A' && fileeachChar < 'Z') {
            inWord = true;
        }
        else if(fileeachChar = ',') {                     //�����֡�������ո�ʱ���ָ�Ϊ����
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
