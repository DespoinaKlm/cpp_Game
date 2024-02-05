#pragma once
#include <fstream>
#include <iostream>
#include <sgg/graphics.h>
#include "GameObject.h"
#include "GameState.h"
#include "box.h"

using namespace std;

class Blocks:public Box{
private:

	graphics::Brush m_block_brigde_brush;
	graphics::Brush m_block_brush_brigde_debug;
	graphics::Brush m_block_tree_brush;
	graphics::Brush m_block_brush_tree_debug;
	graphics::Brush m_block_rope_brush;
	graphics::Brush m_block_brush_rope_debug;
	

public:
	Blocks(float x, float y, float windth, float heigh);
	Blocks();
	~Blocks();
	inline float getBlockX() {return m_pos_x;}
	inline float getBlockY() { return m_pos_x; }
	inline float getBlockW() { return m_width; }
	inline float getBlockH() { return m_height; }
	void update(float dt, float movement);
	void init() ;
	void draw() ;
};
/*
* string filename = "blocks.txt";

class FileOpener {
private:
	fstream& m_file;
public:
	FileOpener(fstream& file, const char* filename) :m_file(file) {
		m_file.open(filename);
	}
	~FileOpener() {
		m_file.close();
	}
	string readFile(fstream& file,string value1){
		//unsigned short value;
		ifstream file(filename, ios_base::in);
		if (!file) {
			cerr << "Cannot open file\n";
			return "null";
		}
		//file.read((char*)&value,2);
		
		for (string line; getline(file, line);) {
			if (line.find(value1)) {
				return value1;
			}
		}

		if (file.fail()) {
			cerr << "Could not read data\n";
			return "null";
		}
		file.close();
	}
};
*/