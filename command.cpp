#include <vector>
#include <iostream>

using namespace std;

class CommandTarget;
class ICommand
{
public:
	virtual void execute(  ) = 0;
	virtual void setTarget( CommandTarget* p )
	{
	}
	virtual ~ICommand(  )
	{
	}
};

class CommandTarget
{
public:
	void action(  )
	{
		cout<<"execute command at target"<<endl;
	}
};

class ConcreteCommand: public ICommand
{
public:
	virtual void execute(  )
	{
		cout<<"concrete command"<<endl;
		m_cmdTgt->action(  );
	}
	void setTarget( CommandTarget* p )
	{
		m_cmdTgt = p;
	}
private:
	CommandTarget* m_cmdTgt;
};

class Agent
{
public:
	void exec(  )
	{
		vector<ICommand*>::iterator iter = m_cmdLists.begin(  );
		for( ; iter != m_cmdLists.end(  ); iter++ )
		{
			( *iter)->execute(  );
		}
	}
	void addCommand( ICommand* cmd )
	{
		m_cmdLists.push_back( cmd );
	}
private:
	vector<ICommand*> m_cmdLists;
};


int main(  )
{
	Agent newAgent;
	CommandTarget ct;
	ICommand* cmd = new ConcreteCommand(  );
	
	if( cmd == NULL )
	{
		return -1;
	}
	cmd->setTarget( &ct );
	newAgent.addCommand( cmd );
	newAgent.exec(  );
	
	delete cmd;
	
	return 0;
}

