#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace chrono;

// Función para convertir una imagen a escala de grises de manera secuencial
void convertirAGrisesSecuencial(const Mat& imagenColor, Mat& imagenGris) {
    for (int r = 0; r < imagenColor.rows; r++) {
        for (int c = 0; c < imagenColor.cols; c++) {
            Vec3b pixel = imagenColor.at<Vec3b>(r, c);
            uchar valorGris = 0.299 * pixel[2] + 0.587 * pixel[1] + 0.114 * pixel[0];
            imagenGris.at<uchar>(r, c) = valorGris;
        }
    }
}

int main(int argc, char* argv[]) {
    // Validacion de argumentos de entrada en input
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <imagen_color_entrada> <imagen_gris_salida> <num_hilos>" << endl;
        return EXIT_FAILURE;
    }

    // Definir variables y número de hilos
    string parametroEntrada = argv[1];
    string parametroSalida = argv[2];

    // Funcion para cargar imagen a color
    Mat imagenColor = imread(parametroEntrada, IMREAD_COLOR);

    // Verificar si la imagen se cargó correctamente
    if (imagenColor.empty()) {
        cerr << "Error: No se pudo leer la imagen de entrada." << endl;
        return EXIT_FAILURE;
    }

    // Imprime por pantalla los valores de filas y columnas
    cout << "Cargando imagen..." << endl;
    cout << "Filas (alto): " << imagenColor.rows << " Columnas (ancho): " << imagenColor.cols << endl;

    // Inicio del tiempo de reloj de conversión
    auto inicio = high_resolution_clock::now();

    // Creación de imagen en escala gris
    Mat imagenGris(imagenColor.rows, imagenColor.cols, CV_8UC1);

    // Llamar a la función para convertir a escala de grises de manera secuencial
    convertirAGrisesSecuencial(imagenColor, imagenGris);

    // Tiempo final de reloj de conversión y medición de tiempo
    auto fin = high_resolution_clock::now();
    auto duracion = duration_cast<milliseconds>(fin - inicio);

    // Mensajes de salida por pantalla
    cout << "Inicio de la conversión..." << endl;
    cout << "Fin de la conversión..." << endl;
    cout << "Tiempo total empleado en segundos: " << duracion.count() / 1000.0 << endl;

    // Función para guardar imagen en un nuevo archivo
    imwrite(parametroSalida, imagenGris, {IMWRITE_JPEG_QUALITY, 100});

    // Finaliza la ejecución
    return EXIT_SUCCESS;
}
