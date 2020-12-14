#ifndef _UTILS_H_
#define _UTILS_H_ 

#include "macros.h"
#include <stdbool.h>

/**
 * @brief Get true if it is a exception code response that seems to be multiline but is just one line reply.
 * 
 * @param code Pointer to code read. 
 */
bool exceptions_one_line(char *code);



#endif 