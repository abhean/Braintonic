#pragma once

#ifndef _GAME_PROPERTY_TYPE_H_
#define _GAME_PROPERTY_TYPE_H_

#include <Foundation/ID.h>

#include <boost/utility.hpp>
#include <boost/unordered_map.hpp>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>

namespace Game
{

	class CPropertyDB;


	enum EPropertyType : uint8
	{
		PROPERTY_TYPE_INT32,
		PROPERTY_TYPE_FLOAT,
		PROPERTY_TYPE_STRING,
		PROPERTY_TYPE_PROPERTY_DB_PTR,
		//...
		PROPERTY_TYPE_COUNT,
		PROPERTY_TYPE_INVALID = 0x7F
	};


	typedef boost::variant< int32, f32, std::string, CPropertyDB*> TPropertyValue;

	// @TODO[egarcia]: Provide functions to convert between enum and string (both ways) (MACRO: value / string table?)

	/*
	 */
	struct SPropertyTypeDef 
	{
		uint8 uSize;
	};


#define PROPERTY_TYPE_DEF_TABLE_BEGIN static SPropertyTypeDef aPropertyTypeDef[] = {
#define PROPERTY_TYPE_DEF_TABLE_END };
#define PROPERTY_TYPE_DEF(ENUM, TYPE) { sizeof(TYPE) },

	// TODO[egarcia]. Review. RTTI?
	template <typename T>
	struct property_type_traits
	{
		static const EPropertyType ePropertyType = PROPERTY_TYPE_INVALID;
	};

	template <>
	struct property_type_traits<int32>
	{
		static const EPropertyType ePropertyType = PROPERTY_TYPE_INT32;
	};

	template <>
	struct property_type_traits<float>
	{
		static const EPropertyType ePropertyType = PROPERTY_TYPE_FLOAT;
	};

	template <>
	struct property_type_traits<std::string>
	{
		static const EPropertyType ePropertyType = PROPERTY_TYPE_STRING;
	};

	template <>
	struct property_type_traits<CPropertyDB*>
	{
		static const EPropertyType ePropertyType = PROPERTY_TYPE_PROPERTY_DB_PTR;
	};


	// @TODO[egarcia]: Static assert to enforce num elements, order?
	PROPERTY_TYPE_DEF_TABLE_BEGIN
		PROPERTY_TYPE_DEF(PROPERTY_TYPE_INT32,			 int32)
		PROPERTY_TYPE_DEF(PROPERTY_TYPE_FLOAT,			 float)
		PROPERTY_TYPE_DEF(PROPERTY_TYPE_STRING,			 std::string)
		PROPERTY_TYPE_DEF(PROPERTY_TYPE_PROPERTY_DB_PTR, CPropertyDB*)
	PROPERTY_TYPE_DEF_TABLE_END


	inline const SPropertyTypeDef& GetPropertyTypeDef(EPropertyType _eType)
	{
		return aPropertyTypeDef[_eType];
	}


} // namespace Game

#endif // _GAME_PROPERTY_TYPE_H_

