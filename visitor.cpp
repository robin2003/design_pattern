#include <vector>
#include <iostream>

using namespace std;

class IVisitor;
class FileElement;
class FolderElement;

// abstract element
class IElement
{
public:
	virtual void getName(  ) = 0;
	virtual void getSize(  ) = 0;
	virtual void accept( IVisitor* visitor ) = 0;
	virtual ~IElement(  )
	{
	}
};

class IVisitor
{
public:
	virtual void doVisit( FileElement* elem ) = 0;
	virtual void doVisit( FolderElement* elem ) = 0;
	virtual ~IVisitor(  )
	{
	}
};

class DefaultVisitor : public IVisitor
{
public:
	virtual void doVisit( FileElement* elem );
	virtual void doVisit( FolderElement* elem );
	virtual ~DefaultVisitor(  )
	{
	}
};

//default implements
void DefaultVisitor::doVisit( FileElement* elem )
{
}

void DefaultVisitor::doVisit( FolderElement* elem )
{
}

class FileVisitor : public DefaultVisitor
{
public:
	virtual void doVisit( FileElement* elem )
	{
		cout<<"This is a file"<<endl;
	}
};

class FolderVisitor : public DefaultVisitor
{
public:
	virtual void doVisit( FolderElement* elem )
	{
		cout<<"This is a folder"<<endl;
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

	FileVisitor fileVisitor;
	cout<<"file visitor----"<<endl;
	fs.applyVisitor( &fileVisitor );
	FolderVisitor folderVisitor;
	cout<<"folder visitor----"<<endl;
	fs.applyVisitor( &folderVisitor );

	return 0;
}
