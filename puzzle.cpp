#include <bangtal.h>
#include <stdlib.h>
#include <time.h>
using namespace bangtal;

int x[4] = { 462, 551, 641, 730 };
int y[4] = { 488, 360, 232, 104 };


void swap(ObjectPtr a, ObjectPtr b) {
	ObjectPtr temp;
	temp = a;
	a = b;
	b = temp;
}


int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	auto scene1 = Scene::create("ÄôÇªÆÒ´õ", "img/½ÃÀÛÀÌ¹ÌÁö.jpg");
	auto startButton = Object::create("img/start.png", scene1, 570, 400);

	auto game1 = Object::create("img/ÄôÇªÆÒ´õ1.jpg", scene1, 100, 200, false);
	auto game2 = Object::create("img/ÄôÇªÆÒ´õ2.jpg", scene1, 800, 200, false);
	auto game1Background = Scene::create("ÄôÇªÆÒ´õ1", "img/¹è°æ1.jpg");
	auto game2Background = Scene::create("ÄôÇªÆÒ´õ2", "img/¹è°æ2.jpg");
	auto game1Back = Object::create("img/¹è°æ1.jpg", game1Background);
	auto game2Back = Object::create("img/¹è°æ2,jpg", game2Background);

	auto game1_1 = Object::create("img/ÄôÇªÆÒ´õ1-1_01.jpg", game1Background, 462, 488);
	auto game1_2 = Object::create("img/ÄôÇªÆÒ´õ1-1_02-0000.jpg", game1Background, 551, 488);
	auto game1_3 = Object::create("img/ÄôÇªÆÒ´õ1_03.jpg", game1Background, 641, 488);
	auto game1_4 = Object::create("img/ÄôÇªÆÒ´õ1_04.jpg", game1Background, 730, 488);

	auto game1_5 = Object::create("img/ÄôÇªÆÒ´õ1_05.jpg", game1Background, 462, 360);
	auto game1_6 = Object::create("img/ÄôÇªÆÒ´õ1_06.jpg", game1Background, 551, 360);
	auto game1_7 = Object::create("img/ÄôÇªÆÒ´õ1_07.jpg", game1Background, 641, 360);
	auto game1_8 = Object::create("img/ÄôÇªÆÒ´õ1_08.jpg", game1Background, 730, 360);

	auto game1_9 = Object::create("img/ÄôÇªÆÒ´õ1_09.jpg", game1Background, 462, 232);
	auto game1_10 = Object::create("img/ÄôÇªÆÒ´õ1_10.jpg", game1Background, 551, 232);
	auto game1_11 = Object::create("img/ÄôÇªÆÒ´õ1_11.jpg", game1Background, 641, 232);
	auto game1_12 = Object::create("img/ÄôÇªÆÒ´õ1_12.jpg", game1Background, 730, 232);

	auto game1_13 = Object::create("img/ÄôÇªÆÒ´õ1_13.jpg", game1Background, 462, 104);
	auto game1_14 = Object::create("img/ÄôÇªÆÒ´õ1_14.jpg", game1Background, 551, 104);
	auto game1_15 = Object::create("img/ÄôÇªÆÒ´õ1_15.jpg", game1Background, 641, 104);

	auto game2_1 = Object::create("img/ÄôÇªÆÒ´õ2_01.jpg", game2Background, 454, 488);
	auto game2_2 = Object::create("img/ÄôÇªÆÒ´õ2_02.jpg", game2Background, 547, 488);
	auto game2_3 = Object::create("img/ÄôÇªÆÒ´õ2_03.jpg", game2Background, 640, 488);
	auto game2_4 = Object::create("img/ÄôÇªÆÒ´õ2_04.jpg", game2Background, 733, 488);

	auto game2_5 = Object::create("img/ÄôÇªÆÒ´õ2_05.jpg", game2Background, 454, 360);
	auto game2_6 = Object::create("img/ÄôÇªÆÒ´õ2_06.jpg", game2Background, 547, 360);
	auto game2_7 = Object::create("img/ÄôÇªÆÒ´õ2_07.jpg", game2Background, 640, 360);
	auto game2_8 = Object::create("img/ÄôÇªÆÒ´õ2_08.jpg", game2Background, 733, 360);

	auto game2_9 = Object::create("img/ÄôÇªÆÒ´õ2_09.jpg", game2Background, 454, 232);
	auto game2_10 = Object::create("img/ÄôÇªÆÒ´õ2_10.jpg", game2Background, 547, 232);
	auto game2_11 = Object::create("img/ÄôÇªÆÒ´õ2_11.jpg", game2Background, 640, 232);
	auto game2_12 = Object::create("img/ÄôÇªÆÒ´õ2_12.jpg", game2Background, 733, 232);

	auto game2_13 = Object::create("img/ÄôÇªÆÒ´õ2_13.jpg", game2Background, 454, 104);
	auto game2_14 = Object::create("img/ÄôÇªÆÒ´õ2_14.jpg", game2Background, 547, 104);
	auto game2_15 = Object::create("img/ÄôÇªÆÒ´õ2_15.jpg", game2Background, 640, 104);

	auto endButton1 = Object::create("img/end.png", game1Background, 50, 50);
	auto endButton2 = Object::create("img/end.png", game2Background, 50, 50);

	auto timer = Timer::create(600.f);

	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		game1->show();
		game2->show();
		startButton->hide();
		return true;
		});
	game1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game2->hide();
		game1->locate(scene1, 450, 100);
		game1Background->enter();
		showTimer(timer);
		timer->start();
		timer->start();
		timer->setOnTimerCallback([&](TimerPtr)->bool {
			showMessage("GAMEOVER");
			return true;
			});
		srand((unsigned int)time(NULL));
		int random = rand() % 4; //0 1 2 3

		return true;
		});
	game2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		game1->hide();
		game2->locate(scene1, 450, 100);
		game2Background->enter();
		showTimer(timer);
		timer->start();
		timer->setOnTimerCallback([&](TimerPtr)->bool {
			showMessage("GAMEOVER");
			return true;
			});
		return true;
		});

	endButton1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		endGame();
		return true;
		});

	endButton2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)-> bool {
		endGame();
		return true;
		});



	startGame(scene1);
	return 0;
}