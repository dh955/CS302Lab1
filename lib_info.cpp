//Name: Daniel Huynh and Ian Henson
//Professor Scott Emrich
//This code takes the file, parses the contents into their data structure, takes the '_' out, stores them into the struct and then prints them for the user
#include <iostream>
#include <map>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

struct Song {
	string title;
	int time = 0;  // could also be a string
};

struct Album {
	map <int, Song > songs;
	string name;
	int time = 0;
	int nsongs = 1;  // optional variable but makes it easier
};

struct Artist {
	map <string, Album > albums;
	string name;
	int time = 0;
	int nsongs = 1;
};


int main(int argc, char *argv[]){
	ifstream fin;
	fin.open(argv[1]);

	string line;
	map<string, Artist> Artists;

	stringstream ss;
	while(getline(fin,line))
	{
		//all of the title, time, artist, album, genre, track will be spliced seperately then put into their
		//respective data type in the struct
		Song song;
		Artist artist;
		Album album;

		string title, time, art, albumn, genre, track;
		ss << line;
		ss >> title >> time >> art >> albumn >> genre >> track;

		//song
		//replaces '_' for white space
		for(int i = 0; i < int(title.length()); i++){
			if(title[i] == '_') title[i] = ' ';
		}
		song.title = title;

		//pull minute and second info
		int min = stoi(time.substr(0, time.find(':')));
		int sec = stoi(time.substr(time.find(':')+1,time.size()));
		int total = (min * 60) + sec;
		song.time = total;
		//artist
		//replaces '_' for white space
		for(int i = 0; i < int(art.length()); i++){
			if(art[i] == '_') art[i] = ' ';
		}
		//different behavior if new or already stored
		if(Artists.find(art) != Artists.end()){
			Artists[art].time += total;
			Artists[art].nsongs++;
		}
		else{
			artist.time = total;
			artist.name = art;

			Artists[art] = artist;
		}
		//albumn
		//replaces '_' for white space
		for(int i = 0; i < int(albumn.length()); i++){
			if(albumn[i] == '_') albumn[i] = ' ';
		}
		//same thing as above
		if(Artists[art].albums.find(albumn) != Artists[art].albums.end()){
			Artists[art].albums[albumn].time += total;
			Artists[art].albums[albumn].nsongs++;
			Artists[art].albums[albumn].songs[stoi(track)] = song;
		}
		else{
			album.time = total;
			album.songs[stoi(track)] = song;
			album.name = albumn;

			Artists[art].albums[albumn] = album;
		}
		//genre 'not used anywhere'

		//track, inserts new track into albums map
		//puts album into struc
		//find dupe album
		//adds artist to unordered map, checks for dupe artist, then updates info in Artists
		
		ss.clear();//reset string stream, \n sometimes 
	}

	fin.close();

	for(auto i = Artists.begin(); i != Artists.end(); ++i){
		cout << i->first << ": " << (i->second).nsongs << ", " << (i->second).time / 60 << ":";
		((i->second).time % 60 >= 10) ? cout << (i->second).time % 60 << endl : cout << '0' << (i->second).time % 60 << endl;//make sure the extra 0 is printed
		for(auto j = (i->second).albums.begin(); j != (i->second).albums.end(); ++j){
			cout << '\t' << j->first<< ": "<< (j->second).nsongs << ", " << (j->second).time / 60<< ":";
			((j->second).time % 60 >= 10) ? cout << (j->second).time % 60 << endl : cout << '0' << (j->second).time % 60 << endl;//make sure the extra 0 is printed
			for(auto k = (j->second).songs.begin(); k != (j->second).songs.end(); ++k){
				cout << "\t\t" << k->first << ". " << (k->second).title << ": " << (k->second).time / 60 << ':';
				((k->second).time % 60 >= 10) ? cout << (k->second).time % 60 << endl : cout << '0' << (k->second).time % 60 << endl;//make sure the extra 0 is printed
			}
		}
	}
}
