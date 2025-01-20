#include "game.h"
#include <string>
#include <iostream>
#include <sstream>

const int WINDOW_WIDTH = 2000;
const int WINDOW_HEIGHT = 1500;
const int VIEW_HIEGHT = 1000;
const string GAME_TITLE = "turtix";
const string MAP_FILE = "map.txt";
const string TURTIX_ANIME_FILE = "./sprite/1C5230-removebg-preview.png";
const string MINI_TURTLE_ANIME_FILE = "./sprite/11F3EA5_prev_ui.png";
const string STAR_ANIME_FILE = "./sprite/3A6D1D_prev_ui.png";
const string DIAMOND_ANIME_FILE = "./sprite/DA305C_prev_ui.png";
const string ENEMY_ANIME_FILE = "./sprite/2AA02D-removebg-preview.png";
const string EXIT_BOTTON_IMG = "exit_botton.png";
const string PAUSED_BOTTON_IMG = "paused_botton.png";
const string MINI_TURTLE_TEXTURE_FILE = "./sprite/F4BE8_prev_ui.png";
const string PORTAL_TEXTURE_FILE = "./sprite/Gate_B_3.png";
const string OBSTACLE_TEXTURE_FILE = "./sprite/22981E_NB.png";
const string FONT_FILE = "Dosis-Light.ttf";
const int STAR_POINT = 10;
const int DIAMOND_POINT = 22;
const Color GRAY = {150,150,150};

const Vector2f BOTTON_SIZE = {50.f, 50.f};

void Game::resize_view(RenderWindow &window, View &view)
{
    float aspect_retio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HIEGHT * aspect_retio, VIEW_HIEGHT);
}

void Game::menu()
{
    RenderWindow menu_window(VideoMode(800, 600), "My Game");
    set_menu_bottons(menu_window);

    while (menu_window.isOpen())
    {
        Event event;
        while (menu_window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                menu_window.close();
            else if (event.type == Event::MouseButtonPressed)
                handle_menu_mouse_press(menu_window);
            else if (event.type == Event::MouseMoved)
                handle_menu_mouse_move(menu_window);
        }
        show_menu(menu_window);
    }
}

void Game::set_menu_bottons(RenderWindow &menu_window)
{
    Font *font = new Font;
    font->loadFromFile(FONT_FILE);

    Text *start_txt = new Text("Start", *font, 50);
    this->start_text = start_txt;
    start_text->setPosition(menu_window.getSize().x / 2 - start_text->getGlobalBounds().width / 2, 200);

    Text *exit_txt = new Text("Exit", *font, 50);
    this->exit_text = exit_txt;
    exit_text->setPosition(menu_window.getSize().x / 2 - exit_text->getGlobalBounds().width / 2, 300);

    RectangleShape *start_button = new RectangleShape(Vector2f(start_text->getGlobalBounds().width + 20,
                                                               start_text->getGlobalBounds().height + 20));
    this->start_botton = start_button;
    start_botton->setPosition(start_text->getPosition().x - 10, start_text->getPosition().y + 10);

    RectangleShape *exit_button = new RectangleShape(Vector2f(exit_text->getGlobalBounds().width + 20,
                                                              exit_text->getGlobalBounds().height + 20));
    this->return_botton = exit_button;
    return_botton->setPosition(exit_text->getPosition().x - 10, exit_text->getPosition().y + 10);

    *regular_color = Color::Magenta;
    *hover_color = Color::Blue;

    start_botton->setFillColor(*regular_color);
    return_botton->setFillColor(*regular_color);
}

void Game::show_menu(RenderWindow &menu_window)
{
    menu_window.clear(GRAY);

    draw_menu(menu_window);

    menu_window.display();
}

void Game::draw_menu(RenderWindow &menu_window)
{
    menu_window.draw(*start_botton);
    menu_window.draw(*start_text);
    menu_window.draw(*return_botton);
    menu_window.draw(*exit_text);
}

void Game::handle_menu_mouse_move(RenderWindow &menu_window)
{
    Vector2i mousePos = Mouse::getPosition(menu_window);

    if (start_botton->getGlobalBounds().contains(mousePos.x, mousePos.y))
        start_botton->setFillColor(*hover_color);
    else
        start_botton->setFillColor(*regular_color);

    if (return_botton->getGlobalBounds().contains(mousePos.x, mousePos.y))
        return_botton->setFillColor(*hover_color);
    else
        return_botton->setFillColor(*regular_color);
}

void Game::handle_menu_mouse_press(RenderWindow &menu_window)
{
    Vector2i mousePos = Mouse::getPosition(menu_window);

    if (start_botton->getGlobalBounds().contains(mousePos.x, mousePos.y))
    {
        cout << "Starting game..." << endl;
        Game game;
        game.play();
    }

    if (return_botton->getGlobalBounds().contains(mousePos.x, mousePos.y))
        menu_window.close();
}

void Game::play()
{
    set_game();

    Clock clock;
    while (window->isOpen())
    {
        delta_time = clock.restart().asSeconds();

        Event event;

        while (window->pollEvent(event))
            handle_event(event);

        if (is_game_over)
        {
            if (event.type == Event::MouseButtonPressed)
                window->close();
        }
        else if (!paused)
            process();

        show();
    }
}

void Game::process()
{
    check_collisions();
    update();
}

void Game::show()
{
    window->clear(GRAY);

    draw();

    window->display();
}

void Game::set_game()
{
    set_window();
    set_view();
    set_player();
    set_platforms();
    set_mini_turtles();
    set_enemies();
    set_mad_enemies();
    set_stars();
    set_diamonds();
    set_portal();
    set_obstacle();
    set_bottons();
}

void Game::add_bonus_Entities(string image_file, IntRect int_rect, Vector2i pos, int point)
{
    BonusEntity *bonus = new BonusEntity(point);
    bonus->set_animation(image_file, int_rect, {4, 4, 0, 15}, 0.1f);
    Texture *anime_texture = new Texture;
    anime_texture->loadFromFile(image_file, int_rect);
    bonus->get_body()->setTexture(*anime_texture);

    bonus->set_pos(pos.x, pos.y);
    bonus_entities.push_back(bonus);
}

void Game::set_stars()
{
    vector<Vector2i> pos_star = {{500, 500}, {650, 500}};
    IntRect star_rect = {0, 0, 500, 500};
    for (int i = 0; i < pos_star.size(); i++)
        add_bonus_Entities(STAR_ANIME_FILE, star_rect, pos_star[i], STAR_POINT);
}

void Game::set_diamonds()
{
    vector<Vector2i> pos_diamond = {{800, 550}, {950, 550}};
    IntRect diamond_rect = {0, 0, 400, 400};
    for (int i = 0; i < pos_diamond.size(); i++)
        add_bonus_Entities(DIAMOND_ANIME_FILE, diamond_rect, pos_diamond[i], DIAMOND_POINT);
}

void Game::set_window()
{
    window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), GAME_TITLE, Style::Close | Style::Resize);
}

void Game::handle_event(Event &event)
{
    if (event.type == Event::Closed)
        window->close();
    else if (event.type == Event::KeyPressed)
        get_state(event);
    else if (event.type == Event::Resized)
        resize_view(*window, *view);
    else if (event.type == Event::KeyReleased)
        state = IDLE;
    else if (event.type == Event::MouseButtonReleased)
        handle_mouse();
}

void Game::handle_mouse()
{
    Vector2i mousePos = Mouse::getPosition(*window);
    Vector2f worldPos = window->mapPixelToCoords(mousePos);

    if (paused_button->getGlobalBounds().contains(worldPos))
        paused = !paused;
    if (paused && exit_button->getGlobalBounds().contains(worldPos))
        window->close();
}

void Game::get_state(Event &event)
{
    switch (event.key.code)
    {
    case Keyboard::A:
        state = LEFT;
        break;

    case Keyboard::D:
        state = RIGHT;
        break;

    case Keyboard::Space:
        state = JUMP;
        break;
    }
}

void Game::set_view()
{
    view = new View(Vector2f(0.0f, 0.0f), Vector2f(VIEW_HIEGHT, VIEW_HIEGHT));
}

void Game::set_player()
{
    turtix = new Turtix;

    turtix->set_animation(TURTIX_ANIME_FILE, IntRect(0, 0, 480, 380), {5, 4, 0, 15}, 0.10f);
    turtix->set_pos(780.0f, 1000.0f);
    turtix->set_state(IDLE);
}

void Game::set_platforms()
{
    ReadMap read_map(MAP_FILE);
    platforms = read_map.get_platforms();
}

void Game::draw()
{
    if (!paused)
    {
        draw_platforms();
        draw_mini_turtles();
        draw_bonus_entities();
        draw_enemies();
        draw_mad_enemies();

        if (is_game_over)
            draw_end_game_text();

        portal->draw(window);
        obstacle->draw(window);
        window->draw(*ui_text);
        turtix->draw(window);
    }

    else
        window->draw(*exit_button);

    window->draw(*paused_button);
}

void Game::update()
{
    update_turtix();
    update_mini_turtles();
    update_bonus_entities();
    update_enemies();
    update_mad_enemies();
    update_texts();
}

void Game::set_mini_turtles()
{
    vector<Vector2i> poss = {{500, -50}, {1000, 300}};
    for (int i = 0; i < poss.size(); i++)
    {
        MiniTurtle *mini_turtle = new MiniTurtle;
        mini_turtle->set_animation(MINI_TURTLE_ANIME_FILE, IntRect(0, 0, 600, 300), {6, 3, 0, 14}, 0.2f);
        Texture *anime_texture = new Texture;
        anime_texture->loadFromFile(MINI_TURTLE_ANIME_FILE, IntRect(0, 0, 600, 300));
        mini_turtle->set_anime_texture(anime_texture);
        Texture *texture = new Texture;
        texture->loadFromFile(MINI_TURTLE_TEXTURE_FILE, IntRect(0, 0, 160, 160));
        mini_turtle->set_spawn_texture(texture);
        mini_turtle->set_pos(poss[i].x, poss[i].y);
        mini_turtles.push_back(mini_turtle);
    }
}

void Game::set_enemies()
{
    vector<Vector2i> poss = {{100, 200}};
    for (int i = 0; i < poss.size(); i++)
    {
        EnemyEntity *enemy = new EnemyEntity;
        enemy->set_animation(ENEMY_ANIME_FILE, IntRect(0, 0, 800, 420), {6, 5, 0, 29}, 0.2f);
        Texture *anime_texture = new Texture;
        anime_texture->loadFromFile(ENEMY_ANIME_FILE, IntRect(0, 0, 800, 420));
        enemy->get_body()->setTexture(*anime_texture);
        enemy->get_body()->setScale(1.25, 1.25);
        enemy->set_jump_status(false);
        enemy->set_pos(poss[i].x, poss[i].y);
        enemies.push_back(enemy);
    }
}

void Game::set_mad_enemies()
{
    vector<Vector2i> poss = {{800, 400}};
    for (int i = 0; i < poss.size(); i++)
    {
        MadEnemy *mad_enemy = new MadEnemy;
        mad_enemy->set_animation(ENEMY_ANIME_FILE, IntRect(0, 0, 800, 420), {6, 5, 0, 29}, 0.2f);
        Texture *anime_texture = new Texture;
        anime_texture->loadFromFile(ENEMY_ANIME_FILE, IntRect(0, 0, 800, 420));
        mad_enemy->get_body()->setTexture(*anime_texture);
        mad_enemy->get_body()->setScale(1.25, 1.25);
        mad_enemy->set_jump_status(false);
        mad_enemy->set_pos(poss[i].x, poss[i].y);
        mad_enemies.push_back(mad_enemy);
    }
}

void Game::set_is_game_over(bool _game_over)
{
    is_game_over = _game_over;
}

void Game::set_portal()
{
    portal->set_texture(PORTAL_TEXTURE_FILE, IntRect(110, 35, 200, 100));
    portal->set_pos(670, 1125);
    portal->set_body();
}

void Game::set_obstacle()
{
    obstacle->set_texture(OBSTACLE_TEXTURE_FILE, IntRect(50, 615, 200, 150));
    obstacle->set_pos(-700, 570);
    obstacle->set_body();
}

void Game::check_collisions()
{
    collide_between_turtix_and_platforms();
    collision_between_turtix_and_mini_turtles();
    collide_between_enemies_and_platforms();
    collide_between_mad_enemies_and_platforms();
    collision_between_portal_and_mini_turtiles();
    collision_between_turtix_and_bonus_entities();
    collision_between_turtix_and_enemies();
    collision_between_turtix_and_mad_enemies();
    collision_between_turtix_and_obstacle();
    check_if_game_over();
}

void Game::init_fonts()
{
    font->loadFromFile(FONT_FILE);
}

void Game::initialize_text(Text *text, int size)
{
    text->setFont(*font);
    text->setCharacterSize(size);
    text->setFillColor(Color::Black);
    text->setStyle(Text::Bold);
    text->setPosition(view->getCenter().x - view->getSize().x / 2 + 50, view->getCenter().y - view->getSize().y / 2 + 50);
}

void Game::init_text()
{
    stringstream ss;
    initialize_text(ui_text, 38);
    ss << "Points: " << turtix->get_point() << "\n"
       << "Health: " << turtix->get_HP() << "\n";
    ui_text->setString(ss.str());
    initialize_text(lost_text, 500);
    lost_text->setString("Gagool");
    initialize_text(win_text, 500);
    win_text->setString("You Won!");
}

void Game::draw_platforms()
{
    for (Platform *platform : platforms)
        platform->draw(window);
}

void Game::draw_mini_turtles()
{
    for (MiniTurtle *mini_turtle : mini_turtles)
        mini_turtle->draw(window);
}

void Game::draw_enemies()
{
    for (EnemyEntity *enemy : enemies)
        enemy->draw(window);
}

void Game::draw_mad_enemies()
{
    for (MadEnemy *mad_enemy : mad_enemies)
        mad_enemy->draw(window);
}

void Game::draw_bonus_entities()
{
    for (BonusEntity *bonus_entity : bonus_entities)
        bonus_entity->draw(window);
}

void Game::draw_end_game_text()
{
    if (has_won)
        window->draw(*win_text);
    else
        window->draw(*lost_text);
}

void Game::update_mini_turtles()
{
    for (MiniTurtle *mini_turtle : mini_turtles)
        mini_turtle->update(delta_time);
}

void Game::update_enemies()
{
    for (EnemyEntity *enemy : enemies)
        enemy->update(delta_time);
}

void Game::update_mad_enemies()
{
    for (MadEnemy *mad_enemy : mad_enemies)
        mad_enemy->update(delta_time);
}

void Game::update_bonus_entities()
{
    for (BonusEntity *bonus_entity : bonus_entities)
        bonus_entity->update(delta_time);
}

void Game::update_turtix()
{
    turtix->set_state(state);

    turtix->update(delta_time, state);

    view->setCenter(turtix->get_position());
}

void Game::update_texts()
{
    init_fonts();
    init_text();

    paused_button->setPosition(view->getCenter().x - view->getSize().x / 2 + 1800, view->getCenter().y - view->getSize().y / 2 + 50);
    exit_button->setPosition(view->getCenter().x - view->getSize().x / 2 + 1800, view->getCenter().y - view->getSize().y / 2 + 150);
    window->setView(*view);
}

void Game::set_bottons()
{
    paused_button = init_botton(PAUSED_BOTTON_IMG);
    exit_button = init_botton(EXIT_BOTTON_IMG);
}

RectangleShape *Game::init_botton(string image_file)
{

    Texture *botton_texture = new Texture;
    botton_texture->loadFromFile(image_file);

    RectangleShape *botton = new RectangleShape;
    botton->setTexture(botton_texture);
    botton->setSize(BOTTON_SIZE);
    botton->setFillColor(SEMI_TRANSPARENT);

    return botton;
}

void Game::collide_between_turtix_and_platforms()
{
    Collision collision;
    Intersection from;
    bool is_on_ground = false;
    for (Platform *platform : platforms)
        if (collision.check_collision(turtix->get_body(), platform->get_body(), from))
        {
            turtix->handle_collision(from);
            if (from == FROM_UP)
                is_on_ground = true;
        }
    if (!is_on_ground)
        turtix->set_jump_status(false);
    else
        turtix->set_jump_status(true);
}

void Game::collide_between_enemies_and_platforms()
{
    for (EnemyEntity *enemy : enemies)
        enemy->tick(platforms);
}

void Game::collide_between_mad_enemies_and_platforms()
{
    for (MadEnemy *mad_enemy : mad_enemies)
        mad_enemy->tick(platforms);
}

void Game::collision_between_portal_and_mini_turtiles()
{
    for (int i = 0; i < mini_turtles.size(); i++)
        if (portal->get_body()->getGlobalBounds().intersects(mini_turtles.at(i)->get_body()->getGlobalBounds()))
            mini_turtles.erase(mini_turtles.begin() + i);
}

void Game::collision_between_turtix_and_bonus_entities()
{
    for (int i = 0; i < bonus_entities.size(); i++)
    {
        if (turtix->get_body()->getGlobalBounds().intersects(bonus_entities.at(i)->get_body()->getGlobalBounds()))
        {
            turtix->add_point(bonus_entities[i]->get_point());
            bonus_entities.erase(bonus_entities.begin() + i);
        }
    }
}

void Game::collision_between_turtix_and_enemies()
{
    Collision collision;
    Intersection from;
    for (int i = 0; i < enemies.size(); i++)
        if (!turtix->get_gosted() && collision.check_collision(turtix->get_body(), enemies[i]->get_body(), from))
        {
            if (from == FROM_UP)
                enemies.erase(enemies.begin() + i);
            else if (from == FROM_LEFT || from == FROM_RIGHT)
                turtix->loose_HP();
        }
}

void Game::collision_between_turtix_and_mad_enemies()
{
    Collision collision;
    Intersection from;
    for (int i = 0; i < mad_enemies.size(); i++)
    {
        if (!turtix->get_gosted() && collision.check_collision(turtix->get_body(), mad_enemies[i]->get_body(), from))
        {
            if (from == FROM_UP)
            {
                if (mad_enemies[i]->get_mad())
                    turtix->loose_HP();
                else
                    mad_enemies.erase(mad_enemies.begin() + i);
            }
            else if (from == FROM_LEFT || from == FROM_RIGHT)
                turtix->loose_HP();
        }
    }
}

void Game::collision_between_turtix_and_obstacle()
{
    Collision collision;
    Intersection from;

    if (!turtix->get_gosted() && collision.check_collision(turtix->get_body(), obstacle->get_body(), from))
        turtix->loose_HP();
}

void Game::check_if_game_over()
{
    if (turtix->get_HP() == 0)
    {
        set_is_game_over(true);
        has_won = false;
        return;
    }
    if (turtix->get_body()->getGlobalBounds().intersects(portal->get_body()->getGlobalBounds()) && mini_turtles.empty())
    {
        has_won = true;
        set_is_game_over(true);
    }
}

void Game::collision_between_turtix_and_mini_turtles()
{
    for (MiniTurtle *mini_turtle : mini_turtles)
    {
        mini_turtle->tick(platforms);
        if (turtix->get_body()->getGlobalBounds().intersects(mini_turtle->get_body()->getGlobalBounds()))
            mini_turtle->make_free();
    }
}