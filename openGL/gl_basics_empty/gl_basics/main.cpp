#include <iostream>
#include <vector>

#include <QApplication>
#if QT_VERSION_MAJOR >= 6
    #include <QtOpenGLWidgets/QOpenGLWidget>
#else
    #include <QOpenGLWidget>
#endif
#include <QOpenGLFunctions_3_3_Core>



////////////////////////////////////////////////////////////////////////////////
//! Kod zrodlowy shadera wierzcholkow (finalnie do przeniesienia do osobnego pliku)
const char* vshader = "#version 330\n"
        "layout (location=4) in vec3 pos;"
        "void main() {gl_Position = vec4(pos,1);}"; // musimy dopisac ten 4 elementowy wector
//! Kod zrodlowy shadera fragmentow (finalnie do przeniesienia do osobnego pliku)
const char* fshader = "#version 330\n"
            "out vec4 FragColor"
            "void main() {FragColor = vec4(1,0,0,1);}";



////////////////////////////////////////////////////////////////////////////////
/**
 * @brief PRINT_GL_ERRORS - funkcja przeglada stos bledow opengl, jezeli na stosie sa bledy, drukuje je na konsoli
 * @param mess - dowolny string, ktory bedzie wyswietlony przed opisem bledu
 */
#include <GL/glu.h>
void PRINT_GL_ERRORS(const char* mess)
{
    GLenum err;
    while( (err=glGetError()) != GL_NO_ERROR)
        std::cout << "ERROR in: " << mess <<(const char*)gluErrorString(err) << std::endl;
}



////////////////////////////////////////////////////////////////////////////////
//!Pomocnicze struktury do przechowywania pozycji i atrybutow wierzcholkow.
struct vec3 {float x,y,z;};
struct vec4 {float x,y,z,w;};



////////////////////////////////////////////////////////////////////////////////
/// \brief The Window class - klasa, ktora stanowi okno naszej aplikacji
/// i zawiera w sobie kontekst opengl-a.
/// Najlepiej przeniesc do osobnych plikow .h i .cpp
class Window : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    std::vector<vec3> pos; //!tablica zawierajaca wspolrzedne wierzcholkow
    std::vector<vec4> colors;
    int pos_index; //!index, pod ktorym bedzie powiazany bufor wierzcholkow z atrybutem w shaderze

    GLuint vbo; //!uchwyt do bufora wierzcholkow, liczba reprezentujaca dany zasob opengl
    GLuint vao; //!uchwyt do tablicy obiektow buforowych
    GLuint vbc;
    GLuint shaderProgram; //!uchwyt do programu shadera

    //!Pomocnicza funkcja wyswietlajaca potencjalne bledy kompilacji shadera
    bool checkShaderStatus(GLuint shader)
    {
        GLint stat;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &stat);
        if(stat == GL_FALSE)
        {
            GLchar infoLog[10240];
            glGetShaderInfoLog(shader, 10240, NULL, infoLog);
            std::cout << "Shader ERROR: " << infoLog << std::endl;
            return false;
        }
        return true;
    }

    //!Pomocnicza funkcja wyswietlajaca potencjalne bledy linkowania programu shadera
    bool checkProgramStatus(GLuint program)
    {
        GLint stat;
        glGetProgramiv(program, GL_LINK_STATUS, &stat);
        if(stat == GL_FALSE)
        {
            GLchar infoLog[10240];
            glGetProgramInfoLog(program, 10240, NULL, infoLog);
            std::cout << "Program ERROR: " << infoLog << std::endl;
            return false;
        }
        return true;
    }

protected:
    /**
     * @brief initializeGL - reimplementacja metody; wywolywana po konstrukcji obiektu klasy
     * ale przed pierwszym wywolaniem resizeGL() i paintGL().
     * W tej funkcji mamy gwarancje, ze kontekst opengl jest juz utworzony.
     * To jest odpowiednie miejsce do setup-u opengla i sceny.
     */
    void initializeGL() override
    {
        //!Wywolanie metody z klasy QOpenGLFunctions; niezbedne do utawienia odpowiednich wskaznikow do funkcji opengl
        initializeOpenGLFunctions();

        //!Wypisanie wersji opengl
        std::cout << (const char*)glGetString(GL_VERSION) << std::endl;



        pos = {{0,0,0},{1,1,0},{0.5,-0.5,0}};
        colors = {{1,0,0,1},{0,1,0,1},{0,1,1,1}};

        glGenVertexArrays(1,&vao);
        glBindVertexArray(vao);


        glGenBuffers(1,&vbo);
        glGenBuffers(1,&vbc);

        glBindBuffer(GL_ARRAY_BUFFER,vbo);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,0,0);
        glBufferData(GL_ARRAY_BUFFER,
                     pos.size() * sizeof(vec3),
                     pos.data(),
                     GL_STATIC_DRAW);



//        glBindBuffer(GL_ARRAY_BUFFER,0); deaktyvacja bufora
//        glVertexAttribArray(0); deaktyvacja bufora



//        glBindBuffer(GL_ARRAY_BUFFER,vbc);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glVertexAttribPointer(7,4,GL_FLOAT,GL_FALSE,0,0);
        glBindBuffer(GL_ARRAY_BUFFER,vbc);
        glEnableVertexAttribArray(7);

        glBufferData(GL_ARRAY_BUFFER,
                     colors.size() * sizeof(vec4),
                     colors.data(),
                     GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);

        shaderProgram = glCreateProgram();

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        GLchar* srcs[] = {(GLchar*)vshader};
        glShaderSource(vs,1,srcs,NULL);
        glCompileShader(vs);
        if(checkShaderStatus(vs)){
            glAttachShader(shaderProgram,vs);
            glDeleteShader(vs);
        }



        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        GLchar* frcs[] = {(GLchar*)vshader};
        glShaderSource(fs,1,frcs,NULL);
        glCompileShader(fs);
        if(checkShaderStatus(fs)){
            glAttachShader(shaderProgram,fs);
            glDeleteShader(fs);
        }



        glLinkProgram(shaderProgram);

        PRINT_GL_ERRORS("init");
    }

    /**
     * @brief paintGL - reimplementacja metody; wywolywana zawsze gdy jest potrzeba
     * odrysowania widgetu. Nie wywolujemy jej nigdy jawnie.
     * Jezeli jest potrzeba odrysowania sceny, wywolujemy te funkcje niejawnie,
     * poprzez metode update()
     */
    void paintGL() override
    {
        //!Kolor czyszczenia bufora kolorów, (r,g,b,a) in <0.0; 1.0>
        glClearColor(0.5, 0.5, 1.0, 1.0);

        //!Wyczyszczenie bufora kolorow i glebi
        glClear(GL_COLOR_BUFFER_BIT);


        glUseProgram(shaderProgram);


        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES,0,3);
        glBindVertexArray(0);


        glUseProgram(0);


        PRINT_GL_ERRORS("paint");
    }

    /**
     * @brief resizeGL - reimplementacja metody; wywolywana jest zawsze gdy
     * okienko pojawia się lub zmienia swoj rozmiar.
     * Dobre miejsce do wywolania niezbednych funkcji, do setupu sceny zaleznych
     * od wielkosci okna, np. glViewport() lub aktualizacji macierzy projekcji.
     * @param w - w tym parametrze bedzie nowa szerokosc okna
     * @param h - w tym parametrze bedzie nowa wysokosc okna
     */
    void resizeGL(int w, int h) override
    {
        glViewport(0,0,w,h);
    }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //!Utworzenie i wyswietlenie okna aplikacji
    Window w;
    w.show();

    return a.exec();
}
