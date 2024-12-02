#include "header.hpp"

User_Team::User_Team(string _team_name, string _password)
{
    team_name = _team_name;
    password = _password;
    is_user_login = true;
    is_team_ready = false;
    number_of_sales = 0;
    team_point = 0;
    team_captain = NULL;
    budget = 2500;
}

string User_Team::get_name()
{
    return team_name;
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
        is_player_captain(player);
        cout << "OK\n";
        budget += player->get_cost();
    }
    else
    {
        if (number_of_sales < 2)
        {
            players.erase(players.begin() + find_index_player(player));
            number_of_sales++;
            is_player_captain(player);
            cout << "OK\n";
            budget += player->get_cost();
        }
        else
            cout << "Persmission Denied\n";
    }
}

void User_Team::save_last_arrange()
{
    last_players = players;
}

vector<Player *> User_Team::get_last_players()
{
    return last_players;
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
        {
            if (players[i] == team_captain)
                team_point += (TWO_TIMES * (players[i]->get_final_score()[week_number]));
            else
                team_point += players[i]->get_final_score()[week_number];
        }
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
    if (player->get_cost() > budget)
    {
        cout << "Bad Request\n";
        return;
    }
    if (player->is_player_available())
        if (does_team_have_free_space(player->get_position()) && check_no_duplicate_buy(player))
        {
            players.push_back(player);
            check_is_ready();
            cout << "OK\n";
            budget -= player->get_cost();
            return;
        }
    cout << "This players is not available for next week\n";
}

int User_Team::calculate_team_cost()
{
    int total_cost = 0;
    for (int i = 0; i < players.size(); i++)
    {
        total_cost += players[i]->get_cost();
    }
    return total_cost;
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

void User_Team::set_team_captain(Player *captain)
{
    team_captain = captain;
    cout << "OK\n";
}

void User_Team::is_player_captain(Player *player)
{
    if (player == team_captain)
        team_captain = NULL;
}

bool User_Team::have_player(string name)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_name() == name)
            return true;
    }
    return false;
}

int User_Team::get_budget()
{
    return budget;
}

void User_Team::ready_for_competition()
{
    is_team_join_competition = true;
}

Player *User_Team::get_captain()
{
    return team_captain;
}