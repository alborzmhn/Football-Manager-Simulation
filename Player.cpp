#include "header.hpp"

Player::Player(string _name, int _position)
{
    name = _name;
    position = _position;
    is_available = true;
    injury_weeks = 0;
}

string Player::get_name()
{
    return name;
}

int Player::get_position()
{
    return position;
}

vector<float> Player::get_score()
{
    return score;
}

bool Player::is_player_available()
{
    if (is_available)
        return true;
    return false;
}

bool Player::is_in_this_position(int _position)
{
    if (position == _position)
        return true;
    return false;
}

void Player::save_injury()
{
    injury = true;
    injury_weeks = MAX_INJURY_WEEKS;
}

void Player::save_yellow_cards()
{
    yellow_cards++;
}

void Player::save_score(float _score)
{
    // cout << _score << " ";
    score.push_back(_score);
}

void Player::change_score(string _score)
{
    score[score.size() - 1] = stof(_score);
}

void Player::save_red_cards()
{
    red_cards++;
}

bool Player::check_yellow_cards()
{
    if (yellow_cards == MAX_YELLOW_CARDS)
    {
        // cout << "yy " << name << "\n";
        is_available = false;
        yellow_cards = 0;
    }
}

float Player::get_average_score()
{
    float sum = 0;
    float num_of_play_weeks = 0;
    for (int i = 0; i < score.size(); i++)
    {
        if (score[i] > 0)
        {
            sum += score[i];
            num_of_play_weeks++;
        }
    }
    if (sum == 0)
        return 0.0;
    return sum / num_of_play_weeks;
}

bool Player::check_red_cards()
{
    if (red_cards == MAX_RED_CARDS)
    {
        // cout << "rr " << name << "\n";
        is_available = false;
        yellow_cards = 0;
        red_cards = 0;
    }
}

bool Player::check_injury()
{
    if (injury)
        is_available = false;
}

void Player::set_availablitiy()
{

    if (injury_weeks == 0)
    {
        is_available = true;
        injury = false;
    }
    else
    {
        injury_weeks--;
    }
}
