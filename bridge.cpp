#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

#define _CLASS_DEFAULT_VIRTUAL_FUNCTION_( className )		\
	virtual ~className(  )									\
	{														\
	}														\
	

class TEA
{
public:
	explicit TEA( const string& type )
		:m_type( type )
	{
	}
	virtual void getContent(  ) = 0;
	
	_CLASS_DEFAULT_VIRTUAL_FUNCTION_( TEA )
private:
	string m_type;
};

class IPackage
{
public:
	IPackage(  )
		:m_tea( NULL )
	{
	}

	virtual void getContent( void ) = 0;
	void setTea( TEA* tea )
	{
		m_tea = tea;
	}

	_CLASS_DEFAULT_VIRTUAL_FUNCTION_( IPackage )
protected:
	TEA* getTea(  ) const
	{
		return m_tea;
	}
	
private:
	TEA* m_tea;
};

class RedTea : public TEA
{
public:
	RedTea( )
		:TEA( string( "red tea" ) )
	{
	}

	void getContent(  )
	{
		cout<<"red tea content is red"<<endl;
	}
};

class BlackTea : public TEA
{
public:
	BlackTea( )
		:TEA( string( "black tea" ) )
	{
	}

	void getContent(  )
	{
		cout<<"black tea content is black"<<endl;
	}
};

class BagPackage : public IPackage
{
public:
	void getContent(  )
	{
		TEA* tea = getTea(  );
		assert( tea != NULL );
		tea->getContent(  );
	}
};

int main( void )
{
	RedTea rt;
	BlackTea bt;
	BagPackage bp;
	
	bp.setTea( &rt );
	bp.getContent(  );
	
	return 0;
}

