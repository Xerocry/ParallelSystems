#ifndef MY_RANDOM_H
#define MY_RANDOM_H


#define NULL 0

#define EINVAL 23

typedef int int32_t;


struct random_data
{
    int32_t *fptr;      /* Front pointer.  */
    int32_t *rptr;      /* Rear pointer.  */
    int32_t *state;     /* Array of state values.  */
    int rand_type;      /* Type of random number generator.  */
    int rand_deg;       /* Degree of random number generator.  */
    int rand_sep;       /* Distance between front and rear.  */
    int32_t *end_ptr;       /* Pointer behind state table.  */
};


#define errno my_errno
extern int my_errno;

static inline void __set_errno(int err) { my_errno = err; };

int random_r (struct random_data *buf, int32_t *result);

int myrandom(void);
void init_myrandom();

#endif