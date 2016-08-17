#ifndef QUATERNION_H
#define QUATERNION_H

#include <stdio.h>
#include <stdlib.h>

#define LOC {printf("[%s:%s:%d]\n",__FILE__,__FUNCTION__,__LINE__); fflush(NULL);}
#define LOC_P(P) {printf("[%s:%s:%d] %p\n",__FILE__,__FUNCTION__,__LINE__,(P)); fflush(NULL);}

typedef float qel_t; /**< Quaternion element */

struct _quaternion
{
    qel_t a; /**< ones component */
    qel_t b; /**< i component */
    qel_t c; /**< j component */
    qel_t d; /**< k component */
};

typedef struct _quaternion Q[1];

/*
 * @brief Initializes a quaternion to zero.
 *
 * @param q[in,out] - the quaternion to be initilialized
 */
void q_init ( Q q );

/*
 * @brief Initializes a quaternion to one.
 *
 * @param q[in,out] - the quaternion to be initilialized
 */
void q_set_1 ( Q q );

/*
 * @brief Initializes a quaternion to i.
 *
 * @param q[in,out] - the quaternion to be initilialized
 */
void q_set_i ( Q q );

/*
 * @brief Initializes a quaternion to j.
 *
 * @param q[in,out] - the quaternion to be initilialized
 */
void q_set_j ( Q q );

/*
 * @brief Initializes a quaternion to k.
 *
 * @param q[in,out] - the quaternion to be initilialized
 */
void q_set_k ( Q q );

/*
 * @brief Initializes a quaternion to specific values.
 *
 * @param q[in,out] - the quaternion to be initilialized
 * @param a[in] - sets the ones place
 * @param b[in] - sets the i place
 * @param c[in] - sets the j place
 * @param d[in] - sets the k place
 */
void q_set ( Q q, qel_t a, qel_t b, qel_t c, qel_t d );


/*
 * @brief Prints a quaternion as a four tuple
 *
 * @param q[in] - the quaternion to be printed
 */
void q_print ( Q q );

/*
 * @brief Prints a quaternion as a four tuple with a label with
 *        format 'x=(a,b,c,d)' ending with a return character.
 *
 * @param q[in] - the quaternion to be printed
 * @param x[in] - the label of the quaternion
 */
void q_print_label ( Q q, char * x );


/*
 * @brief Adds two quaternions, component-wise.
 *
 * @param a[in,out] - the sum of the quaternions
 * @param x[in] - the quaternion summand
 * @param y[in] - the quaternion summand
 */
void q_add ( Q a, Q x, Q y );

/*
 * @brief Subtracts two quaternions, component-wise,
 *        as a = x-y.
 *
 * @param a[in,out] - the difference of the quaternions
 * @param x[in] - the quaternion from which to be subtracted
 * @param y[in] - the quaternion to subract
 */
void q_sub ( Q a, Q x, Q y );

/*
 * @brief Multiplies two quaternions, based on the rules
 *        multiplying i, j, and k.
 *
 * @param a[in,out] - the product of the quaternions
 * @param x[in] - the quaternion multiplicand.
 * @param y[in] - the quaternion multiplicand.
 */
void q_mul ( Q a, Q x, Q y );

/*
 * @brief Divide two quaternions, with a = x/y, based on
 *        multiplying i, j, and k.
 *
 * @param a[in,out] - the division of the quaternions
 * @param x[in] - the quaternion to be divided.
 * @param y[in] - the quaternion to divide.
 */
void q_div ( Q a, Q x, Q y );

/*
 * @brief Inverts a quaternion, where a = Inv(x), based on
 *        multiplying i, j, and k.
 *
 * @param a[in,out] - the inversion of x
 * @param x[in] - the quaternion to be inverted.
 */
void q_inv ( Q a, Q x );


/*
 * @brief Determines if a quaternion is zero, component wise.
 *
 * @param x[in] - the quaternion to be checked.
 */
int q_is_zero( Q x );

#endif
