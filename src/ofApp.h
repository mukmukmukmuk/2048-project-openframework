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
		void setup(); // ���� ���� �� �Ǵ� �� ũ�⸦ �Է¹ް�, ���߿� ���� ������ �ʱ�ȭ��
		void update();
		void draw(); //ȭ���� �׷���
		void exit(); //���� ��ư�� ������ �� ������, �̶� ��� �޸𸮸� free��
		void keyPressed(int key);
		void keyReleased(int key); // Ű�� �������� ������ �� ����,'w', 'a', 's', 'd' Ű�� ������ �� ������ ������ ���⿡ �°� �̵���Ŵ
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void addition(); // �������� ���� �߰� ��Ŵ, �̶� 2/3 Ȯ���� 2��, 1/3 Ȯ���� 4�� �߰� ��Ŵ
		void init(); // ó���� �迭�� ũ�⸦ �������ϰ�, addition()�� �̿��� ���� 2�� �߰�����, �ʱ�ȭ���� ������
		bool check(); // ������ ���� �� �̻� ������ ������ �� �������� check��
		void sw(int k); //k�� 1�϶� ����������, k�� 0�϶� �������� ������ �̵���Ŵ
		void transpose(); // 1����(n*n/1) �迭�� 2����(n/n)���� ǥ������ ��, ��� ���� ���� �ٲ�
		int n, mx; //n�� ���� ���� �� �Ǵ� ���� ũ�⸦ �ǹ���, mx�� ���鿡 �ִ� ������ �ִ����� 2048�� �Ǹ� ������ �����Ŵ
		int line_len; // ������ �� ĭ�� ũ�⸦ �ǹ���.
		int score; // ���� ������ ������
		vector<int>arr; // ���� ���� ������ ������ ���� ������
		vector<int>bin; // ���� �ǿ��� 0�� ���� ���� ������ �ε����� ������
		ofTrueTypeFont myFont;
};
