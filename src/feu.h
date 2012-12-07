/**************************************************************************//**
 * @file feu.h
 *
 * @brief Define our list and stack implementation
 *
 * @details This is, fundamentally, a simplification  of the
 * Linux kernel list routines.  (Go with what you know, eh?)
 * */
#ifndef _FEU_H_
#define _FEU_H_

#include <stdlib.h>
#include <stdio.h>

/**
 * Container/entry ref/deref
 */
#define feu_offset_of(type, member) \
    ((size_t)&((type *)0)->member)

#define feu_container_of(ptr, type, member) ({          \
    const typeof(((type *)0)->member) * __mptr = (ptr); \
    (type *)((char *)__mptr - feu_offset_of(type, member)); })

/**
 * Singly-linked List/stack
 */
typedef struct feu_list {
    struct feu_list *next;
} feu_list_t;
#define FEU_LIST_INIT(_head) { NULL; }
#define FEU_LIST(_head) \
    struct feu_list _head = FEU_LIST_INIT(_head)
#define INIT_FEU_LIST(_head) (_head)->next = NULL;

typedef feu_list_t feu_list_node_t;

static inline void feu_list_prepend(feu_list_t *node, feu_list_t *head)
{
    node->next = head->next;
    head->next = node;
}

#define feu_list_add(__n, __h) feu_list_prepend(__n, __h)

static inline void feu_list_append(feu_list_t *node, feu_list_t *head)
{
    struct feu_list *marker = head;
    while (NULL != marker->next) marker=marker->next;
    marker->next = node;
    node->next = NULL;
}

static inline struct feu_list *feu_list_pop(feu_list_t *head)
{
    struct feu_list *ret = head->next;
    if (NULL==ret) return NULL; 
    head->next = ret->next;
    return ret;
}

/**************************************************************************//**
 * @brief Push a structure onto a stack
 *
 * @details Pushes a structure onto a stack, using the named structure
 * meber for the linkage.  This allows structures to be on multiple stacks.
 *
 * @param __node The larger structure to push
 * @param __member The member in the __node structure to use for linkage
 * @param __stack The head of the stack onto which we'll push
 * */
#define feu_stack_push(__node, __member, __stack) \
    feu_list_prepend(&((__node)->__member), __stack)

/**************************************************************************//**
 * @brief Pop a structure off of a stack
 *
 * @details Pop a structure off of a stack that is using the named member
 * for linkage; returns the specified type.
 *
 * @param __type The type of object to pop
 * @param __member The member of __type used for linkage
 * @param __stack The stack from which to pop.
 * */
#define feu_stack_pop(__type, __member, __stack) ({ \
     struct feu_list *ret = feu_list_pop(&(__stack)); \
     ret?feu_container_of(ret,__type,__member):NULL; })

/**
 * @brief FEU property (attribute)
 * @details A FEU property is a value container, than may itself
 * be contained in other objects. 
 * For our purposes, every property has both a string value and a
 * numeric (float) value.  Most operations will only deal with the
 * float value, however.
 * If "floatValue" is non-NULL, it should point to 'floatStore'; this
 * lets us determine if the value has been set or not.
 * Resist the urge to put a backpointer here.
 */
typedef struct feu_property_s
{
    char *name;      /* Name of this property */
    char *textValue; /* String value of this property */
    float *floatValue; /* Floating-point value of this property */
    float floatStore; /* Storage for actual numeric value */

    feu_list_t siblings;  /* Linkage for object to whom we belong */
} feu_property_t;

/**
 * @brief Generic FEU object.
 * @details For our purposes, a FEU object is a data structure
 * containing some class information (used for management), some
 * lists for holding children, and some nodes for the various kinds
 * of stacks or lists for which objects can be used.
 */

typedef struct feu_object_s
{
    //const struct feu_object_s *class;  /* Class backpointer */

    /* Cache/stash for various bits */
    const char *name; /* If this is a named object, this member is a pointer
                         into the "name" property.  DO NOT FREE THIS. */

    /* Linkages */
    struct feu_object_s *parent; /* parent object backpointer */
    feu_list_t siblings;  /* Chain of storage in parent object */
    feu_list_t garbage; /* Chain of all objects for garbage collection */

    /* Properties stack head */
        /* Each time a property is looked up, it is placed at the head
         * of this stack; this effectively implements a very simple cache
         * scheme.
         */
    feu_list_node_t properties;

    /* Child objects stack head */
        /* Each time a child is looked up, it is placed at the head
         * of this stack; this effectively implements a very simple cache
         * scheme.
         */
    feu_list_node_t kids;
} feu_object_t;


/**
 * Function prototypes 
 */
void feu_object_init(feu_object_t *);
feu_object_t *feu_object_create(void);
void feu_object_destroy(feu_object_t *);
void feu_property_init(feu_property_t *);
feu_property_t *feu_property_create(void);
void feu_property_destroy(feu_property_t *);


#endif /* _FEU_H_ */
