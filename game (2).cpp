#include "header.hpp"

game_data::game_data(Real_Team *_team_1, Real_Team *_team_2)
{
    team_1 = _team_1;
    team_2 = _team_2;
}

Real_Team *game_data::get_team_1()
{
    return team_1;
}

Real_Team *game_data::get_team_2()
{
    return team_2;
}

void game_data::set_result(vector<string> results)
{
    team_1->save_result(stoi(results[0]), stoi(results[1]));
    team_2->save_result(stoi(results[1]), stoi(results[0]));
}

void game_data::set_injured_players(vector<string> injured_players)
{
    for (int i = 0; i < injured_players.size(); i++)
    {
        if (find_the_team_contains_player(injured_players[i]) == 1)
            team_1->save_injured_player(injured_players[i]);
        else
            team_2->save_injured_player(injured_players[i]);
    }
}

void game_data::give_players_point(vector<string> team_players_1, vector<string> team_players_2, vector<string> result)
{
    give_points_part_one(team_players_1, team_players_2, result);
    calculate_clean_sheets(result);
    give_points_part_two(team_players_1, team_players_2);
    give_points_part_three(team_players_1, team_players_2);
    set_final_score(team_players_1, team_players_2);
}

void game_data::set_final_score(vector<string> team_players_1, vector<string> team_players_2)
{
    for (int i = 0; i < team_players_1.size(); i++)
    {
        find_player_by_name(team_players_1[i])->calculate_final_score();
        find_player_by_name(team_players_2[i])->calculate_final_score();
    }
}

void game_data::give_points_part_three(vector<string> team_players_1, vector<string> team_players_2)
{
    for (int i = 0; i < goal_scorers.size(); i++)
    {
        if (team_1->have_the_player(goal_scorers[i]->get_name()))
        {
            subtract_point_from_opposing_player(find_index_player_in_team(goal_scorers[i]->get_name(), team_players_1), team_players_2);
        }
        else if (team_2->have_the_player(goal_scorers[i]->get_name()))
        {
            subtract_point_from_opposing_player(find_index_player_in_team(goal_scorers[i]->get_name(), team_players_2), team_players_1);
        }
        else
        {
        }
    }
}

int game_data::find_index_player_in_team(string player_name, vector<string> team_players)
{
    for (int i = 0; i < team_players.size(); i++)
    {
        if (team_players[i] == player_name)
            return i;
    }
}

void game_data::subtract_point_from_opposing_player(int index_goal_scorer, vector<string> opposing_team)
{
    if (index_goal_scorer == 1 || index_goal_scorer == 8)
        find_player_by_name(opposing_team[4])->subtract_one_point();
    if (index_goal_scorer == 4 || index_goal_scorer == 10)
        find_player_by_name(opposing_team[1])->subtract_one_point();
    if (index_goal_scorer == 9 || index_goal_scorer == 2 || index_goal_scorer == 3)
    {
        find_player_by_name(opposing_team[2])->subtract_one_point();
        find_player_by_name(opposing_team[3])->subtract_one_point();
    }
    if (index_goal_scorer == 5 || index_goal_scorer == 6 || index_goal_scorer == 7)
    {
        find_player_by_name(opposing_team[5])->subtract_one_point();
        find_player_by_name(opposing_team[6])->subtract_one_point();
        find_player_by_name(opposing_team[7])->subtract_one_point();
    }
}

void game_data::give_points_part_two(vector<string> team_players_1, vector<string> team_players_2)
{
    for (int i = 0; i < team_players_1.size(); i++)
    {
        if (team_1->does_clean_sheet_this_week())
            find_player_by_name(team_players_1[i])->give_clean_sheet_point();
        else
            find_player_by_name(team_players_1[i])->subtract_goal_point(team_1->get_no_goals_in_last_week());
        if (team_2->does_clean_sheet_this_week())
            find_player_by_name(team_players_2[i])->give_clean_sheet_point();
        else
            find_player_by_name(team_players_2[i])->subtract_goal_point(team_2->get_no_goals_in_last_week());
    }
    give_individual_points(team_players_1);
    give_individual_points(team_players_2);
}

void game_data::give_individual_points(vector<string> team_players)
{
    for (int i = 0; i < team_players.size(); i++)
    {
        find_player_by_name(team_players[i])->give_initial_point();
        find_player_by_name(team_players[i])->give_goal_point();
        find_player_by_name(team_players[i])->give_assist_point();
        find_player_by_name(team_players[i])->give_own_goal_point();
    }
}

void game_data::calculate_clean_sheets(vector<string> result)
{
    if (result[0] == "0")
        team_2->add_clean_sheet();
    else
        team_2->add_no_clean_sheet();
    if (result[1] == "0")
        team_1->add_clean_sheet();
    else
        team_1->add_no_clean_sheet();
}

void game_data::give_points_part_one(vector<string> team_players_1, vector<string> team_players_2, vector<string> result)
{
    if (stoi(result[0]) > stoi(result[1]))
    {
        team_1->add_winners_point(team_players_1);
        team_2->subtract_losers_point(team_players_2);
    }
    else if (stoi(result[0]) < stoi(result[1]))
    {
        team_2->add_winners_point(team_players_2);
        team_1->subtract_losers_point(team_players_1);
    }
    else
    {
        team_2->add_equal_game_point(team_players_2);
        team_1->add_equal_game_point(team_players_1);
    }
}

void game_data::print()
{
    // cout << team_1->get_team_name() << " " << team_2->get_team_name() << "\n";
    cout << "\n\nteam 1: " << team_1->get_team_name() << "\n\n";
    team_1->print();
    cout << "\n\nteam 2: " << team_2->get_team_name() << "\n\n";
    team_2->print();
    // cout << "\n\n";
}

int game_data::find_the_team_contains_player(string name)
{
    if (team_1->have_the_player(name))
        return 1;
    // cout << 2;
    return 2;
}

void game_data::set_yellow_cards(vector<string> yellow_card_players)
{
    for (int i = 0; i < yellow_card_players.size(); i++)
    {
        // cout << yellow_card_players[i] << "\n";
        if (find_the_team_contains_player(yellow_card_players[i]) == 1)
            team_1->save_yellow_card_player(yellow_card_players[i]);
        else
            team_2->save_yellow_card_player(yellow_card_players[i]);
    }
}

void game_data::set_red_cards(vector<string> red_card_players)
{
    for (int i = 0; i < red_card_players.size(); i++)
    {
        if (find_the_team_contains_player(red_card_players[i]) == 1)
            team_1->save_red_card_player(red_card_players[i]);
        else
            team_2->save_red_card_player(red_card_players[i]);
    }
}

void game_data::set_players_goals_assists(vector<string> goals_assists)
{
    seperate_players_goals_assists(goals_assists);
    add_a_week();
    for (int i = 0; i < goal_scorers.size(); i++)
    {
        goal_scorers[i]->add_goal();
    }
    for (int i = 0; i < goal_assisters.size(); i++)
    {
        if (goal_assisters[i] == goal_scorers[i])
            goal_scorers[i]->add_own_goal();
        else
            goal_assisters[i]->add_assist();
    }
}

void game_data::add_a_week()
{
    for (int i = 0; i < team_1->get_all_players_of_team().size(); i++)
    {
        team_1->get_all_players_of_team()[i]->add_week();
    }
    for (int i = 0; i < team_2->get_all_players_of_team().size(); i++)
    {
        team_2->get_all_players_of_team()[i]->add_week();
    }
}

void game_data::seperate_players_goals_assists(vector<string> goals_assits)
{
    string goal_scorer, goal_assister;
    for (int i = 0; i < goals_assits.size(); i++)
    {
        goal_scorer = "", goal_assister = "";
        for (int j = 0; j < goals_assits[i].size(); j++)
        {
            if (goals_assits[i][j] == ':')
            {
                goal_assister = goals_assits[i].substr(j + 1);
                break;
            }
            goal_scorer += goals_assits[i][j];
        }
        if (goal_assister == "OWN_GOAL")
            goal_assisters.push_back(find_player_by_name(goal_scorer));
        else
            goal_assisters.push_back(find_player_by_name(goal_assister));
        goal_scorers.push_back(find_player_by_name(goal_scorer));
    }
}

Player *game_data::find_player_by_name(string name)
{
    for (int i = 0; i < team_1->get_all_players_of_team().size(); i++)
    {
        if (team_1->get_all_players_of_team()[i]->get_name() == name)
            return team_1->get_all_players_of_team()[i];
    }
    for (int i = 0; i < team_2->get_all_players_of_team().size(); i++)
    {
        if (team_2->get_all_players_of_team()[i]->get_name() == name)
            return team_2->get_all_players_of_team()[i];
    }
}