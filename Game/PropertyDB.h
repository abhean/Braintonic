#pragma once

#ifndef _GAME_PROPERTY_DB_H_
#define _GAME_PROPERTY_DB_H_

#include "PropertyValue.h"
#include "PropertyDef.h"

#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

namespace Game
{

/**
 */
class CPropertyDB
{
public:

	// Initialization / Destruction
					CPropertyDB					() :
						m_uNumRows(0),
						m_pData(NULL),
						m_uDataSize(0),
						m_uCurRowSize(0)
					{/* ... */}

				   ~CPropertyDB					() 
					{ _FreeRows(); }

	template <typename TValueType>
	TValueType		GetPropertyValue			(uint32 _uRowIndex, uint32 _uPropertyIndex) const;

	template <typename TValueType>
	void			SetPropertyValue			(uint32 _uRowIndex, uint32 _uPropertyIndex, const TValueType& _Value);

	void			DEBUG_AddPropertyDef		(CPropertyDef* _pPropertyDef) { _AddPropertyDef(_pPropertyDef); }

	void			AllocRows					(uint32 _uNumRows);

	uint32			CreateRow					();
	uint32			GetNumRows					() const;
	bool			IsEmpty						() const;

//private:

	// PropertyDef Management
	void			_AddPropertyDef				(CPropertyDef* _pPropertyDef);


	// DBRows Management
	uint16			_CalculateRowSize			() const;
	uint16			_GetRowSize					() const;

	uint32			_CalculateRowOffset			(uint32 _uRowIndex) const;
	uint32			_CalculatePropertyOffset	(uint32 _uPropertyIndex) const;
	uint32			_CalculateValueOffset		(uint32 _uRowIndex, uint32 _uPropertyIndex) const;


	boost::ptr_vector<CPropertyDef>			m_vpPropertyDefs;

	uint32									m_uNumRows;

	/******************************
	 * DB Internal Data Management
	 ******************************/
	char*			_GetDataMemPtr				()  	 { return m_pData; }
	char const*		_GetDataMemPtr				() const { return m_pData; }
	uint32			_GetNumAllocatedRows		() const { return m_uDataSize / _GetRowSize(); }
	void 			_FreeRows					();

	char*									m_pData;
	uint32									m_uDataSize;

	// Catched values
	uint16									m_uCurRowSize;
};

/**
 *
 */
template <typename TValueType>
void CPropertyDB::SetPropertyValue(uint32 _uRowIndex, uint32 _uPropertyIndex, const TValueType& _ValueType)
{
	// Check Property Type is right
	assert(m_vpPropertyDefs[_uPropertyIndex].GetType() == property_type_traits<TValueType>::ePropertyType);


	char* pDataMemPtr = _GetDataMemPtr();
	uint32 uPropertyValueOffset = _CalculateValueOffset(_uRowIndex, _uPropertyIndex);

	*reinterpret_cast<TValueType*>(pDataMemPtr + uPropertyValueOffset) = _ValueType;
}

/**
 *
 */
template <typename TValueType>
TValueType	CPropertyDB::GetPropertyValue(uint32 _uRowIndex, uint32 _uPropertyIndex) const
{
	// Check Property Type is right
	assert(m_vpPropertyDefs[_uPropertyIndex].GetType() == property_type_traits<TValueType>::ePropertyType);


	char const* pDataMemPtr = _GetDataMemPtr();
	uint32 uPropertyValueOffset = _CalculateValueOffset(_uRowIndex, _uPropertyIndex);

	return *reinterpret_cast<const TValueType*>(pDataMemPtr + uPropertyValueOffset);

}


} // namespace Game

#endif // _GAME_PROPERTY_DB_H_
