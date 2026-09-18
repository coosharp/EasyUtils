/**
 * @file u_shell.h
 *
 */
  
#ifndef _U_SHELL_H
#define _U_SHELL_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stddef.h>
#include <stdint.h>
#include <string.h>
/*********************
 *      MACROS
 *********************/
#define U_SHELL_MEMSET(dst, val, len)   memset((dst), (val), (len))
/*********************
 *      DEFINE
 *********************/
#define U_SHELL_MAX_CMD_LEN     128
#define U_SHELL_MAX_CMD_ARGS    8
#define U_SHELL_PROMPT          "$$ "
/*********************
 *    DECLARATIONS
 *********************/
typedef void (* u_shell_print_fn_t)(const char * str);
typedef int (* u_shell_cmd_cb_fn_t)(int argc, char ** argv);

struct u_shell_cmd
{
        u_shell_cmd_cb_fn_t cb;
        const char * name;
        const char * desc;
};

void u_shell_init(const struct u_shell_cmd * cmd_list, 
                  uint32_t cmd_cnt,
                  u_shell_print_fn_t print);
void u_shell_loop(const char * str, size_t len);


#ifdef __cplusplus
}
#endif

#endif /*_U_SHELL_H*/


/******************************* (END OF FILE) *********************************/




