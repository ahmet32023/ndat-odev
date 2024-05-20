#include <GL/glut.h>
#include <vector>
#include <string>
#include <iostream>

// Pencere boyutlar�
const int PEN_BOY = 800;
const int PEN_EN = 600;

// Oyun alan� boyutlar�
const int ALAN_BOY = 800;
const int ALAN_EN = 600;

// Y�lan �zellikleri
const int y�lan_boy = 20;
const int y�lan_boy_ilk = 3;
std::vector<std::pair<int, int>> snake;
int y�lanX = 1; // Y�lan�n X eksenindeki hareket y�n�
int y�lanY = 0; // Y�lan�n Y eksenindeki hareket y�n�

// Yiyecek �zellikleri
int yemX;
int yemY;

// Ba�lang�� men�s�nde d�nen k�p �zellikleri
float menuCubeRotation = 0.0f;

// Oyun durumu
bool oyun_baslad� = false;
bool oyun_bitti = false;
bool baslangic_menu = true;
bool hazirlayanlar_acik = false;

// Skor
int skor = 0;






void baslangicMenuCiz() {
    // K�p� d�nd�rme a��s�
    menuCubeRotation += 3.0f;


    // "Oyuna Ba�la" se�ene�i
    glColor3f(1.0, 1.0, 1.0); // Beyaz renk
    glRasterPos2f(ALAN_BOY / 2 - 80, ALAN_EN / 2 + 50);
    std::string oyunaBaslaMesaji = "Oyuna Basla (Space)";
    for (char const& c : oyunaBaslaMesaji) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }


    // "Haz�rlayanlar" se�ene�i
    glRasterPos2f(ALAN_BOY / 2 - 80, ALAN_EN / 2 - 60);
    std::string hazirlayanlarMesaji = "Hazirlayanlar (H)";
    for (char const& c : hazirlayanlarMesaji) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    if (hazirlayanlar_acik) {
        glColor3f(1.0, 1.0, 1.0); // Beyaz renk
        glRasterPos2f(ALAN_BOY / 2 - 60, ALAN_EN / 2 - 100);
        std::string hazirlayanlarIsimler = "Fatih UNAL NO:200401011";
        for (char const& c : hazirlayanlarIsimler) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        glRasterPos2f(ALAN_BOY / 2 - 60, ALAN_EN / 2 - 120);
        hazirlayanlarIsimler = "Ahmet SARI NO:210401033";
        for (char const& c : hazirlayanlarIsimler) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        glRasterPos2f(ALAN_BOY / 2 - 60, ALAN_EN / 2 - 140);
        hazirlayanlarIsimler = "Oyku KURTGOZ NO:210401131";
        for (char const& c : hazirlayanlarIsimler) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        glRasterPos2f(ALAN_BOY / 2 - 60, ALAN_EN / 2 - 160);
        hazirlayanlarIsimler = "Buse Nur YILMAZ NO:210401101";
        for (char const& c : hazirlayanlarIsimler) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }
    }


}


void y�lan�iz() {
    glColor3f(0.0, 1.0, 0.0); // Ye�il renk
    for (auto const& segment : snake) {
        glRectf(segment.first, segment.second, segment.first + y�lan_boy, segment.second + y�lan_boy);
    }
}

void yem�iz() {
    glColor3f(1.0, 0.0, 0.0); // K�rm�z� renk
    glRectf(yemX, yemY, yemX + y�lan_boy, yemY + y�lan_boy);
}

void skorCiz() {
    glColor3f(1.0, 1.0, 1.0); // Beyaz renk
    glRasterPos2f(10, 10);
    std::string skorMesaji = "Skor: " + std::to_string(skor);
    for (char const& c : skorMesaji) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (baslangic_menu) {
        baslangicMenuCiz();
    }

    else if (!oyun_bitti) {
        // Y�lan�, yiyece�i ve k�p� �iz
        y�lan�iz();
        yem�iz();
        skorCiz();
    }
    else {
        // Oyun bitti�inde ekrana bir mesaj yazd�rabilirsiniz
        glColor3f(1.0, 1.0, 1.0); // Beyaz renk
        glRasterPos2f(ALAN_BOY / 2 - 60, ALAN_EN / 2);
        std::string gameOverMsg = "Game Over!";
        for (char const& c : gameOverMsg) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);
        }
    }

    // K�p� �iz
    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0); // Mavi renk
    glTranslatef(ALAN_BOY / 2.0f, 300.0f, 1.0f); // K�p�n ba�lang�� pozisyonunu ayarla
    glRotatef(menuCubeRotation, 100.0f, 100.0f, 1.0f); // K�p� d�nd�r
    glutSolidCube(50.0); // 50 birim kenar uzunlu�unda bir dolu k�p �iz
    glPopMatrix();

    glutSwapBuffers();
}


void yenile(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, ALAN_BOY, 0, ALAN_EN);
    glMatrixMode(GL_MODELVIEW);
}

void baslat(int value) {
    if (!baslangic_menu) {
        if (oyun_baslad� && !oyun_bitti) {
            // Y�lan� hareket ettir
            int newX = snake[0].first + y�lanX * y�lan_boy;
            int newY = snake[0].second + y�lanY * y�lan_boy;

            // Y�lan�n kendine �arpmas�n� kontrol et
            for (int i = 1; i < snake.size(); i++) {
                if (newX == snake[i].first && newY == snake[i].second) {
                    oyun_bitti = true;
                    break;
                }
            }

            if (!oyun_bitti) {
                // Y�lan�n ekran�n d���na ��kmas�n� kontrol et
                if (newX < 0 || newX >= ALAN_BOY || newY < 0 || newY >= ALAN_EN) {
                    oyun_bitti = true;
                }
                else {
                    // Y�lan�n ba��n� g�ncelle
                    snake.insert(snake.begin(), std::make_pair(newX, newY));

                    // Yiyecek yendi mi kontrol et
                    if (newX == yemX && newY == yemY) {
                        // Y�lan�n boyunu uzat
                        skor += 10;
                        // Yeni yiyecek konumu olu�tur
                        yemX = (rand() % (ALAN_BOY / y�lan_boy)) * y�lan_boy;
                        yemY = (rand() % (ALAN_EN / y�lan_boy)) * y�lan_boy;
                    }
                    else {
                        // Y�lan�n sonundaki kuyru�u sil
                        snake.pop_back();
                    }
                }
            }
        }

        menuCubeRotation += 1.0f; // Ba�lang�� men�s�nde d�nen k�p� her frame'de d�nd�r
    }

    glutPostRedisplay();
    glutTimerFunc(100, baslat, 0);
}
void klavye(unsigned char key, int x, int y) {
    switch (key) {
    case ' ': // 'bo�luk' tu�una bas�ld���nda oyunu ba�lat
        if (baslangic_menu) {
            baslangic_menu = false;
            oyun_baslad� = true;
        }
        break;
    case 'h': // 'h' tu�una bas�ld���nda "Haz�rlayanlar" men�s�n� a�
        if (baslangic_menu) {
            hazirlayanlar_acik = !hazirlayanlar_acik;
        }
        break;
    case 27: // ESC tu�una bas�ld���nda ��k�� yap
        exit(0);
        break;
    case 'w': // Yukar� ok tu�una bas�ld���nda y�lan�n y�n�n� yukar� de�i�tir
        if (y�lanY != -1) {
            y�lanX = 0;
            y�lanY = 1;
        }
        break;
    case 's': // A�a�� ok tu�una bas�ld���nda y�lan�n y�n�n� a�a�� de�i�tir
        if (y�lanY != 1) {
            y�lanX = 0;
            y�lanY = -1;
        }
        break;
    case 'a': // Sol ok tu�una bas�ld���nda y�lan�n y�n�n� sola de�i�tir
        if (y�lanX != 1) {
            y�lanX = -1;
            y�lanY = 0;
        }
        break;
    case 'd': // Sa� ok tu�una bas�ld���nda y�lan�n y�n�n� sa�a de�i�tir
        if (y�lanX != -1) {
            y�lanX = 1;
            y�lanY = 0;
        }
        break;
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(PEN_BOY, PEN_EN);
    glutCreateWindow("Y�lan Oyunu");
    glutDisplayFunc(display);
    glutReshapeFunc(yenile);
    glutTimerFunc(0, baslat, 0);
    glutKeyboardFunc(klavye);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    // Y�lan�n ba�lang�� pozisyonunu belirle
    int initialSnakeX = ALAN_BOY / 2;
    int initialSnakeY = ALAN_EN / 2;
    for (int i = 0; i < y�lan_boy_ilk; i++) {
        snake.push_back(std::make_pair(initialSnakeX - i * y�lan_boy, initialSnakeY));
    }

    // �lk yiyecek konumunu belirle
    yemX = (rand() % (ALAN_BOY / y�lan_boy)) * y�lan_boy;
    yemY = (rand() % (ALAN_EN / y�lan_boy)) * y�lan_boy;

    glutMainLoop();

    return 0;
}
