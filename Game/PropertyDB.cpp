#include "PropertyDB.h"
#include "PropertyDef.h"

#include <algorithm>
#include <numeric>

namespace Game
{
	/************************************************************************/
	/*                                                                      */
	/************************************************************************/
	void CPropertyDB::_AddPropertyDef( CPropertyDef* _pPropertyDef )
	{
		// We do not allow to modify the DB Scheme while it has rows
		// @TODO[egarcia]: It should be considered if removing this limitation is worth the effort (default values, memory reallocating, etc.).
		assert(m_vRows.empty());

		m_vpPropertyDefs.push_back(_pPropertyDef);
		m_uCurRowSize += _pPropertyDef->GetValueSize();
	}

	/**
	 */
	uint16 CPropertyDB::_CalculateRowSize() const
	{
		uint16 uSize = 0;

		std::for_each(m_vpPropertyDefs.begin(), m_vpPropertyDefs.end(), [&uSize] (const CPropertyDef& _PropertyDef) 
		{
			uSize += _PropertyDef.GetValueSize();
		});

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
		assert(_uRowIndex < m_vRows.size());

		uint32 uOffset = _GetRowSize() * std::max<int32>(0, static_cast<int32>(_uRowIndex) - 1);
		return uOffset;
	}

	/**
	 */
	uint32 CPropertyDB::_CalculatePropertyOffset( uint32 _uPropertyIndex ) const
	{
		assert(_uPropertyIndex < m_vpPropertyDefs.size());

		uint32 uOffset		  = 0;
		int32  iNumProperties = m_vpPropertyDefs.size();
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
	 */
	CPropertyDB::TDBRow CPropertyDB::CreateAndPushRow()
	{
		TDBRow NewRow = _CreateRow();
		m_vRows.push_back(NewRow);

		return NewRow;
	}

	/**
	 * @TODO[egarcia]: Pool, Memory Management
	 */
	CPropertyDB::TDBRow CPropertyDB::_CreateRow() const
	{
		return static_cast<TDBRow>(new char[m_uCurRowSize]);
	}

} // namespace Game
