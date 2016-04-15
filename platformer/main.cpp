#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

using namespace sf;

int ground = 400;
float offsetX=0,offsetY=0;
const int H = 12;
const int W = 73;
const int Tile_s = 32;
String TileMap[] = 
{
"1111111111111111111111111111111111111111111111111111111111111111111111111",
"1000000000000000000000000000000000000000000000000000000000000000002000001",
"1000000000000000000000000000000000000000000200000000000000000000020200001",
"1000000000000000000000000000000000200000000110000020000000000000202020001",
"1000000000000000000000220000000000000000000000200111000000000002020202001",
"1000002222000000000000000000000111100000020000000000000000011111111111111",
"1000000000000000000000000000000000100000111000200000000000000000000000001",
"1000000000000000000011100000002000100000000001110000000000000000000002201",
"1110000000000000000000000000020200100000000000000000000000000000000001111",
"1000000000001100000000000000202020000000000000000000002020202000000000001",
"1000000000001100000000000000000000000000000000000000000202020200000000001",
"1111111111111111111111111111111111111111111111111111111111111111111111111"
};



class Player
{
public:
	float dx,dy;// speed
	FloatRect rect;
	bool OnGround;
	Sprite sprite;

	Player(Texture &Image)
	{
		sprite.setTexture(Image);
		rect = FloatRect(300,300,32,32);
		dx = dy = 0.1;
	}
	
	void CollisionX()
	{
		for (int i=rect.top/32;i<(rect.top+rect.height)/32;i++)
			for (int j=rect.left/32;j<(rect.left+rect.width)/32;j++)
			{
				if (TileMap[i][j] == '1')
				{
					if (dx>0)
						rect.left = j*32 - rect.width;
					if (dx<0)
						rect.left = j*32 + 32;
				}
				if (TileMap[i][j] == '2')
					TileMap[i][j] = '0';
			}
	}


	void CollisionY()
	{
		for (int i=rect.top/32;i<(rect.top+rect.height)/32;i++)
			for (int j=rect.left/32;j<(rect.left+rect.width)/32;j++)
			{
				if (TileMap[i][j] == '1')
				{
					if (dy>0)
					{
						rect.top = i*32 - rect.height;
						dy = 0;
						OnGround = true;
					}
					if (dy<0)
					{
						rect.top = i*32 + 32;
						dy = 0;
					}
				}

				if (TileMap[i][j] == '2')
					TileMap[i][j] = '0';
			}
	}

	void update ()
	{
		rect.left +=dx;
		CollisionX();
		if (!OnGround)
			dy +=0.001;

		rect.top += dy;
		OnGround = false;
		CollisionY();
	
		sprite.setPosition(rect.left-offsetX,rect.top-offsetY);
			dx=0;
	}
};



int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 450), "Platform Game");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	sf::Color c;
	
	sf::RectangleShape rectangle(Vector2f(32, 32));

	Texture t;
	t.loadFromFile("Content\\boeBadGuy.png");
	
	Player p(t);

	while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if (Keyboard::isKeyPressed(Keyboard::Left))// || Keyboard::isKeyPressed(Keyboard::A))
		{
			p.dx = -0.381;//0.1
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))// || Keyboard::isKeyPressed(Keyboard::D))
		{
				p.dx = 0.381; //0.1
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.OnGround)
			{
				p.dy = -0.58;//0.4
				p.OnGround = false;
			}
		
		}
		p.update();

		if (p.rect.left>300 && p.rect.left<(W*Tile_s-300))
			offsetX = p.rect.left - 600/2;
		if (p.rect.top>200 && p.rect.top<250)
		offsetY = p.rect.top-400/2;

		window.clear(c.Cyan);

		for (int i=0;i<H; i++)
			for (int j=0;j<W;j++)
			{
				if (TileMap[i][j] == '1')
				{
					rectangle.setFillColor(c.Black);
				};
				if (TileMap[i][j] == '2')
					rectangle.setFillColor(c.Yellow);
				if (TileMap[i][j] == '0') 
					continue;

				rectangle.setPosition((j)*32-offsetX,(i)*32-offsetY);
				window.draw(rectangle);
			};

		window.draw(p.sprite);
        window.display();
    }

    return 0;
}