# pg_notify

## Setup

### Install PostgreSQL
Install PostgreSQL(i prefer v14) core and development library.

[https://www.postgresql.org/download/](https://www.postgresql.org/download/)

### Compile Extension

```bash
make
```

### Install Extension

```bash
make install
```

### Integrate Extension
Run sql command on your database server.

```
DB_HOST="localhost" DB_USER="" DB_PASS="" DB_PORT="" DB_AUTH_DB="" make load
```

## Usage

```js
// TODO:
```

## License
This project is under the [MIT license](./LICENSE).