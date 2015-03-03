#include <iostream>

using namespace std;

enum Level_t
{
	LOW,
	MIDDLE,
	HIGH
};

class Request
{
public:
	explicit Request( Level_t level )
		:m_Level( level )
	{
	}
	
	void setLevel( Level_t level )
	{
		m_Level = level;
	}
	
	Level_t getLevel( void )
	{
		return m_Level;
	}
private:
	Level_t m_Level;
};

class ILevelProcessor
{
public:
	virtual void process( Request* req ) = 0;
	void setSuccessor( ILevelProcessor* levelProcessor )
	{
		successor = levelProcessor;
	}
	
	ILevelProcessor* getSuccessor(  )
	{
		return successor;
	}
	
	virtual ~ILevelProcessor(  )
	{
	}
private:
	ILevelProcessor* successor;
};

class MiddleLevelProcessor : public ILevelProcessor
{
public:
	virtual void process( Request* req )
	{
		if( req->getLevel(  ) == MIDDLE)
		{
			cout<<"middle level processor"<<endl;
			return;
		}

		ILevelProcessor* successor = getSuccessor(  );
		if( successor != NULL )
		{
			successor->process( req );	
		}
	}
};

class HighLevelProcessor : public ILevelProcessor
{
public:
	virtual void process( Request* req )
	{
		if( req->getLevel(  ) == HIGH )
		{
			cout<<"high level processor"<<endl;
			return;
		}

		ILevelProcessor* successor = getSuccessor(  );
		if( successor != NULL )
		{
			successor->process( req );	
		}
	}
};

class LowLevelProcessor : public ILevelProcessor
{
public:
	virtual void process( Request* req )
	{
		if( req->getLevel(  ) == LOW )
		{
			cout<<"low level processor"<<endl;
			return;
		}

		ILevelProcessor* successor = getSuccessor(  );
		if( successor != NULL )
		{
			successor->process( req );	
		}
	}
};

int main( void )
{
	Request request( LOW );

	HighLevelProcessor high;
	MiddleLevelProcessor mid;
	LowLevelProcessor low;

	low.setSuccessor( &mid );
	mid.setSuccessor( &high );
	high.setSuccessor( NULL );

	low.process( &request );

	request.setLevel( HIGH );
	low.process( &request );

	request.setLevel( MIDDLE );
	low.process( &request );

	return 0;
}
