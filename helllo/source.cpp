#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<vector>
#include"point.h"
#include"fileOoperation.h"
#include<vector>
using namespace std;
using namespace sf;
using namespace project;
vector<point>V;
int main(){
	vector<point> Obstacles;
	Obstacles.clear();
	ifstream myFile;
	myFile.open("Obstacles.txt" , ios::in );
	string line;
	if (myFile.is_open()){
		while ( getline (myFile,line) ){
			string tokens[2];
			int i = line.find(" ");
			int X = atoi((line.substr(0,i)).c_str());
			line.erase(0,i+1);
			int Y = atoi(line.c_str());
			Obstacles.push_back(point(X,Y));
		}
		myFile.close();
	}
	vector<point>  path;
	
	sf::CircleShape shape(1.f);
	shape.setFillColor(Color(250,0,0));
	sf::Time t2=milliseconds(50);
	sf::RenderWindow window(sf::VideoMode(600, 600), "my window");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
		{
            if (event.type == sf::Event::Closed)
                window.close();
        }
		for (int j=0 ; j<Obstacles.size() ; j++)
		{
			shape.setPosition(Obstacles[j].x,Obstacles[j].y);
			sf::sleep(t2);
			window.draw(shape);
			window.display();
		}
		Run(Obstacles,path);
		sf::CircleShape shape2(1.f);
		t2=milliseconds(1000);
		for(int i=0 ; i<path.size() ; ++i)
		{
			//for (int j=0 ; j<path[i].size() ; ++j)
			//{
				shape2.setPosition(path[i].x,path[i].y);
				window.draw(shape2);
				window.display();
				sf::sleep(t2);
			//}
			
		}
		
    }
	

    return 0;
}