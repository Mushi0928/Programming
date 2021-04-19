#include <stdio.h>
#include <stdlib.h>

typedef struct book{
    int origin_table;
    int current_table;
    struct book* upper;
    struct book* lower;
}Book;
typedef struct table{
    Book* top;
    Book* bottom;
}Table;

Table* tables;
Book* books;
int N;

void init();
void return_top(Book* book);
void move_to_table(Book* book,int tableNum);
void move_onto(Book* bookA,Book* bookB);
void move_over(Book* bookA,Book* bookB);
void pile_onto(Book* bookA,Book* bookB);
void pile_over(Book* bookA,Book* bookB);



int main(){
    scanf("%d",&N);
    init();

    char temp[6];
    int operation = 0;
    int A,B;
    while(1){
        scanf("%s",temp);
        if(temp[0] == 'e')break;
        else if(temp[0] == 'm');
        else if(temp[0] == 'p')operation += 2;

        scanf("%d",&A);

        scanf("%s",temp);
        if(temp[1] == 'n');
        else if(temp[1] == 'v')operation += 1;

        scanf("%d",&B);

        if(books[A].current_table == books[B].current_table){
            operation = 0;
            continue;
        }

        switch(operation){
            case 0:
                move_onto(books + A,books + B);
                break;
            case 1:
                move_over(books + A,books + B);
                break;
            case 2:
                pile_onto(books + A,books + B);
                break;
            case 3:
                pile_over(books + A,books + B);
                break;
        }

        operation = 0;
    }

    for(int i = 0;i<N;i++){
        printf("%d:",i);
        if(tables[i].bottom != NULL){
            Book* temp = tables[i].bottom;
            while(temp != NULL){
                printf(" %d",temp->origin_table);
                temp = temp->upper;
            }
        }
        printf("\n");
    }
    
    return 0;
}
void init(){
    tables = (Table*)malloc(N * sizeof(Table));
    books = (Book*)malloc(N * sizeof(Book));
    for(int i = 0;i<N;i++){
        books[i].origin_table = i;
        books[i].current_table = i;
        books[i].upper = NULL;
        books[i].lower = NULL;
        tables[i].top = books + i;
        tables[i].bottom = books + i;
    }
}
void return_top(Book* book){
    if(book == NULL)return;
    return_top(book->upper);
    move_to_table(book,book->origin_table);
}
void move_to_table(Book* book,int tableNum){
    if(book == NULL)return;

    if(book->lower != NULL){
        (book->lower)->upper = book->upper;
    }else{
        tables[book->current_table].bottom = book->upper;
    }
    if(tables[book->current_table].top == book){
        tables[book->current_table].top = book->lower;
    }

    if(tables[tableNum].bottom == NULL){
        tables[tableNum].bottom = book;
        tables[tableNum].top = book;
        book->current_table = tableNum;
        book->upper = NULL;
        book->lower = NULL;
    }else{
        (tables[tableNum].top)->upper = book;
        book->lower = tables[tableNum].top;
        book->upper = NULL;
        book->current_table = tableNum;
        (tables[tableNum].top) = book;
    }
    printf("book %2d moved to table %2d\n",book->origin_table,book->current_table);
}

void pile_to_table(Book* book,int tableNum){
    Book* new_top = tables[book->current_table].top;

    if(book->lower != NULL){
        (book->lower)->upper = NULL;
        tables[book->current_table].top = book->lower;
    }else{
        tables[book->current_table].bottom = NULL;
        tables[book->current_table].top = NULL;
    }

    if(tables[tableNum].bottom == NULL){
        tables[tableNum].bottom = book;
        book->lower = NULL;    
    }
    if(tables[tableNum].top != NULL){
        (tables[tableNum].top)->upper = book;
        book->lower = tables[tableNum].top;
    }
    tables[tableNum].top = new_top;

    Book* temp = book;
    while(temp != NULL){
        book->current_table = tableNum;
        temp = temp->upper;
    }

    printf("piled book %2d to table %2d\n",book->origin_table,book->current_table);
}
void move_onto(Book* bookA,Book* bookB){
    return_top(bookA->upper);
    return_top(bookB->upper);
    move_to_table(bookA,bookB->current_table);
}
void move_over(Book* bookA,Book* bookB){
    return_top(bookA->upper);
    move_to_table(bookA,bookB->current_table);
}
void pile_onto(Book* bookA,Book* bookB){
    return_top(bookB->upper);
    pile_to_table(bookA,bookB->current_table);
}
void pile_over(Book* bookA,Book* bookB){
    pile_to_table(bookA,bookB->current_table);
}