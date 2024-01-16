#include <Novice.h>

const char kWindowTitle[] = "LC1D_20_ナラ_ケイタ";

struct Vector2 {
	float x;
	float y;
};

//プレイヤー
struct Ball {
	Vector2 pos;
	Vector2 velocity;
	Vector2 acceleration;
	float radius;
	unsigned int color;
};

//ボックス
struct Box {
	Vector2 pos;
	Vector2 velocty;
	Vector2 acceleration;
	float rad;
	unsigned int color;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取るボックス
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//プレイヤーの矩形の幅と高さ
	float Pw = 100.0f;
	float Ph = 100.0f;

	//ブロックの矩形の幅と高さ
	float Bw = 200.0f;
	float Bh = 100.0f;

	//プレイヤーのスピード
	int Speed = 8;

	//スクリーン
	float s = 0;

	//プレイヤー
	Ball ball = {
	{600.0f,400.0f},
	{0.0f,0.0f},
	{0.0f,-0.8f},
	50.0f,
	WHITE
	};

	//ボックス
	Box box = {
	{800.0f,200.0f},
	{0.0f,0.0f},
	{0.0f,-0.8f},
	100.0f,
	WHITE
	};

	//プレイヤーの矩形
	Vector2 PlayerLeftTop = { ball.pos.x - Pw / 2.0f,ball.pos.y - Ph / 2.0f };
	Vector2 PlayerRightTop = { ball.pos.x + Pw / 2.0f,ball.pos.y - Ph / 2.0f };
	Vector2 PlayerLeftBottom = { ball.pos.x - Pw / 2.0f,ball.pos.y + Ph / 2.0f };
	Vector2 PlayerRightBottom = { ball.pos.x + Pw / 2.0f,ball.pos.y + Ph / 2.0f };

	//ボックスの矩形
	Vector2 BoxLeftTop = { box.pos.x - Bw / 2.0f,box.pos.y - Bh / 2.0f };
	Vector2 BoxRightTop = { box.pos.x + Bw / 2.0f,box.pos.y - Bh / 2.0f };
	Vector2 BoxLeftBottom = { box.pos.x - Bw / 2.0f,box.pos.y + Bh / 2.0f };
	Vector2 BoxRightBottom = { box.pos.x + Bw / 2.0f,box.pos.y + Bh / 2.0f };

	int WhiteGh = Novice::LoadTexture("./white1x1.png");

	//ジャンプカウント
	int isJump = false;

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
			ball.pos.x -= Speed;
		}
		
		if (keys[DIK_D]) {
			ball.pos.x += Speed;
		}
		

		/*----------------------
		   ボックスの当たり判定
		  ---------------------*/

		//プレイヤー
		PlayerLeftTop = { ball.pos.x - Pw / 2.0f,ball.pos.y - Ph / 2.0f };
		PlayerRightTop = { ball.pos.x + Pw / 2.0f,ball.pos.y - Ph / 2.0f };
		PlayerLeftBottom = { ball.pos.x - Pw / 2.0f,ball.pos.y + Ph / 2.0f };
		PlayerRightBottom = { ball.pos.x + Pw / 2.0f,ball.pos.y + Ph / 2.0f };

		//ボックス
		BoxLeftTop = { box.pos.x - Bw / 2.0f,box.pos.y - Bh / 2.0f };
		BoxRightTop = { box.pos.x + Bw / 2.0f,box.pos.y - Bh / 2.0f };
		BoxLeftBottom = { box.pos.x - Bw / 2.0f,box.pos.y + Bh / 2.0f };
		BoxRightBottom = { box.pos.x + Bw / 2.0f,box.pos.y + Bh / 2.0f };


        //================＼
		//    ジャンプ      >
	    //================／

		if (keys[DIK_W] != 0 && ball.pos.y == ball.radius  && isJump == 0) {
			isJump = true;
			ball.velocity.y = 30.0f;
		}

		ball.velocity.x += ball.acceleration.x;//速度 += 
		ball.velocity.y += ball.acceleration.y;

		ball.pos.x += ball.velocity.x;
		ball.pos.y += ball.velocity.y;

		if (ball.pos.y <= ball.radius) {
			ball.pos.y = ball.radius;
		}
		

		  /*ブロックの上に乗る*/
		//////////////////////////
		//                      //
		//    ^     ら     ^    //
		//                      //
		//////////////////////////

		if (BoxLeftTop.x < PlayerRightBottom.x && PlayerLeftBottom.x < BoxRightTop.x) {
			if (PlayerLeftTop.y < BoxRightBottom.y && PlayerLeftBottom.y < BoxRightTop.y) {
				
				ball.velocity.y = -30.0f;
				//ball.acceleration.y = -10.0f;//プレイヤーが地面に落ちるスピード	
				isJump = false;
			}
		}

		if (PlayerLeftBottom.y<=100){
			isJump = false;
		}

		/*
		if (PlayerLeftBottom.y >= s) {
			isJump = 1;
			
			ball.velocity.y = 0;
			ball.acceleration.y = -100.0f;//プレイヤーの飛躍力
		}*/
		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		//プレイヤーのスクリーン//
		float Screen = ball.pos.y;
		Screen += -500;
		Screen *= -1;

		// ==左上のスクリーン== //
		float ScreenLeftTop = PlayerLeftTop.y;
		ScreenLeftTop += -500;
		ScreenLeftTop *= -1;

		// ==右上のスクリーン== //
		float ScreenRightTop = PlayerRightTop.y;
		ScreenRightTop += -500;
		ScreenRightTop *= -1;

		// ==左下のスクリーン== //
		float ScreenLeftBottom = PlayerLeftBottom.y;
		ScreenLeftBottom += -500;
		ScreenLeftBottom *= -1;

		// ==右下のスクリーン== //
		float ScreenRightBottom = PlayerRightBottom.y;
		ScreenRightBottom += -500;
		ScreenRightBottom *= -1;

	/*-----------------------------------------------------------------*/

		//ボックスのスクリーン//
		float Bs = box.pos.y;
		Bs += -500;
		Bs *= -1;

		// ==左上スクリーン== //
		float BoxScreenLeftTop = BoxLeftTop.y;
		BoxScreenLeftTop += -500;
		BoxScreenLeftTop *= -1;

		// ==右上のスクリーン== //
		float BoxScreenRightTop = BoxRightTop.y;
		BoxScreenRightTop += -500;
		BoxScreenRightTop *= -1;

		// ==左下のスクリーン== //
		float BoxScreenLeftBottom = BoxLeftBottom.y;
		BoxScreenLeftBottom += -500;
		BoxScreenLeftBottom *= -1;

		// ==右下のスクリーン== //
		float BoxScreenRightBottom = BoxRightBottom.y;
		BoxScreenRightBottom += -500;
		BoxScreenRightBottom *= -1;

		//線のスクリーン//
		float ScreenY = s;
		ScreenY += -500;
		ScreenY *= -1;

	/*-------------------------------------------------------------------------------------------------*/

	    //プレイヤー
		Novice::DrawQuad((int)PlayerLeftTop.x, (int)ScreenLeftTop,//左上
							(int)PlayerRightTop.x, (int)ScreenRightTop,//右上
								(int)PlayerLeftBottom.x, (int)ScreenLeftBottom,//左下
									(int)PlayerRightBottom.x, (int)ScreenRightBottom,//右下
										0, 0, 1, 1, WhiteGh, (int)ball.color);//白色

	/*--------------------------------------------------------------------------------------------------*/
	
	    //ボックス
		Novice::DrawQuad((int)BoxLeftTop.x, (int)BoxScreenLeftTop,//左上
							(int)BoxRightTop.x, (int)BoxScreenRightTop,//右上
								(int)BoxLeftBottom.x, (int)BoxScreenLeftBottom,//左下
									(int)BoxRightBottom.x, (int)BoxScreenRightBottom,//右下
										0, 0, 1, 1, WhiteGh, (int)ball.color);//白色
		
		//ライン
		Novice::DrawLine(2000, (int)ScreenY, 0, 500, WHITE);

		Novice::ScreenPrintf(32, 32, "player.pos.x=%.1f", PlayerLeftBottom.y);

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
