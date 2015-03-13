#include <iostream>
#include <string>
#include <boost/scoped_ptr.hpp>

using namespace std;

class Meeting
{
public:
	explicit Meeting( const string& place, const string& date )
		:m_place( place ), m_date( date )
	{
	}

	void meeting(  )
	{
		cout<<"place: "<<m_place<<" date: "<<m_date<<endl;
		checking(  );
		doMeeting(  );
		meetingFeedback(  );
	}

	virtual ~Meeting(  )
	{
	}
protected:
	virtual void checking(  )
	{
		cout<<"all people can enter"<<endl;
	}
	virtual void doMeeting(  )
	{
		cout<<"default meeting"<<endl;
	}
	virtual void meetingFeedback(  )
	{
		cout<<"default meeting feedback"<<endl;
	}
	
private:
	string m_place;
	string m_date;
};

class BoardMeeting : public Meeting
{
public:
	explicit BoardMeeting(  const string& place, const string& date )
		: Meeting( place, date )
	{
	}

protected:
	virtual void checking(  )
	{
		cout<<"only stockholder can checking!"<<endl;
	}
	virtual void doMeeting(  )
	{
		cout<<"meeting content is where to go!"<<endl;
	}
	virtual void meetingFeedback(  )
	{
		cout<<"stockholders choise what to do!"<<endl;
	}
};

int main( void )
{
	string place( "LA. USA" );
	string date( "2015-10-1" );
	boost::scoped_ptr<Meeting> meeting( new BoardMeeting( place, date ) );
	meeting->meeting(  );
	
	return 0;
}
