#include "header.hpp"

void Real_Team::set_members_name(string _team_name, vector<string> players_name, int players_position)
{
    team_name = _team_name;
    for (int i = 0; i < players_name.size(); i++)
    {
        Player *temp = new Player(players_name[i], players_position);
        team_players.push_back(temp);
    }
}

int Real_Team::find_player_position(string name)
{
    for (int i = 0; i < team_players.size(); i++)
    {
        if (team_players[i]->get_name() == name)
        {
            return team_players[i]->get_position();
        }
    }
    return 0;
}

string Real_Team::get_team_name()
{
    return team_name;
}

vector<Player *> Real_Team::get_all_players_of_team()
{
    return team_players;
}

void Real_Team::save_result(int _goals, int _no_goals)
{
    goals.push_back(_goals);
    no_goals.push_back(_no_goals);
}

void Real_Team::save_injured_player(string name)
{
    // cout << find_player_by_name(name)->get_name() << " ";
    find_player_by_name(name)->save_injury();
}

void Real_Team::save_yellow_card_player(string name)
{
    find_player_by_name(name)->save_yellow_cards();
}

void Real_Team::save_red_card_player(string name)
{
    find_player_by_name(name)->save_red_cards();
}

void Real_Team::save_score_player(string score, string name)
{
    find_player_by_name(name)->change_score(score);
}

bool Real_Team::have_the_player(string name)
{
    // cout << name.size() << "\n";
    // cout << team_players[team_players.size() - 1]->get_name().size() << "\n";
    for (int i = 0; i < team_players.size(); i++)
    {
        if (team_players[i]->get_name() == name)
        {
            // cout << "true";
            return true;
        }
    }
    // cout << "false";
    return false;
}

Player *Real_Team::find_player_by_name(string name)
{
    // print();
    for (int i = 0; i < team_players.size(); i++)
    {
        if (team_players[i]->get_name() == name)
            return team_players[i];
    }
}

void Real_Team::print()
{
    for (int i = 0; i < team_players.size(); i++)
    {
        cout << team_players[i]->get_name() << "\n";
    }
}

int Real_Team::get_game_point(int week_number)
{
    if (goals[week_number - 1] > no_goals[week_number - 1])
        return WIN_POINT;
    if (goals[week_number - 1] < no_goals[week_number - 1])
        return LOSE_POINT;
    if (goals[week_number - 1] == no_goals[week_number - 1])
        return EQUAL_POINT;
}

int Real_Team::get_total_goals()
{
    int count = 0;
    for (int i = 0; i < goals.size(); i++)
    {
        count += goals[i];
    }
    return count;
}

int Real_Team::get_total_no_goals()
{
    int count = 0;
    for (int i = 0; i < no_goals.size(); i++)
    {
        count += no_goals[i];
    }
    return count;
}

int Real_Team::get_total_score()
{
    int points = 0;
    for (int i = 0; i < goals.size(); i++)
    {
        points += get_game_point(i + 1);
    }
    return points;
}

int Real_Team::get_tafazol()
{
    return get_total_goals() - get_total_no_goals();
}

int Real_Team::get_goals_in_week(int week_number)
{
    return goals[week_number];
}