/**************************************************************************//**
  @file feu_object.c

  @brief Implementation of FEU object handling

  @details

  <em>Copyright (C) 2012, Andrew Kephart (akephart@akephart.org)</em>.
  Permission to use, copy, modify, distribute, and sell this software and its
  documentation for any purpose is hereby granted without fee, provided that
  the above copyright notice appear in all copies and that both that
  copyright notice and this permission notice appear in supporting
  documentation.  No representations are made about the suitability of this
  software for any purpose.  It is provided "as is" without express or 
  implied warranty.
*/
#ifndef _FEU_OBJECT_C_ 
#define _FEU_OBJECT_C_

#include "feu.h"

/**
 * @brief Garbage collector list.  All objects go on this list when allocated.
 */
static feu_list_t feu_object_garbage;


/**************************************************************************//**
 * @brief Initialize a feu object
 *
 * @details This method initializes all of the default fields of a feu
 * object.
 *
 * @param obj Pointer to the object to initialized
 *
 * @remarks
 * */
void
feu_object_init(
    feu_object_t *this
)
{
    /* Step 1: Simple assignments */
    this->name = NULL;
    this->last_property = NULL;
    this->parent = NULL;

    /* Step 2: List inits */
    INIT_FEU_LIST(&this->siblings);
    INIT_FEU_LIST(&this->garbage);
    INIT_FEU_LIST(&this->properties);
    INIT_FEU_LIST(&this->kids);
}

/**************************************************************************//**
 * @brief Allocate a feu object
 *
 * @details Allocate and initialize a new object
 *
 * @returns Newly-prepared object on success, NULL on failure
 *
 * @remarks
 * */
feu_object_t *
feu_object_create(void)
{
    feu_object_t *new;

    /* Step 1: Simple alloc */
    if (NULL == (new = malloc(sizeof(*new)))) return NULL;
    /* Step 2: Callout init */
    feu_object_init(new);

    return new;
}

/**************************************************************************//**
 * @brief Initialize a feu property
 *
 * @details This method initializes all of the default fields of a feu
 * property.
 *
 * @param this Pointer to the property to initialized
 *
 * @remarks
 * */
void
feu_property_init(
    feu_property_t *this
)
{
    /* Step 1: Simple assignments */
    this->name = NULL;
    this->type = FEU_TYPE_ERROR;

    /* Step 2: List inits */
    INIT_FEU_LIST(&this->siblings);
}

/**************************************************************************//**
 * @brief Allocate a feu property
 *
 * @details Allocate and initialize a new property
 *
 * @returns Newly-prepared property on success, NULL on failure
 *
 * @remarks
 * */
feu_property_t *
feu_property_create(void)
{
    feu_property_t *new;

    /* Step 1: Simple alloc */
    if (NULL == (new = malloc(sizeof(*new)))) return NULL;
    /* Step 2: Callout init */
    feu_property_init(new);

    return new;
}

#endif /* _FEU_OBJECT_C_ */
