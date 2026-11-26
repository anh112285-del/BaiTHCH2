#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char hoten[30];
    int masv;
    float d1, d2, d3;
} Data;

typedef struct tagNode {
    Data infor;
    struct tagNode *link;
} Node;

typedef struct {
    Node *pHead;
    Node *pTail;
    int spt;
} LList;

void initList(LList *L) { L->pHead = L->pTail = NULL; L->spt = 0; }
int emptyList(LList L) { return L.spt == 0; }

Node* makeNode(Data x)
{
    Node *pp = (Node*) malloc(sizeof(Node));
    if (pp == NULL) return NULL;
    pp->infor = x;
    pp->link = NULL;
    return pp;
}

void insert_Head(LList *L, Data x)
{
    Node *pp = makeNode(x);
    if (pp == NULL) return;
    if (emptyList(*L)) L->pHead = L->pTail = pp;
    else { pp->link = L->pHead; L->pHead = pp; }
    L->spt++;
}

void insert_Tail(LList *L, Data x)
{
    Node *pp = makeNode(x);
    if (pp == NULL) return;
    if (emptyList(*L)) L->pHead = L->pTail = pp;
    else { L->pTail->link = pp; L->pTail = pp; }
    L->spt++;
}

int insert_After(LList *L, int ma, Data x)
{
    Node *q = L->pHead;
    while (q != NULL && q->infor.masv != ma) q = q->link;
    if (q == NULL) return 0;
    Node *pp = makeNode(x);
    if (pp == NULL) return 0;
    pp->link = q->link;
    q->link = pp;
    if (q == L->pTail) L->pTail = pp;
    L->spt++;
    return 1;
}

int delete_Head(LList *L)
{
    if (emptyList(*L)) return 0;
    Node *p = L->pHead;
    L->pHead = p->link;
    if (L->pHead == NULL) L->pTail = NULL;
    free(p);
    L->spt--;
    return 1;
}

int delete_Tail(LList *L)
{
    if (emptyList(*L)) return 0;
    if (L->pHead == L->pTail) return delete_Head(L);
    Node *q = L->pHead;
    while (q->link != L->pTail) q = q->link;
    free(L->pTail);
    q->link = NULL;
    L->pTail = q;
    L->spt--;
    return 1;
}

int delete_Ma(LList *L, int ma)
{
    Node *prev = NULL, *cur = L->pHead;
    while (cur != NULL && cur->infor.masv != ma) { prev = cur; cur = cur->link; }
    if (cur == NULL) return 0;
    if (prev == NULL) return delete_Head(L);
    prev->link = cur->link;
    if (cur == L->pTail) L->pTail = prev;
    free(cur);
    L->spt--;
    return 1;
}

Node* search_Ma(LList L, int ma)
{
    Node *p = L.pHead;
    while (p != NULL && p->infor.masv != ma) p = p->link;
    return p;
}

float dtb(Data x) { return (x.d1 + x.d2 + x.d3) / 3; }

void sort_DTB(LList *L)
{
    Node *i, *j;
    Data tmp;
    for (i = L->pHead; i != NULL; i = i->link)
        for (j = i->link; j != NULL; j = j->link)
            if (dtb(i->infor) < dtb(j->infor)) {
                tmp = i->infor; i->infor = j->infor; j->infor = tmp;
            }
}

void freeList(LList *L)
{
    Node *p = L->pHead, *t;
    while (p != NULL) { t = p; p = p->link; free(t); }
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

void processList(LList L)
{
    if (emptyList(L)) { printf("Danh sach rong\n"); return; }
    for (Node *p = L.pHead; p != NULL; p = p->link) in(p->infor);
}

int main()
{
    LList L;
    int kt = 0, chon, ma;
    Data x;
    Node *p;
    initList(&L);
    do {
        printf("\nChuong trinh lam viec voi DSLK don SV\n");
        printf("\n1: Them nut vao dau danh sach");
        printf("\n2: Them nut vao cuoi danh sach");
        printf("\n3: Them nut vao sau mot nut khac");
        printf("\n4: Xoa nut dau");
        printf("\n5: Xoa nut cuoi");
        printf("\n6: Xoa nut theo ma sv");
        printf("\n7: Tim sv theo ma");
        printf("\n8: Sap xep theo diem TB (giam dan)");
        printf("\n9: Duyet ds");
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
        case 0:
            printf("Bye bye\n");
            freeList(&L);
            kt = 1;
            break;
        }
    } while (kt == 0);
    return 0;
}

