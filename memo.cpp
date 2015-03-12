#include <iostream>
#include <vector>
#include <boost/shared_ptr.hpp>

using namespace std;

class GameMemo
{
public:
	explicit GameMemo(int index, int scene  )
		:m_index( index ), m_scene( scene )
	{
	}
	int getIndex(  )
	{
		return m_index;
	}
	void setIndex( int index )
	{
		m_index = index;
	}
	int getScene(  )
	{
		return m_scene;
	}
	void setScene( int scene )
	{
		m_scene = scene;
	}

	~GameMemo(  )
	{
		cout<<"----------game memo destroy"<<endl;
	}
private:
	int m_index;
	int m_scene;
};

class MemoMgr
{
public:
	typedef boost::shared_ptr<GameMemo> GAME_MEMO_PTR;
	typedef vector<GAME_MEMO_PTR >::iterator GAME_MEMO_ITER;
	
	void addMemo( GameMemo* memo )
	{
		GAME_MEMO_PTR tmp( memo );
		m_memos.push_back( tmp );
	}
	
	GameMemo* getMemo( int index )
	{
		GameMemo* memo = NULL;
		GAME_MEMO_ITER iter = m_memos.begin(  );
		for( ; iter != m_memos.end(  ); iter++ )
		{
			memo = ( *iter ).get(  );
			if( memo->getIndex(  ) == index )
			{
				return memo;
			}
		}

		return memo;
	}
private:
	vector<GAME_MEMO_PTR> m_memos;
};

class Game
{
public:
	Game( int index, int scene )
		:m_index( index ), m_scene( scene )
	{
	}

	GameMemo* createMemo(  )
	{
		return new GameMemo( m_index, m_scene );
	}

	void resetGame( GameMemo* memo )
	{
		m_index = memo->getIndex(  );
		m_scene = memo->getScene(  );
	}

	void setIndex( int index )
	{
		m_index = index;
	}
	
	void setScene( int scene )
	{
		m_scene = scene;
	}

	void toString(  )
	{
		cout<<"index:"<<m_index<<" scene:"<<m_scene<<endl;
	}

private:
	int m_index;
	int m_scene;
};

int main( void )
{
	MemoMgr memoMgr;
	GameMemo* memo = NULL;
	Game game( 0, 0 );

	cout<<"pass to gate 1"<<endl;
	game.setIndex( 1 );
	game.setScene( 1 );
	memo = game.createMemo(  );
	memoMgr.addMemo( memo );
	game.toString(  );
	
	cout<<"pass to gate 2"<<endl;
	game.setIndex( 2 );
	game.setScene( 2 );
	memo = game.createMemo(  );
	memoMgr.addMemo( memo );
	game.toString(  );

	cout<<"pass to gate 3"<<endl;
	game.setIndex( 3 );
	game.setScene( 3 );
	memo = game.createMemo(  );
	memoMgr.addMemo( memo );
	game.toString(  );
	
	cout<<"rollback to 2"<<endl;
	memo = memoMgr.getMemo( 2 );
	game.resetGame( memo );
	game.toString(  );
	
	return 0;
}
