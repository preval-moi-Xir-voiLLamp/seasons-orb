/*! \file Constant.h
 */
#ifndef HEAD_CONSTANT
#define HEAD_CONSTANT
#include <SFML/Graphics.hpp>

/*! \brief Enumaration of the different actions one can have in the game
 */
enum class Action
{
    None,
    Left,
    Right,
    Up,
    Down,
};

/*! \brief Direction in the game
 */
enum class Direction
{
    None,
    Left,
    Right,
    Up,
    Down
};

inline sf::Vector2i operator+(sf::Vector2i lhs, Direction rhs)
{
    switch(rhs)
    {
    case Direction::None:
        break;

    case Direction::Left:
        lhs.x--;
        break;

    case Direction::Right:
        lhs.x++;
        break;

    case Direction::Up:
        lhs.y--;
        break;

    case Direction::Down:
        lhs.y++;
        break;
    }
    return lhs;
}

#endif //HEAD_CONSTANT
