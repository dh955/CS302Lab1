//Name: Daniel Huynh
//Professor Scott Emrich
//This code takes the file, parses the contents into their data structure, takes the '_' out, stores them into the struct
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Song {
    string title;
    int time;  // could also be a string
};

struct Album {
    map <int, Song > songs;
    string name;
    int time;
    int nsongs;  // optional variable but makes it easier
};

struct Artist {
    map <string, Album > albums;
    string name;
    int time;
    int nsongs;
};


int main(int argc, char *argv[]){
	ifstream fin;
	fin.open(argv[1]);
	string line;
	string temp;
	int min = 0;
	int sec = 0;
	int total = 0;
	char hold;
	Song song;
	Artist artist;
	Album album;

	stringstream ss;
    while(getline(fin,line))
    {
		//all of the title, time, artist, album, genre, track will be spliced seperately then put into their
		//respective data type in the struct
		
		//title
        ss << line;
        ss >> temp;
		song.title = temp;
		//replaces '_' for white space
		for(int i = 0; i < temp.length(); i++){
			if(temp[i] == '_') temp[i] = ' ';
		}
		//time
		ss << line;
		ss >> min >> hold >> sec;
		total = (min * 60) + sec;
		song.time = total;
		//artist
		ss << line;
		ss >> temp;
		//replaces '_' for white space
		for(int i = 0; i < temp.length(); i++){
			if(temp[i] == '_') temp[i] = ' ';
		}
		//Checks for dupe
		if(artist.albums.find(temp) == artist.albums.end()){
			artist.albums.insert(temp, song);
		}
		artist.name = temp;

		//album
        ss << line;
        ss >> temp;
		album.name = temp;
		//replaces '_' for white space
		for(int i = 0; i < temp.length(); i++){
			if(temp[i] == '_') temp[i] = ' ';
		}
		//genre 'not used anywhere'
        ss << line;
        ss >> temp;
		
		//track
        ss << line;
        ss >> sec;
		Album.songs.insert(sec, song);
    }
		fin.close();
}
