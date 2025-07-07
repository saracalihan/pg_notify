EXTENSION = pg_notify
MODULES = pg_notify
DATA = pg_notify--1.0.sql
PG_CONFIG = pg_config

# PostgreSQL'in yapılandırmasını al
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
