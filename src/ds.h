#ifndef _DS_H_
#define _DS_H_

#include "util.h"

int max(int a, int b);

struct Treap {
    struct Treap *lc, *rc;
    int sz, key, pri;
    int val;
};

int Sz(struct Treap* t);

void pull(struct Treap* t);

struct Treap* merge(struct Treap* a, struct Treap* b);

void split_by_key(struct Treap** t, int k, struct Treap** a, struct Treap** b);

void split_by_sz(struct Treap** t, int k, struct Treap** a, struct Treap** b);

void treap_init(struct Treap* t, int key, int val);

void insert_new(struct Treap** root, int key, int val);

void pop_begin(struct Treap** root);

int do_begin(struct Treap* now);

struct Node {
    struct Node* nxt;
    struct Node* pre;
    struct Process* val;
};

struct Queue {
    struct Node *head, *tail;
};

void init_queue(struct Queue *que);

int empty(struct Queue *que);

void push(struct Queue *que, struct Process *p);

struct Process* front(struct Queue *que);

void pop(struct Queue *que);

#endif // _DS_H_
