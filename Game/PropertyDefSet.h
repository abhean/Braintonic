#pragma once

#ifndef _GAME_PROPERTY_DEF_SET_H_
#define _GAME_PROPERTY_DEF_SET_H_

#include <Foundation/ID.h>

#include <boost/unordered_set.hpp>

namespace Game
{

// Game Forward Declarations	
class CPropertyDef;


/**
 */
class CPropertyDefSet
{
public:

	void		 AddPropertyDef		(const CPropertyDef* _pPropertyDef);
	


private:

	// Hash table
	boost::unordered_set<const CPropertyDef*> m_PropertyDefMap;
};

} // namespace Game

#endif // _GAME_PROPERTY_DEF_SET_H_