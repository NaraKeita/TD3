#include <Novice.h>

const char kWindowTitle[] = "LC1D_20_ナラ_ケイタ";

//自機
struct Vector2 {
	float x;
	float y;
};

struct Ball {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float radius;
	unsigned int color;
};

struct Box {
	Vector2 position;
	Vector2 velocty;
	Vector2 acceleration;
	float rad;
	unsigned int color;
};



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//矩形の幅と高さ
	float w = 100.0f;
	float h = 100.0f;

	int speed = 8;

	float s = 0;

	Ball ball = {
	{600.0f,400.0f},
	{0.0f,0.0f},
	{0.0f,-0.8f},
	50.0f,
	WHITE
	};

	Box box = {
	{700.0f,100.0f},
	{0.0f,0.0f},
	{0.0f,-0.8f},
	100.0f,
	WHITE
	};

	Vector2 lefttop = { ball.position.x - w / 2.0f,ball.position.y - h / 2.0f };
	Vector2 righttop = { ball.position.x + w / 2.0f,ball.position.y - h / 2.0f };
	Vector2 leftbottom = { ball.position.x - w / 2.0f,ball.position.y + h / 2.0f };
	Vector2 rightbottom = { ball.position.x + w / 2.0f,ball.position.y + h / 2.0f };

	Vector2 boxlefttop = { box.position.x - w / 2.0f,box.position.y - h / 2.0f };
	Vector2 boxrighttop = { box.position.x + w / 2.0f,box.position.y - h / 2.0f };
	Vector2 boxleftbottom = { box.position.x - w / 2.0f,box.position.y + h / 2.0f };
	Vector2 boxrightbottom = { box.position.x + w / 2.0f,box.position.y + h / 2.0f };

	int WhiteGh = Novice::LoadTexture("./white1x1.png");

	//ジャンプカウント
	int JumpCount = 1;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_A]) {
			ball.position.x -= speed;
		}
		
		if (keys[DIK_D]) {
			ball.position.x += speed;
		}
		

		/*---------------
		   箱の当たり判定
		  ---------------*/

		lefttop = { ball.position.x - w / 2.0f,ball.position.y - h / 2.0f };
		righttop = { ball.position.x + w / 2.0f,ball.position.y - h / 2.0f };
		leftbottom = { ball.position.x - w / 2.0f,ball.position.y + h / 2.0f };
		rightbottom = { ball.position.x + w / 2.0f,ball.position.y + h / 2.0f };



		boxlefttop = { box.position.x - w / 2.0f,box.position.y - h / 2.0f };
		boxrighttop = { box.position.x + w / 2.0f,box.position.y - h / 2.0f };
		boxleftbottom = { box.position.x - w / 2.0f,box.position.y + h / 2.0f };
		boxrightbottom = { box.position.x + w / 2.0f,box.position.y + h / 2.0f };


        //================＼
		//    ジャンプ     ｜
	    //================／

		if (keys[DIK_W] != 0 && ball.position.y == ball.radius  && JumpCount == 0) {
			JumpCount = -1;
			ball.velocity.y = 18.0f;
		}

		ball.velocity.x += ball.acceleration.x;//速度 += 
		ball.velocity.y += ball.acceleration.y;

		ball.position.x += ball.velocity.x;
		ball.position.y += ball.velocity.y;

		if (ball.position.y <= ball.radius) {
			ball.position.y = ball.radius;
		}

		/*---------------------
		   箱の上にいくとのれる
		  ---------------------*/
		/*if (boxlefttop.y <= lefttop.y) {
			ball.velocity.y -= ball.acceleration.y;
			ball.position.y -= ball.velocity.y;
			
			if (ball.position.y <= ball.radius) {
				ball.position.y = ball.radius;
			}
		}*/
		

		//当たり判定
		/*if (boxlefttop.x > rightbottom.x && lefttop.x > boxrightbottom.x) {
			if (boxlefttop.y > rightbottom.y && lefttop.y > boxrightbottom.y) {
				JumpCount = true;
				ball.velocity.y = 0;
				ball.acceleration.y = -0.8f;
		}*/

		if (boxlefttop.x < rightbottom.x && lefttop.x < boxrightbottom.x) {
			 if (boxlefttop.y < rightbottom.y && lefttop.y < boxrightbottom.y) {
				JumpCount = +1;
				ball.velocity.y = 0;
				ball.acceleration.y = 0.0f;
			 }
		}else{
			ball.velocity.y = 0;
			ball.acceleration.y = -0.8f;
		}
		
		if (lefttop.y <= s) {
			JumpCount = 1;
			ball.velocity.y = 0;
			ball.acceleration.y = -0.8f;
		}
		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		//自機のスクリーン//
		float screen = ball.position.y;
		screen += -500;
		screen *= -1;

		// ==左上のスクリーン== //
		float screenlefttop = lefttop.y;
		screenlefttop += -500;
		screenlefttop *= -1;

		// ==右上のスクリーン== //
		float screenrighttop = righttop.y;
		screenrighttop += -500;
		screenrighttop *= -1;

		// ==左下のスクリーン== //
		float screenleftbottom = leftbottom.y;
		screenleftbottom += -500;
		screenleftbottom *= -1;

		// ==右下のスクリーン== //
		float screenrightbottom = rightbottom.y;
		screenrightbottom += -500;
		screenrightbottom *= -1;



		//箱のスクリーン//
		float boxscreenlefttop = boxlefttop.y;
		boxscreenlefttop += -500;
		boxscreenlefttop *= -1;

		float boxscreenrighttop = boxrighttop.y;
		boxscreenrighttop += -500;
		boxscreenrighttop *= -1;

		float boxscreenleftbottom = boxleftbottom.y;
		boxscreenleftbottom += -500;
		boxscreenleftbottom *= -1;

		float boxscreenrightbottom = boxrightbottom.y;
		boxscreenrightbottom += -500;
		boxscreenrightbottom *= -1;


		float Bs = box.position.y;
		Bs += -500;
		Bs *= -1;


		//線のスクリーン//
		float screenY = s;
		screenY += -500;
		screenY *= -1;

		//自機
		Novice::DrawQuad((int)lefttop.x, (int)screenlefttop,
			(int)righttop.x, (int)screenrighttop,
			(int)leftbottom.x, (int)screenleftbottom,
			(int)rightbottom.x, (int)screenrightbottom,
			0, 0, 1, 1, WhiteGh, (int)ball.color);

		//箱
		Novice::DrawQuad((int)boxlefttop.x, (int)boxscreenlefttop,
			(int)boxrighttop.x, (int)boxscreenrighttop,
			(int)boxleftbottom.x, (int)boxscreenleftbottom,
			(int)boxrightbottom.x, (int)boxscreenrightbottom,
			0, 0, 1, 1, WhiteGh, (int)ball.color);
		
		//ライン
		Novice::DrawLine(2000, (int)screenY, 0, 500, WHITE);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
