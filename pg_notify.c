#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"

PG_MODULE_MAGIC;
 
PG_FUNCTION_INFO_V1(hello_world);

Datum hello_world(PG_FUNCTION_ARGS) {
    text *result = cstring_to_text("Hello, pg_notify Extension!");
    PG_RETURN_TEXT_P(result);
}
