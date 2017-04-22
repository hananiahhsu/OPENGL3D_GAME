#pragma once
class TeaPot
{
public:
	TeaPot()
	{

	}
	~TeaPot()
	{

	}
public:

public:
	static void init(void);
	static void display(void);
	static void reshape(int w, int h);
	static void keyboard(unsigned char key, int x, int y);
	static void spinDisplay(void);
	int  main(int argc, char** argv);
};