#include <SFML/Graphics.hpp>
using namespace sf;

struct ImageMatrix
{
    unsigned row_count;
    unsigned col_count;

    int start_index;
    int end_index;
};

class Animation
{
public:
    Animation(Texture *texture, ImageMatrix _images, float switch_time);
    void update(const float& delta_time, bool is_moving);
    void set_direction(bool _face_right);
    Texture *get_texture() { return texture; }
    IntRect uv_rect;

private:
    void go_to_next_frame_line();
    void reset_frames();
    void pick_next_image();

    Texture *texture;
    Vector2u current_image;

    int image_index = 0;
    ImageMatrix images;

    float total_time;
    float switch_time;

    bool face_right = true;
};