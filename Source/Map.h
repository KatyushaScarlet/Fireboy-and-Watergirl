#define MAP_SIZE_WIDTH 40
#define MAP_SIZE_HEIGHT 30
#define MAP_GIRD_PIXEL 32

namespace game_framework
{
	class Map
	{
	public:
		Map();
		void LoadMapArray(int map_array[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH]);
		void LoadBitmap();
		void OnShow();
		~Map();
	private:
		int				map[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];
		CMovingBitmap	background_ingame;	//±³¾°Í¼
		CMovingBitmap	wall;				//Ç½±Ú
	};
}