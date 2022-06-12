#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
using namespace sf;

// �浹 ���� Ȯ��(�簢�浹)
bool isCollide(Sprite s1, Sprite s2);

#define GAME_OVER -1

//inline bool isCollide(Sprite s1, Sprite s2);

int main(void)
{

	// windowâ ����
	RenderWindow app(VideoMode(520, 450), "Arkanoid");
	app.setFramerateLimit(60);	//1�ʿ� 60�� �׸� ����

	//�ؽ��� load
	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/block01.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/ball.png");
	t4.loadFromFile("images/paddle.png");

	// Sprite�� image ��ġ
	Sprite sBackground(t2), sBall(t3), sPaddle(t4);
	sPaddle.setPosition(300, 400);
	sBall.setPosition(300, 300);



	// ���� ����
	Sprite block[200];

	int n = 0;
	for (int x = 1; x <= 10; x++) {
		for (int y = 0; y <= 10; y++) {
			block[n].setTexture(t1);
			block[n].setPosition(x * 43, y * 20);
			n++;
		}
		
	}

	// �� �ӵ�(����), x,y�� ������ ���� ���� ���ϱ� ���ؼ� ��¦ ����!
	// ���� ũ�Ⱑ Ŭ���� �ӵ��� ������!
	//   1 2 3 4 
	// 0  -----------x
	// | 1
	// | 2
	// | 3
	// y

	float dx = 5.0f, dy = 5.0;

	while (app.isOpen()) {
		Event e;	//�̺�Ʈ ����
		while (app.pollEvent(e)) {
			if (e.type == Event::Closed)
				app.close();
		}

		//�� �����̱�
		sBall.move(dx, 0);
		for (int i = 0; i < n; i++) {
			if (isCollide(sBall, block[i]))
			{
				dx = -dx;
				// ������ �þ߿��� ������� ��
				block[i].setPosition(-300, 0);
			}

		}

		sBall.move(0, dy);
		for (int i = 0; i < n; i++) {
			if (isCollide(sBall, block[i]))
			{
				dy = -dy;
				// ������ �þ߿��� ������� ��
				block[i].setPosition(0, -300);
			}

		}
		// ���� ��ġ(��ǥ)
		Vector2f b = sBall.getPosition();
		// ȭ�� �ٱ��� �׵θ��� �浿�ϴ� ���
		if (b.x < 0 || b.x>520) dx = -dx;
		if(b.y < 0 || b.y>450) dy = -dy;

		// Ű���忡 ���� paddle�� ������
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			sPaddle.move(10.0f, 0.0f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			sPaddle.move(-10.0f, 0.0f);
		}
		if (isCollide(sPaddle, sBall)) {
			dy = -dy;
		}



		app.clear();
		app.draw(sBackground);
		
		app.draw(sPaddle);

		for (int i = 0; i < n; i++)
			app.draw(block[i]);
		app.draw(sBall);
		app.display();
	}
	return 0;
}

bool isCollide(Sprite s1, Sprite s2)
{
	return s1.getGlobalBounds().intersects(s2.getGlobalBounds());
}