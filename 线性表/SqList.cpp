/*线性表顺序表示和实现*/
#include "../public/HEADERS.H"
typedef int ElemType;
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量
#define LISTINCREMENT 10 //线性表存储空间的分配增量
typedef struct{
    ElemType *elem; //存储空间基址
    int length;     //当前长度
    int listsize;   //当前分配的存储容量（以sizeof(ElemType)为单位）
}SqList;

Status InitList_Sq(SqList &L)
{
    L.elem = (ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
    if(!L.elem)
        exit(_OVERFLOW);
    L.length = 0;
    L.listsize = LIST_INIT_SIZE;
    return OK;
}// InitList_Sq

Status DestroyList_Sq(SqList &L)
{
    free(L.elem);
    L.elem = NULL;
    L.length = 0;
    L.listsize = 0;
    return OK;
}// DestroyList_Sq

Status ClearList_Sq(SqList &L)
{
    L.length = 0;
    return OK;
}// ClearList_Sq

Status ListEmpty_Sq(SqList L)
{
    if(L.length == 0)
    return TRUE;
    else
    return FALSE;
}// ListEmpty_Sq

int ListLength_Sq(SqList L)
{
    return L.length;
}// ListLength_Sq

Status GetElem_Sq(SqList L,int i,ElemType &e)
{
    if(i < 1||i > L.length)
        exit(ERROR);
    e = *(L.elem + i - 1);// 下标从0开始
    return OK;
}// GetElem_Sq

int LocateElem_Sq(SqList L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    ElemType *p;
    int i = 1;
    p = L.elem;
    while(i <= L.length&&!compare(*p++,e))
        ++i;
    if(i<=L.length)
        return i;
    else
        return 0;
}// LocateElem_Sq

Status PriorElem_Sq(SqList L,ElemType cur_e,ElemType &pre_e)
{
    int i = 2;
    ElemType *p = L.elem + 1;
    while(i <= L.length&&*p!=cur_e)
    {
        p++;
        i++;
    }
    if(i > L.length)
    {
        return INFEASIBLE;
    }
    else
    {
        pre_e = *--p;
        return OK;
    }
}// PriorElem_Sq

Status NextElem_Sq(SqList L, ElemType cur_e,ElemType &next_e)
{
    int i = 1;
    ElemType *p = L.elem;
    while(i <= L.length&&*p!=cur_e)
    {
        i++;
        p++;
    }
    if(i == L.length)
        return INFEASIBLE;
    else
    {
        next_e = *++p;
        return OK;
    }
}// NextElem_Sq

Status ListInsert_Sq(SqList &L,int i,ElemType e )
{
    ElemType *newbase,*q,*p;
    if(i < 1||i > L.length + 1)
        return ERROR;
    if(L.length >= L.listsize)
    {
        if(!(newbase = (ElemType *)realloc(L.elem,(L.listsize + LISTINCREMENT)*sizeof(ElemType))))
            exit(_OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;
    }
    q = &(L.elem[i-1]);
    for(p = &(L.elem[L.length - 1]);p >= q;--p)
        *(p + 1) = *p;
    *q = e;
    ++L.length;
    return OK;
}// ListInsert_Sq

Status ListDelete_Sq(SqList &L,int i,ElemType &e)
{
    ElemType *p,*q;
    if(i < 1||i > L.length)
        return ERROR;
    p = &(L.elem[i - 1]);
    e = *p;
    q = L.elem + L.length - 1;
    for(++p;p <= q;++p)
        *(p - 1) = *p;
    --L.length;
    return OK;
}// ListDelete_Sq

Status ListTraverse_Sq(SqList L,void(*vi)(ElemType&))
{
    ElemType *p;
    int i;
    p = L.elem;
    for(i = 1;i <= L.length;i++)
        vi(*p++);
    cout<<endl;
    return OK;
}// ListTraverse_Sq

int main()
{
    // test 1 InitList
    SqList L;
    if(InitList_Sq(L))
    {
        puts("InitList_Sq Success!");
        printf("length=%d listsize=%d\n",L.length,L.listsize);
    }
    else puts("InitList_Sq Failure!");
    // test 2 DestroyList
    if(DestroyList_Sq(L))
    {
        puts("DestroyList_Sq Success!");
        printf("length=%d listsize=%d\n",L.length,L.listsize);
    }

    return 0;
}
