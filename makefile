EXTENSION = pg_notify
MODULES = pg_notify
DATA = pg_notify--1.0.sql
PG_CONFIG = pg_config

RAYLIB_PATH=/home/saracalihan/Desktop/projects/pg_notify/raylib-5.0
PG_CFLAGS = -I${RAYLIB_PATH}/src -lraylib -Wl,--whole-archive $(RAYLIB_PATH)/src/libraylib.a -Wl,--no-whole-archive


# llvm ile .bc dosyası üretirlirken cpp değeri isteniyor.
PG_CPPFLAGS = $(PG_CFLAGS)
PG_LDFLAGS = -L${RAYLIB_PATH}/src
# PG_LDFLAGS = -L${RAYLIB_PATH}/src -l:libraylib.so -Wl,-rpath=${RAYLIB_PATH}/src

PGXS := $(shell $(PG_CONFIG) --pgxs )
include $(PGXS)

