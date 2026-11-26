#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char hoten[30];
    int masv;
    float d1, d2, d3;
} Data;

typedef struct tagNode {
    Data infor;
    struct tagNode *prev;
    struct tagNode *next;
} Node;

typedef struct {
    Node *pHead;
    Node *pTail;
    int spt;
} DList;

void initList(DList *L) { L->pHead = L->pTail = NULL; L->spt = 0; }
int emptyList(DList L) { return L.spt == 0; }

Node* makeNode(Data x)
{
    Node *pp = (Node*) malloc(sizeof(Node));
    if (pp == NULL) return NULL;
    pp->infor = x;
    pp->prev = pp->next = NULL;
    return pp;
}

void insert_Head(DList *L, Data x)
{
    Node *pp = makeNode(x);
    if (pp == NULL) return;
    if (emptyList(*L)) L->pHead = L->pTail = pp;
    else {
        pp->next = L->pHead;
        L->pHead->prev = pp;
        L->pHead = pp;
    }
    L->spt++;
}

void insert_Tail(DList *L, Data x)
{
    Node *pp = makeNode(x);
    if (pp == NULL) return;
    if (emptyList(*L)) L->pHead = L->pTail = pp;
    else {
        pp->prev = L->pTail;
        L->pTail->next = pp;
        L->pTail = pp;
    }
    L->spt++;
}

int insert_After(DList *L, int ma, Data x)
{
    Node *q = L->pHead;
    while (q != NULL && q->infor.masv != ma) q = q->next;
    if (q == NULL) return 0;
    Node *pp = makeNode(x);
    if (pp == NULL) return 0;
    pp->prev = q;
    pp->next = q->next;
    if (q->next != NULL) q->next->prev = pp;
    else L->pTail = pp;
    q->next = pp;
    L->spt++;
    return 1;
}

int delete_Head(DList *L)
{
    if (emptyList(*L)) return 0;
    Node *p = L->pHead;
    L->pHead = p->next;
    if (L->pHead == NULL) L->pTail = NULL;
    else L->pHead->prev = NULL;
    free(p);
    L->spt--;
    return 1;
}

int delete_Tail(DList *L)
{
    if (emptyList(*L)) return 0;
    Node *p = L->pTail;
    L->pTail = p->prev;
    if (L->pTail == NULL) L->pHead = NULL;
    else L->pTail->next = NULL;
    free(p);
    L->spt--;
    return 1;
}

int delete_Ma(DList *L, int ma)
{
    Node *cur = L->pHead;
    while (cur != NULL && cur->infor.masv != ma) cur = cur->next;
    if (cur == NULL) return 0;
    if (cur == L->pHead) return delete_Head(L);
    if (cur == L->pTail) return delete_Tail(L);
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    free(cur);
    L->spt--;
    return 1;
}

Node* search_Ma(DList L, int ma)
{
    Node *p = L.pHead;
    while (p != NULL && p->infor.masv != ma) p = p->next;
    return p;
}

float dtb(Data x) { return (x.d1 + x.d2 + x.d3) / 3; }

void sort_DTB(DList *L)
{
    Node *i, *j;
    Data tmp;
    for (i = L->pHead; i != NULL; i = i->next)
        for (j = i->next; j != NULL; j = j->next)
            if (dtb(i->infor) < dtb(j->infor)) {
                tmp = i->infor; i->infor = j->infor; j->infor = tmp;
            }
}

void freeList(DList *L)
{
    Node *p = L->pHead, *t;
    while (p != NULL) { t = p; p = p->next; free(t); }
    initList(L);
}

void nhap(Data *x)
{
    printf("Nhap ma sv (<=0 de huy): ");
    scanf("%d", &(x->masv));
    if (x->masv > 0) {
        printf("Nhap ho ten: ");
        scanf(" %29[^\n]", x->hoten);
        printf("Nhap diem mon 1: "); scanf("%f", &(x->d1));
        printf("Nhap diem mon 2: "); scanf("%f", &(x->d2));
        printf("Nhap diem mon 3: "); scanf("%f", &(x->d3));
    }
}

void in(Data x)
{
    printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 3: %.2f, TB: %.2f\n",
           x.hoten, x.masv, x.d1, x.d2, x.d3, dtb(x));
}

void processList(DList L)
{
    if (emptyList(L)) { printf("Danh sach rong\n"); return; }
    for (Node *p = L.pHead; p != NULL; p = p->next) in(p->infor);
}

void processListReverse(DList L)
{
    if (emptyList(L)) { printf("Danh sach rong\n"); return; }
    for (Node *p = L.pTail; p != NULL; p = p->prev) in(p->infor);
}

int main()
{
    DList L;
    int kt = 0, chon, ma;
    Data x;
    Node *p;
    initList(&L);
    do {
        printf("\nChuong trinh lam viec voi DSLK kep SV\n");
        printf("\n1: Them nut vao dau danh sach");
        printf("\n2: Them nut vao cuoi danh sach");
        printf("\n3: Them nut vao sau mot nut khac");
        printf("\n4: Xoa nut dau");
        printf("\n5: Xoa nut cuoi");
        printf("\n6: Xoa nut theo ma sv");
        printf("\n7: Tim sv theo ma");
        printf("\n8: Sap xep theo diem TB (giam dan)");
        printf("\n9: Duyet ds (xuoi)");
        printf("\n10: Duyet ds (nguoc)");
        printf("\n0: Thoat");
        printf("\nMoi ban chon: ");
        scanf("%d", &chon);
        switch (chon) {
        case 1:
            nhap(&x);
            if (x.masv > 0) insert_Head(&L, x);
            break;
        case 2:
            nhap(&x);
            if (x.masv > 0) insert_Tail(&L, x);
            break;
        case 3:
            printf("Them sau sv co ma: ");
            scanf("%d", &ma);
            nhap(&x);
            if (x.masv > 0 && !insert_After(&L, ma, x))
                printf("Khong tim thay sv co ma %d\n", ma);
            break;
        case 4:
            printf(delete_Head(&L) ? "Da xoa nut dau\n" : "Danh sach rong\n");
            break;
        case 5:
            printf(delete_Tail(&L) ? "Da xoa nut cuoi\n" : "Danh sach rong\n");
            break;
        case 6:
            printf("Nhap ma sv can xoa: ");
            scanf("%d", &ma);
            if (delete_Ma(&L, ma)) printf("Da xoa\n");
            else printf("Khong tim thay sv co ma %d\n", ma);
            break;
        case 7:
            printf("Nhap ma sv can tim: ");
            scanf("%d", &ma);
            p = search_Ma(L, ma);
            if (p != NULL) in(p->infor);
            else printf("Khong tim thay sv co ma %d\n", ma);
            break;
        case 8:
            sort_DTB(&L);
            printf("Da sap xep\n");
            break;
        case 9:
            processList(L);
            break;
        case 10:
            processListReverse(L);
            break;
        case 0:
            printf("Bye bye\n");
            freeList(&L);
            kt = 1;
            break;
        }
    } while (kt == 0);
    return 0;
}
