#include <bangtal.h>

#include <ctime>
#include <iostream>
using namespace bangtal;
using namespace std;
int main() {

	srand((unsigned int)time(NULL));

	auto scene = Scene::create("겨울왕국2", "Images/배경.png");

	ObjectPtr game_board[16];
	ObjectPtr init_board[16];
	int blank = 15;
	for (int i = 0; i < 16; i++) {
		string filename = "Images/" + to_string(i+1) + ".png";
		cout << filename << endl;
	
		game_board[i] = Object::create(filename, scene, 300 + (i % 4) * 150, 470 - (i / 4) * 150);
		//init_board[i] = Object::create(filename, scene, 300 + (i % 4) * 150, 470 - (i / 4) * 150);
		game_board[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)->bool {
			int j = 0;
			for (j = 0; j < 16; j++) {
				if (game_board[j] == object)
					break;

			}

			if ((j%4> 0 && j-1 == blank)||(j%4<3 && j+1 == blank)||(j>3 && j-4 == blank)||(j<12 && j+4 == blank)) {
				cout << "move " << blank << "<->" << j << endl;
				
				game_board[j]->locate(scene, 300 + (blank % 4) * 150, 470 - (blank / 4) * 150);
				game_board[blank]->locate(scene, 300 + (j % 4) * 150, 470 - (j / 4) * 150);
		// 배열 바꾸기
				game_board[j] = game_board[blank];
				game_board[blank] = object;
				blank = j;
				
				int k=0;
				for (k = 0; k < 16; k++) {
					if (game_board[k] != init_board[k])break;
				}
				if (k == 16) {
					showMessage("complete");
				}
			}
		//	cout << j << endl;
			//이미지위치바뀌기
			
			return true;
			});
	}
	game_board[blank]->hide();
	auto count = 0;
	auto timer = Timer::create(0.1f);
	timer->setOnTimerCallback([&](TimerPtr t)-> bool {
		cout << "timeout" << count <<endl;
		int n = rand() % 4;
		int j = 0;
		do {
			switch (rand() % 4) {
			case 0: //좌
				j = blank - 1; break;
			case 1: // 우 
				j = blank + 1; break;
			case 2: j = blank - 4; break; //아래
			case 3: j = blank + 4; break; //위
			}
		} while ((j < 0 || j>15) || !(j % 4 > 0 && j - 1 == blank) || (j % 4 < 3 && j + 1 == blank) || (j > 3 && j - 4 == blank) || (j < 12 && j + 4 == blank)); 
		
		if ((j > 0 && j<16) && (j % 4 > 0 && j - 1 == blank) || (j % 4 < 3 && j + 1 == blank) || (j > 3 && j - 4 == blank) || (j < 12 && j + 4 == blank))
		{
			cout << "move " << blank << "<->" << j << endl;

			game_board[j]->locate(scene, 300 + (blank % 4) * 150, 470 - (blank / 4) * 150);
			game_board[blank]->locate(scene, 300 + (j % 4) * 150, 470 - (j / 4) * 150);
			// 배열 바꾸기
			auto object = game_board[j];
			game_board[j] = game_board[blank];
			game_board[blank] = object;
			blank = j;

		}

		count++;
		if (count < 100) {
			t->set(0.1f);
			t->start();
		}
		
		return true;
		});
	timer->start();
	startGame(scene);
}