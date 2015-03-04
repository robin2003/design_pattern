#include <iostream>
#include <boost/scoped_ptr.hpp>
#include <string>

using namespace std;

class ICharger
{
public:
	virtual void charge(  ) = 0;
	virtual ~ICharger(  )
	{
	}
};

class USBCharger : public ICharger
{
public:
	virtual void charge(  )
	{
		cout<<"usb charger....."<<endl;
	}
	~USBCharger(  )
	{
		cout<<"usb charger finished"<<endl;
	}
};

class Mobile
{
public:
	explicit Mobile( const string& type )
		: m_charger(NULL), m_type( type )
	{
	}
	
	void init(  )
	{
		m_charger.reset( new USBCharger(  ) );
	}
	
	void doCharge(  )
	{
		assert( m_charger != NULL );
		m_charger->charge(  );
	}
	
private:
	boost::scoped_ptr<ICharger> m_charger;
	string m_type;
};


int main( void )
{
	string type( "samsung" );
	Mobile mobile( type );
	mobile.init(  );
	mobile.doCharge(  );
	
	return 0;
}
