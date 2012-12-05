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

/**
 * Container/entry ref/deref
 */
#define feu_offset_of(type, member) \
    ((size_t)&((type *)0)->member)

#define feu_container_of(ptr, type, member) ({          \
    const typeof(((type *)0)->member) * __mptr = (ptr); \
    (type *)((char *)__mptr - feu_offset_of(type, member)); })
#endif

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
     struct feu_list *ret = feu_list_pop(__stack); \
     ret?feu_container_of(ret,__type,__member):NULL })

/**
 * @brief Enumeration of supported property types
 */
typedef enum feu_type_e
{
    FEU_TYPE_ERROR = 0,
    FEU_TYPE_INTEGER = 1,  /* Native integer size */
    FEU_TYPE_STRING = 2, /* String property */
    FEU_TYPE_FLOAT = 3, /* Floating point value */
    FEU_TYPE_MAX
} feu_type_t;

/**
 * @brief FEU property (attribute)
 * @details A FEU property is a value container, than may itself
 * be contained in other objects.  Note that we only support
 * processor-native numbers here (i.e. no 64-bit integers on
 * 32-bit platforms).
 * Resist the urge to put a backpointer here.
 */
typedef struct feu_property_s
{
    char *name;      /* Name of this property */
    feu_type_t type; /* Type of this property */

    union {
        char *textValue; /* String value of this property */
        int   intValue;  /* Integer value of this property */
        float floatValue; /* Floating-point value of this property */
    } u;

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
    feu_property_t *last_property;  /* Last property we looked up */

    /* Linkages */
    struct feu_object_s *parent; /* parent object backpointer */
    feu_list_t siblings;  /* Chain of storage in parent object */
    feu_list_t garbage; /* Chain of all objects for garbage collection */

    /* Properties */
    feu_list_t properties;

    /* Child objects */
    feu_list_t kids;
} feu_object_t;


/**
 * Function prototypes 
 */
void feu_object_init(feu_object_t *);
feu_object_t *feu_object_create(void);


#endif /* _FEU_H_ */
