#include <iostream>

using namespace std;

class ISurfStratage
{
public:
	virtual void doSurfing(  ) = 0;
	virtual ~ISurfStratage(  ) {
		
	}
};

class WifiSurfStratage : public ISurfStratage
{
public:
	virtual void doSurfing(  )
	{
		cout<<"using wifi surfing"<<endl;
	}
};

class WiredSurfStratage : public ISurfStratage
{
public:
	virtual void doSurfing(  )
	{
		cout<<"using wired surfing"<<endl;
	}
};

// internet surf has lot of stragage
class InternetSurf
{
public:
	InternetSurf( ISurfStratage* p )
		: m_pstratage( p )
	{
		
	}

	void setStratage( ISurfStratage* p )
	{
		m_pstratage = p;
	}
	
	void doSurf(  )
	{
		m_pstratage->doSurfing(  );
	}
private:
	ISurfStratage* m_pstratage;
};


int main(  )
{
	WifiSurfStratage wifi;
	WiredSurfStratage wired;
	// wifi surfing
	InternetSurf internet( &wifi );
	internet.doSurf(  );

	// wired surfing
	internet.setStratage( &wired );
	internet.doSurf(  );

	return 0;
}
