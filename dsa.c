#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define list_size 5

typedef struct student{
    char id[10];
    char name[10];
}student;

struct node{
    struct student data;
    struct node *next;
}node;

typedef struct list{
    struct node *header;
}list;

int regCount = 0;

void initialize(list *l);
int isEmpty(list *l);
void regStudent(list *l , char id[10] ,char name[10]);
void removeStudent(list *l , char id[10]);
int search(list *l);
void display(list *l);

int main(){

    list lt;
    initialize(&lt);

    int choose;
    do{
        
        printf("\t\tMain Menu\n");
        printf("1.Register Student\n");
        printf("2.Drop Student\n");
        printf("3.Undo Last Drop\n");
        printf("4.Search Student\n");
        printf("5.Display Registered Students\n");
        printf("6.Display Waiting Queue\n");
        printf("7.Display Drop History\n");
        printf("8.Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choose);

        if(choose==1){
            printf("Register Student........\n");
            char id[10];
            char name[10];
            
            printf("Enter Student ID: ");
            scanf("%s",id);
            printf("Enter Student Name: ");
            scanf("%s",name);

            regStudent(&lt,id,name);
        
        }
        else if(choose==2){
            printf("Drop Student.........\n");
        }
        else if(choose==3){
            printf("Undo Last Drop.........\n");
        }
        else if(choose==4){
            printf("Search Student.........\n");
        }
        else if(choose==5){
            printf("Display Registered Students.........\n");
            display(&lt);
        }
        else if(choose==6){
            printf("Display Waiting Queue.........\n");
        }
        else if(choose==7){
            printf("Display Drop History.........\n");
        }
        else if(choose==8){
            printf("Exit.........\n");
        }
        else{
            printf("Invalid Enter\n");
        }
    }while(choose!=8);

    return 0;
}

void initialize(list *l){
    l->header = NULL;
}

int isEmpty(list *l){
    return l->header == NULL;
}

void regStudent(list *l , char id[10] ,char name[10]){
    struct node *nw ,*tmp;
    nw = (struct node*)malloc(sizeof(struct node));

    strcpy(nw->data.id , id);
    strcpy(nw->data.name , name);
    nw->next = NULL;
	
    tmp = l->header;

    if(regCount < 5){
        if(isEmpty(l)){
            l->header = nw;
        }
        else{
            while(tmp->next != NULL)
                tmp = tmp->next;
                
            tmp->next = nw;
        }
        regCount++;
    }
}

void display(list *l){
    struct node *tmp = l->header;
    printf("\n Display Registration Students Details\n");

    while(tmp!=NULL){
        printf("Student Id: %s\n",tmp->data.id);
        printf("Student Name: %s\n\n",tmp->data.name);

        tmp = tmp->next;
    }
}

void removeStudent(list *l , char id[10]){

}