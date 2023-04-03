#include "ofApp.h"


void ofApp :: exit() {
	//�Ҵ��� �����޸� �ݳ�
	arr.clear();
	bin.clear();
}
//--------------------------------------------------------------
void ofApp::setup() {
	// �� �� �Ǵ� �� ���� ĭ �� �Է�
	cout << "2048 ������ ĭ ���� �Է��Ͻÿ�. (2�̻��� ����) :";
	cin >> n;
	//�� �� �� ������ ����
	init();
	// ���� Ÿ��Ʋ
	ofSetWindowTitle("2048 Game");

	//�ʱ� �� ����
	ofBackground(255, 255,255);
	ofSetFrameRate(15);
	myFont.loadFont("verdana.ttf", 30, true, true);
	score = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
	// �� ĭ�� ���� ����
	line_len = 100;
	//�ִ��� 2048�̸� ���� ����
	int sz = n * n;
	for (int i = 0; i < sz; i++)mx = max(mx,arr[i]);
	if (mx == 2048) {
		myFont.drawString("Good Job!", 0, line_len * 2);
		myFont.drawString("SCORE : " + to_string(score), 0, line_len * 3);
		// ���� ������ �ȵǵ��� 0���� �ʱ�ȭ
		for (int i = 0; i < sz; i++)arr[i]=0;
	}
	// ���� �� ������ �� ������ ���� ���� ���� ���¸� �׸�
	else if (check()) {
		// �� �׸���
		ofSetColor(102, 102, 102);
		ofRect(0, 0, line_len*n, line_len*n);
		ofSetColor(51, 51, 51);
		ofSetLineWidth(5);
		for (int i = 0; i <= n; i++) {
			ofDrawLine(0, i*line_len, line_len*n, i*line_len);
			ofDrawLine(i*line_len, 0, i*line_len, line_len*n);
		}
		// ���� �� �׸���
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				ofSetColor(0);
				int tmp = arr[i * n + j];
				switch (tmp) {
				case 0: continue;break;
				case 2:	ofSetColor(210, 219, 226);break;
				case 4:ofSetColor(255, 250, 101);break;
				case 8:ofSetColor(255, 192, 72);break;
				case 16:ofSetColor(255, 159, 26);break;
				case 32:ofSetColor(255, 204, 204);break;
				case 64:ofSetColor(255, 94, 87);break;
				case 128:ofSetColor(196, 251, 109);	break;
				case 256:ofSetColor(11, 232, 129);break;
				case 512:ofSetColor(52, 231, 228);break;
				case 1024:ofSetColor(205, 132, 241);break;
				case 2048:ofSetColor(87, 95, 207);
				default: break;
				}
				ofRect(j*line_len, i*line_len, line_len, line_len);
				ofSetColor(51, 51, 51);
				ofSetLineWidth(5);
				ofNoFill();
				ofRect(j*line_len, i*line_len, line_len, line_len);
				ofFill();
				ofSetColor(0);
				myFont.drawString(to_string(arr[i*n + j]), j*line_len, (i + 1)*line_len-line_len/3);
			}
		}
		//���� �׸���
		myFont.drawString("SCORE : "+to_string(score), 0,line_len*(n + 1));
	}
	// �� �̻� ���� ������ �� ������ ���� ����
	else {
		
		myFont.drawString("GAME OVER", 0, line_len*2);
		myFont.drawString("SCORE : " + to_string(score), 0, line_len * 3);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

void ofApp::keyReleased(int key) {

	//���� �̵�
	if (key == 'W' || key == 'w') {
		transpose();
		sw(0);
		transpose();
		addition();
	}
	//�������� �̵�
	if (key == 'a' || key == 'A') {
		sw(0);
		addition();
	}

	//���������� �̵�
	if (key == 'd' || key == 'D') {
		sw(1);
		addition();
	}

	//�Ʒ��� �̵�
	if (key == 's' || key == 'S') {
		transpose();
		sw(1);
		transpose();
		addition();
	}

}

//--------------------------------------------------------------


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::addition() {
	int sz = n * n;
	// bin �迭�� �Ҵ�� �� ����
	bin.clear();
	// arr�� �迭���� 0�� ������ �ε����� bin�� �߰�
	for (int i = 0; i < sz; i++) {
		if (!arr[i])bin.push_back(i);
	}
	//num�� bin�� �ε��� �߿��� ������ ���� ������ ��
	if (!bin.empty()) {
		int num = rand() % bin.size();
		//tmp�� ������ �ε����� bin ��, �� arr�� ���� 0��, ������ arr�� �ε�����
		int tmp = bin[num];


		// rand�� �⺻�� ���� ����
		srand(time(NULL));
		int t = rand() % 3;
		//2/3 Ȯ���� arr�� 2 �߰�
		if (t != 0)arr[tmp] = 2;
		// 1/3 Ȯ���� arr�� 4�߰�
		else arr[tmp] = 4;
	}
}


void ofApp::init() {
	srand(time(NULL));
	//�迭�� ũ�� �缳��
	arr.resize(n * n, 0);
	//�����ϰ� �� ĭ ä��
	addition();
	addition();
}

bool ofApp::check() {
	int tmp = n * n;
	// bin�� �� �迭, �� arr�� 0�� ���� ���� �������� ���ϸ� ����
	if (!bin.empty())return true;

	// ������, �Ʒ��ʿ� ���� ���� ���� ���� �����Ѵٸ� ������ �� ����
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i+1 <= n - 1) {
				if (arr[(i+1)*n+j] == arr[i*n+j])return true;
			}
			if (j + 1 <= n - 1) {
				if (arr[i*n+j] == arr[i*n+j+1])return true;
			}
		}
	}
	// ���� ������ ��� �������� �ʴ´ٸ� ����
	return false;
}

void ofApp::sw(int k) {
	int tmp = n * n;
	queue<int>que;
	// k�� 1�� �� ������ ���������� �̵�
	if (k) {
		// �����ʿ�������  ���� ����
		for (int i = tmp - 1; i >= 0; i--) {
			// arr�� 0�� �ƴ� ��쿡 que�� �� �߰�, �׸��� arr���� 0���� �ٲ�
			if (arr[i]) {
				que.push(arr[i]);
				arr[i] = 0;
			}
			// �� ���� �� �о��� ��쿡 ����
			if (i % n == 0) {
				int j = i + n - 1;
				// �����ʿ��� ����, arr�� ���� 0�̸� que�� front������ ��ü, 
				// arr�� front�� ���ٸ� arr�� 2��, �� ��� ��� �ƴ϶�� arr�� ���� front�� ��ü
				while (!que.empty()) {
					int t = que.front();
					que.pop();
					if (arr[j] == 0)arr[j] = t;
					else if (arr[j] == t) {
						arr[j--] = 2 * t;
						//���� ���� 2�� ��ŭ ���� ����
						score += 2 * t;
					}
					else {
						arr[--j] = t;
					}
				}
			}
		}
	}
	// k�� 0�� �� ������ �������� �̵�
	else {
		// ���ʿ������� ���� ����
		for (int i = 0; i <= tmp - 1; i++) {
			// arr�� 0�� �ƴ� ��쿡 que�� �� �߰�, �׸��� arr���� 0���� �ٲ�
			if (arr[i]) {
				que.push(arr[i]);
				arr[i] = 0;
			}
			// �� ���� �� �о��� ��쿡 ����
			if (i % n == n - 1) {
				// ���ʿ��� ����, arr�� ���� 0�̸� que�� front������ ��ü, 
				// arr�� front�� ���ٸ� arr�� 2��, �� ��� ��� �ƴ϶�� arr�� ���� front�� ��ü
				int j = i - n + 1;
				while (!que.empty()) {
					int t = que.front();
					que.pop();
					if (arr[j] == 0)arr[j] = t;
					else if (arr[j] == t) {
						arr[j++] = 2 * t;
						//���� ���� 2�� ��ŭ ���� ����
						score += 2 * t;
					}
					else {
						arr[++j] = t;
					}
				}
			}
		}
	}
}

void ofApp::transpose() {
	int tmp = n * n;
	int k = n - 1;
	// 1���� �迭�� 2������ n/n ��ķ� ǥ������ �� �밢��(0,0�� n-1,n-1�� �մ� ��)�� �������� ���κи� Ž���ϸ�,
	// ��� ���� ���� �ٲ�
	for (int i = 0; i < tmp; i += (n + 1)) {
		for (int j = i + 1; j <= i + k; j++) {
			int x = j / n, y = j % n;
			swap(arr[x * n + y], arr[y * n + x]);
		}
		k--;
	}
}

