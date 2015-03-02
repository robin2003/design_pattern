#include <vector>
#include <iostream>

using namespace std;

class IVisitor;
// abstract element
class IElement
{
public:
	virtual void getName(  ) = 0;
	virtual void getSize(  ) = 0;
	virtual void accept( IVisitor* visitor ) = 0;
	virtual ~IElement(  ) {
	}
};

class IVisitor
{
public:
	virtual void doVisit( IElement* elem ) = 0;
	virtual ~IVisitor(  ) {
		
	}
};

class SizeVisitor : public IVisitor
{
public:
	virtual void doVisit( IElement* elem )
	{
		elem->getSize(  );
	}
};

class NameVisitor : public IVisitor
{
public:
	virtual void doVisit( IElement* elem )
	{
		elem->getName(  );		
	}
};

class FileElement : public IElement
{
public:
	FileElement( char* name, const int size )
		:m_Name( name ), m_Size( size )
	{
		
	}
	virtual void getName(  )
	{
		cout<<"File name is "<<m_Name<<endl;
	}
	virtual void getSize(  )
	{
		cout<<"file:"<<m_Name<<"  size:"<<m_Size<<endl;
	}

	virtual void accept( IVisitor* visitor )
	{
		visitor->doVisit( this );
	}

private:
	char* m_Name;
	int m_Size;
};

class FolderElement : public IElement
{
public:
	FolderElement( char* name, const int size )
		:m_Name( name ), m_Size( size )
	{
		
	}
	virtual void getName(  )
	{
		cout<<"Folder name is "<<m_Name<<endl;
	}
	
	virtual void getSize(  )
	{
		cout<<"folder:"<<m_Name<<"  size:"<<m_Size<<endl;
	}

	virtual void accept( IVisitor* visitor )
	{
		visitor->doVisit( this );
	}
private:
	char* m_Name;
	int m_Size;
};

class FileSystem
{
public:
	void addElement( IElement* p )
	{
		m_Elements.push_back( p );
	}
	void applyVisitor( IVisitor* visitor )
	{
		vector<IElement*>::iterator it = m_Elements.begin(  );
		for( ; it != m_Elements.end(  ); it++ )
		{
			IElement* elem = *it;
			elem->accept( visitor );
		}
	}
private:
	vector<IElement*> m_Elements;
};


static FileSystem fs;

int main( void )
{

	FileElement fileElem( "file1" , 100 );
	FolderElement folderElem( "folder1" , 200 );

	fs.addElement( &fileElem );
	fs.addElement( &folderElem );

	SizeVisitor sizeVisitor;
	cout<<"size visitor----"<<endl;
	fs.applyVisitor( &sizeVisitor );
	NameVisitor nameVisitor;
	cout<<"name visitor----"<<endl;
	fs.applyVisitor( &nameVisitor );

	return 0;
}
