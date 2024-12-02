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
        if (find_the_team_contains_player(injured_players[i]) == TEAM_1)
            team_1->save_injured_player(injured_players[i]);
        else
            team_2->save_injured_player(injured_players[i]);
    }
}

void game_data::print()
{
    cout << "\n\nteam 1: " << team_1->get_team_name() << "\n\n";
    team_1->print();
    cout << "\n\nteam 2: " << team_2->get_team_name() << "\n\n";
    team_2->print();
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
        if (find_the_team_contains_player(yellow_card_players[i]) == TEAM_1)
            team_1->save_yellow_card_player(yellow_card_players[i]);
        else
            team_2->save_yellow_card_player(yellow_card_players[i]);
    }
}

void game_data::set_red_cards(vector<string> red_card_players)
{
    for (int i = 0; i < red_card_players.size(); i++)
    {
        if (find_the_team_contains_player(red_card_players[i]) == TEAM_1)
            team_1->save_red_card_player(red_card_players[i]);
        else
            team_2->save_red_card_player(red_card_players[i]);
    }
}

void game_data::set_players_score(vector<string> _players_score)
{
    vector<vector<string>> players_name_and_scores = seperate_players_scores(_players_score);
    vector<string> players_name = players_name_and_scores[0];
    vector<string> players_score = players_name_and_scores[1];
    for (int i = 0; i < players_score.size(); i++)
    {
        // cout << players_name[i] << " " << players_score[i] << " ";
        if (find_the_team_contains_player(players_name[i]) == TEAM_1)
            team_1->save_score_player(players_score[i], players_name[i]);
        else
            team_2->save_score_player(players_score[i], players_name[i]);
    }
}

vector<vector<string>> game_data::seperate_players_scores(vector<string> players_scores)
{
    string name, score;
    vector<vector<string>> players_and_scores;
    vector<string> temp;
    players_and_scores.push_back(temp);
    players_and_scores.push_back(temp);
    for (int i = 0; i < players_scores.size(); i++)
    {
        int flag = 1;
        name = "", score = "";
        for (int j = 0; j < players_scores[i].size(); j++)
        {
            if (players_scores[i][j] == ':')
            {
                flag = 0;
                continue;
            }
            if (flag)
                name += players_scores[i][j];
            else
                score += players_scores[i][j];
        }
        players_and_scores[0].push_back(name);
        players_and_scores[1].push_back(score);
    }
    return players_and_scores;
}