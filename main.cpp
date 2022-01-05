#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Game_Object
{
	public:
		sf::Vector2f position;
		sf::Vector2f size;

};

class Paddle : public Game_Object
{
	public:
		int score = 0;
		Paddle(){};
		Paddle(float x_position, float y_position, float width, float height) : score(0)
		{
			position = sf::Vector2f(x_position, y_position);
			size = sf::Vector2f(width, height);
		}
};

class Ball : public Game_Object
{
	public:
		Ball(){}
		Ball(float x_position, float y_position, float width, float height)
		{
			position = sf::Vector2f(x_position, y_position);
			size = sf::Vector2f(width, height);
		}
};

class Game
{
	public:
		sf::RenderWindow window;
		sf::Event event{};

		Ball game_ball;
		Paddle player_1;
		Paddle player_2;

		Game(float window_width, float window_height, float paddle_width, float paddle_height) : window(sf::VideoMode(300, 300), "Pong")
		{
			player_1 = Paddle(window_width / 2, window_height - paddle_height, paddle_width, paddle_height);
			player_2 = Paddle(window_width / 2, 0, paddle_width, paddle_height);
			game_ball = Ball(window_width / 2, window_height / 2, 10, 10);
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
	
	Game pong(300, 300, 50, 10);

	
	while (pong.window.isOpen())
	{
		while (pong.window.pollEvent(pong.event))
		{
			switch (pong.event.type)
			{
				case sf::Event::Closed:
					pong.window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (pong.event.mouseButton.button == sf::Mouse::Left)
						std::cout << "Clicked" << std::endl;
					break;
			}
		}
		pong.render();
	}
	return 0;
}