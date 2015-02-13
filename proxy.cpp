#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace std;

class Subject
{
public:
	virtual void display(  ) = 0;
	virtual ~Subject(  )
	{
		
	}
};

class RealSubject : public Subject
{
public:
	virtual void display(  )
	{
		cout<<"real subject display"<<endl;
	}
	~RealSubject(  )
	{
		cout<<"deconstruction realSubject"<<endl;
	}
};

class SubjectProxy : public Subject
{
public:
	explicit SubjectProxy( const boost::shared_ptr<Subject> & p )
		: m_pSubject( p )
	{
		
	}
	
	virtual void display(  )
	{
		if( m_pSubject != NULL )
			m_pSubject->display(  );
	}
private:
	const boost::shared_ptr<Subject> & m_pSubject;
};


int main(  )
{
	boost::shared_ptr<Subject> p( new RealSubject );
	SubjectProxy sp( p );
	sp.display(  );
	
	return 0;
}
