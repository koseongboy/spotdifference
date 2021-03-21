
#include <bangtal.h>
#include <stdio.h>
#include<string.h>

ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown, float scale) {

    ObjectID object = createObject(image);

    locateObject(object, scene, x, y);

    if (shown) {
        showObject(object);
    }
    scaleObject(object, scale);

    return object;

}

SceneID startScreen, game1, restart;

ObjectID restartBotton, menu, start, end, howto, problem1, life1, life2, life3;

ObjectID left1[5];
ObjectID right1[5];
ObjectID eleft1[5];
ObjectID eright1[5];
Second remaintime;
TimerID timer1;

float time = 60.0f;

bool first[5];


int EX[5] = {120 ,225 , 440, 375, 470};
int EY[5] = {265, 505, 695, 165, 135};

int life = 3;


void startGame() {
    life = 3;
    showObject(life2);
    showObject(life3);
    enterScene(game1);
    setTimer(timer1, time);
    startTimer(timer1);
}

void endGame(bool success) {
    if (success) {
        stopTimer(timer1); 
        

        
        showMessage("틀린 그림을 모두 찾았어요!");
        enterScene(startScreen);
    }
    else {
        showMessage("세 번 틀렸어요 ㅠㅠ");
        enterScene(restart);
        stopTimer(timer1);
    }
    for (int i = 0; i < 5; i++) {
        hideObject(left1[i]);
        hideObject(right1[i]);
        showObject(eleft1[i]);
        showObject(eright1[i]);
    }

}

void reduceLife() {
    if (life == 3) {
        life -= 1;
        hideObject(life3);
    }
    else if (life == 2) {
        life -= 1;
        hideObject(life2);
    }
    else if (life == 1) {
        endGame(false);
    }
}

void correct(ObjectID object1, ObjectID object2, ObjectID object3, ObjectID object4, bool stage, int check) {
    showObject(object1);
    showObject(object2);
    hideObject(object3);
    hideObject(object4);
        first[check] = true;
        
        if (first[0] == true && first[1] == true && first[2] == true && first[3] == true && first[4] == true && first[5] == true && first[6] == true) {
            endGame(true);
        }
    


 
}

bool checkIn(int x, int y, int cx, int cy, int r) {
    return (x > cx - r && x < cx + r && y > cy - r && y < cy + r);
}



ObjectID lCheck(SceneID scene, int x, int y) {

    ObjectID object = createObject("images\\check.png", scene, x - 25, y - 25, false, 1.0f);
    return object;

}
ObjectID rCheck(SceneID scene, int x, int y) {

    ObjectID object = createObject("images\\check.png", scene, x + 615, y - 25, false, 1.0f);
    return object;

}
ObjectID elCheck(SceneID scene, int x, int y) {

    ObjectID object = createObject("images\\empty.png", scene, x - 200, y - 200, true, 1.0f);
    return object;

}
ObjectID erCheck(SceneID scene, int x, int y) {

    ObjectID object = createObject("images\\empty.png", scene, x + 440, y - 200, true, 1.0f);
    return object;

}


void mouseCallback(ObjectID object, int x, int y, MouseAction action) {

    if (object == end) {
        endGame();
    }

    else if (object == start) {
        startGame();

    }

    else if (object == howto) {
        showMessage("제시된 그림에서 다른 부분을 찾아 클릭하세요! \n 목숨은 세 개 입니다!");
    }

    else if (object == menu) {
        enterScene(startScreen);
    }

    else if (object == restartBotton) {
        startGame();
    }
    for (int i = 0; i < 5; i++) {
        if (object == eleft1[i] || object == eright1[i]) {
            correct(left1[i], right1[i], eleft1[i], eright1[i], true, i);
            if (first[0] == true && first[1] == true && first[2] == true && first[3] == true && first[4] == true) {
                endGame(true);
            }
    }

    }
    

    if (object == problem1) {
        reduceLife();
    }

}

void timerCallback(TimerID timer) {
    if (timer == timer1) {
        endGame(false);
    }
}

int main()
{   
    for (int i = 0; i < 5; ++i) {
        first[i] = false;
    }
    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);

    restart = createScene("GAME OVER", "images\\gameover.png");

    menu = createObject("images\\menu.png", restart, 590, 20, true, 0.5f);

    restartBotton = createObject("images\\restart.png", restart, 590, 70, true, 1.0f);

    startScreen = createScene("틀린그림찾기", "images\\main.png");

    start = createObject("images\\start.png", startScreen, 590, 130, true, 1.0f);

    howto = createObject("images\\howto.png", startScreen, 590, 70, true, 0.5f);

    end = createObject("images\\end.png", startScreen, 590, 20, true, 1.0f);

    game1 = createScene("1단계", "images\\problem1.png");

    problem1 = createObject("images\\problem1.png", game1, 0, 0, true, 1.0f);

    life1 = createObject("images\\heart.png", game1, 10, 580, true, 0.3f);

    life2 = createObject("images\\heart.png", game1, 50, 580, true, 0.3f);

    life3 = createObject("images\\heart.png", game1, 90, 580, true, 0.3f);

    for (int i = 0; i < 5; i++) {
        left1[i] = lCheck(game1, EX[i], EY[i]);

        right1[i] = rCheck(game1, EX[i], EY[i]);

        eleft1[i] = elCheck(game1, EX[i], EY[i]);

        eright1[i] = erCheck(game1, EX[i], EY[i]);
    }

    timer1 = createTimer(time);
    showTimer(timer1);
    
    startGame(startScreen);

}
