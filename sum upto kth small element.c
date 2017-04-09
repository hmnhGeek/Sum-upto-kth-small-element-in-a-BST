#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
    int data;
    struct node *left, *right;
}bst;

bst *root = NULL;
bst *parent = NULL;
int sum = 0, counter = 1;

bst *newNode(int item){
    bst *temp = (bst *)malloc(sizeof(bst));
    temp -> data = item;
    temp -> left = temp -> right = NULL;
    return temp;
}

void sum_upto(bst *node, int k){
    if(node != NULL){
        sum_upto(node -> left, k);
        if(counter <= k){
            sum += node -> data;
            counter += 1;
        }
        sum_upto(node -> right, k);
    }
}

void searchNode(bst *node, int item){
    if(node -> data < item){
        if(node -> right != NULL){
            searchNode(node -> right, item);
        }
        else{
            node -> right = newNode(item);
        }
    }
    else{
        if(node -> left != NULL){
            searchNode(node -> left, item);
        }
        else{
            node -> left = newNode(item);
        }
    }
}

int smallest(bst * node){
    while(node -> left != NULL){
        node = node -> left;
    }
    return node -> data;
}

void delete_it(bst * node){
    // Leaf node. //
    if(node -> left == NULL && node -> right == NULL){
        if(parent == node){
            root = NULL;
            parent = root;
        }
        else if(parent -> left == node){
            parent -> left =NULL;
        }
        else{
            parent -> right = NULL;
        }
        free(node);
    }
    // Has right child //
    else if(node -> left == NULL){
        if(parent == node){
            root = parent -> right;
            parent = root;
        }
        else if(parent -> right == node){
            parent -> right = node -> right;
        }
        else{
            parent -> left = node -> right;
        }
        free(node);
    }
    else if(node -> right == NULL){
        if(parent == node){
            root = parent -> left;
            parent = root;
        }
        else if(parent -> left == node){
            parent -> left = node -> left;
        }
        else{
            parent -> right = node -> left;
        }
        free(node);
    }
    else if(node -> left != NULL && node -> right != NULL){
        int small = smallest(node -> right);
        search(root, small);
        node -> data = small;
    }
}

void search(bst * node, int item){
    if(item > node -> data){
        parent = node;
        search(node -> right, item);
    }
    else if(item < node -> data){
        parent = node;
        search(node -> left, item);
    }
    else{
        delete_it(node);
    }
}

void delete(int item){
    if(root == NULL){
        printf("The tree is empty.\n");
    }
    else{
        parent = root;
        search(root, item);
    }
}

void insert(bst * node, int item){
    if(root == NULL){
        root = newNode(item);
    }
    else{
        searchNode(root, item);
    }
}

void inorder(bst *node){
    if(node != NULL){
        inorder(node -> left);
        printf("%d\n", node -> data);
        inorder(node -> right);
    }
}

void find(bst *node, int item){
    
    if(node -> data == item){
        printf("True\n");
    }
    else{
        if(item > node -> data){
            if(node -> right != NULL){
                find(node -> right, item);
            }
            else
                printf("False\n");
            return;
        }
        else{
            if(node -> left != NULL){
                find(node -> left, item);
            }
            else
                printf("False\n");
            return;
        }
    }
}

void main(){
    int ch = 1;
    while(ch){
        printf("Enter 1 to insert.\n");
        printf("Enter 2 to delete.\n");
        printf("Enter 3 to display.\n");
        printf("Enter 4 to find.\n");
        printf("Enter 5 to sum upto kth smallest number.\n");
        
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        if (choice == 1){
            int item;
            printf("Enter the item: ");
            scanf("%d", &item);
            
            insert(root, item);
        }
        else if(choice == 2){
            int item;
            printf("Enter the item: ");
            scanf("%d", &item);
            
            delete(item);
        }
        else if(choice == 3){
            inorder(root);
        }
        else if(choice == 4){
            int item;
            printf("Enter the item: ");
            scanf("%d", &item);
            
            find(root, item);
        }
        else if(choice == 5){
            int k;
            sum = 0;
            counter = 1;
            printf("Enter k: ");
            scanf("%d", &k);
            sum_upto(root, k);
            printf("%d\n", sum);
        }
        else{
            ch = 0;
        }
    }
}
