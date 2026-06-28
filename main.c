#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define ACCOMMODATIONS 5
#define NAME_LENGTH 30
#define ID_LENGTH 20

typedef enum{
    true = 1 , false = 0
}bool;

typedef struct Student{
    char id[ID_LENGTH];
    char name[NAME_LENGTH];
}Student;

struct StudentNode{
    Student student;
    struct StudentNode * next;
};

typedef struct RegList{
    struct StudentNode * head;
}RegList;

typedef struct WaitingQueue{
    struct StudentNode * front;
    struct StudentNode * rear;
}WaitingQueue;

typedef struct History{
    struct StudentNode * top;
}History;

void initRegList(RegList * list);
void initQueue(WaitingQueue * q);
void initHistory(History * h);
int sizeOFList(RegList * l);
Student makeStudent( char id[],  char name[]);
void addRegisteredStudent(RegList * list ,Student stu);
void removeRegisteredStudent(RegList * list, Student stu);
Student* searchStu(RegList* list ,  char id[]);
void displayRegStu(RegList* list);
void enqueue(WaitingQueue * q , Student stu);
Student dequeue(WaitingQueue * q );
void displayQueue(WaitingQueue* q);
bool isQueueEmpty(WaitingQueue *q);
void pushHistory(History * h , Student stu);
Student popHistory(History * h);
void displayHistory(History* h);
bool isHistoryEmpty(History * h);

int main(void)
{
    
    RegList registeredStudents;
    RegList * registeredStudents_ptr = &registeredStudents;
    initRegList(registeredStudents_ptr);
    
    WaitingQueue waitingQueue;
    WaitingQueue * waitingQueue_ptr = &waitingQueue;
    initQueue(waitingQueue_ptr);
    
    History history;
    History * history_ptr = &history;
    initHistory(history_ptr);

    int option;
    char name[NAME_LENGTH] , id[ID_LENGTH];
    Student * stu_ptr;

    do
    {
        printf("\t\tMain Menu\n");
        printf("1.Register Student\n");
        printf("2.Drop Student\n");
        printf("3.Undo Last Drop\n");
        printf("4.Search Student\n");
        printf("5.Display Registered Students\n");
        printf("6.Display Waiting Queue\n");
        printf("7.Display Drop History\n");
        printf("8.Exit\n\n\n\n");

        printf("Enter your choice: ");
        scanf("%d",&option);

        switch (option)
        {
        case 1:
            printf("Enter Student name :");
            scanf("%s" , name);
            printf("Enter Student id :");
            scanf("%s" , id);
    
            sizeOFList(registeredStudents_ptr) >= ACCOMMODATIONS  
                ? enqueue(waitingQueue_ptr , makeStudent(id , name))
                : addRegisteredStudent(registeredStudents_ptr , makeStudent(id , name)) ;

            break;
        
        case 2:
            printf("Enter Student id :");
            scanf("%s" , id);
            
            stu_ptr = searchStu(registeredStudents_ptr , id);
            if ( stu_ptr == NULL) break;
            Student tmp = *stu_ptr;
            removeRegisteredStudent(registeredStudents_ptr , tmp);
            pushHistory(history_ptr , tmp);
            
            !isQueueEmpty(waitingQueue_ptr) 
                ? addRegisteredStudent(registeredStudents_ptr , dequeue(waitingQueue_ptr))
                : NULL;
            break;
        case 3:
            if(isHistoryEmpty(history_ptr)){
                printf("History is Empty\n");
                break;
            }
            *stu_ptr = popHistory(history_ptr);
            
            sizeOFList(registeredStudents_ptr) <= ACCOMMODATIONS && stu_ptr != NULL
                ? addRegisteredStudent(registeredStudents_ptr , *stu_ptr)
                : NULL;

            break;
        case 4:
            printf("Enter Student id to search:");
            scanf("%s" , id);

            stu_ptr = searchStu(registeredStudents_ptr , id);
            if(stu_ptr == NULL){
                break;
            }
            
            printf("Student Found !\n");
            printf("{\n\tID : %s\n\t Name : %s\n}\n" , stu_ptr->id , stu_ptr->name);          
            break;
        case 5: 
            displayRegStu(registeredStudents_ptr);
            break;
        case 6:
            displayQueue(waitingQueue_ptr);
            break;
        case 7:
            displayHistory(history_ptr);
            break;
        default:
            printf("Please Enter a valid option 1 to 8\n");
            break;
        }
    } while (option != 8);
    
    
    return 0;
}

void initRegList(RegList * list){
    list->head = NULL;
}

Student makeStudent( char id[],  char name[]) {
    Student stu;
    strcpy(stu.id , id);
    strcpy(stu.name  , name);
    return stu;
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

    if (strcmp(curr->student.id , stu.id) == 0) {
        list->head = curr->next; 
        free(curr);         
        return;
    }

    while (curr != NULL && strcmp(curr->student.id , stu.id) != 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) return;
    if(curr->next == NULL) prev->next = NULL;
    prev->next = curr->next;
    free(curr);
}

Student* searchStu(RegList* list ,  char id[]){
    struct StudentNode *tmp = list->head;

    while (tmp != NULL) {
        if (strcmp(tmp->student.id , id) == 0) return &(tmp->student);
        tmp = tmp->next; 
    }
    return NULL;
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

int sizeOFList(RegList * l){
    struct StudentNode * tmp = l->head;
    int count = 0;
    while (tmp != NULL){
        count++;
        tmp = tmp->next; 
    }
    return count;
    
}

// Waiting Queue (Linked List-Based Queue)

void initQueue(WaitingQueue * q){
    q->front = q->rear =NULL;
}

void enqueue(WaitingQueue * q , Student stu){
    struct StudentNode * nw  =(struct StudentNode *)malloc(sizeof(struct StudentNode));
    nw->student = stu;
    nw->next=NULL;

    if (q->front == NULL){
        q->front = nw;
        q->rear = nw;
        return;
    }

    q->rear->next= nw;
    q->rear = nw;

}

Student dequeue(WaitingQueue * q ){
    if(q->front == NULL) return (Student){0};

    struct StudentNode *tmp = q->front;
    Student student = tmp->student; 

    q->front = q->front->next;

    if (q->front == NULL) q->rear = NULL;

    free(tmp);
    return student;

}


void displayQueue(WaitingQueue* q){
    printf("\n/---------- Waiting Queue ---------- /\n");
    struct StudentNode * tmp = q->front;

    if (tmp ==NULL)printf("\t Queue Is Empty");
    int x = 1;
    
    while (tmp != NULL) {
        printf("%d). { Id: %s, Name: %s }\n", x++ , tmp->student.id, tmp->student.name);
        tmp = tmp->next;
    }
    
    printf("\n/-------------- END -------------- /\n\n");
}

bool isQueueEmpty(WaitingQueue *q){
    return q->front == NULL ? true :false;
}


// Drop History Stack (Linked List-Based Stack)

void initHistory(History *h){
    h->top = NULL;
}

void pushHistory(History * h , Student stu){
    struct StudentNode * nw = (struct StudentNode*)malloc(sizeof(struct StudentNode));
    nw->student = stu;
    nw->next = h->top;
    h->top = nw;
}

Student popHistory(History * h){
    // if(h->top == NULL) return NULL;
    struct StudentNode * node = h->top;
    Student stu = h->top->student;
    h->top = h->top->next;
    free(node);
    return stu;
}

void displayHistory(History* h){
    printf("\n/---------- Drop History ---------- /\n");
    struct StudentNode * tmp = h->top;

    if (tmp ==NULL)printf("\t History Is Empty");
    int x = 1;
    
    while (tmp != NULL) {
        printf("%d). { Id: %s, Name: %s }\n", x++ , tmp->student.id, tmp->student.name);
        tmp = tmp->next;
    }
    
    printf("\n/-------------- END -------------- /\n\n");
}

bool isHistoryEmpty(History * h){
    return h->top == NULL ? true : false;
}