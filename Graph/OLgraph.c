typedef struct Arcbox{
    int tailvex,headvex;
    struct Arcbox *hlink,*tlink;
    int *info;
}Arcbox;
typedef struct Vexnode{
    char data;
    Arcbox *firstin,*firstout;
}Vexnode;
typedef struct {
    Vexnode xlist[20];
    int vexnum,arcnum;
}OLgraph;
