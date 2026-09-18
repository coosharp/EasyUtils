/**
 * @file u_log.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "u_log.h"
/**********************
 *  STATIC VARIABLES
 **********************/
static u_log_printf_t fnLogCallback = NULL;
static char ucLogBuf[U_LOG_BUFFER_SIZE];
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void u_log_init(u_log_printf_t callback)
{
        fnLogCallback = callback;
}

void u_log_deinit(void)
{
        fnLogCallback = NULL;
}

void u_log_write(const char * fmt, ...)
{
        va_list args;
        va_start(args, fmt);

        if (fnLogCallback != NULL) {
                int len = vsnprintf(ucLogBuf, sizeof(ucLogBuf), fmt, args);
                fnLogCallback(ucLogBuf, len);
        }

        va_end(args);
}


/******************************* (END OF FILE) *********************************/



 







