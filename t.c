#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;

int initializeBST(Node** h);


void inorderTraversal(Node* ptr);    
void preorderTraversal(Node* ptr);   
void postorderTraversal(Node* ptr);   
int insert(Node* head, int key);    
int deleteLeafNode(Node* head, int key);  
Node* searchRecursive(Node* ptr, int key);  
Node* searchIterative(Node* head, int key);    
int freeBST(Node* head); 



int main()
{
    char command;
    int key;
    Node* head = NULL;
    Node* ptr = NULL;    /* 임시 포인터 */

    printf("[-----[최 현 철]    [2022078014]-----]");

    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                   Binary Search Tree #1                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize BST       = z                                       \n");
        printf(" Insert Node          = n      Delete Leaf Node             = d \n");
        printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
        printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
        printf(" Postorder Traversal  = t      Quit                         = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch(command) {
        case 'z': case 'Z':
            initializeBST(&head);
            break;
        case 'q': case 'Q':
            freeBST(head);
            break;
        case 'n': case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insert(head, key);
            break;
        case 'd': case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteLeafNode(head, key);
            break;
        case 'f': case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            ptr = searchIterative(head, key);
            if(ptr != NULL)
                printf("\n 노드 [%d]가 %p에 존재합니다.\n", ptr->key, ptr);
            else
                printf("\n 노드 [%d]를 찾을 수 없습니다.\n", key);
            break;
        case 's': case 'S':
            printf("Your Key = ");
            scanf("%d", &key);
            ptr = searchRecursive(head->left, key);
            if(ptr != NULL)
                printf("\n 노드 [%d]가 %p에 존재합니다.\n", ptr->key, ptr);
            else
                printf("\n 노드 [%d]를 찾을 수 없습니다.\n", key);
            break;

        case 'i': case 'I':
            inorderTraversal(head->left);
            break;
        case 'p': case 'P':
            preorderTraversal(head->left);
            break;
        case 't': case 'T':
            postorderTraversal(head->left);
            break;
        default:
            printf("\n       >>>>>   집중하세요!!   <<<<<     \n");
            break;
        }

    } while(command != 'q' && command != 'Q');

    return 1;
}
int initializeBST(Node** h) {
    // 트리가 비어 있지 않으면 트리의 모든 할당된 노드를 제거합니다.
    if (*h != NULL)
        freeBST(*h);

    // 헤드 노드 생성
    *h = (Node*)malloc(sizeof(Node));
    (*h)->left = NULL;    // 루트
    (*h)->right = *h;
    (*h)->key = -9999;
    return 1;
}
void inorderTraversal(Node* ptr) {
    // 중위 순회: 왼쪽 서브트리 -> 현재 노드 -> 오른쪽 서브트리
    if (ptr) {
        inorderTraversal(ptr->left);  // 왼쪽 서브트리 순회
        printf(" [%d] ", ptr->key);   // 현재 노드 출력
        inorderTraversal(ptr->right); // 오른쪽 서브트리 순회
    }
}

void preorderTraversal(Node* ptr) {
    // 전위 순회: 현재 노드 -> 왼쪽 서브트리 -> 오른쪽 서브트리
    if (ptr) {
        printf(" [%d] ", ptr->key);   // 현재 노드 출력
        preorderTraversal(ptr->left); // 왼쪽 서브트리 순회
        preorderTraversal(ptr->right);// 오른쪽 서브트리 순회
    }
}

void postorderTraversal(Node* ptr) {
    // 후위 순회: 왼쪽 서브트리 -> 오른쪽 서브트리 -> 현재 노드
    if (ptr) {
        postorderTraversal(ptr->left);  // 왼쪽 서브트리 순회
        postorderTraversal(ptr->right); // 오른쪽 서브트리 순회
        printf(" [%d] ", ptr->key);     // 현재 노드 출력
    }
}
int insert(Node* head, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;

    if (head->left == NULL) {
        head->left = newNode;
        return 1;
    }

    // head->left는 루트 노드입니다.
    Node* ptr = head->left;

    Node* parentNode = NULL;
    while (ptr != NULL) {
        // 해당 키를 가진 노드가 이미 있는 경우 그냥 반환합니다.
        if (ptr->key == key)
            return 1;

        // 자식 노드로 이동해야 하므로 부모를 추적하기 위해 parentNode를 사용합니다.
        parentNode = ptr;

        // 키 비교: 현재 노드의 키가 입력 키보다 작으면 새 노드를 오른쪽 서브트리에 삽입합니다.
        // 그렇지 않으면 왼쪽 서브트리에 삽입합니다.
        if (ptr->key < key)
            ptr = ptr->right;
        else
            ptr = ptr->left;
    }

    // 새 노드를 부모에 연결합니다.
    if (parentNode->key > key)
        parentNode->left = newNode;
    else
        parentNode->right = newNode;
    return 1;
}

int deleteLeafNode(Node* head, int key) {
    // 특정 키 값을 가진 단말 노드를 삭제하는 함수

    // 트리가 비어있는 경우
    if (head == NULL) {
        printf("\n 삭제할 노드가 없습니다!!\n");
        return -1;
    }

    // 루트 노드가 없는 경우
    if (head->left == NULL) {
        printf("\n 삭제할 노드가 없습니다!!\n");
        return -1;
    }

    Node* parent = head; // 부모 노드
    Node* target = head->left; // 삭제할 노드
    Node* child = NULL; // 삭제할 노드의 자식 노드

    // 삭제할 노드를 찾을 때까지 반복
    while (target != NULL) {
        // 삭제할 노드를 찾은 경우
        if (target->key == key) {
            // 단말 노드인 경우
            if (target->left == NULL && target->right == NULL) {
                // 부모 노드와의 연결을 끊음
                if (parent->left == target)
                    parent->left = NULL;
                else
                    parent->right = NULL;
            } else {
                // 단말 노드가 아닌 경우
                printf("\n 단말 노드가 아닙니다!!\n");
                return -1;
            }
            free(target); // 삭제할 노드 메모리 해제
            return 1;
        }

        parent = target; // 부모 노드 업데이트

        // 키 값에 따라 왼쪽 서브트리 또는 오른쪽 서브트리로 이동
        if (target->key < key)
            target = target->right;
        else
            target = target->left;
    }

    printf("\n 삭제할 노드가 없습니다!!\n");
    return -1;
}

Node* searchRecursive(Node* ptr, int key) {
    // 재귀적인 방법으로 노드 검색
    // ptr: 검색을 시작할 노드
    // key: 검색할 키 값

    // 노드가 NULL인 경우 또는 키 값이 일치하는 경우
    if (ptr == NULL || ptr->key == key)
        return ptr;

    // 키 값에 따라 왼쪽 서브트리 또는 오른쪽 서브트리로 이동
    if (ptr->key < key)
        return searchRecursive(ptr->right, key);
    else
        return searchRecursive(ptr->left, key);
}

Node* searchIterative(Node* head, int key) {
    // 반복적인 방법으로 노드 검색
    // head: 트리의 헤드 노드
    // key: 검색할 키 값

    // 루트 노드
    Node* ptr = head->left;

    while (ptr != NULL) {
        // 키 값이 일치하는 경우 해당 노드 반환
        if (ptr->key == key)
            return ptr;

        // 키 값에 따라 왼쪽 서브트리 또는 오른쪽 서브트리로 이동
        if (ptr->key < key)
            ptr = ptr->right;
        else
            ptr = ptr->left;
    }

    // 노드를 찾지 못한 경우 NULL 반환
    return NULL;
}

void freeNode(Node* ptr) {
    // 재귀적으로 노드와 관련된 메모리를 해제하는 함수
    // ptr: 해제할 노드

    if (ptr) {
        freeNode(ptr->left);  // 왼쪽 서브트리의 노드들을 재귀적으로 해제
        freeNode(ptr->right); // 오른쪽 서브트리의 노드들을 재귀적으로 해제
        free(ptr);            // 노드 자체의 메모리 해제
    }
}

int freeBST(Node* head) {
    // 이진 탐색 트리의 모든 메모리를 해제하는 함수
    // head: 트리의 헤드 노드

    if (head->left == head) {
        free(head); // 헤드 노드만 있는 경우 헤드 노드 메모리 해제
        return 1;
    }

    Node* p = head->left; // 루트 노드

    freeNode(p);  // 루트 노드를 포함한 모든 노드들의 메모리 해제
    free(head);   // 헤드 노드 메모리 해제
    return 1;
}
