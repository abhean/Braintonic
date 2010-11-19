#include "PropertyDefSet.h"
#include "PropertyDef.h"


void Game::CPropertyDefSet::AddPropertyDef( const CPropertyDef* _pPropertyDef )
{
	m_PropertyDefMap.insert(_pPropertyDef);
}
