#include <bangtal.h>

#include <ctime>
#include <iostream>
using namespace bangtal;
using namespace std;

bool findBlank(int index, int blank) {
	return (index % 4 > 0 && index - 1 == blank) || (index % 4 < 3 && index + 1 == blank) || (index > 3 && index - 4 == blank) || (index < 12 && index + 4 == blank);
	
};

auto indexToBlank(ObjectPtr arr[], ScenePtr scene, int index, int blank) {
	return arr[index]->locate(scene, (blank % 4) * 320, 540 - (blank / 4) * 180);
	
};
auto blankToindex(ObjectPtr arr[], ScenePtr scene, int index, int blank) {
	return arr[blank]->locate(scene, (index % 4) * 320, 540 - (index / 4) * 180);
};
auto swap(ObjectPtr arr[], ObjectPtr swapobject, int index, int blank) {
	arr[index] = arr[blank];
	arr[blank] = swapobject;
	blank = index;
};
auto swap2(ObjectPtr arr[], ObjectPtr swapobject, int index, int blank) {
	swapobject = arr[index];
	arr[index] = arr[blank];
	arr[blank] = swapobject;
	blank = index;
};

auto makeSwitch(int index, int blank, bool (*findBlank)(int, int) ){
	srand((unsigned)time(NULL));
	do { // blank 15 j 11
		switch (rand() % 4) {
		case 0: return index = blank - 1; break;//좌
		case 1: return index = blank + 1; break;//우
		case 2: return index = blank - 4; break;//위
		case 3: return index = blank + 4; break;//아래
		}
	} while (index < 0 || index > 15 || !(findBlank(index, blank)));
};


int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	srand(time(NULL));

	auto startscene = Scene::create("시작페이지", "img/맨처음시작.png"); //시작이미지
	auto scene = Scene::create("쿵푸팬더", "img/배경.png"); //배경이미지
	auto scene2 = Scene::create("해리포터", "img/배경.png"); // 배겨이미지
	auto scene3 = Scene::create("쿵푸팬더 정답이미지", "img/쿵푸팬더.jpg");
	auto scene4 = Scene::create("해리포터 정답이미지", "img/해리포터.jpg");
	auto game1 = Object::create("img/쿵푸팬더선택.jpg", startscene, false); //쿵푸팬더 선택
	auto game2 = Object::create("img/해리포터선택.png", startscene, 640, 0, false); // 해리포터 선택
	auto startbutton = Object::create("img/start.png", startscene, 570, 400);
	
	time_t start_time1;
	time_t start_time2;

	startbutton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		startbutton->hide();
		game1->show();
		game2->show();
		showMessage("퍼즐맞출 그림선택하세요, 선택 후 spacebar를 누르면 정답화면이 보입니다.");
		return true;
		});

	game1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene->enter();
		start_time1 = time(NULL);
		return true;
		});

	game2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		scene2->enter();
		start_time2 = time(NULL);
		return true;
		});

	// 쿵푸팬더 
	int blank = 15;
	int blank2 = 15;
	ObjectPtr game_board[16];
	ObjectPtr init_board[16];
	ObjectPtr game_board2[16];
	ObjectPtr init_board2[16];

	for (int i = 0; i < 16; i++) {
		string filename = "img/" + to_string(i + 21) + ".jpg";
		game_board2[i] = Object::create(filename, scene2, (i % 4) * 320, 540 - (i / 4) * 180);
		init_board2[i] = game_board2[i];



		game_board2[i]->setOnMouseCallback([&](ObjectPtr object2, int, int, MouseAction)-> bool {
			int index2;
			for (index2 = 0; index2 < 16; index2++) {
				if (game_board2[index2] == object2)
					break;
			}
			if (findBlank(index2, blank2)) {
				cout << "move" << blank2 << "<->" << index2 << endl;
				indexToBlank(game_board2, scene2, index2, blank2);
				blankToindex(game_board2, scene2, index2, blank2);

				game_board2[index2] = game_board2[blank2];
				game_board2[blank2] = object2;
				blank2 = index2; //바꾸기함수로 바꾸자
				//swap(game_board2, object2, index2, blank2);
				int k2;
				for (k2 = 0; k2 < 16; k2++) {
					if (game_board2[k2] != init_board2[k2])break;
				}
				if (k2 == 16) {
					auto end_time2 = time(NULL);
					cout << difftime(end_time2, start_time2) << endl;
					string buf2 = to_string(difftime(end_time2, start_time2)) + "걸렸습니다!!";
					showMessage("완성 buf2.c_str()");
				}
			}
			return true;
			});
	}

	for (int i = 0; i < 16; i++) {
		string filename = "img/" + to_string(i) + ".jpg";
		game_board[i] = Object::create(filename, scene, (i % 4) * 320, 540 - (i / 4) * 180);
		init_board[i] = game_board[i];

		game_board[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
			int index1;
			for (index1 = 0; index1 < 16; index1++) {
				if (game_board[index1] == object)
					break;
			}
			if (findBlank(index1, blank)) {
				cout << "move" << blank << "<->" << index1 << endl;
				//game_board[index1]->locate(scene, (blank % 4) * 320, 540 - (blank / 4) * 180);
				//game_board[blank]->locate(scene, (index1 % 4) * 320, 540 - (index1 / 4) * 180);
				indexToBlank(game_board, scene, index1, blank);
				blankToindex(game_board, scene, index1, blank);
				game_board[index1] = game_board[blank];
				game_board[blank] = object;
				blank = index1; //바꾸기함수로 바꾸자
				
				//swap(game_board, object, index1, blank);
				int k;
				for (k = 0; k < 16; k++) {
					if (game_board[k] != init_board[k])break;
				}
				if (k == 16) {
					auto end_time1 = time(NULL);
					cout << difftime(end_time1, start_time1) << endl;
					string buf1 = to_string(difftime(end_time1, start_time1)) + "걸렸습니다!!";
					showMessage("완성 buf1.c_str()");
				}
			}
			return true;
			});
	}

	game_board[blank]->hide();
	game_board2[blank]->hide();



	int count = 0;
	auto timer = Timer::create(0.1f);
	timer->setOnTimerCallback([&](TimerPtr t)->bool {
		cout << "harrypotter-timeout!! " << count << endl;

		int index3 = 0;
		do {
			switch (rand() % 4) {
			case 0:index3 = blank2 - 1; break;//좌
			case 1: index3 = blank2 + 1; break;//우
			case 2: index3 = blank2 - 4; break;//위
			case 3:index3 = blank2 + 4; break;//아래
		}
		} while (index3 < 0 || index3 > 15 || !(findBlank(index3, blank2))); 


		indexToBlank(game_board2, scene2, index3, blank2);
		blankToindex(game_board2, scene2, index3, blank2);
		
		auto object = game_board2[index3];
		game_board2[index3] = game_board2[blank2];
		game_board2[blank2] = object;
		blank2 = index3;

		count++;
		if (count < 100) {
			t->set(0.1f);
			t->start();
		}
		return true;
		});

	int count2 = 0;
	auto timer2 = Timer::create(0.1f);
	timer2->setOnTimerCallback([&](TimerPtr time)->bool {
		cout << "panda- timeout!! " << count << endl;
		//blank 움직여주기
		int j = 0;

		do { // blank 15 j 11
			switch (rand() % 4) {
			case 0: j = blank - 1; break;//좌
			case 1: j = blank + 1; break;//우
			case 2: j = blank - 4; break;//위
			case 3: j = blank + 4; break;//아래
			}
		} while (j < 0 || j > 15 || !(findBlank(j, blank))); // not movable
	
		indexToBlank(game_board, scene, j, blank);
		blankToindex(game_board, scene, j, blank);

		auto object = game_board[j];
		game_board[j] = game_board[blank];
		game_board[blank] = object;
		blank = j;

		count2++;
		if (count2 < 100) {
			time->set(0.1f);
			time->start();
		}
		return true;
		});
	timer2->start();
	timer->start();

	scene->setOnKeyboardCallback([=](ScenePtr answerscene, int key, bool pressed)->bool {
		if (key == 75) {
			scene3->enter();
		}
		return true;
		});
	scene3->setOnKeyboardCallback([=](ScenePtr answerscene, int key, bool pressed)->bool {
		if (key == 75) {
			scene->enter();
		}
		return true;
		});
	scene2->setOnKeyboardCallback([=](ScenePtr answerscene, int key, bool pressed)->bool {
		if (key == 75) {
			scene4->enter();
		}
		return true;
		});
	scene4->setOnKeyboardCallback([=](ScenePtr answerscene, int key, bool pressed)->bool {
		if (key == 75) {
			scene2->enter();
		}
		return true;
		});

	startGame(startscene);
	return 0;
}
