//Name: Daniel Huynh and Ian Henson PS: Line 67 is where it goes wrong
//Professor Scott Emrich
//This code takes the file, parses the contents into their data structure, takes the '_' out, stores them into the struct
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
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
	string temp;
	int min = 0;
	int sec = 0;
	int total = 0;
	char hold;

	Song song;
	Artist artist;
	Album album;

	unordered_map<string, Artist> Artsists;
	map<int, Song >::iterator nit;
	map<string, Album>::iterator artIter;

	stringstream ss;
	while(getline(fin,line))
	{
		//all of the title, time, artist, album, genre, track will be spliced seperately then put into their
		//respective data type in the struct

		//title
		ss << line;
		ss >> temp;
		song.title = temp;
		cout << temp << endl;
		//replaces '_' for white space
		for(int i = 0; i < int(temp.length()); i++){
			if(temp[i] == '_') temp[i] = ' ';
		}
		//time, bug line 67
		ss << line;
		ss >> min >> hold >> sec;
		total = (min * 60) + sec;
		song.time = total;
		album.time = total;
		artist.time = total;
		//artist
		ss << line;
		ss >> temp;
		//replaces '_' for white space
		for(int i = 0; i < int(temp.length()); i++){
			if(temp[i] == '_') temp[i] = ' ';
		}
			artist.name = temp;
			ss.clear();
		//album
		ss << line;
		ss >> temp;
		//replaces '_' for white space
		for(int i = 0; i < int(temp.length()); i++){
			if(temp[i] == '_') temp[i] = ' ';
		}
		cout << temp << endl;
		album.name = temp;
		//genre 'not used anywhere'
		ss << line;
		ss >> temp;

		//track, inserts new track into albums map
		ss << line;
		ss >> sec;
		//puts album into struc
		album.songs[sec] = song;
		//find dupe album
		artist.albums[album.name] = album;
		//adds artist to unordered map, checks for dupe artist, then updates info in artsists
		if(Artsists.find(artist.name) != Artsists.end()){
			artist.time += Artsists[artist.name].time;
			artist.nsongs += 1;
			//cout << "Old Artists: " <<  artist.name << endl;
	}
		else{
			//cout << "New Artists: " << artist.name << endl;
		}

		if(Artsists[artist.name].albums.find(album.name) != Artsists[artist.name].albums.end()){
			album.time += Artsists[artist.name].albums[album.name].time;
			album.nsongs += 1; 
		//	cout << "Old Albums: " << album.name << endl;
		}
		else{
		//cout << "New Albums: " << album.name << endl;
		}
	Artsists[artist.name].albums[album.name] = album;
	Artsists[artist.name] = artist;
	}

	fin.close();
}
