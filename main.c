#include<stdio.h>
#include<stdlib.h>
#include <string.h>

typedef enum{
    true = 1 , false = 0
}bool;

typedef struct Student;
struct StudentNode;
typedef struct RegList;

int main(void)
{
    // TODO: 1. Add Student Type

    // TODO: 2. Student Registration List (Linked List)

    // TODO: 3. Waiting Queue (Linked List-Based Queue)

    // TODO: 4. Drop History Stack (Linked List-Based Stack)

    // TODO: 5. Main Menu

    return 0;
}


// Student Structure


typedef struct Student{
    char id[20];
    char name[30];
}Student;



// Student Linked List

struct StudentNode{
    Student  student;
    struct StudentNode * next;
};

typedef struct RegList{
    struct StudentNode * head;
}RegList;

void initRegList(RegList * list){
    list->head = NULL;
}

Student student(char id, char name) {
    return (Student){id, name};
}

void addRegisteredStudent(RegList * list ,Student stu ){
    struct StudentNode * nw = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    nw->student = stu;
    nw->next = NULL;

    if(list->head == NULL){ list->head = nw; return;} 

    struct StudentNode * tmp = list->head;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = nw;

}

void removeRegisteredStudent(RegList * list, Student stu) {
    if (list->head == NULL) return; 

    struct StudentNode *curr = list->head;
    struct StudentNode *prev = NULL;

    if (strcmp(curr->student.id , stu.id)) {
        list->head = curr->next; 
        free(curr);         
        return;
    }

    while (curr != NULL && !strcmp(curr->student.id , stu.id)) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) return;

    prev->next = curr->next;
    free(curr);
}

bool searchStu(RegList* list ,  char id){
    struct StudentNode *tmp = list->head;

    while (tmp != NULL) {
        if (strcmp(tmp->student.id , id)) return true;
        tmp = tmp->next; 
    }
    return false;
}

void displayRegStu(RegList* list){
    printf("\n/---------- Registerd Student List ---------- /\n");
    struct StudentNode * tmp = list->head;

    if (tmp ==NULL)printf("\t List Is Empty");
    
    while (tmp != NULL) {
        printf("{ Id: %s, Name: %s }\n", tmp->student.id, tmp->student.name);
        tmp = tmp->next;
    }
    
    printf("\n/------------------- END ------------------- /\n\n");
}

