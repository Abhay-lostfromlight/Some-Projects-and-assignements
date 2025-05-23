#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

//list struct 
typedef struct NODE{
    int d;
    struct NODE *next;
} NODE;

//insert at the end function
void insert_end(NODE **head, int value){
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    new_node->d = value;
    new_node->next = NULL;

    if(*head == NULL){
        *head = new_node;
        return;
    }
    NODE *temp = *head;
    while( temp->next != NULL){
        temp = temp->next;
    }

    temp->next = new_node;
}

//genrating and inserting 100 random random integers function
NODE *genrate_random_list(){
    srand(time(NULL));

    NODE *head = NULL;
    for( int i = 0; i < 100; i++ ){
        int num = rand() % 1000;
        insert_end(&head, num);
    }
    return head;

}

//function to bubble sort
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
 
//printing list in 5 diffrent rows
void print_list(NODE *head){
    int count = 0;

    NODE *current = head;
    while(current != NULL){
        printf("%4d", current->d);
        count++;

        if(count % 5 == 0){
            printf("\n");
        }

        current =  current ->next;
    }

    if(count % 5 != 0){
        printf("\n");
    }

}

int main(void){
    NODE *head = genrate_random_list();

    bubble_sort(head);

    print_list(head);

    return 0;
}
