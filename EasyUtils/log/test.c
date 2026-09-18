#include <stdio.h>
#include "u_log.h"

static void log_output_cb(const char * buf, size_t len)
{
        printf("%.*s", (int)len, buf);
}

int main(void)
{
        u_log_init(log_output_cb);

        U_LOG_TRACE("trace message: value=%d", 1);
        U_LOG_INFO("info message: value=%d", 2);
        U_LOG_WARN("warn message: value=%d", 3);
        U_LOG_ERROR("error message: value=%d", 4);
        U_LOG_USER("user message: value=%d", 6);
        
        
        pr_log("custom raw log: %s\r\n", "hello");
        pr_info("custom info: %s", "world");

        U_LOG_FATAL("fatal message: value=%d", 5);

        return 0;
}
