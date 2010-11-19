#pragma once

#ifndef _FOUNDATION_ID_H_
#define _FOUNDATION_ID_H_

// External Dependencies
#include "Config.h"
#include "IDRegistry.h"

#include <string>
#include <algorithm>

namespace Foundation
{

/****************************************************
 * Fast ID Traits
 ****************************************************/

/** Fast ID types traits
 *  It must define:
 *  INVALID_FAST_ID
 */
template <class THashID>
struct fast_id_traits
{
};

/****************************************************
 * Text ID Equivalence Policies
 ****************************************************/

/**
 * Text ID case sensitive equivalence policy
 */
template <class TTextID>
struct text_id_case_sensitive_equivalence
{
	// @TODO[egarcia]: Check optimality
	static TTextID GetCanonicalTextID(const TTextID& _TextID)
	{
		return _TextID;
	}
};

/**
 * Text ID case insensitive equivalence policy
 */
template <class TTextID>
struct text_id_case_insensitive_equivalence
{
	// @TODO[egarcia]: Check optimality
	static TTextID GetCanonicalTextID(const TTextID& _TextID)
	{
		std::string CanonicalTextID;
		CanonicalTextID.resize(_TextID.size());
		std::transform(_TextID.begin(), _TextID.end(), CanonicalTextID.begin(), toupper);

		return CanonicalTextID;
	}
};

/****************************************************
 * ID
 ****************************************************/


/** Provides IDs with fast comparations and small footprint (Ej.: int32).
	*  To debug purposes, it provides debug text ids that are stored in a ID Registry.
	*  
	*  @TODO[egarcia]: Review concurrency issues (registry access, etc.).
	*/
template <class THashID = FOUNDATION_ID_DEFAULT_HASH_TYPE, class TTextID = FOUNDATION_ID_DEFAULT_TEXT_TYPE, typename text_id_equivalence_policy = text_id_case_sensitive_equivalence<TTextID> >
class ID
{
public:

	// Publish template types
	typedef THashID  hashID_type;
	typedef TTextID  textID_type;

	typedef text_id_equivalence_policy textID_equivalence_policy_type;

	// Initialization / Destruction

	/** Default constructor. Provides an INVALID ID that can be assigned to a valid value later
	 *
	 */
	/* implicit */ ID() :
		m_HashID(fast_id_traits<THashID>::INVALID_FAST_ID)
	{
	}

	/** Copy Constructor.
		*/
	/* implicit */ ID(const ID& _ID) :
		m_HashID(_ID.m_HashID)
	{ /* It is not necessary to register the Id */	}


	/** Debug String Constructor.
		*/
	/* implicit */ ID(const TTextID& _sID) :
		m_HashID(fast_id_traits<THashID>::INVALID_FAST_ID)
	{
		m_HashID = _GetHashID(_sID);
	}

	/** ID Consctructor.
		*  @TODO[egarcia]: Review use cases.
		*/
	/* implicit */ ID(const THashID& _HashID) :
		m_HashID(_HashID)
	{
		// @TODO[egarcia]: Review: m_sID default value?
	}

	/** Destructor.
		*/
	/* final */ ~ID()
	{
	}

	/**
	 */
	THashID GetHashID() const 
	{
		return m_HashID;
	}

	/**
		* Implicit String casting
		*/ 
		
	operator const TTextID ()
	{
#ifdef FOUNDATION_ID_STORE_TEXT_IDS
		return _GetTextID();
#else
		static_assert(false, "FOUNDATION_ID_STORE_TEXT_IDS must be defined to use convert to TextID operator.");
#endif // FOUNDATION_ID_STORE_TEXT_IDS
	}


	/** 
		*/
	friend bool operator==(const ID& _ID1, const ID& _ID2)
	{
		return _ID1.m_HashID == _ID2.m_HashID;
	}


private:

	THashID m_HashID;

	/**
	  */
	THashID _GetHashID(const TTextID& _TextID) const
	{
		return CIDRegistry<ID<THashID, TTextID>>::Instance()->RegisterAndRetrieveID(_TextID);
	}

	/**
	  */
	const TTextID _GetTextID() const
	{
		return CIDRegistry<ID<THashID, TTextID>>::Instance()->GetTextID(m_HashID);
	}
};


} // namespace Foundation



#endif // _FOUNDATION_ID_H_
