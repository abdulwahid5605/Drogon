#include <drogon/drogon.h>
#include <sqlite3.h>
#include <iostream>

sqlite3 *db = nullptr;

int main() {
    LOG_DEBUG << "Starting Drogon app...";

    // Open SQLite3 database (creates file if it doesn't exist)
    int rc = sqlite3_open("users.db", &db);
    if (rc) {
        std::cerr << "Can't open DB: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Create users table
    const char *sql = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, city TEXT);";
    char *errMsg = nullptr;
    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table ensured.\n";
    }

    drogon::app().addListener("127.0.0.1", 8000);
    drogon::app().run();

    // Close DB after server shuts down
    sqlite3_close(db);
    return 0;
}
