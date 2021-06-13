typedef struct List
{
    int count;
    int capacity;
    char ** list;
} List;

List * initList();
void addElement(List * list, char * element);
char getElement(List * list, char * element);
void freeList(List * list);