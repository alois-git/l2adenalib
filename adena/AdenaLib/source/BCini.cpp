/*
 * BCini.cpp - .ini file loader and creator.
 * Created April 07, 2006, by Michael 'Bigcheese' Spencer.
 */

#include "BCini.h"
#include <iostream>
#include <ostream>

BCini::BCini(const char* filename){
	name = new char[strlen(filename) + 1];
	strcpy(name, filename);
	groups = 0;
	size = len = 0;
	file = new std::fstream;
	file->open(filename, std::fstream::in);
	parse();
};

BCini::~BCini(){
	delete file;
	for(int i = len; i < size; i++){
		if(groups[i] != 0)
			delete groups[i];
	}
	delete[] groups;
	delete[] name;
};

char* BCini::getName(){
	return name;
};

int BCini::getLen(){
	return len;
};

Group& BCini::at(int i){
	return *groups[i];
};

void BCini::growData(){
	Group** tmp = new Group*[size + 10];
	memcpy(tmp, groups, sizeof(Group*) * len);
	if(groups != 0)
		delete[] groups;
	groups = tmp;
	size += 10;
	for(int i = len; i < size; i++){
		groups[i] = 0;
	}
};

Group* BCini::addGroup(const char* key){
	if(len == size)
		growData();
	groups[len] = new Group(key);
	len++;
	return groups[len-1];
};

void BCini::parse(){
	char* buff = new char[BUFFSIZE];
	char* move = 0;
	char* hold = 0;
	Group* curgroup = 0;
	while(file->getline(buff, BUFFSIZE)){
		move = hold = buff;
		
		if(move[0] != 0 || move[0] != ';')
		{
			while(move[0] != 0){
				if(move[0] == '['){ // Starting group.
					// Move to end of line.
					hold = move;
					hold++;
					while(move[0] != ']'){
						move++;
					}
					//at the end.
					move[0] = 0;
					curgroup = addGroup(hold);
					break;
				}
				//Otherwise its a key.
				if(curgroup == 0)
					throw std::exception("Syntax error: Key data not within a group.");

				// Get the key.
				hold = move;
				while(move[0] != '='){
					move++;
				}
				move[0] = 0;
				char* k = hold;
				move++;
				hold = move;

				// Get the data.
				while(move[0] != 0){
					move++;
				}
				move[0] = 0;
				char* d = hold;
				curgroup->addRow(k, d);
				break;
			}
		}else{
		}

	}
	delete[] buff;
};

Group& BCini::operator [](const char* ikey){
	Group* ret = 0;
	for(int i = 0; i < len; i++){
		if(strcmp(groups[i]->getKey(), ikey) == 0){
			ret = groups[i];
			break;
		}
	}
	if(ret == 0)
		ret = addGroup(ikey);
	return *ret;
};

void BCini::flush(){
	file->close();
	std::ofstream f(name, std::ios::trunc);
	f << *this;
	f.close();
	file->open(name,  std::fstream::in);	
};

//=========================================================

Group::Group(const char* ikey){
	size = len = 0;
	rows = 0;
	key = new char[strlen(ikey) + 1];
	memcpy(key, ikey, sizeof(char) * strlen(ikey));
	key[strlen(ikey)] = 0;
};

Group::~Group(){
	for(int i = len; i < size; i++){
		if(rows[i] != 0)
			delete rows[i];
	}
	delete[] key;
};

void Group::growData(){
	Row** tmp = new Row*[size + 10];
	memcpy(tmp, rows, sizeof(Row*) * len);
	if(rows != 0)
		delete[] rows;
	rows = tmp;
	size += 10;
	for(int i = len; i < size; i++){
		rows[i] = 0;
	}
};

char* Group::getKey(){
	return key;
};

Row& Group::operator[] (const char* ikey){
	Row *ret = 0;
	for(int i = 0; i < len; i++){
		if(strcmp(rows[i]->getKey(), ikey) == 0){
			ret = rows[i];
			break;
		}
	}
	if(ret == 0)
		ret = addRow(ikey, "0");
	return *ret;
};

Row* Group::addRow(const char* ikey, const char* idata){
	if(len == size)
		growData();
	rows[len] = new Row(ikey, idata);
	len++;
	return rows[len-1];
};

int Group::getLen(){
	return len;
};

Row& Group::at(int i){
	return *rows[i];
};

//=========================================================

Row::Row(const char* ikey, const char* idata){
	data = 0;
	key = new char[strlen(ikey) + 1];
	memcpy(key, ikey, sizeof(char) * strlen(ikey));
	key[strlen(ikey)] = 0;

	data = new char[strlen(idata) + 1];
	memcpy(data, idata, sizeof(char) * strlen(idata));
	data[strlen(idata)] = 0;
};

Row::~Row(){
	delete[] key;
	delete[] data;
};

char* Row::getKey(){
	return key;
};

char* Row::getData(){
	return data;
};

Row& Row::operator = (int i){
	delete[] data;
	char* tmp = new char[10];
	itoa(i, tmp, 10);
	data = new char[strlen(tmp)];
	strcpy(data, tmp);
	delete[] tmp;
	return *this;
};

Row& Row::operator = (const char* c){
	delete[] data;
	data = new char[strlen(c) + 1];
	strcpy(data, c);
	return *this;
};

//=========================================================

std::ostream& operator << (std::ostream& stream, BCini& ini){
	for(int i = 0; i < ini.getLen(); i++){
		stream << ini.at(i);
	}
	return stream;
};

std::ostream& operator << (std::ostream& stream, Group& g){
	stream << "[" << g.getKey() << "]\n";
	for(int i = 0; i < g.getLen(); i++){
		stream << g.at(i).getKey() << "=" << g.at(i).getData() << "\n";
	}
	return stream;
};

std::ostream &operator << (std::ostream &stream, Row &r){
	stream << r.getData();
	return stream;
};