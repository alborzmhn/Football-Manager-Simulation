#include "header.hpp"

int main(){
    Admin* admin = new Admin ("admin", "123456");
    Futball futball(admin);
    futball.read_premier_leage_data();
    futball.read_order();
}