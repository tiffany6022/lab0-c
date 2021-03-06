#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    if (!q)
        return;
    if (!q->head) {
        free(q);
        return;
    }

    while (q->head->next) {
        list_ele_t *temp = q->head->next;
        free(q->head->value);
        free(q->head);
        q->head = temp;
    }
    /* Free queue structure */
    free(q->head->value);
    free(q->head);
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = malloc(strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }

    strncpy(newh->value, s, (strlen(s) + 1));
    newh->next = q->head;

    if (!q->head)
        q->tail = newh;
    q->head = newh;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q)
        return false;
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    newt->value = malloc(strlen(s) + 1);
    if (!newt->value) {
        free(newt);
        return false;
    }

    strncpy(newt->value, s, (strlen(s) + 1));
    newt->next = NULL;

    if (!q->head)
        q->head = newt;
    if (q->tail)
        q->tail->next = newt;
    q->tail = newt;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return false;

    if (sp) {
        if (strlen(q->head->value) < bufsize) {
            strncpy(sp, q->head->value, (strlen(q->head->value) + 1));
        } else {
            strncpy(sp, q->head->value, (bufsize - 1));
            sp[bufsize - 1] = '\0';
        }
    }

    list_ele_t *temp = q->head->next;
    free(q->head->value);
    free(q->head);
    q->head = temp;
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return;

    list_ele_t *_prev = NULL;
    list_ele_t *_curr = q->head;
    list_ele_t *_next = q->head->next;
    q->tail = _curr;
    while (_next) {
        _curr->next = _prev;
        _prev = _curr;
        _curr = _next;
        _next = _curr->next;
    }
    _curr->next = _prev;
    q->head = _curr;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    list_ele_t *temp, *head;
    if (strcasecmp(l1->value, l2->value) < 0) {
        temp = l1;
        l1 = l1->next;
    } else {
        temp = l2;
        l2 = l2->next;
    }
    head = temp;

    while (l1 && l2) {
        if (strcasecmp(l1->value, l2->value) < 0) {
            temp->next = l1;
            temp = temp->next;
            l1 = l1->next;
        } else {
            temp->next = l2;
            temp = temp->next;
            l2 = l2->next;
        }
    }

    if (l1)
        temp->next = l1;
    if (l2)
        temp->next = l2;

    return head;
}

list_ele_t *mergeSortList(list_ele_t *head)
{
    if (!head || !head->next)
        return head;

    list_ele_t *slow = head;
    list_ele_t *fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;

    list_ele_t *l1 = mergeSortList(head);
    list_ele_t *l2 = mergeSortList(fast);

    return merge(l1, l2);
}

void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    /* https://npes87184.github.io/2015-09-12-linkedListSort/ */
    if (!q || !q->head)
        return;

    q->head = mergeSortList(q->head);
    list_ele_t *temp = q->head;
    while (temp->next) {
        temp = temp->next;
    }
    q->tail = temp;
}
