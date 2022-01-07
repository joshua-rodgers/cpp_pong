#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

class Game_Object
{
	public:
		sf::Vector2f position;
		sf::Vector2f size;
		float top;
		float bottom;
		float speed;
		std::string type;
};

class Paddle : public Game_Object
{
	public:
		int score = 0;
		bool is_moving_up = false;
		bool is_moving_down = false;
		float edge = 0;
		float paddle_segment[8];

		char side = ' ';
		
		Paddle() {};
		Paddle(float x_position, float y_position, float width, float height, float speed, char side) : score(0)
		{
			position = sf::Vector2f(x_position, y_position);
			size = sf::Vector2f(width, height);
			top = position.y;
			bottom = position.y + size.y;
			this->speed = speed;
			this->side = side;
			this->type = "paddle";

			if (side == 'l')
				edge = position.x + size.x;

			if (side == 'r')
				edge = position.x;


		}
		
};

class Ball : public Game_Object
{
	public:
		float x_speed = 0;
		float y_speed = 0;
		int direction = 1;
		float right_edge = 0;
		float left_edge = 0;

		Ball(){}
		Ball(float x_position, float y_position, float width, float height, int speed)
		{
			position = sf::Vector2f(x_position, y_position);
			size = sf::Vector2f(width, height);
			this->type = "ball";
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

		Game(float window_width, float window_height, float paddle_width, float paddle_height, int ball_speed, int paddle_speed) : window(sf::VideoMode(window_width, window_height), "Pong")
		{
			this->window_width = window_width;
			this->window_height = window_height;
			player_1 = Paddle(window_width - paddle_width, window_height / 2, paddle_width, paddle_height, paddle_speed, 'r');
			player_2 = Paddle(0, window_height / 2, paddle_width, paddle_height, paddle_speed, 'l');
			
			game_ball = Ball(window_width / 2, window_height / 2, 10, 10, ball_speed);
			game_ball.x_speed = ball_speed;

			std::srand(std::time(nullptr));
			int rand_value = std::rand();
			if (rand_value % 2 == 0)
				game_ball.direction = -game_ball.direction;
		}

		void update()
		{
			//move the game ball
			game_ball.position.x += (game_ball.x_speed * game_ball.direction);
			game_ball.position.y += (game_ball.y_speed * game_ball.direction);
			update_edges(game_ball);

			// move the paddle first regardless..
			if (player_1.is_moving_up)
			{
				player_1.position.y -= player_1.speed;
				update_edges(player_1);
			}
			else if (player_1.is_moving_down)
			{
				player_1.position.y += player_1.speed;
				update_edges(player_1);
			}
			
			// check if paddle passed top edge and place it back in bounds if so...
			if (player_1.top < 0)
			{
				update_edges(player_1, 0);
				player_1.position.y = 0;
			}
			// same for bottom edge
			if (player_1.bottom > this->window_height)
			{
				update_edges(player_1, window_height - player_1.size.y);
				player_1.position.y = player_1.top;	
			}
			
			// player_2's logic is identical, beyond the trivial note...
			if (player_2.is_moving_up)
			{
				player_2.position.y -= player_2.speed;
				update_edges(player_2);
			}
			else if (player_2.is_moving_down)
			{
				player_2.position.y += player_2.speed;
				update_edges(player_2);
			}
			
			if (player_2.top < 0)
			{
				player_2.position.y = 0;
				update_edges(player_2, 0);
			}

			if (player_2.bottom > this->window_height)
			{
				// this differs from player_1's logic simply to acknowledge that i 
				// found the cause of a semmingly weird bug XD
				player_2.position.y += (window_height - player_2.bottom);
				update_edges(player_2, player_2.position.y);
			}

		}

		void check_collisions()
		{
			if (game_ball.right_edge >= player_1.edge)
			{
				if (game_ball.bottom > player_1.top && game_ball.top < player_1.bottom)
				{
					get_trajectory(1);
					game_ball.direction = -game_ball.direction;
				}
				else
				{
					reset_game_objects();
				}
					
			}
			else if (game_ball.left_edge <= player_2.edge)
			{

				if (game_ball.bottom > player_2.top && game_ball.top < player_2.bottom)
				{
					game_ball.direction = -game_ball.direction;
				}
				else
				{
					reset_game_objects();
				}
					
			}
			

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

		private:
			void update_edges(Paddle &obj)
			{
				obj.top = obj.position.y;
				obj.bottom = obj.top + obj.size.y;
				switch (obj.side)
				{
					case 'l':
						obj.edge = obj.position.x + obj.size.x;
						break;
					case 'r':
						obj.edge = obj.position.x;
						break;
				}	
			}

			void update_edges(Paddle &obj, float new_y_position)
			{
				obj.top = new_y_position;
				obj.bottom = obj.top + obj.size.y;

				switch (obj.side)
				{
					case 'l':
						obj.edge = obj.position.x + obj.size.x;
						break;
					case 'r':
						obj.edge = obj.position.x;
						break;
				}
			}

			void update_edges(Ball &obj)
			{
				obj.top = obj.position.y;
				obj.bottom = obj.top + obj.size.y;
				obj.left_edge = obj.position.x;
				obj.right_edge = obj.position.x + obj.size.x;
			}

			void update_edges(Ball& obj, float new_y_position)
			{
				obj.top = new_y_position;
				obj.bottom = obj.top + obj.size.y;
				obj.left_edge = obj.position.x;
				obj.right_edge = obj.position.x + obj.size.x;
			}

			void update_edges(Ball& obj, float new_y_position, float new_x_position)
			{
				obj.top = new_y_position;
				obj.bottom = obj.top + obj.size.y;
				obj.left_edge = new_x_position;
				obj.right_edge = obj.left_edge + obj.size.x;
			}

			void reset_game_objects()
			{
				game_ball.position.x = window_width / 2;
				game_ball.position.y = window_height / 2;
				player_1.position = sf::Vector2f(window_width - player_1.size.x, window_height / 2);
				player_2.position = sf::Vector2f(0, window_height / 2);
				update_edges(player_1);
				update_edges(player_2);
				update_edges(game_ball);
			}

			void get_trajectory(int player)
			{

			}
};

int main()
{
	Game pong(800, 600, 10, 50, 10, 10);

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
		pong.check_collisions();
		pong.render();
		sf::sleep(sf::milliseconds(50));
	}
	return 0;
}