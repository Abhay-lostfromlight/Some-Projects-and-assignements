#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//node struct
struct node{
    int d;
    struct node *prev;
    struct node *next;
};

typedef struct node NODE;

//insert function
NODE *insert_end(NODE *head, int data){
    NODE *new_node = (NODE*)malloc(sizeof(NODE));

    new_node->d = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    if( head == NULL ){
        return new_node;
    }

    NODE *current = head;
    while( current->next != NULL){
        current = current ->next;
    }

    current->next = new_node;
    new_node->prev = current;
    return head;
    
}

//genrate and fill list function with 200 random integers

NODE *genrate_list(){
    srand(time(NULL));

   NODE *head = NULL;

   for(int i = 0; i < 200; i++){
        int num = rand() % 50;
        head = insert_end(head, num);
   }
   return head;
}

//bubble sorting the list 
void bubble_sort( NODE *head){
    if(head == NULL || head->next == NULL){
        return;
    }

    bool swapped = true;

    while( swapped) {
        swapped = false;
        NODE *current = head;
        while( current ->next != NULL){
            if(current ->d > current->next->d){
                //swapping
                int temp = current->d;
                current->d = current->next->d;
                current->next->d = temp;
                
                swapped = true;
            }
            current = current ->next;
        }
    }
}

//function to remove duplicates adjacently
void removeDuplicates( NODE *head){
    NODE *current = head; 

    while(current != NULL && current->next != NULL){
        if(current->d == current->next->d){
            NODE *temp = current->next;

            current->next = temp->next;
            if(temp->next != NULL){
                temp ->next->prev = current;
            }

            free(temp);
        }
        else {
            current = current ->next;
        }
    }
}

//printing list
void printlist( NODE *head){
    NODE *current = head;
    int count = 0;

    while( current != NULL){
        printf("%2d\t", current->d );
        current = current->next;
        count++;
        if (count % 10 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

//freeing memory
void freelist(NODE *head){
    NODE *temp;
    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main(void){
    NODE *head = genrate_list();
    printf("orignal list: \n");
    printlist(head);

    bubble_sort(head);
    printf("sorted list: \n");
    printlist(head);

    removeDuplicates(head);
    printf("\n after removing duplicates: \n");
    printlist(head);

    freelist(head);
    return 0;
}