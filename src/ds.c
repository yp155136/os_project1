#include "ds.h"

int max(int a, int b) {
    return a > b ? a : b;
}

int Sz(struct Treap* t) {
    return t ? t->sz : 0;
}

void pull(struct Treap* t) {
    if (!t) return;
    t->sz = Sz(t->lc) + Sz(t->rc) + 1;
}

struct Treap* merge(struct Treap* a, struct Treap* b) {
    if (!a || !b) return a ? a : b;
    else if (a->pri > b->pri) {
        a->rc = merge(a->rc, b);
        pull(a);
        return a;
    }
    else {
        b->lc = merge(a, b->lc);
        pull(b);
        return b;
    }
}

void split_by_key(struct Treap** t, int k, struct Treap** a, struct Treap** b) {
    if ((*t) == NULL) {
        *a = *b = NULL;
    }
    else if ((*t)->key <= k) {
        (*a) = (*t);
        split_by_key(&((*t)->rc), k, &((*a)->rc), b);
        pull(*a);
    }
    else {
        (*b) = (*t);
        split_by_key(&((*t)->lc), k, a, &((*b)->lc));
        pull(*b);
    }
}

void split_by_sz(struct Treap** t, int k, struct Treap** a, struct Treap** b) {
    if ((*t) == NULL) {
        *a = *b = NULL;
    }
    else if (Sz((*t)->lc) + 1 <= k) {
        (*a) = (*t);
        split_by_sz(&((*t)->rc), k - Sz((*t)->rc) - 1, &((*a)->rc), b);
        pull(*a);
    }
    else {
        (*b) = (*t);
        split_by_sz(&((*t)->lc), k, a, &((*b)->lc));
        pull(*b);
    }
}

void treap_init(struct Treap* t, int key, int val) {
    t->lc = t->rc = NULL;
    t->key = key; t->sz = 1; t->pri = rand();
    t->val = val;
}

void insert_new(struct Treap** root, int key, int val) {
    if (*root == NULL) {
        // fprintf(stderr, "empty treap\n");
        *root = calloc(1, sizeof(struct Treap));
        treap_init(*root, key, val);
        return;
    }
    // fprintf(stderr, "not empty treap\n");
    struct Treap* t = calloc(1, sizeof(struct Treap));
    treap_init(t, key, val);
    struct Treap *a = NULL, *b = NULL;
    split_by_key(root, key - 1, &a, root);
    split_by_key(root, key, root, &b);
    *root = merge(merge(a, *root), merge(t, b));
}

void pop_begin(struct Treap** root) {
    if (*root == NULL) {
        fprintf(stderr, "pop an empty treap");
        exit(0);
    }
    struct Treap *a;
    split_by_sz(root, 1, &a, root);
}

int do_begin(struct Treap* now) {
    // fprintf(stderr, "key = %d\n", now->key);
    if (now->lc != NULL) {
        // fprintf(stderr, "key = %d\n", now->key);
        // fflush(stderr);
        return do_begin(now->lc);
    }
    else {
        now->key--;
        return now->val;
    }
}

void init_queue(struct Queue *que) {
    que->head = calloc(1, sizeof(struct Node));
    que->tail = calloc(1, sizeof(struct Node));
    que->head->nxt = que->tail;
    que->tail->pre = que->head;
}

int empty(struct Queue *que) {
    if (que->head->nxt == que->tail) {
        return 1;
    }
    else {
        return 0;
    }
}

void push(struct Queue *que, struct Process *p) {
    struct Node *node = calloc(1, sizeof(struct Node));
    node->nxt = que->tail;
    node->pre = que->tail->pre;
    que->tail->pre->nxt = node;
    que->tail->pre = node;
    node->val = p;
}

struct Process* front(struct Queue *que) {
    if (empty(que) == 1) {
        fprintf(stderr, "front an empty queue");
        assert(0);
    }
    return que->head->nxt->val;
}

void pop(struct Queue *que) {
    if (empty(que) == 1) {
        fprintf(stderr, "pop an empty queue");
        assert(0);
    }
    que->head->nxt->nxt->pre = que->head;
    que->head->nxt = que->head->nxt->nxt;
}

