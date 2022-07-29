#include <iostream>
#include <cmath>
#include <list>
#include <iterator>

using namespace std;

struct Coord {
	int x, y;
	Coord(){
		x = 0; y = 0;
	}
	Coord(int a, int b){
		x = a;
		y = b;
	}
};
class Figure {
public:
	virtual void Draw() const = 0;
	virtual void Move(int x, int y) = 0;
};
class Point : public Figure {
private:
	Coord coord;
public:
	Point(Coord& c) : coord(c) {}
	void change_point(Coord& c) { coord = c; }
	virtual void Draw() const{
		std::cout << "Абсцисса точки: " << coord.x << ".\n" <<
			"Ордината точки: " << coord.y << ".\n";
	}
	virtual void Move(int x, int y){
		coord.x += x;
		coord.y += y;
	}
};
class line : public Figure{
protected:
	Coord f_point, s_point;
public:
	line(Coord& f, Coord& s) : f_point(f), s_point(s) {}
	void set_coord(Coord& c) { f_point = c; s_point = c; }
	virtual void Draw() const	{
		cout << "Координаты первой точки: " << endl << "(" << f_point.x << "," << f_point.y << ")" << endl;
		cout << "Координаты второй точки: " << endl << "(" << s_point.x << "," << s_point.y << ")" << endl;
	}
	virtual void Move(int x, int y) {
		f_point.x += x;
		f_point.y += y;
		s_point.x += x;
		s_point.y += y;
	}
};
class circle : public Figure{
protected:
	Coord center, c_point;
public:
	circle(Coord c, Coord cp) : center(c), c_point(cp) {} // Конструктор
	void set_coord(Coord c, Coord cp){
		center = c;
		c_point = cp;
	}
	virtual void Draw() const{
		std::cout << "Координаты центра (" << center.x << ", " << center.y << ")" << endl;
		std::cout << "Координаты точки на окружности (" << c_point.x << ", " << c_point.y << ")" << endl;
	}
	virtual void Move(int x, int y){
		center.x += x;
		center.y += y;
		c_point.x += x;
		c_point.y += y;
	}
};
class triangle : public Figure{
protected:
	Coord first_p, second_p, third_p;
public:
	triangle(Coord f, Coord s, Coord t) : first_p(f), second_p(s), third_p(t)
	{}
	void set_coord(Coord c){
		first_p = c; second_p = c; third_p = c;
	}
	virtual void Draw() const{
		cout << "Координаты первой точки треугольника: (" << first_p.x << ", " << first_p.y << ").\n" <<
			"Координаты второй точки треугольника: (" << second_p.x << ", " << second_p.y << ").\n" <<
			"Координаты третьей точки треугольника: (" << third_p.x << ", " << third_p.y << ").\n";
	}
	virtual void Move(int x, int y) {
		first_p.x += x;
		first_p.y += y;
		second_p.x += x;
		second_p.y += y;
		third_p.x += x;
		third_p.y += y;
	}
};
const int SIZE = 100;
class polygon : public Figure{
protected:
	int num;
	Coord arr[SIZE];
public:
	polygon(){

	}
	polygon(int n)
	{
		num = n;
	}
	void set_coord(){
		for (int i = 0; i < num; i++){
			cout << "Введите координаты " << i + 1 << " точки" << endl;
			cin >> arr[i].x;
			cin >> arr[i].y;
		}
	}
	virtual void Draw() const{
		for (int i = 0; i < num; i++){
			cout << "Координата X и У " << i + 1 << " точки :" << endl;
			cout << "(" << arr[i].x << "," << arr[i].y << ")" << endl;
		}
	}
	virtual void Move(int x, int y){
		for (int i = 0; i < num; i++){
			arr[i].x += x;
			arr[i].y += y;
		}
	}
};
class square : public polygon{
protected:
	Coord first_p, second_p, third_p, fourth_p;
public:
	square(Coord f, Coord s, Coord t, Coord fo) : first_p(f), second_p(s), third_p(t), fourth_p(fo)
	{}
	void set_coord(Coord c){
		first_p = c; second_p = c; third_p = c, fourth_p = c;
	}
	virtual void Draw() const{
		cout << "Координаты первой точки квадрата: (" << first_p.x << ", " << first_p.y << ").\n" <<
			"Координаты второй точки квадрата: (" << second_p.x << ", " << second_p.y << ").\n" <<
			"Координаты третьей точки квадрата: (" << third_p.x << ", " << third_p.y << ").\n" <<
			"Координаты четвертой точки квадрата: (" << fourth_p.x << ", " << fourth_p.y << ").\n";
	}
	virtual void Move(int x, int y) {
		first_p.x += x;
		first_p.y += y;
		second_p.x += x;
		second_p.y += y;
		third_p.x += x;
		third_p.y += y;
		fourth_p.x += x;
		fourth_p.y += y;
	}
};
class Drawing {
private:
	std::list<Figure*> figures;
public:
	void add(Figure* f) { figures.push_back(f); }
	void draw() {
		for (Figure* f : figures) {
			f->Draw();
			std::cout << "\n";
		}
	}
	void move(int x, int y) {
		for (Figure* f : figures){
			f->Move(x, y);
			std::cout << "\n";
		}
	}
};
int main(){
	
	setlocale(LC_ALL, "rus");
	Drawing draw;
	
	//Точка
	Coord c(1, 3);
	Point point(c);
	draw.add(&point);
	
	//Линия
	Coord fl(1, 2), sl(2, 2);
	line line(fl, sl);
	draw.add(&line);
	
	//Треуголник
	Coord ft(2, 3), st(5, 6), tt(8, 8);
	triangle triangle(ft, st, tt);
	draw.add(&triangle);
	
	//Круг
	Coord center(0, 0);
	Coord c_point(0, 5);
	circle circle(center, c_point);
	draw.add(&circle);
	
	//Квадрат
	Coord fp(4, 2), sp(5, 7), tp(8, 10), fop(10, 13);
	square sq(fp, sp, tp, fop);
	draw.add(&sq);
	
	//Многоугольник
	polygon p(5);
	p.set_coord();
	draw.add(&p);
	
	std::cout << "Изначальные данные\n";
	draw.draw();
	std::cout << "\n\n";
	int x = 2, y = 3;
	point.Move(x, y);
	line.Move(x, y);
	triangle.Move(x, y);
	circle.Move(x, y);
	sq.Move(x, y);
	
	std::cout << "Новые данные\n";
	draw.draw();
	
	cout << "После перемещения " << endl;
	draw.move(x, y);
	draw.draw();
}

