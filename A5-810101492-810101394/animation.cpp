// #pragma once
#include "animation.h"

using namespace std;

enum Direction
{
    RIGHT = 0,
    LEFT = 1,
    IDLE = 2,
    UP = 3,
};

Animation::Animation(Texture *_texture, ImageMatrix _images, float _switch_time)
{
    this->switch_time = _switch_time;
    images = _images;
    total_time = 0.0f;
    image_index = 0;
    current_image.x = 0;
    current_image.y = 0;

    uv_rect.width = _texture->getSize().x / float(images.row_count);
    uv_rect.height = _texture->getSize().y / float(images.col_count);
}
void Animation::update(const float& delta_time, bool is_moving)
{
    total_time += delta_time;

    if (total_time >= switch_time)
    {
        total_time -= switch_time;
        if (is_moving == true)
            pick_next_image();
    }
    uv_rect.top = current_image.y * uv_rect.height;
    if (face_right)
    {
        uv_rect.left = current_image.x * uv_rect.width;
        uv_rect.width = abs(uv_rect.width);
    }
    else
    {
        uv_rect.left = (current_image.x + 1) * abs(uv_rect.width);
        uv_rect.width = -abs(uv_rect.width);
    }
}
void Animation::set_direction(bool _face_right)
{
    face_right = _face_right;
}
void Animation::pick_next_image()
{
    current_image.x++;
    image_index++;

    if (current_image.x == images.row_count)
        go_to_next_frame_line();
    if (image_index == images.end_index)
        reset_frames();
}
void Animation::go_to_next_frame_line()
{
    current_image.x = 0;
    current_image.y++;
}
void Animation::reset_frames()
{
    current_image.x = 0;
    current_image.y = 0;
    image_index = 0;
}