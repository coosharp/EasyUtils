/**
 * @file u_log.h
 *
 */
  
#ifndef _U_LOG_H
#define _U_LOG_H


#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
/*********************
 *      DEFINES
 *********************/
#define U_LOG_ENABLE        (1)
#define U_LOG_COLOR_ENABLE  (1)
#define U_LOG_BUFFER_SIZE   (128)

#define U_LOG_LEVEL_TRACE   0     /* 最低级别，用于最详细的跟踪信息 */
#define U_LOG_LEVEL_INFO    1     /* 重要状态信息，测试阶段使用 */
#define U_LOG_LEVEL_WARN    2     /* 警告信息，提示潜在问题 */
#define U_LOG_LEVEL_ERROR   3     /* 错误信息，功能异常但可恢复 */
#define U_LOG_LEVEL_FATAL   4     /* 严重错误，系统可能崩溃 */
#define U_LOG_LEVEL_NONE    5     /* 不输出日志 */


#define U_LOG_LEVEL         (U_LOG_LEVEL_TRACE)

#define U_LOG_COLOR_RED     "\033[31m"
#define U_LOG_COLOR_GREEN   "\033[32m"
#define U_LOG_COLOR_YELLOW  "\033[33m"
#define U_LOG_COLOR_BLUE    "\033[34m"
#define U_LOG_COLOR_MAGENTA "\033[35m"
#define U_LOG_COLOR_CYAN    "\033[36m"
#define U_LOG_COLOR_WHITE   "\033[37m"
#define U_LOG_COLOR_RESET   "\033[0m"


#define U_LOG_COLOR_TRACE   U_LOG_COLOR_CYAN
#define U_LOG_COLOR_INFO    U_LOG_COLOR_GREEN
#define U_LOG_COLOR_WARN    U_LOG_COLOR_YELLOW
#define U_LOG_COLOR_ERROR   U_LOG_COLOR_RED
#define U_LOG_COLOR_FATAL   U_LOG_COLOR_MAGENTA
#define U_LOG_COLOR_USER    U_LOG_COLOR_WHITE


/**********************
 *      TYPEDEFS
 **********************/
typedef void (* u_log_printf_t)(const char * buf, size_t len);
/**********************
*  GLOBAL PROTOTYPES
 **********************/
void u_log_init         (u_log_printf_t callback);
void u_log_deinit       (void);
void u_log_write        (const char * fmt, ...);

/**********************
 *      MACROS
 **********************/
#if U_LOG_ENABLE
    #define U_LOG_OUTPUT(fmt, ...)        u_log_write(fmt, ##__VA_ARGS__)
#else
    #define U_LOG_OUTPUT(fmt, ...)        do {} while (0)
#endif


#ifndef U_LOG_TRACE
    #if U_LOG_LEVEL <= U_LOG_LEVEL_TRACE
        #if U_LOG_COLOR_ENABLE
            #define U_LOG_TRACE(fmt, ...)  U_LOG_OUTPUT(U_LOG_COLOR_TRACE "[Trace] [%s:%d] " fmt U_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define U_LOG_TRACE(fmt, ...)  U_LOG_OUTPUT("[Trace] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define U_LOG_TRACE(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef U_LOG_INFO
    #if U_LOG_LEVEL <= U_LOG_LEVEL_INFO
        #if U_LOG_COLOR_ENABLE
            #define U_LOG_INFO(fmt, ...)   U_LOG_OUTPUT(U_LOG_COLOR_INFO "[Info ] [%s:%d] " fmt U_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define U_LOG_INFO(fmt, ...)   U_LOG_OUTPUT("[Info ] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define U_LOG_INFO(fmt, ...)       do {} while (0)
    #endif
#endif

#ifndef U_LOG_WARN
    #if U_LOG_LEVEL <= U_LOG_LEVEL_WARN
        #if U_LOG_COLOR_ENABLE
            #define U_LOG_WARN(fmt, ...)   U_LOG_OUTPUT(U_LOG_COLOR_WARN "[Warn ] [%s:%d] " fmt U_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define U_LOG_WARN(fmt, ...)   U_LOG_OUTPUT("[Warn ] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define U_LOG_WARN(fmt, ...)       do {} while (0)
    #endif
#endif

#ifndef U_LOG_ERROR
    #if U_LOG_LEVEL <= U_LOG_LEVEL_ERROR
        #if U_LOG_COLOR_ENABLE
            #define U_LOG_ERROR(fmt, ...)   U_LOG_OUTPUT(U_LOG_COLOR_ERROR "[Error] [%s:%d] " fmt U_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define U_LOG_ERROR(fmt, ...)   U_LOG_OUTPUT("[Error] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define U_LOG_ERROR(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef U_LOG_FATAL
    #if U_LOG_LEVEL <= U_LOG_LEVEL_FATAL
        #if U_LOG_COLOR_ENABLE
            #define U_LOG_FATAL(fmt, ...)   do { U_LOG_OUTPUT(U_LOG_COLOR_FATAL "[Fatal] [%s:%d] " fmt U_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); while(1); } while(0)
        #else
            #define U_LOG_FATAL(fmt, ...)   do { U_LOG_OUTPUT("[Fatal] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); while(1); } while(0)
        #endif
    #else
        #define U_LOG_FATAL(fmt, ...)      do {} while (0)
    #endif
#endif

#ifndef U_LOG_USER
    #if U_LOG_ENABLE
        #if U_LOG_COLOR_ENABLE
            #define U_LOG_USER(fmt, ...)   U_LOG_OUTPUT(U_LOG_COLOR_USER "[User ] [%s:%d] " fmt U_LOG_COLOR_RESET "\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #else
            #define U_LOG_USER(fmt, ...)   U_LOG_OUTPUT("[User] [%s:%d] " fmt"\r\n", __FUNCTION__, __LINE__, ##__VA_ARGS__)
        #endif
    #else
        #define U_LOG_USER(fmt, ...)       do {} while (0)
    #endif
#endif


#ifndef pr_log
    #define pr_log      U_LOG_OUTPUT
#endif

#ifndef pr_trace
    #define pr_trace    U_LOG_TRACE
#endif

#ifndef pr_info
    #define pr_info     U_LOG_INFO
#endif

#ifndef pr_warn
    #define pr_warn     U_LOG_WARN
#endif

#ifndef pr_error
    #define pr_error    U_LOG_ERROR
#endif

#ifndef pr_fatal
    #define pr_fatal    U_LOG_FATAL
#endif

#ifndef pr_user
    #define pr_user     U_LOG_USER
#endif



#ifdef __cplusplus
}
#endif

#endif /*_U_LOG_H*/


/******************************* (END OF FILE) *********************************/


