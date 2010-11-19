#pragma once

#ifndef _GAME_PROPERTY_DB_H_
#define _GAME_PROPERTY_DB_H_

#include "PropertyValue.h"

#include <boost/ptr_container/ptr_vector.hpp>
#include <vector>

namespace Game
{

class CPropertyDef;

/**
 */
class CPropertyDB
{
public:

	// Generic DBRow
	typedef			char*		TDBRow;

	// Initialization / Destruction
					CPropertyDB					() : m_uCurRowSize(0)
					{/* ... */}

				   ~CPropertyDB					() 
					{/* ... */}

	TDBRow			CreateAndPushRow			();

	void			DEBUG_AddPropertyDef		(CPropertyDef* _pPropertyDef) { _AddPropertyDef(_pPropertyDef); }

//private:

	// PropertyDef Management
	void			_AddPropertyDef				(CPropertyDef* _pPropertyDef);


	// DBRows Management
	TDBRow			_CreateRow					() const;

	uint16			_CalculateRowSize			() const;
	uint16			_GetRowSize					() const;

	uint32			_CalculateRowOffset			(uint32 _uRowIndex) const;
	uint32			_CalculatePropertyOffset	(uint32 _uPropertyIndex) const;
	uint32			_CalculateValueOffset		(uint32 _uRowIndex, uint32 _uPropertyIndex) const;


	boost::ptr_vector<CPropertyDef>			m_vpPropertyDefs;
	std::vector<TDBRow>						m_vRows;

	//
	uint16									m_uCurRowSize;
};


} // namespace Game

#endif // _GAME_PROPERTY_DB_H_