#include <vector>
#include <iostream>
#include <boost/scoped_ptr.hpp>

using namespace std;

//interface
class IObserver
{
public:
	virtual void onNotify(  ) = 0;
	virtual ~IObserver(  )
	{
	}
};

class NewsObserver : public IObserver
{
public:
	virtual void onNotify(  )
	{
		cout<<"news observer recieved"<<endl;
	}
};

class MovieObserver : public IObserver
{
	virtual void onNotify(  )
	{
		cout<<"Movie observer recieved"<<endl;
	}
};

class Observee
{
	typedef vector<IObserver*> observer_list;
	typedef observer_list::iterator observer_iter;
public:
	void addObserver( IObserver* p )
	{
		m_observerList.push_back( p );
	}
	
	void delObserver( IObserver* p )
	{
		observer_iter iter = m_observerList.begin(  );
		for( ; iter != m_observerList.end(  );  )
		{
			if( *iter == p )
			{
				iter = m_observerList.erase( iter );
			}
			else
			{
				iter++;
			}
		}
	}
	
	void notify(  )
	{
		observer_iter iter = m_observerList.begin(  );
		for( ; iter != m_observerList.end(  ); iter++ )
		{
			( *iter )->onNotify(  );
		}
	}
private:
	observer_list m_observerList;
};

int main(  )
{
	typedef boost::scoped_ptr<IObserver> type_observer_ptr;

	Observee observee;
	type_observer_ptr newsObserver(new NewsObserver(  ));
	type_observer_ptr movieObserver(new MovieObserver(  ));

	//add two observer
	observee.addObserver( newsObserver.get(  ) );
	observee.addObserver( movieObserver.get(  ) );
	observee.notify(  );
	
	//delete one
	observee.delObserver( newsObserver.get(  ) );
	observee.notify(  );

	//delete another
	observee.delObserver( movieObserver.get(  ) );
	observee.notify(  );
	
	return 0;
}
