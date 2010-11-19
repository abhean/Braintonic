#pragma once

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <boost/utility.hpp>

#include <cassert>


namespace Foundation
{

	template <typename T>
	class CSingleton : public boost::noncopyable
	{
	public:

		virtual ~CSingleton() { assert(m_pInstance != NULL); m_pInstance = NULL; }

		static void Done()
		{

		}

		static T* Instance();

	protected:

		CSingleton() 
		{
			assert(m_pInstance == NULL);
			m_pInstance = static_cast<T*>(this);
		}

	private:

		static T* m_pInstance;
	};

	template<typename T> T* CSingleton<T>::m_pInstance = NULL;

	template <typename T>
	T* CSingleton<T>::Instance()
	{
		assert(m_pInstance != NULL);
		return m_pInstance;
	}


} // namespace Foundation

#define INITIALIZE_SINGLETON(T) new T();

#endif // _SINGLETON_H_
