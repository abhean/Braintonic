/*
 * DefaultID.h
 *
 *  Created on: Nov 19, 2010
 *      Author: kique
 */

#ifndef DEFAULTID_H_
#define DEFAULTID_H_

#include "Config.h"

#include "ID.h"
#include "IDRegistry.h"

namespace Foundation
{
	typedef ID<FOUNDATION_ID_DEFAULT_HASH_TYPE, FOUNDATION_ID_DEFAULT_TEXT_TYPE> TDefaultID;
	typedef CIDRegistry<TDefaultID> TDefaultIDRegistry;

	// @TODO[egarcia]: Review: the invalid ID value is probably more related to the hash function than the type.
	template <>
	struct fast_id_traits<FOUNDATION_ID_DEFAULT_HASH_TYPE>
	{
		static const FOUNDATION_ID_DEFAULT_HASH_TYPE INVALID_FAST_ID = 0;
	};

} // namespace Foundation


#define ID(TEXT_ID) Foundation::TDefaultID(#TEXT_ID)


#endif /* DEFAULTID_H_ */
