#include <vector>
#include <cstdint>
#include <iostream>
#include <memory>
class SensorVectorRegistry;

template<typename T>
class SensorVector : public std::vector<T>
{
public:
	SensorVector( SensorVectorRegistry* pRegister );
	int32_t m_WriteCnt{ 0 };
};

class Wrapper
{
public:
	virtual ~Wrapper() {}
	virtual void clear() = 0;
};

template<typename T>
class VectorWrapper : public Wrapper
{
public:
	VectorWrapper( SensorVector<T>* pVec ) : m_Vec( pVec ) {}

	void clear() override
	{
		m_Vec->clear();
		m_Vec->m_WriteCnt = 0;
	}

private:
	SensorVector<T>* m_Vec;
};

class SensorVectorRegistry
{
public:
	template<typename T>
	void Regist( SensorVector<T>* pVec )
	{
		m_Registered.push_back(
			std::make_unique<VectorWrapper<T>>( pVec )
		);
	}

	void clear()
	{
		for ( auto& reg : m_Registered )
		{
			reg->clear();
		}
	}

private:
	std::vector<std::unique_ptr<Wrapper>> m_Registered;
};

template<typename T>
SensorVector<T>::SensorVector( SensorVectorRegistry* pRegister )
{
	pRegister->Regist( this );
}