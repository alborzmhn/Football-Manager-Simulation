#include "header.hpp"

Week::Week(vector<game_data *> games)
{
    games_data = games;
}

void Week::push_back_game(game_data *game_data)
{
    games_data.push_back(game_data);
    // cout << game_data->team_1 << " " << game_data->team_2 << "\n";
}

vector<game_data *> Week::get_game_data()
{
    return games_data;
}