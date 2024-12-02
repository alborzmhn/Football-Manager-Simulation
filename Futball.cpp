#include "header.hpp"

Futball::Futball(Admin *_admin)
{
    flag_transfer_window = true;
    is_user_online = false;

    admin = _admin;
}

void Futball::read_one_week(string file_name)
{
    ifstream input_file;
    input_file.open(file_name);
    string line_of_file;
    getline(input_file, line_of_file);
    line_of_file = "";
    vector<game_data *> games;
    while (getline(input_file, line_of_file))
    {
        vector<string> teams_name = get_names(line_of_file, ':');
        game_data *game = make_game(teams_name);
        game->set_result(get_names(line_of_file, ':'));
        game->set_injured_players(get_names(line_of_file, ';'));
        game->set_yellow_cards(get_names(line_of_file, ';'));
        game->set_red_cards(get_names(line_of_file, ';'));
        set_team_players_score_with_zero(teams_name);
        game->set_players_score(get_names(line_of_file, ';'));
        games.push_back(game);
    }
    Week *week = new Week(games);
    weeks.push_back(week);
    input_file.close();
}

void Futball::set_team_players_score_with_zero(vector<string> teams_name)
{
    for (int i = 0; i < NUMBER_OF_TEAMS; i++)
    {
        for (int j = 0; j < find_team_by_name(teams_name[i])->get_all_players_of_team().size(); j++)
        {
            find_team_by_name(teams_name[i])->get_all_players_of_team()[j]->save_score(ZERO);
        }
    }
}

game_data *Futball::make_game(vector<string> teams_name)
{
    game_data *temp = new game_data(find_team_by_name(teams_name[0]), find_team_by_name(teams_name[1]));
    return temp;
}

void Futball::read_premier_leage_data()
{
    ifstream input;
    input.open("premier_league.csv");
    string line_of_file;
    getline(input, line_of_file);
    line_of_file = "";

    while (getline(input, line_of_file))
    {
        vector<string> team_name = get_names(line_of_file, ';');
        vector<string> players_name;
        Real_Team *temp_team = new Real_Team;
        for (int i = 0; i < NUMBER_OF_POSITIONS; i++)
        {
            players_name = get_names(line_of_file, ';');
            set_teams(team_name[0], players_name, i + 1, temp_team);
        }
        real_teams.push_back(temp_team);
    }
    input.close();
}

int Futball::get_first_comma_index(string &line)
{
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ',')
        {
            line.erase(line.begin(), line.begin() + i + 1);
            return i;
        }
    }
}

void Futball::set_teams(string team_name, vector<string> players_name, int players_position, Real_Team *temp_team)
{

    temp_team->set_members_name(team_name, players_name, players_position);
}

vector<int> Futball::find_first_5_commas(string line)
{
    vector<int> index_of_commas;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ',')
            index_of_commas.push_back(i);

        if (index_of_commas.size() == 5)
            return index_of_commas;
    }
}

vector<string> Futball::get_names(string &line, char spacer_charachter)
{
    string name = "";
    vector<string> names;
    if (line[0] == ',')
    {
        line.erase(line.begin(), line.begin() + 1);
        return names;
    }
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == spacer_charachter)
        {
            if (name != "")
            {
                names.push_back(name);
                name = "";
            }
            continue;
        }
        if (line[i + 1] == ',' || i == line.size() - 2)
        {
            name += line[i];
            names.push_back(name);
            line.erase(line.begin(), line.begin() + i + 2);
            break;
        }
        name += line[i];
    }
    return names;
}

vector<string> Futball::read_input(string line)
{
    string name = "";
    vector<string> names;
    line += " ";
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ')
        {
            if (name != "")
                names.push_back(name);
            name = "";
            continue;
        }
        name += line[i];
    }

    return names;
}

void Futball::read_order()
{
    string order = "", next_order = "";
    while (cin >> order >> next_order)
    {
        if (order == "GET")
            get_orders(next_order);
        if (order == "PUT")
            ;
        if (order == "DELETE")
            ;
        if (order == "POST")
            post_orders(next_order);
    }
    delete_vectors();
}

void Futball::delete_vectors()
{
    delete admin;
    for (int i = 0; i < real_teams.size(); i++)
    {
        delete real_teams[i];
    }
    for (int i = 0; i < user_teams.size(); i++)
    {
        delete user_teams[i];
    }
    for (int i = 0; i < weeks.size(); i++)
    {
        delete weeks[i];
    }
}

void Futball::post_orders(string order)
{
    if (order == "signup")
        signup();
    if (order == "login")
        login();
    if (order == "logout")
        logout();
    if (order == "sell_player")
        sell_player();
    if (order == "pass_week")
        pass_week();
    if (order == "buy_player")
        buy_player();
    if (order == "register_admin")
        register_admin();
    if (order == "open_transfer_window")
        open_transfer_window();
    if (order == "close_transfer_window")
        close_transfer_window();
}

void Futball::open_transfer_window()
{
    if (!admin->is_admin_online())
    {
        cout << "Permission Denied\n";
        return;
    }
    flag_transfer_window = true;
    cout << "Ok\n";
}

void Futball::close_transfer_window()
{
    if (!admin->is_admin_online())
    {
        cout << "Permission Denied\n";
        return;
    }
    flag_transfer_window = false;
    cout << "Ok\n";
}

void Futball::register_admin()
{
    string username, order, password;
    getline(cin, order);
    vector<string> order_words = read_input(order);
    if (is_anybody_online() || order_words[1] != "username" || order_words[3] != "password")
    {
        cout << "Bad Request\n";
        return;
    }
    username = order_words[2];
    password = order_words[4];
    admin->do_resgister(username, password);
}

void Futball::pass_week()
{
    if (!admin->is_admin_online())
    {
        cout << "Permission Denied\n";
        return;
    }
    string file_name = "week_" + to_string(weeks.size() + 1) + ".csv";
    read_one_week(file_name);
    for (int i = 0; i < user_teams.size(); i++)
    {
        user_teams[i]->save_last_arrange();
        if (user_teams[i]->is_team_full())
            user_teams[i]->ready_for_competition();
    }
    update_team_points();
    set_players_availability();
    check_players_absence();
    cout << "OK\n";
}

void Futball::set_players_availability()
{
    for (int i = 0; i < real_teams.size(); i++)
    {
        for (int j = 0; j < real_teams[i]->get_all_players_of_team().size(); j++)
        {
            real_teams[i]->get_all_players_of_team()[j]->set_availablitiy();
        }
    }
}

void Futball::check_players_absence()
{
    for (int i = 0; i < real_teams.size(); i++)
    {
        for (int j = 0; j < real_teams[i]->get_all_players_of_team().size(); j++)
        {
            real_teams[i]->get_all_players_of_team()[j]->check_yellow_cards();
            real_teams[i]->get_all_players_of_team()[j]->check_red_cards();
            real_teams[i]->get_all_players_of_team()[j]->check_injury();
        }
    }
}

void Futball::update_team_points()
{
    for (int i = 0; i < user_teams.size(); i++)
    {
        if (user_teams[i]->is_team_full())
            user_teams[i]->update_points(weeks.size() - 1);
    }
}

void Futball::sell_player()
{
    string order, name;
    cin >> order >> order;
    getline(cin, name);
    if (!is_user_online || order != "name")
    {
        cout << "Bad Request\n";
        return;
    }
    name.erase(name.begin(), name.begin() + 1);
    if (check_player_existence(name) && is_transfer_window_open())
        which_team_is_login()->delete_player(find_player_by_name(name));
}

void Futball::buy_player()
{
    string order, name;
    cin >> order >> order;
    getline(cin, name);
    if (!is_user_online || order != "name")
    {
        cout << "Bad Request\n";
        return;
    }
    name.erase(name.begin(), name.begin() + 1);
    if (check_player_existence(name) && is_transfer_window_open())
        which_team_is_login()->add_player(find_player_by_name(name));
}

bool Futball::is_transfer_window_open()
{
    if (flag_transfer_window)
        return true;
    cout << "Permission Denied\n";
    return false;
}

bool Futball::check_player_existence(string player_name)
{
    for (int i = 0; i < real_teams.size(); i++)
    {
        for (int j = 0; j < real_teams[i]->get_all_players_of_team().size(); j++)
        {
            if (real_teams[i]->get_all_players_of_team()[j]->get_name() == player_name)
                return true;
        }
    }
    cout << "Not Found\n";
    return false;
}

void Futball::logout()
{
    if (!is_anybody_online())
    {
        cout << "Bad Request\n";
        return;
    }
    if (admin->is_admin_online())
        admin->logout();
    else
    {
        which_team_is_login()->logout();
        is_user_online = false;
    }
}

User_Team *Futball::which_team_is_login()
{
    for (int i = 0; i < user_teams.size(); i++)
    {
        if (user_teams[i]->is_login())
            return user_teams[i];
    }
}

void Futball::signup()
{
    string team_name, order, password;
    getline(cin, order);
    vector<string> order_words = read_input(order);
    if (is_anybody_online() || order_words[1] != "team_name" || order_words[3] != "password")
    {
        cout << "Bad Request\n";
        return;
    }
    team_name = order_words[2];
    password = order_words[4];
    if (check_duplicate_team_name(team_name))
        return;
    User_Team *p = new User_Team(team_name, password);
    user_teams.push_back(p);
    is_user_online = true;
    cout << "OK\n";
}

bool Futball::check_duplicate_team_name(string name)
{
    for (int i = 0; i < user_teams.size(); i++)
    {
        if (user_teams[i]->get_name() == name)
        {
            cout << "Bad Request\n";
            return true;
        }
    }
    return false;
}

void Futball::login()
{
    string team_name, order, password;
    getline(cin, order);
    vector<string> order_words = read_input(order);
    if (is_anybody_online() || order_words[1] != "team_name" || order_words[3] != "password")
    {
        cout << "Bad Request\n";
        return;
    }
    team_name = order_words[2];
    password = order_words[4];
    if (check_user_team_existence(team_name))
        if (find_user_team_by_name(team_name)->check_password_correctness(password))
        {
            find_user_team_by_name(team_name)->login();
            is_user_online = true;
        }
}

bool Futball::check_user_team_existence(string team_name)
{
    for (int i = 0; i < user_teams.size(); i++)
    {
        if (user_teams[i]->get_name() == team_name)
        {
            return true;
        }
    }
    cout << "Not Found\n";
    return false;
}

bool Futball::is_anybody_online()
{
    if (is_user_online || admin->is_admin_online())
        return true;
    return false;
}

User_Team *Futball::find_user_team_by_name(string team_name)
{
    for (int i = 0; i < user_teams.size(); i++)
    {
        if (user_teams[i]->get_name() == team_name)
            return user_teams[i];
    }
}

void Futball::get_orders(string order)
{
    if (order == "team_of_the_week")
        make_team_of_the_week();
    if (order == "players")
        filter_players_of_team();
    if (order == "league_standings")
        print_league_standings();
    if (order == "matches_result_league")
        matches_result_league();
    if (order == "users_ranking")
        print_users_ranking();
    if (order == "squad")
        make_user_team();
}

void Futball::make_user_team()
{
    string name = find_team_name();
    if (!is_user_online)
    {
        cout << "Permission Denied\n";
        return;
    }
    if (!check_user_team_existence(name))
        return;
    vector<Player *> players_of_fantasy_team = find_user_team_by_name(name)->get_last_players();
    if (players_of_fantasy_team.size() < MAX_PLAYERS_OF_FANTASY_TEAM || weeks.size() == 0)
    {
        cout << "Empty\n";
        return;
    }
    print_user_team(players_of_fantasy_team, find_user_team_by_name(name));
}

string Futball::find_team_name()
{
    string name, order;
    getline(cin, order);
    vector<string> orders;
    order += " ";
    orders = get_names(order, ' ');
    if (orders.size() == 3)
        name = orders[2];
    else
        name = which_team_is_login()->get_name();
    return name;
}

void Futball::print_user_team(vector<Player *> players, User_Team *user_team)
{
    cout << "fantasy_team: " << user_team->get_name() << "\n";
    sort_players_by_their_position(players);
    vector<string> position_names = {"Goalkeeper: ", "Defender1: ", "Defender2: ", "Midfielders: ", "Striker: "};
    for (int i = 0; i < players.size(); i++)
    {
        cout << position_names[i] << players[i]->get_name() << "\n";
    }
    cout << "Total Points: " << floorf(user_team->get_team_point() * 10) / 10 << "\n";
}

void Futball::sort_players_by_their_position(vector<Player *> &players)
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = i + 1; j < players.size(); j++)
        {
            if (players[i]->get_position() > players[j]->get_position())
            {
                swap(players[i], players[j]);
            }
            else if (players[i]->get_position() == players[j]->get_position())
                if (players[i]->get_name() > players[j]->get_name())
                    swap(players[i], players[j]);
        }
    }
}

void Futball::print_users_ranking()
{
    vector<User_Team *> sorted_teams = sort_user_teams_by_their_points(user_teams);
    for (int i = 0; i < sorted_teams.size(); i++)
    {
        cout << i + 1 << ". team_name: " << sorted_teams[i]->get_name() << " | point: " << floorf(sorted_teams[i]->get_team_point() * 10) / 10 << "\n";
    }
}

vector<User_Team *> Futball::sort_user_teams_by_their_points(vector<User_Team *> teams)
{
    for (int i = 0; i < teams.size(); i++)
    {
        for (int j = i + 1; j < teams.size(); j++)
        {
            if (teams[i]->get_team_point() < teams[j]->get_team_point())
            {
                swap(teams[i], teams[j]);
            }
            else if (teams[i]->get_team_point() == teams[j]->get_team_point())
                if (teams[i]->get_name() > teams[j]->get_name())
                    swap(teams[i], teams[j]);
        }
    }
    return teams;
}

void Futball::matches_result_league()
{
    string order;
    getline(cin, order);
    order += ' ';
    vector<string> order_words = read_input(order);
    int week_number = find_the_chosen_week(order_words);
    print_matches_result(week_number);
}

int Futball::find_the_chosen_week(vector<string> order_words)
{
    int week_number = 0;
    if (order_words.size() == 3 && order_words[1] == "week")
        if (stoi(order_words[2]) - 1 > weeks.size() - 1 || stoi(order_words[2]) - 1 < 0)
        {
            cout << "Bad Request\n";
            return NOT_FOUND;
        }
        else
            week_number = stoi(order_words[2]) - 1;
    else if (order_words.size() == 1 && order_words[0] == "?")
        week_number = weeks.size() - 1;
    else
    {
        cout << "Bad Request\n";
        return NOT_FOUND;
    }
    return week_number;
}

void Futball::print_matches_result(int week_number)
{
    for (int i = 0; i < weeks[week_number]->get_game_data().size(); i++)
    {
        cout << weeks[week_number]->get_game_data()[i]->get_team_1()->get_team_name() << " ";
        cout << weeks[week_number]->get_game_data()[i]->get_team_1()->get_goals_in_week(week_number) << " | ";
        cout << weeks[week_number]->get_game_data()[i]->get_team_2()->get_team_name() << " ";
        cout << weeks[week_number]->get_game_data()[i]->get_team_2()->get_goals_in_week(week_number) << "\n";
    }
}

void Futball::print_league_standings()
{
    sort_teams_by_their_score();
    cout << "league standings: \n";
    for (int i = 0; i < real_teams.size(); i++)
    {
        cout << i + 1 << ". " << real_teams[i]->get_team_name() << ": score: " << real_teams[i]->get_total_score()
             << " | GF: " << real_teams[i]->get_total_goals() << " | GA: " << real_teams[i]->get_total_no_goals() << "\n";
    }
}

void Futball::sort_teams_by_their_score()
{
    for (int i = 0; i < real_teams.size(); i++)
    {
        for (int j = i + 1; j < real_teams.size(); j++)
        {
            if (real_teams[i]->get_total_score() < real_teams[j]->get_total_score())
            {
                swap(real_teams[i], real_teams[j]);
            }
            else if (real_teams[i]->get_total_score() == real_teams[j]->get_total_score())
                sort_teams_by_their_tafazol(&real_teams[i], &real_teams[j]);
        }
    }
}

void Futball::sort_teams_by_their_tafazol(Real_Team **team_1, Real_Team **team_2)
{
    if ((*team_1)->get_tafazol() < (*team_2)->get_tafazol())
    {
        Real_Team *temp = *team_1;
        *team_1 = *team_2;
        *team_2 = temp;
    }
    else if ((*team_1)->get_tafazol() == (*team_2)->get_tafazol())
        sort_teams_by_their_goals(team_1, team_2);
}

void Futball::sort_teams_by_their_goals(Real_Team **team_1, Real_Team **team_2)
{
    if ((*team_1)->get_total_goals() < (*team_2)->get_total_goals())
    {
        Real_Team *temp = *team_1;
        *team_1 = *team_2;
        *team_2 = temp;
    }
}

void Futball::filter_players_of_team()
{
    string order;
    int chosen_position;
    getline(cin, order);
    vector<string> order_words = read_input(order);
    vector<Player *> players_in_position, sorted_players;
    string team_name = make_team_name(order_words[2]);
    if (!check_real_team_existence(team_name))
        return;
    if (order_words.size() > 3 && order_words[3] != "ranks")
    {
        if (!(chosen_position = change_position_name_to_int(order_words[3])))
            return;
        get_players_of_team_by_position(find_team_by_name(team_name), chosen_position, players_in_position);
    }
    else
        for (int i = 0; i < NUMBER_OF_POSITIONS; i++)
        {
            get_players_of_team_by_position(find_team_by_name(team_name), i + 1, players_in_position);
        }
    print_players_of_team(players_in_position, order_words);
}

bool Futball::check_real_team_existence(string team_name)
{
    for (int i = 0; i < real_teams.size(); i++)
    {
        if (real_teams[i]->get_team_name() == team_name)
        {
            return true;
        }
    }
    cout << "Not Found\n";
    return false;
}

string Futball::make_team_name(string team_name)
{
    for (int i = 0; i < team_name.size(); i++)
    {
        if (team_name[i] == '_')
            team_name[i] = ' ';
    }
    return team_name;
}

void Futball::print_players_of_team(vector<Player *> players_in_position, vector<string> order_words)
{
    vector<Player *> sorted_players;
    if (order_words[order_words.size() - 1] == "ranks")
        sorted_players = sort_players_by_their_rank(players_in_position);
    else
        sorted_players = sort_players_by_their_name(players_in_position);
    cout << "list of players: \n";
    for (int i = 0; i < sorted_players.size(); i++)
    {
        cout << i + 1 << ". name: " << sorted_players[i]->get_name() << " | role: " << convert_number_to_position_name(sorted_players[i]->get_position()) << " | score: " << floorf(sorted_players[i]->get_average_score() * 10) / 10 << "\n";
    }
}

string Futball::convert_number_to_position_name(int position)
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

vector<Player *> Futball::sort_players_by_their_name(vector<Player *> players_in_position)
{
    vector<string> players_name;
    for (int i = 0; i < players_in_position.size(); i++)
    {
        players_name.push_back(players_in_position[i]->get_name());
    }
    sort(players_name.begin(), players_name.end());
    vector<Player *> sorted_players;
    for (int i = 0; i < players_name.size(); i++)
    {
        sorted_players.push_back(find_player_by_name(players_name[i]));
    }
    return sorted_players;
}

Player *Futball::find_player_by_name(string name)
{
    for (int i = 0; i < real_teams.size(); i++)
    {
        for (int j = 0; j < real_teams[i]->get_all_players_of_team().size(); j++)
        {
            if (real_teams[i]->get_all_players_of_team()[j]->get_name() == name)
            {
                return real_teams[i]->get_all_players_of_team()[j];
            }
        }
    }
}

int Futball::change_position_name_to_int(string position)
{
    if (position == "gk")
        return 1;
    if (position == "df")
        return 2;
    if (position == "md")
        return 3;
    if (position == "fw")
        return 4;
    else
    {
        cout << "Bad Request\n";
        return NOT_FOUND;
    }
}

void Futball::get_players_of_team_by_position(Real_Team *team, int position, vector<Player *> &players_in_position)
{
    vector<Player *> players = team->get_all_players_of_team();
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_position() == position)
        {
            players_in_position.push_back(players[i]);
        }
    }
}

Real_Team *Futball::find_team_by_name(string name)
{
    for (int i = 0; i < real_teams.size(); i++)
    {
        if (name == real_teams[i]->get_team_name())
            return real_teams[i];
    }
}

void Futball::make_team_of_the_week()
{
    string order;
    getline(cin, order);
    vector<string> order_words = read_input(order);
    int week_number = find_the_chosen_week(order_words);
    if (week_number == NOT_FOUND)
        return;
    cout << "team of the weak:\n";
    make_position_of_the_week(GOALKEEPER, 1, week_number, "GoalKeeper");
    make_position_of_the_week(DEFENDER, 2, week_number, "Defender");
    make_position_of_the_week(MIDFIELDER, 1, week_number, "Midfielder");
    make_position_of_the_week(FORWARD, 1, week_number, "Forward");
}

void Futball::make_position_of_the_week(int position, int number_of_players, int week_number, string position_name)
{
    vector<Player *> players_in_position = seperate_players_position(position);
    vector<Player *> sorted_players = sort_players_by_their_rank_and_name(players_in_position, week_number);
    print_team_of_the_week(sorted_players, position_name, week_number, number_of_players);
}

vector<Player *> Futball::sort_players_by_their_rank_and_name(vector<Player *> players, int week_number)
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = i + 1; j < players.size(); j++)
        {
            if (players[i]->get_score()[week_number] < players[j]->get_score()[week_number])
                swap(players[i], players[j]);
            else if (players[i]->get_score()[week_number] == players[j]->get_score()[week_number])
                if (players[i]->get_name() > players[j]->get_name())
                    swap(players[i], players[j]);
        }
    }
    return players;
}

vector<Player *> Futball::sort_players_by_their_rank(vector<Player *> players)
{
    for (int i = 0; i < players.size(); i++)
    {
        for (int j = i + 1; j < players.size(); j++)
        {
            if (players[i]->get_average_score() < players[j]->get_average_score())
                swap(players[i], players[j]);
            else if (players[i]->get_average_score() == players[j]->get_average_score())
                if (players[i]->get_name() > players[j]->get_name())
                    swap(players[i], players[j]);
        }
    }
    return players;
}

void Futball::print_team_of_the_week(vector<Player *> max_score_player, string position_name, int week_number, int number_of_players)
{
    for (int i = 0; i < number_of_players; i++)
    {
        if (number_of_players > 1)
            cout << position_name << i + 1 << ": " << max_score_player[i]->get_name() << " | Score: " << max_score_player[i]->get_score()[week_number] << "\n";
        else
            cout << position_name << ": " << max_score_player[i]->get_name() << " | Score: " << floorf(max_score_player[i]->get_score()[week_number] * 10) / 10 << "\n";
    }
}

bool Futball::check_no_duplicate_player(Player *player_max, vector<Player *> players)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->get_name() == player_max->get_name())
            return false;
    }
    return true;
}

vector<Player *> Futball::seperate_players_position(int position)
{
    vector<Player *> players_in_position;
    for (int i = 0; i < real_teams.size(); i++)
    {
        for (int j = 0; j < real_teams[i]->get_all_players_of_team().size(); j++)
        {
            if (position == real_teams[i]->get_all_players_of_team()[j]->get_position())
            {
                players_in_position.push_back(real_teams[i]->get_all_players_of_team()[j]);
            }
        }
    }
    return players_in_position;
}

int Futball::find_player_position_by_name(string name)
{
    int position;
    for (int i = 0; i < real_teams.size(); i++)
    {
        if (position = real_teams[i]->find_player_position(name))
        {
            return position;
        }
    }
}
