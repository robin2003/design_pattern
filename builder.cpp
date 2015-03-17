#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;

class IBuilder;
typedef boost::shared_ptr<IBuilder> BUILDER_PTR;

class IBuilder
{
public:
	virtual void buildHead(  ) = 0;
	virtual void buildBody(  ) = 0;
	virtual ~IBuilder(  )
	{
	}
};

class HTTP : public IBuilder
{
public:
	void buildHead(  )
	{
		cout<<"build HTTP head"<<endl;
	}
	void buildBody(  )
	{
		cout<<"builder HTTP body"<<endl;
	}

	~HTTP(  )
	{
		cout<<"------------destroy HTTP"<<endl;
	}
};

class FTP : public IBuilder
{
public:
	void buildHead(  )
	{
		cout<<"build FTP head"<<endl;
	}
	void buildBody(  )
	{
		cout<<"builder FTP body"<<endl;
	}

	~FTP(  )
	{
		cout<<"------------destroy FTP"<<endl;
	}
};

class ProtocolDirector
{
public:
	explicit ProtocolDirector( BUILDER_PTR & builder )
		:m_builder( builder )
	{
	}

	void setBuilder( BUILDER_PTR & builder )
	{
		m_builder = builder;
	}
	
	void getProtocol(  )
	{
		assert( m_builder.get(  ) != NULL );
		m_builder->buildHead(  );
		m_builder->buildBody(  );
	}

private:
	BUILDER_PTR m_builder;
};

int main( void )
{
	BUILDER_PTR buider( new FTP(  ) );
	ProtocolDirector director( buider );
	director.getProtocol(  );
	
	buider.reset( new HTTP(  ) );
	director.setBuilder( buider );
	director.getProtocol(  );
	
	return 0;
}
