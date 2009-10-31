#include <dux/drivers/core/screen.h>
#include <dux/drivers/core/console.h>
#include <dux/drivers/core/kb.h>

#include <readline.h>

int paddle_y;
int ball_x, ball_y;
int ball_x_speed, ball_y_speed;

void draw_paddle(x, y)
{
	unsigned char attr = screen_getattr().attr;
	char i;
	for (i = 1; i < 4; i++)
		screen_writechar(x, y + i, attr, '|');
	
	screen_writechar(x, y - 1, attr, ' ');
	screen_writechar(x, y, attr, '+');
	screen_writechar(x, y + 4, attr, '+');
	screen_writechar(x, y + 5, attr, ' ');
}

void pong()
{
	while (1)
	{
		paddle_y = 5;
		
		ball_x = 10;
		ball_y = 10;
		
		ball_x_speed = 1;
		ball_y_speed = -1;
		
		console_clear();
		
		int scancode;
		unsigned char sym;
		char* input;
		
		while (1)
		{
			draw_paddle(1, paddle_y);
			draw_paddle(78, ball_y - 3);
			
			screen_writechar(ball_x, ball_y, screen_getattr().attr, ' ');
			
			ball_x += ball_x_speed;
			ball_y += ball_y_speed;
			
			if (ball_y < 0)
			{
				ball_y = -ball_y;
				ball_y_speed = 1;
			}
			else if (ball_y > 24)
			{
				ball_y = -(ball_y - 24) + 24;
				ball_y_speed = -1;
			}
			
			if (ball_x > 77)
			{
				ball_x = -(ball_x - 77) + 77;
				ball_x_speed = -1;
			}
			else if (ball_x < 2)
			{
				if (ball_y < paddle_y || ball_y > (paddle_y + 4))
				{
					break;
				}
				else
				{
					ball_x = -(ball_x - 2) + 2;
					ball_x_speed = 1;
				}
			}
			
			screen_writechar(ball_x, ball_y, screen_getattr().attr, 'O');
		
			if (kb_has_input())
			{
				scancode = kb_read();
				sym = kb_resolve_scancode(scancode);
				
				if (!(scancode & 0x80))
				{
					if (scancode == 72 && paddle_y > 1)
						paddle_y--;
					else if (scancode == 80 && paddle_y < 19)
						paddle_y++;
				
					if (kb_ctrl() && sym == 'c')
					{
						console_clear();
						printf("Caught interrupt.\n\n");
						return;
					}
				}
			}
				
			HalTimerSleep(100);
		}
	
		console_clear();
		input = readline("You lost.\n\nDo you want to try again? [Y/n] ");
		
		if (input[0] == 'y' || input[0] == 'Y')
			continue;
		else
			break;
	}
}
					
