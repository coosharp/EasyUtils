/**
 * @file u_shell.c
 *
 */
  
/*********************
 *      INCLUDES
 *********************/
#include "u_shell.h"
/*********************
 *      DEFINE
 *********************/

/* Default characters */
#define U_SHELL_ASCII_NULL      0x00 /*!< Null character */
#define U_SHELL_ASCII_BACKSPACE 0x08 /*!< Backspace */
#define U_SHELL_ASCII_LF        0x0A /*!< Line feed */
#define U_SHELL_ASCII_CR        0x0D /*!< Carriage return */
#define U_SHELL_ASCII_DEL       0x7F /*!< Delete character */
#define U_SHELL_ASCII_SPACE     0x20 /*!< Space character */
/**********************
 *  STATIC PROTOTYPES
 **********************/
static size_t ullIdx = 0;
static char cBuffer[U_SHELL_MAX_CMD_LEN] = {0};
static int32_t iArgc = 0;
static char * pcArgv[U_SHELL_MAX_CMD_ARGS] = {0};
static u_shell_print_fn_t fnPrint = NULL;
static const struct u_shell_cmd * ptCmdList = NULL;
static uint32_t ulCmdCnt = 0;

static void parse_proc(void);
/**********************
 *   GLOBAL FUNCTIONS
 **********************/ 
void u_shell_init(const struct u_shell_cmd * cmd_list, 
                  uint32_t cmd_cnt,
                  u_shell_print_fn_t print)
{
        ptCmdList = cmd_list;
        ulCmdCnt = cmd_cnt;
        fnPrint = print;

        fnPrint(U_SHELL_PROMPT);
}

void u_shell_loop(const char * str, size_t len)
{
        const char * p = str;

        for(size_t idx = 0; idx < len; idx++) {
                switch (p[idx])
                {
                        case U_SHELL_ASCII_CR:
                        case U_SHELL_ASCII_LF:
                        {
                                parse_proc();
                                U_SHELL_MEMSET(cBuffer, 0, sizeof(cBuffer));
                                U_SHELL_MEMSET(pcArgv, 0, sizeof(pcArgv));
                                ullIdx = 0;
                                fnPrint(U_SHELL_PROMPT);
                                break;
                        }

                        case U_SHELL_ASCII_BACKSPACE:
                        case U_SHELL_ASCII_DEL:
                        {
                                if(ullIdx > 0) {
                                        ullIdx -= 1;
                                        cBuffer[ullIdx] = '\0';
                                        fnPrint("\b \b");
                                }

                                break;
                        }
                                
                        default:
                        {
                                if(p[idx] >= 0x20 && p[idx] < 0x7F) {
                                        if(ullIdx < U_SHELL_MAX_CMD_LEN - 1) {
                                                cBuffer[ullIdx++] = p[idx];
                                                cBuffer[ullIdx] = '\0';
                                        }
                                }

                                break;
                        }
                                
                }
        }
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void parse_proc(void)
{
        size_t len;
        char * str;

        len = strlen(cBuffer);
        if(len != ullIdx || ullIdx == 0) return;

        iArgc = 0;
        pcArgv[0] = cBuffer;
        str = cBuffer;

        while(*str != '\0') {

                while(*str == ' ' && ++str);

                if(*str == '\0') break;

                if(*str == '"') {
                        ++str;
                        pcArgv[iArgc++] = str;

                        /* Process until end of quote */
                        while (*str != '\0') {
                                if (*str == '\\') {
                                        ++str;
                                        if (*str == '"') {
                                                ++str;
                                        }
                                } 
                                else if (*str == '"') {
                                        *str = '\0';
                                        ++str;
                                        break;
                                } 
                                else {
                                        ++str;
                                }
                        }
                }
                else {
                        pcArgv[iArgc++] = str; 
                        while (*str != ' ' && *str != '\0') {
                                if (*str == '"') { 
                                        *str = '\0';   
                                }
                                ++str;
                        }
                        if (*str == '\0') {
                                break;
                        }
                        *str = '\0';
                        ++str;
                }

                if(iArgc == U_SHELL_MAX_CMD_ARGS) {
                        break;
                }
        }

        if(iArgc > 0) {
                const struct u_shell_cmd * cmd = NULL;
                size_t arg_len = strlen(pcArgv[0]);

                if((ptCmdList != NULL) && (ulCmdCnt > 0)) {
                        for(size_t idx = 0; idx < ulCmdCnt; idx++) {
                                if((arg_len == strlen(ptCmdList[idx].name)) && 
                                   (strncmp(ptCmdList[idx].name, pcArgv[0], arg_len) == 0))
                                {
                                        cmd = &ptCmdList[idx];
                                        break;
                                }
                        }
                }

                if(cmd != NULL) {
                        if((iArgc == 2U) &&
                           (pcArgv[1][0] == '-') &&
                           (pcArgv[1][1] == 'h'))
                        {
                                fnPrint(cmd->desc);
                                fnPrint("\r\n");
                        }
                        else {
                                cmd->cb(iArgc, pcArgv);
                        }
                }
                else if((arg_len == 7U) && (strncmp(pcArgv[0], "listcmd", 7U) == 0)) {
                        fnPrint("List of registered commands\r\n");
                        for(size_t idx = 0; idx < ulCmdCnt; idx++) {
                                fnPrint(ptCmdList[idx].name);
                                fnPrint("\t\t\t");
                                fnPrint(ptCmdList[idx].desc);
                                fnPrint("\r\n");
                        }
                }
                else {
                        fnPrint("Unknown command\r\n");
                }
        }
}


/******************************* (END OF FILE) *********************************/


