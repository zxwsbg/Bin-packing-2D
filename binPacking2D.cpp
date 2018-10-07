#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#define NUM_ITEMS 100
#define MAX_LEN 10
#define BIN_SIZE 96

using namespace std;

struct Component2D{
	int horizontal, vertical;
};

ostream& operator<<(ostream& out, const Component2D& comp)
{
	return out << '(' << comp.horizontal << ", " << comp.vertical << ')';
}

class Bin{
	public:
		Bin(): nextPos(), currentShelfHeight(1), dimensions{BIN_SIZE, BIN_SIZE} {}
			   
		void shelfChange()
		{
			nextPos.horizontal = 0;
			nextPos.vertical += currentShelfHeight; //old shelf height
			currentShelfHeight = 1; //new shelf height
		}
		
		//Getters
		unsigned getWidth() {return dimensions.horizontal;}
		
		unsigned getHeight() {return dimensions.vertical;}
		   
		unsigned getNextX() {return nextPos.horizontal;}
		
		unsigned getNextY() {return nextPos.vertical;}
		
		Component2D getNextPos() {return nextPos;}
		
		unsigned getCurrentShelfHeight() {return currentShelfHeight;}
		
		//Setters
		void incNextX(unsigned amount) {nextPos.horizontal += amount;}
		
		void setCurrentShelfHeight(unsigned nsh) {currentShelfHeight = nsh;}
		
	private:
		unsigned currentShelfHeight;
		Component2D dimensions, nextPos;
};

class Item{
	public:
		Item(): position(), dimensions{rand()%MAX_LEN+1, rand()%MAX_LEN+1} {}
		
		void shelfNextFitInto(Bin *bin)
		{
			//check if item fits in the shelf width-wise
			if(bin->getNextX() + dimensions.horizontal > bin->getWidth())
				bin->shelfChange();
				
			//check if item is taller than the shelf
			if(dimensions.vertical > bin->getCurrentShelfHeight())
				bin->setCurrentShelfHeight(dimensions.vertical);
				
			setPos(bin->getNextPos());
			bin->incNextX(dimensions.horizontal);
		}
		
		void setPos(Component2D nPos) {position = nPos;}
		
		void toStr() {cout << position << ' ' << dimensions << endl;}
		
	private:
		Component2D dimensions,
					position; //Topleft corner
};

int main(void)
{
	Bin bin;
	srand(time(NULL));
	vector<Item> items(NUM_ITEMS);
	
	cout << "Position | Dimensions" << endl;
	for(Item item: items)
	{
		item.shelfNextFitInto(&bin);
		item.toStr();
	}
	return 0;
}
