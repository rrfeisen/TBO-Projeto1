#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <set>
#include <iomanip>

using namespace std;
using namespace chrono;

// Estrutura para representar um filme
struct Movie {
    string id;
    string titleType;
    string primaryTitle;
    string originalTitle;
    bool isAdult;
    int startYear;
    int endYear;
    int runtimeMinutes;
    vector<string> genres;
};

// Estrutura para representar um cinema
struct Cinema {
    string id;
    string name;
    double coordX;
    double coordY;
    double price;
    vector<string> movieIds;
};

class MovieCinemaSystem {
private:
    vector<Movie> movies;
    vector<Cinema> cinemas;
    unordered_map<string, int> movieIndex; // Para busca rápida de filmes por ID

public:
    // Função para dividir string por delimitador
    vector<string> split(const string &str, char delimiter) {
        vector<string> tokens;
        stringstream ss(str);
        string token;
        while (getline(ss, token, delimiter)) {
            // Remove espaços em branco no início e fim
            token.erase(0, token.find_first_not_of(" \t\r\n"));
            token.erase(token.find_last_not_of(" \t\r\n") + 1);
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
        return tokens;
    }

    // Função para carregar filmes do arquivo (formato TSV do IMDb)
    bool loadMovies(const string &filename) {
        auto start = high_resolution_clock::now();
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "ERRO: Não foi possível abrir o arquivo '" << filename << "'" << endl;
            return false;
        }
        string line;
        // Ler primeira linha (cabeçalho)
        getline(file, line);

        while (getline(file, line)) {
            vector<string> fields = split(line, '\t');
            // Verificar se tem pelo menos os campos mínimos
            if (fields.size() < 9) {
                continue;
            }

            Movie movie;

            // Formato: tconst, titleType, primaryTitle, originalTitle, isAdult, startYear, endYear, runtimeMinutes, genres
            movie.id = fields[0];
            movie.titleType = fields[1];
            movie.primaryTitle = fields[2];
            movie.originalTitle = fields[3];
            movie.isAdult = (fields[4] == "1");

            // startYear
            movie.startYear = (fields[5].empty() || fields[5] == "\\N") ? 0 : stoi(fields[5]);

            // endYear
            movie.endYear = (fields[6].empty() || fields[6] == "\\N") ? 0 : stoi(fields[6]);

            // runtimeMinutes
            movie.runtimeMinutes = (fields[7].empty() || fields[7] == "\\N") ? 0 : stoi(fields[7]);

            // genres
            if (!fields[8].empty() && fields[8] != "\\N") {
                movie.genres = split(fields[8], ',');
            }

            movies.push_back(movie);
            movieIndex[movie.id] = movies.size() - 1;
        }

        file.close();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Filmes carregados em " << duration.count() << " ms" << endl;
        return true;
    }

    // Função para carregar cinemas do arquivo (formato CSV personalizado)
    bool loadCinemas(const string &filename) {
        auto start = high_resolution_clock::now();
        ifstream file(filename);
        string line;
        // Ler primeira linha (cabeçalho)
        getline(file, line);

        while (getline(file, line)) {
            vector<string> fields = split(line, ',');

            if (fields.size() < 6) {
                continue;
            }

            Cinema cinema;

            // Formato: Cinema_ID, Nome_do_Cinema, Coordenada_X, Coordenada_Y, Preço_Ingresso, Filmes_Em_Exibição
            cinema.id = fields[0];

            cinema.name = fields[1];

            cinema.coordX = fields[2].empty() ? 0.0 : stod(fields[2]);
            cinema.coordY = fields[3].empty() ? 0.0 : stod(fields[3]);
            cinema.price = fields[4].empty() ? 0.0 : stod(fields[4]);

            // Filmes em exibição - podem estar em campos separados
            for (size_t i = 5; i < fields.size(); i++) {
                if (!fields[i].empty()) {
                    cinema.movieIds.push_back(fields[i]);
                }
            }

            cinemas.push_back(cinema);
        }

        file.close();

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Cinemas carregados em " << duration.count() << " ms" << endl;
        return true;
    }

    // Função para calcular distância entre dois pontos
    double calculateDistance(double x1, double y1, double x2, double y2) {
        double dx = x2 - x1;
        double dy = y2 - y1;
        return sqrt(dx * dx + dy * dy);
    }

    // Função para encontrar filme por ID
    Movie *findMovie(const string &movieId) {
        auto it = movieIndex.find(movieId);
        if (it != movieIndex.end()) {
            return &movies[it->second];
        }
        return nullptr;
    }

    // Função para verificar se filme atende aos critérios
    bool movieMatchesCriteria(const Movie &movie, const vector<string> &titleTypes, const vector<string> &genres,
                              int minDuration, int maxDuration, int minYear, int maxYear) {
        // Verificar tipo de título
        if (!titleTypes.empty()) {
            bool typeMatch = false;
            for (const string &type: titleTypes) {
                if (movie.titleType == type) {
                    typeMatch = true;
                    break;
                }
            }
            if (!typeMatch) return false;
        }

        // Verificar gêneros
        if (!genres.empty()) {
            bool genreMatch = false;
            for (const string &genre: genres) {
                for (const string &movieGenre: movie.genres) {
                    if (movieGenre == genre) {
                        genreMatch = true;
                        break;
                    }
                }
                if (genreMatch) break;
            }
            if (!genreMatch) return false;
        }

        // Verificar duração
        if (minDuration > 0 && movie.runtimeMinutes < minDuration) return false;
        if (maxDuration > 0 && movie.runtimeMinutes > maxDuration) return false;

        // Verificar ano
        if (minYear > 0 && movie.startYear < minYear) return false;
        if (maxYear > 0 && movie.startYear > maxYear) return false;

        return true;
    }

    // Buscar filmes
    vector<Movie> searchMovies(const vector<string> &titleTypes = {},
                               const vector<string> &genres = {},
                               int minDuration = 0, int maxDuration = 0,
                               int minYear = 0, int maxYear = 0) {
        auto start = high_resolution_clock::now();

        vector<Movie> results;

        for (const Movie &movie: movies) {
            if (movieMatchesCriteria(movie, titleTypes, genres, minDuration, maxDuration, minYear, maxYear)) {
                results.push_back(movie);
            }
        }

        // Ordenar resultados por título
        sort(results.begin(), results.end(), [](const Movie &a, const Movie &b) {
            return a.primaryTitle < b.primaryTitle;
        });

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Busca de filmes executada em " << duration.count() << " ms" << endl;

        return results;
    }

    // Buscar cinemas
    vector<Cinema> searchCinemas(const vector<string> &titleTypes = {},
                                 const vector<string> &genres = {},
                                 int minDuration = 0, int maxDuration = 0,
                                 double centerX = 0, double centerY = 0, double maxDistance = 0,
                                 double maxPrice = 0,
                                 int minYear = 0, int maxYear = 0) {
        auto start = high_resolution_clock::now();

        vector<Cinema> results;

        for (const Cinema &cinema: cinemas) {
            bool cinemaMatches = true;

            // Verificar distância
            if (maxDistance > 0) {
                double distance = calculateDistance(cinema.coordX, cinema.coordY, centerX, centerY);
                if (distance > maxDistance) {
                    cinemaMatches = false;
                }
            }

            // Verificar preço
            if (maxPrice > 0 && cinema.price > maxPrice) {
                cinemaMatches = false;
            }

            // Verificar se tem filmes que atendem aos critérios
            if (cinemaMatches && (!titleTypes.empty() || !genres.empty() || minDuration > 0 || maxDuration > 0 ||
                                  minYear > 0 || maxYear > 0)) {
                bool hasMatchingMovie = false;

                for (const string &movieId: cinema.movieIds) {
                    Movie *movie = findMovie(movieId);
                    if (movie && movieMatchesCriteria(*movie, titleTypes, genres, minDuration, maxDuration, minYear,
                                                      maxYear)) {
                        hasMatchingMovie = true;
                        break;
                    }
                }

                if (!hasMatchingMovie) {
                    cinemaMatches = false;
                }
            }

            if (cinemaMatches) {
                results.push_back(cinema);
            }
        }

        // Ordenar resultados por nome
        sort(results.begin(), results.end(), [](const Cinema &a, const Cinema &b) {
            return a.name < b.name;
        });

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << "Busca de cinemas executada em " << duration.count() << " ms" << endl;

        return results;
    }

    // Função para exibir resultados de filmes
    void displayMovies(const vector<Movie> &movies, int limit = 10) {
        cout << "\n=== RESULTADOS DE FILMES ===" << endl;
        cout << "Total encontrado: " << movies.size() << " filmes" << endl;
        cout << "Mostrando até " << min(limit, (int) movies.size()) << " resultados:" << endl;

        for (int i = 0; i < min(limit, (int) movies.size()); i++) {
            const Movie &movie = movies[i];
            cout << "\n" << (i + 1) << ". " << movie.primaryTitle << endl;
            cout << "   ID: " << movie.id << endl;
            cout << "   Tipo: " << movie.titleType << endl;
            cout << "   Título Original: " << movie.originalTitle << endl;
            cout << "   Ano: " << movie.startYear;
            if (movie.endYear > 0) cout << "-" << movie.endYear;
            cout << endl;
            cout << "   Duração: " << movie.runtimeMinutes << " min" << endl;
            cout << "   Adulto: " << (movie.isAdult ? "Sim" : "Não") << endl;
            cout << "   Gêneros: ";
            for (size_t j = 0; j < movie.genres.size(); j++) {
                cout << movie.genres[j];
                if (j < movie.genres.size() - 1) cout << ", ";
            }
            if (movie.genres.empty()) cout << "Não informado";
            cout << endl;
        }
    }

    // Função para exibir resultados de cinemas
    void displayCinemas(const vector<Cinema> &cinemas, int limit = 10) {
        cout << "\n=== RESULTADOS DE CINEMAS ===" << endl;
        cout << "Total encontrado: " << cinemas.size() << " cinemas" << endl;
        cout << "Mostrando até " << min(limit, (int) cinemas.size()) << " resultados:" << endl;

        for (int i = 0; i < min(limit, (int) cinemas.size()); i++) {
            const Cinema &cinema = cinemas[i];
            cout << "\n" << (i + 1) << ". " << cinema.name << endl;
            cout << "   ID: " << cinema.id << endl;
            cout << "   Coordenadas: (" << cinema.coordX << ", " << cinema.coordY << ")" << endl;
            cout << "   Preço: R$ " << fixed << setprecision(2) << cinema.price << endl;
            cout << "   Filmes em exibição: " << cinema.movieIds.size() << " filmes" << endl;

            // Mostrar alguns filmes em exibição
            cout << "   IDs dos filmes: ";
            for (size_t j = 0; j < min((size_t) 5, cinema.movieIds.size()); j++) {
                cout << cinema.movieIds[j];
                if (j < min((size_t) 5, cinema.movieIds.size()) - 1) cout << ", ";
            }
            if (cinema.movieIds.size() > 5) cout << "...";
            cout << endl;
        }
    }

    // Função para mostrar tipos de título
    void showTitleTypes() {
        set<string> uniqueTypes;
        for (const Movie &movie: movies) {
            uniqueTypes.insert(movie.titleType);
        }

        cout << "\n=== TIPOS DE TÍTULO DISPONÍVEIS ===" << endl;
        for (const string &type: uniqueTypes) {
            cout << "- " << type << endl;
        }
    }

    // Função para mostrar gêneros
    void showGenres() {
        set<string> uniqueGenres;
        for (const Movie &movie: movies) {
            for (const string &genre: movie.genres) {
                uniqueGenres.insert(genre);
            }
        }

        cout << "\n=== GÊNEROS DISPONÍVEIS ===" << endl;
        for (const string &genre: uniqueGenres) {
            cout << "- " << genre << endl;
        }
    }
};
