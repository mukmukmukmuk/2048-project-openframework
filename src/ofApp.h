#pragma once

#include "ofMain.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <queue>

class ofApp : public ofBaseApp{

	public:
		void setup(); // 게임 판의 행 또는 열 크기를 입력받고, 나중에 쓰일 값들을 초기화함
		void update();
		void draw(); //화면을 그려줌
		void exit(); //종료 버튼을 눌렀을 때 실행함, 이때 모든 메모리를 free함
		void keyPressed(int key);
		void keyReleased(int key); // 키가 눌러졌다 떼졌을 때 실행,'w', 'a', 's', 'd' 키를 눌렀을 때 블럭들을 각각의 방향에 맞게 이동시킴
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void addition(); // 무작위로 블럭을 추가 시킴, 이때 2/3 확률로 2를, 1/3 확률로 4를 추가 시킴
		void init(); // 처음에 배열의 크기를 재조정하고, addition()을 이용해 블럭을 2개 추가시켜, 초기화면을 셋팅함
		bool check(); // 게임이 끝나 더 이상 블럭들이 움직일 수 없는지를 check함
		void sw(int k); //k가 1일때 오른쪽으로, k가 0일때 왼쪽으로 블럭들을 이동시킴
		void transpose(); // 1차원(n*n/1) 배열을 2차원(n/n)으로 표현했을 때, 행과 열의 값을 바꿈
		int n, mx; //n은 게임 판의 행 또는 열의 크기를 의미함, mx는 블럭들에 있는 숫자의 최댓값으로 2048이 되면 게임을 종료시킴
		int line_len; // 게임판 한 칸의 크기를 의미함.
		int score; // 현재 점수를 저장함
		vector<int>arr; // 게임 판의 각각의 블럭들의 값을 저장함
		vector<int>bin; // 게임 판에서 0의 값을 갖는 블럭들의 인덱스를 저장함
		ofTrueTypeFont myFont;
};
