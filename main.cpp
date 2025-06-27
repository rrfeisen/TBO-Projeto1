#include "system.hpp"
int main() {
    MovieCinemaSystem system;

    cout << "=== SISTEMA DE BUSCA DE FILMES E CINEMAS ===" << endl;
    cout << "Carregando dados..." << endl;

    // Carrega arquivo para movies
    system.loadMovies("movies.tsv");

    // Carrega arquivo para cinemas
    system.loadCinemas("cinemas.csv");

    int option;
    do {
        cout << "\n=== MENU PRINCIPAL ===" << endl;
        cout << "1. Buscar filmes" << endl;
        cout << "2. Buscar cinemas" << endl;
        cout << "3. Mostrar tipos de título" << endl;
        cout << "4. Mostrar gêneros" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opção: ";
        cin >> option;

        switch (option) {
            case 1: {

                cout << "\n=== BUSCA DE FILMES ===" << endl;

                vector<string> titleTypes, genres;
                int minDuration = 0, maxDuration = 0, minYear = 0, maxYear = 0;

                cout << "Digite os tipos de título (separados por vírgula, ou ENTER para pular): ";
                cin.ignore();
                string input;
                getline(cin, input);
                if (!input.empty()) {
                    titleTypes = system.split(input, ',');
                }

                cout << "Digite os gêneros (separados por vírgula, ou ENTER para pular): ";
                getline(cin, input);
                if (!input.empty()) {
                    genres = system.split(input, ',');
                }

                cout << "Duração mínima em minutos (0 para pular): ";
                cin >> minDuration;

                cout << "Duração máxima em minutos (0 para pular): ";
                cin >> maxDuration;

                cout << "Ano mínimo (0 para pular): ";
                cin >> minYear;

                cout << "Ano máximo (0 para pular): ";
                cin >> maxYear;

                auto results = system.searchMovies(titleTypes, genres, minDuration, maxDuration, minYear, maxYear);
                system.displayMovies(results);
                cout << "Pressione Enter para continuar...";
                cin.get();
                break;
            }

            case 2: {

                cout << "\n=== BUSCA DE CINEMAS ===" << endl;

                vector<string> titleTypes, genres;
                int minDuration = 0, maxDuration = 0, minYear = 0, maxYear = 0;
                double centerX = 0, centerY = 0, maxDistance = 0, maxPrice = 0;

                cout << "Digite os tipos de título dos filmes (separados por vírgula, ou ENTER para pular): ";
                cin.ignore();
                string input;
                getline(cin, input);
                if (!input.empty()) {
                    titleTypes = system.split(input, ',');
                }

                cout << "Digite os gêneros dos filmes (separados por vírgula, ou ENTER para pular): ";
                getline(cin, input);
                if (!input.empty()) {
                    genres = system.split(input, ',');
                }

                cout << "Duração mínima dos filmes em minutos (0 para pular): ";
                cin >> minDuration;

                cout << "Duração máxima dos filmes em minutos (0 para pular): ";
                cin >> maxDuration;

                cout << "Coordenada X do centro de busca (0 para pular): ";
                cin >> centerX;

                cout << "Coordenada Y do centro de busca (0 para pular): ";
                cin >> centerY;

                cout << "Distância máxima (0 para pular): ";
                cin >> maxDistance;

                cout << "Preço máximo (0 para pular): ";
                cin >> maxPrice;

                cout << "Ano mínimo dos filmes (0 para pular): ";
                cin >> minYear;

                cout << "Ano máximo dos filmes (0 para pular): ";
                cin >> maxYear;

                auto results = system.searchCinemas(titleTypes, genres, minDuration, maxDuration,
                                                  centerX, centerY, maxDistance, maxPrice, minYear, maxYear);
                system.displayCinemas(results);
                cout << "Pressione Enter para continuar...";
                cin.get();
                break;
            }

            case 3: {
                system.showTitleTypes();
                cout << "Pressione Enter para continuar...";
                cin.get();       
                break;
            }

            case 4: {
                system.showGenres();
                cout << "Pressione Enter para continuar...";
                cin.get();
                break;
            }

        }

    } while (option != 0);

    cout << "\nObrigado por usar o sistema!" << endl;
    return 0;
}
