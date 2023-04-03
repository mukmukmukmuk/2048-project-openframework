#include "ofApp.h"


void ofApp :: exit() {
	//할당한 동적메모리 반납
	arr.clear();
	bin.clear();
}
//--------------------------------------------------------------
void ofApp::setup() {
	// 한 행 또는 한 열의 칸 수 입력
	cout << "2048 게임의 칸 수를 입력하시오. (2이상의 정수) :";
	cin >> n;
	//블럭 두 개 무작위 배정
	init();
	// 게임 타이틀
	ofSetWindowTitle("2048 Game");

	//초기 값 셋팅
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
	// 한 칸의 길이 설정
	line_len = 100;
	//최댓값이 2048이면 게임 종료
	int sz = n * n;
	for (int i = 0; i < sz; i++)mx = max(mx,arr[i]);
	if (mx == 2048) {
		myFont.drawString("Good Job!", 0, line_len * 2);
		myFont.drawString("SCORE : " + to_string(score), 0, line_len * 3);
		// 점수 갱신이 안되도록 0으로 초기화
		for (int i = 0; i < sz; i++)arr[i]=0;
	}
	// 블럭을 더 움직일 수 있으면 현재 게임 판의 상태를 그림
	else if (check()) {
		// 판 그리기
		ofSetColor(102, 102, 102);
		ofRect(0, 0, line_len*n, line_len*n);
		ofSetColor(51, 51, 51);
		ofSetLineWidth(5);
		for (int i = 0; i <= n; i++) {
			ofDrawLine(0, i*line_len, line_len*n, i*line_len);
			ofDrawLine(i*line_len, 0, i*line_len, line_len*n);
		}
		// 숫자 블럭 그리기
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
		//점수 그리기
		myFont.drawString("SCORE : "+to_string(score), 0,line_len*(n + 1));
	}
	// 더 이상 블럭을 움직일 수 없으면 게임 종료
	else {
		
		myFont.drawString("GAME OVER", 0, line_len*2);
		myFont.drawString("SCORE : " + to_string(score), 0, line_len * 3);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

void ofApp::keyReleased(int key) {

	//위로 이동
	if (key == 'W' || key == 'w') {
		transpose();
		sw(0);
		transpose();
		addition();
	}
	//왼쪽으로 이동
	if (key == 'a' || key == 'A') {
		sw(0);
		addition();
	}

	//오른쪽으로 이동
	if (key == 'd' || key == 'D') {
		sw(1);
		addition();
	}

	//아래로 이동
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
	// bin 배열의 할당된 값 해제
	bin.clear();
	// arr의 배열에서 0인 값들의 인덱스를 bin에 추가
	for (int i = 0; i < sz; i++) {
		if (!arr[i])bin.push_back(i);
	}
	//num은 bin의 인덱스 중에서 랜덤한 값을 추출한 것
	if (!bin.empty()) {
		int num = rand() % bin.size();
		//tmp는 랜덤한 인덱스의 bin 값, 즉 arr의 값이 0인, 무작위 arr의 인덱스임
		int tmp = bin[num];


		// rand의 기본값 새로 설정
		srand(time(NULL));
		int t = rand() % 3;
		//2/3 확률로 arr에 2 추가
		if (t != 0)arr[tmp] = 2;
		// 1/3 확률로 arr에 4추가
		else arr[tmp] = 4;
	}
}


void ofApp::init() {
	srand(time(NULL));
	//배열의 크기 재설정
	arr.resize(n * n, 0);
	//랜덤하게 두 칸 채움
	addition();
	addition();
}

bool ofApp::check() {
	int tmp = n * n;
	// bin이 빈 배열, 즉 arr에 0인 값이 없어 움직이지 못하면 종료
	if (!bin.empty())return true;

	// 오른쪽, 아래쪽에 같은 값을 가진 블럭이 존재한다면 움직일 수 있음
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
	// 위의 조건이 모두 충족되지 않는다면 종료
	return false;
}

void ofApp::sw(int k) {
	int tmp = n * n;
	queue<int>que;
	// k가 1일 때 블럭들을 오른쪽으로 이동
	if (k) {
		// 오른쪽에서부터  값을 읽음
		for (int i = tmp - 1; i >= 0; i--) {
			// arr가 0이 아닐 경우에 que에 값 추가, 그리고 arr값을 0으로 바꿈
			if (arr[i]) {
				que.push(arr[i]);
				arr[i] = 0;
			}
			// 한 행을 다 읽었을 경우에 실행
			if (i % n == 0) {
				int j = i + n - 1;
				// 오른쪽에서 부터, arr의 값이 0이면 que의 front값으로 대체, 
				// arr와 front가 같다면 arr값 2배, 두 경우 모두 아니라면 arr의 값을 front로 대체
				while (!que.empty()) {
					int t = que.front();
					que.pop();
					if (arr[j] == 0)arr[j] = t;
					else if (arr[j] == t) {
						arr[j--] = 2 * t;
						//현재 블럭의 2배 만큼 점수 증가
						score += 2 * t;
					}
					else {
						arr[--j] = t;
					}
				}
			}
		}
	}
	// k가 0일 때 블럭들을 왼쪽으로 이동
	else {
		// 왼쪽에서부터 값을 읽음
		for (int i = 0; i <= tmp - 1; i++) {
			// arr가 0이 아닐 경우에 que에 값 추가, 그리고 arr값을 0으로 바꿈
			if (arr[i]) {
				que.push(arr[i]);
				arr[i] = 0;
			}
			// 한 행을 다 읽었을 경우에 실행
			if (i % n == n - 1) {
				// 왼쪽에서 부터, arr의 값이 0이면 que의 front값으로 대체, 
				// arr와 front가 같다면 arr값 2배, 두 경우 모두 아니라면 arr의 값을 front로 대체
				int j = i - n + 1;
				while (!que.empty()) {
					int t = que.front();
					que.pop();
					if (arr[j] == 0)arr[j] = t;
					else if (arr[j] == t) {
						arr[j++] = 2 * t;
						//현재 블럭의 2배 만큼 점수 증가
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
	// 1차원 배열을 2차원의 n/n 행렬로 표현했을 때 대각선(0,0과 n-1,n-1을 잇는 선)을 기준으로 윗부분만 탐색하며,
	// 행과 열의 값을 바꿈
	for (int i = 0; i < tmp; i += (n + 1)) {
		for (int j = i + 1; j <= i + k; j++) {
			int x = j / n, y = j % n;
			swap(arr[x * n + y], arr[y * n + x]);
		}
		k--;
	}
}

