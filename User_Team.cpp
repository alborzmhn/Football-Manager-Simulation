#include "header.hpp"

User_Team::User_Team(string _team_name, string _password)
{
    team_name = _team_name;
    password = _password;
    is_user_login = true;
    is_team_ready = false;
    number_of_sales = 0;
    team_point = 0;
    is_team_join_competition = false;
}

string User_Team::get_name()
{
    return team_name;
}

void User_Team::save_last_arrange()
{
    last_players = players;
}

vector<Player *> User_Team::get_last_players()
{
    return last_players;
}

bool User_Team::check_password_correctness(string _password)
{
    if (password == _password)
        return true;
    cout << "Permission Denied\n";
    return false;
}

void User_Team::login()
{
    is_user_login = true;
    cout << "OK\n";
}

bool User_Team::is_login()
{
    return is_user_login;
}

void User_Team::logout()
{
    is_user_login = false;
    cout << "OK\n";
}

void User_Team::delete_player(Player *player)
{
    if (!is_team_join_competition)
    {
        players.erase(players.begin() + find_index_player(player));
        cout << "OK\n";
    }
    else
    {
        if (number_of_sales < 2)
        {
            players.erase(players.begin() + find_index_player(player));
            number_of_sales++;
            cout << "OK\n";
        }
        else
            cout << "Persmission Denied\n";
    }
}

float User_Team::get_team_point()
{
    return team_point;
}

bool User_Team::does_team_have_free_space(int position)
{
    if (position == GOALKEEPER)
    {
        if (number_of_players_in_position(GOALKEEPER) < 1)
            return true;
    }
    if (position == DEFENDER)
    {
        if (number_of_players_in_position(DEFENDER) < 2)
            return true;
    }
    if (position == MIDFIELDER)
    {
        if (number_of_players_in_position(MIDFIELDER) < 1)
            return true;
    }
    if (position == FORWARD)
    {
        if (number_of_players_in_position(FORWARD) < 1)
            return true;
    }
    cout << "Bad Request\n";
    return false;
}

int User_Team::number_of_players_in_position(int position)
{
    int count = 0;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_position() == position)
            count++;
    }
    return count;
}

void User_Team::update_points(int week_number)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->is_player_available())
            team_point += players[i]->get_score()[week_number];
    }
}

bool User_Team::is_team_full()
{
    if (players.size() == MAX_PLAYERS_OF_FANTASY_TEAM)
        return true;
    return false;
}

void User_Team::add_player(Player *player)
{
    if (player->is_player_available())
        if (does_team_have_free_space(player->get_position()) && check_no_duplicate_buy(player))
        {
            players.push_back(player);
            check_is_ready();
            cout << "OK\n";
            return;
        }
    cout << "This players is not available for next week\n";
}

bool User_Team::check_no_duplicate_buy(Player *player)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i] == player)
            return false;
    }
    return true;
}

void User_Team::check_is_ready()
{
    if (players.size() == MAX_PLAYERS_OF_FANTASY_TEAM)
    {
        is_team_ready = true;
    }
    else
        is_team_ready = false;
}

bool User_Team::is_ready()
{
    return is_team_ready;
}

int User_Team::find_index_player(Player *player)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i] == player)
            return i;
    }
}

vector<Player *> User_Team::get_players()
{
    return players;
}

void User_Team::ready_for_competition()
{
    is_team_join_competition = true;
}