#include "mysql_driver.h"
#include <cppconn/prepared_statement.h>

#include "database.class.h"

Database::Database(void){
	oDriver = sql::mysql::get_mysql_driver_instance();
	this->oCon = oDriver->connect(DSN, USER, PASSWORD);
	this->oCon->setSchema(DATABASE);

}

// Cosa fa			:			Estrapola la connessione al db
// Ritorna			:			this->oCon, sql::Connection, oggetto connessione al db
sql::Connection *Database::getConnection(){
	return this->oCon;
}

Database::~Database(void){
	delete this->oCon;
}