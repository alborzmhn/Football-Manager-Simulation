#include "header.hpp"

void Real_Team::set_members_name(string _team_name, vector<string> players_name, int players_position)
{
    team_name = _team_name;
    for (int i = 0; i < players_name.size(); i++)
    {
        // Player *temp = new Player(players_name[i], players_position);
        // team_players.push_back(temp);
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
    for (int i = 0; i < team_players.size(); i++)
    {
        if (team_players[i]->get_name() == name)
        {
            return true;
        }
    }
    return false;
}

Player *Real_Team::find_player_by_name(string name)
{
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

int Real_Team::get_no_goals_in_last_week()
{
    return no_goals[no_goals.size() - 1];
}

void Real_Team::set_goalkeepers(string _team_name, vector<string> players_name_cost)
{
    team_name = _team_name;
    vector<Player_data> players_data = make_players_data(players_name_cost);
    for (int i = 0; i < players_data.size(); i++)
    {
        Goalkeeper *temp = new Goalkeeper(players_data[i]);
        team_players.push_back(temp);
    }
}

void Real_Team::set_defenders(string _team_name, vector<string> players_name_cost)
{
    team_name = _team_name;
    vector<Player_data> players_data = make_players_data(players_name_cost);
    for (int i = 0; i < players_data.size(); i++)
    {
        Defender *temp = new Defender(players_data[i]);
        team_players.push_back(temp);
    }
}

void Real_Team::set_midfielders(string _team_name, vector<string> players_name_cost)
{
    team_name = _team_name;
    vector<Player_data> players_data = make_players_data(players_name_cost);
    for (int i = 0; i < players_data.size(); i++)
    {
        Midfielder *temp = new Midfielder(players_data[i]);
        team_players.push_back(temp);
    }
}

void Real_Team::set_forwards(string _team_name, vector<string> players_name_cost)
{
    team_name = _team_name;
    vector<Player_data> players_data = make_players_data(players_name_cost);
    for (int i = 0; i < players_data.size(); i++)
    {
        Forward *temp = new Forward(players_data[i]);
        team_players.push_back(temp);
    }
}

vector<Player_data> Real_Team::make_players_data(vector<string> name_cost)
{
    vector<Player_data> players_data;
    for (int i = 0; i < name_cost.size(); i++)
    {
        players_data.push_back(seperate_name_and_cost(name_cost[i]));
    }
    return players_data;
}

void Real_Team::add_winners_point(vector<string> team_players)
{
    for (int i = 0; i < team_players.size(); i++)
    {
        find_player_by_name(team_players[i])->add_win_point();
    }
}

void Real_Team::subtract_losers_point(vector<string> team_players)
{
    for (int i = 0; i < team_players.size(); i++)
    {
        find_player_by_name(team_players[i])->subtract_lost_point();
    }
}

void Real_Team::add_equal_game_point(vector<string> team_players)
{
    for (int i = 0; i < team_players.size(); i++)
    {
        find_player_by_name(team_players[i])->add_equal_point();
    }
}

Player_data Real_Team::seperate_name_and_cost(string name_cost)
{
    Player_data temp;
    string name;
    string cost;
    for (int i = 0; i < name_cost.size(); i++)
    {
        if (name_cost[i] == ':')
        {
            cost = name_cost.substr(i + 1, 3);
            break;
        }
        name += name_cost[i];
    }
    temp.player_name = name;
    temp.player_cost = stoi(cost);
    return temp;
}

void Real_Team::add_clean_sheet()
{
    is_clean_sheet.push_back(TRUE);
}

void Real_Team::add_no_clean_sheet()
{
    is_clean_sheet.push_back(FALSE);
}

bool Real_Team::does_clean_sheet_this_week()
{
    if (is_clean_sheet[is_clean_sheet.size() - 1])
        return true;
    return false;
}