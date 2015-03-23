#include <iostream>
#include <memory>
#include <string>
#include <boost/shared_ptr.hpp>

using namespace std;

class IBike
{
public:
	IBike( const string& type )
		:m_type( type )
	{
	}
	virtual void ride(  ) = 0;
	virtual ~IBike(  )
	{
	}
	string& getType(  )
	{
		return m_type;
	}
private:
	string m_type;
};

class SmartBike : public IBike
{
public:
	SmartBike( const string& type  )
		:IBike( type )
	{
		cout<<"smart bike created"<<endl;
	}
	void ride(  )
	{
		cout<<"ride "<<getType()<<" smart bike"<<endl;
	}
	~SmartBike(  )
	{
		cout<<"--------destroy smart bike"<<endl;
	}
};

class NormalBike : public IBike
{
public:
	NormalBike( const string& type )
		:IBike( type )
	{
		cout<<"normal bike created"<<endl;
	}
	void ride(  )
	{
		cout<<"ride "<<getType()<<" normal bike"<<endl;
	}
	~NormalBike(  )
	{
		cout<<"--------destroy normal bike"<<endl;
	}
};

class IFactory
{
public:
	virtual boost::shared_ptr<IBike> createNormal(  ) = 0 ;
	virtual boost::shared_ptr<IBike> createSmart(  ) = 0 ;
	virtual ~IFactory(  )
	{
	}
};

class GiantBikeFactory : public IFactory
{
public:
	GiantBikeFactory(  )
	{
		cout<<"giant bike factory created----"<<endl;
	}
	boost::shared_ptr<IBike> createNormal(  )
	{
		boost::shared_ptr<IBike> bike( new NormalBike( string( "Giant" )  ) );
		return bike;
	}
	
	boost::shared_ptr<IBike> createSmart(  )
	{
		boost::shared_ptr<IBike> bike( new SmartBike( string( "Giant" ) ) );
		return bike;
	}

	~GiantBikeFactory(  )
	{
		cout<<"-------giant bike factory destroy"<<endl;
	}
};

class MerridaBikeFactory : public IFactory
{
public:
	MerridaBikeFactory(  )
	{
		cout<<"merrida bike factory created----"<<endl;
	}
	
	boost::shared_ptr<IBike> createNormal(  )
	{
		boost::shared_ptr<IBike> bike( new NormalBike( string( "Merrida" )  ) );
		return bike;
	}
	boost::shared_ptr<IBike> createSmart(  )
	{
		boost::shared_ptr<IBike> bike( new SmartBike( string( "Merrida" ) ) );
		return bike;
	}

	~MerridaBikeFactory(  )
	{
		cout<<"-------merrida bike factory destroy"<<endl;
	}
};

int main( void )
{
	auto_ptr<IFactory> Giant;
	Giant.reset( new GiantBikeFactory(  ) );

	boost::shared_ptr<IBike> normal;
	boost::shared_ptr<IBike> smart;

	//giant factory
	normal = Giant->createNormal(  );
	normal->ride(  );
	smart = Giant->createSmart(  );
	smart->ride(  );
	
	auto_ptr<IFactory> Merrida;
	Merrida.reset( new MerridaBikeFactory(  ) );

	//merrida factory
	normal = Merrida->createNormal(  );
	normal->ride(  );
	smart = Merrida->createSmart(  );
	smart->ride(  );
	
	return 0;
}
