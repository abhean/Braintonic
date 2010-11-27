// Braintonic.cpp : Defines the entry point for the console application.
//
#include "Game/PropertyType.h"
#include "Game/PropertyDB.h"
#include "Game/PropertyDef.h"

#include "Foundation/DefaultID.h"

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::cout << "Hello world!" << std::endl;

	INITIALIZE_SINGLETON(Foundation::TDefaultIDRegistry);

	Game::CPropertyDB PropertyDB;
	PropertyDB.DEBUG_AddPropertyDef(new Game::CPropertyDef(ID(TestProperty), Game::PROPERTY_TYPE_FLOAT));
	PropertyDB.DEBUG_AddPropertyDef(new Game::CPropertyDef(ID(TestProperty2), Game::PROPERTY_TYPE_STRING));
	PropertyDB.DEBUG_AddPropertyDef(new Game::CPropertyDef(ID(TestProperty2), Game::PROPERTY_TYPE_INT32));
	PropertyDB.AllocRows(10);
	PropertyDB.CreateRow({3.2f, "hola", 4});
	PropertyDB.CreateRow();
	PropertyDB.CreateRow();
	PropertyDB.CreateRow();
	PropertyDB.CreateRow();
	PropertyDB.CreateRow();
	PropertyDB.CreateRow();

	//PropertyDB.SetPropertyValue<float>(0, 0, 1.2);
	std::cout << "TestProperty, Row 0, Property 0, Value = " << PropertyDB.GetPropertyValue<float>(0, 0) << std::endl;

	//PropertyDB.SetPropertyValue<std::string>(0, 1, sTestText);
	std::cout << "TestProperty, Row 0, Property 1, Value = " << PropertyDB.GetPropertyValue<std::string>(0, 1) << std::endl;


	std::cout << "RowSize: " << PropertyDB._GetRowSize() << std::endl;

	uint32 uRow = 3;
	uint32 uProperty = 1;
	std::cout << "Offset Row [" << uRow << "], Property [" << uProperty << "] : " << PropertyDB._CalculateValueOffset(uRow, uProperty) << std::endl;

	Foundation::TDefaultID ID1("Hellow World");
	std::cout << ID1.GetHashID() << "," << sizeof(ID1) << std::endl;
	Foundation::TDefaultID ID2("Hellow WorLD");
	std::cout << ID2.GetHashID() << "," << sizeof(ID2) << std::endl;
	std::cout << "equals: " << (ID1 == ID2) << std::endl;

	std::cout << static_cast<std::string>(ID1) << std::endl;

	std::cout << static_cast<int>(Game::aPropertyTypeDef[Game::PROPERTY_TYPE_STRING].uSize) << std::endl;

	std::cout << typeid(Game::CPropertyDB).name() << std::endl;

	// Wait for a key
	char cInput;
	std::cin >> cInput;

	return 0;
}

