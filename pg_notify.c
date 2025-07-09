#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "utils/elog.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h> // Ensure errno is properly included


const char *fifo_path = "/tmp/drawer_fifo";

PG_MODULE_MAGIC;
 
PG_FUNCTION_INFO_V1(hello_world);

Datum hello_world(PG_FUNCTION_ARGS) {
    text *result = cstring_to_text("Hello, pg_notify Extension!");
    PG_RETURN_TEXT_P(result);
}

PG_FUNCTION_INFO_V1(show_notification);

Datum show_notification(PG_FUNCTION_ARGS) {
    VarChar *arg1 = PG_GETARG_VARCHAR_P(0);
    VarChar *arg2 = PG_GETARG_VARCHAR_P(1);

    elog(INFO, "show_notification called with arguments: %s, %s", VARDATA_ANY(arg1), VARDATA_ANY(arg2));

    int err = mkfifo(fifo_path, 0777);
    if (err == -1 && errno != EEXIST) {
        elog(ERROR, "Failed to create FIFO: %m", err);
        PG_RETURN_NULL();
    }

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s,%s", VARDATA_ANY(arg1), VARDATA_ANY(arg2));

    // Write data to FIFO
    int fd = open(fifo_path, O_WRONLY);
    if (fd < 0) {
        elog(ERROR, "Failed to open FIFO: %m");
        PG_RETURN_NULL();
    }

    write(fd, buffer, strlen(buffer) + 1);
    close(fd);

    char *result_str = psprintf("%s,%s", VARDATA_ANY(arg1), VARDATA_ANY(arg2));

    elog(INFO, "show_notification result: %s", result_str);

    PG_RETURN_TEXT_P(cstring_to_text(result_str));
}
