//

#pragma once

#ifndef _GAME_PROPERTY_DEF_H_
#define _GAME_PROPERTY_DEF_H_

#include "PropertyType.h"

#include <Foundation/DefaultID.h>

#include <boost/utility.hpp>
#include <boost/unordered_map.hpp>

namespace Game
{
	/**
	 */
	class CPropertyDef : boost::noncopyable
	{
	public:

		// Initialization / Destruction
										CPropertyDef	(const Foundation::TDefaultID& _ID, EPropertyType _eType) :
											m_ID(_ID), m_eType(_eType)
										{ /* ... */ }

		virtual						   ~CPropertyDef() 
										{ /* ... */ }

		// Accessors
		const Foundation::TDefaultID&	GetID			()		const { return m_ID; }
		EPropertyType					GetType			()		const { return m_eType; }

		uint16							GetValueSize	()		const { return GetPropertyTypeDef(m_eType).uSize; }

	private:

		Foundation::TDefaultID m_ID;
		EPropertyType		   m_eType;
	};
} // namespace Game

#endif // _GAME_PROPERTY_DEf_H_

