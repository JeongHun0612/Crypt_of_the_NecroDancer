#pragma once
#include "../../../2DFrameWork/DesingPattern/SingletonBase.h"

#define MAX_LOBBY_COL			13
#define MAX_LOBBY_ROW			15

#define MAX_STAGE1_1_COL		27
#define MAX_STAGE1_1_ROW		28

#define MAX_STAGE1_2_COL		34
#define MAX_STAGE1_2_ROW		26

#define MAX_BOSS_COL			17
#define MAX_BOSS_ROW			28

class Enemy;

enum class TILE_TYPE
{
	TERRAIN,
	WALL,
	DECO
};

enum class ENEMY_TYPE
{
	SLIME_GREEN,
	SLIME_BLUE,
	SLIME_ORANGE,
	SKELETON_NORMAL,
	SKELETON_YELLOW,
	SKELETON_BLACK,
	ZOMBIE,
	BAT_BLUE,
	BAT_RED,
	MONKEY_NORMAL,
	MONKEY_WHITE,
	GHOST,
	WRAITH,
	MINOTAUR_NORMAL,
	DRAGON_RED,
	NECRODANCER,
	SHOPKEEPER
};

enum class TERRAIN_TYPE
{
	GROUND,
	OPEN_STAIR,
	LOCK_STAIR,

	END
};

enum class WALL_TYPE
{
	NONE,
	DIRT,
	BRICK,
	STONE,
	STEEL,
	BORDER,
	DOOR,
	GOLDWALL
};

struct Node
{
	Vec2 posIdx;
	int tileIdx;
	int alpha;
	bool isCollider;
};

struct Tile
{
	TERRAIN_TYPE _terrainType;
	WALL_TYPE _wallType;

	int _idxX;
	int _idxY;

	int _frameX;
	int _frameY;

	int _alpha;
	int _hardNess;

	bool _isExist;
	bool _isCollider;
	bool _isSearch;
	bool _isLight;
};

class TileMap : public SingletonBase<TileMap>
{
private:
	vector<vector<Tile*>> _vTiles;
	vector<Tile*> _vTerrainTile;
	vector<Tile*> _vWallTile;
	vector<Enemy*> _vEnemy;
	vector<Item*> _vItem;

	vector<Node> _vShowNode;

	int _tileMaxCol;
	int _tileMaxRow;
	int _stairTileIdx;

	bool _isLobby;
	bool _isNextStage;

public:
	HRESULT init(int currentScene);
	void update(void);
	void relese(void);
	void render(HDC hdc);

	vector<vector<Tile*>>& getTiles() { return _vTiles; }
	vector<Tile*>& getTerrainTile() { return _vTerrainTile; }
	vector<Tile*>& getWallTile() { return _vWallTile; }
	vector<Enemy*>& getEnemyList() { return _vEnemy; }
	vector<Item*>& getItemList() { return _vItem; }

	void addEnemyList(Enemy* enemy);

	int getTileMaxCol() { return _tileMaxCol; }
	void setTileMaxCol(int tileMaxCol) { _tileMaxCol = tileMaxCol; }

	int getTileMaxRow() { return _tileMaxRow; }
	void setTileMaxRow(int tileMaxRow) { _tileMaxRow = tileMaxRow; }

	bool getIsNextStage() { return _isNextStage; }

	TileMap() {}
	~TileMap() {}

private:
	void tileSet(HDC hdc, vector<Tile*> vTile, TILE_TYPE tileType);					// 타일 출력
	void getShowTileBFS(vector<Node>& vShowNode);		// 플레이어 시야 범위 (BFS)
	
	void showTileNum(HDC hdc);			// 타일 번호 출력
	void showTileDist(HDC hd);			// 플레이어에서 타일간의 거리 출력
	void showEnemyCollider(HDC hdc);	// 적 객체 충돌체
	void showMiniMap(HDC hdc);
};

