#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Game_Object
{
	public:
		sf::Vector2f position;
		sf::Vector2f size;
		float top;
		float bottom;
		float speed;

};

class Paddle : public Game_Object
{
	public:
		int score = 0;
		bool is_moving_up = false;
		bool is_moving_down = false;
		
		Paddle() {};
		Paddle(float x_position, float y_position, float width, float height, float speed) : score(0)
		{
			position = sf::Vector2f(x_position, y_position);
			size = sf::Vector2f(width, height);
			top = position.y;
			bottom = position.y + size.y;
			this->speed = speed;
		}
		
};

class Ball : public Game_Object
{
	public:
		Ball(){}
		Ball(float x_position, float y_position, float width, float height, int speed)
		{
			position = sf::Vector2f(x_position, y_position);
			size = sf::Vector2f(width, height);
		}
};

class Game
{
	public:
		sf::RenderWindow window;
		float window_width = 0;
		float window_height = 0;
		sf::Event event{};

		Ball game_ball;
		Paddle player_1;
		Paddle player_2;

		Game(float window_width, float window_height, float paddle_width, float paddle_height, int ball_speed, int paddle_speed) : window(sf::VideoMode(300, 300), "Pong")
		{
			this->window_width = window_width;
			this->window_height = window_height;
			player_1 = Paddle(window_width - paddle_width, window_height / 2, paddle_width, paddle_height, paddle_speed);
			player_2 = Paddle(0, window_height / 2, paddle_width, paddle_height, paddle_speed);
			game_ball = Ball(window_width / 2, window_height / 2, 10, 10, ball_speed);
		}

		void update()
		{
			if (player_1.position.y >= 0 && player_1.position.y + player_1.size.y <= window_height)
			{
				if (player_1.is_moving_up)
				{
					player_1.position.y -= player_1.speed;
					player_1.top = player_1.position.y;
					player_1.bottom = player_1.top + player_1.size.y;
				}
				else if (player_1.is_moving_down)
				{
					player_1.position.y += player_1.speed;
					player_1.top = player_1.position.y;
					player_1.bottom = player_1.top + player_1.size.y;
				}
			}
			
			
			if (player_1.top < 0)
			{
				player_1.position.y = 0;
				player_1.top = 0;
			}

			if (player_1.bottom > this->window_height)
			{
				player_1.position.y += (window_height - player_1.bottom);
				player_1.top = player_1.position.y;
				player_1.bottom = player_1.top + player_1.size.y;
			}
				
			
			if (player_2.position.y >= 0 && player_2.position.y + player_2.size.y <= window_height)
			{
				if (player_2.is_moving_up)
				{
					player_2.position.y -= player_2.speed;
					player_2.top = player_2.position.y;
					player_2.bottom = player_2.top + player_2.size.y;
				}
				else if (player_2.is_moving_down)
				{
					player_2.position.y += player_2.speed;
					player_2.top = player_2.position.y;
					player_2.bottom = player_2.top + player_2.size.y;
				}
			}

			if (player_2.top < 0)
			{
				player_2.position.y = 0;
				player_2.top = 0;
			}

			if (player_2.bottom > this->window_height)
			{
				player_2.position.y += (window_height - player_2.bottom);
				player_2.top = player_2.position.y;
				player_2.bottom = player_2.top + player_2.size.y;
			}

		}

		void check_collisions()
		{

		}

		void render()
		{
			sf::RectangleShape render_player_1(player_1.size);
			render_player_1.setPosition(player_1.position);
			render_player_1.setFillColor(sf::Color::White);

			sf::RectangleShape render_player_2(player_2.size);
			render_player_2.setPosition(player_2.position);
			render_player_2.setFillColor(sf::Color::White);

			sf::RectangleShape render_ball(game_ball.size);
			render_ball.setPosition(game_ball.position);
			render_ball.setFillColor(sf::Color::White);

			window.clear(sf::Color::Black);

			window.draw(render_ball);
			window.draw(render_player_1);
			window.draw(render_player_2);

			window.display();
		}
};

int main()
{
	
	Game pong(300, 300, 10, 50, 10, 10);

	
	while (pong.window.isOpen())
	{
		while (pong.window.pollEvent(pong.event))
		{
			switch (pong.event.type)
			{
				case sf::Event::KeyPressed:
					switch (pong.event.key.code)
					{
						case sf::Keyboard::Up:
							pong.player_1.is_moving_up = true;
							break;
						case sf::Keyboard::Down:
							pong.player_1.is_moving_down = true;
							break;
						case sf::Keyboard::W:
							pong.player_2.is_moving_up = true;
							break;
						case sf::Keyboard::S:
							pong.player_2.is_moving_down = true;
							break;
					}
				break;

				case sf::Event::KeyReleased:
					switch (pong.event.key.code)
					{
						case sf::Keyboard::Up:
							pong.player_1.is_moving_up = false;
							break;
						case sf::Keyboard::Down:
							pong.player_1.is_moving_down = false;
							break;
						case sf::Keyboard::W:
							pong.player_2.is_moving_up = false;
							break;
						case sf::Keyboard::S:
							pong.player_2.is_moving_down = false;
							break;
					}
					break;

				case sf::Event::Closed:
					pong.window.close();
					break;
			}
		}
		pong.update();
		pong.render();
		sf::sleep(sf::milliseconds(50));
	}
	return 0;
}