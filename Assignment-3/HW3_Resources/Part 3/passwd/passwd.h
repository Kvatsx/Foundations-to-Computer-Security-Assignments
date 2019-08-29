#ifndef PASSWD_H
#define PASSWD_H
/* This technique is used so that even if you include your file million times
 * It gets included only once.. It's called the once pattern (I guess) */

#include<stdio.h>

int register_user(char *, char *);
int auth_user(char *, char *);

/* dont add any more public functions unless you really need to */


#endif /* end of include guard: PASSWD_H */
