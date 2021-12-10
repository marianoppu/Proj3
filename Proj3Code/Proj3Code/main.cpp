//
//  main.cpp
//  Proj3Code
//
//  Created by Mariano Patino-Paul on 12/9/21.
//

#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <iostream>
using namespace std::chrono;
using namespace std;

struct Song {
    
    double key;
    string artist_name;
    string track_name;
    double f_valence;
    double f_energy;
    double f_danceability;
    double f_loudness;
    double f_popularity;
    
    Song() {
        
        key = 0;
        this->artist_name = "";
        this->track_name = "";
        this->f_valence = 0;
        this->f_energy = 0;
        this->f_danceability = 0;
        this->f_loudness = 0;
        this->f_popularity = 0;
        
    }
    
//    Song(string artist_name, string track_name, double f_energy, double f_danceability, double f_loudness, double f_valence, double f_popularity) {
//
//        this->artist_name = artist_name;
//        this->track_name = track_name;
//        this->f_energy = f_energy;
//        this->f_danceability = f_danceability;
//        this->f_loudness = f_loudness;
//        this->f_valence = f_valence;
//        this->f_popularity = f_popularity;
//
//    }
    
};

class BST {
    
    struct node {
        
        double key;
        node* left;
        node* right;
        vector<Song> vec;
        
        node() {
            key = 0;
            left = right = nullptr;
        }
        
        node(Song s) {
            key = s.key;
            vec.push_back(s);
        }
        
    };

    node* root;

    node* makeEmpty(node* r) {
        
        if (r == NULL)
            return NULL;
        
        {
            makeEmpty(r->left);
            makeEmpty(r->right);
            delete r;
        }
        
        return NULL;
    }

    // Song s
    node* insert(Song s, node* root) {
        
        if (root == NULL) {
            root = new node;
            root->key = s.key;
            root->vec.push_back(s);
            root->left = root->right = NULL;
        }
        
        else if(s.key < root->key) {
            root->left = insert(s, root->left);
        }
        
        else if (s.key > root->key) {
            root->right = insert(s, root->right);
        }
        
        else if (s.key == root->key) {
            root->vec.push_back(s);
        }
        
        return root;
        
    }

    void ascendingInorder(node* t, int& c, string g) {
        
        if (c < 0) {
            return;
        }
        
        if (t == NULL) return;
        ascendingInorder(t->left, c, g);
        
        if (c > 0) {
            cout << g << t->key << " " << endl;
        } else {
            return;
        }
                
        for (int i = 0; i<t->vec.size(); i++) {
            c--;
            
            if (c >= 0) {
                cout << t->vec[i].track_name << " - " << t->vec[i].artist_name << endl;
            } else {
                return;
            }
            
        }
        
        cout << endl;
        
        if (c < 0) return;
        ascendingInorder(t->right, c, g);
        
    }
    
    void descendingReverse(node* t, int& c, string g) {
        
        if (c < 0) {
            return;
        }
        
        if (t == NULL) return;
        descendingReverse(t->right, c, g);
        
        if (c > 0) {
            cout << g << t->key << " " << endl;
        } else {
            return;
        }
                
        for (int i = 0; i<t->vec.size(); i++) {
            c--;
            
            if (c >= 0) {
                cout << t->vec[i].track_name << " - " << t->vec[i].artist_name << endl;
            } else {
                return;
            }
            
        }
        
        cout << endl;
        
        if (c < 0) return;
        descendingReverse(t->left, c, g);
        
    }


public:
    
    BST() {
        root = NULL;
    }

    ~BST() {
        root = makeEmpty(root);
    }

    void insert(Song s, double k) {
        
        s.key = k;
        
        root = insert(s, root);
    }


    void displayAscending(int count, string g) {
            
        ascendingInorder(root, count, g);
        cout << endl;
    }
    
    void displayDescending(int count, string g) {
            
        descendingReverse(root, count, g);
        cout << endl;
    }

};

// Save all data from CSV in vectors -> returns a vector of songs
vector<Song> getDataFromCSV(string filepath) {

    vector<Song> SONG_VECTOR;

    ifstream infile(filepath);

    if (infile.is_open()) {

        // 1. Read header data
        string lineFromFile;
        getline(infile, lineFromFile);

        // Get all entries
        while (getline(infile,lineFromFile)) {

            // Create a stream of a line of data from the file
            istringstream stream(lineFromFile);

            Song tempSong;

            getline(stream, tempSong.artist_name, ',');
            getline(stream, tempSong.track_name, ',');

            string tempDanceability;
            getline(stream, tempDanceability, ',');
            tempSong.f_danceability = stod(tempDanceability);

            string tempEnergy;
            getline(stream, tempEnergy, ',');
            tempSong.f_energy = stod(tempEnergy);
            
            string tempLoudness;
            getline(stream, tempLoudness, ',');
            tempSong.f_loudness = stod(tempLoudness);

            string tempValence;
            getline(stream, tempValence, ',');
            tempSong.f_valence = stod(tempValence);

            string tempPopularity;
            getline(stream, tempPopularity, ',');
            tempSong.f_popularity = stod(tempPopularity);
            
            SONG_VECTOR.push_back(tempSong);

        }

    } else {
        cout << "file not opened" << endl;
    }

    return SONG_VECTOR;
}

int main(int argc, const char * argv[]) {

    int numberOfSongs = 0;
    int category = 0;
    int order = 0;
    
    cout << "Number of songs you want in your new playlist: " << endl;
    
    cin >> numberOfSongs;
    
    cout << endl << "Select from 1-5. Would you like to sort your playlist by:" << endl;
    
    cout << "1. Valence" << endl;
    cout << "2. Energy" << endl;
    cout << "3. Danceability" << endl;
    cout << "4. Loudness" << endl;
    cout << "5. Popularity" << endl;
    
    cin >> category;
    
    cout << endl << "Nice! Would you like to sort your playlist in an 1.Ascending or 2.Descending order?" << endl;
    
    cin >> order;
        
    cout << endl << "Great choice! Here is your playlist:\n" << endl;
    
    auto start = high_resolution_clock::now();
    
    BST t;

    vector<Song> song_vector = getDataFromCSV("SpotifyMusicFeatures.csv");
    
    // Populate BST
    for (int i = 0; i<song_vector.size(); i++) {
        
        if (category == 1) {
            t.insert(song_vector[i], song_vector[i].f_valence);
        }
        else if (category == 2) {
            t.insert(song_vector[i], song_vector[i].f_energy);
        }
        else if (category == 3) {
            t.insert(song_vector[i], song_vector[i].f_danceability);
        }
        else if (category == 4) {
            t.insert(song_vector[i], song_vector[i].f_loudness);
        }
        else if (category == 5) {
            t.insert(song_vector[i], song_vector[i].f_popularity);
        }
        
    }
    
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "||| The BST sort of 130,000 songs took " << duration.count() << " milliseconds ||| \n" << endl;
    
    /*
     
     CALCULATE TIME IT TOOK !!!!
     
     */
    
    
    string arr[5] = {"Valence: ", "Energy: ", "Danceability: ", "Loudness: ", "Popularity: "};

    if (order == 1) {
        t.displayAscending(numberOfSongs, arr[category-1]);
    }
    
    if (order == 2) {
        t.displayDescending(numberOfSongs, arr[category-1]);
    }

}


