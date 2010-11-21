#include "PropertyDB.h"
#include "PropertyDef.h"

#include <boost/foreach.hpp>

#include <algorithm>
#include <numeric>

#include <stdlib.h>

namespace Game
{
	/**
	 *
	 */
	void CPropertyDB::AllocRows(uint32 _uNumRows)
	{
		// We do not currently support DB resizing
		assert(m_pData == NULL);
		assert(_GetRowSize() > 0);

		m_uDataSize = _uNumRows * _GetRowSize();
		m_pData 	= new char[m_uDataSize];
	}

	/**
	 *
	 */
	uint32 CPropertyDB::CreateRow()
	{
		// We do not currently support DB resizing
		assert(m_uNumRows < _GetNumAllocatedRows());

		return m_uNumRows++;
	}

	/**
	 *
	 */
	uint32 CPropertyDB::GetNumRows() const
	{
		return m_uNumRows;
	}

	/**
	 *
	 */
	bool CPropertyDB::IsEmpty() const
	{
		return m_uNumRows == 0;
	}


	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	void CPropertyDB::_AddPropertyDef( CPropertyDef* _pPropertyDef )
	{
		// We do not allow to modify the DB Scheme while it has rows
		// @TODO[egarcia]: It should be considered if removing this limitation is worth the effort (default values, memory reallocating, etc.).
		assert(m_pData == NULL);

		m_vpPropertyDefs.push_back(_pPropertyDef);
		m_uCurRowSize += _pPropertyDef->GetValueSize();
	}

	/**
	 */
	uint16 CPropertyDB::_CalculateRowSize() const
	{
		uint16 uSize = 0;

		BOOST_FOREACH(const CPropertyDef& _PropertyDef, m_vpPropertyDefs)
		{
			uSize += _PropertyDef.GetValueSize();
		}

		return uSize;
	}

	/**
	 * @TODO[egarcia]: Cachear
	 */
	uint16 CPropertyDB::_GetRowSize() const
	{
		return _CalculateRowSize();
	}


	/**
	 */
	uint32 CPropertyDB::_CalculateRowOffset( uint32 _uRowIndex ) const
	{
		assert(_uRowIndex < GetNumRows());

		uint32 uOffset = _GetRowSize() * std::max<int32>(0, static_cast<int32>(_uRowIndex) - 1);
		return uOffset;
	}

	/**
	 */
	uint32 CPropertyDB::_CalculatePropertyOffset( uint32 _uPropertyIndex ) const
	{
		assert(_uPropertyIndex < m_vpPropertyDefs.size());

		uint32 uOffset		  = 0;
		for (uint32 uProperty = 0; uProperty < _uPropertyIndex; ++uProperty)
		{
			uOffset += m_vpPropertyDefs[uProperty].GetValueSize();
		}

		return uOffset;
	}

	/**
	 */
	uint32 CPropertyDB::_CalculateValueOffset( uint32 _uRowIndex, uint32 _uPropertyIndex ) const
	{
		return _CalculateRowOffset(_uRowIndex) + _CalculatePropertyOffset(_uPropertyIndex);
	}

	/**
	 *
	 */
	void CPropertyDB::_FreeRows()
	{
		delete [] m_pData;
	}



} // namespace Game
