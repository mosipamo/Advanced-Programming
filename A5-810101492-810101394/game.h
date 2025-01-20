#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include "read_map.h"
#include "collision.h"
#include "MiniTurtle.h"
#include "BonusEntity.h"
#include "MadEnemy.h"

using namespace sf;
using namespace std;

class Game
{
public:
    void menu();
    void draw_menu(RenderWindow &menu_window);
    void show_menu(RenderWindow &menu_window);
    void handle_menu_mouse_move(RenderWindow &menu_window);
    void handle_menu_mouse_press(RenderWindow &menu_window);
    void set_menu_bottons(RenderWindow &menu_window);

    void play();
    void set_game();
    void set_window();
    void handle_event(Event &event);
    void handle_mouse();
    void set_player();
    void get_state(Event &event);
    void set_view();
    void set_platforms();
    void resize_view(RenderWindow &window, View &view);
    void draw();
    void update();
    void check_collisions();
    void set_mini_turtles();
    void set_portal();
    void set_stars();
    void set_diamonds();
    void add_bonus_Entities(string image_file, IntRect int_rect, Vector2i poss, int point);
    void set_enemies();
    void set_mad_enemies();
    void set_is_game_over(bool _is_game_over);
    void set_obstacle();
    void set_bottons();
    void initialize_text(Text *text, int size);
    RectangleShape *init_botton(string image_file);
    void process();
    void show();

private:
    void draw_platforms();
    void draw_mini_turtles();
    void draw_enemies();
    void draw_mad_enemies();
    void draw_bonus_entities();
    void draw_end_game_text();
    void update_mini_turtles();
    void update_enemies();
    void update_mad_enemies();
    void update_bonus_entities();
    void update_turtix();
    void update_texts();

    void collide_between_turtix_and_platforms();
    void collide_between_enemies_and_platforms();
    void collide_between_mad_enemies_and_platforms();
    void collision_between_portal_and_mini_turtiles();
    void collision_between_turtix_and_bonus_entities();
    void collision_between_turtix_and_enemies();
    void collision_between_turtix_and_mad_enemies();
    void collision_between_turtix_and_mini_turtles();
    void collision_between_turtix_and_obstacle();
    void check_if_game_over();

private:
    RenderWindow *window;
    View *view;

    State state;
    float delta_time;
    bool paused = false;

    Turtix *turtix;

    GameEntity *portal = new GameEntity;
    GameEntity *obstacle = new GameEntity;

    vector<Platform *> platforms;
    vector<MiniTurtle *> mini_turtles;
    vector<BonusEntity *> bonus_entities;
    vector<EnemyEntity *> enemies;
    vector<MadEnemy *> mad_enemies;

    bool is_game_over = false;
    bool has_won = false;

    void init_fonts();
    void init_text();

    Font *font = new Font;

    Text *ui_text = new Text;
    Text *lost_text = new Text;
    Text *win_text = new Text;

    RectangleShape *paused_button = new RectangleShape;
    RectangleShape *exit_button = new RectangleShape;

    Text *start_text = new Text;
    Text *exit_text = new Text;
    RectangleShape *start_botton = new RectangleShape;
    RectangleShape *return_botton = new RectangleShape;
    Color *regular_color = new Color;
    Color *hover_color = new Color;
};