/**
 *
 */
#pragma once

#ifndef _FOUNDATION_ID_REGISTRY_H_
#define _FOUNDATION_ID_REGISTRY_H_

#include "Config.h"
#include "Types.h"
#include "Singleton.h"

#include <map>
#include <boost/functional/hash.hpp>

namespace Foundation
{

/** 
 */
template <typename TID, typename THasher = boost::hash<typename TID::textID_type> >
class CIDRegistry : public CSingleton<CIDRegistry<TID, THasher> >
{
public:

	typedef typename TID::hashID_type THashID;
	typedef typename TID::textID_type TTextID;

	THashID				RegisterAndRetrieveID	(const TTextID& _TextID);

#ifdef FOUNDATION_ID_STORE_TEXT_IDS
	const TTextID		GetTextID				(THashID _HashID);
#endif // FOUNDATION_ID_STORE_TEXT_IDS

private:

	typedef std::map<THashID, TTextID> TIDMap;

	TIDMap m_IDMap;
};


/*
 * TEMPLATE DEFINITIONS
 */

/**
 */
template <typename TID, typename THasher>
typename CIDRegistry<TID, THasher>::THashID	CIDRegistry<TID, THasher>::RegisterAndRetrieveID(const typename CIDRegistry<TID, THasher>::TTextID& _TextID)
{
	// @TODO[egarcia]: Review: Case sensitive/insensitive -> traits/policy
	TTextID CanonicalTextID = TID::textID_equivalence_policy_type::GetCanonicalTextID(_TextID);

	typename TID::hashID_type HashID = THasher()(CanonicalTextID);
		
#ifdef FOUNDATION_ID_STORE_TEXT_IDS

	// Check text IDs collisions
	typename TIDMap::const_iterator itID  	   = m_IDMap.find(HashID);
	bool   							bCollision = (itID != m_IDMap.end() && (itID->second != CanonicalTextID));

	assert(!bCollision);
	if    (!bCollision)
	{
		m_IDMap.insert(std::make_pair(HashID, CanonicalTextID));
	}

#endif

	return HashID;
}

#ifdef FOUNDATION_ID_STORE_TEXT_IDS

template <typename TID, typename THasher>
const typename CIDRegistry<TID, THasher>::TTextID CIDRegistry<TID, THasher>::GetTextID(typename CIDRegistry<TID, THasher>::THashID _HashID)
{
	typename CIDRegistry<TID, THasher>::TTextID TextID;

	typename TIDMap::iterator itID = m_IDMap.find(_HashID);
	if (itID != m_IDMap.end())
	{
		TextID = itID->second;
	}

	return TextID;
}

#endif // FOUNDATION_ID_STORE_TEXT_IDS



} // namespace Foundation

#endif // _FOUNDATION_ID_REGISTRY_H_
