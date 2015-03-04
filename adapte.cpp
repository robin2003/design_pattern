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

class ACCharger : public ICharger
{
public:
	virtual void charge(  )
	{
		cout<<"AC charging....."<<endl;
	}
	~ACCharger(  )
	{
		cout<<"AC charger finished"<<endl;
	}
};

class ChargerAdaptee
{
public:
	ChargerAdaptee(  )
		:m_charger( new ACCharger(  ) )
	{
	}
	
	void doCharge(  )
	{
		assert( m_charger != NULL );
		cout<<"adaptee AC charger for mobile"<<endl;
		m_charger->charge(  );
	}
	
private:
	boost::scoped_ptr<ICharger> m_charger;

};

class Mobile
{
public:
	explicit Mobile( const string& type )
		: m_type( type )
	{
	}
	
	void doCharge(  )
	{
		m_charger.doCharge(  );
	}
	
private:
	ChargerAdaptee m_charger;
	string m_type;
};


int main( void )
{
	string type( "samsung" );
	Mobile mobile( type );
	mobile.doCharge(  );
	
	return 0;x
}
