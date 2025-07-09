CREATE FUNCTION hello_world()
RETURNS TEXT AS 'pg_notify', 'hello_world'
LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION show_notification(varchar, varchar)
RETURNS TEXT AS 'pg_notify', 'show_notification'
LANGUAGE C IMMUTABLE STRICT;
