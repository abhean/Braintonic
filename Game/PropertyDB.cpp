#include "PropertyDB.h"
#include "PropertyDef.h"

#include <boost/foreach.hpp>

#include <algorithm>
#include <numeric>
#include <iostream>

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
	uint32 CPropertyDB::CreateRow(std::initializer_list<TPropertyValue> _lPropertyValues)
	{
		// We do not currently support DB resizing
		assert(_lPropertyValues.size() <= GetNumProperties());

		uint32 uNewRowIndex   = CreateRow();
		uint32 uPropertyIndex = 0;
		BOOST_FOREACH(const TPropertyValue& _PropertyValue, _lPropertyValues)
		{
			SetPropertyValue(uNewRowIndex, uPropertyIndex, _PropertyValue);
			std::cout << _PropertyValue << std::endl;

			++uPropertyIndex;
		}


		return uNewRowIndex++;
	}


	/**
	 *
	 */
	uint32 CPropertyDB::CreateRow()
	{
		// We do not currently support DB resizing
		assert(m_uNumRows < _GetNumAllocatedRows());

		/*
		BOOST_FOREACH(const TPropertyValue& _PropertyValue, _lPropertyValues)
		{
			SetPropertyValue(uNewRowIndex, uPropertyIndex, _PropertyValue);
			std::cout << _PropertyValue << std::endl;

			++uPropertyIndex;
		}
		*/

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
	uint32 CPropertyDB::GetNumProperties() const
	{
		return m_vpPropertyDefs.size();
	}

	/**
	 *
	 */
	bool CPropertyDB::IsEmpty() const
	{
		return m_uNumRows == 0;
	}

	/**
	 * Clase auxiliar que asigna un TPropertyValue a un fila/columna de la BD
	 */
	class CPropertyDBSetValueVisitor : public boost::static_visitor<>
	{
	public:

		CPropertyDBSetValueVisitor(CPropertyDB& _PropertyDB, uint32 _uRowIndex, uint32 _uPropertyIndex) :
			m_PropertyDB(_PropertyDB),
			m_uRowIndex(_uRowIndex),
			m_uPropertyIndex(_uPropertyIndex)
		{
			/* ... */
		}

		template <typename TValue>
		void operator()(TValue const& _Value) const
		{
			m_PropertyDB.SetPropertyValue(m_uRowIndex, m_uPropertyIndex, _Value);
		}

	private:

		CPropertyDB& m_PropertyDB;
		uint32		 m_uRowIndex;
		uint32		 m_uPropertyIndex;
	};

	/**
	 *
	 */
	void CPropertyDB::SetPropertyValue(uint32 _uRowIndex, uint32 _uPropertyIndex, TPropertyValue const& _ValueType)
	{
		CPropertyDBSetValueVisitor SetPropertyValueVisitor(*this, _uRowIndex, _uPropertyIndex);
		boost::apply_visitor(SetPropertyValueVisitor, _ValueType);
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
		return m_uCurRowSize;
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
