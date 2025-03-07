#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義鏈結串列節點
typedef struct Node {
    char data;
    int count;
    struct Node *next;
} Node;

// 檢查字元是否可列印
int isPrintable(char ch) {
    return (ch >= 32 && ch <= 126);
}

// 新增節點到鏈結串列
void append(Node **head, char ch) {
    Node *temp = *head;
    while (temp) {
        if (temp->data == ch) {
            temp->count++;
            return;
        }
        temp = temp->next;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "記憶體分配失敗\n");
        exit(1);
    }
    newNode->data = ch;
    newNode->count = 1;
    newNode->next = *head;
    *head = newNode;
}

// 釋放鏈結串列
void freeList(Node *head) {
    Node *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    FILE *file = fopen(__FILE__, "r"); // 讀取自身檔案
    if (!file) {
        fprintf(stderr, "無法開啟檔案\n");
        return 1;
    }

    Node *head = NULL;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        append(&head, ch);
    }
    fclose(file);

    printf("\n每個字元的總數:\n");
    Node *temp = head;
    while (temp) {
        if (isPrintable(temp->data)) {
            printf("%c : %d\n", temp->data, temp->count);
        } else {
            printf("ASCII %d : %d\n", (unsigned char)temp->data, temp->count);
        }
        temp = temp->next;
    }

    freeList(head);
    return 0;
}
