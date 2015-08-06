#include "mysql_driver.h"
#include <cppconn/prepared_statement.h>

using namespace std;

#ifndef DATABASE_CLASS_H
#define DATABASE_CLASS_H

#define	DSN			"localhost"
#define	USER		"root"
#define	PASSWORD	"root"
#define	DATABASE	"SocialNetworkBot"

class Database
{
	public:
		Database();
		~Database();
		sql::Connection *getConnection();

	private:		
		sql::mysql::MySQL_Driver *oDriver;
		sql::Connection *oCon;

};

#endif