#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include <sstream>
#include <string>

using namespace std;

#define WINDOWS_WIDHT 320
#define WINDOWS_HEIGHT 320

enum Color
{
    red = 0x000000FF,
    green = 0x0000FF00,
    blue = 0x00FF0000,
    yellow = 0x0000FFFF,
};

void ColorChannels(Color color, unsigned int &red, unsigned int &green, unsigned int &blue, unsigned int &alpha)
{
    unsigned int int_color = color;
    alpha = int_color>>24;
    int_color <<= 8;
    int_color >>= 8;
    blue = int_color>>16;
    int_color <<= 16;
    int_color >>= 16;
    green = int_color>>8;
    int_color <<= 24;
    int_color >>= 24;
    red = int_color;
}

class Shape
{
protected:
    Color color;
    unsigned int WindowPositionX;
    unsigned int WindowPositionY;
public:
    Shape(Color color, unsigned int WindowPositionX, unsigned int WindowPositionY):color(color)
    {
        set_WindowPositionX(WindowPositionX);
        set_WindowPositionY(WindowPositionY);
    }
    void set_WindowPositionX(unsigned int WindowPositionX)
    {
        this->WindowPositionX = WindowPositionX;
    }
    void set_WindowPositionY(unsigned int WindowPositionY)
    {
        this->WindowPositionY = WindowPositionY;
    }
    virtual ~Shape(){}

    virtual double get_area() const = 0;
    virtual double  get_perimeter() const = 0;
    virtual void draw(int argc, char **argv) const = 0;
    virtual void info(int argc, char **argv) const
    {
        cout << "Площадь: " << get_area() << endl;
        cout << "Периметр: " << get_perimeter() << endl;
        draw(argc, argv);
    }
};

class Rectangle:public Shape
{
    static const int MIN_LENGTH = 5;
    static const int MAX_LENGTH = min(WINDOWS_WIDHT,WINDOWS_HEIGHT);
    double lenght;
    double width;
public:
    double get_lenght() const
    {
        return lenght;
    }
    double get_width() const
    {
        return width;
    }
    void set_lenght(double lenght)
    {
        if (lenght < MIN_LENGTH) lenght = MIN_LENGTH;
        if (lenght > MAX_LENGTH) lenght = MAX_LENGTH;
        this->lenght = lenght;
    }
    void set_width(double width)
    {
        if (width < MIN_LENGTH) width = MIN_LENGTH;
        if (width > MAX_LENGTH) width = MAX_LENGTH;
        this->width = width;
    }
    Rectangle(double lenght, double width, Color color, unsigned int WindowPositionX, unsigned int WindowPositionY): Shape(color,WindowPositionX,WindowPositionY)
    {
        set_lenght(lenght);
        set_width(width);
    }
    double get_area() const
    {
        return lenght*width;
    }
    double get_perimeter() const
    {
        return (lenght+width)*2;
    }
    void draw(int argc, char **argv) const
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(WINDOWS_WIDHT, WINDOWS_HEIGHT);
        glutInitWindowPosition(WindowPositionX, WindowPositionY);

        stringstream sstream;
        sstream << hex << (unsigned long long) this;
        string StrPointer = sstream.str();
        string Title = typeid(*this).name();
        Title.append(" ");
        Title.append(StrPointer);
        glutCreateWindow(Title.c_str());

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT);

        unsigned int red {0}, green {0}, blue {0}, alpha {0};
        ColorChannels(color, red, green, blue, alpha);
        glColor4f(red,green,blue,alpha);

        glRectd(-lenght/WINDOWS_HEIGHT,width/WINDOWS_WIDHT,lenght/WINDOWS_HEIGHT,-width/WINDOWS_WIDHT);
        glFlush();
        glutMainLoop();
    }
    void info(int argc, char **argv) const
    {
        cout << typeid(*this).name() << " " << this << endl;
        cout << "Длина: " << get_lenght() << endl;
        cout << "Ширина: " << get_width() << endl;
        Shape::info(argc, argv);
    }
};

class Square:public Rectangle
{
public:
    Square(double side, Color color, unsigned int WindowPositionX, unsigned int WindowPositionY): Rectangle(side, side, color, WindowPositionX, WindowPositionY){}
    void info(int argc, char **argv) const
    {
        cout << typeid(*this).name() << this << endl;
        cout << "Длина стороны: " << get_lenght() << endl;
        Shape::info(argc, argv);
    }
};

class Circle:public Shape
{
    static const int MIN_RADIUS = 5;
    static const int MAX_RADIUS = min(WINDOWS_WIDHT,WINDOWS_HEIGHT)/2;
    double radius;
public:
    double get_radius() const
    {
        return radius;
    }
    void set_radius(double radius)
    {
        if (radius < MIN_RADIUS) radius = MIN_RADIUS;
        if (radius > MAX_RADIUS) radius = MAX_RADIUS;
        this->radius = radius;
    }
    Circle(double radius, Color color, unsigned int WindowPositionX, unsigned int WindowPositionY): Shape(color,WindowPositionX,WindowPositionY)
    {
        set_radius(radius);
    }
    double get_area() const
    {
        return M_PI*radius*radius;
    }
    double get_perimeter() const
    {
        return 2*M_PI*radius;
    }
    void info(int argc, char **argv) const
    {
        cout << typeid(*this).name() << " " << this << endl;
        cout << "Радиус: " << get_radius() << endl;
        Shape::info(argc, argv);
    }
    void draw(int argc, char **argv) const
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(WINDOWS_WIDHT, WINDOWS_HEIGHT);
        glutInitWindowPosition(WindowPositionX, WindowPositionY);

        stringstream sstream;
        sstream << hex << (unsigned long long) this;
        string StrPointer = sstream.str();
        string Title = typeid(*this).name();
        Title.append(" ");
        Title.append(StrPointer);
        glutCreateWindow(Title.c_str());

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT);

        unsigned int red {0}, green {0}, blue {0}, alpha {0};
        ColorChannels(color, red, green, blue, alpha);
        glColor4f(red,green,blue,alpha);

        glutSolidSphere(radius/MAX_RADIUS,100,100);
        glFlush();
        glutMainLoop();
    }
};

class Triangle:public Shape
{
public:
    virtual double get_height() const = 0;
    Triangle(Color color, unsigned int WindowPositionX, unsigned int WindowPositionY): Shape(color,WindowPositionX,WindowPositionY) {}
};

class IsoscelesTriangle:public Triangle
{
    static const int MIN_SIDE = 5;
    static const int MAX_SIDE = min(WINDOWS_HEIGHT,WINDOWS_WIDHT);
    double base;
    double side;
public:
    double get_base() const
    {
        return base;
    }
    double get_side() const
    {
        return side;
    }
    void set_base(double base)
    {
        if (base<MIN_SIDE) base = MIN_SIDE;
        if (base>MAX_SIDE) base = MAX_SIDE;
        this->base = base;
    }
    void set_side(double side)
    {
        if (side<MIN_SIDE) side = MIN_SIDE;
        if (side>MAX_SIDE) side = MAX_SIDE;
        this->side = side;
    }
    IsoscelesTriangle(double base, double side, Color color, unsigned int WindowPositionX, unsigned int WindowPositionY): Triangle(color, WindowPositionX, WindowPositionY)
    {
        set_base(base);
        set_side(side);
    }
    double get_height() const
    {
        return sqrt(side*side-(base/2)*(base/2));
    }
    double get_area() const
    {
        return base*get_height()/2;
    }
    double get_perimeter() const
    {
        return base+side*2;
    }
    void draw(int argc, char **argv) const
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutInitWindowSize(WINDOWS_WIDHT, WINDOWS_HEIGHT);
        glutInitWindowPosition(WindowPositionX, WindowPositionY);

        stringstream sstream;
        sstream << hex << (unsigned long long) this;
        string StrPointer = sstream.str();
        string Title = typeid(*this).name();
        Title.append(" ");
        Title.append(StrPointer);
        glutCreateWindow(Title.c_str());

        glClearColor(1.0, 1.0, 1.0, 1.0);
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT);

        unsigned int red {0}, green {0}, blue {0}, alpha {0};
        ColorChannels(color, red, green, blue, alpha);
        glColor4f(red,green,blue,alpha);

        glBegin(GL_TRIANGLES);
            glVertex2d(-base/WINDOWS_WIDHT,-get_height()/WINDOWS_HEIGHT);
            glVertex2d(0,get_height()/WINDOWS_HEIGHT);
            glVertex2d(base/WINDOWS_WIDHT,-get_height()/WINDOWS_HEIGHT);
        glEnd();

        glFlush();
        glutMainLoop();
    }
    void info(int argc, char **argv) const
    {
        cout << typeid(*this).name() << " " << this << endl;
        cout << "Основание: " << get_base() << endl;
        cout << "Боковая сторона: " << get_side() << endl;
        Shape::info(argc, argv);
    }
};

class EquilateralTriangle:public IsoscelesTriangle
{
public:
    EquilateralTriangle(double side, Color color, unsigned int WindowPositionX, unsigned int WindowPositionY): IsoscelesTriangle(side, side, color, WindowPositionX, WindowPositionY){};
    void info(int argc, char **argv) const
    {
        cout << typeid(*this).name() << this << endl;
        cout << "Длина стороны: " << get_side() << endl;
        Shape::info(argc, argv);
    }
};

int main(int argc, char **argv) {
    setlocale(LC_ALL, "Russian");

    /*Rectangle rect(300,200,Color::red, 450, 100);
    rect.info(argc, argv);*/

    /*Square square(8, Color::console_green);
    square.info();*/

    /*Circle circle(15, Color::yellow, 250, 100);
    circle.info(argc, argv);*/

    /*IsoscelesTriangle triangle(200,250,Color::green,450,120);
    triangle.info(argc, argv);*/

    EquilateralTriangle eq_triangle(200,Color::green,450,120);
    eq_triangle.info(argc, argv);

    return 0;
}
