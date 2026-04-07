#include "DatabaseManager.h"

DatabaseManager& DatabaseManager::getInstance()
{
	static DatabaseManager instance;
	return instance;
}
