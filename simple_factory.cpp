#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;

class IBike
{
public:
	virtual void ride(  ) = 0;
	virtual ~IBike(  )
	{
	}
};

class SmartBike : public IBike
{
public:
	SmartBike(  )
	{
		cout<<"smart bike created"<<endl;
	}
	void ride(  )
	{
		cout<<"ride smart bike"<<endl;
	}
	~SmartBike(  )
	{
		cout<<"--------destroy smart bike"<<endl;
	}
};

class NormalBike : public IBike
{
public:
	NormalBike(  )
	{
		cout<<"normal bike created"<<endl;
	}
	void ride(  )
	{
		cout<<"ride normal bike"<<endl;
	}
	~NormalBike(  )
	{
		cout<<"--------destroy normal bike"<<endl;
	}
};

class BikeFactory
{
public:
	enum BikeCate
	{
		NORMAL_BIKE,
		SMART_BIKE
	};
	static boost::shared_ptr<IBike> create( const BikeCate type );
};

boost::shared_ptr<IBike> BikeFactory::create( const BikeCate type )
{
	boost::shared_ptr<IBike> bike;
	if( type == NORMAL_BIKE )
	{
		bike.reset( new NormalBike(  ) );
	}
	else if( type == SMART_BIKE )
	{
		bike.reset( new SmartBike(  ) );
	}

	return bike;
}

int main( void )
{
	boost::shared_ptr<IBike> bike;
	bike = BikeFactory::create( BikeFactory::NORMAL_BIKE );
	bike->ride(  );

	bike = BikeFactory::create( BikeFactory::SMART_BIKE );
	bike->ride(  );
	
	return 0;
}
