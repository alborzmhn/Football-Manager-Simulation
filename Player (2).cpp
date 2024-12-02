#include "header.hpp"

Player::Player(Player_data player_name_cost, int _position)
{
    name = player_name_cost.player_name;
    cost = player_name_cost.player_cost;
    position = _position;
    is_available = true;
    injury_weeks = 0;
    clean_sheet = 0;
}

int Player::get_cost()
{
    return cost;
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

vector<float> Player::get_final_score()
{
    return final_score;
}

void Player::add_win_point()
{
    score[score.size() - 1] += 5;
}

void Player::subtract_lost_point()
{
    score[score.size() - 1] -= 1;
}

void Player::add_equal_point()
{
    score[score.size() - 1]++;
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
    score.push_back(_score);
    final_score.push_back(_score);
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
        is_available = false;
        yellow_cards = 0;
    }
}

float Player::get_average_score()
{
    float sum = 0;
    float num_of_play_weeks = 0;
    for (int i = 0; i < final_score.size(); i++)
    {
        if (final_score[i] > 0)
        {
            sum += final_score[i];
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

void Player::add_goal()
{
    goals_number[goals_number.size() - 1]++;
}

void Player::add_assist()
{
    assists_number[assists_number.size() - 1]++;
}

void Player::add_own_goal()
{
    own_goals_number[own_goals_number.size() - 1]++;
}

void Player::add_week()
{
    goals_number.push_back(0);
    assists_number.push_back(0);
    own_goals_number.push_back(0);
}

void Player::give_own_goal_point()
{
    for (int i = 0; i < own_goals_number[own_goals_number.size() - 1]; i++)
    {
        score[score.size() - 1] += OWN_GOAL_POINT;
    }
}

int Player::get_total_goals()
{
    int count = 0;
    for (int i = 0; i < goals_number.size(); i++)
    {
        count += goals_number[i];
    }
    return count;
}

int Player::get_total_assists()
{
    int count = 0;
    for (int i = 0; i < assists_number.size(); i++)
    {
        count += assists_number[i];
    }
    return count;
}

int Player::get_number_of_clean_sheets()
{
    return clean_sheet;
}

string Player::convert_number_to_position_name(int position)
{
    if (position == GOALKEEPER)
        return "gk";
    if (position == DEFENDER)
        return "df";
    if (position == MIDFIELDER)
        return "md";
    if (position == FORWARD)
        return "fw";
}

void Player::subtract_one_point()
{
    score[score.size() - 1]--;
}

void Player::calculate_final_score()
{
    float surat = 10;
    float makhraj = 1 + exp(-(score[score.size() - 1]) / 6);
    final_score[final_score.size() - 1] = surat / makhraj;
}

Goalkeeper::Goalkeeper(Player_data player_name_cost)
    : Player(player_name_cost, GOALKEEPER)
{
}

void Goalkeeper::give_clean_sheet_point()
{
    score[score.size() - 1] += GOALKEEPER_CLEAN_SHEET_POINT;
    clean_sheet++;
}

void Goalkeeper::give_initial_point()
{
    score[score.size() - 1] += GOALKEEPER_INITIAL_POINT;
}

void Goalkeeper::print_specifications(int order)
{
    cout << order << ". name: " << name << " | role: " << convert_number_to_position_name(position)
         << " | score: " << floorf(get_average_score() * 10) / 10 << " | cost: " << cost << " | clean sheets: " << clean_sheet << "\n";
}

void Goalkeeper::give_goal_point(){};

void Goalkeeper::give_assist_point(){};

void Goalkeeper::subtract_goal_point(int number_of_goals)
{
    score[score.size() - 1] -= number_of_goals;
}

Defender::Defender(Player_data player_name_cost)
    : Player(player_name_cost, DEFENDER)
{
}

void Defender::give_clean_sheet_point()
{
    clean_sheet++;
    score[score.size() - 1] += DEFENDER_CLEAN_SHEET_POINT;
}

void Defender::give_initial_point()
{
    score[score.size() - 1] += DEFENDER_INITIAL_POINT;
}

void Defender::give_goal_point()
{
    for (int i = 0; i < goals_number[goals_number.size() - 1]; i++)
    {
        score[score.size() - 1] += DEFENDER_GOAL_POINT;
    }
}

void Defender::give_assist_point()
{
    for (int i = 0; i < assists_number[assists_number.size() - 1]; i++)
    {
        score[score.size() - 1] += DEFENDER_ASSIST_POINT;
    }
}

void Defender::print_specifications(int order)
{
    cout << order << ". name: " << name << " | role: " << convert_number_to_position_name(position)
         << " | score: " << floorf(get_average_score() * 10) / 10 << " | cost: " << cost << " | goals: " << get_total_goals()
         << " | assists: " << get_total_assists() << " | clean sheets: " << clean_sheet << "\n";
}

void Defender::subtract_goal_point(int number_of_goals){};

Midfielder::Midfielder(Player_data player_name_cost)
    : Player(player_name_cost, MIDFIELDER)
{
}

void Midfielder::give_clean_sheet_point()
{
    clean_sheet++;
    score[score.size() - 1] += MIDFIELDER_CLEAN_SHEET_POINT;
}

void Midfielder::give_goal_point()
{
    for (int i = 0; i < goals_number[goals_number.size() - 1]; i++)
    {
        score[score.size() - 1] += MIDFIELDER_GOAL_POINT;
    }
}

void Midfielder::give_assist_point()
{
    for (int i = 0; i < assists_number[assists_number.size() - 1]; i++)
    {
        score[score.size() - 1] += MIDFIELDER_ASSIST_POINT;
    }
}

void Midfielder::print_specifications(int order)
{
    cout << order << ". name: " << name << " | role: " << convert_number_to_position_name(position)
         << " | score: " << floorf(get_average_score() * 10) / 10 << " | cost: " << cost << " | goals: " << get_total_goals()
         << " | assists: " << get_total_assists() << " | clean sheets: " << clean_sheet << "\n";
}

void Midfielder::give_initial_point(){};

void Midfielder::subtract_goal_point(int number_of_goals){};

Forward::Forward(Player_data player_name_cost)
    : Player(player_name_cost, FORWARD)
{
}

void Forward::give_goal_point()
{
    for (int i = 0; i < goals_number[goals_number.size() - 1]; i++)
    {
        score[score.size() - 1] += FORWARD_GOAL_POINT;
    }
    if (goals_number[goals_number.size() - 1] == 0)
    {
        score[score.size() - 1] -= 1;
    }
}

void Forward::give_assist_point()
{
    for (int i = 0; i < assists_number[assists_number.size() - 1]; i++)
    {
        score[score.size() - 1] += FORWARD_ASSIST_POINT;
    }
}

void Forward::print_specifications(int order)
{
    cout << order << ". name: " << name << " | role: " << convert_number_to_position_name(position)
         << " | score: " << floorf(get_average_score() * 10) / 10 << " | cost: " << cost << " | goals: " << get_total_goals()
         << " | assists: " << get_total_assists() << "\n";
}

void Forward::give_initial_point(){};

void Forward::give_clean_sheet_point(){};

void Forward::subtract_goal_point(int number_of_goals){};
