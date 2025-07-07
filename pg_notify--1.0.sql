CREATE FUNCTION hello_world()
RETURNS TEXT AS 'pg_notify', 'hello_world'
LANGUAGE C IMMUTABLE STRICT;
