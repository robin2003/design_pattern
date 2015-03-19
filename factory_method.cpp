#include <iostream>
#include <memory>
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

class IFactory
{
public:
	virtual boost::shared_ptr<IBike> create(  ) = 0 ;
	virtual ~IFactory(  )
	{
	}
};

class NormalBikeFactory : public IFactory
{
public:
	NormalBikeFactory(  )
	{
		cout<<"normal bike factory created----"<<endl;
	}
	boost::shared_ptr<IBike> create(  )
	{
		boost::shared_ptr<IBike> bike( new NormalBike(  ) );
		return bike;
	}
	~NormalBikeFactory(  )
	{
		cout<<"-------normal bike factory destroy"<<endl;
	}
};

class SmartBikeFactory : public IFactory
{
public:
	SmartBikeFactory(  )
	{
		cout<<"smart bike factory created----"<<endl;
	}
	
	boost::shared_ptr<IBike> create(  )
	{
		boost::shared_ptr<IBike> bike( new SmartBike(  ) );
		return bike;
	}
	~SmartBikeFactory(  )
	{
		cout<<"-------smart bike factory destroy"<<endl;
	}
};

int main( void )
{
	auto_ptr<IFactory> factory;
	factory.reset( new NormalBikeFactory(  ) );
	
	boost::shared_ptr<IBike> bike;
	bike = factory->create(  );
	bike->ride(  );

	factory.reset( new SmartBikeFactory(  ) );
	bike = factory->create(  );
	bike->ride(  );
	
	return 0;
}
